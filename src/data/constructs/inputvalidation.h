/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cstring>
using namespace std;


template <typename T>
class has_size
{
    typedef char one;
    typedef long two;

    template <typename C> static one test( decltype(&C::size) ) ;
    template <typename C> static two test(...);


public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};



template <typename T>
static auto IsEmpty(T *t) -> typename std::enable_if<has_size<T>::value ==1, bool>::type {
  return (NULL == t || t->size() == 0);
}

template <typename T>
static auto IsEmpty(T *t) -> typename std::enable_if<not has_size<T>::value , bool>::type {
  return (NULL == t );
}


static auto IsEmpty(char *t)->  decltype(NULL !=t, bool()){
  return (NULL == t  || strlen(t) == 0);
}

template <typename... T>
bool
IsEmpty() {
  
  return false;
}


static bool isValidPort(uint32_t port)
{
    if (port < 1024 || port >65535)
    {
      return false;
    }
    return true;
}

static vector<std::string> split(string str, char delim)
{

  std::stringstream test(str);
  std::string segment;
  std::vector<std::string> seglist;

  while(std::getline(test, segment, delim))
  {
      
    seglist.push_back(segment);
  }
  
  return seglist;
}


#endif // INPUTVALIDATION_H
