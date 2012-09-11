#ifndef TRANSLATION_STREAM
#define TRANSLATION_STREAM


//#include "dataoutstream.h"
#include "data_out_stream.h"



namespace cclient {
namespace data {
namespace streams {

class EndianTranslationStream : public HadoopDataOutputStream
 {
public:

	EndianTranslationStream(OutputStream *os);

	uint64_t htonlw(uint64_t value);

	uint64_t writeShort(short shortVal);

	uint64_t writeInt(int intVal);

	uint64_t writeLong(uint64_t val);




};
}
}
}
#endif
