// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "TestService.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace accumulo::cloudtrace;

class TestServiceHandler : virtual public TestServiceIf {
 public:
  TestServiceHandler() {
    // Your initialization goes here
  }

  bool checkTrace(const TInfo& tinfo, const std::string& message) {
    // Your implementation goes here
    printf("checkTrace\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<TestServiceHandler> handler(new TestServiceHandler());
  shared_ptr<TProcessor> processor(new TestServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

