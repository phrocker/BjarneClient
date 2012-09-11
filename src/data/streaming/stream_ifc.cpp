#include "data_writer.h"

#include "input/in_stream.h"

#include "input/byte_in_stream.h"

#include "dataoutstream.h"

#include "byte_stream.h"
/*
 */

using namespace cclient::data::streams;

StreamInterface::StreamInterface() {

}

StreamInterface::~StreamInterface() {

}

StreamInterface* StreamInterface::getStream() {
	return NULL;
}

uint64_t StreamInterface::write(OutputStream *out) {
	return 0;
}

uint64_t StreamInterface::read(InputStream *in) {
	return 0;
}

