#include "rkey.h"
using namespace cclient::data;
using namespace cclient::data::streams;

RelativeKey::RelativeKey() :
		fieldsSame(0) {

}

RelativeKey::RelativeKey(Key *previous_key, Key *my_key) :
		fieldsSame(0) {
	if (my_key == NULL)
		throw std::runtime_error("Key must not be null");

	setKey(my_key, &key);

	if (previous_key != NULL) {
		setKey(previous_key, &prevKey);

		if (isSame(prevKey.getRow(), key.getRow())) {

			fieldsSame |= ROW_SAME;
		}

		if (isSame(prevKey.getColQualifier(), key.getColQualifier())) {

			fieldsSame |= CQ_SAME;
		}

		if (isSame(prevKey.getColFamily(), key.getColFamily())) {

			fieldsSame |= CF_SAME;
		}

		if (isSame(prevKey.getColVisibility(), key.getColVisibility())) {

			fieldsSame |= CV_SAME;
		}

		if (prevKey.getTimeStamp() == key.getTimeStamp()) {

			fieldsSame |= TS_SAME;
		}
	}

	if (key.isDeleted())
		fieldsSame |= DELETED;

}

StreamInterface *RelativeKey::getStream() {
	return &key;
}

void RelativeKey::setBase(Key *my_key) {
	if (my_key != NULL)
		setKey(my_key, &key);
}

void RelativeKey::setPrevious(Key *previous_key) {
	if (previous_key != NULL)
		setKey(previous_key, &prevKey);
}

uint64_t RelativeKey::write(OutputStream *outStream) {
	outStream->writeByte(fieldsSame);

	std::pair<char*, size_t> p;
	if (!(fieldsSame & ROW_SAME)) {

		p = key.getRow();
		//outStream->writeVLong(p.second);
		HadoopStream::writeHadoopLong(outStream, p.second);
		outStream->writeBytes(p.first, p.second);
	}

	if (!(fieldsSame & CF_SAME)) {

		p = key.getColFamily();
		HadoopStream::writeHadoopLong(outStream, p.second);
		outStream->writeBytes(p.first, p.second);
	}

	if (!(fieldsSame & CQ_SAME)) {

		p = key.getColQualifier();
		HadoopStream::writeHadoopLong(outStream, p.second);
		outStream->writeBytes(p.first, p.second);
	}

	if (!(fieldsSame & CV_SAME)) {

		p = key.getColVisibility();
		HadoopStream::writeHadoopLong(outStream, p.second);
		outStream->writeBytes(p.first, p.second);
	}

	if (!(fieldsSame & TS_SAME)) {

		HadoopStream::writeHadoopLong(outStream, key.getTimeStamp());
	}

}

bool RelativeKey::operator <(const RelativeKey &rhs) const {
	return key < rhs.key;
}

bool RelativeKey::operator <(const RelativeKey *rhs) const {
	return *this < *rhs;

}

RelativeKey::~RelativeKey() {
}

void RelativeKey::setKey(Key *keyToCopy, Key *keyToCopyTo) {
	std::pair<char*, size_t> p = keyToCopy->getRow();
	keyToCopyTo->setRow(p.first, p.second);

	p = keyToCopy->getColFamily();
	keyToCopyTo->setColFamily(p.first, p.second);
	p = keyToCopy->getColQualifier();
	keyToCopyTo->setColQualifier(p.first, p.second);
	p = keyToCopy->getColVisibility();
	keyToCopyTo->setColVisibility(p.first, p.second);
	keyToCopyTo->setTimeStamp(keyToCopy->getTimeStamp());

}

bool RelativeKey::isSame(std::pair<char*, size_t> a,
		std::pair<char*, size_t> b) {
	if (a.second > 0 && a.second == b.second) {
		return (memcmp(a.first, b.first, a.second) == 0);
	} else
		return false;
}
