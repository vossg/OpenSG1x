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


#ifndef _OSGFIELDCONTAINERTYPE_H_
#define _OSGFIELDCONTAINERTYPE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>
#include <vector>

#include "OSGStringLink.h"
#include "OSGBaseTypes.h"
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGFieldContainer;
class OSGFieldDescription;

class OSGFieldContainer;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef void                 (*OSGInitContainerF)  (void);

typedef OSGFieldContainerPtr (*OSGPrototypeCreateF)(void);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainer type
 */

class OSGFieldContainerType 
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGFieldContainerType"; };
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	OSGFieldContainerType(const OSGChar8      *name,  
                          const OSGChar8      *parentName       = NULL,
                          const OSGChar8      *group            = NULL,
                          OSGPrototypeCreateF  prototypeCreateF = NULL,
                          OSGInitContainerF    initMethod       = NULL,
                          OSGFieldDescription *desc             = NULL,
                          OSGUInt32            descByteCounter  = 0);
    OSGFieldContainerType(const OSGFieldContainerType &obj);

    virtual ~OSGFieldContainerType (void);

    /*----------------------------- id --------------------------------------*/

    OSGUInt32 getId      (void) const;
    OSGUInt16 getGroupId (void) const;

    /*------------------------ general info ---------------------------------*/

    OSGFieldContainerType *getParent(void) const;

    const OSGChar8        *getName  (void) const;

    /*------------------------- prototye ------------------------------------*/

    OSGFieldContainerPtr getPrototype(void) const;
    OSGBool              setPrototype(OSGFieldContainerPtr prototype);

    /*----------------------------- create ----------------------------------*/

    OSGFieldContainerPtr createFieldContainer(void) const;
    OSGNodePtr           createNode          (void) const;
	OSGNodeCorePtr       createNodeCore      (void) const;
	OSGAttachmentPtr     createAttachment    (void) const;

    /*-------------------------- properties ---------------------------------*/

	OSGBool isAbstract      (void) const;

    OSGBool isFieldContainer(void) const;
    OSGBool isNode          (void) const;
    OSGBool isNodeCore      (void) const;
    OSGBool isAttachment    (void) const;

    OSGBool isDerivedFrom(const OSGFieldContainerType &other) const;
        
    /*------------------------- description ---------------------------------*/

	const OSGFieldDescription *findFieldDescription(
        const OSGChar8 *fieldName) const;

          OSGFieldDescription *getFieldDescription (
              OSGUInt32 index) ;
    const OSGFieldDescription *getFieldDescription (
              OSGUInt32 index) const;

    OSGUInt32            getNumFieldDescriptions(void) const;

    OSGUInt32            addDescription(const OSGFieldDescription &desc);

    /*----------------------------- dump ------------------------------------*/

	void print(void) const;

    /*------------------------- your_category -------------------------------*/

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum OSGBaseType
    {
        OSGIsFieldContainer,
        OSGIsNode,
        OSGIsNodeCore,
        OSGIsAttachment
    };

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
    
    typedef map   <OSGStringLink,       OSGFieldDescription *> OSGDescMap;
    typedef vector<OSGFieldDescription *>                      OSGDescVec;

    typedef OSGDescMap::iterator OSGDescMapIt;
    typedef OSGDescVec::iterator OSGDescVecIt;

    typedef OSGDescMap::const_iterator OSGDescMapConstIt;
    typedef OSGDescVec::const_iterator OSGDescVecConstIt;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

	friend class OSGFieldContainerFactory;

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

	const OSGString        _name;
          OSGString        _parentName;

    OSGBool                _initialized;

	OSGUInt32              _Id;
	OSGUInt16              _groupId;

    OSGFieldContainerPtr   _prototypeP;

    OSGPrototypeCreateF    _prototypeCreateF;

	OSGFieldContainerType *_parentP;

    OSGBaseType            _baseType;

	OSGDescMap             _descriptionMap;
    OSGDescVec             _descriptionVec;

    OSGFieldDescription   *_descA;
    OSGUInt32              _byteSizeOfDescA;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	void registerType(const OSGChar8 *group);

    void initPrototype   (void);
    void initBaseType    (void);
    void initFields      (void);
    void initParentFields(void);

	void initialize  (void);
    void terminate   (void);

	// prohibit default functions (move to 'public' if you need one)

    void operator =(const OSGFieldContainerType &source);
};

typedef OSGFieldContainerType* OSGFieldContainerTypeP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERTYPE_H_ */
