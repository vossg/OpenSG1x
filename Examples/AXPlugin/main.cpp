/****************************************************************************
** $Id: main.cpp,v 1.2 2004/06/18 14:31:18 a-m-z Exp $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/
//
// Qt OpenGL example: Box
//
// A small example showing how a GLWidget can be used just as any Qt widget
// 
// File: main.cpp
//
// The main() function 
// 

#include "OSGAXPlugin.h"
#include <qapplication.h>
#include <qgl.h>
#include <qmessagebox.h>

#include <qaxfactory.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>

#ifdef OSG_GV_BETA
#define EXPERIMENTAL_VRML_LOADER
#endif

#ifdef EXPERIMENTAL_VRML_LOADER
#include <OpenSG/OSGVRMLSceneFileType.h>
#endif

#ifdef HAS_CGCHUNK
#include <OpenSG/OSGCGChunk.h>
#endif

QAXFACTORY_DEFAULT( OSGAXPlugin, 
            "{7CDDF9C3-F9DD-4245-ADF3-965DA5998FE4}",
            "{D5DFDF01-A3C3-4bb0-A397-E55F5CAEC78B}",
            "{C04774DD-2DFC-4241-835B-6B2FAA0D76CF}",
            "{985F43A2-49D0-48c1-A7B8-2178587FF2FF}",
            "{7687FBB9-FFA7-4cb9-A974-E32F15444CF5}"
            )


/*
  The main program is here. 
*/

int main(int argc, char **argv)
{
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a(argc,argv);

    if(!QGLFormat::hasOpenGL())
    {
        qWarning( "This system has no OpenGL support. Exiting." );
        return -1;
    }

    // init OpenSG
    //OSG::ChangeList::setReadWriteDefault();
    OSG::osgInit(argc, argv);
    
#if defined(EXPERIMENTAL_VRML_LOADER) && !defined(__sgi)
    OSG::VRMLSceneFileType::the();
#endif

#ifdef HAS_CGCHUNK
    // without the printf O2 optimizes it away.
    printf("Class id %d\n", OSG::CGChunk::getClassTypeId());
#endif

    int r;
    
    if(!QAxFactory::isServer())
    {
        OSGAXPlugin *w = new OSGAXPlugin;
        w->resize(640, 512);
        a.setMainWidget(w);
        w->show();
        r = a.exec();
        // we have to delete it before osgExit!
        delete w;
        OSG::osgExit();
        return r;
    }
    
    r = a.exec();
    OSG::osgExit();
    return r;
}
