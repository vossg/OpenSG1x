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


#ifndef _OSGMFIELD_H_
#define _OSGMFIELD_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
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

#if !defined(__sun) && !defined(WIN32)  && !defined(__linux)

#pragma set woff 1375

template<class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
class OSGMFieldVector : public vector<_Tp, _Alloc>
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

    static const char *getClassname(void) { return "OSGMFieldVector"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    explicit OSGMFieldVector(const typename Inherited::allocator_type &__a = 
                                 allocator_type());

             OSGMFieldVector(typename Inherited::size_type  __n, 
                             _Tp                            __value,
                             const typename Inherited::allocator_type &__a = 
                                 allocator_type());

    explicit OSGMFieldVector(typename Inherited::size_type __n);

             OSGMFieldVector(const OSGMFieldVector &__x);
    
#ifdef __STL_MEMBER_TEMPLATES
    /** \brief Creates a vector with a copy of a range. 
     */

    template <class _InputIterator>
             OSGMFieldVector(_InputIterator                            __first,
                             _InputIterator                            __last,
                             const typename Inherited::allocator_type &__a =
                                 allocator_type()) :
                 Inherited(__first, __last, __a) {}
#else
             OSGMFieldVector(const _Tp                                *__first,
                             const _Tp                                *__last,
                             const typename Inherited::allocator_type &__a = 
                                 allocator_type());
#endif /* __STL_MEMBER_TEMPLATES */

    ~OSGMFieldVector();

    /*------------------------- assignment ----------------------------------*/

    OSGMFieldVector<_Tp, _Alloc> &operator =(
        const OSGMFieldVector<_Tp, _Alloc> &__x);

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
 *  \brief Base class for all multi field, for example ::OSGMFMatrix
 */

template <class OSGFieldTypeT>
class OSGMField : public OSGField
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

#if !defined(__sun) && !defined(WIN32)  && !defined(__linux)
    typedef OSGMFieldVector<OSGFieldTypeT>                  OSGStorageType;

    typedef typename OSGMFieldVector<OSGFieldTypeT>::
        iterator        iterator;
    typedef typename OSGMFieldVector<OSGFieldTypeT>::
        const_iterator  const_iterator;

    typedef typename OSGMFieldVector<OSGFieldTypeT>::
        reference       reference;
    typedef typename OSGMFieldVector<OSGFieldTypeT>::
        const_reference const_reference;
#else
    typedef vector<OSGFieldTypeT>                  OSGStorageType;

    typedef typename vector<OSGFieldTypeT>::
        iterator        iterator;
    typedef typename vector<OSGFieldTypeT>::
        const_iterator  const_iterator;

    typedef typename vector<OSGFieldTypeT>::
        reference       reference;
    typedef typename vector<OSGFieldTypeT>::
        const_reference const_reference;
#endif
    
    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static const OSGFieldType _fieldType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char         *getClassname(void) { return "OSGMField"; };
    static const OSGFieldType &getClassType(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGMField         (void);
    OSGMField         (const OSGUInt32   size);
    OSGMField         (const OSGMField  &obj);

    virtual ~OSGMField(void); 

    /*------------------------------ access ---------------------------------*/

          OSGFieldTypeT  &getValue (const OSGUInt32 index);
    const OSGFieldTypeT  &getValue (const OSGUInt32 index) const;

          OSGStorageType &getValues(void);
	const OSGStorageType &getValues(void) const;

    void setAbstrValue(const OSGField &obj);

    void setValue (const OSGFieldTypeT            &value,
                   const OSGUInt32                 index);
    void setValues(const OSGStorageType           &value);
	void setValues(const OSGMField<OSGFieldTypeT> &obj  );

    /*------------------------- container interface -------------------------*/

    void addValue (const OSGFieldTypeT            &value);

    iterator        begin (void);
    iterator        end   (void);
    
    const_iterator  begin (void) const;
    const_iterator  end   (void) const;

    reference       front (void);
    const_reference front (void) const;

    reference       back  (void);
    const_reference back  (void) const;

    iterator        insert(iterator pos, const OSGFieldTypeT &value);
    iterator        erase (iterator pos);

    void            clear (void);

    iterator        find(const OSGFieldTypeT &value);
    const_iterator  find(const OSGFieldTypeT &value) const;

    void            resize(size_t newsize);

    void            push_back(const OSGFieldTypeT &value);

    /*----------------------- field information -----------------------------*/

	OSGField::Cardinality getCardinality (void) const;

	// OSGMField has a vector<> interface and an OSG interface, so both are 
	// sensible
    virtual OSGUInt32     size           (void) const;
            OSGUInt32     getSize        (void) const;

    /*-------------------------- field type ---------------------------------*/

	virtual const OSGFieldType &getType (void) const;

    /*-------------------------- string io ----------------------------------*/

	virtual void       setValueByStr(const char *str);
    virtual OSGString &getStrValue  (OSGString &string) const;

    /*-------------------------- index operator------------------------------*/

          OSGFieldTypeT &operator [](OSGUInt32 index);
    const OSGFieldTypeT &operator [](OSGUInt32 index) const;

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    OSGStorageType  _values;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual void doSync(OSGField *source);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGField Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------
    
    friend class OSGFieldContainer;

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

	static OSGField *create(void);

    void beginEdit(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    void operator =(const OSGMField &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGMField.inl>

#endif /* _OSGSFIELD_H_ */

