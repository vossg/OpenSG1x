/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include "OSGField.h"
#include "OSGFieldFactory.h"

OSG_USING_NAMESPACE

/** \fn const char *OSGField::getClassname(void)
 *  \brief Classname
 */

/** \var OSGField::OSGCardinality
 *  \brief Cardinality of the field
 */

/** \var OSGField::Cardinality OSGField::OSGSINGLE_FIELD
 *  \brief Single field
 */

/** \var OSGField::Cardinality OSGField::OSGMULTI_FIELD
 *  \brief Mulit field
 */

/** \fn void OSGField::setValueByStr(char *str)
 * \brief Set value from string
 */

/** \fn OSGString &OSGField::getStrValue(OSGString &string) const
 *  \brief Dump the field to a given string
 */

/** \fn void OSGField::operator =(const OSGField &source)
 *  \brief Not implemented.
 */

/** \fn const OSGFieldType &OSGField::getType(void) const
 *  \brief Get field type
 */

/** \fn OSGUInt32 OSGField::size(void) const
 *  \brief Returns the size of the field, allway 1 for single fields.
 */

/** \fn Cardinality OSGField::getCardinality(void) const
 *  \brief Returns the cardinality of the field
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGField::cvsid[] = "@(#)$Id: $";

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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGField::OSGField(void)
{
}

/** \brief Copy Constructor
 */

OSGField::OSGField(const OSGField &source)
{
}

/** \brief Destructor
 */

OSGField::~OSGField(void)
{
}

/*-------------------------- field information ------------------------------*/

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

