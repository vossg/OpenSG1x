/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#ifndef _OSGACTORINFO_H_
#define _OSGACTORINFO_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

class StateElemInfo;

/*! \brief ActorInfo class.
           Stores information about an actor, i.e. its name, parent, 
           FunctorStores for enter and leave and a list of StateElemInfos.
*/

class OSG_SYSTEMLIB_DLLMAPPING ActorInfo
{
    /*==========================  PUBLIC  =================================*/
  public:
    enum ActorStoreE
    {
        EmptyStore   = 0,
        SimpleStore  = 1,
        SingleStore  = 2,
        MultiStore   = 3
    };

    typedef std::vector<StateElemInfo>     StateElemBag;
    typedef StateElemBag::iterator         StateElemBagIt;
    typedef StateElemBag::const_iterator   StateElemBagConstIt;

    typedef std::vector<std::string>       ExtraHeaderBag;
    typedef ExtraHeaderBag::iterator       ExtraHeaderBagIt;
    typedef ExtraHeaderBag::const_iterator ExtraHeaderBagConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name                       Constructors                           */
    /*! \{                                                                 */

    ActorInfo(const std::string &name                   = "",
              const std::string &parentName             = "ActorBase",
              const std::string &parentHeader           = "OSGActorBase.h",
              const std::string &parentHeaderPrefix     = "",
              const std::string &libName                = "System",
              const std::string &headerPrefix           = "",
                    ActorStoreE  enterStore             = EmptyStore,
                    ActorStoreE  leaveStore             = EmptyStore,
                    bool         acceptStateAwareIter   = true,
                    bool         acceptStateUnawareIter = true,
                    bool         useLocalIncludes       = false            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set & Get                             */
    /*! \{                                                                 */

    void               setName         (const std::string &name);
    const std::string &getName         (void                   ) const;

    void               setParentName   (const std::string &parentName);
    const std::string &getParentName   (void                          ) const;

    void               setParentHeader (const std::string &parentHeader);
    const std::string &getParentHeader (void                           ) const;

    void               setParentHeaderPrefix(const std::string &prefix);
    const std::string &getParentHeaderPrefix(void                     ) const;

    void               setLibName      (const std::string &libName   );
    const std::string &getLibName      (void                         ) const;

    void               setHeaderPrefix (const std::string &headerPrefix);
    const std::string &getHeaderPrefix (void                           ) const;

    void               setEnterStore   (      ActorStoreE  enterStore);
    void               setEnterStore   (const std::string &enterStore);
    ActorStoreE        getEnterStore   (void                         ) const;
    const std::string &getEnterStoreStr(void                         ) const;

    void               setLeaveStore   (      ActorStoreE  leaveStore);
    void               setLeaveStore   (const std::string &leaveStore);
    ActorStoreE        getLeaveStore   (void                         ) const;
    const std::string &getLeaveStoreStr(void                         ) const;

    void               setAcceptStateAwareIter  (bool val);
    bool               getAcceptStateAwareIter  (void    ) const;

    void               setAcceptStateUnawareIter(bool val);
    bool               getAcceptStateUnawareIter(void    ) const;

    void               setUseLocalIncludes      (bool val);
    bool               getUseLocalIncludes      (void    ) const;

    void               addStateElem   (const StateElemInfo &stateElem  );

    void               addExtraHeader (const std::string   &extraHeader);

    void               dump(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     State Iterators                          */
    /*! \{                                                                 */

    StateElemBagIt beginStateElems(void);
    StateElemBagIt endStateElems  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Extra Header Iterators                       */
    /*! \{                                                                 */

    ExtraHeaderBagIt   beginExtraHeaders(void);
    ExtraHeaderBagIt   endExtraHeaders  (void);

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/
  private:
    bool mapActorStoreName(const std::string &store, ActorStoreE &outVar);
    void updateStoreStr   (ActorStoreE store, std::string &storeStr     );

    std::string    _name;
    std::string    _parentName;
    std::string    _parentHeader;
    std::string    _parentHeaderPrefix;
    std::string    _libName;
    std::string    _headerPrefix;
    std::string    _enterStoreStr;
    std::string    _leaveStoreStr;
    ActorStoreE    _enterStore;
    ActorStoreE    _leaveStore;
    bool           _acceptStateAwareIter;
    bool           _acceptStateUnawareIter;
    bool           _useLocalIncludes;

    StateElemBag   _stateElems;

    ExtraHeaderBag _extraHeaders;
};

OSG_END_NAMESPACE

#include "OSGActorInfo.inl"

#define OSGACTORINFO_HEADER_CVSID "@(#)$Id: OSGActorInfo.h,v 1.2 2003/10/10 14:27:45 neumannc Exp $"

#endif /* _OSGACTORINFO_H_ */
