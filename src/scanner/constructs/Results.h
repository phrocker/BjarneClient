/*
 * Results.h
 *
 *  Created on: Dec 9, 2012
 *      Author: marc
 */

#ifndef RESULTS_H_
#define RESULTS_H_

#include <iostream>
#include <string>

using namespace std;

namespace scanners {

template<class T, class TypeT = void>
class Results : public std::iterator<std::forward_iterator_tag, TypeT> {
protected:
		T *iterCurrent;
		T *iterEnd;
public:
	Results() : iterCurrent(0), iterEnd(0)
	{

	}
	virtual ~Results();
};

} /* namespace scanners */
#endif /* RESULTS_H_ */
