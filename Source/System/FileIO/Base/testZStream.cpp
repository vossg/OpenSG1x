
#include "OSGConfig.h"
#include "OSGBaseTypes.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "OSGZStream.h"

#ifdef OSG_ZSTREAM_SUPPORTED

OSG_USING_NAMESPACE

int main (int argc, char **argv)
{
    std::stringstream compressed(std::stringstream::in | std::stringstream::out);

    // with false we add no gzip header and footer.
    zip_ostream zout(compressed, false);
    
    zout << std::string("Begin")
         << " " << Int32(123456789)
         << " " << Real32(1.41232)
         << " " << std::string("End");

    // this flushes the stream and adds the gzip footer, this is
    // done automatically in the zip_ostream destructor, but in this
    // case we need to call it directly!
    zout.finished();

    std::cout << "Compressed  : " << "'" << compressed.str() << "' (" << compressed.str().size() << ")" << std::endl;

    std::string str1;
    Int32 v1 = 0;
    Real32 v2 = 0.0f;
    std::string str2;

    zip_istream zin(compressed);
    zin >> str1 >> v1 >> v2 >> str2;

    std::cout << "Uncompressed: " << "'" << str1 << "' " << v1 << " " << v2
                                  << " '" << str2 << "'" << std::endl;

    return 0;
}
#else

int main (int argc, char **argv)
{
    std::cerr << "Z-Stream not supported!" << std::endl;
}

#endif // OSG_ZSTREAM_SUPPORTED
