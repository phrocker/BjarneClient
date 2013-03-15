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

#ifndef SERVERCONNECTION_H_
#define SERVERCONNECTION_H_

#include "../../data/constructs/inputvalidation.h"

namespace interconnect
{
struct Cmp_ServerConnection
{
	bool operator()(const ServerConnection& first,
			const ServerConnection& second)
	{
		bool less = first.host < second.host;
		if (less)
			return true;
		else
		{
			if (first.host > second.host)
				return false;
			else
			{
				less = first.port < second.port;
				if (less)
					return true;
				else
				{
					if (first.port > second.port)
						return false;
					else
					{
						return first.timeout < second.timeout;
					}
				}
			}
		}
	}
};

class ServerConnection
{
public:
	ServerConnection(string loc, uint16_t port, uint64_t timeout) :
			host(loc), port(port), timeout(timeout)
	{
		if (IsEmpty(&loc))
		{
			throw IllegalArgumentException("Invalid Input; host name is empty");
		}

	}

	bool operator==(ServerConnection &rhs) const
	{

		return host == rhs.host && port == rhs.port && timeout == rhs.timeout;
	}

	string getHost()
	{
		return host;
	}

	uint16_t getPort()
	{
		return port;
	}

	uint64_t getTimeout()
	{
		return timeout;
	}

	ServerConnection &operator=(const ServerConnection &rhs)
	{

		host = rhs.host;
		port = rhs.port;
		timeout = rhs.timeout;
		return *this;
	}

protected:
	string host;
	uint16_t port;
	uint64_t timeout;
};
}
#endif /* SERVERCONNECTION_H_ */
