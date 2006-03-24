/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//-------------------------------
//  Includes
//-------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include "OSGPerformerLoader.h"

#include "OSGPerfSceneFileType.h"

OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


/*! \class osg::PerfSceneFileType
    \ingroup GrpSystemFileIO

 */

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:

const Char8 *PerfSceneFileType::_suffixA[] = {
"3ds","arcinfo","bin","bpoly","breakup","bw","byu","closest","csb",
"ctol","ct","dem","dted",
"dwb","dxf","evt","flt","gds","geoa","gfo","gopt","im","irtp","iv",
"lsa","lsb","medit","m","nff","obj","pegg","pfb","phd","poly",
"post","proc","projtex","pts","rpc","sgf","sgo","so",
"spf","spherepatch3","spherepatch","sphere","sponge","star","stla",
"stlb","subdiv","substclip","sv","trans","tri","ttol","unc","vct"};

PerfSceneFileType PerfSceneFileType::_the(_suffixA, sizeof(_suffixA),
                                          false,    10);



NodePtr PerfSceneFileType::readFile(const Char8 *fileName) const
{
    PerformerLoader l;

    l.setHighestLODOnly(_highestLODOnly);
    
    osg::NodePtr root = l.load(fileName);

    return root;
}


bool PerfSceneFileType::setHighestLODOnly(bool val)
{
    bool oldval = _highestLODOnly;
    _highestLODOnly = val;
    
    return oldval;
}

PerfSceneFileType::PerfSceneFileType(const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority),
    _highestLODOnly(true)
{
    pfInit();
    pfMultiprocess(PFMP_APPCULLDRAW);
    pfConfig();
}

PerfSceneFileType &PerfSceneFileType::the(void)
{
    return _the;
}

const Char8 *PerfSceneFileType::getName(void) const
{
    return "Performer";
}

PerfSceneFileType::PerfSceneFileType(const PerfSceneFileType &obj) :
    SceneFileType(obj),
    _highestLODOnly(obj._highestLODOnly)
{
    return;
}

PerfSceneFileType::~PerfSceneFileType (void )
{
    pfExit();
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGPerfSceneFileType.cpp,v 1.1 2006/03/24 17:06:53 dirk Exp $";
    static Char8 cvsid_hpp[] = OSGPERFSCENEFILETYPE_HEADER_CVSID;
}

