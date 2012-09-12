/*
 * testConstructs.cpp
 *
 *  Created on: Sep 11, 2012
 *      Author: marc
 */

#include <iostream>
using namespace std;
#include "rkey.h"
#include "KeyExtent.h"
#include "Key.h"
#include "Mutation.h"

using namespace cclient::data;

int main()
{

	Key key;
			key.setColFamily("cf",2);
			key.setColQualifier("cq",2,0);
			key.setRow("row",3);
			key.setTimeStamp(0);
			RelativeKey rKey(&key,&key);


	return 0;
}
