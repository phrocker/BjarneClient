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

#ifndef TESTKEY_H_
#define TESTKEY_H_

#include "RunUnit.h"
#include "../Key.h"
#include <assert.h>

using namespace cclient::data;
using namespace cclient::test;

class TestKey: public RunUnit
{
public:

	bool testCreate()
	{
		char testVal[3] =
		{ 0x01, 0x02, 0x03 };

		Key key;

		// test reuse
		for (int i = 0; i < 1000; i++)
		{

			UNIT_ASSERT(key.isDeleted() == false);

			key.setRow(testVal, 3);
			std::pair<char*, size_t> rowRet = key.getRow();

			UNIT_ASSERT(memcmp(testVal, rowRet.first, 3) == 0);
			UNIT_ASSERT(rowRet.second == 3);

			key.setColFamily(testVal, 3);
			std::pair<char*, size_t> colFamRet = key.getColFamily();

			UNIT_ASSERT(memcmp(testVal, colFamRet.first, 3) == 0);
			UNIT_ASSERT(colFamRet.second == 3);

		}

		return true;
	}

	TestKey()
	{
		unit create("Test key creation and reuse", (unitFunc) &TestKey::testCreate);
		addUnit(create);
	}

};

#endif /* TESTKEY_H_ */
