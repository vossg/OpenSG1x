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


#ifndef _OSGMFMATHTYPES_H_
#define _OSGMFMATHTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGMathFieldDataType.h>

/** \file OSGMFMathTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG math multi fields
 *
 *  <UL>
 *  <LI> osg::OSGMFMatrix
 *  <LI> osg::OSGMFQuaternion
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGMFMatrix
 */

typedef OSGMField<OSGMatrix>     OSGMFMatrix;

/** \brief OSGMFQuaternion
 */

typedef OSGMField<OSGQuaternion> OSGMFQuaternion;

OSG_END_NAMESPACE

#endif /* _OSGMFMATHBASE_H_ */
