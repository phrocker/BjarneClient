/**
  * Hello, this is BjarneClient, a free and open implementation of Accumulo
  * and big table. This is meant to be the client that accesses Accumulo
  * and BjarneTable -- the C++ implemenation of Accumulo. Copyright (C)
  * 2013 -- Marc Delta Poppa @ accumulo.net
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.

  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  **/

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
