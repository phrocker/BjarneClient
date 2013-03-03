/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Instance.h"
#include "./zookeeperinstance.h"
#include "./zookeeper/zookeepers.h"
#include "./zookeeper/zoocache.h"
#include "../configuration/Configuration.h"
#include "../../../connector/Connector.h"
#include "../../../connector/impl/AccumuloConnector.h"

#include "../../../interconnect/InterConnect.h"


#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <boost/iterator/iterator_concepts.hpp>

namespace cclient{
namespace data{
  namespace zookeeper{
    
    using namespace interconnect;
    
    using namespace cclient::connector::impl;
    using namespace cclient::impl;

    using namespace std;
    
    string ZookeeperInstance::getRootTabletLocation()
    {
      string masterLockPath = getRoot() + ZROOT_TABLET_LOCATION;
	
	string rootLoc = myZooCache->getPath(masterLockPath);
	
	
	if (IsEmpty(rootLoc))
	{
	    return NULL;
	}
	
	return split(rootLoc,'|').at(0);
    }
 
 
    string ZookeeperInstance::getRoot()
    {
	return ZROOT + "/" + instanceId;
    }
  
 
    vector<string> ZookeeperInstance::getMasterLocations()
    {
	string masterLockPath = getRoot() + ZMASTER_LOCK;
	
	string lockData = myZooCache->getLockData(masterLockPath);
	
	
	vector<string> masters;
	
	if (IsEmpty(lockData))
	{
	    return masters;
	}
	
	masters.insert(lockData);
	
	return masters;
	
	
    }
//     
    string ZookeeperInstance::getInstanceId()
    {
      if (IsEmpty(instanceId))
      {
	  stringstream instancePathName;
	  instancePathName <<  ZROOT << ZINSTANCES << "/" << instanceName;
	  string dataPath = myZooCache->getPath(instancePathName.str());
	  
	  if (IsEmpty(&dataPath))
	  {
	    throw ClientException("Instance name does not exist within zookeeper");
	  }
	  
	  instanceId = dataPath;
	  
	  instancePathName.clear();
	  
	  instancePathName <<  ZROOT << "/" << instanceId;
	  
	  dataPath = myZooCache->getPath(instancePathName.str());
	  
	  if (IsEmpty(&dataPath))
	  {
	    throw ClientException("Instance Id does not exist within zookeeper");
	  }
	  
	  return instanceId;
	  
      }
    }
    string ZookeeperInstance::getInstanceName()
    {
	stringstream instancePathName;
	  instancePathName <<  ZROOT << ZINSTANCES;
	  vector<string> children  = myZooCache->getChildren(instancePathName.str());
	  
	  for(string child : children)
	  {
	    instancePathName.clear();
	    instancePathName <<  ZROOT << ZINSTANCES << "/" << child;
	    string childId  = myZooCache->getPath(instancePathName.str());
	    if (childId == instanceId)
	    {
	      return childId;
	    }
	  }
	  
      return "";
    }
    //virtual string getZooKeepers() = 0;
    Connector *ZookeeperInstance::getConnector(AuthInfo *authoration)
    {
      return new AccumuloConnector(this,authoration->getUserName(),authoration->getPassword());
    }
    Configuration *ZookeeperInstance::getConfiguration()
    {
      return myConfiguration;
    }
    void ZookeeperInstance::setConfiguration(Configuration *conf)
    {
     myConfiguration = conf; 
    }
    Master * ZookeeperInstance::getMasterInterconnects()
    {
	  stringstream instancePathName;
	  instancePathName <<  getRoot() << TSERVERS;
	  vector<string> children  = myZooCache->getChildren(instancePathName.str());
	  
	  vector<ServerConnection> servers;
	  
	  for(string child : children)
	  {
	    
	      instancePathName.clear();
	      // get tserver
	      instancePathName << getRoot() << TSERVERS << "/" << child;
	      string serverId  = myZooCache->getLockData(instancePathName.str());
	      
	      if (!IsEmpty(serverId) && serverId == "master")
	      {
		servers.insert( ServerConnection("",0,0));
	      }
	    
	  }
	  
	  
	
	return new Master(this);
    }
    ~ZookeeperInstance();
  }
}
}