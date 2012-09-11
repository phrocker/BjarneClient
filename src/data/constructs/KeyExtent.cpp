/*
 * KeyExtent.cpp
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#include "KeyExtent.h"

namespace cclient {
namespace data {


KeyExtent::KeyExtent(string flattenedText, Value *prevEndRow) {
	decodeMetadataRow(flattenedText);

}

KeyExtent::~KeyExtent() {
	// TODO Auto-generated destructor stub
}

} /* namespace data */
} /* namespace cclient */
