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
#include "Master.h"
#include "../data/constructs/security/AuthInfo.h"
#include <string>

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

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

#include "../ClientService.h"
#include "../TabletClientService.h"
#include "../data/constructs/Mutation.h"
#include "../writer/Sink.h"
#include "../writer/MutationCollector.h"
#include "ClientInterface.h"
#include "../data/exceptions/ClientException.h"

using namespace std;
namespace interconnect
{

using namespace cclient::exceptions;
using namespace cclient::data::security;

MasterConnect::MasterConnect(shared_ptr<TTransport> transporty)
{
	setTransport(transporty);
}
MasterConnect::MasterConnect(const string host, const int port) :
		::ClientInterface(host, port)
{

	shared_ptr<TTransport> serverTransport(new TSocket(host, port));

	shared_ptr<TTransport> transporty(new TFramedTransport(serverTransport));
	shared_ptr<TProtocol> protocolPtr(new TCompactProtocol(transporty));
	transporty->open();

	client = new accumulo::client::ClientServiceClient(protocolPtr);
	tserverClient = new accumulo::tabletserver::TabletClientServiceClient(
			protocolPtr);

	transport = transporty;

	client->getZooKeepers(zookeepers);
	client->getInstanceId(instanceId);

}

void MasterConnect::authenticate(AuthInfo *credentials)
{

	string username = credentials->getUserName();
	string password = credentials->getPassword();
	accumulo::cloudtrace::TInfo tinfo;
	accumulo::security::AuthInfo creds;
	string str = "";

	creds.instanceId = instanceId;
	creds.user = username;
	creds.password = password;

	tinfo.parentId = 0;
	tinfo.traceId = rand();
	if (!client->authenticateUser(tinfo, creds, username, password))
	{
		throw ClientException("Invalid username");
	}
	authenticated = true;
	authenticated_user = username;
	authenticated_password = password;
}

void MasterConnect::authenticate(string username, string password)
{
	accumulo::cloudtrace::TInfo tinfo;
	accumulo::security::AuthInfo creds;
	string str = "";

	creds.instanceId = instanceId;
	creds.user = username;
	creds.password = password;

	tinfo.parentId = 0;
	tinfo.traceId = rand();
	if (!client->authenticateUser(tinfo, creds, username, password))
	{
		throw ClientException("Invalid username");
	}
	authenticated = true;
	authenticated_user = username;
	authenticated_password = password;
}

MasterConnect::~MasterConnect()
{
	transport->close();
}
}
