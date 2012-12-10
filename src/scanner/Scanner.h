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
#include "../constructs/Results.h"


namespace scanners
{

class ScannerBase{
public:
	ScannerBase();
	virtual Results * getResultSet(uint32_t maxSize) = 0;
	virtual ~ScannerBase();
};
}
#endif /* SCANNER_H_ */
