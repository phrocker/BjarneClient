#ifndef SCAN_IDENT_H_
#define SCAN_IDENT_H_

#include <iostream>
#include <algorithm>
#include <map>


using namespace std;

#include "../transport/TransportIdentifiers.h"

namespace interconnect
{
struct CopyKey
{
	template<typename T>
	typename T::first_type operator()(T keyValuePair) const
	{
		return keyValuePair.first;
	}
};




template<typename M, typename V>
class ScanIdentifier: private TransportIdenifiers<M,V>
{
protected:
	map<M, vector<V> > globalIdentifierMapping;

public:
	ScanIdentifier()
	{

	}

	vector<V> getIdentifiers(M m)
	{
		return globalIdentifierMapping[m];
	}

	vector<M> getGlobalMapping()
	{
		vector<M> keys;
		transform(globalIdentifierMapping.begin(),
				globalIdentifierMapping.end(), back_inserter(keys), CopyKey());
		return keys;
	}
};
}
#endif
