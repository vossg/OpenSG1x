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

class OSGNodePtr;
class OSGNodeCorePtr;
class OSGAttachmentPtr;


class OSGFieldContainer;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef void                 (*OSGInitContainerMethod)(void);

typedef OSGFieldContainerPtr (*OSGPrototypeCreateF)   (void);

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

	OSGFieldContainerType(
        const OSGChar                 *name,  
        const OSGChar                 *parentName       = NULL,
        const OSGChar                 *group            = NULL,
        OSGPrototypeCreateF            prototypeCreateF = NULL,
        OSGInitContainerMethod         initMethod       = NULL,
        OSGFieldDescription           *desc             = NULL,
        OSGUInt32                      descByteCounter  = 0);

    virtual ~OSGFieldContainerType (void);

    /*----------------------------- id --------------------------------------*/

    OSGUInt32 getId      (void) const;
    OSGUInt16 getGroupId (void) const;

    /*------------------------ general info ---------------------------------*/

    OSGFieldContainerType *getParent(void);

    const char            *getName  (void) const;

    /*------------------------- prototye ------------------------------------*/

    OSGFieldContainerPtr getPrototype(void);
    OSGBool              setPrototype(OSGFieldContainerPtr prototype);

    /*----------------------------- create ----------------------------------*/

    OSGNodePtr       createNode      (void);
	OSGNodeCorePtr   createNodeCore  (void);
	OSGAttachmentPtr createAttachment(void);

    /*-------------------------- properties ---------------------------------*/

	OSGBool isAbstract   (void) const;

    OSGBool isNode       (void) const;
    OSGBool isNodeCore   (void) const;
    OSGBool isAttachment (void) const;

    OSGBool isDerivedFrom(const OSGFieldContainerType &other) const;
        
    /*------------------------- description ---------------------------------*/

	OSGFieldDescription *findFieldDescription   (const char *fieldName) const;
    OSGFieldDescription *getFieldDescription    (const OSGUInt32 index) const;

    OSGUInt32            getNumFieldDescriptions(void)                  const;

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

    OSGFieldContainerType(const OSGFieldContainerType &obj);

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

	OSGFieldContainerType *_parent;

    OSGBaseType            _baseType;

	map   <OSGStringLink,       OSGFieldDescription *> _descriptionMap;
    vector<OSGFieldDescription *>                      _descriptionVec;

    OSGFieldDescription   *_descA;
    OSGUInt32              _byteSizeOfDescA;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	void registerType(const OSGChar *group);

	void initialize  (void);
    void terminate   (void);

	// prohibit default functions (move to 'public' if you need one)
    void operator =(const OSGFieldContainerType &source);
};

typedef OSGFieldContainerType* OSGFieldContainerTypeP;

OSG_END_NAMESPACE

#endif // _OSGFIELDCONTAINERTYPE_H_
