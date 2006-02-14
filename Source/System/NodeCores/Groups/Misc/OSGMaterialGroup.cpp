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

#include <OSGConfig.h>

#include "OSGNodePtr.h"
#include "OSGMaterialGroup.h"
#include "OSGDrawAction.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE

/*! \class osg::MaterialGroup
*/

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void MaterialGroup::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & MaterialFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfMaterial.getValue());
            }
            else
            {
                MaterialPtr pMat = _sfMaterial.getValue();
                
                _sfMaterial.setValue(NullFC);
                
                setMaterial(pMat);
            }
        }
    }

    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void MaterialGroup::dump(      UInt32    uiIndent, 
                         const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MaterialGroup::MaterialGroup(void) :
    Inherited()
{
}

MaterialGroup::MaterialGroup(const MaterialGroup &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MaterialGroup::~MaterialGroup(void)
{
    subRefCP(_sfMaterial.getValue());
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

Action::ResultE MaterialGroup::drawEnter(Action *action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    if(da != NULL && _sfMaterial.getValue() != NullFC &&
       da->getMaterial() == NULL)
    {
        da->setMaterial(&(*(_sfMaterial.getValue())), action->getActNode());
    }

    da->selectVisibles();
    
    return Action::Continue;
}

Action::ResultE MaterialGroup::drawLeave(Action * action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    if(da != NULL && da->getMaterialNode() == action->getActNode())
    {
        da->setMaterial(NULL, NullFC);
    }

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               Render                                    */

Action::ResultE MaterialGroup::renderEnter(Action * action)
{
    RenderAction *da = dynamic_cast<RenderAction *>(action);

    Action::ResultE r = Group::renderEnter(action);

    // ok all children are culled away so we leave
    // immediately and don't set the material!
    if(r == Action::Skip)
        return r;

    if(da != NULL && _sfMaterial.getValue() != NullFC &&
       da->getMaterial() == NULL)
    {
        da->setMaterial(&(*(_sfMaterial.getValue())), action->getActNode());
    }

    return r;
}

Action::ResultE MaterialGroup::renderLeave(Action * action)
{
    RenderAction *da = dynamic_cast<RenderAction *>(action);

    if(da != NULL && da->getMaterialNode() == action->getActNode())
    {
        da->setMaterial(NULL, NullFC);
    }

    return Group::renderLeave(action);
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */
 
void MaterialGroup::initMethod(void)
{
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            MaterialGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&MaterialGroup::drawEnter));

    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            MaterialGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&MaterialGroup::drawLeave));

    RenderAction::registerEnterDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            MaterialGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&MaterialGroup::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            MaterialGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&MaterialGroup::renderLeave));
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
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGMATERIALGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGMATERIALGROUP_INLINE_CVSID;
}
