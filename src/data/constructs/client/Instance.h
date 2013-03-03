/*
 * Instance.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <string>
#include <list>

using namespace std;

#include "../../../interconnect/Master.h"
#include "Connector.h"
#include "../security/AuthInfo.h"
#include "../configuration/Configuration.h"

#include <string>
#include <list>
using namespace std;

namespace cclient {
namespace data {

using namespace cclient::impl;
using namespace cclient::connector::impl;
using namespace cclient::data::security;
using namespace interconnect;
class Instance {
public:
	virtual string getRootTabletLocation() = 0;
	virtual vector<string> getMasterLocations = 0;
	virtual string getInstanceId() = 0;
	virtual string getInstanceName() = 0;
	//virtual string getZooKeepers() = 0;
	virtual Connector *getConnector(AuthInfo *authoration) = 0;
	virtual Configuration *getConfiguration() = 0;
	virtual void setConfiguration(Configuration *conf) = 0;
	virtual Master * getMasterInterconnects();
	virtual ~Instance();
};

} /* namespace impl */
} /* namespace cclient */
#endif /* INSTANCE_H_ */

