/****************************************************************************
** $Id: main.cpp,v 1.3 2005/02/04 17:46:12 a-m-z Exp $
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

// for static linking
#ifndef OSG_BUILD_DLL

#include <OpenSG/OSGVRMLSceneFileType.h>
#include <OpenSG/OSGOSGSceneFileType.h>
#include <OpenSG/OSGNFIOSceneFileType.h>
#include <OpenSG/OSGNFIOGeneric.h>
#include <OpenSG/OSGNFIOGeometry.h>
#include <OpenSG/OSGNFIOImage.h>

#include <OpenSG/OSGPhongMaterial.h>
#include <OpenSG/OSGDVRVolume.h>
#include <OpenSG/OSGDVRVolumeTexture.h>
#include <OpenSG/OSGDVRIsoSurface.h>
#include <OpenSG/OSGDVRLookupTable.h>
#include <OpenSG/OSGDVRSimpleLUTShader.h>

#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGGeoPropColors.h>
#include <OpenSG/OSGSurface.h>

#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGJPGImageFileType.h>
#include <OpenSG/OSGTIFImageFileType.h>
#include <OpenSG/OSGPNGImageFileType.h>
#include <OpenSG/OSGGIFImageFileType.h>
#include <OpenSG/OSGSGIImageFileType.h>
#include <OpenSG/OSGDATImageFileType.h>
#include <OpenSG/OSGMNGImageFileType.h>
#include <OpenSG/OSGMTDImageFileType.h>
#include <OpenSG/OSGPNMImageFileType.h>
#include <OpenSG/OSGTGAImageFileType.h>

#endif
// -------------------------

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

static void initializeStatics(void)
{
    // for static linking
#ifndef OSG_BUILD_DLL
    
    printf("VRML: %p\n", OSG::VRMLSceneFileType::the());
    printf("OSG: %p\n", OSG::OSGSceneFileType::the());
    printf("OSB: %p\n", OSG::NFIOSceneFileType::the());
    new OSG::NFIOGeneric;
    new OSG::NFIOGeometry;
    new OSG::NFIOImage;

    printf("Class id %d\n", OSG::DVRVolume::getClassTypeId());
    printf("Class id %d\n", OSG::DVRVolumeTexture::getClassTypeId());
    printf("Class id %d\n", OSG::DVRIsoSurface::getClassTypeId());
    printf("Class id %d\n", OSG::DVRLookupTable::getClassTypeId());
    printf("Class id %d\n", OSG::DVRSimpleLUTShader::getClassTypeId());

    printf("Class id %d\n", OSG::PhongMaterial::getClassTypeId());
    printf("Class id %d\n", OSG::SHLChunk::getClassTypeId());
    printf("Class id %d\n", OSG::GeoColors3f::getClassTypeId());
    printf("Class id %d\n", OSG::Surface::getClassTypeId());

#ifdef OSG_WITH_JPG
    printf("JPG: %p\n", OSG::JPGImageFileType::the());
#endif
#ifdef OSG_WITH_TIF
    printf("TIF: %p\n", OSG::TIFImageFileType::the());
#endif
#ifdef OSG_WITH_PNG
    printf("PNG: %p\n", OSG::PNGImageFileType::the());
#endif
#ifdef OSG_WITH_GIF
    printf("GIF: %p\n", OSG::GIFImageFileType::the());
#endif

    printf("SGI: %p\n", OSG::SGIImageFileType::the());
    printf("DAT: %p\n", OSG::DATImageFileType::the());
    printf("MNG: %p\n", OSG::MNGImageFileType::the());
    printf("MTD: %p\n", OSG::MTDImageFileType::the());
    printf("PNM: %p\n", OSG::PNMImageFileType::the());
    printf("TGA: %p\n", OSG::TGAImageFileType::the());
    printf("Image %p\n", OSG::ImageFileHandler::the());

#endif
}

/*
  The main program is here. 
*/

int main(int argc, char **argv)
{
    initializeStatics();

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
