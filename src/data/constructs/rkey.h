/*
 * rkey.h
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#ifndef R_KEY
#define R_KEY

#include "Key.h"
#include <stdint.h>

#include "../streaming/stream_ifc.h"

#include <stdint.h>
#include <cstdio>
#include <cstring>
#include <stdexcept>

namespace cclient {
namespace data {

using namespace cclient::data::streams;

/**
 * Based on the accumulo relative key.
 */
class RelativeKey: public StreamInterface {

public:
	RelativeKey();

	RelativeKey(Key *previous_key, Key *my_key);

	StreamInterface *getStream();

	void setBase(Key *my_key);

	void setPrevious(Key *previous_key);

	uint64_t write(OutputStream *outStream);

	bool operator <(const RelativeKey &rhs) const;

	bool operator <(const RelativeKey *rhs) const;

	~RelativeKey();
protected:

	Key key;

	uint8_t fieldsSame;

	Key prevKey;
	// flags taken from java relative key
	static const uint8_t ROW_SAME = 0x01;
	static const uint8_t CF_SAME = 0x02;
	static const uint8_t CQ_SAME = 0x04;
	static const uint8_t CV_SAME = 0x08;
	static const uint8_t TS_SAME = 0x10;
	static const uint8_t DELETED = 0x20;

	void setKey(Key *keyToCopy, Key *keyToCopyTo);

	bool isSame(std::pair<char*, size_t> a, std::pair<char*, size_t> b);

};
}
}

#endif
