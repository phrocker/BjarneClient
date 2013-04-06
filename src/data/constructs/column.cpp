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

#include <string>
using namespace std;

#include "inputvalidation.h"


#include "column.h"


namespace cclient {
namespace data {


Column::Column(string *columFam, string *columnQual, string *columnVis) {
	if (!IsEmpty(columFam)) {
		columnFamily = new char[columFam->size() + 1];
		memcpy(columnFamily, columFam->c_str(), columFam->size());
		columnFamilyLen = columFam->size();
	} else
	{
		columnFamily = new char[0];
		columnFamilyLen = 0;
	}

	if (!IsEmpty(columnQual)) {
		columnQualifier = new char[columnQual->size() + 1];
		memcpy(columnQualifier, columnQual->c_str(), columnQual->size());
		columnQualifierLen = columFam->size();
	} else
	{
		columnQualifier = new char[0];
		columnQualifierLen = 0;
	}

	if (!IsEmpty(columnVis)) {
		columnVisibility = new char[columnVis->size() + 1];
		memcpy(columnVisibility, columnVis->c_str(), columnVis->size());
	} else
		columnVisibility = new char[0];
}


void Column::setColFamily(const char *r, uint32_t size) {

	if (columnFamilyLen > 0) {
		delete[] columnFamily;
		columnFamily = new char[size];
		columnFamilyLen = size;
	}

	memcpy(columnFamily, r, size);
	columnFamilyLen = size;

}

void Column::setColQualifier(const char *r, uint32_t size) {
	if (columnQualifierLen > 0) {
		delete[] columnQualifier;
		columnQualifier = new char[size];
		columnQualifierLen = size;
	}

	memcpy(columnQualifier, r, size);
	columnQualifierLen = size;

}

void Column::setColVisibility(const char *r, uint32_t size) {
		if (columnVisibilityLen > 0) {
			delete[] columnVisibility;
			columnVisibility = new char[size];
			columnVisibilityLen = size;
		}

		memcpy(columnVisibility, r, size);
		columnVisibilityLen = size;

	}

Column::~Column() {
	delete[] columnFamily;
	delete[] columnQualifier;
	delete[] columnVisibility;
}

Column& Column::operator=(const Column& other) {
	return *this;
}

bool Column::operator <(const Column &rhs) const {

	int compare = compareBytes(columnFamily, 0, columnFamilyLen,
			rhs.columnFamily, 0, rhs.columnFamilyLen);

	if (compare < 0)
		return true;
	else if (compare > 0)
		return false;;

	compare = compareBytes(columnQualifier, 0, columnQualifierLen,
			rhs.columnQualifier, 0, rhs.columnQualifierLen);

	if (compare < 0)
		return true;
	else if (compare > 0)
		return false;

	compare = compareBytes(columnVisibility, 0, columnVisibilityLen,
			rhs.columnVisibility, 0, rhs.columnVisibilityLen);

	if (compare < 0)
		return true;

	return false;

}

bool Column::operator ==(const Column & rhs) const {
	int compare = compareBytes(columnFamily, 0, columnFamilyLen,
			rhs.columnFamily, 0, rhs.columnFamilyLen);

	if (compare != 0)
		return false;

	compare = compareBytes(columnQualifier, 0, columnQualifierLen,
			rhs.columnQualifier, 0, rhs.columnQualifierLen);

	if (compare != 0)
		return false;

	compare = compareBytes(columnVisibility, 0, columnVisibilityLen,
			rhs.columnVisibility, 0, rhs.columnVisibilityLen);

	if (compare != 0)
		return false;
	else
		return true;

}

uint64_t Column::write(OutputStream *outStream) {

	if (IsEmpty(columnFamily)) {
		outStream->writeBoolean(false);
	} else {
		outStream->writeBoolean(true);
		outStream->writeBytes(columnFamily, columnFamilyLen);
	}

	if (IsEmpty(columnQualifier)) {
		outStream->writeBoolean(false);
	} else {
		outStream->writeBoolean(true);
		outStream->writeBytes(columnQualifier, columnQualifierLen);
	}

	if (IsEmpty(columnVisibility)) {
		return outStream->writeBoolean(false);
	} else {
		outStream->writeBoolean(true);
		return outStream->writeBytes(columnVisibility, columnVisibilityLen);
	}

}

}
}
