/*
 * Connector.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef CONNECTOR_H_
#define CONNECTOR_H_
#include <string>
using namespace std;
#include "../scanner/thrift/Scanner.h"
#include "../data/constructs/security/AuthInfo.h"
#include "../data/constructs/security/Authorizations.h"
namespace cclient {
namespace impl {
using namespace cclient::thrift;
using namespace cclient::data::security;
class Connector {
public:
	Connector();

	virtual Scanner *createScanner(string tableName, Authorizations *authorizations, int numQueryThreads) = 0;

	virtual ~Connector();
};

} /* namespace impl */
} /* namespace cclient */
#endif /* CONNECTOR_H_ */
