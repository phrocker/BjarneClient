#ifndef HADOOP_DIN_STREAM
#define HADOOP_DIN_STREAM

#include <iostream>
#include <stdexcept>
using namespace std;
#include "in_stream.h"

namespace cclient {
namespace data {
namespace streams {

class HadoopDataInputStream: public InputStream {
public:

	HadoopDataInputStream(InputStream *out_stream) :
			InputStream(out_stream), input_stream_ref(out_stream) {

	}

	virtual ~HadoopDataInputStream() {

	}

	virtual InputStream *seek(uint64_t pos) {
		input_stream_ref->seek(pos);
		return this;
	}

	virtual uint64_t readBytes(const uint8_t *bytes, size_t cnt) {
		return input_stream_ref->readBytes(bytes, cnt);
	}

protected:
	// output stream reference.
	InputStream *input_stream_ref;

};
}
}
}
#endif
