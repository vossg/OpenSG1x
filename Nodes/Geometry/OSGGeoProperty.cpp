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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGGeoProperty.h"

OSG_USING_NAMESPACE

// explicit instantiation to work around compiler problems with static
// init for templated classes

#ifdef OSG_NEED_EXPLICIT_INST_FOR_STATIC

template class OSGAbstractGeoProperty<OSGGeoPositionPropertyDesc>;
template class OSGGeoProperty<OSGGeoPosition3fPropertyDesc>;

template class OSGAbstractGeoProperty<OSGGeoNormalPropertyDesc>;
template class OSGGeoProperty<OSGGeoNormal3fPropertyDesc>;

template class OSGAbstractGeoProperty<OSGGeoIndexPropertyDesc>;
template class OSGGeoProperty<OSGGeoIndexUI32PropertyDesc>;

template class OSGGeoProperty<OSGGeoPTypePropertyDesc>;

template class OSGGeoProperty<OSGGeoPLengthPropertyDesc>;

#endif


///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

