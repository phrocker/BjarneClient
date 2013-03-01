/*
 * Authorizations.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: marc
 */

#include "Authorizations.h"

using namespace cclient::data::security;
#include <iostream>

#include <string>
#include <set>

using namespace std;



void Authorizations::addAuthorization(string auth)
{
	authStrings.insert( auth );
}


Authorizations::~Authorizations()
{

}
