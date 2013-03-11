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
#include <iostream>

#include "Results.h"
#include "TypedResults.h"

using namespace std;
using namespace scanners;

int main()
{
	Results<int,ResultBlock<int> > res;
	res.add(34);
	res.add(6);
	res.add(9);
	res.add(3);


	Results<int,ResultBlock<int>>::iterator iter = res.begin();

	TypedResults<int,float> riter(&iter);

	TypedResults<float,double> titer(&riter);

///*
	for (; titer != titer.end(); titer++)
	{
		cout << "Value " << (*titer) << endl;
	}
//	*/
	/*

	for (; riter != riter.end(); riter++)
		{
			cout << "Value " << (*riter) << endl;
		}
	*/
}

