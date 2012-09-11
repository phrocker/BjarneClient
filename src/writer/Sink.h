/*
 * Sink.h
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#ifndef SINK_H_
#define SINK_H_

#include "MutationCollector.h"

namespace cclient {
namespace writer {



class Sink {
public:
	Sink();

	virtual uint8_t write(MutationCollector &writer) = 0;

	virtual ~Sink();
};

} /* namespace data */
} /* namespace cclient */
#endif /* SINK_H_ */
