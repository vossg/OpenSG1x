/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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


#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


/*! pseudo constructor. Standard interface for OpenSG object creation.
 */
inline SimpleSceneManager* SimpleSceneManager::create(void)
{
    return new SimpleSceneManager;
}

/*! get the window to be used for display
 */
inline WindowPtr SimpleSceneManager::getWindow(void)
{
    return _win;
}

/*! set the window to be used for display
 */
inline void SimpleSceneManager::setWindow(WindowPtr win)
{
    _win = win;
}

/*! get the root of the displayed tree
 */
inline NodePtr SimpleSceneManager::getRoot(void)
{
    return _root;
}

/*! get the action used to render the scene
 */
inline DrawActionBase *SimpleSceneManager::getAction(void)
{
    return _action;
}

/*! set the root of the displayed tree
 */
inline void SimpleSceneManager::setRoot(NodePtr root)
{
    if(_root != NullFC)
    {
        _internalRoot->subChild(_root);
        subRefCP(_root);
    }
    
    if(_internalRoot == NullFC)
    {
        initialize();
    }

    _root = root;

    addRefCP(_root);
    _internalRoot->addChild(_root);
}

/*! set the headlight setting
 */
inline void SimpleSceneManager::setHeadlight(Bool on)
{
    if(_headlight != NullFC)
        _headlight->setOn(on);
}

/*! turn headlight on.
 */
inline void SimpleSceneManager::turnHeadlightOn(void)
{
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

    if(_headlight != NullFC)
        _headlight->setOn(true);

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif
}

/*! turn headlight off.
 */
inline void SimpleSceneManager::turnHeadlightOff(void)
{
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

    if(_headlight != NullFC)
        _headlight->setOn(false);

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif
}

/*! set the highlight object
 */
inline void SimpleSceneManager::setHighlight(NodePtr highlight)
{
    _highlight = highlight;
    highlightChanged();
}

/*! get the highlight object
 */
inline NodePtr SimpleSceneManager::getHighlight(void)
{
    return _highlight;
}

OSG_END_NAMESPACE

#define OSGSIMPLESCENEMANAGER_INLINE_CVSID "@(#)$Id: OSGSimpleSceneManager.inl,v 1.6 2001/10/15 03:10:25 vossg Exp $"


