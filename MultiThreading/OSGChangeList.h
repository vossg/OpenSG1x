/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSGCHANGELIST_H_
#define _OSGCHANGELIST_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGMemoryObject.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Thread;
class Field;


//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseThreading
 *  \brief ChangeList
 */

class OSG_SYSTEMLIB_DLLMAPPING ChangeList : public MemoryObject
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum Mode
    {
        Private,
        Public
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

//    typedef pair<FieldContainerPtr, BitVector>  ChangeEntry;

    typedef pair<UInt32, BitVector>             ChangeEntry;     
    typedef FieldContainerPtr                   RefEntry;    
    typedef UInt32                              IdRefEntry;

    typedef vector<ChangeEntry>::size_type      changed_size_type;
    typedef vector<ChangeEntry>::const_iterator changed_const_iterator;

//    typedef vector<RefEntry>::size_type       refd_size_type;
//    typedef vector<RefEntry>::const_iterator  refd_const_iterator;

    typedef vector<IdRefEntry>::size_type       refd_size_type;
    typedef vector<IdRefEntry>::const_iterator  refd_const_iterator;

    typedef vector<IdRefEntry>::size_type       idrefd_size_type;
    typedef vector<IdRefEntry>::const_iterator  idrefd_const_iterator;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef MemoryObject Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class Thread;

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

    Bool           _bReadOnly;

    UInt32         _uiAspectId;
    Mode           _listMode;

    vector<ChangeEntry> _vChangedFieldContainers;

//    vector<RefEntry>    _vAddRefdFieldContainers;
//    vector<RefEntry>    _vSubRefdFieldContainers;

    vector<IdRefEntry>  _vAddRefdFieldContainers;
    vector<IdRefEntry>  _vSubRefdFieldContainers;
    
    vector<IdRefEntry>  _vCreatedFieldContainers;
    vector<IdRefEntry>  _vDestroyedFieldContainers;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    ChangeList(const ChangeList &source);
    void operator =(const ChangeList &source);

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

  public:

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ChangeList(void);
    virtual ~ChangeList(void); 

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

    idrefd_const_iterator  beginCreated(void) const;
    idrefd_const_iterator  endCreated  (void) const;

    idrefd_size_type       sizeCreated (void) const;

    idrefd_const_iterator  beginDestroyed(void) const;
    idrefd_const_iterator  endDestroyed  (void) const;

    idrefd_size_type       sizeDestroyed (void) const;

    void addChanged  (const FieldContainerPtr &pFieldContainer, 
                               BitVector       bvWhichField);
    void addAddRefd  (const FieldContainerPtr &pFieldContainer);
    void addSubRefd  (const FieldContainerPtr &pFieldContainer);

    void addCreated  (const UInt32 uiContainerId);
    void addDestroyed(const UInt32 uiContainerId);
    
    void clearAll    (void);
    Bool merge       (const ChangeList &list);

    void setAspect  (UInt32 uiAspectId);

    void setReadOnly(Bool bReadOnly);

    void applyTo       (UInt32 uiAspectId);
    void applyToCurrent(void);

    void dump(void);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef ChangeList *ChangeListP;

OSG_END_NAMESPACE

#endif /* _CLASSNAME_H_ */
