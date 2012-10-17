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

using namespace std;



void Authorizations::addAuthorization(string auth)
{
	authStrings.push_back( auth );
}


Authorizations::~Authorizations()
{

}
