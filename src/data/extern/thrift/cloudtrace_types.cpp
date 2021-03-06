/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
#include "cloudtrace_types.h"

namespace accumulo { namespace cloudtrace {

const char* RemoteSpan::ascii_fingerprint = "22EA46E738FDCE7962363D25AEC46FDF";
const uint8_t RemoteSpan::binary_fingerprint[16] = {0x22,0xEA,0x46,0xE7,0x38,0xFD,0xCE,0x79,0x62,0x36,0x3D,0x25,0xAE,0xC4,0x6F,0xDF};

uint32_t RemoteSpan::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->sender);
          this->__isset.sender = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->svc);
          this->__isset.svc = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->traceId);
          this->__isset.traceId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->spanId);
          this->__isset.spanId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->parentId);
          this->__isset.parentId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->start);
          this->__isset.start = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->stop);
          this->__isset.stop = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 8:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->description);
          this->__isset.description = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 9:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->data.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _ktype1;
            ::apache::thrift::protocol::TType _vtype2;
            iprot->readMapBegin(_ktype1, _vtype2, _size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              std::string _key5;
              xfer += iprot->readString(_key5);
              std::string& _val6 = this->data[_key5];
              xfer += iprot->readString(_val6);
            }
            iprot->readMapEnd();
          }
          this->__isset.data = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RemoteSpan::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("RemoteSpan");
  xfer += oprot->writeFieldBegin("sender", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->sender);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("svc", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->svc);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("traceId", ::apache::thrift::protocol::T_I64, 3);
  xfer += oprot->writeI64(this->traceId);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("spanId", ::apache::thrift::protocol::T_I64, 4);
  xfer += oprot->writeI64(this->spanId);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("parentId", ::apache::thrift::protocol::T_I64, 5);
  xfer += oprot->writeI64(this->parentId);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("start", ::apache::thrift::protocol::T_I64, 6);
  xfer += oprot->writeI64(this->start);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("stop", ::apache::thrift::protocol::T_I64, 7);
  xfer += oprot->writeI64(this->stop);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("description", ::apache::thrift::protocol::T_STRING, 8);
  xfer += oprot->writeString(this->description);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("data", ::apache::thrift::protocol::T_MAP, 9);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, this->data.size());
    std::map<std::string, std::string> ::const_iterator _iter7;
    for (_iter7 = this->data.begin(); _iter7 != this->data.end(); ++_iter7)
    {
      xfer += oprot->writeString(_iter7->first);
      xfer += oprot->writeString(_iter7->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* TInfo::ascii_fingerprint = "F33135321253DAEB67B0E79E416CA831";
const uint8_t TInfo::binary_fingerprint[16] = {0xF3,0x31,0x35,0x32,0x12,0x53,0xDA,0xEB,0x67,0xB0,0xE7,0x9E,0x41,0x6C,0xA8,0x31};

uint32_t TInfo::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->traceId);
          this->__isset.traceId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->parentId);
          this->__isset.parentId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TInfo::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TInfo");
  xfer += oprot->writeFieldBegin("traceId", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->traceId);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("parentId", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->parentId);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

}} // namespace
