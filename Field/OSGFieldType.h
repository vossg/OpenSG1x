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


#ifndef _OSGFIELDTYPE_H_
#define _OSGFIELDTYPE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <typeinfo>
#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>
#include <OSGTypeBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Field;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------



/*! \ingroup FieldLib
 *  \brief FieldType
 */

class OSG_FIELD_DLLMAPPING FieldType : public TypeBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Field * (*CreateFieldMethod)(void);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Field"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FieldType(const Char8             *szName, 
                    CreateFieldMethod  createMethod);

    virtual ~FieldType (void);

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
	/** Did I mentioned before that I love this ********* Microsoft Compiler.
		This piece of software really drives me nuts ;-(. The latest joke is,
		that I have to make the following two functions public to initialize
		the field type. I simply cannot write
		
		\code
		template <class FieldTypeT>
		FieldType SFSysTypes<FieldTypeT>::_fieldType(
			SimpleFieldDataTraits<FieldTypeT>::getFieldType(), 
			SimpleFieldDataTraits<FieldTypeT>::getName(), 
			create);
		\endcode

		no, I have to code the following

		\code
		template <class FieldTypeT>
		FieldType SFSysTypes<FieldTypeT>::_fieldType = FieldType(
			SimpleFieldDataTraits<FieldTypeT>::getFieldType(), 
			SimpleFieldDataTraits<FieldTypeT>::getName(), 
			create);
		\endcode

		And to make it really complete, I do not have to implement them since
		the compiler never generates code where these functions are called.(GV)
	*/

    FieldType(const FieldType &source);
	FieldType &operator =(const FieldType &obj);
#endif

    /*------------------------------ access ---------------------------------*/

    /*----------------------------- comparision -----------------------------*/

    /*----------------------------- assignment ------------------------------*/


  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef TypeBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldFactory;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

//    const TypeBase          &_contentType;
    const CreateFieldMethod  _createMethod;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

#if !defined(OSG_MICROSOFT_COMPILER_ALERT)
    FieldType(const FieldType &source);
	FieldType &operator =(const FieldType &obj);
#endif
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief FieldTypeP
 */

typedef FieldType* FieldTypeP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDTYPE_H_ */



