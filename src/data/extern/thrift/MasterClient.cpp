#define SIGNED_RIGHT_SHIFT_IS 5
#define ARITHMETIC_RIGHT_SHIFT 5
#include <string>
#include "MasterClientService.h"

#include <protocol/TBinaryProtocol.h>
#include <protocol/TCompactProtocol.h>

#include <transport/TServerSocket.h>
#include <transport/TServerTransport.h>
#include <transport/TTransport.h>
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>



using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
//using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace std;




#include "MasterClient.h"

namespace cmaster{




MasterClient::MasterClient(
			string host,
			int port) : server_host(host) , server_port(port) ,authenticated(false)
	{
		shared_ptr<TTransport> serverTransport( new TSocket(host,port));
		shared_ptr<TTransport> transporty( new TFramedTransport(serverTransport));
		shared_ptr<TProtocol> protocolPtr( new TCompactProtocol(transporty));
		transporty->open();



		client = new accumulo::master::MasterClientServiceClient(protocolPtr);

        transport = transporty;


	}

MasterClient::~MasterClient()
	{
		transport->close();
	}

	void
	MasterClient::login(string username, string password)
	{


	}
}


