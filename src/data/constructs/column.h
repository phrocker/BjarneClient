/*
 <one line to give the program's name and a brief idea of what it does.>
 Copyright (C) 2013  <copyright holder> <email>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COLUMN_H
#define COLUMN_H

#include "../streaming/stream_ifc.h"
#include "../streaming/hadoop_stream.h"

#include <stdint.h>

#include <stdio.h>
#include <string.h>

namespace cclient
{
namespace data
{

using namespace cclient::data::streams;

class Column: public StreamInterface
{

public:
	Column(){

	}
	Column(string *columFam, string *columnQual, string *columnVis);
	Column(const Column& other)
	{

	}
	virtual ~Column();
	virtual Column& operator=(const Column& other);
	virtual bool operator==(const Column& other) const;
	bool operator <(const Column &rhs) const;

	bool operator <(const Column *rhs) const
	{
		return *this < *rhs;
	}
	uint64_t write(OutputStream *outStream);

private:

	char *columnFamily;
	uint16_t columnFamilyLen;

	char *columnQualifier;
	uint16_t columnQualifierLen;

	char *columnVisibility;
	uint16_t columnVisibilityLen;

	void setColFamily(const char *r, uint32_t size);

	std::pair<char*, size_t> getColFamily()
	{
		return std::make_pair(columnFamily, columnFamilyLength);
	}

	void setColQualifier(const char *r, uint32_t size);

	std::pair<char*, size_t> getColQualifier()
	{
		return std::make_pair(columnQualifier, colQualLen);
	}

	void setColVisibility(const char *r, uint32_t size);

	std::pair<char*, size_t> getColVisibility()
	{
		return std::make_pair(columnVisibility, columnVisibilityLen);
	}

	/**
	 * copied from writable comparable utils
	 */
	static int compareBytes(const char *b1, int s1, int l1, const char *b2,
			int s2, int l2)
	{
		int end1 = s1 + l1;
		int end2 = s2 + l2;
		for (int i = s1, j = s2; i < end1 && j < end2; i++, j++)
		{
			int a = (b1[i] & 0xff);
			int b = (b2[j] & 0xff);
			if (a != b)
			{
				return a - b;
			}
		}
		return l1 - l2;
	}
};

#endif // COLUMN_H
