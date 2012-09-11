#include <iostream>

#include "tablet_man.h"
#include <assert.h>
#include "tablets/c_tablet.h"
#include "MemoryStore.h"
#include "data-objects/containers/KeyValueStore.h"
using namespace std;

using namespace IO;
using namespace IO::DataObjects::Containers;
using namespace IO::Tablet;
int main()
{
  
    IngestConfiguration config;
    config.concurrent_index_threads = 3;
    config.debug = true;
    
    config.file_read_size = 12345;
    config.max_tablet_count = 10;
    config.max_tablet_rows = 25;
    TabletManager *manager = new TabletManager(&config,0,0);
    while(!manager->tabletsReady());
    cout << "Tablets are ready" << endl;
    
    MemoryStore **store = manager->getKeyValueStore();
    uint32_t size = manager->getKeyValueStoreSize();
    for(int i=0; i< size; i++)
    {
      assert( store[i]->getSize() == config.max_tablet_rows );
    }
    
    assert( config.max_tablet_count == manager->getTabletCount() );
    IO::Tablet::Tablet **tablets = manager->getTablets();
    tablets[0]->sync(3,"./",false,NULL);
    assert( store != NULL );
    delete manager;
    return 0;
}