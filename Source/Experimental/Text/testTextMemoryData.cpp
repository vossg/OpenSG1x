// OpenSG Tutorial Example: Text Geometry
//
// This example shows how to use TrueType(tm) Fonts with OSGText
//
#include <fstream>
#include <string>
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include "OSGLog.h"

#ifndef WIN32

// Headers
#include <OSGSimpleGeometry.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGGeometry.h>
#include <OSGPathHandler.h>

#ifdef OSG_WITH_FREETYPE1
#include "OSGFontStyleFactory.h"
#include "OSGTXFFont.h"
#include "OSGTXFFontStyle.h"
#include "OSGTTFontStyle.h"
#include "OSGText.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    int retCode = 0;
    Real32 size = 1;
    
    if(argc < 3)
    {
        FFATAL(("Usage: %s [-s size] <ttf-file> <outfile>\n", argv[0]));
        return -1;
    }

    // OSG init
    osgInit(argc, argv);

    if(!strcmp(argv[1], "-s"))
    {
        size = atof(argv[2]);
        argv += 2;
        argc -= 2;
    }
    
    PathHandler paths;
    paths.push_backPath(".");

    // create the scene
    // build a standard txf-font
    FontStyle   *fontStyle = FontStyleFactory::the().create(paths, argv[1],
                                size);
    assert(fontStyle);
    ((TTFontStyle *) fontStyle)->createTXFMap();

    // write it somewhere
    std::ostrstream  target;
    fontStyle->dump(target);

    FLOG(("Font size: %d byte\n", target.pcount()));

    std::ofstream    out(argv[2]);
    if(out.eof() == false)
    {
        UChar8    *data = (UChar8 *) target.str();

        out << "UInt32 fontDataSize = " << target.pcount() << ";"
            << std::endl;
        out << "UChar8 fontData[" << target.pcount() << "] = {";
        for(UInt32 i = 0; i < target.pcount(); i++)
        {
            if((i % 20) == 0)
                out << std::endl;
            out << int(data[i]);
            if(i < target.pcount() - 1)
                out << ",";
        }

        out << std::endl << "};" << std::endl;
        delete[] data;
        retCode = 0;
    }
    else
    {
        FFATAL(("Can not open %s output file\n"));
        retCode = -2;
    }

    return retCode;
}

#else

/* */
int main(int argc, char **argv)
{
    FFATAL(("Need freeType 1 lib\n"));

    return -1;
}
#endif
#else

/* */
int main(int argc, char **argv)
{
    FFATAL(("Text doesn't work on Windows yet\n"));

    return -1;
}
#endif
