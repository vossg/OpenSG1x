/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGFieldFactory;
class OSGField;
class OSGNode;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------



/*! \ingroup FieldLib
 *  \brief OSGFieldType
 */

class OSGFieldType
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGField * (*OSGCreateFieldMethod)(void);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGField"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFieldType(const char           *szName, 
                 OSGCreateFieldMethod  createMethod);

    virtual ~OSGFieldType (void);

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
	/** Did I mentioned before that I love this ********* Microsoft Compiler.
		This piece of software really drives me nuts ;-(. The latest joke is,
		that I have to make the following two functions public to initialize
		the field type. I simply cannot write
		
		\code
		template <class OSGFieldTypeT>
		OSGFieldType OSGSFSysTypes<OSGFieldTypeT>::_fieldType(
			OSGSimpleFieldDataTraits<OSGFieldTypeT>::getFieldType(), 
			OSGSimpleFieldDataTraits<OSGFieldTypeT>::getName(), 
			create);
		\endcode

		no, I have to code the following

		\code
		template <class OSGFieldTypeT>
		OSGFieldType OSGSFSysTypes<OSGFieldTypeT>::_fieldType = OSGFieldType(
			OSGSimpleFieldDataTraits<OSGFieldTypeT>::getFieldType(), 
			OSGSimpleFieldDataTraits<OSGFieldTypeT>::getName(), 
			create);
		\endcode

		And to make it really complete, I do not have to implement them since
		the compiler never generates code where these functions are called.(GV)
	*/

    OSGFieldType(const OSGFieldType &source);
	void operator =(const OSGFieldType &obj);
#endif

    /*------------------------------ access ---------------------------------*/

	OSGUInt32   getTypeId(void) const;
    
    const char *getName  (void) const;

    /*----------------------------- comparision -----------------------------*/

    OSGBool operator ==(const OSGFieldType &source) const;
    OSGBool operator !=(const OSGFieldType &source) const;

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

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGFieldFactory;

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

    OSGUInt32  _typeId;

    char      *_szName;

    OSGCreateFieldMethod _createMethod;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

#if !defined(OSG_MICROSOFT_COMPILER_ALERT)
    OSGFieldType(const OSGFieldType &source);
    void operator =(const OSGFieldType &source);
#endif
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief OSGFieldTypeP
 */

typedef OSGFieldType* OSGFieldTypeP;

OSG_END_NAMESPACE

#endif /* _CLASSNAME_H_ */



