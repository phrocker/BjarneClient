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

#ifndef TESTCOLUMN_H_
#define TESTCOLUMN_H_
#include <string>
using namespace std;
#include "../column.h"
#include "RunUnit.h"

class TestColumn: public RunUnit
{
public:

	bool testCreate()
	{
		Column *column = new Column("family", "qualifier", "viz");

		UNIT_ASSERT(string(column->getColFamily().first).compare("family")==0);

		UNIT_ASSERT(string(column->getColQualifier().first).compare("qualifier"));

		UNIT_ASSERT(string(column->getColVisibility().first).compare("viz"));

		UNIT_ASSERT(column->getColFamily().second == strlen("family"));

		UNIT_ASSERT(column->getColQualifier().second == strlen("qualifier"));

		UNIT_ASSERT(column->getColVisibility().second == strlen("viz"));

		delete column;

		return true;
	}

	TestColumn()
	{
		unit create("Test Creating Column",
				(unitFunc) & TestColumn::testCreate);
		addUnit(create);
	}
};

#endif /* TESTCOLUMN_H_ */
