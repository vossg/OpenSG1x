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

#ifndef _OSGSTRINGCONVERSIONSTATEBASE_H_
#define _OSGSTRINGCONVERSIONSTATEBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGField.h>

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGStringConversionStateBase.h
    \ingroup GrpBaseStringConversion
 */
#endif

/*! \ingroup GrpBaseStringConversion
 */

class OSG_BASE_DLLMAPPING StringConversionStateBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StringConversionStateBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StringConversionStateBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Handle Fields                             */
    /*! \{                                                                 */

    virtual std::string &beginField (const Field       *pF,    
                                           std::string &outStr) = 0;
    virtual std::string &addValueStr(      std::string &value, 
                                           std::string &outStr) = 0;
    virtual std::string &endField   (const Field  *pF,    
                                           std::string &outStr) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    StringConversionStateBase(const StringConversionStateBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const StringConversionStateBase &source);
};

OSG_END_NAMESPACE

#define OSGSTRINGCONVERSIONSTATEBASE_HEADER_CVSID "@(#)$Id: $"

#include <OSGStringConversionStateBase.inl>

#endif /* _OSGSTRINGCONVERSIONSTATEBASE_H_ */
