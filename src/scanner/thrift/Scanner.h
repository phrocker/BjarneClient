/*
 * Scanner.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

#include "../../data/constructs/security/AuthInfo.h"
#include "../../data/constructs/KeyExtent.h"
#include "../../data/constructs/Range.h"

namespace cclient {
namespace thrift{


class Scanner {
public:
	Scanner();

	/*
	static bool getBatchFromServer(
			AuthInfo *credentials,
			Range *range,
			KeyExtent *extent,
			string server,
			map<Key,Value> results,
			set<string> fetchedColumns, int size, */
	virtual ~Scanner();
};

} /* namespace thrift */
} /* namespace cclient */
#endif /* SCANNER_H_ */
