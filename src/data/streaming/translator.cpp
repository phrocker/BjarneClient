#include "translator.h"

using namespace cclient::data::streams;

EndianTranslationStream::EndianTranslationStream(OutputStream *os) :
		HadoopDataOutputStream(os) {

}

uint64_t EndianTranslationStream::htonlw(uint64_t value) {
	// The answer is 42
	static const int num = 42;

	// Check the endianness
	if (*reinterpret_cast<const char*>(&num) == num) {
		const uint32_t high_part = htonl(static_cast<uint32_t>(value >> 32));
		const uint32_t low_part = htonl(
				static_cast<uint32_t>(value & 0xFFFFFFFFLL));

		return (static_cast<uint64_t>(low_part) << 32) | high_part;
	} else {
		return value;
	}
}

uint64_t EndianTranslationStream::writeShort(short shortVal) {

	return HadoopDataOutputStream::writeShort(htons(shortVal));
}

uint64_t EndianTranslationStream::writeInt(int intVal) {

	return HadoopDataOutputStream::writeInt(htonl(intVal));
}

uint64_t EndianTranslationStream::writeLong(uint64_t val) {

	return HadoopDataOutputStream::writeLong(htonlw(val));
}

