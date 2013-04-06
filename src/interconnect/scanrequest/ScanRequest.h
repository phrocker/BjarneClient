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

#include <vector>
using namespace std;

#include "../../data/constructs/IterInfo.h"
#include "../../data/constructs/column.h"

#include "../../data/constructs/security/AuthInfo.h"
#include "../../data/constructs/security/Authorizations.h"
#include "../../data/constructs/inputvalidation.h"
#include "../../data/exceptions/IllegalArgumentException.h"
#include "../transport/ServerConnection.h"
#include "ScanIdentifier.h"

namespace interconnect
{
using namespace cclient::data;
using namespace cclient::exceptions;
using namespace cclient::data::security;
/**
 * Represents a scan request
 */

template<typename K, typename V>
class ScanRequest
{

public:
	ScanRequest(AuthInfo *credentials, Authorizations *auths,
			ServerConnection *server) :
			creds(credentials), auths(auths), connection(server)
	{

		if (IsEmpty(credentials) || IsEmpty(auths) || IsEmpty(server))
		{
			throw IllegalArgumentException(
					"credentials, authorizations, and server must not be empty");
		}

	}

	virtual ~ScanRequest()
	{

	}

	virtual void setIters(vector<IterInfo*> *iters)
	{
		iterators.insert(iterators.end(), iters->begin(), iters->end());
	}

	void addColumn(Column *col)
	{
		columns.push_back(col);
	}

	void addColumns(vector<Column*> *cols)
	{
		columns.insert(columns.end(), cols->begin(), cols->end());
	}

	vector<Column*> *getColumns() const
	{
		return columns;
	}

	AuthInfo *getCredentials() const
	{
		return creds;
	}

	Authorizations *getAuthorizations() const
	{
		return auths;
	}

	vector<IterInfo*> *getIterators() const
	{
		return &iterators;
	}

	void putIdentifier(ScanIdentifier<K,V> *ident)
	{
		identifiers.push_back(ident);
	}

	vector<ScanIdentifier<K,V>*> *getRangeIdentifiers() const
	{
		return &identifiers;
	}

protected:

	vector<ScanIdentifier<K,V>*> identifiers;
	AuthInfo *creds;
	Authorizations *auths;
	vector<IterInfo*> iterators;
	vector<Column*> columns;
	ServerConnection *connection;
};

} /* namespace interconnect */
#endif /* SCANREQUEST_H_ */
