/*
 * Master.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: marc
 */

#include "Master.h"
#include <string>

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

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

#include "../ClientService.h"
#include "../TabletClientService.h"
#include "../data/constructs/Mutation.h"
#include "../writer/Sink.h"
#include "../writer/MutationCollector.h"
#include "ClientInterface.h"
#include "../data/exceptions/ClientException.h"

using namespace std;
namespace interconnect{
  
  using namespace cclient::exceptions;
Master::Master(
		const string host, const int port) : ::ClientInterface(host,port){
  
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

void Master::authenticate(string username, string password)
{
  accumulo::cloudtrace::TInfo tinfo;
  accumulo::security::AuthInfo creds;
  string str = "";

  creds.instanceId = instanceId;
  creds.user = username;
  creds.password = password;

  tinfo.parentId = 0;
  tinfo.traceId = rand();
  if (!client->authenticateUser(tinfo, creds, username, password)) {
	  throw ClientException("Invalid username");
  }
  authenticated = true;
  authenticated_user = username;
  authenticated_password = password;
}

Master::~Master() {
	transport->close();
}
}
