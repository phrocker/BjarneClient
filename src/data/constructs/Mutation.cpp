/*
 * Mutation.cpp
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#include "Mutation.h"

namespace cclient
{

namespace data
{


Mutation::Mutation(string row) : mut_row(row), ptr(0), entries(0)
{

}

Mutation::~Mutation() {

}


void Mutation::put(string cf, string cq, string cv, int64_t ts, uint8_t *value, uint64_t value_len)
{
	writeInt(cf.size());
	write((uint8_t*)cf.c_str(),cf.size());
	writeInt(cq.size());
	write((uint8_t*)cq.c_str(),cq.size());
	writeInt(cv.size());
	write((uint8_t*)cv.c_str(),cv.size());
	write(true);
	writeLong(ts);
	write(false);
	writeInt(value_len);
	write(value,value_len);
	entries++;

}

void Mutation::put(string cf, string cq, string cv, unsigned long ts)
{

}


accumulo::data::TMutation Mutation::toThrift()
{
	accumulo::data::TMutation newMutation;
	newMutation.row = mut_row;
	newMutation.data.append((char*)&data.at(0),ptr);
	cout << "ptr length is " << ptr << " " << entries << endl;
	newMutation.entries = entries;


	return newMutation;
}


}
}
