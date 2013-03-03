
#define SIGNED_RIGHT_SHIFT_IS 5
#define ARITHMETIC_RIGHT_SHIFT 5



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

#include "../ClientService.h"
#include "../TabletClientService.h"

#ifndef MASTER_H_
#define MASTER_H_
#include <string>
#include "ClientInterface.h"
using namespace std;
namespace interconnect{
class Master : public ClientInterface {
public:
	Master(const string host, const int port);
	Master(shared_ptr<TTransport> transport);
	
	
	virtual ~Master();
protected:

	accumulo::client::ClientServiceClient *client;
	accumulo::tabletserver::TabletClientServiceClient *tserverClient;
	shared_ptr<TTransport> transport;

	
};
}
#endif /* MASTER_H_ */
