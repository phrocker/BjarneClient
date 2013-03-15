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

#include "TabletServer.h"
#include "ClientInterface.h"
#include <string>
using namespace std;
using namespace interconnect;

ServerInterconnect::ServerInterconnect(const string host, const int port) :
		::ClientInterface(host, port)
{

}

ServerInterconnect::ServerInterconnect(shared_ptr<TTransport> transport)
{

	shared_ptr<TTransport> serverTransport(new TSocket(host, port));

	shared_ptr<TTransport> transporty(
			new TFramedTransport(serverTransport));
	shared_ptr<TProtocol> protocolPtr(new TCompactProtocol(transporty));
	transporty->open();

	client = new accumulo::client::ClientServiceClient(protocolPtr);
	tserverClient = new accumulo::tabletserver::TabletClientServiceClient(
			protocolPtr);

	transport = transporty;

	client->getZooKeepers(zookeepers);
	client->getInstanceId(instanceId);

}

ServerInterconnect::~ServerInterconnect()
{

	transport->close();

}

void ServerInterconnect::authenticate(AuthInfo *credentials)
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
