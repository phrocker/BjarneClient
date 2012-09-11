/*
 * ExtentLocator.h
 *
 *  Created on: Aug 26, 2012
 *      Author: marc
 */

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
