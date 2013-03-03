/*
 * AccumuloConnector.h
 *
 *  Created on: Oct 16, 2012
 *      Author: marc
 */

#ifndef ACCUMULOCONNECTOR_H_
#define ACCUMULOCONNECTOR_H_

#include "../Connector.h"
#include <string>
using namespace std;

#include "../../data/constructs/client/Instance.h"
#include "../../data/constructs/security/AuthInfo.h"
#include "../../data/constructs/security/Authorizations.h"

namespace cclient {
namespace connector {
namespace impl {

using namespace cclient::data::security;
using namespace cclient::data::security;

class AccumuloConnector: public Connector {
public:
	AccumuloConnector(Instance *instance, string user, string password);
	virtual ~AccumuloConnector();
	Scanner *createScanner(string tableName, Authorizations *authorizations, int numQueryThreads);
protected:
    Instance *myInstance;
    AuthInfo *credentials;
};
}}}
#endif /* ACCUMULOCONNECTOR_H_ */
