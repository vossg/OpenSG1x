
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

int main (int argc, char **argv)
{
    int retCode = 0;
    char defaultOutImage[] = "out.pnm";
    Image *pImage;

    OSG::ImageFileHandler::the().dump();

    if (argc > 1)
    {
        pImage = new Image;

        pImage->read(argv[1]);
        pImage->dump();
        pImage->write( (argc > 2) ? argv[2] : defaultOutImage);

        OSG::subRefP(pImage);

    }
    else
    {
        FLOG (("usage: %s inputimage [ouputimage]\n", argv[0]));
        retCode = -1;
    }

    return retCode;
}
