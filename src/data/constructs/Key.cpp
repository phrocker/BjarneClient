/*
 * Key.cpp
 *
 *  Created on: Sep 11, 2012
 *      Author: marc
 */

#include "Key.h"

namespace cclient {
namespace data {

Key::Key() :
		deleted(false), timestamp((uint64_t) -1), colVisSize(0), rowMaxSize(0), columnFamilySize(
				0), colQualSize(0), rowLength(0), columnFamilyLength(0), colQualLen(
				0) {

	row = new char[0];

	colFamily = new char[0];

	colQualifier = new char[0];

	keyVisibility = new char[0];

}

Key::~Key() {

	delete[] row;
	delete[] colFamily;
	delete[] colQualifier;
	delete[] keyVisibility;

}

void Key::setRow(const char *r, uint32_t size) {
	if (size > rowMaxSize) {
		delete[] row;
		row = new char[size];
		rowMaxSize = size;
	}

	memcpy(row, r, size);
	rowLength = size;

}

void Key::setColFamily(const char *r, uint32_t size) {

	if (size > columnFamilySize) {
		delete[] colFamily;
		colFamily = new char[size];
		columnFamilySize = size;
	}

	memcpy(colFamily, r, size);
	columnFamilyLength = size;

}

void Key::setColQualifier(const char *r, uint32_t size, uint32_t offset) {
	if (offset + size > colQualSize) {
		char *nr = new char[size + offset];
		memcpy(nr, colQualifier, colQualSize);
		delete[] colQualifier;
		colQualifier = nr;
		colQualSize = size + offset;
	}

	memcpy(colQualifier + offset, r, size);
	colQualLen = size + offset;

}

void Key::setColVisibility(const char *r, uint32_t size) {
		if (size > colVisSize) {
			delete[] keyVisibility;
			keyVisibility = new char[size];
			colVisSize = size;
		}

		memcpy(keyVisibility, r, size);

	}

bool Key::operator <(const Key &rhs) const {
		int compare = compareBytes(row, 0, rowMaxSize, rhs.row, 0,
				rhs.rowMaxSize);

		if (compare < 0)
			return true;
		else if (compare > 0)
			return false;

		compare = compareBytes(colFamily, 0, columnFamilySize, rhs.colFamily, 0,
				rhs.columnFamilySize);

		if (compare < 0)
			return true;
		else if (compare > 0)
			return false;

		compare = compareBytes(colQualifier, 0, colQualSize, rhs.colQualifier,
				0, rhs.colQualSize);

		if (compare < 0)
			return true;

		return false;
	}

bool Key::operator ==(const Key & rhs) const {
		int compare = compareBytes(row, 0, rowMaxSize, rhs.row, 0,
				rhs.rowMaxSize);

		if (compare != 0)
			return false;

		compare = compareBytes(colFamily, 0, columnFamilySize, rhs.colFamily, 0,
				rhs.columnFamilySize);

		if (compare != 0)
			return false;

		compare = compareBytes(colQualifier, 0, colQualSize, rhs.colQualifier,
				0, rhs.colQualSize);

		if (compare != 0)
			return false;

		return (timestamp < rhs.timestamp);

	}

uint64_t Key::write(OutputStream *outStream) {

		uint32_t offset = rowMaxSize;

		HadoopStream::writeHadoopLong(outStream, offset);
		//outStream->writeHadoopLong( offset ); // cf offset

		offset += columnFamilySize;
		HadoopStream::writeHadoopLong(outStream, offset);
		//outStream->writeHadoopLong( offset ); // cq offset

		offset += colQualSize;
		HadoopStream::writeHadoopLong(outStream, offset);
		//outStream->writeHadoopLong( offset ); // colvis offset

		offset += colVisSize;
		HadoopStream::writeHadoopLong(outStream, offset);
		//outStream->writeHadoopLong( offset ); // total

		outStream->writeBytes(row, rowMaxSize);
		outStream->writeBytes(colFamily, columnFamilySize);
		outStream->writeBytes(colQualifier, colQualSize);
		outStream->writeBytes(keyVisibility, colVisSize);
		HadoopStream::writeHadoopLong(outStream, timestamp);
		//outStream->writeHadoopLong( timestamp);

		return outStream->writeBoolean(deleted);

	}
} /* namespace data */
} /* namespace cclient */
