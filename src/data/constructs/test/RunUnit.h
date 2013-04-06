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

#ifndef RUNUNIT_H_
#define RUNUNIT_H_
#include <iostream>
#include <vector>
#include <string>

using namespace std;


namespace cclient
{
namespace test
{

typedef bool (*unitFunc)();

struct unit
{
	unit(string n, unitFunc p)
	{
		name = n;
		ptr = p;
	}
	string name;
	unitFunc ptr;
};


#define UNIT_ASSERT(x) if (!x) return false


class RunUnit
{
private:
	vector<unit> testUnits;
protected:
	void addUnit(unit p)
	{
		testUnits.push_back( p );
	}
public:


	RunUnit()
	{

	}

	void run()
	{
		for(unit ptr : testUnits)
		{

			bool result = ptr.ptr();
			cout << ptr.name << "  ; Result: " << (result == 1 ? "passed" : "failed") << " " << endl;
		}
	}


	virtual ~RunUnit()
	{

	}
};

static vector<RunUnit> units;

#define ADD_UNIT(X) units.push_back(X);

#define RUN_TESTS for(auto t: units) t.run();

#define RUN_TEST(x) x.run();

static bool encounteredException=false;

#define BEGIN_EXPECTED_EXCEPTION(e) \
			encounteredException = false; try{

#define END_EXPECTED_EXCEPTION(e) \
			}catch(e){ \
				encounteredException = true; \
			}	\
			UNIT_ASSERT( encounteredException == true);

}
}



#endif /* RUNUNIT_H_ */
