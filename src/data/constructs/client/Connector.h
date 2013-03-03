/*
 * Connector.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

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

	virtual ScannerBase *createScanner(string tableName,
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
