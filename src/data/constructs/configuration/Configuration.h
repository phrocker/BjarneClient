/*
 * Configuration.h
 *
 *  Created on: Oct 7, 2012
 *      Author: marc
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <map>

using namespace std;

namespace cclient {
namespace impl {

class Configuration {
public:
	Configuration();
	virtual ~Configuration();
    void set(string name, string value);
    string get(string name);
protected:
    map<string,string> configurationMap;
};

} /* namespace impl */
} /* namespace cclient */
#endif /* CONFIGURATION_H_ */
