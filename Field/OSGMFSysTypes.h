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


#ifndef _OSGMFSYSTYPES_H_
#define _OSGMFSYSTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGSysFieldDataType.h>

/** \file OSGMFSysTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG system multi fields
 *
 *  <UL>
 *  <LI> osg::OSGMFBool
 *  <LI> osg::OSGMFInt8
 *  <LI> osg::OSGMFUInt8
 *  <LI> osg::OSGMFInt16
 *  <LI> osg::OSGMFUInt16
 *  <LI> osg::OSGMFInt32
 *  <LI> osg::OSGMFUInt32
 *  <LI> osg::OSGMFInt64
 *  <LI> osg::OSGMFUInt64
 *  <LI> osg::OSGMFReal32
 *  <LI> osg::OSGMFReal64
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGMFBool
 */

typedef OSGMField<OSGBool>   OSGMFBool;


/** \brief OSGMFInt8
 */

typedef OSGMField<OSGInt8>   OSGMFInt8;

/** \brief OSGMFUInt8
 */

typedef OSGMField<OSGUInt8>  OSGMFUInt8;


/** \brief OSGMFInt16
 */

typedef OSGMField<OSGInt16>  OSGMFInt16;

/** \brief OSGMFUInt16
 */

typedef OSGMField<OSGUInt16> OSGMFUInt16;


/** \brief OSGMFInt32
 */

typedef OSGMField<OSGInt32>  OSGMFInt32;

/** \brief OSGMFUInt32
 */

typedef OSGMField<OSGUInt32> OSGMFUInt32;


/** \brief OSGMFInt64
 */

typedef OSGMField<OSGInt64>  OSGMFInt64;

/** \brief OSGMFUInt64
 */

typedef OSGMField<OSGUInt64> OSGMFUInt64;


/** \brief OSGMFReal32
 */

typedef OSGMField<OSGReal32> OSGMFReal32;

/** \brief OSGMFReal64
 */

typedef OSGMField<OSGReal64> OSGMFReal64;

OSG_END_NAMESPACE

#endif /* _OSGSFSYSTYPES_H_ */

















