/*
 * TabletServer.h
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#ifndef TABLETSERVER_H_
#define TABLETSERVER_H_

#include <string>
#include "ClientInterface.h"

using namespace std;

namespace interconnect {
class TabletServer : public ClientInterface {
public:
	TabletServer(
			const string host, const int port);
	virtual ~TabletServer();
};

}
#endif /* TABLETSERVER_H_ */
