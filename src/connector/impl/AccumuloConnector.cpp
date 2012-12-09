/*
 * AccumuloConnector.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: marc
 */

#include <string>
#include "AccumuloConnector.h"

#include "../../data/constructs/client/Instance.h"
#include "../../data/constructs/security/AuthInfo.h"
#include "../../interconnect/Master.h"
using namespace std;
using namespace cclient::data::security;
using namespace cclient::data;
using namespace interconnect;
/**
 * Creates a connection to the accumulo server.
 */
AccumuloConnector::AccumuloConnector(
		Instance *instance,
		string user,
		string &password)
{
	myInstance = instance;
	credentials = new AuthInfo(user,password,instance->getInstanceId());
	password.clear();
	Master *master = instance->getMasterInterconnects();
	master->authenticate(user,password);

}

AccumuloConnector::~AccumuloConnector() {
	// TODO Auto-generated destructor stub
}

Scanner *AccumuloConnector::createScanner(string tableName, Authorizations *authorizations, int numQueryThreads)
{

}

