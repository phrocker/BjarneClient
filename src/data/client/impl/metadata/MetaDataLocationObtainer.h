/*
 * MetaDataLocationObtainer.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef METADATALOCATIONOBTAINER_H_
#define METADATALOCATIONOBTAINER_H_

#include "../TabletLocationObtainer.h"

#include "../../../constructs/security/AuthInfo.h"
#include "../../../constructs/client/zookeeper/ZookeeperInstance.h"
namespace cclient {
namespace impl {

using namespace cclient::data;


class MetaDataLocationObtainer : TabletLocationObtainer{
protected:
	ZookeeperInstance *instance;
	AuthInfo *credentials:
public:
	MetaDataLocationObtainer(AuthInfo *credentials,ZookeeperInstance *instance ) : credentials(credentials), instance(instance)
	{

	}
	virtual ~MetaDataLocationObtainer();
};

} /* namespace impl */
} /* namespace cclient */
#endif /* METADATALOCATIONOBTAINER_H_ */

