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

#ifndef MASTER_H_
#define MASTER_H_

#define SIGNED_RIGHT_SHIFT_IS 5
#define ARITHMETIC_RIGHT_SHIFT 5

#include <protocol/TBinaryProtocol.h>
#include <protocol/TCompactProtocol.h>
#include <server/TSimpleServer.h>

#include <transport/TServerSocket.h>
#include <transport/TServerTransport.h>
#include <transport/TTransport.h>
#include <transport/TSocket.h>
#include <server/TNonblockingServer.h>
#include <transport/TBufferTransports.h>

#include <concurrency/ThreadManager.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

#include "../ClientService.h"
#include "../TabletClientService.h"


#include <string>

#include "ClientInterface.h"
using namespace std;

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace interconnect
{
class MasterConnect: public ClientInterface
{
public:
	MasterConnect(const string host, const int port);
	MasterConnect(shared_ptr<TTransport> transport);

	void authenticate(string username, string password);

	void authenticate(AuthInfo *credentials);

	virtual ~MasterConnect();
protected:



	void setTransport(shared_ptr<TTransport> transporty)
	{
		shared_ptr<TProtocol> protocolPtr(new TCompactProtocol(transporty));

		client = new accumulo::client::ClientServiceClient(protocolPtr);
		tserverClient = new accumulo::tabletserver::TabletClientServiceClient(
				protocolPtr);

		transport = transporty;

		client->getZooKeepers(zookeepers);
		client->getInstanceId(instanceId);
	}

	accumulo::client::ClientServiceClient *client;
	accumulo::tabletserver::TabletClientServiceClient *tserverClient;
	shared_ptr<TTransport> transport;

};
}
#endif /* MASTER_H_ */
