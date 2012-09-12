/*
 * TabletServerLocator.h
 *
 *  Created on: Sep 11, 2012
 *      Author: marc
 */

#ifndef TABLETSERVERLOCATOR_H_
#define TABLETSERVERLOCATOR_H_

#include "../ExtentLocator.h"

namespace cclient {
namespace impl {

class TabletServerLocator : TabletLocator{
public:
	TabletServerLocator(string tableId, TabletLocator *parent, TabletLocationObtainer *locator);
	virtual ~TabletServerLocator();

protected:
	string lastTabletRow;
	string tableId;
	TabletLocator *parent;
	TabletLocationObtainer *locator;
};

} /* namespace data */
} /* namespace cclient */
#endif /* TABLETSERVERLOCATOR_H_ */
