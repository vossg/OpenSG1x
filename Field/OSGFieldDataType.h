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


#ifndef _OSG_FIELDDATATYPE_H_
#define _OSG_FIELDDATATYPE_H_

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

/** \file OSGFieldDataType.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OpenSG Field Data Types  
*/

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Documentation dummy
 */

struct OSGTraits
{
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template <class OSGFieldTypeT>
struct OSGFieldDataTraits : public OSGTraits
{
};

OSG_END_NAMESPACE

#endif /* _OSG_FIELDDATATYPE_H_ */
