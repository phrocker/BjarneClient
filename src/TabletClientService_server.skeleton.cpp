// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "TabletClientService.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace accumulo::tabletserver;

class TabletClientServiceHandler : virtual public TabletClientServiceIf {
 public:
  TabletClientServiceHandler() {
    // Your initialization goes here
  }

  void startScan(accumulo::data::InitialScan& _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const accumulo::data::TKeyExtent& extent, const accumulo::data::TRange& range, const std::vector<accumulo::data::TColumn> & columns, const int32_t batchSize, const std::vector<accumulo::data::IterInfo> & ssiList, const std::map<std::string, std::map<std::string, std::string> > & ssio, const std::vector<std::string> & authorizations, const bool waitForWrites, const bool isolated) {
    // Your implementation goes here
    printf("startScan\n");
  }

  void continueScan(accumulo::data::ScanResult& _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::data::ScanID scanID) {
    // Your implementation goes here
    printf("continueScan\n");
  }

  void closeScan(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::data::ScanID scanID) {
    // Your implementation goes here
    printf("closeScan\n");
  }

  void startMultiScan(accumulo::data::InitialMultiScan& _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const accumulo::data::ScanBatch& batch, const std::vector<accumulo::data::TColumn> & columns, const std::vector<accumulo::data::IterInfo> & ssiList, const std::map<std::string, std::map<std::string, std::string> > & ssio, const std::vector<std::string> & authorizations, const bool waitForWrites) {
    // Your implementation goes here
    printf("startMultiScan\n");
  }

  void continueMultiScan(accumulo::data::MultiScanResult& _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::data::ScanID scanID) {
    // Your implementation goes here
    printf("continueMultiScan\n");
  }

  void closeMultiScan(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::data::ScanID scanID) {
    // Your implementation goes here
    printf("closeMultiScan\n");
  }

  accumulo::data::UpdateID startUpdate(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials) {
    // Your implementation goes here
    printf("startUpdate\n");
  }

  void applyUpdates(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::data::UpdateID updateID, const accumulo::data::TKeyExtent& keyExtent, const std::vector<accumulo::data::TMutation> & mutations) {
    // Your implementation goes here
    printf("applyUpdates\n");
  }

  void closeUpdate(accumulo::data::UpdateErrors& _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::data::UpdateID updateID) {
    // Your implementation goes here
    printf("closeUpdate\n");
  }

  void update(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const accumulo::data::TKeyExtent& keyExtent, const accumulo::data::TMutation& mutation) {
    // Your implementation goes here
    printf("update\n");
  }

  void bulkImport(std::vector<accumulo::data::TKeyExtent> & _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const int64_t tid, const accumulo::data::TabletFiles& files, const bool setTime) {
    // Your implementation goes here
    printf("bulkImport\n");
  }

  void splitTablet(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const accumulo::data::TKeyExtent& extent, const std::string& splitPoint) {
    // Your implementation goes here
    printf("splitTablet\n");
  }

  void loadTablet(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock, const accumulo::data::TKeyExtent& extent) {
    // Your implementation goes here
    printf("loadTablet\n");
  }

  void unloadTablet(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock, const accumulo::data::TKeyExtent& extent, const bool save) {
    // Your implementation goes here
    printf("unloadTablet\n");
  }

  void flush(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock, const std::string& tableId, const std::string& startRow, const std::string& endRow) {
    // Your implementation goes here
    printf("flush\n");
  }

  void flushTablet(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock, const accumulo::data::TKeyExtent& extent) {
    // Your implementation goes here
    printf("flushTablet\n");
  }

  void chop(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock, const accumulo::data::TKeyExtent& extent) {
    // Your implementation goes here
    printf("chop\n");
  }

  void compact(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock, const std::string& tableId, const std::string& startRow, const std::string& endRow) {
    // Your implementation goes here
    printf("compact\n");
  }

  void useLoggers(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::set<std::string> & loggers) {
    // Your implementation goes here
    printf("useLoggers\n");
  }

  void getTabletServerStatus(accumulo::master::TabletServerStatus& _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials) {
    // Your implementation goes here
    printf("getTabletServerStatus\n");
  }

  void getTabletStats(std::vector<TabletStats> & _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& tableId) {
    // Your implementation goes here
    printf("getTabletStats\n");
  }

  void getHistoricalStats(TabletStats& _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials) {
    // Your implementation goes here
    printf("getHistoricalStats\n");
  }

  void halt(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock) {
    // Your implementation goes here
    printf("halt\n");
  }

  void fastHalt(const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials, const std::string& lock) {
    // Your implementation goes here
    printf("fastHalt\n");
  }

  void getActiveScans(std::vector<ActiveScan> & _return, const accumulo::cloudtrace::TInfo& tinfo, const accumulo::security::AuthInfo& credentials) {
    // Your implementation goes here
    printf("getActiveScans\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<TabletClientServiceHandler> handler(new TabletClientServiceHandler());
  shared_ptr<TProcessor> processor(new TabletClientServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

