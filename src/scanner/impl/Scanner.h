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

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../Source.h"
#include "../constructs/Results.h"
#include "../constructs/ServerHeuristic.h"
#include "../../interconnect/ClientInterface.h"

namespace scanners
{
using namespace interconnect;
class Scanner: public scanners::Source
{
public:
	Scanner();
	Results * getResultSet();

	void addResults(Results *results)
	{

	}



	void setHeuristic(ScannerHeuristic *heuristic)
	{
		scannerHeuristic = heuristic;
	}

	void addServerDefinition(ClientInterface *ifc)
	{
		servers.push_back(ifc);
	}

	void addServerDefinition(vector<ClientInterface*> ifc)
	{
		servers.insert(servers.end(), ifc.begin(), ifc.end());
	}

	virtual ~Scanner();
protected:

	vector<ClientInterface*> servers;
	ScannerHeuristic *scannerHeuristic;
};
}
#endif /* SCANNER_H_ */

