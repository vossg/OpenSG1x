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


#ifndef _OSGCHANGELIST_H_
#define _OSGCHANGELIST_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>
#include <OSGBaseTypes.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGThread;
class OSGField;

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

class OSGChangeList
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum OSGMode
    {
        OSGPrivate,
        OSGPublic
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef pair<OSGFieldContainerPtr, OSGBitVector> OSGChangeEntry;
    typedef OSGFieldContainerPtr                     OSGRefEntry;

    typedef vector<OSGChangeEntry>::size_type      changed_size_type;
    typedef vector<OSGChangeEntry>::const_iterator changed_const_iterator;

    typedef vector<OSGRefEntry>::size_type         refd_size_type;
    typedef vector<OSGRefEntry>::const_iterator    refd_const_iterator;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGChangeList"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGChangeList(void);

    virtual ~OSGChangeList(void); 

    /*------------------------- your_category -------------------------------*/

    changed_size_type      sizeChanged (void);

    changed_const_iterator beginChanged(void) const;
    changed_const_iterator endChanged  (void) const;

    refd_size_type         sizeAddRefd (void);

    refd_const_iterator    beginAddRefd(void) const;
    refd_const_iterator    endAddRefd  (void) const;

    refd_size_type         sizeSubRefd (void);

    refd_const_iterator    beginSubRefd(void) const;
    refd_const_iterator    endSubRefd  (void) const;

    void    addChanged  (const OSGFieldContainerPtr &fieldP, 
                               OSGBitVector          whichField);
    void    addAddRefd  (const OSGFieldContainerPtr &fieldP);
    void    addSubRefd  (const OSGFieldContainerPtr &fieldP);

    void    clearAll(void);
    OSGBool merge   (const OSGChangeList &list);

    void    applyTo       (OSGUInt32 aspectId);
    void    applyToCurrent(void);

    void    setAspect  (OSGUInt32 aspectId);

    void    setReadOnly(OSGBool readOnly);

    void    dump(void);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGChangeList &other) const;
    
	//OSGBool operator == (const OSGChangeList &other) const;
	//OSGBool operator != (const OSGChangeList &other) const;

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

    friend class OSGThread;

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

    bool              _bReadOnly;

    OSGUInt32         _aspectId;
    OSGMode           _listMode;

    vector<OSGChangeEntry> _changedFieldContainerV;
    vector<OSGRefEntry>    _addRefdFieldContainerV;
    vector<OSGRefEntry>    _subRefdFieldContainerV;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    OSGChangeList(const OSGChangeList &source);
    void operator =(const OSGChangeList &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGChangeList *OSGChangeListP;

OSG_END_NAMESPACE

#endif /* _CLASSNAME_H_ */
