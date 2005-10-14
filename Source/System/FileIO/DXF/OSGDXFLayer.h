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

#ifndef _OSGDXFLAYER_H_
#define _OSGDXFLAYER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include "OSGDXFEntityBase.h"
#include "OSGDXFTableEntry.h"

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

/*! \brief Handles the LAYER table entry in the DXF file structure.
 */

class OSG_SYSTEMLIB_DLLMAPPING DXFLayer : public DXFTableEntry
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
	
	static  const Char8 *getClassname(void)       { return "DXFLayer"; }

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~DXFLayer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

	static DXFLayer *_the;

	// Data for (some) LAYER groups
	Int16		_colorNumber;					// 62
	std::string _linetypeName;			   		// 6
	// Group codes not implemented: 70, 290, 370, 390

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Parsing                                  */
    /*! \{                                                                 */
	
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef DXFTableEntry Inherited;
	
	/*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DXFLayer(void);  // private for classes DXF<EntityType>

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
    /*! \name                     Parsing                                  */
    /*! \{                                                                 */

	virtual DXFResult evalRecord(void);

	virtual DXFResult beginEntity(void);
	virtual DXFResult endEntity(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    DXFLayer(const DXFLayer &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const DXFLayer &source);
};

OSG_END_NAMESPACE

#define OSGDXFLAYER_HEADER_CVSID "@(#)$Id: OSGDXFLayer.h,v 1.2 2005/10/14 08:33:35 a-m-z Exp $"

//#include "OSGDXFLayer.inl"

#endif /* _OSGDXFLAYER_H_ */
