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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>
#include <set>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerFactory.h>
#include <OSGChangeList.h>
#include <OSGConnection.h>
#include <OSGTypedFunctors.h>
#include <OSGStatCollector.h>
#include <OSGStatElemTypes.h>

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
        SUBREFED  =7
    };
    /** functor called for changed containers **/

    typedef ArgsCollector<RemoteAspect *> FunctorArgs;

    typedef TypedFunctor2Base<bool, 
                              CPtrRefCallArg<FieldContainerPtr>, 
                              FunctorArgs                      > Functor;

    /** Map of received containers **/
    typedef std::map<UInt32,UInt32>    ReceivedFCT;
    /** Map of received types **/
    typedef std::map<UInt32,UInt32>    ReceivedTypeT;
    /** Field filter map **/
    typedef std::map<UInt32,BitVector> FieldFilterT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RemoteAspect();
    virtual ~RemoteAspect(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Remote aspect functionaliy                 */
    /*! \{                                                                 */

    void receiveSync       ( Connection &connection,
                             bool applyToChangelist=false   );
    void sendSync          ( Connection &connection,
                             ChangeList *changeList=NULL    );
    void registerCreated   ( const FieldContainerType &type, 
                             const Functor &func            );
    void registerDestroyed ( const FieldContainerType &type, 
                             const Functor &func            );
    void registerChanged   ( const FieldContainerType &type, 
                             const Functor &func            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistics                                 */
    /*! \{                                                                 */

    void           setStatistics(StatCollector * stat  );

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** remote id to fieldcontainer mapping **/
    ReceivedFCT                       _receivedFC;
    /** remote typeid mapping **/
    ReceivedTypeT                     _receivedType;
    /** is type mapped **/
    std::set<UInt32>                  _sentType;
    /** mapped fieldcontainer with mask **/
    std::map<UInt32,BitVector>        _sentFC;
    /** fild filter **/
    FieldFilterT                      _fieldFilter;
    std::vector<Functor>              _createdFunctors;
    std::vector<Functor>              _destroyedFunctors;
    std::vector<Functor>              _changedFunctors;
    StatCollector                    *_statistics;
    
    void   send          ( Connection &connection    );
    void   receive       ( Connection &connection    );
    bool   callCreated   ( FieldContainerPtr &node   );
    bool   callDestroyed ( FieldContainerPtr &node   );
    bool   callChanged   ( FieldContainerPtr &node   );

    /*==========================  PRIVATE  ================================*/
  private:

    friend class RemoteAspectFieldContainerMapper;
	static char cvsid[];

    static bool _defaultCreatedFunction(FieldContainerPtr& fcp,
                                                      RemoteAspect * aspect);
    static bool _defaultDestroyedFunction(FieldContainerPtr& fcp,
                                                      RemoteAspect * aspect);
    static bool _defaultChangedFunction(FieldContainerPtr& fcp,
                                                      RemoteAspect * aspect);

    static StatElemDesc<StatTimeElem> statSyncTime;

	// prohibit default functions (move to 'public' if you need one)
    RemoteAspect(const RemoteAspect &source);
    RemoteAspect &operator =(const RemoteAspect &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef RemoteAspect *RemoteAspectP;

struct RemoteAspectFieldContainerMapper:public FieldContainerMapper
{                                              
    virtual UInt32 map(UInt32 uiId);
    RemoteAspect *_remoteAspect;
};

OSG_END_NAMESPACE

#endif /* _REMOTEASPECT_H_ */
