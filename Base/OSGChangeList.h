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
#include <OSGMemoryObject.h>

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

class OSG_BASE_DLLMAPPING ChangeList : public MemoryObject
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

    typedef pair<FieldContainerPtr, BitVector> ChangeEntry;
    typedef FieldContainerPtr                     RefEntry;

    typedef vector<ChangeEntry>::size_type      changed_size_type;
    typedef vector<ChangeEntry>::const_iterator changed_const_iterator;

    typedef vector<RefEntry>::size_type         refd_size_type;
    typedef vector<RefEntry>::const_iterator    refd_const_iterator;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "ChangeList"; };

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

    void    addChanged  (const FieldContainerPtr &fieldP, 
                               BitVector          whichField);
    void    addAddRefd  (const FieldContainerPtr &fieldP);
    void    addSubRefd  (const FieldContainerPtr &fieldP);

    void    clearAll(void);
    Bool    merge   (const ChangeList &list);

    void    applyTo       (UInt32 aspectId);
    void    applyToCurrent(void);

    void    setAspect  (UInt32 aspectId);

    void    setReadOnly(Bool readOnly);

    void    dump(void);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const ChangeList &other) const;
    
	//Bool operator == (const ChangeList &other) const;
	//Bool operator != (const ChangeList &other) const;

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

    typedef MemoryObject Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSG_BASE_DLLMAPPING Thread;

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

    Bool                _bReadOnly;

    UInt32              _aspectId;
    Mode                _listMode;

    vector<ChangeEntry> _changedFieldContainerV;
    vector<RefEntry>    _addRefdFieldContainerV;
    vector<RefEntry>    _subRefdFieldContainerV;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    ChangeList(const ChangeList &source);
    void operator =(const ChangeList &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef ChangeList *ChangeListP;

OSG_END_NAMESPACE

#endif /* _OSGCHANGELIST_H_ */

