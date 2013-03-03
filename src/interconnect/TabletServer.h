/*
 * TabletServer.h
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

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

using namespace std;

namespace interconnect {
  
   using namespace cclient::exceptions;
   using namespace accumulo::data;
  
class TabletServer : public Master {
public:
	TabletServer(const string host, const int port) :Master(host,port)
	{
	}
	TabletServer(shared_ptr<TTransport> transport) :Master(transport)
	{
	}
	
	static bool getBatchFromServer(AuthInfo *credentials, Range *range, KeyExtent *extent, string server, map<Key,Value> *results,
				       set<Column> *fetchedColumns, uint32_t size, Authorizations, boolean retry, Configuration *conf)
	{
	  if (IsEmpty(server))
	  {
	      throw ClientException("Invalid server name");
	      
	  }
	  //ServerConnection
	  //CLUSTER_COORDINATOR.
	  
	      ConnectorService conn("tserver;" + server);
		
		const uint16_t tserverPort = (uint16_t)conf->getLong(TSERVER_PORT_OPT,TSERVER_DEFAULT_PORT);
			
		if (!isValidPort(tserverPort))
		{
		  throw IllegalArgumentException("Invalid port");
		}
		
		const uint32_t timeout = conf->getLong(GENERAL_RPC_TIMEOUT_OPT,GENERAL_RPC_TIMEOUT);
		
		ServerConnection tServer(conn.getAddressString(interconnect::INTERCONNECT_TYPES::TSERV_CLIENT),tserverPort,timeout);
		
		shared_ptr<TTransport> cachedTransport = CLUSTER_COORDINATOR.createNewTransport(&tServer);
		
		TabletServer server(cachedTransport);
		
		vector<IterInfo*> list;
		
		map<string, map<string,string> map;
		
		ScanState *state = new ScanState(
		
		
		
		
		
	}
	virtual ~TabletServer();
};

}
#endif /* TABLETSERVER_H_ */
