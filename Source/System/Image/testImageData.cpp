
#include "OpenSG/OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OpenSG/OSGBaseFunctions.h"
#include "OpenSG/OSGLog.h"
#include "OpenSG/OSGImage.h"
#include "OpenSG/OSGImageFileHandler.h"

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    bool retCode = 0;
    std::ofstream out;
    OSG::ImageFileType *fileType;
    OSG::ImagePtr pImage = OSG::Image::create();
    OSG::UChar8 *data = 0;
    unsigned long i,maxSize;

    if(argc >= 3 && !OSG::stringcasecmp(argv[1], "-type"))
    {
        fileType = OSG::ImageFileHandler::the().getFileType(argv[2]);  
        argv += 2;
        argc -= 2;       
    }
    else 
    {
        fileType = OSG::ImageFileHandler::the().getDefaultType();
    }
    
    if (argc > 2)
    {
        if (pImage->read(argv[1]))
        {
            FINFO (( "Input image has alpha: %s\n",
                     pImage->hasAlphaChannel() ? "true" : "false" ));

            out.open(argv[2]);
            if (out.eof() == false)
            {
                maxSize = fileType->maxBufferSize(pImage);
                data = new OSG::UChar8[maxSize];
                maxSize = fileType->store(pImage,(OSG::UChar8*)data);
                out << "static unsigned char imageData[" << maxSize << "] = {" ;
                for (i = 0; i < maxSize; i++)
                {
                    if ((i % 8) == 0)
                        out << std::endl;
                    out << int(data[i]) << ", ";
                }
                out << std::endl << "};" << std::endl;
                delete [] data;
                retCode = 0;
            }
            else
            {
                FFATAL (("Can not open %s output file\n"));
                retCode = -2;
            }
        }
        else
        {
            FFATAL (("Can not open %s input file\n"));
            retCode = -3;
        }
    }
    else
    {
        FLOG (( "usage: %s inputImageFile outputAsciiFile\n", argv[0] ));
        retCode = -1;
    }

    return retCode;
}
