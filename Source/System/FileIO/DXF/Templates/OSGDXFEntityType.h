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

#ifndef _OSGDXFENTITYNAME_H_
#define _OSGDXFENTITYNAME_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include "OSGDXFEntityBase.h"
#include "OSGDXFparentclass.h"

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

/*! \brief Handles the ENTITYNAME entry in the DXF file structure.
 */

class OSG_SYSTEMLIB_DLLMAPPING DXFentityname : public DXFparentclass
{
    /*==========================  PUBLIC  =================================*/
  public:
	
    /*---------------------------------------------------------------------*/
    /*! \name                   Initialization                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
	
	static  const Char8 *getClassname(void)       { return "DXFentityname"; }

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~DXFentityname(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

	static DXFentityname *_the;

	// Data for (some) ENTITYNAME groups
	//			   									// X
	// Group codes not implemented: 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Parsing                                  */
    /*! \{                                                                 */
	
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef DXFparentclass Inherited;
	
	/*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DXFentityname(void);  // private for classes DXF<EntityType>

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
    DXFentityname(const DXFentityname &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const DXFentityname &source);
};

OSG_END_NAMESPACE

#define OSGDXFENTITYNAME_HEADER_CVSID "@(#)$Id: OSGDXFEntityType.h,v 1.1 2004/02/19 16:45:44 a-m-z Exp $"

//#include "OSGDXFentityname.inl"

#endif /* _OSGDXFENTITYNAME_H_ */
