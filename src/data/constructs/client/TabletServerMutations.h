/*
 * TabletServerMutations.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#ifndef TABLETSERVERMUTATIONS_H_
#define TABLETSERVERMUTATIONS_H_

#include <map>
#include <list>

#include "../KeyExtent.h"
#include "../Mutation.h"

using namespace std;
namespace cclient {
namespace data {

class TabletServerMutations {
public:
	TabletServerMutations();
	virtual ~TabletServerMutations();

	void addMutation(KeyExtent *extent, Mutation m) {
		list<Mutation> mutationList = mutations[m];
		mutationList.push_back(m);
	}

	map<KeyExtent*, list<Mutation> > *getMutations() {
		return &mutations;
	}

protected:
	static map<KeyExtent*, list<Mutation>> mutations;
};

} /* namespace data */
} /* namespace cclient */
#endif /* TABLETSERVERMUTATIONS_H_ */
