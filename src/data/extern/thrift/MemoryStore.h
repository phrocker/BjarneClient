#ifndef MEMORY_STORE
#define MEMORY_STORE

#include <pthread.h>
#include "rfile/rfile.h"

/**
 * @file MemoryStore.h
 * @author Marc Parisi
 * @version 1.0
 * @section Description
 * Memory store will be the generic instance that allows us
 * to allocate a chunk of memory for the tablet manager
 * The concrete classes will prescribe a specific data type
 */
namespace IO 
{
class MemoryStore
{
  
public:

	MemoryStore()
	{
	 
		pthread_mutex_init( &mem_lock, NULL );
		mySize = 0;
	}

	virtual ~MemoryStore()
	{}
	/**
	 * Allocate the chunk of memory. This will
	 * be defined by the concrete class.
	 * @param size size of the memory to allocate.
	 */
	virtual void allocate(const uint64_t size) =0;
	
	/**
	 * Returns the size of the allocated memory
	 * @returns size
	 */
	uint64_t getSize()
	{
		return mySize;
	}

	
	virtual void *getStore() = 0;

	/**
	 * Locks the given data store. Note that getStore
	 * may already lock this memory store
	 */
	void lock()
	{
		pthread_mutex_lock( &mem_lock );
	}

	/**
	 * Unlocks the memory store
	 */
	void unlock()
	{
		pthread_mutex_unlock( &mem_lock );
	}


protected:
	// memory store lock.
	pthread_mutex_t mem_lock;
	// size of memory store.
	uint64_t mySize;
}; 

typedef struct
{
	MemoryStore **kvList;
	int i;
	uint64_t allocationSize;
} MEM_ALLOC, *PMEM_ALLOC; 

}

#endif