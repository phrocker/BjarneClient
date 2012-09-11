/*
 * ClientException.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#ifndef CLIENTEXCEPTION_H_
#define CLIENTEXCEPTION_H_

#include <string>

#include <iostream>
using namespace std;
namespace cclient {
namespace exceptions {


class ClientException: public std::exception {
public:
	ClientException(string excp) :
			excp_str(excp) {

	}

	~ClientException() throw () {

	}
	const char *what() {
		return excp_str.c_str();
	}
private:
	string excp_str;
};
} /* namespace data */
} /* namespace cclient */
#endif /* CLIENTEXCEPTION_H_ */
