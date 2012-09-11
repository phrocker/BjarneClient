/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
#ifndef tabletserver_TYPES_H
#define tabletserver_TYPES_H

#include <Thrift.h>
#include <TApplicationException.h>
#include <protocol/TProtocol.h>
#include <transport/TTransport.h>

#include "data_types.h"
#include "security_types.h"
#include "client_types.h"
#include "master_types.h"
#include "cloudtrace_types.h"


namespace accumulo { namespace tabletserver {

struct ScanType {
  enum type {
    SINGLE = 0,
    BATCH = 1
  };
};

extern const std::map<int, const char*> _ScanType_VALUES_TO_NAMES;

struct ScanState {
  enum type {
    IDLE = 0,
    RUNNING = 1,
    QUEUED = 2
  };
};

extern const std::map<int, const char*> _ScanState_VALUES_TO_NAMES;

typedef int64_t LogID;

typedef int32_t TabletID;

typedef struct _NotServingTabletException__isset {
  _NotServingTabletException__isset() : extent(false) {}
  bool extent;
} _NotServingTabletException__isset;

class NotServingTabletException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "636807D016867BC3A79FD54005E0677E";
  static const uint8_t binary_fingerprint[16]; // = {0x63,0x68,0x07,0xD0,0x16,0x86,0x7B,0xC3,0xA7,0x9F,0xD5,0x40,0x05,0xE0,0x67,0x7E};

  NotServingTabletException() {
  }

  virtual ~NotServingTabletException() throw() {}

  accumulo::data::TKeyExtent extent;

  _NotServingTabletException__isset __isset;

  bool operator == (const NotServingTabletException & rhs) const
  {
    if (!(extent == rhs.extent))
      return false;
    return true;
  }
  bool operator != (const NotServingTabletException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const NotServingTabletException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TooManyFilesException__isset {
  _TooManyFilesException__isset() : extent(false) {}
  bool extent;
} _TooManyFilesException__isset;

class TooManyFilesException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "636807D016867BC3A79FD54005E0677E";
  static const uint8_t binary_fingerprint[16]; // = {0x63,0x68,0x07,0xD0,0x16,0x86,0x7B,0xC3,0xA7,0x9F,0xD5,0x40,0x05,0xE0,0x67,0x7E};

  TooManyFilesException() {
  }

  virtual ~TooManyFilesException() throw() {}

  accumulo::data::TKeyExtent extent;

  _TooManyFilesException__isset __isset;

  bool operator == (const TooManyFilesException & rhs) const
  {
    if (!(extent == rhs.extent))
      return false;
    return true;
  }
  bool operator != (const TooManyFilesException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TooManyFilesException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class NoSuchScanIDException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  NoSuchScanIDException() {
  }

  virtual ~NoSuchScanIDException() throw() {}


  bool operator == (const NoSuchScanIDException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const NoSuchScanIDException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const NoSuchScanIDException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ConstraintViolationException__isset {
  _ConstraintViolationException__isset() : violationSummaries(false) {}
  bool violationSummaries;
} _ConstraintViolationException__isset;

class ConstraintViolationException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "3884B00559CED48471BE62CF7B94E4D1";
  static const uint8_t binary_fingerprint[16]; // = {0x38,0x84,0xB0,0x05,0x59,0xCE,0xD4,0x84,0x71,0xBE,0x62,0xCF,0x7B,0x94,0xE4,0xD1};

  ConstraintViolationException() {
  }

  virtual ~ConstraintViolationException() throw() {}

  std::vector<accumulo::data::TConstraintViolationSummary>  violationSummaries;

  _ConstraintViolationException__isset __isset;

  bool operator == (const ConstraintViolationException & rhs) const
  {
    if (!(violationSummaries == rhs.violationSummaries))
      return false;
    return true;
  }
  bool operator != (const ConstraintViolationException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ConstraintViolationException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ActionStats__isset {
  _ActionStats__isset() : status(false), elapsed(false), num(false), count(false), sumDev(false), fail(false), queueTime(false), queueSumDev(false) {}
  bool status;
  bool elapsed;
  bool num;
  bool count;
  bool sumDev;
  bool fail;
  bool queueTime;
  bool queueSumDev;
} _ActionStats__isset;

class ActionStats {
 public:

  static const char* ascii_fingerprint; // = "38F10F0BD2F539F3CA606E0480459450";
  static const uint8_t binary_fingerprint[16]; // = {0x38,0xF1,0x0F,0x0B,0xD2,0xF5,0x39,0xF3,0xCA,0x60,0x6E,0x04,0x80,0x45,0x94,0x50};

  ActionStats() : status(0), elapsed(0), num(0), count(0), sumDev(0), fail(0), queueTime(0), queueSumDev(0) {
  }

  virtual ~ActionStats() throw() {}

  int32_t status;
  double elapsed;
  int32_t num;
  int64_t count;
  double sumDev;
  int32_t fail;
  double queueTime;
  double queueSumDev;

  _ActionStats__isset __isset;

  bool operator == (const ActionStats & rhs) const
  {
    if (!(status == rhs.status))
      return false;
    if (!(elapsed == rhs.elapsed))
      return false;
    if (!(num == rhs.num))
      return false;
    if (!(count == rhs.count))
      return false;
    if (!(sumDev == rhs.sumDev))
      return false;
    if (!(fail == rhs.fail))
      return false;
    if (!(queueTime == rhs.queueTime))
      return false;
    if (!(queueSumDev == rhs.queueSumDev))
      return false;
    return true;
  }
  bool operator != (const ActionStats &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ActionStats & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TabletStats__isset {
  _TabletStats__isset() : extent(false), cmajor(false), cminor(false), split(false), numEntries(false), ingestRate(false), queryRate(false), splitCreationTime(false) {}
  bool extent;
  bool cmajor;
  bool cminor;
  bool split;
  bool numEntries;
  bool ingestRate;
  bool queryRate;
  bool splitCreationTime;
} _TabletStats__isset;

class TabletStats {
 public:

  static const char* ascii_fingerprint; // = "EDECD13D47255249DE8E10225F40F87E";
  static const uint8_t binary_fingerprint[16]; // = {0xED,0xEC,0xD1,0x3D,0x47,0x25,0x52,0x49,0xDE,0x8E,0x10,0x22,0x5F,0x40,0xF8,0x7E};

  TabletStats() : numEntries(0), ingestRate(0), queryRate(0), splitCreationTime(0) {
  }

  virtual ~TabletStats() throw() {}

  accumulo::data::TKeyExtent extent;
  ActionStats cmajor;
  ActionStats cminor;
  ActionStats split;
  int64_t numEntries;
  double ingestRate;
  double queryRate;
  int64_t splitCreationTime;

  _TabletStats__isset __isset;

  bool operator == (const TabletStats & rhs) const
  {
    if (!(extent == rhs.extent))
      return false;
    if (!(cmajor == rhs.cmajor))
      return false;
    if (!(cminor == rhs.cminor))
      return false;
    if (!(split == rhs.split))
      return false;
    if (!(numEntries == rhs.numEntries))
      return false;
    if (!(ingestRate == rhs.ingestRate))
      return false;
    if (!(queryRate == rhs.queryRate))
      return false;
    if (!(splitCreationTime == rhs.splitCreationTime))
      return false;
    return true;
  }
  bool operator != (const TabletStats &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TabletStats & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ActiveScan__isset {
  _ActiveScan__isset() : client(false), user(false), tableId(false), age(false), idleTime(false), type(false), state(false), extent(false), columns(false), ssiList(false), ssio(false) {}
  bool client;
  bool user;
  bool tableId;
  bool age;
  bool idleTime;
  bool type;
  bool state;
  bool extent;
  bool columns;
  bool ssiList;
  bool ssio;
} _ActiveScan__isset;

class ActiveScan {
 public:

  static const char* ascii_fingerprint; // = "F4F889DE141BE07DB04911E941115C34";
  static const uint8_t binary_fingerprint[16]; // = {0xF4,0xF8,0x89,0xDE,0x14,0x1B,0xE0,0x7D,0xB0,0x49,0x11,0xE9,0x41,0x11,0x5C,0x34};

  ActiveScan() : client(""), user(""), tableId(""), age(0), idleTime(0) {
  }

  virtual ~ActiveScan() throw() {}

  std::string client;
  std::string user;
  std::string tableId;
  int64_t age;
  int64_t idleTime;
  ScanType::type type;
  ScanState::type state;
  accumulo::data::TKeyExtent extent;
  std::vector<accumulo::data::TColumn>  columns;
  std::vector<accumulo::data::IterInfo>  ssiList;
  std::map<std::string, std::map<std::string, std::string> >  ssio;

  _ActiveScan__isset __isset;

  bool operator == (const ActiveScan & rhs) const
  {
    if (!(client == rhs.client))
      return false;
    if (!(user == rhs.user))
      return false;
    if (!(tableId == rhs.tableId))
      return false;
    if (!(age == rhs.age))
      return false;
    if (!(idleTime == rhs.idleTime))
      return false;
    if (!(type == rhs.type))
      return false;
    if (!(state == rhs.state))
      return false;
    if (!(extent == rhs.extent))
      return false;
    if (!(columns == rhs.columns))
      return false;
    if (!(ssiList == rhs.ssiList))
      return false;
    if (!(ssio == rhs.ssio))
      return false;
    return true;
  }
  bool operator != (const ActiveScan &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ActiveScan & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class NoSuchLogIDException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  NoSuchLogIDException() {
  }

  virtual ~NoSuchLogIDException() throw() {}


  bool operator == (const NoSuchLogIDException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const NoSuchLogIDException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const NoSuchLogIDException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LoggerClosedException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  LoggerClosedException() {
  }

  virtual ~LoggerClosedException() throw() {}


  bool operator == (const LoggerClosedException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LoggerClosedException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LoggerClosedException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LogFile__isset {
  _LogFile__isset() : name(false), id(false) {}
  bool name;
  bool id;
} _LogFile__isset;

class LogFile {
 public:

  static const char* ascii_fingerprint; // = "1CCCF6FC31CFD1D61BBBB1BAF3590620";
  static const uint8_t binary_fingerprint[16]; // = {0x1C,0xCC,0xF6,0xFC,0x31,0xCF,0xD1,0xD6,0x1B,0xBB,0xB1,0xBA,0xF3,0x59,0x06,0x20};

  LogFile() : name(""), id(0) {
  }

  virtual ~LogFile() throw() {}

  std::string name;
  LogID id;

  _LogFile__isset __isset;

  bool operator == (const LogFile & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (!(id == rhs.id))
      return false;
    return true;
  }
  bool operator != (const LogFile &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LogFile & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TabletMutations__isset {
  _TabletMutations__isset() : tabletID(false), seq(false), mutations(false) {}
  bool tabletID;
  bool seq;
  bool mutations;
} _TabletMutations__isset;

class TabletMutations {
 public:

  static const char* ascii_fingerprint; // = "9C2B6033A382BDB0F85A25591E4A6801";
  static const uint8_t binary_fingerprint[16]; // = {0x9C,0x2B,0x60,0x33,0xA3,0x82,0xBD,0xB0,0xF8,0x5A,0x25,0x59,0x1E,0x4A,0x68,0x01};

  TabletMutations() : tabletID(0), seq(0) {
  }

  virtual ~TabletMutations() throw() {}

  TabletID tabletID;
  int64_t seq;
  std::vector<accumulo::data::TMutation>  mutations;

  _TabletMutations__isset __isset;

  bool operator == (const TabletMutations & rhs) const
  {
    if (!(tabletID == rhs.tabletID))
      return false;
    if (!(seq == rhs.seq))
      return false;
    if (!(mutations == rhs.mutations))
      return false;
    return true;
  }
  bool operator != (const TabletMutations &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TabletMutations & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LogCopyInfo__isset {
  _LogCopyInfo__isset() : fileSize(false), loggerZNode(false) {}
  bool fileSize;
  bool loggerZNode;
} _LogCopyInfo__isset;

class LogCopyInfo {
 public:

  static const char* ascii_fingerprint; // = "727CAEA8265A5DE67DBC931F55CD8753";
  static const uint8_t binary_fingerprint[16]; // = {0x72,0x7C,0xAE,0xA8,0x26,0x5A,0x5D,0xE6,0x7D,0xBC,0x93,0x1F,0x55,0xCD,0x87,0x53};

  LogCopyInfo() : fileSize(0), loggerZNode("") {
  }

  virtual ~LogCopyInfo() throw() {}

  int64_t fileSize;
  std::string loggerZNode;

  _LogCopyInfo__isset __isset;

  bool operator == (const LogCopyInfo & rhs) const
  {
    if (!(fileSize == rhs.fileSize))
      return false;
    if (!(loggerZNode == rhs.loggerZNode))
      return false;
    return true;
  }
  bool operator != (const LogCopyInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LogCopyInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

}} // namespace

#endif
