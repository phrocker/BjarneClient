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

#ifndef ZOOKEEPERS_H
#define ZOOKEEPERS_H

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <zookeeper/zookeeper.hh>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include <pthread.h>

using namespace org::apache::zookeeper::ZooKeeper;
using namespace std;
#include "watch.h"

#define  TIME_BETWEEN_CONNECT_CHECKS_MS  100
#define  TOTAL_CONNECT_TIME_WAIT_MS  10 * 1000

#define ZROOT "/accumulo"
#define ZINSTANCES "/instances"
#define ZMASTERS "/masters"
#define ZMASTER_LOCK "/masters/lock"
#define ZROOT_TABLET "/root_tablet"
#define ZROOT_TABLET_LOCATION "/root_tablet/location"
#define TSERVERS "/tservers"

namespace cclient{
namespace data{
  namespace zookeeper{

    
pthead_mutex_t syncBarrier = PTHREAD_MUTEX_INITIALIZER; 

    
class ZooSession
{
public:
    ZooSession(ZooKeeper *keeper,Watch *watcher)  : zooKeeper(keeper)
    {
    }
    
protected:
    ZooKeeper *zooKeeper;
};




class ZooKeepers
{
private:
    static map<string,ZooSession*> sessions = new map<string,ZooSession*>();
public:
  
  static string sessionKey(string keepers, uint16_t timeout, string auth)
  {
      stringstream ss (stringstream::in | stringstream::out);
      ss << keepers << ":" << timeout << ":" << (auth.size() > 0 ? auth : "");
      return ss.str();
  }
  
  static ZooKeeper *getSession(string zookeepers, uint16_t timeout, string auth)
  {
    pthread_mutex_lock(&syncBarrier);
    string sessionKey = sessionKey(zookeepers,timeout,auth);
    string readOnlyKey = sessionKey(zookeepers,timeout,"");
    
    
    map<string,ZooSession*>::iterator it = sessions.find( sessionKey );
    
    // it exists
    
    ZooSession *zsi = NULL;
    
    if (it != sessions.end() )
    {
	zsi = (*it);
	if (zsi->zooKeeper->getState() != SessionState::type::Connected)
	{
	   map<string,ZooSession*>::iterator pt;
	    if (( pt = sessions.find( readOnlyKey) ) == it)
	    {
		sessions.erase( pt );
	    }
	    sessions.erase( it );
	}
	
	
    }
    else
    {
      ZooWatch *watcher = new ZooWatch();
      
      zsi = new ZooSession( connect(zookeepers, timeout, auth, &watcher);
      
      sessions.insert(zsi );
    }
    
    
    pthread_mutex_unlock(&syncBarrier);
    
    return zsi;
  }
  
  static ZooKeeper *connect(string &hosts, uint32_t timeout, string auth, Watch *watcher)
  {
      bool tryAgain = true;
      uint16_t sleepTime = 100;
      ZooKeeper *zk = NULL;
      do
      {
	  boost::shared_ptr< Watch > watchers(watcher);
	  zk = new Zookeeper();
	  
	  ReturnCode::type ret = zk->init(hosts, timeout, watchers );
	  
	  switch(ret)
	  {
	    case ReturnCode::type::Ok:
	  
	    for (int i = 0; i < TOTAL_CONNECT_TIME_WAIT_MS / TIME_BETWEEN_CONNECT_CHECKS_MS && tryAgain; i++) {
	      
	      SessionState::type state = zk->getState();
	      
	      if ( state == SessionState::type::Connected )
	      {
		  if (auth.size() > 0)
		  {
		      ret = zk->addAuth("digest",auth);	
		      tryAgain = false;
		  }
		  else
		  {
		    // sleep
		    sleep(1);
		  }
	      }
	      break;
	    default:
	      break;
	      tryAgain = false;
	    }
	    //else if (ret == ReturnCode::type::
	      
	      
	  };
	      
	      
	  
	  
	  
      }while(tryAgain);
      
      return zk;
  }
};
  }
}
}
//const map<string,

#endif // ZOOKEEPERS_H
