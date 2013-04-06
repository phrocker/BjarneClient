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

#ifndef TESTSERVERCONN_H_
#define TESTSERVERCONN_H_

#include "../../data/constructs/test/RunUnit.h"
#include "../transport/ServerConnection.h"
#include <assert.h>

//using namespace cclient::data;
using namespace interconnect;
using namespace cclient::test;

class TestServerConnection: public RunUnit
{
public:

	bool testCreate()
	{
		ServerConnection *connection = new ServerConnection("location", 32,
				0000L);
		delete connection;
		return true;
	}

	bool testGetters()
	{
		//ScanRequest<int> *request = new ScanRequest<int>(NULL, NULL, NULL);
		ServerConnection *connection = new ServerConnection("location", 32,
				0006L);

		if (connection->getHost() != "location")
			return false;

		if (connection->getPort() != 32)
			return false;

		if (connection->getTimeout() != 6)
			return false;

		return true;
	}

	TestServerConnection()
	{
		addUnit(
				unit("Test Creating ServerConnection",
						(unitFunc) &TestServerConnection::testCreate));

		addUnit(
				unit("Test Getters of server connection",
						(unitFunc) &TestServerConnection::testGetters));

	}

};

#endif /* TESTKEY_H_ */
