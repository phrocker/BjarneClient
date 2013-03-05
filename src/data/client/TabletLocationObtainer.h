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

#ifndef TABLETLOCATIONOBTAINER_H_
#define TABLETLOCATIONOBTAINER_H_


#include <list>
#include <iostream>
#include <string>

using namespace std;

#include "../constructs/KeyExtent.h"
#include "../constructs/Range.h"
#include "ExtentLocator.h"
#include "TabletLocation.h"
namespace cclient {
namespace impl {

using namespace cclient::data;
class TabletLocationObtainer : public TabletLocator{
public:
	TabletLocationObtainer();

	virtual ~TabletLocationObtainer();

	virtual list<TabletLocation> findTablet(TabletLocation *source, string row, string stopRow,TabletLocator *parent) = 0;
	virtual list<TabletLocation> findTablet(string tabletserver, map<KeyExtent,list<Range> > *map,TabletLocator *parent) = 0;

};

} /* namespace data */
} /* namespace cclient */
#endif /* TABLETLOCATIONOBTAINER_H_ */
