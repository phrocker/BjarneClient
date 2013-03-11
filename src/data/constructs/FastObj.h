#ifndef FAST_OBJ_H_
#define FAST_OBJ_H_


#include "../extern/cpp-btree/btree_set.h"
#include "../extern/cpp-btree/btree_map.h"

template<typename T, typename V>
struct GoogleMap
{

	typedef btree::btree_map<T,V> Map;

};

template<typename T>
struct GoogleSet
{
	typedef btree::btree_set<T> Set;
};


#endif

