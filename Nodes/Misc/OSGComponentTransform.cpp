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

#include "OSGConfig.h"

#include "OSGComponentTransform.h"
#include "OSGDrawAction.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGComponentTransform.cpp,v 1.7 2001/11/09 08:32:08 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGCOMPONENTTRANSFORM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGCOMPONENTTRANSFORM_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::ComponentTransform
*/


/*-------------------------------------------------------------------------*/
/*                               Changed                                   */

void ComponentTransform::changed(BitVector which, ChangeMode mode)
{
    ComponentTransformPtr ptr(*this);

    if(which != MatrixFieldMask)
    {
        beginEditCP(ptr, MatrixFieldMask);
        {
            getMatrix().setTransform(getTranslation     (),
                                     getRotation        (),
                                     getScale           (),
                                     getScaleOrientation(),
                                     getCenter          ());
        }
        endEditCP  (ptr, MatrixFieldMask);
    }
    else
    {
        this->Transform::changed(which, mode);
    }
}
void ComponentTransform::dump(      UInt32    uiIndent, 
                              const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

#ifdef OSG_NOFUNCTORS
Action::ResultE ComponentTransform::ComponentTransformDrawEnter(
    CNodePtr &cnode, 
    Action   *pAction)
{
    NodeCore           *pNC = cnode.getCPtr();
    ComponentTransform *pTr = dynamic_cast<ComponentTransform *>(pNC);

    if(pTr == NULL)
    {
        fprintf(stderr, "VTRDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pTr->drawEnter(pAction);
    }
}

Action::ResultE ComponentTransform::ComponentTransformDrawLeave(
    CNodePtr &cnode, 
    Action   *pAction)
{
    NodeCore           *pNC = cnode.getCPtr();
    ComponentTransform *pTr = dynamic_cast<ComponentTransform *>(pNC);

    if(pTr == NULL)
    {
        fprintf(stderr, "VTRDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pTr->drawLeave(pAction);
    }
}
#endif


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ComponentTransform::ComponentTransform(void) :
    Inherited()
{
    _sfScale.getValue().setValues(1.f, 1.f, 1.f);         
}

ComponentTransform::ComponentTransform(const ComponentTransform &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ComponentTransform::~ComponentTransform(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void ComponentTransform::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  ComponentTransformPtr, 
                                  Action *>(&ComponentTransform::drawEnter));

    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  ComponentTransformPtr, 
                                  Action *>(&ComponentTransform::drawLeave));


    RenderAction::registerEnterDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  ComponentTransformPtr, 
                                  Action *>(&ComponentTransform::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  ComponentTransformPtr, 
                                  Action *>(&ComponentTransform::renderLeave));


    IntersectAction::registerEnterDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                 CNodePtr,  
                                 ComponentTransformPtr, 
                                 Action*>(&ComponentTransform::intersectEnter));

    IntersectAction::registerLeaveDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                 CNodePtr,  
                                 ComponentTransformPtr, 
                                 Action*>(&ComponentTransform::intersectLeave));
    
#else

    DrawAction::registerEnterDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(
            ComponentTransform::ComponentTransformDrawEnter));
    
    DrawAction::registerLeaveDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(
            ComponentTransform::ComponentTransformDrawLeave));
#endif
}




