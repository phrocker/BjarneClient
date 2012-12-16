/*
 * Configuration.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#include "Configuration.h"


#include <string>
#include <map>

using namespace std;

namespace cclient {
namespace impl {

Configuration::Configuration() {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}


void
Configuration::set(string name, string value)
{
    configurationMap[name] = value;

}


string Configuration::get(string name)
{
    if (configurationMap.find(name) == configurationMap.end())
    {
        return NULL;
    }
    else
        return configurationMap[ name ];

}

} /* namespace impl */
} /* namespace cclient */
