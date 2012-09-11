/*
 * Writer.cpp
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#include "MutationCollector.h"


namespace cclient {
namespace writer {
MutationCollector::MutationCollector(string table) : table(table) {
	// TODO Auto-generated constructor stub

}

MutationCollector::~MutationCollector() {
	// TODO Auto-generated destructor stub
}

/**
 * Push the mutation onto the internal vector
 */
void MutationCollector::write(Mutation m)
{
	mutations.push_back(m);
}

vector<Mutation>::iterator MutationCollector::getMutations()
{
	return mutations.begin();
}

}
}
