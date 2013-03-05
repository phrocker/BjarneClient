/**
  * Hello, this is BjarneClient, a free and open implementation of Accumulo
  * and big table. This is meant to be the client that accesses Accumulo
  * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
  * 2013 -- Marc Delta Poppa @ accumulo.net
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.

  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  **/

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

