/*
 * ThriftTabletServer.h
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#ifndef THRIFTTABLETSERVER_H_
#define THRIFTTABLETSERVER_H_

#include <string>
#include "../TabletServer.h"
namespace interconnect
{

using namespace std;



class ThriftTabletServer : public TabletServer {
public:
	ThriftTabletServer(
				const string host, const int port);
	void authenticate(string username, string password);
};

}
}
#endif /* THRIFTTABLETSERVER_H_ */
