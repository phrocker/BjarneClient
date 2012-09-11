#ifndef MASTER_CLIENT
#define MASTER_CLIENT




#include <string>

#include <protocol/TBinaryProtocol.h>
#include <protocol/TCompactProtocol.h>
#include <server/TSimpleServer.h>

#include <transport/TServerSocket.h>

#include <transport/TTransport.h>
#include <transport/TSocket.h>

#include <transport/TBufferTransports.h>



using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;

using namespace std;

#include "MasterClientService.h"


namespace cmaster{


class MasterClient
{
public:
	MasterClient(
			string host,
			int port);

	~MasterClient();
	void login(string username, string password);

protected:
	accumulo::master::MasterClientServiceClient *client;
private:
	string server_host;
	int server_port;
	bool authenticated;
// info abt cluster
	string instanceId;
	string zookeepers;
	shared_ptr<TTransport> transport;

};
}


#endif
