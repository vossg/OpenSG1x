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

#ifndef _OSGSIMPLEFUNCTORSTORE_H_
#define _OSGSIMPLEFUNCTORSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewActionTypes.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING SimpleFunctorStore
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

    inline  SimpleFunctorStore  (      void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    inline ~SimpleFunctorStore  (      void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Empty                                                     */
    /*! \{                                                                 */

    inline bool     empty       (      void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Functor Registration                                      */
    /*! \{                                                                 */

    inline void     regFunctor  (const Functor &refFunc);
    inline void     unregFunctor(      void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Functor Access                                            */
    /*! \{                                                                 */

    inline Functor *getFunctor  (      void            );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    Functor _func;
    bool    _bHasFunctor;
};

OSG_END_NAMESPACE

#include "OSGSimpleFunctorStore.inl"

#define OSGSIMPLEFUNCTORSTORE_HEADER_CVSID "@(#)$Id: OSGSimpleFunctorStore.h,v 1.4 2004/04/20 13:47:08 neumannc Exp $"

#endif /* _OSGSIMPLEFUNCTORSTORE_H_ */
