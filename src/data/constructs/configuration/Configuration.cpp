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
	

}

Configuration::~Configuration() {
	
}


void
Configuration::set(string name, string value)
{
    configurationMap[name] = value;

}


string Configuration::get(string name)
{
     return get(name,NULL);

}

string Configuration::get(string name, string def)
{
    if (configurationMap.find(name) == configurationMap.end())
    {
        return def;
    }
    else
        return configurationMap[ name ];

}

uint32_t Configuration::getLong(string name)
{
     return get(name,0);

}

uint32_t Configuration::getLong(string name, uint32_t def)
{
    if (configurationMap.find(name) == configurationMap.end())
    {
        return def;
    }
    else
        return atol(configurationMap[ name ]);

}

} /* namespace impl */
} /* namespace cclient */
