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


#ifndef _OSGSFBASETYPES_H_
#define _OSGSFBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGBaseFieldDataType.h>

/** \file OSGSFBaseTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG base single fields
 *
 * <UL>
 * <LI> osg::OSGSFString
 * <LI> osg::OSGSFColor
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGSFString
 */

typedef OSGSField<OSGString> OSGSFString;

/** \brief OSGSFColor3f
 */

typedef OSGSField<OSGColor3f> OSGSFColor3f;

/** \brief OSGSFColor4f
 */

typedef OSGSField<OSGColor4f> OSGSFColor4f;

/** \brief OSGSFVolume
 */

typedef OSGSField<OSGDynamicVolume> OSGSFVolume;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
