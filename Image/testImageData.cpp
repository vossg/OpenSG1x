
#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGImage.h"
#include "OSGImageFileHandler.h"

int main (int argc, char **argv)
{
    OSG::Bool retCode = 0;
    ofstream out;
    osg::ImageFileType *fileType;
    osg::Image image;
    osg::UChar8 *data = 0;
    unsigned long i,maxSize;

    OSG::ImageFileHandler::the().print();

    if(argc >= 3 && !OSG::stringcasecmp(argv[1], "-type"))
    {
        fileType = osg::ImageFileHandler::the().getFileType(argv[2]);  
        argv += 2;
        argc -= 2;       
    }
    else 
    {
        fileType = osg::ImageFileHandler::the().getFileType("MTD");
    }
    
    if (argc > 2)
    {
        if (image.read(argv[1]))
        {
            out.open(argv[2]);
            if (out.eof() == false)
            {
                maxSize = fileType->maxBufferSize(image);
                data = new osg::UChar8[maxSize];
                maxSize = fileType->store(image,(osg::UChar8*)data);
                out << "unsigned char imageData[] = {" ;
                for (i = 0; i < maxSize; i++)
                {
                    if ((i % 8) == 0)
                        out << endl;
                    out << int(data[i]) << ", ";
                }
                out << endl << "};" << endl;
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
