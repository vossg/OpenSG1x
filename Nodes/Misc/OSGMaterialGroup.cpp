/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGMaterialGroup.h"
#include "OSGDrawAction.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGMaterialGroup.cpp,v 1.16 2002/02/16 03:48:42 vossg Exp $";
    static Char8 cvsid_hpp[] = OSGMATERIALGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGMATERIALGROUP_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::MaterialGroup
*/

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void MaterialGroup::changed(BitVector, ChangeMode)
{
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
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

Action::ResultE MaterialGroup::drawEnter(Action *action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    if(da != NULL && _sfMaterial.getValue() != NullFC)
    {
        da->setMaterial(&(*(_sfMaterial.getValue())));
    }

    da->selectVisibles();
    
    return Action::Continue;
}

Action::ResultE MaterialGroup::drawLeave(Action * action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    if(da != NULL)
    {
        da->setMaterial(NULL);
    }

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               Render                                    */

Action::ResultE MaterialGroup::renderEnter(Action * action)
{
    RenderAction *da = dynamic_cast<RenderAction *>(action);

    if(da != NULL && _sfMaterial.getValue() != NullFC)
    {
        da->setMaterial(&(*(_sfMaterial.getValue())));
    }

    return Action::Continue;
}

Action::ResultE MaterialGroup::renderLeave(Action * action)
{
    RenderAction *da = dynamic_cast<RenderAction *>(action);

    if(da != NULL)
    {
        da->setMaterial(NULL);
    }

    return Action::Continue;
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


