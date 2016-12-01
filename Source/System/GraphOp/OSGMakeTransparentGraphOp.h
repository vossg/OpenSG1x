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


#ifndef _OSGMAKETRANSPARENTGRAPHOP_H_
#define _OSGMAKETRANSPARENTGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include <list>
#include <map>

#include "OSGConfig.h"

#include "OSGSystemDef.h"
#include "OSGGraphOp.h"
#include "OSGAction.h"
#include "OSGGeometry.h"
#include "OSGMaterialGroup.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING MakeTransparentGraphOp : public GraphOp
{
public:
    class MaterialObject
    {
    public:
        MaterialObject(GeometryPtr geo)
        {
            _geo = geo;
        }

        MaterialObject(MaterialGroupPtr mg)
        {
            _mg = mg;
        }

        MaterialPtr getMaterial()
        {
            return (_geo != osg::NullFC
                    ? _geo->getMaterial()
                    : _mg->getMaterial());
        }

        void setMaterial(MaterialPtr mat)
        {
            if (_geo != osg::NullFC)
            {
                beginEditCP(_geo);
                _geo->setMaterial(mat);
                endEditCP(_geo);
            }
            else
            {
                beginEditCP(_mg);
                _mg->setMaterial(mat);
                endEditCP(_mg);
            }
        }

    private:
        GeometryPtr _geo;
        MaterialGroupPtr _mg;
    };

    static const char *getClassname(void) { return "MakeTransparentGraphOp"; };

    MakeTransparentGraphOp(const char* name = "MakeTransparent");

    GraphOp* create();

    bool traverse(NodePtr& node);

    void setParams(const std::string params);
    
    std::string usage(void);

private:
    Action::ResultE traverseEnter(NodePtr& node);
    Action::ResultE traverseLeave(NodePtr& node, Action::ResultE res);

    void addObject(MaterialObject m);
    void applyTransparency(MaterialPtr m);

    typedef std::list<MaterialObject> MaterialObjectList;
    typedef std::map<MaterialPtr, MaterialObjectList> MaterialObjectMap;

    MaterialObjectMap _materialObjects;
    
    Real32 _transparency;
};

OSG_END_NAMESPACE

#endif
