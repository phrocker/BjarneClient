/*
 * Value.cpp
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#include <utility>
#include <iostream>

using namespace std;

#include "value.h"

using namespace cclient::data;

Value::Value() : valueSize(0)
   {
       value = new uint8_t[0];
       offset = 0;
   }

   virtual Value::~Value()
   {
       if (value != NULL)
           delete [] value;
   }

   /**
    * Sets the value using the value and the corresponding size and offset.
    */
   void Value::setValue(uint8_t *val, size_t size, uint32_t ptrOff = 0)
   {


       if ( (size + ptrOff) > valueSize)
       {
           uint8_t *oldVal = value;
           value = new uint8_t[ size+ptrOff ];
           if (oldVal != NULL)
           {
               memcpy(value,oldVal,ptrOff);
               delete [] oldVal;
           }
           valueSize  = size+ptrOff;
       }

       memcpy(value+ptrOff,val,size);

       offset= size;


   }

   /**
    * Appends val to the current value.
    */
   void Value::append( uint8_t *val, size_t size )
   {
       if ( (size+offset) > valueSize)
       {
           uint8_t *oldVal = value;
           value = new uint8_t[ size+offset ];
           memcpy(value,oldVal,offset);
           delete [] oldVal;
           valueSize  = size+offset;
       }

       memcpy(value+offset,val,size);

       offset += size;
   }



   /**
    * Deep copies the object.
    */
   void Value::deepCopy(Value *v)
   {

       v->value = value;
       v->valueSize = valueSize;
       v->offset = offset;
       value = NULL;
       offset = 0;
       valueSize = 0;
   }


   uint8_t *Value::data()
   {
       return value;
   }


   size_t Value::size()
   {
       return offset;
   }


   StreamInterface *Value::getStream()
   {
       return this;
   }


   std::pair<uint8_t*,size_t> Value::getValue() const
   {
       return make_pair(value,offset);
   }


   uint64_t Value::write(OutputStream *outStream)
   {
       outStream->writeInt( offset );
       return outStream->writeBytes( value,offset );
   }

   bool Value::operator == (const Value & rhs) const
   {
       if (valueSize == rhs.valueSize && offset == rhs.offset)
       {
           return (memcmp(value,rhs.value,valueSize) == 0);
       }
       else
           return false;
   }

   bool Value::operator != (const Value &rhs) const {
       return !(*this == rhs);
   }
