/*
 * Results.h
 *
 *  Created on: Dec 9, 2012
 *      Author: marc
 */

#ifndef RESULTS_H_
#define RESULTS_H_

#include <iostream>
#include <set>
#include <string>

using namespace std;

#include "../../data/constructs/inputvalidation.h"
#include "../../data/constructs/FastObj.h"

namespace scanners
{
template<typename T> class ResultBlock;
template<typename T> class ResultIter;
template<typename T, class BlockType> class Results;

template<typename T>
class ResultBlock: public std::iterator<std::forward_iterator_tag, T>
{
protected:

	typedef typename GoogleSet<T>::Set MySet;

	typedef typename MySet::iterator iter;

	iter myIter;

	MySet *resultSet;

	bool isEnd;

	virtual void setEnd(bool val)
	{
		isEnd = val;
	}

public:

	ResultBlock(typename GoogleSet<T>::Set *mySet, bool setEnd = false) :
			isEnd(setEnd)
	{
		resultSet = mySet;
		myIter = mySet->begin();
		if (setEnd)
			myIter = resultSet->end();
	}

	ResultBlock(ResultBlock *copyResultSet, bool setEnd = false) :
			isEnd(setEnd)
	{
		resultSet = copyResultSet->resultSet;
		myIter = copyResultSet->myIter;
		if (setEnd || copyResultSet->isEnd)
		{

			myIter = resultSet->end();
		}
		else
		{

		}
	}

	ResultBlock<T> begin()
	{

		if (!isEnd)
			myIter = resultSet->begin();
		else
			myIter = resultSet->end();
		return *this;
	}

	bool isEndOfRange()
	{
		return isEnd;
	}

	ResultBlock<T> end()
	{
		return static_cast<ResultBlock<T> >(ResultBlock(this, true));
	}

	T &operator*()
	{
		return *myIter;
	}

	ResultBlock& operator++()
	{
		myIter++;
		return *this;
	}

	ResultBlock& operator++(int t)
	{
		myIter++;
		return *this;
	}

	ResultBlock& operator=(const ResultBlock &rhs)
	{
		resultSet = rhs->resultSet;
		myIter = rhs->begin();
		if (rhs->isEnd)
			myIter = rhs->end();
		return *this;
	}

	bool operator==(const ResultBlock &rhs)
	{
		return *myIter == (*rhs.myIter);
	}

	bool operator==(const ResultIter<T> &rhs)
	{
		return *myIter == (*rhs);
	}

	bool operator!=(const ResultBlock &rhs)
	{
		return !(*this == rhs);
	}

	void add(T t)
	{
		resultSet->insert(t);
	}

	void add(vector<T> *t)
	{
		resultSet->insert(t->begin(),t->end());
	}

	virtual ~ResultBlock()
	{

	}
	friend class ResultIter<T> ;
};

template<typename T>
class ResultIter: public ResultBlock<T>
{
protected:
	ResultBlock<T> *parent;

	void setEnd(bool val)
	{
		ResultBlock<T>::setEnd(val);
	}
public:

	ResultIter(ResultBlock<T> *copyResultSet, bool end = false) :
			ResultBlock<T>(copyResultSet,
					(end ? end : copyResultSet->isEndOfRange()))

	{
		setEnd((end ? end : copyResultSet->isEndOfRange()));
		parent = copyResultSet;
	}

	ResultIter(ResultIter<T> *copyResultSet, bool end = false) :
			ResultBlock<T>(copyResultSet,
					(end ? end : copyResultSet->isEndOfRange()))

	{
		setEnd((end ? end : copyResultSet->isEndOfRange()));
		parent = copyResultSet;
	}

	ResultBlock<T> begin()
	{

		return *this;
	}

	ResultBlock<T> end()
	{

		return parent->end();
	}

	T &operator*()
	{
		return *(*parent);
	}

	ResultIter& operator++()
	{
		(*parent)++;
		return *this;
	}

	ResultIter& operator++(int t)
	{
		(*parent)++;
		return *this;
	}

	bool operator==(const ResultIter &rhs)
	{
		return *(*parent) == *(*rhs.parent);
	}

	bool operator==(const ResultBlock<T> &rhs)
	{
		return *(*parent) == (*rhs.myIter);
	}

	bool operator!=(const ResultIter<T> &rhs)
	{
		return !(*this == rhs);
	}

	bool operator!=(const ResultBlock<T> &rhs)
	{
		return !(*this == rhs);
	}

	virtual ~ResultIter()
	{

	}
};

template<typename T, class BlockType>
class Results
{
protected:

	typedef typename GoogleSet<T>::Set MySet;
	typedef typename GoogleMap<uint64_t, BlockType>::Map MyMap;

	BlockType *iter;

	MyMap resultMap;

public:

	typedef BlockType iterator;

	Results() /*-> decltype(static_cast<BlockType>(T))*/
	{
		MySet *tt = new MySet();

		iter = new BlockType(tt);
	}

	void add(T t)
	{
		iter->add(t);
	}

	void add(vector<T> *t)
	{
		iter->add(t);
	}

	iterator begin()
	{
		return iter->begin();
	}

protected:

};
} /* namespace scanners */
#endif /* RESULTS_H_ */
