
#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include "OSGImageFileHandler.cpp"
#include "OSGImage.h"

using OSG::OSGImage;

int main (int argc, char **argv)
{
	OSGImage image, image2;
	
	// OSGImageFileHandler::the().print();

	image.set (256,256, "R5G5B5P1");

	if (argc > 1) {
		image.read(argv[1]);

		// image.scale (512,512);

		if (argc > 2) 
			image.write(argv[2]);
		else
		  image.write("image.ppm");
	 	
	}

	return 0;
}
