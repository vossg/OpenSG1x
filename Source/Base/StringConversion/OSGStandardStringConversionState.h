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

#ifndef _StandardStringConversionState_H_
#define _StandardStringConversionState_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGField.h>
#include <OSGIndenter.h>
#include <OSGStringTokenizer.h>
#include <OSGStringConversionStateBase.h>

OSG_BEGIN_NAMESPACE

//! Brief
//! \ingroup GrpBaseStringConversion

class OSG_BASE_DLLMAPPING StandardStringConversionState : 
    public StringConversionStateBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    enum { DefaultIndent, DefaultWidth, UnlimitedWidth };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StandardStringConversionState(UInt32 indent = DefaultIndent,
                                  UInt32 width  = DefaultWidth);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StandardStringConversionState(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    inline UInt32 getIndent(void) const;
    inline UInt32 getWidth (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    inline void setIndent(UInt32 newIndent);
    inline void setWidth (UInt32 newWidth );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    virtual std::string &beginField (const      Field  *pF,    
                                           std::string &outStr);
    virtual std::string &addValueStr(      std::string &value, 
                                           std::string &outStr);
    virtual std::string &endField   (const      Field  *pF,    
                                           std::string &outStr);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    // virtual bool operator < (const StandardStringConversionState &other) const;
    
    //bool operator == (const StandardStringConversionState &other) const;
    //bool operator != (const StandardStringConversionState &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */
    
    Indenter        _indent;
    UInt32          _width;

    UInt32          _lineLength;

    bool            _noLineBreakHint;
    bool            _multiFieldHint;

    std::string     _mfSeparator;
    UInt32          _mfSepLength;
    UInt32          _lastMFSepStart;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef StringConversionStateBase Inherited;


    /*!\brief prohibit default function (move to 'public' if needed) */
//    StandardStringConversionState(const StandardStringConversionState &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
//    StandardStringConversionState& operator =(
//        const StandardStringConversionState &source);
};

OSG_END_NAMESPACE

#define OSGSTANDARDSTRINGCONVERSIONSTATE_HEADER_CVSID "@(#)$Id: $"

#include "OSGStandardStringConversionState.inl"

#endif /* _StandardStringConversionState_H_ */

