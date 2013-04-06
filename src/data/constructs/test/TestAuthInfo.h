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

#ifndef TESTAUTHINFO_H_
#define TESTAUTHINFO_H_

#include <string>

using namespace std;

#include "RunUnit.h"
#include "../security/AuthInfo.h"
#include <assert.h>

using namespace cclient::data::security;
using namespace cclient::test;

class TestAuthInfo: public RunUnit
{
public:

	bool testCreate()
	{
		AuthInfo *auth = new AuthInfo("testuser", "testpassword", "instance");

		bool result = true;
		if (auth->getInstanceId() != "instance")
		{
			cout << "Instance Id invalid: " << auth->getInstanceId() << endl;
			result = false;
		}

		if (auth->getPassword() != "testpassword")
		{
			cout << "Password invalid: " << auth->getPassword() << endl;
			result = false;
		}

		if (auth->getUserName() != "testuser")
		{
			cout << "Username invalid: " << auth->getUserName() << endl;

			result = false;
		}

		delete auth;

		return result;
	}

	TestAuthInfo()
	{
		unit create("Test AuthInfo", (unitFunc) &TestAuthInfo::testCreate);
		addUnit(create);
	}

};

#endif /* TESTAUTHINFO_H_ */
