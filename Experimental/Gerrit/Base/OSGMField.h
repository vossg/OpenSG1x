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

#ifndef _OSGMFIELD_H_
#define _OSGMFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGField.h>
#include <OSGMFieldVector.h>
#include <OSGStringConversionStateBase.h>

#include <vector>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \defgroup MultiFields MultiFields
    \brief OpenSG Multi Fields
*/

class BinaryDataHandler;

//! Base class for all multi field, for example ::MFMatrix
//! \ingroup FieldLib
//! \ingroup MultiFields

template <class FieldTypeT, Int32 fieldNameSpace = 0>
class MField : public Field
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef          MFieldVector<FieldTypeT>     StorageType;

    typedef typename StorageType::iterator        iterator;
    typedef typename StorageType::const_iterator  const_iterator;

    typedef typename StorageType::reference       reference;
    typedef typename StorageType::const_reference const_reference;
    
    typedef typename osgIF<fieldNameSpace == 1,
                           FieldDataTraits1<FieldTypeT>,
                           FieldDataTraits2<FieldTypeT> >::_IRet MF1Trait;

    typedef typename osgIF<fieldNameSpace == 0, 
                           FieldDataTraits <FieldTypeT>, 
                           MF1Trait>::_IRet MFieldTraits;

    typedef          MField<FieldTypeT, fieldNameSpace>          Self;

    typedef          FieldTypeT                                  StoredType;

    typedef          MFieldTraits::ArgumentType                  ArgumentType;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             MField(void);
             MField(const MField  &obj);
    explicit MField(const UInt32   size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

                  StorageType &getValues(void);
            const StorageType &getValues(void) const;
 
    virtual const FieldType   &getType  (void) const;

    virtual       bool         isEmpty  (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void setAbstrValue(const Field       &obj  );

            void setValues    (const StorageType &value);
            void setValues    (const Self        &obj  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */

    iterator        begin    (void);
    iterator        end      (void);
    
    const_iterator  begin    (void) const;
    const_iterator  end      (void) const;
    
    reference       front    (void);
    const_reference front    (void) const;
    
    reference       back     (void);
    const_reference back     (void) const;
    
    void            clear    (void);
    
    iterator        insert   (iterator pos, ArgumentType value);
    iterator        erase    (iterator pos                    );
    
    iterator        find     (ArgumentType value);
    const_iterator  find     (ArgumentType value) const;
    
    void            push_back(ArgumentType value);
    
    void            resize   (size_t newsize);
    void            reserve  (size_t newsize);
    
    UInt32          size     (void          ) const;
    bool            empty    (void          ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

          reference operator [](UInt32 index);
    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   String IO                                  */
    /*! \{                                                                 */

    virtual void    pushValueByStr(const Char8               *str  );
    virtual string &getValueByStr (string                    &str  ) const;
    virtual string &getValueByStr (string                    &str,
                                   StringConversionStateBase &state) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

    void syncWith(Self &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   );
    
    void   copyToBin  (BinaryDataHandler &pMem);
    void   copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef Field Inherited;

    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

    static const FieldType    _fieldType;

                 StorageType  _values;


    static       Field       *create(void);

    /*---------------------------------------------------------------------*/

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MField &source);
};

OSG_END_NAMESPACE

#include <OSGMField.inl>

#define OSGMFIELD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGMFIELD_H_ */

