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

#ifndef CLIENTINTERFACE_H_
#define CLIENTINTERFACE_H_

#include <string>

namespace interconnect
{

using namespace std;

class ClientInterface
{
public:
	ClientInterface(const string host, const int port);

	virtual ~ClientInterface();

	virtual void authenticate(string username, string password) = 0;

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


	accumulo::client::ClientServiceClient *getClient()
	{
		return client;
	}


protected:

	accumulo::client::ClientServiceClient *client;

	string server_host;
	int server_port;
	bool authenticated;

	string authenticated_user;
	string authenticated_password;
// info abt cluster
	string instanceId;
	string zookeepers;

};
}
#endif /* CLIENTINTERFACE_H_ */
