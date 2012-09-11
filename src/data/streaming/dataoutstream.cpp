#include "dataoutstream.h"

using namespace cclient::data::streams;

OutputStream::OutputStream(ostream *ptr, uint64_t pos) :
		ostream_ref(ptr), position(new uint64_t(pos)), copy(false) {
}

OutputStream::OutputStream() :
		ostream_ref(NULL), position(new uint64_t(0)), copy(false) {

}

OutputStream::~OutputStream() {
	flush();
	if (!copy)
		delete position;
}

void OutputStream::flush() {
	if (ostream_ref != NULL)
		ostream_ref->flush();
}

uint64_t OutputStream::getPos() {
	return *position;
}

uint64_t OutputStream::write(const char *bytes, long cnt) {

	ostream_ref->write((const char*) bytes, cnt);
	*position += cnt;
	return *position;
}

uint64_t OutputStream::writeByte(int byte) {
	uint8_t bt = 0xFF & byte;
	return writeByte(bt);
}

uint64_t OutputStream::writeString(string s) {
	// write size of string
	writeHadoopLong(s.size());
	return writeBytes((uint8_t*) s.data(), s.size());
}

uint64_t OutputStream::write(const uint8_t *bytes, long cnt) {
	ostream_ref->write((const char*) bytes, cnt);
	*position += cnt;
	return *position;
}

uint64_t OutputStream::writeBytes(const uint8_t *bytes, size_t cnt) {
	ostream_ref->write((const char*) bytes, cnt);
	*position += cnt;
	return *position;
}

uint64_t OutputStream::writeBytes(const char *bytes, size_t cnt) {
	return writeBytes((const uint8_t*) bytes, cnt);
}

uint64_t OutputStream::writeByte(const uint8_t byte) {
	ostream_ref->write((const char*) &byte, 1);
	*position += 1;
	return *position;
}

uint64_t OutputStream::writeShort(const short shortVal) {
	//  memcpy(shortByte,shortVal,2);
	ostream_ref->write((const char*) &shortVal, 2);
	*position += 2;
	return *position;
}

uint64_t OutputStream::writeInt(const int intVal) {
	//  memcpy(intByte,intVal,2);
	ostream_ref->write((const char*) &intVal, 4);
	*position += 4;
	return *position;
}

uint64_t OutputStream::writeLong(const uint64_t val) {
	ostream_ref->write((const char*) &val, 8);
	*position += 8;
	return *position;
}

uint64_t OutputStream::writeBoolean(const bool val) {
	uint8_t byte = 0x00;
	if (val)
		byte = 0x01;
	ostream_ref->write((const char*) &byte, 1);
	*position += 1;
	return *position;
}

uint64_t OutputStream::writeHadoopLong(const int64_t n) {

	if ((n < 128) && (n >= -32)) {

		write((const char*) &n, 1);
		*position += 1;
		return *position;
		//return writeByte((int) n);

	}

	long un = (n < 0) ? ~n : n;
	int temp = n;
	// how many bytes do we need to represent the number with sign bit?
	int len = (64 - numberOfLeadingZeros(un)) / 8 + 1;
	int firstByte = (int) (n >> ((len - 1) * 8));
	switch (len) {
	case 1:
		// fall it through to firstByte==-1, len=2.
		firstByte >>= 8;
	case 2:
		if ((firstByte < 20) && (firstByte >= -20)) {
			temp -= 52;
			write((const char*) &temp, 1);
			write((const char*) &n, 1);
			*position += 2;
			return *position;
			//writeByte(firstByte - 52);
			//return writeByte((int) n);
		}
		// fall it through to firstByte==0/-1, len=3.
		firstByte >>= 8;
	case 3:
		if ((firstByte < 16) && (firstByte >= -16)) {
			temp -= 88;
			write((const char*) &temp, 1);
			write((const char*) ((short*) &n), 2);
			*position += 3;
			//writeByte(firstByte - 88);
			//return writeShort((int) n);
		}
		// fall it through to firstByte==0/-1, len=4.
		firstByte >>= 8;
	case 4:
		if ((firstByte < 8) && (firstByte >= -8)) {
			/*
			 writeByte(firstByte - 112);
			 writeShort(((int) n) >> 8);
			 return writeByte((int) n);
			 */
			temp -= 112;
			write((const char*) &temp, 1);
			temp = n >> 8;
			write((const char*) ((short*) &temp), 2);
			//ostream_ref->write((const char*)((short*)&n),2);
			write((const char*) &n, 1);
			*position += 4;
			return *position;
		}
		temp = len - 129;
		write((const char*) &temp, 1);
		write((const char*) &n, 4);
		*position += 5;
		return *position;
		//writeByte(len - 129);

		///return writeInt((int) n);
	case 5:
		temp = len - 129;
		write((const char*) &temp, 1);
		temp = n >> 8;
		write((const char*) &temp, 4);
		write((const char*) &n, 1);
		*position += 6;
		return *position;
		/*
		 writeByte(len - 129);
		 writeInt((int) (n >> 8));
		 return writeByte((int) n);
		 */
	case 6:
		temp = len - 129;
		write((const char*) &temp, 1);
		temp = n >> 16;
		write((const char*) &temp, 4);
		write((const char*) ((short*) &n), 2);
		*position += 7;
		return *position;
		/*
		 writeByte(len - 129);
		 writeInt((int) (n >> 16));
		 return writeShort((int) n);
		 */
	case 7:
		temp = len - 129;
		write((const char*) &temp, 1);
		temp = n >> 24;
		write((const char*) &temp, 4);
		temp = n >> 8;
		write((const char*) ((short*) &temp), 2);
		write((const char*) ((short*) &n), 1);
		*position += 8;
		return *position;
		/*
		 writeByte(len - 129);
		 writeInt((int) (n >> 24));
		 writeShort((int) (n >> 8));
		 return writeByte((int) n);
		 */
	case 8:
		temp = len - 129;
		write((const char*) &temp, 1);

		write((const char*) &n, 8);
		*position += 9;
		return *position;
		/*
		 writeByte(len - 129);
		 return writeLong(n);
		 */
	default:
		return *position;
	};
	return *position;

}

uint32_t OutputStream::bytesWritten() {

	return *position;
}
