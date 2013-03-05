/**
  * Hello, this is BjarneClient, a free and open implementation of Accumulo
  * and big table. This is meant to be the client that accesses Accumulo
  * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
  * 2013 -- Marc Delta Poppa @ accumulo.net
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.

  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  **/


#ifndef ZOOKEEPERINSTANCE_H
#define ZOOKEEPERINSTANCE_H
#include "Instance.h"


#include <iostream>
#include <string>
#include <zookeeper/zookeeper.hh>
#include "./zookeeper/zookeepers.h"
#include "./zookeeper/zoocache.h"
#include "../inputvalidation.h"
#include "../../../connector/Connector.h"
#include "../../exceptions/ClientException.h"
#include "../configuration/Configuration.h"
#include "../../../interconnect/Master.h"

using namespace org::apache::zookeeper;
using namespace std;
namespace cclient{
namespace data{
  namespace zookeeper{
   
  using namespace interconnect;
  using namespace cclient::impl;
  using namespace cclient::connector::impl;
  using namespace cclient::data;
  using namespace cclient::exceptions;
class ZookeeperInstance : public Instance
{
public:
    ZookeeperInstance(string in, string inId, string zks) : instanceId(inId) , instanceName(in), zookeeperList(zks)
    {
    }
    
    ZookeeperInstance(string in, string zks, uint16_t zkTimeoutMs, Configuration *conf) :  instanceName(in), zookeeperList(zks), timeoutMs(zkTimeoutMs), myConfiguration(conf)
    {
      if (IsEmpty(&in) || IsEmpty(&zks) )
      {
	  throw ClientException("instance name or zookeeper list is empty");
      }
      
      myZooCache = new ZooCache(zks,zkTimeoutMs,NULL);
      
      getInstanceId();
      
    }
    
    string getRootTabletLocation();
    list<string> getMasterLocations();
    string getInstanceId();
    string getInstanceName();
    Connector *getConnector(AuthInfo *authoration);
    Configuration *getConfiguration();
    void setConfiguration(Configuration *conf);
    MasterConnect * getMasterInterconnects();
    ~ZookeeperInstance();
    
protected:
  
    string getRoot();
  
    ZooCache *myZooCache;
  
    Configuration *myConfiguration;
    
    // load the cache
  
    string instanceId;
    string instanceName;
    string zookeeperList;
    
    uint32_t timeoutMs;
    
};
}
}
}

#endif // ZOOKEEPERINSTANCE_H
