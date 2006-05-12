
#include "OSGConfig.h"

#include <string>

#include <stdio.h>

#include "OSGLog.h"

#include "OSGImageFileHandler.h"
#include "OSGImage.h"
#include "OSGBaseFunctions.h"

int main (int argc, char **argv)
{
    OSG::osgInit(argc,argv);

    // create a image with some dpi
    OSG::ImagePtr img = OSG::Image::create();
    img->set(OSG::Image::OSG_RGB_PF, 640, 512);
    img->setResX(300.0f);
    img->setResY(300.0f);
    img->setResUnit(OSG::Image::OSG_RESUNIT_INCH);

    // write/read png
    std::string outname = "out.png";
    OSG::ImageFileHandler::the().write(img, outname.c_str());

    img = OSG::ImageFileHandler::the().read(outname.c_str());
    if(img == OSG::NullFC)
        printf("Couldn't read image '%s'!", outname.c_str());
    else
        printf("Read image '%s' with dpi = %f x %f\n", outname.c_str(), img->getResX(), img->getResY());

    // write/read tiff
    outname = "out.tif";
    OSG::ImageFileHandler::the().write(img, outname.c_str());

    img = OSG::ImageFileHandler::the().read(outname.c_str());
    if(img == OSG::NullFC)
        printf("Couldn't read image '%s'!", outname.c_str());
    else
        printf("Read image '%s' with dpi = %f x %f\n", outname.c_str(), img->getResX(), img->getResY());

    // write/read jpg
    outname = "out.jpg";
    OSG::ImageFileHandler::the().write(img, outname.c_str());

    img = OSG::ImageFileHandler::the().read(outname.c_str());
    if(img == OSG::NullFC)
        printf("Couldn't read image '%s'!", outname.c_str());
    else
        printf("Read image '%s' with dpi = %f x %f\n", outname.c_str(), img->getResX(), img->getResY());

    return 0;
}
