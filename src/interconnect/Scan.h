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

#ifndef SCAN_H_
#define SCAN_H_

#include <iostream>
#include <vector>

using namespace std;

#include "../data/constructs/KeyValue.h"


/**
 * Represents a running scan
 */

namespace interconnect
{
	using namespace cclient::data;
class Scan
{
public:

	Scan(ServerInterconnect *cifc);

	bool getNextResults(vector<KeyValue*> *resultSet)
	{
		return false;
	}
	virtual ~Scan();
protected:
	ServerInterconnect *client;
};
}
#endif /* SCAN_H_ */
