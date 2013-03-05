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

#ifndef SERVERDEFINITION_H_
#define SERVERDEFINITION_H_

#include "../security/AuthInfo.h"
#include "../security/Authorizations.h"
namespace cclient
{

namespace data
{
namespace tserver
{

	using namespace cclient::data::security;



class ServerDefinition
{
public:
	ServerDefinition(AuthInfo *creds, Authorizations *auths, string host, uint32_t port): credentials(creds), auths(auths), server(host), port(port)
	{

	}
	// default to a port

	virtual ~ServerDefinition();


	constexpr AuthInfo *getCredentials()
	{
		return credentials;
	}

	constexpr Authorizations *getAuthorizations()
	{
		return credentials;
	}

	constexpr string getServer()
	{
		return server;
	}

	constexpr uint32_t getPort()
	{
		return port;
	}


protected:
	AuthInfo *credentials;
	Authorizations *auths;
	string server;
	uint32_t port;

};
}
}
}
#endif /* SERVERDEFINITION_H_ */
