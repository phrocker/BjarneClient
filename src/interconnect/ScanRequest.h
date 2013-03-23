/**
 * Hello, this is BjarneClient, a free and open implementation of Accumulo 
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

#ifndef SCANREQUEST_H_
#define SCANREQUEST_H_

#include "../data/constructs/IterInfo.h"
#include "../data/constructs/column.h"

#include "../data/constructs/security/AuthInfo.h"
#include "../data/constructs/security/Authorizations.h"

namespace interconnect
{
using namespace cclient::data;
using namespace cclient::data::security;
/**
 * Represents a scan request
 */

class ScanRequest
{

	/*
	 * void startMultiScan(accumulo::data::InitialMultiScan& _return,
	 const accumulo::cloudtrace::TInfo& tinfo,
	 const accumulo::security::AuthInfo& credentials,
	 const accumulo::data::ScanBatch& batch,
	 const std::vector<accumulo::data::TColumn> & columns,
	 const std::vector<accumulo::data::IterInfo> & ssiList,
	 const std::map<std::string,
	 std::map<std::string, std::string> > & ssio,
	 const std::vector<std::string> & authorizations,
	 const bool waitForWrites);
	 */

public:
	ScanRequest(AuthInfo *credentials, Authorizations *auths,
			ServerConnection *server) :
			creds(credentials), auths(auths), connection(server)
	{

	}

	virtual ~ScanRequest()
	{

	}

	virtual void setIters(vector<IterInfo*> *iters)
		{
		for (auto it = iters->begin(); it != iters->end(); it++)
				{
					iterators.push_back(*it);
				}
		}

	void addColumn(Column *col)
	{
		columns.push_back(col);
	}

	void addColumns(vector<Column*> *cols)
	{
		columns.insert(columns.end(), cols->begin(), cols->end());
	}

	constexpr vector<Column*> *getColumns()
	{
		return columns;
	}

	constexpr AuthInfo *getCredentials()
	{
		return creds;
	}

	constexpr Authorizations *getAuthorizations()
	{
		return auths;
	}

	constexpr auto *getIterators()
	{
		return &iterators;
	}

	void putRangeIdentifier(KeyExtent* extent, vector<Range*> ranges)
	{
		extentToRange[ extent ].insert( extentToRange[extent].end(), ranges.begin(), ranges.end());
	}

	constexpr map<KeyExtent*,vector<Range*> > *getRangeIdentifiers()
		{
		return &extentToRange;
		}


protected:

	map<KeyExtent*,vector<Range*> > extentToRange;
	AuthInfo *creds;
	Authorizations *auths;
	vector<IterInfo*> iterators;
	vector<Column*> columns;
	ServerConnection *connection;
};

} /* namespace interconnect */
#endif /* SCANREQUEST_H_ */
