
#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include "OSGImageFileHandler.h"
#include "OSGImage.h"

using osg::Image;

int main (int argc, char **argv)
{
	Image image, image2;
	
	OSG::ImageFileHandler::the().print();

	image.set ( Image::OSG_RGB_PF, 256, 256 );

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
