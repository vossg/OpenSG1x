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

#ifndef _OSGMFIELD_H_
#define _OSGMFIELD_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGField.h>

#include <vector>

OSG_BEGIN_NAMESPACE

/** \defgroup MultiFields MultiFields
 *  \brief OpenSG Multi Fields
 */

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief Internal vector representation to do the multithreading stuff
 *  hopefully fast enough.
 */

#if defined(FU) && !defined(__sun) && !defined(WIN32)  && !defined(__linux)

#pragma set woff 1375

template<class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
class MFieldVector : public vector<_Tp, _Alloc>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef vector<_Tp, _Alloc> Inherited;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "MFieldVector"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    explicit MFieldVector(const typename Inherited::allocator_type &__a = 
                                 allocator_type());

             MFieldVector(typename Inherited::size_type  __n, 
                             _Tp                            __value,
                             const typename Inherited::allocator_type &__a = 
                                 allocator_type());

    explicit MFieldVector(typename Inherited::size_type __n);

             MFieldVector(const MFieldVector &__x);
    
#ifdef __STL_MEMBER_TEMPLATES
    /** \brief Creates a vector with a copy of a range. 
     */

    template <class _InputIterator>
             MFieldVector(_InputIterator                            __first,
                             _InputIterator                            __last,
                             const typename Inherited::allocator_type &__a =
                                 allocator_type()) :
                 Inherited(__first, __last, __a) {}
#else
             MFieldVector(const _Tp                                *__first,
                             const _Tp                                *__last,
                             const typename Inherited::allocator_type &__a = 
                                 allocator_type());
#endif /* __STL_MEMBER_TEMPLATES */

    ~MFieldVector();

    /*------------------------- assignment ----------------------------------*/

    MFieldVector<_Tp, _Alloc> &operator =(
        const MFieldVector<_Tp, _Alloc> &__x);

    /*------------------------- comparison ----------------------------------*/

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

#pragma reset woff 1375

#endif

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief Base class for all multi field, for example ::MFMatrix
 */

template <class FieldTypeT, Int32 fieldNameSpace = 0>
class OSG_FIELD_DLLMAPPING MField : public Field
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

#if defined(FU) && !defined(__sun) && !defined(WIN32)  && !defined(__linux)
    typedef MFieldVector<FieldTypeT>                  StorageType;

    typedef typename MFieldVector<FieldTypeT>::
        iterator        iterator;
    typedef typename MFieldVector<FieldTypeT>::
        const_iterator  const_iterator;

    typedef typename MFieldVector<FieldTypeT>::
        reference       reference;
    typedef typename MFieldVector<FieldTypeT>::
        const_reference const_reference;
#else
    typedef          vector<FieldTypeT>                  StorageType;

    typedef typename vector<FieldTypeT>::iterator        iterator;
    typedef typename vector<FieldTypeT>::const_iterator  const_iterator;

    typedef typename vector<FieldTypeT>::reference       reference;
    typedef typename vector<FieldTypeT>::const_reference const_reference;
#endif
    
    typedef typename osgIF<fieldNameSpace == 1,
                           FieldDataTraits1<FieldTypeT>,
                           FieldDataTraits2<FieldTypeT> >::_IRet MF1Trait;

    typedef typename osgIF<fieldNameSpace == 0, 
                           FieldDataTraits <FieldTypeT>, 
                           MF1Trait>::_IRet MFieldTraits;


    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const Char8     *getClassname(void) { return "MField"; };
    static const FieldType &getClassType(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    MField         (void);
    MField         (const MField  &obj);
    explicit MField(const UInt32   size);

    virtual ~MField(void); 

    /*------------------------------ access ---------------------------------*/

          FieldTypeT  &getValue (const UInt32 index);
    const FieldTypeT  &getValue (const UInt32 index) const;

          StorageType &getValues(void);
	const StorageType &getValues(void) const;

    void setAbstrValue(const Field &obj);

    void setValue (const FieldTypeT                         &value,
                   const UInt32                              index);
    void setValues(const StorageType                        &value);
	void setValues(const MField<FieldTypeT, fieldNameSpace> &obj  );

    /*------------------------- container interface -------------------------*/

    void addValue (const FieldTypeT            &value);

    iterator        begin (void);
    iterator        end   (void);
    
    const_iterator  begin (void) const;
    const_iterator  end   (void) const;

    reference       front (void);
    const_reference front (void) const;

    reference       back  (void);
    const_reference back  (void) const;

    iterator        insert(iterator pos, const FieldTypeT &value);
    iterator        erase (iterator pos);

    void            clear (void);

    iterator        find(const FieldTypeT &value);
    const_iterator  find(const FieldTypeT &value) const;

    void            resize(size_t newsize);
    void            reserve(size_t newsize);

    void            push_back(const FieldTypeT &value);

    /*----------------------- field information -----------------------------*/
    
    FieldType::Cardinality getCardinality (void) const;

	// MField has a vector<> interface and an OSG interface, so both are 
	// sensible
    virtual UInt32     size    (void) const;
            UInt32     getSize (void) const;

    /*-------------------------- field type ---------------------------------*/

	virtual const FieldType &getType (void) const;

    /*-------------------------- string io ----------------------------------*/

	virtual void    pushValueByStr(const Char8 *str);
    virtual String &getValueByStr (String &string) const;

    /*-------------------------- index operator------------------------------*/

          FieldTypeT &operator [](UInt32 index);
    const FieldTypeT &operator [](UInt32 index) const;

    /*------------------------------- dump ----------------------------------*/

    virtual void dump (void) const;

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

	static const FieldType _fieldType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    StorageType  _values;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual void doSync(Field *source);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Field Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------
    
    friend class FieldContainer;

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

	static Field *create(void);

    void beginEdit(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    void operator =(const MField &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGMField.inl>

#endif /* _OSGSFIELD_H_ */

