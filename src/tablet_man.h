#ifndef  TABLET_MAN_H
#define TABLET_MAN_H 1

#include "tablets/c_tablet.h"
#include "rfile/rfile_tablet.h"
#include "ioexceptions.h"
#include <ctime>
#include "MemoryStore.h"
#include "./data-objects/containers/KeyValueStore.h"
#include "../ingestmon/ingestconfig_types.h"


/*
	Tablet Manager is responsible for initializing tablets and allocating the memory
	that they will use.
*/
/**
 * @file tablet_man.h
 * @author Marc Parisi
 * @section Description
 * Tablet manager is responsible for initializing tablets and
 * allocating the memory through the Memory Store
 */

namespace IO
{

  using namespace IO::Tablet;
  using namespace IO::DataObjects::Containers;

class TabletManager
{
public:
	/**
	 * Constructor, accepts the configuration, the intitial
	 * time stamp, and the number of estimated records
	 * @param configuratoin incoming configuration
	 * @param intitial_ts initial time stamp
	 * @param records number of estimated records
	 */

	TabletManager(
		IngestConfiguration *configuration,
		uint64_t initial_ts = 0,
		uint64_t records = 0) : config( configuration )
	{
		//pf_init_api(configuration->file_read_size);
		pthread_mutex_init( &tabletManagerLock, NULL );

		keyValueStores = NULL;
		tablets = NULL;

		tablets_ready = false;

		if (records != 0)
		{
			tablet_record_size = records;
		}
		else
		{
			tablet_record_size = configuration->max_tablet_rows;
		}

	}


    void init()
    {
        create_memory_store();
		create_tablets( initial_ts, tablet_record_size );
		spawn_init(initial_ts);
    }


	// free memory associated with the tablets.
	virtual ~TabletManager()
	{
		if (tablets != NULL)
		{
		  for(int i=0; i < tabletCount; i++)
		    delete tablets[i];
		  delete [] tablets;
		}

		if (keyValueStores != NULL);
		{
		  for(int i=0; i < keyValueStoreSize; i++)
		    delete keyValueStores[i];
		  delete [] keyValueStores;
		}
	}

	// locks the tablet manager, if it is usjob_configurationed among  threads
	void lock()
	{
		pthread_mutex_lock( &tabletManagerLock );
	}

	// unlocks the tablet manager.
	void unlock()
	{
		pthread_mutex_unlock( &tabletManagerLock );
	}


	// retrieves the tablets
	IO::Tablet::Tablet **getTablets()
	{
	    if (tablets == NULL)
	    {
	        throw TabletException("Not initialized");
	    }
		return tablets;
	}

	/**
	 * Returns the tablet cthrow TabletException("Cannot create tablets");ount;
	 * @returns tablet count
	 */
	uint32_t getTabletCount()
	{
	  return tabletCount;
	}

	// identifies that the tablets are ready for use
	bool tabletsReady()
	{
	    if (tablets == NULL )
	    {
	        init(); // let's call this for the user.
	    }
		return tablets_ready;
	}

	// returns the amount of milliseconds it took to allocate
	// memory for the tablets
	uint64_t getMemoryCreationTime()
	{
		return memoryCreationTime;
	}

	// reinitializes the tablets with their row id
	/*
	void reInit(uint64_t initial_ts)
	{
		char shard_id[SHARD_ID_LENGTH];

		for (int i = config->max_tablet_count-1; i >= 0; i--) {
			SHARD_IDENTIFIER(initial_ts,i,shard_id,SHARD_ID_LENGTH);
			cout << "setting shard id to " << shard_id << endl;
			tablets[i].setRow(shard_id,SHARD_ID_LENGTH);
		}
	}
	*/

	// returns the key values stores
	MemoryStore **getKeyValueStore()
	{
	    if (keyValueStores == NULL)
	    {
	        throw TabletException("Not initialized");
	    }
		return keyValueStores;
	}

	uint32_t getKeyValueStoreSize()
	{
		return keyValueStoreSize;
	}

	IngestConfiguration *getConfiguration()
	{
		return config;
	}



protected:

    /**
     * Create the memory store
     *
     */
    virtual void create_memory_store()
    {
        if (config->debug)
		{
			cout << "Creating " << (config->concurrent_index_threads+1) << " KeyValue arrays, each containing " << config->max_tablet_rows << endl;
		}
        keyValueStores = new MemoryStore*[ config->concurrent_index_threads+1  ]();
		for(int i=0; i < config->concurrent_index_threads+1; i++)
		  keyValueStores[i] = new KeyValueStore();
		if (keyValueStores == NULL)
		{
			throw TabletException("Cannot create tablets");
		}

		keyValueStoreSize = config->concurrent_index_threads+1 ;
    }

	/**
	 * Creates the tablets using the intiial time stamp and the number
	 * of records specified by the records count.
	 * @param init_ts initial time stamp
	 * @param records number of initial records
	 */
	virtual void create_tablets(const uint64_t init_ts,const  uint32_t records)
	{

		// create tablet memory, allocate enough memory for all working
		// threads. What we're doing is sharing the memory among the tablets.

		// create the tablet objects.
		tabletCount = config->max_tablet_count ;
		tablets = new IO::Tablet::Tablet*[ config->max_tablet_count ];
		cout << "oldie" << endl;
		for(int i=0; i < tabletCount; i++)
		{
		  tablets[i] = new RFileTablet();
		}
		if (tablets == NULL)
		{
			throw TabletException("Cannot create tablets");
		}

	    // init and set the maximum records allowed in the tablet.
		for (int i = 0; i < config->max_tablet_count ; i++) {
			tablets[i]->init(i);
			tablets[i]->setMaxFileCount( records );
		}



	}


    /**
     * Spawn the tablet initialization.
     * @param init_ts initial timestamp.
     **/
	void spawn_init(const uint64_t init_ts)
	{
		pthread_t tablet_thread;

		setInitialTimeStamp( init_ts );

		pthread_create( &tablet_thread, NULL, &TabletManager::tablet_init_fp, this);
	}

	/**
	 * Sets the initial ts
	 * @param ts time stamp
	 */
	void setInitialTimeStamp(const uint64_t ts)
	{
		initial_ts = ts;
	}



	static void *allocateMemory(void *obj)
	{
		PMEM_ALLOC memAlloc = (PMEM_ALLOC)obj;

		memAlloc->kvList[ memAlloc->i ]->allocate(  memAlloc->allocationSize  );

	}

	static long allocate_memory(TabletManager *tabMan)
	{
		int allocations = tabMan->config->concurrent_index_threads+1;

		MEM_ALLOC allocator[allocations];
		pthread_t threads[allocations];

		struct timeval start, end;

		gettimeofday(&start, NULL);


		int i=0;
		for(i = 0; i < allocations; i++)
		{
			allocator[i].kvList = tabMan->getKeyValueStore();
			allocator[i].i = i;
			allocator[i].allocationSize = tabMan->getConfiguration()->max_tablet_rows;
			pthread_create( &threads[i], NULL, &TabletManager::allocateMemory, &allocator[i]);
		}
		for(i = 0; i < allocations; i++)
		{
		      pthread_join( threads[i], NULL );
		}


		gettimeofday(&end, NULL);
		long seconds, useconds;

		gettimeofday(&end, NULL);
		seconds = end.tv_sec - start.tv_sec;
		useconds = end.tv_usec - start.tv_usec;

		return (long)((seconds) * 1000 + useconds / 1000.0) + 0.5;
	}



	/*
		Purpose, initializes the tablets using the tablet loader.
	*/
	virtual void init_tablets(uint64_t init_ts, uint64_t number_records ) {

		unsigned short i = 0, j = 0;

		char shard_id[2]= {0x01, 0x00};

		if (config->debug)
		{
			cout << "config tablet count is " << config->max_tablet_count << endl;
		}


		for (i = config->max_tablet_count-1; i != 0; i--) {
				tablets[i]->setRow(shard_id,2);
				tablets[i]->setMaxFileCount( number_records );

		}


	}

	/*
		Function pointer to initialize the tablets.
	*/
	static void *tablet_init_fp(void *obj)
	{

		TabletManager *tabletMan = reinterpret_cast<TabletManager *>(obj);

		tabletMan->init_tablets( tabletMan->initial_ts, tabletMan->tablet_record_size );

		tabletMan->memoryCreationTime = allocate_memory( tabletMan );

		tabletMan->tablets_ready = true;

		pthread_exit(NULL);
	}

	// intiial timestamp, initially in a separate structure called
	// TABLET_LOADER; however, this is a function of the tablet manager
	// so there is no need to keep it externally
	uint64_t initial_ts;
	// size of keyValueStores
	uint32_t keyValueStoreSize;

	// number of records for each
	// tablet
	uint64_t tablet_record_size;

	MemoryStore **keyValueStores;
	// tablet manager lock
	pthread_mutex_t tabletManagerLock;
	// memory creation time.
	uint64_t memoryCreationTime;
	// ingest configuration
	IngestConfiguration *config;
	// tablets
	IO::Tablet::Tablet **tablets;
	// number of tablets.
	uint32_t tabletCount;
	// table ready identifier.
	bool tablets_ready;
};

}

#endif
