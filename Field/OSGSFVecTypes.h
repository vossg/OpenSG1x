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


#ifndef _OSGSFVECTYPES_H_
#define _OSGSFVECTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGVecFieldDataType.h>

/** \file OSGSFVecTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG vector and point single fields
 * 
 *  <UL>
 *  <LI> osg::OSGSFVec2f
 *  <LI> osg::OSGSFVec3f
 *  <LI> osg::OSGSFVec4f
 *  <LI> osg::OSGSFPnt2f
 *  <LI> osg::OSGSFPnt3f
 *  <LI> osg::OSGSFPnt4f
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGSFVec2f
 */

typedef OSGSField<OSGVec2f> OSGSFVec2f;

/** \brief OSGSFVec3f
 */

typedef OSGSField<OSGVec3f> OSGSFVec3f;

/** \brief OSGSFVec4f
 */

typedef OSGSField<OSGVec4f> OSGSFVec4f;

/** \brief OSGSFPnt2f
 */

typedef OSGSField<OSGPnt2f> OSGSFPnt2f;

/** \brief OSGSFPnt3f
 */

typedef OSGSField<OSGPnt3f> OSGSFPnt3f;

/** \brief OSGSFPnt4f
 */

typedef OSGSField<OSGPnt4f> OSGSFPnt4f;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
