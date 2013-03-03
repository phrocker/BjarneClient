 
#ifndef INTERCONNECT_H_
#define INTERCONNECT_H_

#include "../data/exceptions/ClientException.h"
#include "../data/exceptions/IllegalArgumentException.h"

using namespace cclient::exceptions;

namespace interconnect{
  
struct Cmp_ServerConnection {
  bool operator()(const ServerConnection& first,const  ServerConnection& second) {
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
    ServerConnection(String loc, uint16_t port, uint64_t timeout) : host(loc), port(port), timeout(timeout)
    {
	if (IsEmpty(loc))
	{
	    throw IllegalArgumentException("Invalid Input; host name is empty");
	}
	
	
    }
    
    bool operator==(ServerConnection &rhs) const{
      
	return host == rhs.host && port == rhs.port && timeout == rhs.timeout;
    }
    
protected:
    string host;
    uint16_t port;
    uint64_t timeout;
};
}
#endif
