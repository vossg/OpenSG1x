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

#ifndef _OSGSTRINGTOKENIZER_H_
#define _OSGSTRINGTOKENIZER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <string>

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGStringTokenizer.h
    \ingroup GrpBaseStringConversion
 */
#endif

/*! \ingroup GrpBaseStringConversion
 */

class OSG_BASE_DLLMAPPING StringTokenizer
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StringTokenizer(std::string &toTokens);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StringTokenizer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Tokenize                                  */
    /*! \{                                                                 */
   
    bool        hasNext    (void                 );
    std::string getNext    (void                 );
    void        setString  (std::string &toTokens);
    UInt32      countTokens(void                 );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    void nextTokenPos(std::string::size_type &start, 
                      std::string::size_type &end);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */
    
    bool                    _hasNext;
    std::string            &_tokenString;
    std::string             _nextToken;
    std::string::size_type  _currPos;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    StringTokenizer(const StringTokenizer &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const StringTokenizer &source);
};

OSG_END_NAMESPACE

#define OSGSTRINGTOKENIZER_HEADER_CVSID "@(#)$Id: $"

#include "OSGStringTokenizer.inl"

#endif /* _OSGSTRINGTOKENIZER_H_ */
