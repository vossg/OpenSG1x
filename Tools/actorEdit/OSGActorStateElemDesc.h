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

#ifndef _OSGACTORSTATEELEMDESC_H_
#define _OSGACTORSTATEELEMDESC_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGActorDescConstants.h"

#include <string>

OSG_USING_NAMESPACE

class ActorStateElemDesc
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef ActorDescConstants::AccessE AccessE;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    ActorStateElemDesc(void                             );
    ActorStateElemDesc(const std::string &name,
                       const std::string &type,
                             AccessE      access,
                             bool         hierarchical,
                       const std::string &header,
                       const std::string &defaultValue  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    ~ActorStateElemDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Get / Set                                                 */
    /*! \{                                                                 */

    void dump(void);

    const std::string &getName           (void                     ) const;
    void               setName           (const std::string &name  );

    const std::string &getType           (void                     ) const;
    void               setType           (const std::string &type  );

    AccessE            getAccess         (void                     ) const;
    std::string        getAccessStr      (void                     ) const;
    void               setAccess         (AccessE            access);
    void               setAccess         (const std::string &access);

    bool               getHierarchical   (void) const;
    std::string        getHierarchicalStr(void) const;
    void               setHierarchical   (bool               hierarchical);
    void               setHierarchical   (const std::string &hierarchical);

    const std::string &getHeader      (void                           ) const;
    void               setHeader      (const std::string &header      );

    const std::string &getDefaultValue(void                           ) const;
    void               setDefaultValue(const std::string &defaultValue);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    std::string _name;
    std::string _type;
    std::string _header;
    std::string _defaultValue;

    AccessE     _access;
    bool        _hierarchical;
};

//#include "OSGActorStateElemDesc.inl"

#define OSGACTORSTATEELEMDESC_HEADER_CVSID "@(#)$Id: OSGActorStateElemDesc.h,v 1.1 2004/04/20 13:06:50 neumannc Exp $"

#endif /* _OSGACTORSTATEELEMDESC_H_ */
