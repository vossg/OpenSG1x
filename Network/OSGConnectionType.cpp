/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
#include "OSGConnection.h"
#include "OSGConnectionType.h"
#include "OSGConnectionFactory.h"

OSG_USING_NAMESPACE

/** \class osg::ConnectionType
 *  \ingroup Network
 *  \author Marcus Roth
 *
 * A connection type describes a network connection and provides an
 * interface for dynamic connection creation.
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 *
 * \param createFunction  Pointer to the create function
 * \param name            Name of the connection
 */
ConnectionType::ConnectionType(CreateFunction  createFunction, 
                               const string   &name):
    _createFunction(createFunction),
    _name(name)
{
    ConnectionFactory::the().addType(this);
}

/*! Copy constructor
 */
ConnectionType::ConnectionType(const ConnectionType &source):
    _createFunction(source._createFunction),
    _name(source._name)
{
    ConnectionFactory::the().addType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor
 *
 * Unregister the connection from the factory
 */
ConnectionType::~ConnectionType(void)
{
    ConnectionFactory::the().subType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
ConnectionType& ConnectionType::operator = (const ConnectionType &source)
{
    if(this == &source)
        return *this;

    _name           = source._name;
    _createFunction = source._createFunction;
    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*! less
 */

bool ConnectionType::operator < (const ConnectionType &other) const
{
    return _name < other._name;
}

/*! equal
 */

bool ConnectionType::operator == (const ConnectionType &other) const
{
    return _name == other._name;
}

/*! unequal
 */

bool ConnectionType::operator != (const ConnectionType &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*/
/*                             get                                         */

/*! get conneciton name
 */

string ConnectionType::getName(void) const
{
    return _name;
}

/*! get conneciton create function
 */

ConnectionType::CreateFunction ConnectionType::getCreateFunction(void) const
{
    return _createFunction;
}

/*-------------------------------------------------------------------------*/
/*                             your_category                               */

/*! create Connection
 */

Connection *ConnectionType::create(void)
{
    return _createFunction();
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
    static Char8 cvsid_hpp[] = OSG_CONNECTIONTYPEHEADER_CVSID;
}
