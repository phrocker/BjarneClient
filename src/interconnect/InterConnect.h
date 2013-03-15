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

#ifndef INTERCONNECT_H_
#define INTERCONNECT_H_

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

#include "../data/exceptions/ClientException.h"
#include "../data/exceptions/IllegalArgumentException.h"
#include "../data/constructs/inputvalidation.h"
#include "transport/BaseTransport.h"
#include "transport/ServerConnection.h"
#include <boost/concept_check.hpp>

using namespace cclient::exceptions;

namespace interconnect
{

#define TSERVER_PORT_OPT "tserver.port.client"
#define TSERVER_DEFAULT_PORT 9997

#define GENERAL_RPC_TIMEOUT_OPT "general.rpc.timeout"
#define GENERAL_RPC_TIMEOUT 120*1000

enum INTERCONNECT_TYPES
{
	TSERV_CLIENT, MASTER_CLIENT, GC_CLIENT
};

#define SERVICE_SEPARATOR ';'
#define SEPARATOR_CHAR '='

template<typename T>
class EnumParser
{
	map<string, T> enumMap;
public:
	EnumParser()
	{
	}
	;

	T ParseSomeEnum(const string &value)
	{
		map<string, T>::const_iterator iValue = enumMap.find(value);
		if (iValue == enumMap.end())
			throw IllegalArgumentException("");
		return iValue->second;
	}
};

EnumParser<INTERCONNECT_TYPES>::EnumParser()
{
	enumMap["TSERV_CLIENT"] = INTERCONNECT_TYPES::TSERV_CLIENT;
	enumMap["tserv_client"] = INTERCONNECT_TYPES::TSERV_CLIENT;
	enumMap["tserver"] = INTERCONNECT_TYPES::TSERV_CLIENT;

	enumMap["MASTER_CLIENT"] = INTERCONNECT_TYPES::MASTER_CLIENT;
	enumMap["master_client"] = INTERCONNECT_TYPES::MASTER_CLIENT;
	enumMap["master"] = INTERCONNECT_TYPES::MASTER_CLIENT;

	enumMap["GC_CLIENT"] = INTERCONNECT_TYPES::GC_CLIENT;
	enumMap["gc_client"] = INTERCONNECT_TYPES::GC_CLIENT;
	enumMap["gc"] = INTERCONNECT_TYPES::GC_CLIENT;
}

static EnumParser<INTERCONNECT_TYPES> TYPE_PARSER;

class ConnectorService
{
public:
	ConnectorService(string service)
	{

		vector<string> addresses = split(service, SERVICE_SEPARATOR);

		for (auto address : addresses)
		{
			vector<string> sa = split(address, SEPARATOR_CHAR);

			serviceMap.insert(TYPE_PARSER[sa.at(0)], sa.at(1));

		}
	}

	string getAddressString(INTERCONNECT_TYPES type)
	{
		return serviceMap[type];
	}

	uint16_t getPort(string port)
	{
		if (IsEmpty(&port))
			throw IllegalArgumentException("Invalid Port");
		uint16_t intPort = atoi(port.c_str());
		if (intPort < 1024 || intPort > 65535)
		{
			throw IllegalArgumentException("Invalid Port");
		}

		return intPort;
	}

protected:
	map<INTERCONNECT_TYPES, string> serviceMap;
};



#define ERROR_THRESHOLD 20L
#define STUCK_THRESHOLD 2*60*1000

static SpiderConnector<ThriftTransporter> CLUSTER_COORDINATOR;

template<typename Tr>
class SpiderConnector
{
public:
	SpiderConnector()
	{
		cache = new map<ServerConnection, vector<ServerConnection>>();
	}

	~SpiderConnector()
	{
		delete cache;
	}

	void freeTransport(CachedTransport *cachedTransport)
	{

		if (IsEmpty(cachedTransport))
			return;

		bool haveCache = false;

		vector<CachedTransport*> *closeList = new vector<CachedTransport*>();
		pthread_mutex_lock(&cacheLock);

		ServerConnection cacheKey = cachedTransport->getCacheKey();

		vector<CachedTransport*> *cachedConnections = &cache[cacheKey];
		vector<CachedTransport*>::iterator cacheIter =
				cachedConnections->begin();

		timeval time;
		gettimeofday(&time, NULL);
		long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		for (; cacheIter != cachedConnections->end(); cacheIter++)
		{
			if (**cacheIter == *cachedTransport)
			{
				if (cachedTransport->hasError())
				{
					closeList->insert(cachedTransport);
					cacheIter = cachedConnections->erase(cacheIter);

					uint32_t errors = 0;

					if (errorCount.find(cacheKey) != errorCount.end())
					{
						errors = errorCount.at(cacheKey);
					}

					errors++;

					errorCount[cacheKey] = errors;

					errorTime[cacheKey] = millis;

					if (errors > ERROR_THRESHOLD
							&& badServers.find(cacheKey) == badServers.end())
					{
						badServers.insert(cacheKey);
					}

				}
				else
				{
				}
				(*cacheIter)->setReturnTime(millis);
				(*cacheIter)->reserve(false);
				haveCache = true;
				break;

			}
		}

		if (cachedTransport->hasError())
		{
			cacheIter = cachedConnections->begin();
			for (; cacheIter != cachedConnections->end(); cacheIter++)
			{
				if (!(*cacheIter)->isReserved())
				{
					closeList->insert(*cacheIter);
					cacheIter = cachedConnections->erase(cacheIter);
				}
			}

		}

		pthread_mutex_unlock(&cacheLock);

	}

	std::pair<string, Tr> getTransporter(
			const vector<ServerConnection> *servers,
			const bool preferCachedConnection)
	{

		if (preferCachedConnection)
		{
			pthread_mutex_lock(&cacheLock);
			set<ServerConnection> serverSet = new set<ServerConnection>(
					servers->begin(), servers->end());
			map<ServerConnection, vector<ServerConnection>>::iterator it =
					cache->begin();
			for (; it != cache->end(); it++)
			{
				ServerConnection conn = it->first;
				serverSet.insert(conn);
			}
			if (!IsEmpty(&serverSet))
			{
				std::random_shuffle(serverSet.begin(), serverSet.end());

				for (ServerConnection conn : serverSet)
				{
					vector<CachedTransport> *cachedConnections = &cache[conn];
					for (CachedTransport *cacheTransport : cachedConnections)
					{
						if (!cacheTransport->isReserved())
						{
							cacheTransport->reserve();
							pthread_mutex_unlock(&cacheLock);
							return std::make_pair<string, shared_ptr<Tr>>(
									conn.getHost() + ":" + conn.getPort(),
									cacheTransport->getTransporter());
						}
					}
				}

			}
			pthread_mutex_unlock(&cacheLock);

		}

		vector<ServerConnection> serverPool(servers);

		short retryCount = 0;

		ServerConnection *conn;
		while (serverPool.size() > 0 && retryCount < 10)
		{
			int index = std::rand() % serverPool.size();
			conn = &serverPool.at(index);
			if (!preferCachedConnection)
			{
				pthread_mutex_lock(&cacheLock);
				vector<CachedTransport> *cachedConnections = cache[*conn];
				if (!IsEmpty(cachedConnections))
				{
					for (CachedTransport *cacheTransport : cachedConnections)
					{
						if (!cacheTransport->isReserved())
						{
							cacheTransport->reserve();
							pthread_mutex_unlock(&cacheLock);
							return std::make_pair<string, shared_ptr<Tr>>(
									conn->getHost() + ":" + conn->getPort(),
									cacheTransport->getTransporter());
						}
					}
				}
				pthread_mutex_unlock(&cacheLock);
			}

			try
			{
				return std::make_pair<string, shared_ptr<Tr>>(
						conn->getHost() + ":" + conn->getPort(),
						createNewTransport(conn));
			} catch (runtime_error &tfe)
			{
				serverPool.erase(serverPool.begin() + index);
				retryCount++;
			}

		}

		throw runtime_error("Failed to connect to server");
	}

	shared_ptr<Tr> createNewTransport(ServerConnection *conn)
	{

		CachedTransport *cachedTransport = new CachedTransport(new Tr(conn),
				*conn);

		cachedTransport->reserve();

		pthread_mutex_lock(&cacheLock);
		vector<CachedTransport> *cachedConnections = &cache[conn];

		cachedConnections->insert(*conn, cachedTransport);

		pthread_mutex_unlock(&cacheLock);

		return cachedTransport->getTransport();

	}
	/*

	 */

protected:

	pthead_mutex_t cacheLock = PTHREAD_MUTEX_INITIALIZER;

	map<ServerConnection, vector<CachedTransport*>> *cache;
	map<ServerConnection,uint32_t> errorCount;
	map<ServerConnection,uint32_t> errorTime;
	set<ServerConnection> badServers;
};

template<typepname T>
class CachedTransport: public T
{
public:
	CachedTransport(Transporter<T> transport, ServerConnection key) :
			ioCount(0), lastCount(-1), reserved(false), threadName(""), foundError(
					false), lastReturnTime(0)
	{
		cacheKey = key;

		serverTransport = transport;
	}

	void reserve(bool reserve = false)
	{
		reserved = reserve;
	}

	bool isReserved()
	{
		return reserved;
	}

	void open()
	{
		try
		{
			ioCount++;
			serverTransport->open();
		} catch (runtime_error &tfe)
		{
			foundError = true;
			throw tfe;
		}

		ioCount++;
	}

	bool hasError()
	{
		return foundError;
	}

	ServerConnection &getCacheKey()
	{
		return cacheKey;
	}

	shared_ptr<T> getTransporter()
	{
		return shared_ptr<T>(this);
	}

	bool operator ==(const CachedTransport *rhs) const
	{
		return *this == *rhs;
	}

	bool operator==(const CachedTransport &rhs) const
	{
		return threadName == rhs.threadName && cacheKey == rhs.cacheKey;
	}

	bool isOpen()
	{
		return serverTransport->isOpen();
	}

	void setReturnTime(uint64_t t)
	{
		lastReturnTime = t;
	}

	uint64_t getLastReturnTime()
	{
		return lastReturnTime;
	}

protected:

	bool foundError;
	volatile string threadName;
	volatile bool reserved;

	string stuckThreadName;

	uint16_t ioCount;
	int16_t lastCount;
	uint64_t lastReturnTime;
	ServerConnection cacheKey;
	Transporter<T> serverTransport;
};

}
#endif
