/*
 * ZookeeperInstance.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef ZOOKEEPERINSTANCE_H_
#define ZOOKEEPERINSTANCE_H_

#include "../Instance.h"

namespace cclient {
namespace data {

class ZookeeperInstance : public Instance {
public:
	virtual string getZookeepers() = 0;
	virtual int getSessionTimeout() = 0;
	virtual ~ZookeeperInstance();
};

} /* namespace impl */
} /* namespace cclient */
#endif /* ZOOKEEPERINSTANCE_H_ */
