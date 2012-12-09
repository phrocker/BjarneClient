/*
 * ClientInterface.h
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#ifndef CLIENTINTERFACE_H_
#define CLIENTINTERFACE_H_

#include <string>

namespace interconnect
{


using namespace std;

class ClientInterface {
public:
	ClientInterface(
			const string host, const int port);

	virtual ~ClientInterface();

	virtual void authenticate(string username, string password) = 0;

protected:
	string server_host;
	int server_port;
	bool authenticated;

	string instanceId;
	string zookeepers;

};
}
#endif /* CLIENTINTERFACE_H_ */
