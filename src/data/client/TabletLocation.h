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

#ifndef TABLETLOCATION_H_
#define TABLETLOCATION_H_

#include <string>
#include <iostream>
#include <map>
using namespace std;
#include "../constructs/KeyExtent.h"


namespace cclient {
namespace data {

class TabletLocation {
public:
	TabletLocation();
	TabletLocation(KeyExtent *extent, string loc) : tablet_extent(extent), tablet_location(loc)
	{

	}

	constexpr KeyExtent *getExtent()
	{
		return tablet_extent;
	}

	constexpr string getLocation()
	{
		return tablet_location;
	}

	virtual ~TabletLocation();
protected:
	KeyExtent *tablet_extent;
	string tablet_location;
};

} /* namespace data */
} /* namespace cclient */
#endif /* TABLETLOCATION_H_ */
