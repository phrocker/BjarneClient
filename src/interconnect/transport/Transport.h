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

#ifndef TRANSPORT_H_
#define TRANSPORT_H_



#include "ServerConnection.h"


namespace interconnect
{

template<typename T>
class Transporter
{
protected:
	virtual void newTransporter(ServerConnection *conn) = 0;
public:
	Transporter(ServerConnection *conn)
	{
		return newTransporter(conn);
	}

	virtual T getTransport() = 0;
	virtual void registerService(string instance, string clusterManagers) = 0;
	virtual bool open() = 0;
	virtual bool isOpen() = 0;
	virtual void close() = 0;

};

}

#endif /* TRANSPORT_H_ */
