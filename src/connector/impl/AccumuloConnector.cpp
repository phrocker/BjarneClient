/*
 * AccumuloConnector.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: marc
 */

#include "AccumuloConnector.h"

#include "../../data/constructs/client/Instance.h"
#include "../../data/constructs/security/AuthInfo.h"

using namespace cclient::data::security;
using namespace cclient::data;
AccumuloConnector::AccumuloConnector(Instance *instance, string user, string &password)
{
	myInstance = instance;
	credentials = new AuthInfo(user,password,instance->getInstanceId());
	password.clear();
}

AccumuloConnector::~AccumuloConnector() {
	// TODO Auto-generated destructor stub
}

Scanner *AccumuloConnector::createScanner(string tableName, Authorizations *authorizations, int numQueryThreads)
{

}

