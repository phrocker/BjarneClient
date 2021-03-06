/**
 * Hello, this is BjarneClient, a free and open implementation of Accumulo
 * and big table. This is meant to be the client that accesses Accumulo
 * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
 * 2013 -- Marc Delta Poppa @ accumulo.net
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
#ifndef SOURCE_H_
#define SOURCE_H_

#include <iostream>
#include <string>
#include <cstdint>
#include "../constructs/Results.h"

using namespace std;


namespace scanners
{
	using namespace interconnect;
class Source
{
public:
	Source();
	virtual Results * getResultSet() = 0;

	virtual void addResults(Results *results) = 0;

	virtual ~Source();
};
}
#endif /* SCANNER_H_ */
