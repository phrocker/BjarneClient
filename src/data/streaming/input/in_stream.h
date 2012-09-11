#ifndef INPUT_INPUT_STREAM
#define INPUT_INPUT_STREAM

#include <iostream>
#include <stdexcept>

using namespace std;

namespace cclient {
namespace data {
namespace streams {
class InputStream {
public:

	InputStream(istream *ptr, uint64_t pos) :
			istream_ref(ptr), position(new uint64_t(pos)), copy(false) {
	}

	InputStream() :
			istream_ref(NULL), position(new uint64_t(0)), copy(false) {

	}

	virtual InputStream *seek(uint64_t pos) {
		//istream_ref->seekg(pos);
		return this;
	}

	virtual ~InputStream() {

		if (!copy)
			delete position;
	}

	virtual uint64_t getPos() {
		return *position;
	}


	virtual string readString() {
		// write size of string
		uint64_t vLong = readHadoopLong();
		cout << "v long is " << vLong << endl;
		uint8_t *bytes = new uint8_t[vLong];
		readBytes(bytes, vLong);
		string s((char*) bytes);
		delete[] bytes;
		return s;
	}


	virtual uint64_t readBytes(uint8_t *bytes, size_t cnt) {

		istream_ref->read((char*) bytes, cnt);
		*position += cnt;
		return *position;
	}

	virtual uint64_t readBytes(char *bytes, size_t cnt) {

		istream_ref->read((char*) bytes, cnt);
		*position += cnt;
		return *position;
	}


	virtual uint64_t readBytes(uint8_t **bytes, size_t cnt) {
		if (*bytes == NULL) {
			*bytes = new uint8_t[cnt];
		}
		return readBytes(*bytes, cnt);
	}


	virtual uint8_t readByte() {
		uint8_t byte;
		readBytes((uint8_t*) &byte, 1);
		*position += 1;
		return byte;
	}


	virtual short readShort() {
		//  memcpy(shortByte,shortVal,2);
		short shortVal;
		readBytes((uint8_t*) &shortVal, 2);
		*position += 2;
		return shortVal;
	}


	virtual int readInt() {
		int intVal = 0;
		readBytes((uint8_t*) &intVal, 4);
		*position += 4;
		return intVal;
	}


	virtual uint64_t readLong() {
		uint64_t val;
		readBytes((uint8_t*) &val, 8);
		*position += 8;
		return val;
	}


	virtual uint64_t readBoolean() {

		uint8_t byte = 0x00;
		;
		readBytes((uint8_t*) &byte, 1);
		*position += 1;
		if (byte)
			return 0x01;
		else
			return 0x00;
	}


	/**
	 * Taken directly from accumulo code.
	 */
	virtual uint64_t readHadoopLong() {
		uint8_t firstByte = readByte();

		if (firstByte >= -32) {
			return firstByte;
		}

		int len = firstByte + 129;
		switch ((firstByte + 128) / 8) {
		case 11:
		case 10:
		case 9:
		case 8:
		case 7:
			return ((firstByte + 52) << 8) | readByte();
		case 6:
		case 5:
		case 4:
		case 3:
			return ((firstByte + 88) << 16) | readByte();
		case 2:
		case 1:
			return ((firstByte + 112) << 24) | (readByte() << 8) | readByte();
		case 0:

			switch (len) {
			case 4:
				return readInt();
			case 5:
				return ((long) readInt()) << 8 | readByte();
			case 6:
				return ((long) readInt()) << 16 | readByte();
			case 7:
				return ((long) readInt()) << 24 | (readByte() << 8) | readByte();
			case 8:
				return readLong();
			default:
				throw std::runtime_error("Unsupported file type");
			}
		default:
			throw std::runtime_error("Unsupported file type");
		}

	}

	/**
	 * Bytes written shall always return the current position
	 * of the stream ( this stream )
	 * @returns stream position
	 */
	virtual uint32_t bytesRead() {

		return *position;
	}

	virtual uint64_t bytesAvailable() {
		// by default, return the maximum
		return -1;
	}

protected:

	int numberOfLeadingZeros(uint64_t i) {
		// HD, Figure 5-6
		if (i == 0)
			return 64;
		int n = 1;
		int x = (int) (i >> 32);
		if (x == 0) {
			n += 32;
			x = (int) i;
		}
		if (x >> 16 == 0) {
			n += 16;
			x <<= 16;
		}
		if (x >> 24 == 0) {
			n += 8;
			x <<= 8;
		}
		if (x >> 28 == 0) {
			n += 4;
			x <<= 4;
		}
		if (x >> 30 == 0) {
			n += 2;
			x <<= 2;
		}
		n -= x >> 31;
		return n;
	}

	/**
	 * Constructor, which is to be used by DataOutputStream. Note that it is
	 * a friend class
	 * @param ptr stream pointer
	 */
	InputStream(InputStream *ptr) :
			istream_ref(ptr->istream_ref), position(ptr->position), copy(true) {

	}
	// identify that we have copied a stream
	// useful when deleting position
	bool copy;
	// position pointer.
	uint64_t *position;
	// ostream reference.
	istream *istream_ref;

};
}
}
}

#endif
