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


#ifndef _OSGSFSYSTYPES_H_
#define _OSGSFSYSTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGSysFieldDataType.h>

/** \file OSGSFSysTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG system single fields
 *
 *  <UL>
 *  <LI> osg::OSGSFBool
 *  <LI> osg::OSGSFInt8
 *  <LI> osg::OSGSFUInt8
 *  <LI> osg::OSGSFInt16
 *  <LI> osg::OSGSFUInt16
 *  <LI> osg::OSGSFInt32
 *  <LI> osg::OSGSFUInt32
 *  <LI> osg::OSGSFInt64
 *  <LI> osg::OSGSFUInt64
 *  <LI> osg::OSGSFReal32
 *  <LI> osg::OSGSFReal64
 *  </UL>
 */

OSG_BEGIN_NAMESPACE


/** \brief OSGSFBool
 */

typedef OSGSField<OSGBool>   OSGSFBool;


/** \brief OSGSFInt8
 */

typedef OSGSField<OSGInt8>   OSGSFInt8;

/** \brief OSGSFUInt8
 */

typedef OSGSField<OSGUInt8>  OSGSFUInt8;


/** \brief OSGSFInt16
 */

typedef OSGSField<OSGInt16>  OSGSFInt16;

/** \brief OSGSFUInt16
 */

typedef OSGSField<OSGUInt16> OSGSFUInt16;


/** \brief OSGSFInt32
 */
typedef OSGSField<OSGInt32>  OSGSFInt32;

/** \brief OSGSFUInt32
 */

typedef OSGSField<OSGUInt32> OSGSFUInt32;


/** \brief OSGSFInt64
 */
typedef OSGSField<OSGInt64>  OSGSFInt64;

/** \brief OSGSFUInt64
 */

typedef OSGSField<OSGUInt64> OSGSFUInt64;


/** \brief OSGSFReal32
 */

typedef OSGSField<OSGReal32> OSGSFReal32;

/** \brief OSGSFReal64
 */

typedef OSGSField<OSGReal64> OSGSFReal64;

OSG_END_NAMESPACE

#endif /* _OSGSFSYSTYPES_H_ */

















