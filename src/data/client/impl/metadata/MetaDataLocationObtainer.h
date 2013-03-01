/*
 * MetaDataLocationObtainer.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef METADATALOCATIONOBTAINER_H_
#define METADATALOCATIONOBTAINER_H_

#include "../../TabletLocationObtainer.h"

#include "../../../constructs/security/AuthInfo.h"
namespace cclient {
namespace impl {

using namespace cclient::data;


class MetaDataLocationObtainer : TabletLocationObtainer{

public:
	MetaDataLocationObtainer(AuthInfo *credentials,Instance *instance ) : creds(credentials), instance(instance)
	{

	}
	virtual ~MetaDataLocationObtainer();
protected:
	ZookeeperInstance *instance;
	AuthInfo* creds;
};

} /* namespace impl */
} /* namespace cclient */
#endif /* METADATALOCATIONOBTAINER_H_ */

