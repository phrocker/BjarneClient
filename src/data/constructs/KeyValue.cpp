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

#include "KeyValue.h"

namespace cclient {
namespace data {

KeyValue::KeyValue() :
		key((StreamInterface*) new RelativeKey()), my_alloc(true) {

}

KeyValue::~KeyValue() {
	if (my_alloc)
		delete key;
}

void KeyValue::setKey(StreamInterface *k) {
	if (my_alloc)
		delete key;
	key = k;
}

StreamInterface *KeyValue::getKey() {
	return key;
}

StreamInterface *KeyValue::getStream() {
	return key->getStream();
}

Value *KeyValue::getValue() {
	return &value;
}

void KeyValue::setValue(Value *v) {
	v->deepCopy(&value);
}

void KeyValue::setValue(uint8_t *b, size_t size) {
	value.setValue(b, size);
}

uint64_t KeyValue::write(OutputStream *outStream) {

	key->write(outStream);

	return value.write(outStream);
}

KeyValue &KeyValue::operator=(const KeyValue &other) {

	key = other.key;

	std::pair<uint8_t*, uint32_t> p = other.value.getValue();

	value.setValue(p.first, p.second);
	return *this;
}

bool KeyValue::operator <(const KeyValue &rhs) const {
	return (*(Key*) key->getStream() < *(Key*) (rhs.key->getStream()));
}

bool KeyValue::operator <(const KeyValue *rhs) const {
	return *this < *rhs;

}

bool KeyValue::operator ==(const KeyValue & rhs) const {
	return ((Key*) key->getStream() == (Key*) (rhs.key->getStream()))
			&& (value == rhs.value);
}
bool KeyValue::operator !=(const KeyValue &rhs) const {
	return !(*this == rhs);
}

bool KeyValue::operator ==(const KeyValue *rhs) const {
	return *this == *rhs;
}
bool KeyValue::operator !=(const KeyValue *rhs) const {
	return !(*this == *rhs);
}

} /* namespace data */
} /* namespace cclient */
