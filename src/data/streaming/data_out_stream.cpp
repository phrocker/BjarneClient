
#include "data_out_stream.h"

using namespace cclient::data::streams;

HadoopDataOutputStream::HadoopDataOutputStream(OutputStream *out_stream)  : OutputStream(out_stream), output_stream_ref( out_stream )
{

}

virtual HadoopDataOutputStream::~HadoopDataOutputStream() {

}

virtual uint64_t HadoopDataOutputStream::getPos() {
	return output_stream_ref->getPos();
}

uint64_t HadoopDataOutputStream::write(const char *bytes, long cnt) {
	return output_stream_ref->write(bytes, cnt);
}

virtual uint64_t HadoopDataOutputStream::writeByte(int byte) {
	return output_stream_ref->writeByte(byte);
}

virtual uint64_t HadoopDataOutputStream::writeString(string s) {
	// write size of string
	output_stream_ref->writeHadoopLong(s.size());
	return output_stream_ref->writeBytes((uint8_t*) s.data(), s.size());
}

virtual uint64_t HadoopDataOutputStream::write(const uint8_t *bytes, long cnt) {
	return output_stream_ref->write(bytes, cnt);
}

virtual uint64_t HadoopDataOutputStream::writeBytes(const uint8_t *bytes,
		size_t cnt) {
	return output_stream_ref->writeBytes(bytes, cnt);
}

virtual uint64_t HadoopDataOutputStream::writeByte(const uint8_t byte) {
	return output_stream_ref->writeByte(byte);
}

virtual uint64_t HadoopDataOutputStream::writeShort(const short shortVal) {
	return output_stream_ref->writeShort(shortVal);
}
virtual uint64_t HadoopDataOutputStream::writeInt(const int intVal) {
	return output_stream_ref->writeInt(intVal);
}

virtual uint64_t HadoopDataOutputStream::writeLong(const uint64_t val) {
	return output_stream_ref->writeLong(val);
}

virtual uint64_t HadoopDataOutputStream::writeBoolean(const bool val) {

	return output_stream_ref->writeBoolean(val);
}

virtual uint64_t HadoopDataOutputStream::writeHadoopLong(const int64_t n) {
	if ((n < 128) && (n >= -32)) {
		return output_stream_ref->writeByte((int) n);
	} else {

	}

	long un = (n < 0) ? ~n : n;
	// how many bytes do we need to represent the number with sign bit?
	int len = (64 - output_stream_ref->numberOfLeadingZeros(un)) / 8 + 1;
	int firstByte = (int) (n >> ((len - 1) * 8));
	switch (len) {
	case 1:
		// fall it through to firstByte==-1, len=2.
		firstByte >>= 8;
	case 2:
		if ((firstByte < 20) && (firstByte >= -20)) {
			output_stream_ref->writeByte(firstByte - 52);
			return output_stream_ref->writeByte((int) n);
		}
		// fall it through to firstByte==0/-1, len=3.
		firstByte >>= 8;
	case 3:
		if ((firstByte < 16) && (firstByte >= -16)) {
			output_stream_ref->writeByte(firstByte - 88);
			return output_stream_ref->writeShort((int) n);
		}
		// fall it through to firstByte==0/-1, len=4.
		firstByte >>= 8;
	case 4:
		if ((firstByte < 8) && (firstByte >= -8)) {
			output_stream_ref->writeByte(firstByte - 112);
			output_stream_ref->writeShort(((int) n) >> 8);
			return output_stream_ref->writeByte((int) n);
		}
		output_stream_ref->writeByte(len - 129);
		return output_stream_ref->writeInt((int) n);
	case 5:
		output_stream_ref->writeByte(len - 129);
		output_stream_ref->writeInt((int) (n >> 8));
		return output_stream_ref->writeByte((int) n);
	case 6:
		output_stream_ref->writeByte(len - 129);
		output_stream_ref->writeInt((int) (n >> 16));
		return output_stream_ref->writeShort((int) n);
	case 7:
		output_stream_ref->writeByte(len - 129);
		output_stream_ref->writeInt((int) (n >> 24));
		output_stream_ref->writeShort((int) (n >> 8));
		return output_stream_ref->writeByte((int) n);
	case 8:
		output_stream_ref->writeByte(len - 129);
		return output_stream_ref->writeLong(n);
	default:
		return output_stream_ref->getPos();
	};
	return output_stream_ref->getPos();

}
