/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
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

#ifndef _OSGSINGLEFUNCTORSTORE_H_
#define _OSGSINGLEFUNCTORSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewActionTypes.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING SingleFunctorStore
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef NewActionTypes::Functor Functor;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    inline  SingleFunctorStore(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    inline ~SingleFunctorStore(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Empty                                                     */
    /*! \{                                                                 */

    inline bool empty(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Functor Registration                                      */
    /*! \{                                                                 */

    inline void     regFunctor         (const Functor            &refFunc,
                                        const FieldContainerType &refType);
    inline void     unregFunctor       (      void                       );

    inline void     regDefaultFunctor  (const Functor            &refFunc);
    inline void     unregDefaultFunctor(      void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Functor Access                                            */
    /*! \{                                                                 */

    inline Functor *getFunctor         (const FieldContainerType &refType);
    inline Functor *getDefaultFunctor  (      void                       );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    UInt32  _uiTypeId;

    Functor _func;
    Functor _defaultFunc;

    bool    _bHasFunctor;
    bool    _bHasDefaultFunctor;
};

OSG_END_NAMESPACE

#include "OSGSingleFunctorStore.inl"

#define OSGSINGLEFUNCTORSTORE_HEADER_CVSID "@(#)$Id: OSGSingleFunctorStore.h,v 1.4 2004/04/20 13:47:08 neumannc Exp $"

#endif /* _OSGSINGLEFUNCTORSTORE_H_ */
