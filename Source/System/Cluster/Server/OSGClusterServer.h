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

#ifndef _CLUSTERSERVER_H_
#define _CLUSTERSERVER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGFieldContainerPtr.h"
#include "OSGRemoteAspect.h"
#include "OSGClusterWindow.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

class PointConnection;
class ClusterWindow;
class RemoteAspect;
class RenderActionBase;

class OSG_SYSTEMLIB_DLLMAPPING ClusterServer
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ClusterServer(           WindowPtr  window,
                  const std::string    &serviceName,
                  const std::string    &connectionType = "StreamSock",
                  const std::string    &address        = "",
                             UInt32     servicePort    = 8437,
                  const std::string    &serviceGroup   = "");

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ClusterServer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   server actions                             */
    /*! \{                                                                 */

    void start             ( void                     );
    void stop              ( void                     );
    void render            ( RenderActionBase *action );
    void doSync            ( bool applyToChangelist   );
    void doRender          ( RenderActionBase *action );
    void doSwap            ( void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   window access                              */
    /*! \{                                                                 */

           WindowPtr     getClusterWindow(void);
           WindowPtr     getServerWindow (void);

    inline RemoteAspect *getRemoteAspect (void) const;
    inline UInt32        getServerId     (void) const;   
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   set                                        */
    /*! \{                                                                 */

    void setInterface(const std::string &interf);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name            ClusterWindow changed function                    */
    /*! \{                                                                 */

    bool windowChanged(FieldContainerPtr& fcp,
                       RemoteAspect *);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    WindowPtr         _window;
    PointConnection  *_connection;
    std::string       _requestAddress;
    std::string       _boundAddress;
    ClusterWindowPtr  _clusterWindow;
    RemoteAspect     *_aspect;
    std::string       _serviceName;
    std::string       _connectionType;
    UInt32            _servicePort;
    std::string       _serviceGroup;
    UInt32            _serverId;
    std::string       _interface;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     helper function                          */
    /*! \{                                                                 */

    void acceptClient();

    /*! \}                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    ClusterServer(const ClusterServer &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ClusterServer &source);
};

OSG_END_NAMESPACE

#include "OSGClusterServer.inl"

#define OSG_CLUSTERSERVERHEADER_CVSID "@(#)$Id:$"

#endif /* _CLUSTERSERVER_H_ */

