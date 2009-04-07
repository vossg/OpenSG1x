/*---------------------------------------------------------------------------*\
 *                        OpenSG openNURBS SceneFileType                     *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2007-2008 by Seac02 S.r.l.     http://www.seac02.it         *
 * Copyright (C) 2008  by Patrik Mueller    muellerptr@users.sourceforge.net *
 * Copyright (C) 2008  by Akos Balazs       edhellon@cs.uni-bonn.de          *
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

#include <OSGConfig.h>

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include "OSGSceneFileHandler.h"
#include "OSGRhinoSceneFileType.h"

#include "OSGrhino2osb.h"

OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


/*! \class osg::RhinoSceneFileType
    \ingroup GrpSystemFileIO

 */

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:

const Char8 *RhinoSceneFileType::_suffixA[] = {
"3dm"};

RhinoSceneFileType RhinoSceneFileType::_the(_suffixA, sizeof(_suffixA),
                                          false,    10);

NodePtr RhinoSceneFileType::read3DM(const Char8  *fileName) const
{
    rhino2osb ro(m_curveInterpolationSteps, m_tessellationError, m_bDoTessellation, SceneFileHandler::the().getOptions(_suffixA[0]));
    osg::NodePtr root = ro.load(fileName);
    return root;
}

// Parameter handling for the rhino loader
void RhinoSceneFileType::setDoTessellation(bool doTessellation)
{
    m_bDoTessellation = doTessellation;
}

void RhinoSceneFileType::setTessellationError(float tessellationError)
{
    if ( tessellationError > 0 )
    {
        m_tessellationError = tessellationError;
    }
}

void RhinoSceneFileType::setCurveInterpolationSteps(int steps)
{
    if ( steps > 0 )
    {
        m_curveInterpolationSteps = steps;
    }    
}
                
                
NodePtr RhinoSceneFileType::readFile(const Char8 *fileName) const
{
    return read3DM(fileName);
}

NodePtr RhinoSceneFileType::read(std::istream &, const Char8 *fileNameOrExtension) const
{
    return read3DM(fileNameOrExtension);
}

RhinoSceneFileType::RhinoSceneFileType(const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority),
    m_curveInterpolationSteps(100),
    m_tessellationError(0.1f),
    m_bDoTessellation(true)
{
}

RhinoSceneFileType &RhinoSceneFileType::the(void)
{
    return _the;
}

const Char8 *RhinoSceneFileType::getName(void) const
{
    return "Rhinoceros3D";
}

RhinoSceneFileType::RhinoSceneFileType(const RhinoSceneFileType &obj) :
    SceneFileType(obj) 
{
    return;
}

RhinoSceneFileType::~RhinoSceneFileType (void )
{
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGRhinoSceneFileType.cpp,v 1.3 2009/04/07 17:09:28 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGRHINOSCENEFILETYPE_HEADER_CVSID;
}

