
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

using osg::Image;

int main (int argc, char **argv)
{
    int retCode = 0;
    char defaultOutImage[] = "out.pnm";
    Image image, image2;

    OSG::ImageFileHandler::the().print();

    if (argc > 1)
    {
        image.read(argv[1]);
        image.write( (argc > 2) ? argv[2] : defaultOutImage);
    }
    else
    {
        FLOG (("usage: %s inputimage [ouputimage]\n", argv[0]));
        retCode = -1;
    }

    return retCode;
}
