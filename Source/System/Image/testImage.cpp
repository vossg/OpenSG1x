
#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include "OSGLog.h"

#include "OSGImageFileHandler.h"
#include "OSGImage.h"
#include "OSGBaseFunctions.h"

using OSG::Image;
using OSG::ImagePtr;

int main (int argc, char **argv)
{
    int retCode = 0;
    char defaultOutImage[] = "out.pnm";
    ImagePtr pImage;

    OSG::osgInit(argc,argv);

    OSG::ImageFileHandler::the().dump();

    if (argc > 1)
    {
        pImage = OSG::Image::create();

        pImage->read(argv[1]);
        pImage->dump();
        pImage->write( (argc > 2) ? argv[2] : defaultOutImage);

        OSG::subRefCP(pImage);

    }
    else
    {
        FLOG (("usage: %s inputimage [ouputimage]\n", argv[0]));
        retCode = -1;
    }

    return retCode;
}
