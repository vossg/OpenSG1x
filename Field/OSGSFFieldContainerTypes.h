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


#ifndef _OSGSFFIELDCONTAINERTYPES_H_
#define _OSGSFFIELDCONTAINERTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGContainerFieldDataType.h>

/** \file OSGSFFieldContainerTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG field container single fields
 *
 * <UL>
 * <LI> osg::OSGSFFieldContainerPtr
 * <LI> osg::OSGSFNodePtr
 * <LI> osg::OSGSFNodeCorePtr
 * <LI> osg::OSGSFPropertyPtr
 * <LI> osg::OSGSFAttachmentMap;
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGSFFieldContainerPtr
 */

typedef OSGSField<OSGFieldContainerPtr> OSGSFFieldContainerPtr;

/** \brief OSGSFNodePtr
 */

typedef OSGSField<OSGNodePtr>           OSGSFNodePtr;

/** \brief OSGSFNodeCorePtr
 */

typedef OSGSField<OSGNodeCorePtr>       OSGSFNodeCorePtr;

/** \brief OSGSFAttachmentMap
 */

typedef OSGSField<OSGAttachmentMap>     OSGSFAttachmentMap;


OSG_END_NAMESPACE

#endif /* _OSGSFFIELDCONTAINERTYPES_H_ */
