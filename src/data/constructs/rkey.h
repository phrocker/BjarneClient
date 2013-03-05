/**
  * Hello, this is BjarneClient, a free and open implementation of Accumulo
  * and big table. This is meant to be the client that accesses Accumulo
  * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
  * 2013 -- Marc Delta Poppa @ accumulo.net
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.

  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  **/

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
