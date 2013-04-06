#ifndef TESTAUTHORIZATIONS_H
#define TESTAUTHORIZATIONS_H


#include "RunUnit.h"
#include "../security/Authorizations.h"
#include <assert.h>
#include <list>
#include <string>
using namespace std;

using namespace cclient::data;
using namespace cclient::data::security;
using namespace cclient::test;

class TestAuthorizations: public RunUnit
{
public:

	bool testCreate()
	{
		list<string> auths;
		auths.push_back("one");
		auths.push_back("two");

		Authorizations *authorizations = new Authorizations(auths);

		UNIT_ASSERT( authorizations->getAuthorizations().size() == 2);

		delete authorizations;

		return true;
	}

	TestAuthorizations()
	{
		unit create("Test Creating authorizations", (unitFunc) &TestAuthorizations::testCreate);
		addUnit(create);
	}

};


#endif
