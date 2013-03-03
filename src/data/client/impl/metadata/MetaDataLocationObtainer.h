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

#include "../../../constructs/column.h"
#include "../../../constructs/StructureDefinitions.h"
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
	  locationColumns = new set<Column*>();
	  locationColumns->insert( new Column(&METADATA_CURRENT_LOCATION_COLUMN_FAMILY));
	  locationColumns->insert( new Column(&METADATA_TABLET_COLUMN_FAMILY,&METADATA_PREV_ROW_COLUMN_CQ));
	  columns = new vector<Column*>();
	  
	}
	virtual ~MetaDataLocationObtainer();
protected:
	set<Column*> *locationColumns;
	vector<Column*> *columns;
	Instance *instance;
	AuthInfo* creds;
};

} /* namespace impl */
} /* namespace cclient */
#endif /* METADATALOCATIONOBTAINER_H_ */

