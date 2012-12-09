/*
 * ThriftMaster.h
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#ifndef THRIFTMASTER_H_
#define THRIFTMASTER_H_

#include <string>
#include "../Master.h"
namespace interconnect
{

using namespace std;
class ThriftMaster {
public:
	ThriftMaster(const string host, const int port);
	virtual ~ThriftMaster();
	void authenticate(string username, string password);
};
}
#endif /* THRIFTMASTER_H_ */
