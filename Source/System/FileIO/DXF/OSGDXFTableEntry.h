/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2003 by the OpenSG Forum                 *
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

#ifndef _OSGDXFTABLEENTRY_H_
#define _OSGDXFTABLEENTRY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include "OSGDXFEntityBase.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief Base class for all entries inside a TABLE entity. 
 */

class OSG_SYSTEMLIB_DLLMAPPING DXFTableEntry : public DXFEntityBase
{
    /*==========================  PUBLIC  =================================*/
  public:
	
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
	
	static  const Char8 *getClassname(void)       { return "DXFTableEntry"; }
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DXFTableEntry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~DXFTableEntry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

	// Data for common group codes for table entries
	std::string _name;		// 2 Name of table entry

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Parsing                                  */
    /*! \{                                                                 */
	
	virtual DXFResult evalRecord(void);

	virtual DXFResult beginEntity(void);
//	virtual DXFResult endEntity(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef DXFEntityBase Inherited;
	
    /*!\brief prohibit default function (move to 'public' if needed) */
    DXFTableEntry(const DXFTableEntry &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const DXFTableEntry &source);
};

OSG_END_NAMESPACE

#define OSGDXFTABLEENTRY_HEADER_CVSID "@(#)$Id: OSGDXFTableEntry.h,v 1.1 2004/02/19 16:45:40 a-m-z Exp $"

//#include "OSGDXFTableEntry.inl"

#endif /* _OSGDXFTABLEENTRY_H_ */
