// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.
#define SIGNED_RIGHT_SHIFT_IS 5
#define ARITHMETIC_RIGHT_SHIFT 5

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



using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

#include <map>

using namespace std;


//#include "MasterClient.h"
#include "../ClientService.h"
#include "../TabletClientService.h"
#include "../data/constructs/Mutation.h"
#include "../writer/Sink.h"
#include "../writer/MutationCollector.h"

namespace cclient {

namespace tabletClient {



using namespace cclient::data;
using namespace cclient::writer;

class ClientException: public exception {
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

class ClientInterface : public Sink
{
public:
	ClientInterface(string host, int port, string masterHost, int masterPort) :
			server_host(host), server_port(port), authenticated(false) {
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

		//	masterClient = new master::MasterClient(masterHost,masterPort);
	}

	~ClientInterface() {
		transport->close();

		//	masterTransport->close();
	}



	void login(string username, string password) {
		//authenticateUser(const TInfo& tinfo, const AuthInfo& credentials, const std::string& user, const std::string& password)
		accumulo::cloudtrace::TInfo tinfo;
		accumulo::security::AuthInfo creds;
		string str = "";

		cout << str << endl;

		creds.instanceId = instanceId;
		creds.user = username;
		creds.password = password;

		tinfo.parentId = 0;
		tinfo.traceId = 111;
		if (!client->authenticateUser(tinfo, creds, username, password)) {
			throw ClientException("Invalid username");
		}
		authenticated = true;
		authenticated_user = username;
		authenticated_password = password;

	}

	uint8_t write(
			MutationCollector &writer) {

		if (!authenticated) {
				throw ClientException("not authenticated");
			}

			accumulo::cloudtrace::TInfo tinfo;
			accumulo::security::AuthInfo creds;

			creds.instanceId = instanceId;
			creds.user = authenticated_user;
			creds.password = authenticated_password;

	//		tinfo.parentId = 0;
//			tinfo.traceId = 112;

			accumulo::data::UpdateID upId = tserverClient->startUpdate(tinfo,
					creds);
			accumulo::data::UpdateErrors errors;

			accumulo::data::TKeyExtent extent;

			extent.table = "3";
			cout << extent.table << endl;

			extent.endRow = "ha";
			//extent.prevEndRow.resize(1);
			//extent.prevEndRow.push_back(0x00);
			//extent.prevEndRow.append("haha");
			//extent.endRow.push_back(0x01);
			//extent.endRow = "";
			//extent.endRow.append("ha");
	//		extent.endRow.resize(1);
			//extent.endRow.push_back(0x01);
			vector<accumulo::data::TMutation> thriftMtations;

			vector<Mutation>::iterator mutationIter = writer.getMutations();

			for( ; mutationIter < writer.end(); mutationIter++)
			{
				cout << "adding mutation " << (*mutationIter).getRow() << endl;
				thriftMtations.push_back( (*mutationIter).toThrift() );
			}



			tserverClient->applyUpdates(tinfo,upId,extent,thriftMtations);

			tserverClient->closeUpdate(errors, tinfo, upId);

			cout << " what we have " << errors.failedExtents.size() << " " << errors.violationSummaries.size() << " " << errors.authorizationFailures.size() <<  endl;


			std::map<accumulo::data::TKeyExtent, int64_t>::iterator it;

			for(it = errors.failedExtents.begin(); it != errors.failedExtents.end(); it++ )
			{
				cout << (*it).first.table << " " << (*it).second << endl;
			}
			writer.flush();

		return 1;
	}


protected:



	accumulo::client::ClientServiceClient *client;
	accumulo::tabletserver::TabletClientServiceClient *tserverClient;
	//master::MasterClient *masterClient;
private:
	string server_host;
	int server_port;
	bool authenticated;

	string authenticated_user;
	string authenticated_password;
// info abt cluster
	string instanceId;
	string zookeepers;
	shared_ptr<TTransport> transport;
	shared_ptr<TTransport> masterTransport;

};
}
}

int main(int argc, char **argv) {
  int port = 9090;
  /*
  shared_ptr<ClientServiceHandler> handler(new ClientServiceHandler());
  shared_ptr<TProcessor> processor(new ClientServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();


  shared_ptr<TTransport> serverTransport( new TSocket("localhost",9997));
  shared_ptr<TTransport> transporty( new TFramedTransport(serverTransport));
  shared_ptr<TProtocol> protocolPtr( new TCompactProtocol(transporty));

  ClientServiceClient *client = new ClientServiceClient(protocolPtr);
  serverTransport->open();
  string str="";

  client->getZooKeepers(str);
  cout << str << endl;
  transporty->close();
  */
  cclient::tabletClient::ClientInterface *interface = new cclient::tabletClient::ClientInterface("localhost",9997,"localhost",9999);
  try
  {
  	  interface->login("root","secret");
  	  cclient::data::Mutation m("abba");
  	  char *value = new char[1];
  	  value[0] = 0x97;
  	  m.put("cf","cq","cv",1345958001096,(uint8_t*)value,1);

  	  cclient::writer::MutationCollector collector("test");
  	  collector.write(m);
  	  interface->write(collector);
  }
  catch(accumulo::security::ThriftSecurityException &tfe)
  {
	  cout << "error " << tfe.user << " " << tfe.code << endl;
  }
  delete interface;
  return 0;
}

