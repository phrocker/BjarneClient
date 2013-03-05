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

#ifndef EXTENTLOCATOR_H_
#define EXTENTLOCATOR_H_

#include <string>
#include <map>
#include <vector>
#include <vector>
#include "../constructs/client/TabletServerMutations.h"
#include "../constructs/Mutation.h"
#include "../constructs/Range.h"
using namespace std;

#include "TabletLocation.h"
namespace cclient {
namespace impl {

using namespace cclient::data;

struct LocatorKey {
public:
	string instanceId;
	string tableName;
	bool operator==(const LocatorKey &key) {
		return instanceId == key.instanceId && tableName == key.tableName;
	}
};

class TabletLocator {
public:
	TabletLocator();
	virtual ~TabletLocator();

	virtual TabletLocation *locateTablet(string row, bool skipRow,
			bool retry) = 0;

	virtual void binMutations(vector<Mutation> mutations,
			map<string, TabletServerMutations> binnedMutations,
			vector<Mutation> failures) = 0;

	virtual vector<Range> binRanges(vector<Range> ranges,
			map<string, map<KeyExtent, vector<Range> > > binnedRanges) = 0;

	virtual void invalidateCache(KeyExtent failedExtent) = 0;

	virtual void invalidateCache() = 0;

	virtual void invalidateCache(vector<KeyExtent> keySet) = 0;

};

} /* namespace data */
} /* namespace cclient */
#endif /* EXTENTLOCATOR_H_ */
