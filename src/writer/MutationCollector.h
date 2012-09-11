/*
 * Writer.h
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#ifndef WRITER_H_
#define WRITER_H_


#include "../data/Mutation.h"
#include <vector>
#include <string>

using namespace cclient::data;
using namespace std;

namespace cclient {
namespace writer {
class MutationCollector {
public:
	MutationCollector(string table);

	virtual ~MutationCollector();

	vector<Mutation>::iterator getMutations();
	vector<Mutation>::iterator end()
	{
		return mutations.end();
	}

	void write(Mutation m);

	void flush()
	{
		mutations.clear();
	}

	string getTable()
	{
		return table;
	}


protected:
	string table;
	vector<Mutation> mutations;

};
}
}
#endif /* WRITER_H_ */
