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

#ifndef _OSGINDENTER_H_
#define _OSGINDENTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>

#include <iostream>

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGIndenter.h
    \ingroup GrpBaseStringConversion
 */
#endif

/*! \ingroup GrpBaseStringConversion
 */

class OSG_BASE_DLLMAPPING Indenter 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Indenter(      UInt32    indent = 0, 
                   UInt32    step   = 4);
    Indenter(const Indenter &source    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Indenter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    UInt32 getIndent(void) const;
    UInt32 getStep  (void) const;

    std::string str (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setIndent(UInt32 indent);
    void setStep  (UInt32 step  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      operators                               */
    /*! \{                                                                 */

    void      operator++(      int             );
    void      operator++(      void            );

    void      operator--(      int             ); 
    void      operator--(      void            );

    Indenter &operator =(const Indenter &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt32     _indent;
    UInt32     _step;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

inline 
std::ostream &operator <<(std::ostream &stream, const Indenter &indent);


OSG_END_NAMESPACE

#define OSGINDENTER_HEADER_CVSID "@(#)$Id: $"

#include "OSGIndenter.inl"

#endif /* _Indenter_H_ */
