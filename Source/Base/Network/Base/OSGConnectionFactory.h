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

#ifndef _CONNECTIONFACTORY_H_
#define _CONNECTIONFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <map>
#include <OSGBaseTypes.h>
#include <OSGBase.h>
#include <OSGConnectionType.h>

OSG_BEGIN_NAMESPACE

//! \brief Factory for Connections, see 
//! \ingroup GrpBaseNetwork

class OSG_BASE_DLLMAPPING ConnectionFactory 
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      types                                   */
    /*! \{                                                                 */

    typedef std::map<std::string,ConnectionType *> TypeMap;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   access                                     */
    /*! \{                                                                 */

    static ConnectionFactory &the();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   interface                                  */
    /*! \{                                                                 */

    GroupConnection *createGroup(const std::string &name);
    PointConnection *createPoint(const std::string &name);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   fields                                     */
    /*! \{                                                                 */

    TypeMap _groupMap;
    TypeMap _pointMap;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ConnectionFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ConnectionFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    void addGroupType(ConnectionType *type);
    void addPointType(ConnectionType *type);
    void subGroupType(ConnectionType *type);
    void subPointType(ConnectionType *type);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    static ConnectionFactory *_the;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ConnectionFactory(const ConnectionFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ConnectionFactory &source);

    friend class ConnectionType;
};

OSG_END_NAMESPACE

#define OSG_CONNECTIONFACTORYHEADER_CVSID "@(#)$Id:$"

#endif /* _CONNECTIONFACTORY_H_ */
