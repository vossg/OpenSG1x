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

#ifndef _OSGCHANGEDCHANGELISTMIXIN_HPP_
#define _OSGCHANGEDCHANGELISTMIXIN_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGMemoryObject.h>

#include <vector>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! ChangedChangeListMixin
//! \ingroup 

template <class ChangeListDescT>
class OSG_BASE_DLLMAPPING ChangedChangeListMixin : public MemoryObject
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef MemoryObject Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef          ChangeListDescT              Desc;
    
    typedef typename Desc::ContainerId            ContainerId;
    typedef typename Desc::ChangedMask            ChangedMask;

    typedef          std::pair  <ContainerId, 
                                 ChangedMask    > ChangedEntry;

    typedef          std::vector<ChangedEntry   > ChangedStore;

    typedef typename ChangedStore::size_type      changed_size_type;
    typedef typename ChangedStore::const_iterator changed_const_iterator;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
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

    //-----------------------------------------------------------------------
    //   friend functions                                                    
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

    //! prohibit default function (move to 'public' if needed) 
    ChangedChangeListMixin(const ChangedChangeListMixin &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const ChangedChangeListMixin &source);

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

    ChangedStore _vChangedContainerStore;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void clear(void);
    void merge(ChangedChangeListMixin &other);
    
  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ChangedChangeListMixin(void);

    virtual ~ChangedChangeListMixin(void); 

    /*------------------------- your_category -------------------------------*/

    changed_size_type      sizeChanged (void) const;

    changed_const_iterator beginChanged(void) const;
    changed_const_iterator endChanged  (void) const;

    /*------------------------- your_category -------------------------------*/

    void                   addChanged  (const ContainerId &oContainerId, 
                                              ChangedMask  oChangedMask);

    /*------------------------- your_category -------------------------------*/

    void clearChanged(void);

    void mergeChanged(ChangedChangeListMixin &other);
};

OSG_END_NAMESPACE

#define OSGCHANGEDCHANGELISTMIXIN_HEADER_CVSID "@(#)$Id: $"

#include <OSGChangedChangeListMixin.inl>

#endif /* _OSGCHANGEDCHANGELISTMIXIN_HPP_ */
