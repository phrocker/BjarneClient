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

#ifndef BASE_TRANSPORT_H
#define BASE_TRANSPORT_H

#include <map>
#include <set>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;

#include <protocol/TBinaryProtocol.h>
#include <protocol/TCompactProtocol.h>
#include <server/TSimpleServer.h>

#include <transport/TServerSocket.h>
#include <transport/TServerTransport.h>
#include <transport/TTransport.h>
#include <transport/TSocket.h>
#include <transport/TTransportException.h>
#include <server/TNonblockingServer.h>
#include <transport/TBufferTransports.h>

#include <concurrency/ThreadManager.h>

#include <pthread.h>
#include <sys/time.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

#include "Transport.h"
#include <boost/concept_check.hpp>

using namespace cclient::exceptions;

namespace interconnect
{

template<typename T>
class ObjectStreamer
{
public:

	ObjectStreamer() :
			closed(false)
	{
	}

	bool write(T object)
	{
		objects.push_back(object);

		return true;
	}

	void close()
	{
		closed = true;
		iut = objects.begin();
	}

	bool hasNext()
	{
		return !(it == objects.end());
	}

	T next()
	{
		if (!closed)
			throw runtime_exception(
					"attempting to interrogate open object streamer");
		T object = (*it);

		it++;

		return obj;
	}

protected:
	vector<T>::iterator it;
	bool closed;
	vector<T> objects;
};

template<typename T>
class ThriftStreamer: ObjectStreamer<T>
{

};

class ThriftTransporter: public ServerTransport<TTransport>
{
protected:

	shared_ptr<TTransport> underlyingTransport;
	accumulo::client::ClientServiceClient *client;
	accumulo::tabletserver::TabletClientServiceClient *tserverClient;

	void newTransporter(ServerConnection *conn)
	{

		shared_ptr<TTransport> serverTransport(
				new TSocket(conn->getHost(), conn->getPort()));

		shared_ptr<TTransport> transporty(
				new TFramedTransport(serverTransport));

		transporty->open();

		underlyingTransport = transporty;

	}

public:

	ThriftTransporter(ServerConnection *conn) :
			::Transporter(conn)
	{
	}

	void registerService(string instance, string clusterManagers)
	{
		shared_ptr<TProtocol> protocolPtr(
				new TCompactProtocol(underlyingTransport));

		client = new accumulo::client::ClientServiceClient(protocolPtr);
		tserverClient = new accumulo::tabletserver::TabletClientServiceClient(
				protocolPtr);

		client->getZooKeepers(clusterManagers);
		client->getInstanceId(instance);
	}

	Scan *beginScan(ServerConnection *conn)
	{
		return NULL;
	}

	/*
	 shared_ptr<TTransport> createNewTransport(ServerConnection *conn) {
	 shared_ptr<TTransport> serverTransport(
	 new TSocket(conn->getHost(), conn->getPort()));

	 shared_ptr<TTransport> transporty(
	 new TFramedTransport(serverTransport));

	 transporty->open();

	 CachedTransport *cachedTransport = new CachedTransport(transporty,
	 *conn);

	 cachedTransport->reserve();

	 pthread_mutex_lock(&cacheLock);
	 vector<CachedTransport> *cachedConnections = &cache[conn];

	 cachedConnections->insert(*conn, cachedTransport);

	 pthread_mutex_unlock(&cacheLock);

	 return cachedTransport->getTransport();
	 }


	 */

}
;
}
#endif
