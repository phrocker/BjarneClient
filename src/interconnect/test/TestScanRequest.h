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

#ifndef TESTSCANREQUEST_H_
#define TESTSCANREQUEST_H_

#define SIGNED_RIGHT_SHIFT_IS 5
#define ARITHMETIC_RIGHT_SHIFT 5

#include <string>

using namespace std;

#include <protocol/TBinaryProtocol.h>
#include <protocol/TCompactProtocol.h>
#include <server/TSimpleServer.h>

#include <transport/TServerSocket.h>
#include <transport/TServerTransport.h>
#include <transport/TTransport.h>
#include <transport/TSocket.h>
#include <transport/TTransportException.h>
#include <transport/TBufferTransports.h>

#include <concurrency/ThreadManager.h>

#include <pthread.h>
#include <sys/time.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

#include "../../data/constructs/test/RunUnit.h"
#include "../../data/constructs/Key.h"
#include "../../data/constructs/value.h"
#include "../scanrequest/ScanRequest.h"
#include "../scanrequest/ScanIdentifier.h"
#include "../../data/extern/thrift/ThriftWrapper.h"
#include "../../data/extern/thrift/data_types.h"

#include <assert.h>

using namespace cclient::data;
using namespace interconnect;
using namespace cclient::test;



class TestIdentifier: public RunUnit
{
public:

	bool testCreate()
	{
		ScanIdentifier<string, string> identifier;
		identifier.getIdentifiers("autos").push_back("ford");

		vector<string> st = identifier.getGlobalMapping();

		if (st.size() != 1)
			return false;

		return true;
	}

	TestIdentifier()
	{
		addUnit(
				unit("Test Creating Scan Identifier",
						(unitFunc) &TestIdentifier::testCreate));

	}

};

class TestThrift: public RunUnit
{
public:

	bool testCreateAllSet()
	{

		AuthInfo info("testUser", "testPassword", "testInstanceId");

		list<string> authList;
		authList.push_back("one");
		authList.push_back("two");

		Authorizations auths(authList);

		ServerConnection connection("127.0.0.1", 35533, 209023L);

		ScanIdentifier<KeyExtent*, Range*> identifier;

		KeyExtent ex("!0", ";");
		Key key;
		key.setColFamily("first");
		key.setColQualifier("first");

		Key key2;
		key.setColFamily("first");
		key.setColQualifier("first2");

		Range range(&key,true,&key2,false);

		identifier.getIdentifiers(&ex).push_back(&range);

		ScanRequest<ScanIdentifier<KeyExtent*, Range*>> *request =
				new ScanRequest<ScanIdentifier<KeyExtent*, Range*>>(&info, &auths,
						&connection);

		Column c("columnFam", "colQual", "viz");

		request->addColumn(&c);

		request->putIdentifier( &identifier );

		UNIT_ASSERT( request->getIterators()->size() == 0 )

		accumulo::security::AuthInfo authVer = ThriftWrapper::convert(request->getCredentials());

		UNIT_ASSERT( (authVer.instanceId == info.getInstanceId()) )

		UNIT_ASSERT( authVer.password == info.getPassword() )

		UNIT_ASSERT( (authVer.user == info.getUserName()) )

		vector<accumulo::data::IterInfo> iterList = ThriftWrapper::convert( request->getIterators() );

		UNIT_ASSERT( iterList.size() == 0 )

/**
 * ThriftWrapper::convert(request->getCredentials()),
				ThriftWrapper::convert(request->getRangeIdentifier()),
				ThriftWrapper::convert(request->getColumns()),
				ThriftWrapper::convert(iters), iterOptions,
 */




		return true;
	}

	TestThrift()
	{
		addUnit(
				unit("Tests thrift conversion by populating all members",
						(unitFunc) &TestThrift::testCreateAllSet));

	}

};

class TestScanRequest: public RunUnit
{
public:

	bool testCreate()
	{
		return true;
	}

	bool testBadConstructor()
	{
		ScanRequest<ScanIdentifier<string, string> > *request = NULL;
		BEGIN_EXPECTED_EXCEPTION(IllegalArgumentException)request = new ScanRequest<ScanIdentifier<string,string>>(NULL, NULL, NULL);
		END_EXPECTED_EXCEPTION(IllegalArgumentException)
		return true;
	}

	TestScanRequest()
	{
		addUnit(
				unit("Test Creating Scan Request",
						(unitFunc) &TestScanRequest::testCreate));
		addUnit(
				unit("Ensure a failure occurs with null inputs",
						(unitFunc) &TestScanRequest::testBadConstructor));
	}

};

#endif /* TESTKEY_H_ */
