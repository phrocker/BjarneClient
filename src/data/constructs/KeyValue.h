/*
 * KeyValue.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#ifndef KEYVALUE_H_
#define KEYVALUE_H_

#include <stdint.h>
#include "key.h"
#include "value.h"
#include "rkey.h"




namespace cclient {
namespace data {

class KeyValue {
public:
	 KeyValue(): key((StreamInterface*)new RelativeKey()), my_alloc(true)
	    {

	    }



	    virtual ~KeyValue()
	    {
	        if (my_alloc)
	            delete key;
	    }

	    /**
	     * Sets the key
	     * @param k key to set
	     */
	    void setKey(StreamInterface *k)
	    {
	        if (my_alloc)
	            delete key;
	        key = k;
	    }


	    StreamInterface *getKey();

	    StreamInterface *getStream();

	    Value *getValue();
	    void setValue(Value *v);
	    void setValue(uint8_t *b, size_t size);
	    uint64_t write(OutputStream *outStream);
	    KeyValue &operator=(const KeyValue &other);
	    bool operator <(const KeyValue &rhs) const;
	    bool operator <(const KeyValue *rhs) const;
	    bool operator == (const KeyValue *rhs) const;
	    bool operator == (const KeyValue & rhs) const;
	    bool operator != (const KeyValue &rhs) const;
	    bool operator != (const KeyValue *rhs) const;




	protected:
	    StreamInterface *key;
	    Value value;
	    bool my_alloc;

};

} /* namespace data */
} /* namespace cclient */
#endif /* KEYVALUE_H_ */
