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


#ifndef _REMOTEASPECT_H_
#define _REMOTEASPECT_H_
#ifdef __sgi
#pragma once
#endif

#include <map>
#include <set>
#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerFactory.h"
#include "OSGChangeList.h"
#include "OSGConnection.h"
#include "OSGTypedFunctors.h"
#include "OSGStatCollector.h"
#include "OSGStatElemTypes.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING RemoteAspect
{ 
    /*==========================  PUBLIC  =================================*/
  public:
    /** Message types */
    enum DataTypes 
    {
        SYNCENDED =1,
        CREATED   =2,
        DESTROYED =3,
        NEWTYPE   =4,
        CHANGED   =5,
        ADDREFED  =6,
        SUBREFED  =7,
        IDMAPPING =8,
        PASSOVER  =9
    };

    /** functor called for changed containers **/
    typedef ArgsCollector<RemoteAspect *> FunctorArgs;
    typedef TypedFunctor2Base<bool, 
                              CPtrRefCallArg<FieldContainerPtr>, 
                              FunctorArgs                      > Functor;

    /** Map remote to local id **/
    typedef std::map<UInt64,UInt32>    LocalFCMapT;
    /** Map local to remote id **/
    typedef std::map<UInt32,UInt64>    RemoteFCMapT;
    /** Map remote to local type **/
    typedef std::map<UInt32,UInt32>    LocalTypeMapT;

    /** id set **/
    typedef std::set<UInt32>           IdSetT;

    /** Field filter map **/
    typedef std::map<UInt32,BitVector> FieldFilterT;
    typedef std::map<UInt32,BitVector> FieldMaskMapT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RemoteAspect(UInt32 aspectId=0);
    virtual ~RemoteAspect(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Remote aspect functionaliy                 */
    /*! \{                                                                 */

    void receiveSync      ( Connection &connection,
                            bool applyToChangelist=false   );
    void sendSync         ( Connection &connection,
                            ChangeList *changeList=NULL    );
    void registerCreated  ( const FieldContainerType &type, 
                            const Functor &func            );
    void registerDestroyed( const FieldContainerType &type, 
                            const Functor &func            );
    void registerChanged  ( const FieldContainerType &type, 
                            const Functor &func            );
    static void addFieldFilter   ( UInt32 typeId,BitVector mask   );
    static void subFieldFilter   ( UInt32 typeId,BitVector mask   );
    
    static FieldFilterT const &getFieldFilter(void         );
    static BitVector           getFieldFilter(UInt32 typeId);
    
    static void restoreChangeList   (ChangeList *tocl);
    static void storeChangeList     (ChangeList *cl  );
    static UInt32 getStoreSize      (void            );

    typedef std::map<UInt32, UInt32> clStoreMap;
    typedef clStoreMap::iterator clStoreIt;
    static clStoreMap &getStore     (void            );

    static void createCurrentStateChangeList(const FieldContainerPtr &start,
                                             ChangeList              *cl    );
    static void createCurrentStateChangeList(ChangeList              *cl    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistics                                 */
    /*! \{                                                                 */

    void setStatistics( StatCollector * stat );

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  static stat elem                            */
    /*! \{                                                                 */
 
    static StatElemDesc<StatTimeElem> statSyncTime;

    /*---------------------------------------------------------------------*/
    /*! \name                   Callbacks                                  */
    /*! \{                                                                 */

    typedef void (*synccbfp)(const std::string &msg, Int32 progress);
    void setSendSyncCB(synccbfp fp);

    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                   member                                     */
    /*! \{                                                                 */

    /** Aspect id **/
    UInt32                            _aspectId;

    /** remote id to fieldcontainer mapping **/
    LocalFCMapT                       _localFC;
    /** local to remote fieldcontainer mapping **/
    RemoteFCMapT                      _remoteFC;
    /** remote typeid mapping **/
    LocalTypeMapT                     _localType;

    /** indicates fc was sent **/
    IdSetT                            _sentFC;
    /** indicates fc was received **/
    IdSetT                            _receivedFC;

    /** indicates remote knows this fc **/
    IdSetT                            _mappedFC;
    /** indicates mapped type **/
    IdSetT                            _mappedType;

    UInt32                            _remoteAspectId;

#if 0
    /** mapped fieldcontainer with mask **/
    std::map<UInt32,BitVector>        _sentFC;
#endif

    /** fild filter **/
    static FieldFilterT               _fieldFilter;
    std::vector<Functor>              _createdFunctors;
    std::vector<Functor>              _destroyedFunctors;
    std::vector<Functor>              _changedFunctors;
    StatCollector                    *_statistics;

    synccbfp                          _sendSyncFP;

    static std::map<UInt32, UInt32>   _clStore;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 protected helper functions                   */
    /*! \{                                                                 */

    bool   callCreated   ( FieldContainerPtr &node   );
    bool   callDestroyed ( FieldContainerPtr &node   );
    bool   callChanged   ( FieldContainerPtr &node   );

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name                 Helper functions                             */
    /*! \{                                                                 */

    void handleFCMapping   (Connection &connection               );
    void clearFCMapping    (UInt32 localId,UInt32 remoteId       );
    bool getLocalId        (UInt32  remoteId,
                            UInt32 &localId                      );
    UInt64 getFullRemoteId (UInt32  remoteId                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 static elements                              */
    /*! \{                                                                 */
    static bool _defaultCreatedFunction  (FieldContainerPtr& fcp,
                                          RemoteAspect * aspect);
    static bool _defaultDestroyedFunction(FieldContainerPtr& fcp,
                                          RemoteAspect * aspect);
    static bool _defaultChangedFunction  (FieldContainerPtr& fcp,
                                          RemoteAspect * aspect);

    /*! \}                                                                 */

    friend class RemoteAspectFieldContainerMapper;
	// prohibit default functions (move to 'public' if you need one)
    RemoteAspect(const RemoteAspect &source);
    RemoteAspect &operator =(const RemoteAspect &source);
};

// class pointer
typedef RemoteAspect *RemoteAspectP;

struct RemoteAspectFieldContainerMapper:public FieldContainerMapper
{                                              
    virtual UInt32 map(UInt32 uiId);
    RemoteAspect *_remoteAspect;
};

OSG_END_NAMESPACE

#define OSGREMOTEASPECT_HEADER_CVSID "@(#)$Id:$"

#endif /* _REMOTEASPECT_H_ */
