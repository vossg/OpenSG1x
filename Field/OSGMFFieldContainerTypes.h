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


#ifndef _OSGMFFIELDCONTAINERTYPES_H_
#define _OSGMFFIELDCONTAINERTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGContainerFieldDataType.h>

/** \file OSGMFFieldContainerTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG  field container multi fields
 *
 * <UL>
 * <LI> osg::OSGMFFieldContainerPtr
 * <LI> osg::OSGMFNodePtr
 * <LI> osg::OSGMFNodeCorePtr
 * <LI> osg::OSGMFPropertyPtr
 * <LI> osg::OSGMFAttachmentMap
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief OSGMFFieldContainerPtr
 */

typedef OSGMField<OSGFieldContainerPtr> OSGMFFieldContainerPtr;

/** \brief OSGMFNodePtr
 */

typedef OSGMField<OSGNodePtr>           OSGMFNodePtr;

/** \brief OSGMFNodeCorePtr
 */

typedef OSGMField<OSGNodeCorePtr>       OSGMFNodeCorePtr;

/** \brief OSGMFAttachmentMap
 */

typedef OSGMField<OSGAttachmentMap>     OSGMFAttachmentMap;

OSG_END_NAMESPACE

#endif /* _OSGMFFIELDCONTAINERTYPES_H_ */
