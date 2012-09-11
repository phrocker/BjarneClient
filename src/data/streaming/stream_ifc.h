#ifndef DATA_WRITER
#define DATA_WRITER

#include <string>
#include <iostream>
#include <cstring>
using namespace std;

#include <stdint.h>
#include <netinet/in.h>

#include "input/in_stream.h"

#include "data_out_stream.h"

namespace cclient {
namespace data {
namespace streams {

class StreamInterface {
public:

	StreamInterface();
	virtual ~StreamInterface();

	virtual StreamInterface *getStream();

	virtual uint64_t write(OutputStream *out);
	virtual uint64_t read(InputStream *in);

	virtual HadoopDataOutputStream *createDataStream(
			HadoopDataOutputStream *out, string name = "") {
		return NULL;
	}

};
}
}
}

#endif

