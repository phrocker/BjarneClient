/*
 * KeyValue.cpp
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

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
