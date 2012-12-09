/*
 * ThriftTabletServer.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#include <string>


#include "ThriftTabletServer.h"

#include <protocol/TBinaryProtocol.h>
#include <protocol/TCompactProtocol.h>
#include <server/TSimpleServer.h>

#include <transport/TServerSocket.h>
#include <transport/TServerTransport.h>
#include <transport/TTransport.h>
#include <transport/TSocket.h>
#include <server/TNonblockingServer.h>
#include <transport/TBufferTransports.h>

#include <concurrency/ThreadManager.h>
using boost::shared_ptr;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace std;
using namespace interconnect;
using namespace interconnect::thrift;

ThriftTabletServer::ThriftTabletServer(
		const string host, const int port) : ::TabletServer(host,port) {
	shared_ptr<TTransport> serverTransport(new TSocket(host, port));
	shared_ptr<TTransport> transporty(
			new TFramedTransport(serverTransport));
	shared_ptr<TProtocol> protocolPtr(new TCompactProtocol(transporty));
	transporty->open();

	client = new accumulo::client::ClientServiceClient(protocolPtr);
	tserverClient = new accumulo::tabletserver::TabletClientServiceClient(
			protocolPtr);

	transport = transporty;

	client->getZooKeepers(zookeepers);
	client->getInstanceId(instanceId);

}

ThriftTabletServer::~ThriftTabletServer() {
	// TODO Auto-generated destructor stub
}



void
ThriftTabletServer::authenticate(string username, string password) {
		//authenticateUser(const TInfo& tinfo, const AuthInfo& credentials, const std::string& user, const std::string& password)
		accumulo::cloudtrace::TInfo tinfo;
		accumulo::security::AuthInfo creds;
		string str = "";

		cout << str << endl;

		creds.instanceId = instanceId;
		creds.user = username;
		creds.password = password;

		tinfo.parentId = 0;
		// TODO generate a trace ID
		tinfo.traceId = 111;
		if (!client->authenticateUser(tinfo, creds, username, password)) {
			throw ClientException("Invalid username");
		}
		authenticated = true;
		authenticated_user = username;
		authenticated_password = password;

	}
