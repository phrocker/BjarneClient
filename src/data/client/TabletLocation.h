/*
 * TabletLocation.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

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
	virtual ~TabletLocation();
protected:
	KeyExtent *tablet_extent;
	string tablet_location;
};

} /* namespace data */
} /* namespace cclient */
#endif /* TABLETLOCATION_H_ */
