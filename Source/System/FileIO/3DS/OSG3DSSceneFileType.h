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

#ifndef _OSG3DSSCENEFILETYPE_H_
#define _OSG3DSSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <OSGAction.h>
#include <OSGBaseTypes.h>
#include <OSGGeoPositionsFields.h>
#include <OSGGeometry.h>
#include <OSGNode.h>
#include <OSGSceneFileType.h>
#include <OSGMaterial.h>

#include "OSG3DSLoader.h"

OSG_BEGIN_NAMESPACE

/*!\ingroup GrpSystemDrawablesGeometrymetryLoaderLib
 * \brief InventorSceneFileType
 */

class OSG_SYSTEMLIB_DLLMAPPING A3DSSceneFileType : public osg::SceneFileType
{
public:

    static A3DSSceneFileType &the(void);

    virtual ~A3DSSceneFileType(void);

    virtual const osg::Char8 *getName(void) const;

    virtual osg::NodePtr read(std::istream &is) const;

    virtual bool write(const osg::NodePtr &node, std::ostream &os) const;

protected:

    static const osg::Char8            *_suffixA[];
    static       A3DSSceneFileType  _the;

    A3DSSceneFileType(const osg::Char8  *suffixArray[],
                           OSG::UInt16  suffixByteCount,
                           bool    override,
                           OSG::UInt32  overridePriority);

    A3DSSceneFileType(const A3DSSceneFileType &obj);

private:

    OSG::NodePtr createMesh(L3DS &scene, LMesh &mesh) const;
    MaterialPtr createMaterial(L3DS &scene, OSG::UInt32 id) const;

    mutable std::map<OSG::UInt32, OSG::MaterialPtr> _materials;
    typedef std::map<OSG::UInt32, OSG::MaterialPtr>::iterator materialIt;
};

typedef A3DSSceneFileType* A3DSSceneFileTypeP;

OSG_END_NAMESPACE

#define OSG3DSSCENEFILETYPE_HEADER_CVSID "@(#)$Id: OSG3DSSceneFileType.h,v 1.1 2003/08/14 13:24:48 a-m-z Exp $"

#endif // _OSG3DSSCENEFILETYPE_H_
