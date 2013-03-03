/*
 * MetaDataLocationObtainer.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef METADATALOCATIONOBTAINER_H_
#define METADATALOCATIONOBTAINER_H_

#include <set>
#include <vector>
using namespace std;
#include "../../TabletLocationObtainer.h"

#include "../../../constructs/client/Instance.h"
#include "../../../constructs/security/AuthInfo.h"
namespace cclient {
namespace impl {

using namespace cclient::data;
using namespace cclient::data::security;


class MetaDataLocationObtainer : TabletLocationObtainer{

public:
	MetaDataLocationObtainer(AuthInfo *credentials,Instance *instance ) : creds(credentials), instance(instance)
	{

	}
	virtual ~MetaDataLocationObtainer();
protected:
      
	Instance *instance;
	AuthInfo* creds;
};

} /* namespace impl */
} /* namespace cclient */
#endif /* METADATALOCATIONOBTAINER_H_ */

