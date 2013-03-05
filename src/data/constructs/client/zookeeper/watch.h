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

#ifndef WATCH_H
#define WATCH_H


#include <iostream>
#include <string>
#include <zookeeper/zookeeper.hh>
#include <set>
using namespace org::apache::zookeeper;
using namespace org::apache::zookeeper::proto;
using namespace std;

class ZooWatch : public Watch
{
public:
  ZooWatch()
  {
      watchers = new set<Watch*>();
  }
  void process	(WatchEvent::type event,SessionState::type state,const std::string & path)	
  {
      set<Watch*> myWatches = new set<Watch*>( watchers );
      
      for( set<Watch*>::iterator it = myWatches.begin(); it != myWatches.end(); it++)
      {
	(*it)->process( event, state, path );
      }
      
      delete myWatches;
      
  }
protected:
    set<Watch*> watchers;
};

#endif // WATCH_H
