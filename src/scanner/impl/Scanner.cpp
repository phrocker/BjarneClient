/*
 * Scanner.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: marc
 */



#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#include "Scanner.h"

#include "../constructs/Results.h"
#include "../../data/constructs/client/Instance.h"
#include "../../data/constructs/security/AuthInfo.h"
#include "../../data/constructs/security/Authorizations.h"


namespace scanners {
namespace impl
{

using namespace cclient::data;
using namespace cclient::data::security;

/home/marc/BjarneClient/src
Scanner::Scanner(Instance *instance, AuthInfo *credentials, string table, Authorizations *authorizations) {
	// TODO Auto-generated constructor stub

}

Scanner::~Scanner() {
	// TODO Auto-generated destructor stub
}

Results *Scanner::getResultSet(uint32_t maxSize)
{
	return NULL;

}

}
} /* namespace scanners */
