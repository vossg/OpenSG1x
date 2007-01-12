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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>
#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>
#include <OSGSimpleMaterial.h>

#include "OSGBINSceneFileType.h"
#include "OSGBINLoader.h"
#include "OSGBINWriter.h"

OSG_USING_NAMESPACE

/*! \class osg::BINSceneFileType
    \ingroup GrpSystemFileIO

    Binary file type
 */

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning(disable : 383)
#endif

/*-------------------------------------------------------------------------*/
/*                            static get                                   */

/*! get instance
 */
BINSceneFileType &BINSceneFileType::the(void)
{
    return _the;
}

/*-------------------------------------------------------------------------*/
/*                            destructor                                   */

/*! destructor
 */
BINSceneFileType::~BINSceneFileType(void)
{
    return;
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                            read                                         */

/*! read filename
 */
NodePtr BINSceneFileType::read(std::istream &is, const Char8 *) const
{
    BINLoader loader(is);
    loader.read();
    return loader.getRootNode();
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                            write                                        */

/*! write node and its subtree to the given fileName
 */
bool BINSceneFileType::write(const NodePtr &node,
                             std::ostream &os, const Char8 *) const
{
    BINWriter writer(os);
    return writer.write(node);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! constructor
 */
BINSceneFileType::BINSceneFileType(const Char8 *suffixArray[],
                                   UInt16 suffixByteCount, bool override,
                                   UInt32 overridePriority,
                                   UInt32 flags) :
        SceneFileType(suffixArray, suffixByteCount, override, overridePriority,
                      flags)
{
}

/*! copy constructor
 */
BINSceneFileType::BINSceneFileType(const BINSceneFileType &obj) :
    SceneFileType(obj)
{
    return;
}

/*! get name
 */
const Char8 *BINSceneFileType::getName(void) const
{
    return "OpenSG Binary Geometry";
}

/*-------------------------------------------------------------------------*/
/*                              static elements                            */

const Char8 *    BINSceneFileType::_suffixA[] = { "bin" };
BINSceneFileType BINSceneFileType:: _the(_suffixA,
                                         sizeof(_suffixA), false, 10,
                                         OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED);

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8    cvsid_cpp[] = "@(#)$Id: $";
    static Char8    cvsid_hpp[] = OSGBINSCENEFILETYPE_HEADER_CVSID;
}
