/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGSFIELD_H_
#define _OSGSFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGStringConversionStateBase.h>

#include <vector>
#include <string>

#include <OSGField.h>

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSField.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
 */
#endif

class BinaryDataHandler;

/*! Base class for all single fields, for example SFMatrix.
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
 */

template <class FieldTypeT, Int32 fieldNameSpace = 0>
class SField : public Field 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename osgIF<fieldNameSpace == 0,
                           FieldDataTraits <FieldTypeT>,
                           InvalidTrait                >::_IRet SF0Trait;

    typedef typename osgIF<fieldNameSpace == 1,
                           FieldDataTraits1<FieldTypeT>,
                           SF0Trait                    >::_IRet SF1Trait;

    typedef typename osgIF<fieldNameSpace == 2, 
                           FieldDataTraits2<FieldTypeT>, 
                           SF1Trait                     >::_IRet SFieldTraits;

    typedef          SField<FieldTypeT, fieldNameSpace>          Self;



    typedef          FieldTypeT                  StoredType;
    typedef          FieldTypeT                 &reference;
    typedef const    FieldTypeT                 &const_reference;
    typedef typename SFieldTraits::ArgumentType  ArgumentType;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             SField(void                     );
             SField(const SField       &obj  );
    explicit SField(      ArgumentType  value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual       UInt32      getSize (void) const;

                  reference   getValue(void);
            const_reference   getValue(void) const;

    virtual const FieldType  &getType (void) const;

    virtual       bool        isEmpty (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

            void setValue     (      ArgumentType  value);
            void setValue     (const Self         &obj  );

    virtual void setAbstrValue(const Field        &obj  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   String IO                                  */
    /*! \{                                                                 */

    virtual void         pushValueByStr(const Char8             *str  );
    virtual std::string &getValueByStr (      std::string       &str  ) const;
    virtual std::string &getValueByStr (      std::string       &str,
                                      StringConversionStateBase &state) const;
    virtual std::string &getValueByStr (      std::string       &str,
                                              UInt32             index) const;

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
    /*! \name                      Assign                                  */
    /*! \{                                                                 */

    void operator =(const SField &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Field Inherited;

    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

    static const FieldType   _fieldType;

                 FieldTypeT  _value;

    static       Field      *create(void);

    /*---------------------------------------------------------------------*/

    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#include <OSGSField.inl>

#define OSGSFIELD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSFIELD_H_ */

