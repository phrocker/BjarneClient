/**
 * Hello, this is BjarneClient, a free and open implementation of Accumulo 
 * and big table. This is meant to be the client that accesses Accumulo 
 * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
 * 2013 -- BinaryStream LLC
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

#ifndef SERVERHEURISTIC_H_
#define SERVERHEURISTIC_H_

#include "Heuristic.h"
#include "../../interconnect/TabletServer.h"
#include "../../interconnect/Scan.h"
#include "../Source.h"

#include <pthread.h>

namespace scanners
{

struct ScanPair
{
	Source *src;
	ClientInterface *ifc;
};

/**
 * Contains base functionality to support multi scanning
 */
class ScannerHeuristic: Heuristic
{

public:

	/**
	 * Add a server interconnect
	 */
	void addClientInterface(ServerInterconnect *serverIfc)
	{
		pthread_mutex_lock(&serverLock);
		Heuristic::addClientInterface(static_cast<ClientInterface*>(serverIfc));
		pthread_mutex_unlock(&serverLock);
	}

	ScannerHeuristic(short numThreads = 10) :
			it(NULL), threadCount(numThreads), threads(NULL)
	{
		threads = new pthread_t[threadCount];
	}

	virtual ~ScannerHeuristic()
	{
		if (threads != NULL)
		{
			for (int i = 0; i < threadCount; i++)
			{
				pthread_exit(&thread[i]);
			}
		}
	}

	uint16_t scan(Source *source)
	{

		ServerInterconnect *interConnect = NULL;
		while( (interConnect = next()) != NULL)
		{
			ScanPair pair;
			pair.src = source;
			pair.ifc = interConnect;
			scan((void*)&pair);
		}
	}

private:
	pthead_mutex_t serverLock = PTHREAD_MUTEX_INITIALIZER;
	pthread_t *threads;
	short threadCount;
protected:

	virtual void scan(void *ptr)
	{
		ScanPair *pair = static_cast<ScanPair*>(ptr);

		ServerInterconnect *conn = reinterpret_cast<ServerInterconnect*>(pair->ifc);

		Scan *scan = new Scan(conn);

		vector<KeyValue*> nextResults;



		while(scan->getNextResults(&nextResults))
		{

			Results<KeyValue*,ResultBlock<KeyValue*>> *resultSet = new Results<KeyValue*,ResultBlock<KeyValue*>>();

			resultSet->add(&nextResults);

			pair->src->addResults(resultSet);
		}





	}

	virtual ServerInterconnect *next()
	{

		if (it != NULL)
		{
			pthread_mutex_lock(&serverLock);
			it = &servers.begin();
			pthread_mutex_unlock(&serverLock);
		}
		if (it == servers.end())
		{
			return NULL;
		}

		it++;

		return reinterpret_cast<ServerInterconnect*>(*it);

	}

	short threads;

	vector<ClientInterface*>::iterator *it;

};
}
#endif /* SERVERHEURISTIC_H_ */
