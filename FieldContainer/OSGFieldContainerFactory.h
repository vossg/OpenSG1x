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


#ifndef _OSGFIELDCONTAINERFACTORY_CLASS_DECLARATION_H_
#define _OSGFIELDCONTAINERFACTORY_CLASS_DECLARATION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>
#include <vector>
#include <OSGStringLink.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGFieldContainer;
class OSGFieldContainerType;
class OSGLock;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSGFieldContainerFactory 
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

    static        void                          dump         (void);
    static const  vector<OSGFieldContainerPtr> *getFieldStore(void);


    /** Destructor */
    virtual ~OSGFieldContainerFactory (void);

    /** get method for attribute the */
    static OSGFieldContainerFactory the (void) { return _the; }

	/**  */

	static OSGBool   initialize   (int argc, char **argv);
    static OSGBool   terminate    (void);

    static OSGUInt32 registerFieldContainer(
        const OSGFieldContainerPtr &fieldP);

    /**  */
    OSGFieldContainerType * findType (int Id);

    /**  */
    OSGFieldContainerType * findType (const char *name);

		
	const OSGChar * findGroupName (OSGUInt16 Id);

		
	OSGUInt16 findGroupId (const OSGChar * name);

		
	OSGUInt16 getGroupCount (void) { return _groupMap ? _groupMap->size() : 0;}

    /*------------------------- assignment ----------------------------------*/

	OSGNodePtr       createNode      (const char *name);
	OSGNodeCorePtr   createNodeCore  (const char *name);
	OSGAttachmentPtr createAttachment(const char *name);

	OSGUInt32 getTypeCount(void) 
    { 
        return _typeNameMap ? _typeNameMap->size() : 0; 
    }


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

	friend class OSGFieldContainerType;
	friend class OSGAttachment;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static OSGFieldContainerFactory _the;

    static OSGBool                                   _initialized;

    static map <int, OSGFieldContainerType* >       *_typeIdMap;

    static map <OSGString, OSGFieldContainerType* > *_typeNameMap;

	static map <OSGString, OSGUInt16>               *_groupMap;

    static vector<OSGFieldContainerPtr>             *_fieldcontainerStoreV;

    static OSGLock                                  *_storeLock;

	//-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

	static void initTypeMap();

	/**  method to add a group, retuns the group Id */
	static OSGUInt16 addGroup(const OSGChar *groupName);

    /** Default Constructor */
    OSGFieldContainerFactory (void);

    /** Copy Constructor */
    OSGFieldContainerFactory (const OSGFieldContainerFactory &obj);

 
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGFieldContainerFactory* OSGFieldContainerFactoryP;

OSG_END_NAMESPACE

#endif // OSGFIELDCONTAINERFACTORY_CLASS_DECLARATION
