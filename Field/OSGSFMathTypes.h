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


#ifndef _OSGSFMATHTYPES_H_
#define _OSGSFMATHTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGMathFieldDataType.h>

/** \file OSGSFMathTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG math single fields
 *
 *  <UL>
 *  <LI> osg::OSGSFMatrix
 *  <LI> osg::OSGSFQuaternion
 *  </UL>
 */

OSG_BEGIN_NAMESPACE


/** \brief OSGSFMatrix
 */

typedef OSGSField<OSGMatrix>     OSGSFMatrix;

/** \brief OSGSFQuaternion
 */

typedef OSGSField<OSGQuaternion> OSGSFQuaternion;

OSG_END_NAMESPACE

#endif /* _OSGSFMATHBASE_H_ */





