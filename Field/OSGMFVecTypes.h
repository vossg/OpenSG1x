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


#ifndef _OSGMFVECTYPES_H_
#define _OSGMFVECTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGVecFieldDataType.h>

/** \file OSGMFVecTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG vector and point multi fields
 * 
 *  <UL>
 *  <LI> osg::OSGMFVec2f
 *  <LI> osg::OSGMFVec3f
 *  <LI> osg::OSGMFVec4f
 *  <LI> osg::OSGMFVec4ub
 *  <LI> osg::OSGMFPnt2f
 *  <LI> osg::OSGMFPnt3f
 *  <LI> osg::OSGMFPnt4f
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGMFVec2f
 */

typedef OSGMField<OSGVec2f> OSGMFVec2f;

/** \brief OSGMFVec3f
 */

typedef OSGMField<OSGVec3f> OSGMFVec3f;

/** \brief OSGMFVec4f
 */

typedef OSGMField<OSGVec4f> OSGMFVec4f;

/** \brief OSGMFVec4ub
 */

typedef OSGMField<OSGVec4ub> OSGMFVec4ub;

/** \brief OSGMFPnt3f
 */

typedef OSGMField<OSGPnt2f> OSGMFPnt2f;

/** \brief OSGMFPnt3f
 */

typedef OSGMField<OSGPnt3f> OSGMFPnt3f;

/** \brief OSGMFPnt3f
 */

typedef OSGMField<OSGPnt4f> OSGMFPnt4f;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
