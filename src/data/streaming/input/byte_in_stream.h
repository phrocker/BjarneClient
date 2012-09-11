#ifndef BYTE_IN_STREAM
#define BYTE_IN_STREAM


#include <iostream>
#include <stdexcept>
using namespace std;
#include "in_stream.h"


namespace cclient {
namespace data {
namespace streams{

class ByteInputStream : public InputStream
{
public:

    ByteInputStream(InputStream *out_stream) : InputStream(out_stream), input_stream_ref( out_stream )
    {


    }
    
    ByteInputStream(char *byteArray, size_t len)
    {
      iBytes = byteArray;//new char[ len ];
      //memcpy(iBytes,byteArray,len);
      length = len;
      offset = 0;
      

    }
    
    
    



    virtual ~ByteInputStream()
    {

    }
    
    virtual InputStream *seek (uint64_t pos)
    {
	input_stream_ref->seek(pos);
	return this;
    }


  virtual uint64_t readBytes(uint8_t *bytes, size_t cnt)
    {
	if ((cnt+offset) > length)
	    throw runtime_error("Stream unavailable");
	memcpy(bytes,iBytes+offset,cnt);
	offset+= cnt;
	return cnt;
    }
    
    virtual uint64_t readBytes(char *bytes, size_t cnt)
    {
	if ((cnt+offset) > length)
	    throw runtime_error("Stream unavailable");
	memcpy(bytes,iBytes+offset,cnt);
	offset+= cnt;
	return cnt;
    }

    
    virtual uint64_t bytesAvailable()
    {
	return (length - offset );
    }


protected:
    // output stream reference.
    InputStream *input_stream_ref;
    
    char *iBytes;
    
    uint64_t length;
    
    uint32_t offset;

};
}
}
}
#endif
