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

/** Example class of an derived FieldContainer.
	Defines a background FieldContainer which contains 3 Fields 
	a single Field of Real32 (_real), an other single Field (_single) 
	and a multi Field (_multi).
*/

#ifndef _OSG_DERIVEDBACKGROUND_H_
#define _OSG_DERIVEDBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <other classes of basetypes you need>
#include <OSGFieldContainer.h>
#include <OSGWindowBase.h>
#include <OSGBackground.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class DrawAction;
class Viewport;


/** a special FieldContainerPointer is required for every FieldContainer 
*/
class DerivedBackground;
typedef FCPtr<BackgroundPtr, DerivedBackground> DerivedBackgroundPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


class OSG_WINDOW_DLLMAPPING DerivedBackground : public Background
{
  private:

/** for some functions a private FieldContainer variable is required
*/
	typedef FieldContainer Inherited;


  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

/** declaration of the included Fields:
*/
	/** first Field
	*/
    OSG_FC_FIRST_FIELD_IDM_DECL(RealField)

	/** order of Fields
	*/
    OSG_FC_FIELD_IDM_DECL      (SingleField, RealField)
    OSG_FC_FIELD_IDM_DECL      (MultiField, SingleField)

	/** last Field
	*/
    OSG_FC_LAST_FIELD_IDM_DECL (MultiField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

/** always include a function that returns the classname
*/
    static const char *getClassname(void) { return "DerivedBackground"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

/** here comes the declaration of the FieldContainerPointer mentioned above
*/
    OSG_FIELD_CONTAINER_DECL(DerivedBackgroundPtr)

    /*------------------------- your_category -------------------------------*/

/** a background has to have a clear function to clear or draw the background
*/
	void clear( DrawAction * action, Viewport * port );

/** it's required for a FieldContainer that you can set a value for every 
	included Field
*/
	void set(Real32 _multi);
	void set(ValueTypeT _single);
	void set(ValueTypeT _multi);

/** also a get function for one value of every included Field
*/
	Real32 getReal();
	ValueTypeT getSingle();
	ValueTypeT getMulti();

/** and a get function for the hole Field
*/
	SFReal32 *getSFReal();
	SFValueTypeT *getSFSingle();
	MFValueTypeT *getMFMulti();

/** and here you can define further functions you want to make available
*/

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

/** now you need some comparison functions
*/
    Bool operator < (const DerivedBackground &other) const;
    
	//Bool operator == (const Background &other) const;
	//Bool operator != (const Background &other) const;

    /*------------------------------ dump -----------------------------------*/

/** and at last the dump function
*/
    virtual void dump(void) const;

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

/** the included Fields also need to be defined as private variables
*/
	  SFReal32 _real;
	  SFValueTypeT _single;
	  MFValueTypeT _multi;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

/** constructor & destructor
*/
    DerivedBackground(void);
    virtual ~DerivedBackground(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;
    friend class FieldContainerType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

/** and you need some other private variables
*/ 
	/** first the ID
	*/
	static char cvsid[];

	/** then a FieldContainerType variable, in which the description of your 
		FieldContainer has to be saved (see cpp file) 
	*/
	static FieldContainerType _type;

	/** and a FieldDescription variable, in which the description of your 
		included Fields has to be saved (see cpp file)
	*/
	static FieldDescription   _desc[];


    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

/** if you need more private functions then define here
*/

/** some access functions
*/
    DerivedBackground(const DerivedBackground &source);
    DerivedBackground & operator =(const DerivedBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** class pointer (maybe not nessecary)
*/
typedef DerivedBackground *DerivedBackgroundP;


/** now comes some code you dont' need to understand, just adjust
	it to your code!
	(template only required if FieldContainer is used like a Field
	and included in an other FieldContainer)
*/	
	template <>
	struct FieldDataTraits<DerivedBackgroundPtr> : public Traits
	{
		enum                         { StringConvertable = 0x00  };

		static Char8 *getSName(void) { return "SFDerivedBackgroundPtr"; }
		static Char8 *getMName(void) { return "MFDerivedBackgroundPtr"; }
	};

	typedef SField<DerivedBackgroundPtr>       SFDerivedBackgroundPtr;

	#ifndef OSG_COMPILEBACKGROUNDINST
	#if defined(__sgi)

	#pragma do_not_instantiate SField<DerivedBackgroundPtr>::_fieldType

	#else

	OSG_DLLEXPORT_DECL1(SField, DerivedBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

	#endif
	#endif


	typedef MField<DerivedBackgroundPtr>       MFDerivedBackgroundPtr;

	#ifndef OSG_COMPILEBACKGROUNDINST
	#if defined(__sgi)

	#pragma do_not_instantiate MField<DerivedBackgroundPtr>::_fieldType

	#else

	OSG_DLLEXPORT_DECL1(MField, DerivedBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

	#endif
	#endif


OSG_END_NAMESPACE

#include <OSGDerivedBackground.inl>

#endif /* _OSGDERIVEDBACKGROUND_H_ */


