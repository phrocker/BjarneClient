/*
 * AuthInfo.cpp
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#include "AuthInfo.h"

namespace cclient {
namespace data {

AuthInfo::AuthInfo(string user,
		 string password,
		 string instanceId) : user(user), password(password), instanceId(instanceId)
{

}

AuthInfo::~AuthInfo() {
	// TODO Auto-generated destructor stub
}

} /* namespace data */
} /* namespace cclient */
