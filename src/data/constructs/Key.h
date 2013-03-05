#ifndef KEY
#define KEY
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

#include "../streaming/stream_ifc.h"
#include "../streaming/hadoop_stream.h"

#include <stdint.h>

#include <stdio.h>
#include <string.h>

namespace cclient {
namespace data {

using namespace cclient::data::streams;

/**
 * Code is partially based on some code I wrote in 2009 for a personal project
 */
class Key: public StreamInterface {

public:

	Key();

	virtual ~Key();

	void setRow(const char *r, uint32_t size);
	std::pair<char*, size_t> getRow() {
		return std::make_pair(row, rowLength);
	}

	void setColFamily(const char *r, uint32_t size);

	std::pair<char*, size_t> getColFamily() {
		return std::make_pair(colFamily, columnFamilyLength);
	}

	void setColQualifier(const char *r, uint32_t size, uint32_t offset = 0);

	std::pair<char*, size_t> getColQualifier() {
		return std::make_pair(colQualifier, colQualLen);
	}

	void setColVisibility(const char *r, uint32_t size);

	std::pair<char*, size_t> getColVisibility() {
		return std::make_pair(keyVisibility, colVisSize);
	}

	uint64_t getTimeStamp() {
		return timestamp;
	}

	void setTimeStamp(const uint64_t ts) {
		timestamp = ts;
	}

	bool isDeleted() {
		return deleted;
	}

	StreamInterface *getStream() {
		return this;
	}

	bool operator <(const Key &rhs) const;

	bool operator <(const Key *rhs) const {
		return *this < *rhs;
	}

	bool operator ==(const Key & rhs) const;
	bool operator !=(const Key &rhs) const {
		return !(*this == rhs);
	}

	bool operator ==(const Key *rhs) const {
		return *this == *rhs;
	}
	bool operator !=(const Key *rhs) const {
		return !(*this == *rhs);
	}


	uint64_t write(OutputStream *outStream);
private:

	/**
	 * Row part of key
	 */
	char *row;
	uint32_t rowMaxSize;
	uint32_t rowLength;

	/**
	 * Column family
	 */
	uint32_t columnFamilyLength;
	char *colFamily;
	uint32_t columnFamilySize;

	/**
	 * Column qualifier.
	 */
	char *colQualifier;
	uint32_t colQualSize;
	uint32_t colQualLen;
	char *keyVisibility;
	uint32_t colVisSize;
	uint64_t timestamp;
	bool deleted;

	/**
	 * copied from writable comparable utils
	 */
	static int compareBytes(const char *b1, int s1, int l1, const char *b2,
			int s2, int l2) {
		int end1 = s1 + l1;
		int end2 = s2 + l2;
		for (int i = s1, j = s2; i < end1 && j < end2; i++, j++) {
			int a = (b1[i] & 0xff);
			int b = (b2[j] & 0xff);
			if (a != b) {
				return a - b;
			}
		}
		return l1 - l2;
	}
};
} /* namespace data */
}/* namespace cclient */




#endif

