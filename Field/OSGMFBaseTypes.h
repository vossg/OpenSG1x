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


#ifndef _OSGMFBASETYPES_H_
#define _OSGMFBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGBaseFieldDataType.h>

/** \file OSGMFBaseTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG base multi fields
 *
 * <UL>
 * <LI> osg::OSGMFString
 * <LI> osg::OSGMFColor
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGMFString
 */

typedef OSGMField<OSGString> OSGMFString;

/** \brief OSGMFColor3f
 */

typedef OSGMField<OSGColor3f> OSGMFColor3f;

/** \brief OSGMFColor3f
 */

typedef OSGMField<OSGColor3f> OSGMFColor3f;

/** \brief OSGMFVolume
 */

typedef OSGMField<OSGVolume> OSGMFVolume;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
