/*
 * Scanner.h
 *
 *  Created on: Dec 9, 2012
 *      Author: marc
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#include "../Scanner.h"

#include "../constructs/Results.h"
#include "../../data/constructs/client/Instance.h"
#include "../../data/constructs/security/AuthInfo.h"
#include "../../data/constructs/security/Authorizations.h"

namespace scanners {
namespace impl
{

using namespace cclient::data;
using namespace cclient::data::security;

class Scanner : scanners::ScannerBase{
public:
	Scanner(Instance *instance, AuthInfo *credentials, string table, Authorizations *authorizations);
	Results * getResultSet(uint32_t maxSize);
	virtual ~Scanner();
};
} /* namespace impl */
} /* namespace scanners */
#endif /* SCANNER_H_ */
