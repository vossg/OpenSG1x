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

#ifndef _OSGSTRING_H_
#define _OSGSTRING_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <string.h>
#include <vector>
#include <iostream>

OSG_BEGIN_NAMESPACE


class String;
OSG_BASE_DLLMAPPING ostream &operator <<(      ostream &os,
                                         const String  &obj);

/*! \ingroup BaseTypes
 *  \brief OSGString
 *
 *  detailed
 */

class OSG_BASE_DLLMAPPING String
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum MemType
    {
        COPY,
        LINK
    };

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "OSGString"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    explicit String(UInt32 size = 0);

    explicit String(const Char8 *str,  MemType memType = COPY);
             String(const String &obj, MemType memType = COPY);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~String(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Your Category                               */
    /*! \{                                                                 */

    inline const Char8   *str  (void) const { return _str; }

    inline Bool          empty (void) const { return (_str && *_str) ?
                                                 false : true; }

    void   set       (const Char8 *str, MemType memType = COPY);

    void   toUpper   (void);
    void   toLower   (void);

    UInt32 length    (void) const;

    void   setLength (UInt32 length);

    void   tokenize  (vector <String> &v);
    void   tokenize  (vector <String*> &v);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    inline const String & operator =(const String &obj)
        {
            set(obj._str);

            return *this;
        }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Comparison                                  */
    /*! \{                                                                 */

    inline Bool operator < (const String &obj) const
    {
        return (_str && obj._str && (::strcmp(_str, obj._str) < 0));
    }

    inline Bool operator ==(const String &o)   const
    {
        return ((_str == o._str) ?
                1 : (_str && o._str && !::strcmp(_str, o._str)));
    }

    inline Bool operator !=(const String &o)   const
    {
        return ! (*this == o);
    }

    inline Bool operator > (const String &o)   const
    {
        return ! (*this < o) && ! (*this == o);
    }

    inline Bool operator >=(const String &o)   const
    {
        return ! (*this < o);
    }

    inline Bool operator <=(const String &o)   const
    {
        return (*this < o) || (*this == o);
    }

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
    private:

    friend OSG_BASE_DLLMAPPING
    ostream &operator <<(      ostream &os,
                         const String  &obj);

    static char cvsid[];

    Char8   *_str;
    MemType  _memType;

};

typedef String *StringP;

OSG_END_NAMESPACE

#include <OSGStringLink.h>

#endif /* _OSGSTRING_H_ */



