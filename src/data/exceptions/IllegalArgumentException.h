/*
 * ClientException.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#ifndef ILLEGAL_H
#define ILLEGAL_H

#include <string>

#include <iostream>
using namespace std;
namespace cclient {
namespace exceptions {


class IllegalArgumentException: public std::exception {
public:
	IllegalArgumentException(string excp) :
			excp_str(excp) {

	}

	~IllegalArgumentException() throw () {

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
