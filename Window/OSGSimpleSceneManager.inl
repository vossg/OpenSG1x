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


//! pseudo constructor
inline SimpleSceneManager* SimpleSceneManager::create(void)
{
    return new SimpleSceneManager;
}

//! access the window
inline WindowPtr SimpleSceneManager::getWindow(void)
{
    return _win;
}

//! set the window
inline void SimpleSceneManager::setWindow( WindowPtr win )
{
    _win = win;
}

//! access the root
inline NodePtr SimpleSceneManager::getRoot(void)
{
    return _root;
}

//! set the root
inline void SimpleSceneManager::setRoot( NodePtr root )
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

//! set the headlight settings
inline void SimpleSceneManager::setHeadlight( Bool on )
{
    if ( _headlight != NullFC )
        _headlight->setOn( on );
}

inline void SimpleSceneManager::turnHeadlightOn( void )
{
    if ( _headlight != NullFC )
        _headlight->setOn( true );
}

inline void SimpleSceneManager::turnHeadlightOff( void )
{
    if ( _headlight != NullFC )
        _headlight->setOn( false );
}

OSG_END_NAMESPACE

#define OSGSIMPLESCENEMANAGER_INLINE_CVSID "@(#)$Id: OSGSimpleSceneManager.inl,v 1.2 2001/09/28 07:57:00 vossg Exp $"


