/*
 * Range.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#ifndef RANGE_H_
#define RANGE_H_

#include "../exceptions/IllegalArgumentException.h"
#include "Key.h"
namespace cclient {
namespace data {

using namespace cclient::exceptions;
class Range {
public:
	Range();

	Range(Key *startKey, bool startInclusive, Key *endKey, bool endKeyInclusive) :
			start(startKey), startKeyInclusive(startInclusive), stop(endKey), stopKeyInclusive(
					endKeyInclusive) {
		infiniteStartKey = startKey == NULL;
		infiniteStopKey = stop == NULL;

		if (!infiniteStartKey && !infiniteStopKey && (stop < start))
		{
			throw new IllegalArgumentException("Start key must be less than end key in range");
		}
	}
	
	Key *getStartKey()
	{
	    return start;
	}

	virtual ~Range();
protected:
	Key *start;
	Key *stop;
	bool startKeyInclusive;
	bool stopKeyInclusive;
	bool infiniteStartKey;
	bool infiniteStopKey;
};

} /* namespace data */
} /* namespace cclient */
#endif /* RANGE_H_ */
