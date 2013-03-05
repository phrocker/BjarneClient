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

#ifndef TABLETSERVER_H_
#define TABLETSERVER_H_

#include <string>
#include "Master.h"
#include "InterConnect.h"
#include "../data/constructs/inputvalidation.h"
#include "../data_types.h"
#include "../data/constructs/scanstate.h"
#include "../data/exceptions/ClientException.h"
#include "../data/exceptions/IllegalArgumentException.h"
#include "../tablet/TabletType.h"

#include <boost/shared_ptr.hpp>
#include "../data/constructs/server/RangeDefinition.h"
#include "../data/constructs/server/ServerDefinition.h"
using boost::shared_ptr;

using namespace std;

namespace interconnect {
  
   using namespace cclient::exceptions;
   using namespace cclient::data;
   using namespace cclient::impl;
   using namespace accumulo::data;
   using namespace cclient::data::tserver;
   
  
class ServerInterconnect : public MasterConnect {
public:
	ServerInterconnect(const string host, const int port) :MasterConnect(host,port)
	{
	}
	ServerInterconnect(shared_ptr<TTransport> transport) :MasterConnect(transport)
	{
	}
	
	ServerInterconnect(RangeDefinition &rangeDef, Configuration *conf)
	{
		ConnectorService conn("tserver;" + rangeDef.getServer());

		const uint16_t tserverPort = (uint16_t)conf->getLong(TSERVER_PORT_OPT,TSERVER_DEFAULT_PORT);

		if (!isValidPort(tserverPort))
		{
		  throw IllegalArgumentException("Invalid port");
		}

		const uint32_t timeout = conf->getLong(GENERAL_RPC_TIMEOUT_OPT,GENERAL_RPC_TIMEOUT);

		ServerConnection tServer(conn.getAddressString(interconnect::INTERCONNECT_TYPES::TSERV_CLIENT),rangeDef.getPort(),timeout);


		shared_ptr<TTransport> cachedTransport = CLUSTER_COORDINATOR.createNewTransport(&tServer);

		setTransport(cachedTransport);

		authenticate(rangeDef.getCredentials());


		vector<IterInfo*> list;

		map<string, map<string,string> map;

		ScanState *state = new ScanState(credentials,extent->getTableId(),auths,range,fetchedColumns,size,&list,&map,false);

		TabletType type = cclient::data::tserver::fromExtent(extent);
	}


	virtual ~ServerInterconnect();
protected:
	ServerDefinition *serverDef;
};

}
#endif /* TABLETSERVER_H_ */

