#include <iostream>

#include "RunUnit.h"

#include "TestKey.h"
#include "TestKeyValue.h"

using namespace std;


using namespace cclient::test;


int main()
{
	ADD_UNIT( TestKey() );
	ADD_UNIT( TestKeyValue() );

	RUN_TESTS


}
