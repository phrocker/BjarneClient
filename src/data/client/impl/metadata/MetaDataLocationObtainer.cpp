/*
 * MetaDataLocationObtainer.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

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
