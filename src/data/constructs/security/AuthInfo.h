/*
 * AuthInfo.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */



#ifndef AUTHINFO_H_
#define AUTHINFO_H_

#include <string>

using namespace std;
namespace cclient {
namespace data {
namespace security {

class AuthInfo {
public:
	AuthInfo(string user,
			 string password,
			 string instanceId);

	virtual ~AuthInfo();
protected:
	string user;
	string instanceId;
	string password;
};
}
} /* namespace data */
} /* namespace cclient */
#endif /* AUTHINFO_H_ */
