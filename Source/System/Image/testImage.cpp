
#include "OSGConfig.h"

#include <stdio.h>
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

FILE *pWRLFile = NULL;

int main (int argc, char **argv)
{
    int retCode = 0;
    char defaultOutImage[] = "out.pnm";
    ImagePtr pImage;
    ImagePtr pOutImage;
    ImagePtr pWriteImage;

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
    std::copy(l.begin(), 
              l.end(), 
              std::ostream_iterator<std::string>(std::cout, ","));
    std::cout << std::endl;

    pWRLFile = fopen("backdrop.wrl", "w");

    if (argc > 1 && pWRLFile != NULL)
    {
        char        szImageName[2048];
        pImage      = OSG::Image::create();
        pOutImage   = OSG::Image::create();
        pWriteImage = OSG::Image::create();

        pImage->read(argv[1]);
        pImage->dump();

        int iNumFrames = pImage->getFrameCount();

        fprintf(pWRLFile, "#VRML V2.0 utf8\n\n");

        fprintf(pWRLFile, "#!+ VSCPushAllEntries\n\n");

        fprintf(pWRLFile, "DEF BD_Switch Switch\n");
        fprintf(pWRLFile, "{\n");
        fprintf(pWRLFile, "    whichChoice 0\n");
        fprintf(pWRLFile, "    children\n");
        fprintf(pWRLFile, "    [\n");

        fprintf(stderr, "Dumpint %d backdrops (%f)\n", 
                pImage->getFrameCount(),
                OSG::Real32(pImage->getFrameDelay()));

        const OSG::UInt8 *pSrc;
              OSG::UInt8 *pDst;

        pOutImage->set(OSG::Image::OSG_RGB_PF, //pImage->getPixelFormat(),
                       pImage->getWidth(),
                       pImage->getHeight(),
                       pImage->getDepth(),
                       1, 
                       1, 
                       1.0,
                       NULL);


        for(int i = 0; i < iNumFrames; ++i)
        {
            sprintf(szImageName, "backdrop_frame%d.tif", i);
            fprintf(stderr, "writing image %s\n", szImageName);

            pSrc = pImage   ->getData(0, i);
            pDst = pOutImage->getData(0, 0);

            for(int j = 0; j < pImage->getWidth() * pImage->getHeight(); ++j)
            {
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;

                pSrc++;
            }

            pOutImage->scale(2048, 1024, 1, pWriteImage);
            pWriteImage->write(szImageName);

            fprintf(pWRLFile, "        DEF BD_%d Backdrop\n", i);
            fprintf(pWRLFile, "        {\n");
            fprintf(pWRLFile, "            hFoVLeft   -75.5\n");
            fprintf(pWRLFile, "            hFoVRight   75.5\n");
            fprintf(pWRLFile, "        \n");
            fprintf(pWRLFile, "            vFoVTop     22.13\n");
            fprintf(pWRLFile, "            vFoVBottom -22.13\n");
            fprintf(pWRLFile, "        \n");
            fprintf(pWRLFile, "            xSpacing 5.0\n");
            fprintf(pWRLFile, "            ySpacing 1.0\n");
            fprintf(pWRLFile, "            radius   3.6576\n");
            fprintf(pWRLFile, "        \n");
            fprintf(pWRLFile, "            url \"%s\"\n", szImageName);
            fprintf(pWRLFile, "        }\n");
            fprintf(pWRLFile, "        \n");
        }

        fprintf(pWRLFile, "    ]\n");
        fprintf(pWRLFile, "}\n\n");

        fprintf(pWRLFile, "DEF KeyE KeySensor\n");
        fprintf(pWRLFile, "{\n");
        fprintf(pWRLFile, "        key \"e\"\n");
        fprintf(pWRLFile, "}\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "DEF KeyW KeySensor\n");
        fprintf(pWRLFile, "{\n");
        fprintf(pWRLFile, "        key \"q\"\n");
        fprintf(pWRLFile, "}\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "DEF CounterE VSCLimitedCounter\n");
        fprintf(pWRLFile, "{\n");
        fprintf(pWRLFile, "    lowerLimit 0\n");
        fprintf(pWRLFile, "    upperLimit %d\n", iNumFrames - 1);
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "    value 0\n");
        fprintf(pWRLFile, "    step  1\n");
        fprintf(pWRLFile, "}\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "ROUTE_IMM KeyE.pressed TO CounterE.incTrigger\n");
        fprintf(pWRLFile, "ROUTE_IMM KeyW.pressed TO CounterE.decTrigger\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "ROUTE_IMM CounterE.value TO BD_Switch.whichChoice");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "\n\n");

        fprintf(pWRLFile, "DEF BD_Sequencer Int32Sequencer\n");
        fprintf(pWRLFile, "{\n");
        fprintf(pWRLFile, "    key      [ ");
 
        OSG::Real32 rStep = 1.f / OSG::Real32(iNumFrames - 1);
        OSG::Real32 rVal  = 0.f;

        for(int i = 0; i < iNumFrames; ++i)
        {
            fprintf(pWRLFile, "%f ", rVal);
            rVal += rStep;
        }
        fprintf(pWRLFile, "]\n");

        fprintf(pWRLFile, "    keyValue [ ");

        for(int i = 0; i < iNumFrames; ++i)
        {
            fprintf(pWRLFile, "%d ", i);
        }

        fprintf(pWRLFile, "]\n");

        fprintf(pWRLFile, "}\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, 
                "ROUTE_IMM BD_Sequencer.value TO BD_Switch.whichChoice\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, "DEF TS TimeSensor\n");
        fprintf(pWRLFile, "{\n");
        fprintf(pWRLFile, "    loop TRUE\n");
        fprintf(pWRLFile, "    cycleInterval %f\n", 
                OSG::Real32(iNumFrames * pImage->getFrameDelay()));
        fprintf(pWRLFile, "}\n");
        fprintf(pWRLFile, "\n");
        fprintf(pWRLFile, 
                "ROUTE_IMM TS.fraction_changed TO BD_Sequencer.fraction\n");
        fprintf(pWRLFile, "\n");

        OSG::subRefCP(pImage);

        fclose(pWRLFile);
    }
    else
    {
        FLOG (("usage: %s inputimage [ouputimage]\n", argv[0]));
        retCode = -1;
    }

    return retCode;
}
