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

#ifndef _StringConversionStateBase_H_
#define _StringConversionStateBase_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGField.h>

OSG_BEGIN_NAMESPACE

//! Brief
//! \ingroup baselib

class /*OSG_DLLEXPORT*/ StringConversionStateBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    //StringConversionStateBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StringConversionStateBase(void){ }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    virtual string &beginField (const Field  *pF,    string &outStr) = 0;
    virtual string &addValueStr(      string &value, string &outStr) = 0;
    virtual string &endField   (const Field  *pF,    string &outStr) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    //virtual bool operator < (const StringConversionStateBase &other) const;

    //bool operator == (const StringConversionStateBase &other) const;
    //bool operator != (const StringConversionStateBase &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:


    /*!\brief prohibit default function (move to 'public' if needed) */
//    StringConversionStateBase(const StringConversionStateBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
//    void operator =(const StringConversionStateBase &source);
};

OSG_END_NAMESPACE

#define OSGSTRINGCONVERSIONSTATEBASE_HEADER_CVSID "@(#)$Id: OSGStringConversionStateBase.h,v 1.2 2002/02/23 01:02:08 dirk Exp $"

#endif /* _StringConversionStateBase_H_ */
