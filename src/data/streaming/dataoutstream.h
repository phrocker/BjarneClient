#ifndef OUTPUT_STREAM
#define OUTPUT_STREAM

#include <iostream>

#include <stdint.h>
using namespace std;


namespace cclient {
namespace data {
namespace streams {


/**
 * Inspired by java representation.
 */
class OutputStream
{
public:

    OutputStream(ostream *ptr, uint64_t pos);

    OutputStream();




    virtual ~OutputStream();


    virtual void flush();

    virtual uint64_t getPos();


    virtual uint64_t write(const char *bytes, long cnt);

    virtual uint64_t writeByte(int byte);


    virtual uint64_t writeString( string s);


    virtual uint64_t write(const uint8_t *bytes, long cnt);


    virtual uint64_t writeBytes(const uint8_t *bytes, size_t cnt);


    virtual uint64_t writeBytes(const char *bytes, size_t cnt);


    virtual uint64_t writeByte(const uint8_t byte);


    virtual uint64_t writeShort(const short shortVal);

    
    virtual uint64_t writeInt(const int intVal);


    virtual uint64_t writeLong(const uint64_t val);


    virtual uint64_t writeBoolean( const bool val );


    virtual uint64_t writeHadoopLong(const int64_t n = 0);


    virtual uint32_t bytesWritten();
    friend class HadoopDataOutputStream;

protected:

    int numberOfLeadingZeros(uint64_t i) {
        // HD, Figure 5-6
        if (i == 0)
            return 64;
        int n = 1;
        int x = (int)(i >> 32);
        if (x == 0) {
            n += 32;
            x = (int)i;
        }
        if (x >> 16 == 0) {
            n += 16;
            x <<= 16;
        }
        if (x >> 24 == 0) {
            n +=  8;
            x <<=  8;
        }
        if (x >> 28 == 0) {
            n +=  4;
            x <<=  4;
        }
        if (x >> 30 == 0) {
            n +=  2;
            x <<=  2;
        }
        n -= x >> 31;
        return n;
    }

    /**
     * Constructor, which is to be used by DataOutputStream. Note that it is
     * a friend class
     * @param ptr stream pointer
     */
    OutputStream(OutputStream *ptr) : ostream_ref( ptr->ostream_ref ), position( ptr->position), copy(true)
    {


    }
    // identify that we have copied a stream
    // useful when deleting position
    bool copy;
    // position pointer.
    uint64_t *position;
    // ostream reference.
    ostream *ostream_ref;



};
}
}
}
#endif
