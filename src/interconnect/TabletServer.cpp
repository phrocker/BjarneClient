/*
 * TabletServer.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#include "TabletServer.h"
#include "ClientInterface.h"
#include <string>
using namespace std;
using namespace interconnect;

TabletServer::TabletServer(
		const string host, const int port) : ::ClientInterface(host,port){
	// TODO Auto-generated constructor stub

}

TabletServer::~TabletServer() {
	// TODO Auto-generated destructor stub
}

