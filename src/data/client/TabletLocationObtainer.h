/*
 * TabletLocationObtainer.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#ifndef TABLETLOCATIONOBTAINER_H_
#define TABLETLOCATIONOBTAINER_H_

#include "ExtentLocator.h"
namespace cclient {
namespace impl {

class TabletLocationObtainer : public TabletLocator{
public:
	TabletLocationObtainer();
	virtual ~TabletLocationObtainer();

};

} /* namespace data */
} /* namespace cclient */
#endif /* TABLETLOCATIONOBTAINER_H_ */
