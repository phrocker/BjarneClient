#ifndef IOEXCEPTIONS_H
#define IOEXCEPTIONS_H

#include <string>
#include <iostream>
#include <typeinfo>
using namespace std;

/**
    @file ioexceptions.h
    @author Marc Parisi <marc.parisi@g2-inc.com>
    @version 1.0
    @section DESCRIPTION
     Contains the IO related exceptions.


 */

namespace IO
{

    struct TabletException : public std::exception
    {
        std::string s;
        TabletException(std::string ss) : s(ss) {}
        ~TabletException()  throw ()
        {

        }
        const char* what() const throw() {
            return s.c_str();
        }
    };
}

#endif
