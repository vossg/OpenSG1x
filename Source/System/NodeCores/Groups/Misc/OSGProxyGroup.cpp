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

#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <fstream>

#include <OSGConfig.h>

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGCamera.h>
#include <OSGRenderAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGVolumeDraw.h>
#include <OSGSceneFileHandler.h>

#include "OSGProxyGroup.h"

OSG_USING_NAMESPACE

/*! \class osg::ProxyGroup

  This group is used for delayed loading. If enabled the child
  noads are loaded in a second thread. Until the load is finished
  the child nodes of this group are rendered. This could be used
  to show a proxy object. If concurrentLoad is false, then loading
  is done during the first frame. This is the behaviour of a simple
  inline.

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void ProxyGroup::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & (UrlFieldMask))
    {
        if(getAbsoluteUrl().empty())
        {
            PathHandler *ph = SceneFileHandler::the().getPathHandler();
            beginEditCP(ProxyGroupPtr(this),ProxyGroup::AbsoluteUrlFieldMask);
            if(ph) 
                getAbsoluteUrl() = ph->findFile(getUrl().c_str());
            if(getAbsoluteUrl().empty())
                getAbsoluteUrl() = getUrl();
            endEditCP(ProxyGroupPtr(this),ProxyGroup::AbsoluteUrlFieldMask);
            setState(NOT_LOADED);
        }
    }
    if(whichField & (
           StateFieldMask|
           UrlFieldMask|
           VolumeFieldMask))
    {
        for(UInt32 i = 0; i < _parents.size(); i++)
        {
            _parents[i]->invalidateVolume();
        }
    }
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void ProxyGroup::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump ProxyGroup NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ProxyGroup::ProxyGroup(void) :
    Inherited()
{
}

ProxyGroup::ProxyGroup(const ProxyGroup &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ProxyGroup::~ProxyGroup(void)
{
    if(getRoot() != NullFC)
    {
        subRefCP(getRoot());
        setRoot(NullFC);
    }
}

/*! 
  If url was loaded, extend volume by loaded geometry. Otherwise
  extend volume by the volume given in the proxy object
*/
void ProxyGroup::adjustVolume( Volume & volume )
{
    volume.setValid();
    volume.setEmpty();

    if(getEnabled() == false)
        return;

    if(getState() == LOADED && getRoot() != NullFC)
    {
        volume.extendBy(getRoot()->getVolume());
    }
    else
    {
        volume.extendBy(getVolume());
    }
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */
Action::ResultE ProxyGroup::draw(Action *action)
{
    DrawActionBase *da        = dynamic_cast<DrawActionBase *>(action);

    if(getEnabled()     == false)
        return Action::Continue;

    if(getState() == NOT_LOADED)
        startLoading();

    if(getState() == LOAD_THREAD_FINISHED)
    {
        ProxyGroupPtr ptr(this);
            
        if(_loadedRoot != NullFC)
        {
            _loadThread=NULL;
            beginEditCP(ptr,RootFieldMask);
            if(getRoot() != NullFC)
                subRefCP(getRoot());
            setRoot(_loadedRoot);
            getRoot()->invalidateVolume();
            getRoot()->updateVolume();
            endEditCP(ptr,RootFieldMask);
            addRefCP(getRoot());
            beginEditCP(ptr,StateFieldMask);
            setState(LOADED);
            endEditCP(ptr,StateFieldMask);
            da->getActNode()->invalidateVolume();
            da->getActNode()->updateVolume();
        }
        else
        {
            SWARNING << "failed to load " << getAbsoluteUrl() << std::endl;
            beginEditCP(ptr,StateFieldMask);
            setState(LOAD_ERROR);
            endEditCP(ptr,StateFieldMask);
        }
    }

    if(getState() == LOADED)
    {
        da->useNodeList();
        if(da->isVisible(getRoot().getCPtr()))
            da->addNode(getRoot());
    }
    else
    {
        if(da->getActNode()->getNChildren() == 0)
        {
            Color3f col;
            col.setValuesRGB(.5,.3,0);            
            dropVolume(da, da->getActNode(), col);
        }
    }

    // thread cleanup
    if(_loadThread && _loadQueue.empty())
    {
        printf("join\n");
        BaseThread::join(_loadThread);
        _loadThread = NULL;
    }

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               loading                                   */

/*!
  Load the given URL, currently the URL is treated as a filename.
 */
void ProxyGroup::startLoading(void)
{
    ProxyGroupPtr ptr(this);

    if(getConcurrentLoad() == false)
    {
        if(getInline().size() == 0)
        {
            _loadedRoot = SceneFileHandler::the().read(getAbsoluteUrl().c_str());
        }
        else
        {
            std::stringstream tmpStream(std::ios_base::in|
                                        std::ios_base::out|
                                        std::ios_base::binary);
            tmpStream.write((char*)(&getInline()[0]),getInline().size());
            _loadedRoot = SceneFileHandler::the().read(tmpStream, "osb");
        }
        beginEditCP(ptr,StateFieldMask);
        setState(LOAD_THREAD_FINISHED);
        endEditCP(ptr,StateFieldMask);
    }
    else
    {
        if(_loadLock == NULL)
        {
            _loadLock=Lock::get("ProxyGroupLoadLock");
        }

        _loadLock->aquire();
        
        bool noThread=_loadQueue.empty();
        
        _loadQueue.push(ptr);
        beginEditCP(ptr,StateFieldMask);
        setState(LOAD_THREAD_RUNNING);
        endEditCP(ptr,StateFieldMask);
        
        _loadLock->release();
        
        if(noThread)
        {
            if(_loadThread)
                BaseThread::join(_loadThread);
            _loadThread=dynamic_cast<Thread *>(ThreadManager::the()
                                               ->getThread(NULL));
            _loadThread->runFunction( loadProc, 
                                      Thread::getAspect(),
                                      NULL );
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void ProxyGroup::initMethod (void)
{
    DrawAction::registerEnterDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ProxyGroupPtr  ,
            CNodePtr        ,
            Action         *>(&ProxyGroup::draw));

    RenderAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ProxyGroupPtr  ,
            CNodePtr        ,
            Action         *>(&ProxyGroup::draw));
}


void ProxyGroup::loadProc(void *)
{
    bool stopThread=false;
    ProxyGroupPtr g;

    _loadLock->aquire();
    g=_loadQueue.front();
    _loadLock->release();
    while(!stopThread)
    {
        if(g->getInline().size() == 0) 
        {
            g->_loadedRoot=SceneFileHandler::the().read(g->getAbsoluteUrl().c_str());
        }
        else
        {
            std::stringstream tmpStream(std::ios_base::in|
                                        std::ios_base::out|
                                        std::ios_base::binary);
            tmpStream.write((char*)(&g->getInline()[0]),g->getInline().size());
            g->_loadedRoot = SceneFileHandler::the().read(tmpStream, "osb");
        }
        beginEditCP(g,StateFieldMask);
        g->setState(LOAD_THREAD_FINISHED);
        endEditCP(g,StateFieldMask);
        
        _loadLock->aquire();
        _loadQueue.pop();
        if(_loadQueue.empty())
            stopThread=true;
        else
            g=_loadQueue.front();
        _loadLock->release();
    }
}

ThreadBase                 *ProxyGroup::_loadThread=NULL;
std::queue<ProxyGroupPtr>   ProxyGroup::_loadQueue=std::queue<ProxyGroupPtr>();
Lock                       *ProxyGroup::_loadLock=NULL;

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGProxyGroup.cpp,v 1.22 2002/06/30 05:04:22 vossg Exp $";
    static Char8 cvsid_hpp[] = OSGPROXYGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGPROXYGROUP_INLINE_CVSID;
}

    

