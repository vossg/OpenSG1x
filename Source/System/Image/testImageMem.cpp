
#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGImageFileHandler.h"
#include "OSGImage.h"

using OSG::Image;


bool readMemDump (OSG::Image &image, const char *fileName)
{
  bool retCode = false;
  std::ifstream ins(fileName, std::ios::in | std::ios::binary );
  unsigned long readData, dataSize = 0;
  OSG::UChar8 * data;

  if (ins) {
    ins.seekg(0, std::ios::end );
    dataSize = ins.tellg();
    if (dataSize) {
      data = new OSG::UChar8 [dataSize];
      ins.seekg ( 0, std::ios::beg );
      ins.read ( reinterpret_cast<char*>(data), dataSize );
      readData = ins.gcount();
      if (readData == dataSize) {
        image.restore ( data, dataSize );
        retCode = true;
      }
    }
  }

  return retCode;
}

bool writeMemDump (OSG::Image &image, const char *fileName)
{
  bool retCode = false;
  std::ofstream outs(fileName, std::ios::in | std::ios::binary );
  unsigned long maxSize, dataSize;
  OSG::ImageFileType *fType;
  OSG::UChar8 * data;
  
  fType = OSG::ImageFileHandler::the().getFileType("MTD");

  if (fType && outs) {
    maxSize = fType->maxBufferSize(image);
    data = new OSG::UChar8[maxSize];
    dataSize = fType->store(image, (OSG::UChar8*)data );
    outs.write ( reinterpret_cast<char*>(data), dataSize );
    retCode = (dataSize && (dataSize <= maxSize));
  }
  
  return retCode;
}

int main (int argc, char **argv)
{
  int retCode = 0;
  //char defaultOutImage[] = "out.pnm";
  Image *pImage = new Image;
  OSG::ImageFileType *fType;
  
  if (argc > 2)
    {
      fType = OSG::ImageFileHandler::the().getFileType(0,argv[1]);
      if (fType) {
        // read as image file
        fType->read(*pImage,argv[1]);
      }
      else {
        // read as mem dump
        readMemDump(*pImage,argv[1]);
      }

      fType = OSG::ImageFileHandler::the().getFileType(0,argv[2]);
      if (fType) {
        // write as image file
        fType->write(*pImage,argv[2]);
      }
      else {
        // read as mem dump
        writeMemDump(*pImage,argv[2]);
      }
    }
  else
    {
      FLOG (("usage: %s inputimage ouputimage\n", argv[0]));
      retCode = -1;
    }
  
  return retCode;
}
