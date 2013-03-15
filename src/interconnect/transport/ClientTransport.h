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

#ifndef CLIENTRANSPORT_H_
#define CLIENTTRANSPORT_H_

#include "Transport.h"
#include "ServerConnection.h"

namespace interconnect
{

template<typename T>
class ClientTransport: public Transporter<T>
{
public:
	Scan *beginScan(ServerConnection *conn)
	{
		return NULL;
	}
};

} /* namespace interconnect */
#endif /* SERVERTRANSPORT_H_ */
