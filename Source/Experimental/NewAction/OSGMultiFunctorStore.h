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

#ifndef _OSGMULTIFUNCTORSTORE_H_
#define _OSGMULTIFUNCTORSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewActionTypes.h"

#include <list>
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING MultiFunctorStore
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

    inline  MultiFunctorStore(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    inline ~MultiFunctorStore(void);

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
    inline void     unregFunctor       (const FieldContainerType &refType);

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
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef std::list<Functor>           FunctorStore;
    typedef FunctorStore::iterator       FunctorStoreIt;
    typedef FunctorStore::const_iterator FunctorStoreConstIt;

    typedef std::vector<FunctorStoreIt>  FunctorMap;
    typedef FunctorMap::iterator         FunctorMapIt;
    typedef FunctorMap::const_iterator   FunctorMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    FunctorStore _funcStore;
    FunctorMap   _funcMap;

    Functor      _defaultFunc;
    bool         _bHasDefaultFunctor;
};

OSG_END_NAMESPACE

#include "OSGMultiFunctorStore.inl"

#define OSGMULTIFUNCTORSTORE_HEADER_CVSID "@(#)$Id: OSGMultiFunctorStore.h,v 1.4 2004/04/20 13:47:08 neumannc Exp $"

#endif /* _OSGMULTIFUNCTORSTORE_H_ */
