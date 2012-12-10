/*
 * AccumuloConnector.h
 *
 *  Created on: Oct 16, 2012
 *      Author: marc
 */

#ifndef ACCUMULOCONNECTOR_H_
#define ACCUMULOCONNECTOR_H_

#include "Connector.h"
#include <string>
using namespace std;
#include "../../scanner/thrift/Scanner.h"
#include "../../data/constructs/security/AuthInfo.h"
#include "../../data/constructs/security/Authorizations.h"

namespace cclient {
namespace impl {

using namespace cclient::thrift;
using namespace cclient::data::security;

class AccumuloConnector: public cclient::impl::Connector {
public:
	AccumuloConnector(Instance *instance, string user, string password);
	virtual ~AccumuloConnector();
	Scanner *createScanner(string tableName, Authorizations *authorizations, int numQueryThreads);

};
}}
#endif /* ACCUMULOCONNECTOR_H_ */
