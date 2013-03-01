/*
 * ClientInterface.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#include "ClientInterface.h"

#include <string>


using namespace std;

using namespace interconnect;

ClientInterface::ClientInterface(
		const string host, const int port) : server_host(host) , server_port( port)
{


}

ClientInterface::~ClientInterface() {
	transport->close();
}

