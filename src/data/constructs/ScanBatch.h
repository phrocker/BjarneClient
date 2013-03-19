/**
 * Hello, this is BjarneClient, a free and open implementation of Accumulo 
 * and big table. This is meant to be the client that accesses Accumulo 
 * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
 * 2013 -- BinaryStream LLC
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

#ifndef SCANBATCH_H_
#define SCANBATCH_H_

#include "KeyExtent.h"
#include "inputvalidation.h"
#include "../exceptions/IllegalArgumentException.h"
namespace cclient
{
namespace data
{
using namespace cclient::exceptions;

class ScanBatch
{
public:
	ScanBatch(KeyExtent *extent) :
			myExtent(extent)
	{
		if (IsEmpty(extent))
		{
			throw IllegalArgumentException("Extent is not allowed to be null");
		}
	}

	void addRange(Range *range)
	{
		ranges.insert(range);
	}


	virtual ~ScanBatch()
	{

	}
protected:
	KeyExtent *myExtent;
	set<Range*> ranges;
};

} /* namespace data */
} /* namespace cclient */
#endif /* SCANBATCH_H_ */
