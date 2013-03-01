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


#ifndef ZOOKEEPERINSTANCE_H
#define ZOOKEEPERINSTANCE_H
#include "Instance.h"

namespace cclient {
namespace impl {
  using namespace cclient::data;
class ZookeeperInstance : public Instance
{
public:
    ZookeeperInstance();
    string getRootTabletLocation();
    list<string> getMasterLocations();
    string getInstanceId();
    string getInstanceName();
    //virtual string getZooKeepers() = 0;
    Connector *getConnector(AuthInfo *authoration);
    Configuration &getConfiguration();
    void setConfiguration(Configuration *conf);
    Master * getMasterInterconnects();
    ~ZookeeperInstance();
    
protected:
    string instanceId;
    string instanceName;
    string zookeeperList;
    
};
}
}

#endif // ZOOKEEPERINSTANCE_H
