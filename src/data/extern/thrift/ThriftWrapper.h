/**
 d * Hello, this is BjarneClient, a free and open implementation of Accumulo
 * and big table. This is meant to be the client that accesses Accumulo 
 * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
 * 2013 -- BinaryStream LLC
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

#ifndef THRIFTWRAPPER_H_
#define THRIFTWRAPPER_H_

#include "../../constructs/security/AuthInfo.h"
#include "../../constructs/security/Authorizations.h"
#include "../../constructs/inputvalidation.h"
#include "../../constructs/IterInfo.h"
#include "../../constructs/column.h"
#include "data_types.h"
#include "security_types.h"
namespace interconnect
{

class ThriftWrapper
{
public:
	static accumulo::security::AuthInfo convert(
			cclient::data::security::AuthInfo *authInfo)
	{
		accumulo::security::AuthInfo stackAuthInfo;
		stackAuthInfo.instanceId = authInfo->getInstanceId();
		stackAuthInfo.user = authInfo->getUserName();
		stackAuthInfo.password = authInfo->getPassword();
		return stackAuthInfo;
	}

	static vector<accumulo::data::IterInfo> convert(
			vector<cclient::data::IterInfo*> *iters)
	{

		vector<accumulo::data::IterInfo> convertedIters;
		if (!IsEmpty(iters))
		{
			for (auto it = iters->begin(); it != iters->end(); it++)
			{
				accumulo::data::IterInfo iterInfo;
				iterInfo.className = (*it)->getClass();
				iterInfo.iterName = (*it)->getName();
				iterInfo.priority = (*it)->getPriority();
				convertedIters.push_back(iterInfo);
			}
		}

		return convertedIters;

	}
	/*
	 static accumulo::data::ScanBatch convert(
	 map<KeyExtent*,vector<Range*> > *rangeIdentifiers)
	 {
	 for(auto it : rangeIdentifiers->begin())
	 {
	 KeyExtent *extent = it->first;
	 vector<Range*> *ranges = &it->second();
	 TKeyExtent keyExtent;
	 keyExtent.table = extent->getTableId();
	 keyExtent.endRow = extent->getEndRow();
	 keyExtent.prevEndRow = extent->getPrevEndRow();
	 }
	 }
	 */
	static accumulo::data::TKey convert(Key *key)
	{
		accumulo::data::TKey newKey;
		/*
		 * std::string row;
		 std::string colFamily;
		 std::string colQualifier;
		 std::string colVisibility;
		 int64_t timestamp;
		 */
		std::pair<char*, size_t> cfPair = key->getColFamily();
		newKey.colFamily = string(cfPair.first, cfPair.second);

		std::pair<char*, size_t> cqPair = key->getColQualifier();
		newKey.colQualifier = string(cqPair.first, cqPair.second);

		std::pair<char*, size_t> cvPair = key->getColVisibility();
		newKey.colVisibility = string(cvPair.first, cvPair.second);

		newKey.timestamp = key->getTimeStamp();

		return newKey;
	}

	static accumulo::data::TRange convert(Range *range)
	{
		accumulo::data::TRange newRange;
		newRange.start = convert(range->getStartKey());
		newRange.stop = convert(range->getStopKey());
		newRange.startKeyInclusive = range->getStartKeyInclusive();
		newRange.stopKeyInclusive = range->getStopKeyInclusive();
		newRange.infiniteStartKey = range->getInfiniteStartKey();
		newRange.infiniteStopKey = range->getInfiniteStopKey();
		return newRange;
	}

	static vector<accumulo::data::TColumn> convert(
			vector<cclient::data::Column*> *columns)
	{

		vector<accumulo::data::TColumn> convertedColumns;
		/*
		 if (!IsEmpty(iters))
		 {
		 for (auto it = iters->begin(); it != iters->end(); it++)
		 {
		 accumulo::data::TColumn column;
		 std::pair<char*, size_t> cf = (*it)->getColFamily();
		 column.columnFamily = string(cf.first, cf.second);
		 std::pair<char*, size_t> cq = (*it)->getColQualifier();
		 column.columnQualifier = string(cq.first, cq.second);
		 std::pair<char*, size_t> cv = (*it)->getColVisibility();
		 column.columnVisibility = string(cv.first, cv.second);
		 convertedColumns.push_back(column);
		 }
		 }*/

		return convertedColumns;

	}

	static vector<string> convert(Authorizations *auths)
	{

		return auths->getAuthorizations();

	}

protected:
	ThriftWrapper()
	{

	}
	virtual ~ThriftWrapper()
	{

	}
}
;

} /* namespace interconnect */
#endif /* THRIFTWRAPPER_H_ */

