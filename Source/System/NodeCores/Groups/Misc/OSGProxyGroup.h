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

#ifndef _OSGPROXYGROUP_H_
#define _OSGPROXYGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include <queue>

#include "OSGConfig.h"
#include "OSGProxyGroupBase.h"
#include "OSGAction.h"
#include "OSGLock.h"

OSG_BEGIN_NAMESPACE

//! ProxyGroup
//! \ingroup GrpSystemNodeCoresMisc

class OSG_SYSTEMLIB_DLLMAPPING ProxyGroup : public ProxyGroupBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum { NOT_LOADED           =   0,
           LOAD_THREAD_RUNNING  =   1,
           LOAD_THREAD_FINISHED =   2,
           LOADED               =   4,
           LOAD_ERROR           = 100 };

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField,
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef ProxyGroupBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ProxyGroup(void);
    ProxyGroup(const ProxyGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ProxyGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    Action::ResultE draw( Action* action );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      NodeCore Specific                       */
    /*! \{                                                                 */

    void               adjustVolume     (Volume & volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     loading                                  */
    /*! \{                                                                 */

    void               startLoading     (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ProxyGroupBase;

    /*---------------------------------------------------------------------*/
    /*! \name                   thread local                               */
    /*! \{                                                                 */

    NodePtr          _loadedRoot;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(      void                     );

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                    load thread                               */
    /*! \{                                                                 */

    static ThreadBase                 *_loadThread;
    static std::queue<ProxyGroupPtr>   _loadQueue;
    static Lock                       *_loadLock;

    static void loadProc(void *);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ProxyGroup &source);
};

OSG_END_NAMESPACE

#include "OSGProxyGroupBase.inl"
#include "OSGProxyGroup.inl"

#define OSGPROXYGROUP_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGPROXYGROUP_H_ */
