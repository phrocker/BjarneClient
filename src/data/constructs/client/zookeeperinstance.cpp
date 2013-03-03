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

#include <string>
#include <iostream>
#include <sstream>
#include <list>

namespace cclient{
namespace data{
  namespace zookeeper{

    using namespace std;
    
    string ZookeeperInstance::getRootTabletLocation()
    {
    }
 
    list<string> ZookeeperInstance::getMasterLocations()
    {
    }
    
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
    string getInstanceName();
    //virtual string getZooKeepers() = 0;
    Connector *getConnector(AuthInfo *authoration);
    Configuration &getConfiguration();
    void setConfiguration(Configuration *conf);
    Master * getMasterInterconnects();
    ~ZookeeperInstance();
  }
}
}