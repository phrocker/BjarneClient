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
#include <boost/concept_check.hpp>

using namespace cclient::exceptions;

namespace interconnect {

#define TSERVER_PORT_OPT "tserver.port.client"
#define TSERVER_DEFAULT_PORT 9997

#define GENERAL_RPC_TIMEOUT_OPT "general.rpc.timeout"
#define GENERAL_RPC_TIMEOUT 120*1000

enum INTERCONNECT_TYPES {
	TSERV_CLIENT, MASTER_CLIENT, GC_CLIENT
};

#define SERVICE_SEPARATOR ';'
#define SEPARATOR_CHAR '='

template<typename T>
class EnumParser {
	map<string, T> enumMap;
public:
	EnumParser() {
	}
	;

	T ParseSomeEnum(const string &value) {
		map<string, T>::const_iterator iValue = enumMap.find(value);
		if (iValue == enumMap.end())
			throw IllegalArgumentException("");
		return iValue->second;
	}
};

EnumParser<INTERCONNECT_TYPES>::EnumParser() {
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

class ConnectorService {
public:
	ConnectorService(string service) {

		vector<string> addresses = split(service, SERVICE_SEPARATOR);

		for (auto address : addresses) {
			vector<string> sa = split(address, SEPARATOR_CHAR);

			serviceMap.insert(TYPE_PARSER[sa.at(0)], sa.at(1));

		}
	}

	string getAddressString(INTERCONNECT_TYPES type) {
		return serviceMap[type];
	}

	uint16_t getPort(string port) {
		if (IsEmpty(&port))
			throw IllegalArgumentException("Invalid Port");
		uint16_t intPort = atoi(port.c_str());
		if (intPort < 1024 || intPort > 65535) {
			throw IllegalArgumentException("Invalid Port");
		}

		return intPort;
	}

protected:
	map<INTERCONNECT_TYPES, string> serviceMap;
};

struct Cmp_ServerConnection {
	bool operator()(const ServerConnection& first,
			const ServerConnection& second) {
		bool less = first.host < second.host;
		if (less)
			return true;
		else {
			if (first.host > second.host)
				return false;
			else {
				less = first.port < second.port;
				if (less)
					return true;
				else {
					if (first.port > second.port)
						return false;
					else {
						return first.timeout < second.timeout;
					}
				}
			}
		}
	}
};

class ServerConnection {
public:
	ServerConnection(string loc, uint16_t port, uint64_t timeout) :
			host(loc), port(port), timeout(timeout) {
		if (IsEmpty(&loc)) {
			throw IllegalArgumentException("Invalid Input; host name is empty");
		}

	}

	bool operator==(ServerConnection &rhs) const {

		return host == rhs.host && port == rhs.port && timeout == rhs.timeout;
	}

	string getHost() {
		return host;
	}

	uint16_t getPort() {
		return port;
	}

	uint64_t getTimeout() {
		return timeout;
	}

	ServerConnection &operator=(const ServerConnection &rhs) {

		host = rhs.host;
		port = rhs.port;
		timeout = rhs.timeout;
		return *this;
	}

protected:
	string host;
	uint16_t port;
	uint64_t timeout;
};

#define ERROR_THRESHOLD 20L
#define STUCK_THRESHOLD 2*60*1000

static SpiderConnector CLUSTER_COORDINATOR;

class SpiderConnector {
public:
	SpiderConnector() {
		cache = new map<ServerConnection, vector<ServerConnection>>();
	}

	~SpiderConnector() {
		delete cache;
	}

	void freeTransport(shared_ptr<TTransport> transport) {
		if (IsEmpty(&*transport))
			return;

		bool haveCache = false;

		CachedTransport *cachedTransport =
				dynamic_cast<CachedTransport>(&*transport);

		vector<CachedTransport*> *closeList = new vector<CachedTransport*>();
		pthread_mutex_lock(&cacheLock);

		ServerConnection cacheKey = cachedTransport->getCacheKey();

		vector<CachedTransport*> *cachedConnections = &cache[cacheKey];
		vector<CachedTransport*>::iterator cacheIter =
				cachedConnections->begin();

		timeval time;
		gettimeofday(&time, NULL);
		long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		for (; cacheIter != cachedConnections->end(); cacheIter++) {
			if (**cacheIter == *cachedTransport) {
				if (cachedTransport->hasError()) {
					closeList->insert(cachedTransport);
					cacheIter = cachedConnections->erase(cacheIter);

					uint32_t errors = 0;

					if (errorCount.find(cacheKey) != errorCount.end()) {
						errors = errorCount.at(cacheKey);
					}

					errors++;

					errorCount[cacheKey] = errors;

					errorTime[cacheKey] = millis;

					if (errors > ERROR_THRESHOLD
							&& badServers.find(cacheKey) == badServers.end()) {
						badServers.insert(cacheKey);
					}

				} else {
				}
				(*cacheIter)->setReturnTime(millis);
				(*cacheIter)->reserve(false);
				haveCache = true;
				break;

			}
		}

		if (cachedTransport->hasError()) {
			cacheIter = cachedConnections->begin();
			for (; cacheIter != cachedConnections->end(); cacheIter++) {
				if (!(*cacheIter)->isReserved()) {
					closeList->insert(*cacheIter);
					cacheIter = cachedConnections->erase(cacheIter);
				}
			}

		}

		pthread_mutex_unlock(&cacheLock);

	}

	std::pair<string, shared_ptr<TTransport>> getTransporter(
			const vector<ServerConnection> *servers,
			const bool preferCachedConnection) {

		if (preferCachedConnection) {
			pthread_mutex_lock(&cacheLock);
			set<ServerConnection> serverSet = new set<ServerConnection>(
					servers->begin(), servers->end());
			map<ServerConnection, vector<ServerConnection>>::iterator it =
					cache->begin();
			for (; it != cache->end(); it++) {
				ServerConnection conn = it->first;
				serverSet.insert(conn);
			}
			if (!IsEmpty(&serverSet)) {
				std::random_shuffle(serverSet.begin(), serverSet.end());

				for (ServerConnection conn : serverSet) {
					vector<CachedTransport> *cachedConnections = &cache[conn];
					for (CachedTransport *cacheTransport : cachedConnections) {
						if (!cacheTransport->isReserved()) {
							cacheTransport->reserve();
							pthread_mutex_unlock(&cacheLock);
							return std::make_pair<string, shared_ptr<TTransport>>(
									conn.getHost() + ":" + conn.getPort(),
									cacheTransport->getTransport());
						}
					}
				}

			}
			pthread_mutex_unlock(&cacheLock);

		}

		vector<ServerConnection> serverPool(servers);

		short retryCount = 0;

		ServerConnection *conn;
		while (serverPool.size() > 0 && retryCount < 10) {
			int index = std::rand() % serverPool.size();
			conn = &serverPool.at(index);
			if (!preferCachedConnection) {
				pthread_mutex_lock(&cacheLock);
				vector<CachedTransport> *cachedConnections = cache[*conn];
				if (!IsEmpty(cachedConnections)) {
					for (CachedTransport *cacheTransport : cachedConnections) {
						if (!cacheTransport->isReserved()) {
							cacheTransport->reserve();
							pthread_mutex_unlock(&cacheLock);
							return std::make_pair<string, shared_ptr<TTransport>>(
									conn->getHost() + ":" + conn->getPort(),
									cacheTransport->getTransport());
						}
					}
				}
				pthread_mutex_unlock(&cacheLock);
			}

			try {
				return std::make_pair<string, shared_ptr<TTransport>>(
						conn->getHost() + ":" + conn->getPort(),
						createNewTransport(conn));
			} catch (TTransportException &tfe) {
				serverPool.erase(serverPool.begin() + index);
				retryCount++;
			}

		}

		throw TTransportException("Failed to connect to server");
	}

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

protected:

	pthead_mutex_t cacheLock = PTHREAD_MUTEX_INITIALIZER;

	map<ServerConnection, vector<CachedTransport*>> *cache;
	map<ServerConnection,uint32_t> errorCount;
	map<ServerConnection,uint32_t> errorTime;
	set<ServerConnection> badServers;
};

class CachedTransport: public TTransport {
public:
	CachedTransport(shared_ptr<TTransport> transport, ServerConnection key) :
			ioCount(0), lastCount(-1), reserved(false), threadName(""), foundError(
					false), lastReturnTime(0) {
		cacheKey = key;

		serverTransport = transport;
	}

	void reserve(bool reserve = false) {
		reserved = reserve;
	}

	bool isReserved() {
		return reserved;
	}

	void open() {
		try {
			ioCount++;
			serverTransport->open();
		} catch (TTransportException &tfe) {
			foundError = true;
			throw tfe;
		}

		ioCount++;
	}

	bool hasError() {
		return foundError;
	}

	ServerConnection &getCacheKey() {
		return cacheKey;
	}

	shared_ptr<TTransport> getTransport() {
		return shared_ptr<TTransport>(this);
	}

	bool operator ==(const CachedTransport *rhs) const {
		return *this == *rhs;
	}

	bool operator==(const CachedTransport &rhs) const {
		return threadName == rhs.threadName && cacheKey == rhs.cacheKey;
	}

	bool isOpen() {
		return serverTransport->isOpen();
	}

	void setReturnTime(uint64_t t) {
		lastReturnTime = t;
	}

	uint64_t getLastReturnTime() {
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
	shared_ptr<TTransport> serverTransport;
};

}
#endif
