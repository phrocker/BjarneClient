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
namespace cclient {
namespace connector {
namespace impl {

AccumuloConnector::AccumuloConnector(
		Instance *instance,
		string user,
		string &password) 
{
	myInstance = instance;
	credentials = new AuthInfo(user,password,instance->getInstanceId());
	password.clear();
	MasterConnect *master = instance->getMasterInterconnects();
	// an exception will be thrown in the event that this does not work.
	master->authenticate(user,password);
	
	

}


AccumuloConnector::~AccumuloConnector() {
	// TODO Auto-generated destructor stub
}

Scanner *AccumuloConnector::createScanner(string tableName, Authorizations *authorizations, int numQueryThreads)
{

}

}}}

