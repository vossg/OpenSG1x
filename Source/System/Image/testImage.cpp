
#include "OSGConfig.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <list>

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

    std::list<const OSG::Char8 *> l;
    
    OSG::ImageFileHandler::the().getSuffixList(l,
                    OSG::ImageFileType::OSG_READ_SUPPORTED);
                    
    std::cout << "Formats supported for reading: ";
    std::copy(l.begin(), l.end(), std::ostream_iterator<std::string>(std::cout, ","));
    std::cout << std::endl;
     
    OSG::ImageFileHandler::the().getSuffixList(l,
                    OSG::ImageFileType::OSG_WRITE_SUPPORTED);
                    
    std::cout << "Formats supported for writing: ";
    std::copy(l.begin(), l.end(), std::ostream_iterator<std::string>(std::cout, ","));
    std::cout << std::endl;

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
