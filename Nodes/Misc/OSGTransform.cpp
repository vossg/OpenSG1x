/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, vossg@igd.fhg.de, jbehr@zgdv.de         *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGTransform.h"
#include "OSGDrawAction.h"

OSG_USING_NAMESPACE

/** \fn const char *OSGTransform::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGTransform::Inherited
 *  \brief Parent type
 */

/** \var OSGSFMatrix OSGTransform::_matrix
 *  \brief Transformation matrix
 */

/** \fn OSGTransform::OSGTransform(const OSGTransform &source)
 *  \brief Not implemented.
 */

/** \fn void OSGTransform::operator =(const OSGTransform &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(OSGTransform, OSGMatrixField)
OSG_FC_LAST_FIELD_IDM_DEF (OSGTransform, OSGMatrixField)

char OSGTransform::cvsid[] = "@(#)$Id: $";

/** \brief Group field description
 */

OSGFieldDescription OSGTransform::_desc[] = 
{
    OSGFieldDescription(OSGSFMatrix::getClassType(), 
                        "matrix", 
                        OSG_FC_FIELD_IDM_DESC(OSGMatrixField),
                        false,
                        (OSGFieldAccessMethod) &OSGTransform::getSFMatrix)
};

/** \brief Transform type
 */

OSGFieldContainerType OSGTransform::_type(
    "Transform",
    "NodeCore",
    NULL,
    (OSGPrototypeCreateF) &OSGTransform::createEmpty,
    initMethod,
    _desc,
    sizeof(_desc));


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void OSGTransform::initMethod (void)
{
    OSGDrawAction::registerEnterDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::OSGAction::ResultE,
                                OSGCNodePtr,  
                                OSGTransformPtr, 
                                OSGAction *>(&OSGTransform::drawEnter));
    OSGDrawAction::registerLeaveDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::OSGAction::ResultE,
                                OSGCNodePtr,  
                                OSGTransformPtr, 
                                OSGAction *>(&OSGTransform::drawLeave));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(OSGTransform, OSGTransformPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGTransform::OSGTransform(void) :
    Inherited(),
    _matrix()
{
}

/** \brief Copy Constructor
 */

OSGTransform::OSGTransform(const OSGTransform &source) :
    Inherited(source),
    _matrix(source._matrix)
{
}

/** \brief Destructor
 */

OSGTransform::~OSGTransform(void)
{
}

/*------------------------------ access -----------------------------------*/

/** Returns pointer to the stored matrix field.
 */

OSGSFMatrix *OSGTransform::getSFMatrix(void)
{
    return &_matrix;
}

/** Returns a reference to the stored field.
 */

OSGMatrix &OSGTransform::getMatrix(void)
{
    return _matrix.getValue();
}

/** Returns a reference to the stored field.
 */

const OSGMatrix &OSGTransform::getMatrix(void) const
{
    return _matrix.getValue();
}


void OSGTransform::accumulateMatrix( OSGMatrix & result )
{
    result.mult( getMatrix() );
}

void OSGTransform::adjustVolume( OSGVolume & volume )
{
    volume.transform( _matrix.getValue() );
}

/*------------------------------- dump ----------------------------------*/

void OSGTransform::dump(void) const
{
    SDEBUG << "Dump OSGTransform NI" << endl;
}

    
/** Actions */

// execute the OpenGL commands directly 
OSGAction::ResultE OSGTransform::drawEnter(OSGAction *  )
{
    // should use the chunk, but it's not updated yet
    glPushMatrix();
    glMultMatrixf( getMatrix().getValues() );

    return OSGAction::Continue;
}

OSGAction::ResultE OSGTransform::drawLeave(OSGAction *  )
{
    glPopMatrix();

    return OSGAction::Continue;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

