
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
    Image image;
    unsigned w,h,d;

    OSG::ImageFileHandler::the().print();

    if (argc > 2)
    {
      if ( image.read(argv[1])) {
        image.dump();
        if (argc > 5) 
        {
          w = atoi(argv[3]);
          h = atoi(argv[4]);
          d = atoi(argv[5]);
          image.scale( w, h, d );
        }
        else
          image.scaleNextPower2();
        image.dump();
        image.write( argv[2] );
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
