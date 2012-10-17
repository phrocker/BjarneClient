/*
 * Authorizations.h
 *
 *  Created on: Oct 16, 2012
 *      Author: marc
 */

#ifndef AUTHORIZATIONS_H_
#define AUTHORIZATIONS_H_

#include "../../exceptions/ClientException.h"

#include <iostream>
#include <string>
#include <set>
#include <list>

using namespace std;
using namespace cclient::exceptions;

namespace cclient {
namespace data {
namespace security {
class Authorizations {
public:
	Authorizations(string authorizations, char *validCharacters, int valid)
	{
		for(int i=0; i < valid; i++)
		{
			validAuthChars[ validCharacters[i] ] = true;
		}
	}
	Authorizations(list<string> authorizations) {
		for (list<string>::iterator it = authorizations.begin(); it != authorizations.end(); it++)
		    addAuthorization( **it );
	}

	void addAuthorization(string auth);



	static int __init_auths;

	virtual ~Authorizations();
protected:

	void validateAuths()
	{
		for (list<string>::iterator it = authStrings.begin(); it != authStrings.end(); it++)
		{
			for(int i=0; i < (*it).size(); i++)
			{
				if (!isValidAuthCharacter( (*it).at(i) ))
				{
					throw ClientException("Invalid authorization character");
				}
			}
		}
	}
	static int buildDefaultAuths()
	{
		for (int i = 0; i < 256; i++) {
			validAuthChars[i] = false;
		}

		for (int i = 'a'; i <= 'z'; i++) {
			validAuthChars[i] = true;
		}

		for (int i = 'A'; i <= 'Z'; i++) {
			validAuthChars[i] = true;
		}

		for (int i = '0'; i <= '9'; i++) {
			validAuthChars[i] = true;
		}

		validAuthChars['_'] = true;
		validAuthChars['-'] = true;
		validAuthChars[':'] = true;
		return 0;
	}

	static bool isValidAuthCharacter( char c )
	{
		return validAuthChars[ c ];
	}

	set<string> authStrings;

	static bool validAuthChars = new bool[256];
};


int Authorizations::__init_auths = Authorizations::buildDefaultAuths();
}
}
}
#endif /* AUTHORIZATIONS_H_ */
