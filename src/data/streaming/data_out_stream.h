#ifndef HADOOP_DOUT_STREAM
#define HADOOP_DOUT_STREAM

#include "dataoutstream.h"

namespace cclient {
namespace data {
namespace streams {

class HadoopDataOutputStream: public OutputStream {
public:

	HadoopDataOutputStream(OutputStream *out_stream);

	virtual ~HadoopDataOutputStream();
	virtual uint64_t getPos();
	uint64_t write(const char *bytes, long cnt);
	virtual uint64_t writeByte(int byte);
	virtual uint64_t writeString(string s);
	virtual uint64_t write(const uint8_t *bytes, long cnt);
	virtual uint64_t writeBytes(const uint8_t *bytes, size_t cnt);
	virtual uint64_t writeByte(const uint8_t byte);
	virtual uint64_t writeShort(const short shortVal);
	virtual uint64_t writeInt(const int intVal);
	virtual uint64_t writeLong(const uint64_t val);
	virtual uint64_t writeBoolean(const bool val);
	virtual uint64_t writeHadoopLong(const int64_t n);

protected:
	// output stream reference.
	OutputStream *output_stream_ref;

};
}
}
}
#endif
