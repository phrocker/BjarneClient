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

#ifndef CONNECTOR_H_
#define CONNECTOR_H_
#include <iostream>
#include <string>
using namespace std;
#include "../scanner/Scanner.h"
#include "../data/constructs/client/Instance.h"
#include "../data/constructs/security/AuthInfo.h"
#include "../data/constructs/security/Authorizations.h"
namespace cclient {
namespace connector {
namespace impl {
using namespace interconnect;
using namespace cclient::data::security;
using namespace cclient::data;
using namespace scanners;

class Connector {

public:
	Connector(Instance *instance, string user, string password);

	virtual Source *createScanner(string tableName,
			Authorizations *authorizations, int numQueryThreads) = 0;

	virtual ~Connector();
protected:
	Instance *myInstance;
	AuthInfo *credentials;
};

} /* namespace impl */
} /* namespace cclient */
}
#endif /* CONNECTOR_H_ */
