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

#include "MetaDataLocationObtainer.h"
#include "../../../constructs/Range.h"
#include "../../../constructs/Key.h"
#include "../../../constructs/value.h"

namespace cclient {
namespace impl {
  
  using namespace cclient::data;

MetaDataLocationObtainer::~MetaDataLocationObtainer() {
      for(set<Column*>::iterator locIt = locationColumns->begin(); locIt != locationColumns->end(); locIt++)
      {	
	  delete (*locIt);
	  
      }
      
      delete locationColumns;
      
      for(set<Column*>::iterator locIt = columns->begin(); locIt != columns->end(); locIt++)
      {	
	  delete (*locIt);
	  
      }
      
      delete columns;
}

list<TabletLocation> MetaDataLocationObtainer::findTablet(TabletLocation *source, string row, string stopRow,TabletLocator *parent)
{
  vector<TabletLocation> tabletLocations = new vector<TabletLocation>();
  
  Key startKey();
  startKey.setRow(row.c_str(),row.size());
  Key endKey();
  endKey.setRow(stopRow.c_str(),stopRow.size());
  Range *range = new Range(&startKey,true,&endKey,true);
  
  map<Key,Value> resultSet;
  
  
}

} /* namespace impl */
} /* namespace cclient */
