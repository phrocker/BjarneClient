/*
 * TabletServerLocator.cpp
 *
 *  Created on: Sep 11, 2012
 *      Author: marc
 */

#include "TabletServerLocator.h"

namespace cclient {
namespace impl {

TabletServerLocator::TabletServerLocator(string tableId, TabletLocator *parent, TabletLocationObtainer *locator) : tableId(tableId), parent(parent), locator(locator)
{
	// TODO Auto-generated constructor stub

}

TabletServerLocator::~TabletServerLocator() {
	// TODO Auto-generated destructor stub
}

} /* namespace data */
} /* namespace cclient */
