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
 * <LI> osg::OSGMFTime
 * <LI> osg::OSGMFColor3f
 * <LI> osg::OSGMFColor4f
 * <LI> osg::OSGMFVolume
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGMFString
 */

typedef OSGMField<OSGString>  OSGMFString;

/** \brief OSGMFTime
 */

typedef OSGMField<OSGTime>    OSGMFTime;

/** \brief OSGMFColor3f
 */

typedef OSGMField<OSGColor3f> OSGMFColor3f;

/** \brief OSGMFColor4f
 */

typedef OSGMField<OSGColor4f> OSGMFColor4f;

/** \brief OSGMFVolume
 */

typedef OSGMField<OSGVolume>  OSGMFVolume;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
