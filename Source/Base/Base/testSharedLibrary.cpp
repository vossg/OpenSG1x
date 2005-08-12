/*	System Includes
*/
#include <iostream>


/*	OSG Includes
*/
#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

#ifndef OSG_DISABLE_DEPRECATED
#include "OSGSharedLibrary.h"
#endif

/*	General Settings
*/


int main( OSG::Int32 argc, OSG::Char8** argv)
{
	// Init OSG

	OSG::osgInit(argc, argv);

#ifndef OSG_DISABLE_DEPRECATED

#ifdef WIN32
    OSG::SharedLibrary  oSharedGLLib("opengl32.dll");
    OSG::SharedLibrary *pSharedGLUTLib = new OSG::SharedLibrary;
#else
    OSG::SharedLibrary  oSharedGLLib("libGL.so");
    OSG::SharedLibrary *pSharedGLUTLib = new OSG::SharedLibrary;
#endif

    pSharedGLUTLib->open("libGLU.so");


    OSG::AnonSymbolHandle hSym  = 
        oSharedGLLib.getSymbol("glBegin");
    OSG::AnonSymbolHandle hSym1 = 
        pSharedGLUTLib->getSymbol("gluCylinder");

    fprintf(stderr, "%p | %p\n", hSym, hSym1);
	
#endif // #ifndef OSG_DISABLE_DEPRECATED
        
	return 0;
}
