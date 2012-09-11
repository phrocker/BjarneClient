/*
 * Value.h
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#ifndef VALUE_H
#define VALUE_H


#include "../streaming/stream_ifc.h"

#include <stdint.h>
#include <cstdio>
#include <cstring>




namespace cclient
{
namespace data
{
using namespace cclient::data::streams;

class Value : public StreamInterface
{
public:

    Value();

    virtual ~Value();

    void setValue(uint8_t *val, size_t size, uint32_t ptrOff = 0);

    void append( uint8_t *val, size_t size );

    void deepCopy(Value *v);


    uint8_t *data();

    size_t size();

    StreamInterface *getStream();

    std::pair<uint8_t*,size_t> getValue() const;

    uint64_t write(OutputStream *outStream);

    bool operator == (const Value & rhs) const;

    bool operator != (const Value &rhs) const ;

private:

    // value array.
    uint8_t *value;
    // offset;
    uint16_t offset;
    // value size.
    size_t valueSize;
};
}
}


#endif
