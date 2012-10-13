/*
 * TabletLocationObtainer.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

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
