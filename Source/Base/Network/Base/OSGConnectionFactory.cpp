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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGConnection.h"
#include "OSGConnectionType.h"
#include "OSGConnectionFactory.h"

OSG_USING_NAMESPACE

ConnectionFactory *ConnectionFactory::_the=NULL;

/** \class osg::ConnectionFactory
 *  \ingroup GrpBaseNetwork
 *
 * The ConnectionFactory knows all types of connections by name. 
 * A new connection object could be crated by calling 
 * <PRE>
 * Connection *c = ConnectionFactory::the().create("Multicast");
 * if(!c)
 * {
 *     SLOG << "Unknown connection:";
 * }
 * </PRE>
 *
 * Each connection type must be registered to the factory. This is done
 * by static initialisation. The following example shows registration
 * of the Multicast connection.
 *
 * <PRE>
 * ConnectionType MulticastConnection::_type(&MulticastConnection::create,
                                             "Multicast");
 * </PRE>
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor documentation
 */
ConnectionFactory::ConnectionFactory(void) :
    _groupMap(),
    _pointMap()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
ConnectionFactory::~ConnectionFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                      public interface                                   */

/*! create group connection by name
 */
GroupConnection *ConnectionFactory::createGroup(const std::string &name)
{
    TypeMap::iterator i=_groupMap.find(name);
    if(i == _groupMap.end())
        return NULL;
    else
        return i->second->createGroup();
}

/*! create point connection by name
 */
PointConnection *ConnectionFactory::createPoint(const std::string &name)
{
    TypeMap::iterator i=_pointMap.find(name);
    if(i == _pointMap.end())
        return NULL;
    else
        return i->second->createPoint();
}

/*! get singelton factory 
 */
ConnectionFactory &ConnectionFactory::the(void)
{
    if(_the == NULL)
        _the=new ConnectionFactory();
    return *_the;
}

/*-------------------------------------------------------------------------*/
/*                      protected interface                                */

/*! add new group type
 */
void ConnectionFactory::addGroupType(ConnectionType *type)
{
    _groupMap[type->getName()]=type;
    SINFO << "Group Connection type " << type->getName() << " added" << std::endl;
}

/*! add new point type
 */
void ConnectionFactory::addPointType(ConnectionType *type)
{
    _pointMap[type->getName()]=type;
    SINFO << "Point Connection type " << type->getName() << " added" << std::endl;
}

/*! remove point type
 */
void ConnectionFactory::subPointType(ConnectionType *type)
{
    TypeMap::iterator i=_pointMap.find(type->getName());
    if(i != _pointMap.end() && i->second == type)
        _pointMap.erase(i);
    SINFO << "Point connection type " << type->getName() 
          << " removed" << std::endl;
}

/*! remove group type
 */
void ConnectionFactory::subGroupType(ConnectionType *type)
{
    TypeMap::iterator i=_groupMap.find(type->getName());
    if(i != _groupMap.end() && i->second == type)
        _groupMap.erase(i);
    SINFO << "Group connection type " << type->getName() 
          << " removed" << std::endl;
}

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
    static Char8 cvsid_cpp[] = "@(#)$Id:$";
    static Char8 cvsid_hpp[] = OSG_CONNECTIONFACTORYHEADER_CVSID;
}








