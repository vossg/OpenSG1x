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

#ifndef _OSGIDSTRING_H_
#define _OSGIDSTRING_H_
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


class IDString;
OSG_BASE_DLLMAPPING ostream &operator <<(      ostream  &os,
                                         const IDString &obj);

/*! \ingroup BaseTypes
 *  \brief OSGIDString
 *
 *  detailed
 */

class OSG_BASE_DLLMAPPING IDString
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

    static const char *getClassname(void) { return "OSGIDString"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    explicit IDString(UInt32 size = 0);

    explicit IDString(const Char8 *str,  MemType memType = COPY);
             IDString(const IDString &obj, MemType memType = COPY);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~IDString(void);

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

    void   tokenize  (vector <IDString  > &v);
    void   tokenize  (vector <IDString *> &v);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    inline const IDString & operator =(const IDString &obj)
        {
            set(obj._str);

            return *this;
        }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Comparison                                  */
    /*! \{                                                                 */

    inline Bool operator < (const IDString &obj) const
    {
        return (_str && obj._str && (::strcmp(_str, obj._str) < 0));
    }

    inline Bool operator ==(const IDString &o)   const
    {
        return ((_str == o._str) ?
                1 : (_str && o._str && !::strcmp(_str, o._str)));
    }

    inline Bool operator !=(const IDString &o)   const
    {
        return ! (*this == o);
    }

    inline Bool operator > (const IDString &o)   const
    {
        return ! (*this < o) && ! (*this == o);
    }

    inline Bool operator >=(const IDString &o)   const
    {
        return ! (*this < o);
    }

    inline Bool operator <=(const IDString &o)   const
    {
        return (*this < o) || (*this == o);
    }

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
    private:

    friend OSG_BASE_DLLMAPPING
    ostream &operator <<(      ostream  &os,
                         const IDString &obj);

    static char cvsid[];

    Char8   *_str;
    MemType  _memType;

};

typedef IDString *IDStringP;

OSG_END_NAMESPACE

#include <OSGIDStringLink.h>

#endif /* _OSGSTRING_H_ */



