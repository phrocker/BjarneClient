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



#ifndef AUTHINFO_H_
#define AUTHINFO_H_

#include <string>

using namespace std;
namespace cclient {
namespace data {
namespace security {

class AuthInfo {
public:
	AuthInfo(string user,
			 string password,
			 string instanceId);

	virtual ~AuthInfo();
	
	string getUserName() const
	{
	    return user;
	}
	
	string getPassword() const
	{
	    return password;
	}
	
	string getInstanceId() const
	{
	    return instanceId;
	}
	
protected:
	string user;
	string instanceId;
	string password;
};
}
} /* namespace data */
} /* namespace cclient */
#endif /* AUTHINFO_H_ */
