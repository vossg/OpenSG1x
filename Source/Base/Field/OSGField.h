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

#ifndef _OSGFIELD_H_
#define _OSGFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>

#include <OSGFieldType.h>
#include <OSGIDString.h>
#include <OSGLog.h>
#include <string>

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGField.h
    \ingroup GrpBaseField
 */
#endif

class StringConversionStateBase;

/*! \ingroup GrpBaseFieldHelper
    \hideinhierarchy
 */

template <class T>
struct ErrorFromToString
{
    static bool              getFromString(      T      &,
                                           const Char8 *&)
    {
        SLOG << "Error From String Conversion not available for " << std::endl;

        return false;
    }

    static void             putToString(const T           &,
                                              std::string &)
    {
        SLOG << "Error To String Conversion not available for " << std::endl;
    }
};

/*! Base class for all fields
   \ingroup GrpBaseField
 */

class OSG_BASE_DLLMAPPING Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Field(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual const FieldType              &getType       (void) const = 0;
            const DataType               &getContentType(void) const;

                  FieldType::Cardinality  getCardinality(void) const;

    virtual       bool                    isEmpty       (void) const = 0;

    virtual       UInt32                  getSize       (void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   String IO                                  */
    /*! \{                                                                 */

    virtual void          pushValueByStr(const Char8       *str  )       = 0;
    virtual std::string  &getValueByStr (      std::string &str  ) const = 0;
    virtual std::string  &getValueByStr (      std::string &str,
                                 StringConversionStateBase &state) const = 0;

    virtual std::string  &getValueByStr (      std::string &str,
                                               UInt32       index) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void setAbstrValue(const Field &obj) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(void) const = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Field(void);
    Field(const Field &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Field &source);
};

OSG_END_NAMESPACE

#define OSGFIELD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELD_HPP_ */


