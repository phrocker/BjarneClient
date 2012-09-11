#ifndef HADOOP_STREAM
#define HADOOP_STREAM


#include "dataoutstream.h"


namespace cclient {
namespace data {
namespace streams {


class HadoopStream
{
public:

	/**
	 * copied from accumulo code.
	 */
    static uint64_t writeHadoopLong(OutputStream *out_stream_ref,int64_t i)
    {
        if (i >= -112 && i <= 127) {
            out_stream_ref->writeByte((int)i);
            return out_stream_ref->getPos();
        }

        int len = -112;
        if (i < 0) {
            i ^= -1L; // take one's complement'
            len = -120;
        }

        long tmp = i;
        /*
            rshift and decrement length because
            we only need to write the remainder.
         */
        while (tmp != 0) {
            tmp = tmp >> 8;
            len--;
        }
        // write the length out.
        out_stream_ref->writeByte((int)len);

        len = (len < -120) ? -(len + 120) : -(len + 112);
        /*
            Now, write the bytes out after a lshift. write
            each byte out individually.
        */
        for (int idx = len; idx != 0; idx--) {
            int shiftbits = (idx - 1) * 8;
            long mask = 0xFFL << shiftbits;
            out_stream_ref->writeByte((int)((i & mask) >> shiftbits));
        }


        return out_stream_ref->getPos();
    }

protected:



};


}
}
}

#endif
