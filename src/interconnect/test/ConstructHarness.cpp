#include <iostream>
#include <exception>

using namespace std;

#include "../../data/constructs/test/RunUnit.h"


#include "TestScanRequest.h"
#include "TestTransports.h"


using namespace cclient::test;


int main()
{
	try
	{
		RUN_TEST( TestIdentifier() );
		RUN_TEST( TestScanRequest() );
		RUN_TEST( TestServerConnection() );
	}
	catch(std::exception& e)
	{
		cout << "Exception occurred " << e.what() << " ; Result: failed" << endl;
	}


}
