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

#include <string>

using namespace std;

#include "../../data/constructs/test/RunUnit.h"
#include "../scanrequest/ScanRequest.h"
#include "../scanrequest/ScanIdentifier.h"
#include <assert.h>

//using namespace cclient::data;
using namespace interconnect;
using namespace cclient::test;


class TestIdentifier: public RunUnit
{
public:

	bool testCreate()
	{
		ScanIdentifier<string,string> identifier;
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

class TestScanRequest: public RunUnit
{
public:

	bool testCreate()
	{
		return true;
	}

	bool testBadConstructor()
	{
		BEGIN_EXPECTED_EXCEPTION(IllegalArgumentException)
				ScanRequest<int,int> *request = new ScanRequest<int,int>(NULL, NULL, NULL);
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
