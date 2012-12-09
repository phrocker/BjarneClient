/*
 * Master.h
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#ifndef MASTER_H_
#define MASTER_H_
#include <string>
#include "ClientInterface.h"
using namespace std;
using namespace interconnect;
class Master : public ClientInterface {
public:
	Master(const string host, const int port);
	virtual ~Master();
};

#endif /* MASTER_H_ */
