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


#include "column.h"
#include "inputvalidation.h"

namespace cclient {
namespace data {
Column::Column()
{

}

Column::Column(const Column& other)
{

}

Column::~Column()
{
  delete [] columnFamily;
  delete [] columnQualifier;
  delete [] columnVisibility;
}

Column& Column::operator=(const Column& other)
{
return *this;
}

bool Column::operator <(const Column &rhs) const {
				
		int compare = compareBytes(columnFamily, 0, columnFamilyLen, rhs.columnFamily, 0,
				rhs.columnFamilyLen);

		if (compare < 0)
			return true;
		else if (compare > 0)
			return false;;

		compare = compareBytes(columnQualifier, 0, columnQualifierLen, rhs.columnQualifier, 0,
				rhs.columnQualifierLen);

		if (compare < 0)
			return true;
		else if (compare > 0)
			return false;

		compare = compareBytes(columnVisibility, 0, columnVisibilityLen, rhs.columnVisibility,
				0, rhs.columnVisibilityLen);

		if (compare < 0)
			return true;

		return false;
		
	}

bool Column::operator ==(const Column & rhs) const {
		int compare = compareBytes(columnFamily, 0, columnFamilyLen, rhs.columnFamily, 0,
				rhs.columnFamilyLen);

		if (compare != 0)
			return false;

		compare = compareBytes(columnQualifier, 0, columnQualifierLen, rhs.columnQualifier, 0,
				rhs.columnQualifierLen);

		if (compare != 0)
			return false;

		compare = compareBytes(columnVisibility, 0, columnVisibilityLen, rhs.columnVisibility,
				0, rhs.columnVisibilityLen);

		if (compare != 0)
			return false;
		else return true;

		

	}

uint64_t Column::write(OutputStream *outStream) {

		if (IsEmpty(columnFamily))
		{
		    outStream->writeBoolean(false);
		}
		else{
		  outStream->writeBoolean(true);
		  outStream->writeBytes(columnFamily,columnFamilyLen);
		}
		
		
		if (IsEmpty(columnQualifier))
		{
		    outStream->writeBoolean(false);
		}
		else{
		  outStream->writeBoolean(true);
		  outStream->writeBytes(columnQualifier,columnQualifierLen);
		}
		
		if (IsEmpty(columnVisibility))
		{
		    return outStream->writeBoolean(false);
		}
		else{
		    outStream->writeBoolean(true);
		    return outStream->writeBytes(columnVisibility,columnVisibilityLen);
		}
		

	}


}
}