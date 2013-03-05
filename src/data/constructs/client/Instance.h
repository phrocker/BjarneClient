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
#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <string>
#include <list>

using namespace std;

#include "../../../interconnect/Master.h"
#include "Connector.h"
#include "../security/AuthInfo.h"
#include "../configuration/Configuration.h"

#include <string>
#include <list>
using namespace std;

namespace cclient {
namespace data {

using namespace cclient::impl;
using namespace cclient::connector::impl;
using namespace cclient::data::security;
using namespace interconnect;
class Instance {
public:
	virtual string getRootTabletLocation() = 0;
	virtual vector<string> getMasterLocations = 0;
	virtual string getInstanceId() = 0;
	virtual string getInstanceName() = 0;
	//virtual string getZooKeepers() = 0;
	virtual Connector *getConnector(AuthInfo *authoration) = 0;
	virtual Configuration *getConfiguration() = 0;
	virtual void setConfiguration(Configuration *conf) = 0;
	virtual MasterConnect * getMasterInterconnects();
	virtual ~Instance();
};

} /* namespace impl */
} /* namespace cclient */
#endif /* INSTANCE_H_ */

