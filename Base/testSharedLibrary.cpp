/*	System Includes
*/
#include <iostream>


/*	OSG Includes
*/
#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGSharedLibrary.h"

/*	General Settings
*/


int main( osg::Int32 argc, osg::Char8** argv)
{
	// Init OSG

	OSG::osgInit(argc, argv);

    OSG::SharedLibrary  oSharedGLLib("opengl32.dll");
    OSG::SharedLibrary *pSharedGLUTLib = new OSG::SharedLibrary;

    pSharedGLUTLib->open("glut32.dll");


    OSG::AnonSymbolHandle hSym  = oSharedGLLib.getSymbol("glBegin");
    OSG::AnonSymbolHandle hSym1 = oSharedGLLib.getSymbol("glutPostRedisplay");

    fprintf(stderr, "%p | %p\n", hSym, hSym);
	
	return 0;
}
