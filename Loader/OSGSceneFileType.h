/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGSCENEFILETYPE_H_
#define _OSGSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once 
#endif 


//-------------------------------------------------------
//Includes
//-------------------------------------------------------

#include <OSGSystemDef.h>

#include <list>

#include <OSGBaseTypes.h>
#include <OSGString.h>

#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE


//-------------------------------------------------------
//Forward References	 
//-------------------------------------------------------


//-------------------------------------------------------
//Types		 
//-------------------------------------------------------


//-------------------------------------------------------
//Class 	   
//-------------------------------------------------------


/*!\ingroup baselib 
 * \brief Brief 
 * 
 * detailed 
 */ 


class OSG_SYSTEMLIB_DLLMAPPING SceneFileType
{
  public:

    //-------------------------------------------------------
    //enums   
    //-------------------------------------------------------


    //-------------------------------------------------------
    //types 
    //-------------------------------------------------------


    //-------------------------------------------------------
    //class functions 
    //-------------------------------------------------------


     static const char *getClassname(void) 
			 { return "SceneFileType"; };

    //-------------------------------------------------------
    // instance functions 
    //-------------------------------------------------------

		 /** Destructor */
		 virtual ~SceneFileType (void);
		 
		 /** get mathod for the type name */
		 virtual const char *getName (void) const = 0;
		 
		 /** get method for attribute suffixList */
		 virtual list<String> & suffixList (void) { return _suffixList; }
		 
		 /** fill the given image with the content of the file 'fileName' */
		 virtual NodePtr read (const char *fileName ) const = 0;
		 
		 /** write the given image to 'fileName' */
		 virtual Bool write ( const NodePtr node,
													const char *fileName ) const = 0;
		 
		 /** print debug info to cerr */
		 void print(void);


  protected:

    //-------------------------------------------------------
    //enums 
    //-------------------------------------------------------
    

    //-------------------------------------------------------
    //types 	 
    //-------------------------------------------------------


    //-------------------------------------------------------
    //class Variables  
    //-------------------------------------------------------


    //-------------------------------------------------------
    //class functions  
    //-------------------------------------------------------


    //-------------------------------------------------------
    //instance Variables  
    //-------------------------------------------------------


		/** Default Constructor */
		SceneFileType ( const char * suffixArray[], 
											 UInt16 suffixByteCount );

		/** Copy Constructor */
		SceneFileType (const SceneFileType &obj);

  private:

    //-------------------------------------------------------
    //enums    		 
    //-------------------------------------------------------


    //-------------------------------------------------------
    //types 
    //-------------------------------------------------------
    

    //-------------------------------------------------------
    //friend Classes   
    //-------------------------------------------------------


    //-------------------------------------------------------
    //friend functions 
    //-------------------------------------------------------


    //-------------------------------------------------------
    //class Variables 
    //-------------------------------------------------------

		/** suffix list for the type */
		list<String> _suffixList;

    //-------------------------------------------------------
    //class functions
    //-------------------------------------------------------


    //-------------------------------------------------------
    //instance Variables  
    //-------------------------------------------------------


    //-------------------------------------------------------
    //instance functions   
    //-------------------------------------------------------


};

typedef SceneFileType* SceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGSCENEFILETYPE_H_
