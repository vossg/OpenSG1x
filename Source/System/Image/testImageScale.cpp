
#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGImageFileHandler.h"
#include "OSGImage.h"

using OSG::Image;
using OSG::ImagePtr;

int main (int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    int retCode = 0;
    ImagePtr pImage = Image::create();
    unsigned w,h,d;

    OSG::ImageFileHandler::the().dump();

    if (argc > 2)
    {
      if ( pImage->read(argv[1])) {
        pImage->dump();
        if (argc > 5) 
        {
          w = atoi(argv[3]);
          h = atoi(argv[4]);
          d = atoi(argv[5]);
          pImage->scale( w, h, d );
        }
        else
          pImage->scaleNextPower2();
        pImage->dump();
        pImage->write( argv[2] );
      }
      else 
      {
        FFATAL (("Cannot read %s\n", argv[1]));
      }
    }
    else
    {
        FLOG (( "usage: %s inputimage outputimage [width height depht]\n", 
                argv[0]));
        retCode = -1;
    }

    return retCode;
}
