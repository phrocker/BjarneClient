/*
 * Mutation.h
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#ifndef MUTATION_H_
#define MUTATION_H_

#include "../data_types.h"
#include <iostream>
#include <sys/types.h>
#include <stdint.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <byteswap.h>
using namespace std;

namespace cclient
{

namespace data
{

class Mutation {
public:
	Mutation(string row);

	void put(string cf, string cq, string cv, int64_t ts, uint8_t *value, uint64_t value_len);
	void put(string cf, string cq="", string cv="", unsigned long ts=0);
	accumulo::data::TMutation toThrift();
	virtual ~Mutation();
	string getRow()
	{
		return mut_row;
	}
protected:

    void write(const uint8_t *b, uint32_t length) {
      reserve(length);
      memcpy(&data.at(ptr),b,length);
      ptr+=length;
    }

    void write(bool b) {
      reserve(1);
      if (b == true)
        data.at(ptr) = 1;
      else
    	data.at(ptr) = 0;
      ptr++;
    }



    void writeLong(int64_t l) {
      reserve(8);

      int64_t v = bswap_64(l);
      write((uint8_t*)&v,sizeof(int64_t));
    }

    void writeInt(int32_t i) {
      reserve(4);
      int32_t v = bswap_32(i);
      write((uint8_t*)&v,sizeof(int32_t));
    }

    void reserve(uint32_t reserveSize)
    {
    	data.resize(data.size() + reserveSize );
    }


	string mut_row;

	uint32_t ptr;
	vector< uint8_t > data;

	int32_t entries;
	vector< vector<uint8_t*> > values;


};
}
}
#endif /* MUTATION_H_ */
