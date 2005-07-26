
#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGImage.h"
#include "OSGImageFileHandler.h"

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    bool retCode = 0;
    std::ofstream out;
    OSG::ImageFileType *fileType;
    OSG::ImagePtr pImage = OSG::Image::create();
    OSG::UChar8 *data = 0;
    unsigned long i,maxSize;

    if(argc >= 4 && !OSG::stringcasecmp(argv[1], "-t"))
    {
        fileType = OSG::ImageFileHandler::the().getFileType(argv[2]);  
        argv += 2;
        argc -= 2;       
    }
    else 
    {
        fileType = OSG::ImageFileHandler::the().getDefaultType();
    }
    
    if (argc > 3)
    {
        if (pImage->read(argv[1]))
        {
            out.open(argv[3]);
            if (out.eof() == false)
            {
                maxSize = (unsigned long)(fileType->maxBufferSize(pImage));
                data = new OSG::UChar8[maxSize];
                maxSize = (unsigned long)fileType->store(pImage,(OSG::UChar8*)data);
                out << "/* Image: " << argv[1] << "*/" << std::endl;
                out << "static unsigned int " << argv[2] << "Width = " 
                    << pImage->getWidth() << ";" << std::endl;               
                out << "static unsigned int " << argv[2] << "Height = " 
                    << pImage->getHeight() << ";" << std::endl;               
                out << "static unsigned char " << argv[2] << "Data[" << maxSize << "] = {" ;
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
        FLOG (( "usage: %s [-t <mimeType>] inputImageFile varname outputAsciiFile\n", argv[0] ));
        retCode = -1;
    }

    return retCode;
}
