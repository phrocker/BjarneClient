#include "byte_stream.h"
#include <string.h> /* memset */

using namespace cclient::data::streams;

ByteOutputStream::ByteOutputStream(size_t initial_size,
		OutputStream *out_stream) :
		offset(0), output_stream_ref(out_stream) {
	size = initial_size;
	array = new char[size];
	memset(array, 0x00, size);
}

ByteOutputStream::~ByteOutputStream() {
	flush();
	delete[] array;
}

void ByteOutputStream::flush() {
	if (output_stream_ref != NULL) {
		output_stream_ref->write(array, offset);
	}
	offset = 0;
}

 uint64_t ByteOutputStream::getPos() {
	return offset;
}

void ByteOutputStream::getByteArray(char *inArray, size_t inArraySize) {
	if (inArraySize < offset) {
		throw runtime_error("Sizes are unequal");
	}
	memcpy(inArray, array, offset);
}

char *ByteOutputStream::getByteArray() {
	return array;
}

size_t ByteOutputStream::getSize() {
	return size;
}

void ByteOutputStream::setOutputStreamRef(OutputStream *out_stream) {
	output_stream_ref = out_stream;
}

 uint64_t ByteOutputStream::write(const char *bytes, long cnt) {

	if (size - offset < cnt) {
		// we don't have space, so create
		// a new array that we can copy to
		char *nArray = new char[size + (cnt * 2)];
		memcpy(nArray, array, offset);

		delete[] array;
		array = nArray;
		size += cnt * 2;
	}
	memcpy(array + offset, bytes, cnt);
	offset += cnt;
	return offset;
}

 uint64_t ByteOutputStream::writeByte(int byte) {
	uint8_t bt = 0xFF & byte;
	return writeByte(bt);
}

 uint64_t ByteOutputStream::writeString(string s) {
	// write size of string
	writeHadoopLong(s.size());
	return writeBytes((uint8_t*) s.data(), s.size());
}

 uint64_t ByteOutputStream::write(const uint8_t *bytes, long cnt) {
	return write((const char*) bytes, cnt);
}

 uint64_t ByteOutputStream::writeBytes(const uint8_t *bytes,
		size_t cnt) {
	return write((const char*) bytes, cnt);
}

 uint64_t ByteOutputStream::writeByte(const uint8_t byte) {
	return write((const char*) &byte, 1);

}

 uint64_t ByteOutputStream::writeShort(const short shortVal) {

	return write((const char*) &shortVal, 2);
}
 uint64_t ByteOutputStream::writeInt(const int intVal) {
	return write((const char*) &intVal, 4);

}

 uint64_t ByteOutputStream::writeLong(const uint64_t val) {
	return write((const char*) &val, 8);

}

 uint64_t ByteOutputStream::writeBoolean(const bool val) {
	uint8_t byte = 0x00;
	if (val)
		byte = 0x01;
	return write((const char*) &byte, 1);
}

