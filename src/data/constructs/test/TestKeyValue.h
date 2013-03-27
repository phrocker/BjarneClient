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

#ifndef TESTKEYVALUE_H_
#define TESTKEYVALUE_H_

#include "RunUnit.h"
#include "../Key.h"
#include "../KeyValue.h"
#include "../rkey.h"
#include "../../streaming/stream_ifc.h"
#include <assert.h>

using namespace cclient::data;
using namespace cclient::test;

class TestKeyValue: public RunUnit
{
public:

	bool testCreate()
	{
		StreamInterface **kv = new StreamInterface*[25];
		for (int i = 0; i < 25; i++)
		{
			kv[i] = new KeyValue();
			delete kv[i];
		}

		delete[] kv;

		KeyValue *kvList = new KeyValue[200];

		char tst[400];
		memset(tst, 0x01, 400);

		for (int i = 0; i < 200; i++)
		{
			assert( kvList[i].getValue() != NULL);

			kvList[i].getValue()->setValue((uint8_t*) tst, 400);

			UNIT_ASSERT(
					memcmp(tst, kvList[i].getValue()->getValue().first, kvList[i].getValue()->getValue().second) == 0);

			UNIT_ASSERT(
					dynamic_cast<RelativeKey*>(kvList[i].getKey()) != NULL);
			UNIT_ASSERT( dynamic_cast<Key*>(kvList[i].getStream()) != NULL);

		}
		delete[] kv;

		return true;
	}

	TestKeyValue()
	{
		unit create("Test KeyValue Conversion to Key and Relative Key", (unitFunc) &TestKey::testCreate);
		addUnit(create);
	}

};

#endif /* TESTKEY_H_ */
