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

#ifndef _OSGACTORDESC_H_
#define _OSGACTORDESC_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGActorDescConstants.h"

#include <string>
#include <vector>

OSG_USING_NAMESPACE

class ActorStateElemDesc;

class ActorDesc
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef std::vector<ActorStateElemDesc> StateElemList;
    typedef StateElemList::iterator         StateElemListIt;
    typedef StateElemList::const_iterator   StateElemListConstIt;

    typedef ActorDescConstants::FunctorStoreE FunctorStoreE;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    ActorDesc(void                                   );
    ActorDesc(const std::string   &actorName,
              const std::string   &parentName,
              const std::string   &libraryName,
                    FunctorStoreE  enterFunctorStore,
                    FunctorStoreE  leaveFunctorStore,
                    bool           useLocalIncludes,
                    bool           systemComponent,
                    bool           parentSystemComponent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    ~ActorDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Clear                                                     */
    /*! \{                                                                 */

    void clear(void);
    void dump (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Get / Set                                                 */
    /*! \{                                                                 */

    const std::string &getActorName  (void                          ) const;
    void               setActorName  (const std::string &actorName  );

    const std::string &getParentName (void) const;
    void               setParentName (const std::string &parentName );

    const std::string &getLibraryName(void                          ) const;
    void               setLibraryName(const std::string &libraryName);

    bool          getUseLocalIncludes    (void) const;
    std::string   getUseLocalIncludesStr (void) const;
    void          setUseLocalIncludes    (bool               useLocalIncludes );
    void          setUseLocalIncludes    (const std::string &useLocalIncludes );

    bool          getSystemComponent     (void) const;
    std::string   getSystemComponentStr  (void) const;
    void          setSystemComponent     (bool               systemComponent  );
    void          setSystemComponent     (const std::string &systemComponent  );

    bool          getParentSystemComponent(void) const;
    std::string   getParentSystemComponentStr(void) const;
    void          setParentSystemComponent(bool               parentSystemComponent);
    void          setParentSystemComponent(const std::string &parentSystemComponent);

    FunctorStoreE getEnterFunctorStore   (void) const;
    std::string   getEnterFunctorStoreStr(void) const;
    void          setEnterFunctorStore   (FunctorStoreE      enterFunctorStore);
    void          setEnterFunctorStore   (const std::string &enterFunctorStore);

    FunctorStoreE getLeaveFunctorStore   (void) const;
    std::string   getLeaveFunctorStoreStr(void) const;
    void          setLeaveFunctorStore   (FunctorStoreE      leaveFunctorStore);
    void          setLeaveFunctorStore   (const std::string &leaveFunctorStore);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    State Element Access                                      */
    /*! \{                                                                 */

    StateElemListConstIt beginStateElems(void) const;
    StateElemListIt      beginStateElems(void);

    StateElemListConstIt endStateElems  (void) const;
    StateElemListIt      endStateElems  (void);

    const StateElemList &getStateElemList(void) const;
          StateElemList &getStateElemList(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    std::string   _actorName;
    std::string   _parentName;
    std::string   _libraryName;
    bool          _useLocalIncludes;
    bool          _systemComponent;
    bool          _parentSystemComponent;

    FunctorStoreE _enterFunctorStore;
    FunctorStoreE _leaveFunctorStore;

    StateElemList _stateElems;
};

//#include "OSGActorDesc.inl"

#define OSGACTORDESC_HEADER_CVSID "@(#)$Id: OSGActorDesc.h,v 1.1 2004/04/20 13:06:50 neumannc Exp $"

#endif /* _OSGACTORDESC_H_ */
