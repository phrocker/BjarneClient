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

#ifndef RANGEDEFINITION_H_
#define RANGEDEFINITION_H_

#include "ServerDefinition.h"
namespace cclient
{

namespace data
{
namespace tserver
{

class RangeDefinition : public ServerDefinition
{
public:
	RangeDefinition(AuthInfo *creds, Authorizations *auths, string host, uint32_t port, vector<Range*> *keyRange, vector<KeyExtent*> *keyExt): ::ServerDefinition(creds,auths,host,port)
	{
		ranges.insert(keyRange->begin(),keyRange->end());
		extents.insert(keyExt->begin(),keyExt->end());

	}

	constexpr vector<Range*> *getRanges()
	{
		return &ranges;
	}

	virtual ~RangeDefinition();
protected:
	vector<Range*> ranges;
	vector<KeyExtent*> extents;
};
}
}
}
#endif /* RANGEDEFINITION_H_ */
