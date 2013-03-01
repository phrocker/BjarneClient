/*
 * AuthInfo.cpp
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#include "AuthInfo.h"

namespace cclient {
namespace data {
namespace security{

AuthInfo::AuthInfo(string user,
		 string password,
		 string instanceId) : user(user), password(password), instanceId(instanceId)
{

}

AuthInfo::~AuthInfo() {
	
}

  
  
}
} /* namespace data */
} /* namespace cclient */
