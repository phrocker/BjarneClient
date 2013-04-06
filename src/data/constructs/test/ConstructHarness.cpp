#include <iostream>

#include "RunUnit.h"

#include "TestKey.h"
#include "TestAuthorizations.h"
#include "TestKeyValue.h"
#include "TestAuthInfo.h"
#include "TestColumn.h"

using namespace std;


using namespace cclient::test;


int main()
{
	ADD_UNIT( TestKey() );
	ADD_UNIT( TestKeyValue() );
	ADD_UNIT( TestAuthorizations() );
	ADD_UNIT( TestAuthInfo() );
	ADD_UNIT( TestColumn() );
	RUN_TESTS


}
