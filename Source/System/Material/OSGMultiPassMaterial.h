/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGMULTIPASSMATERIAL_H_
#define _OSGMULTIPASSMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGMultiPassMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiPassMaterial class. See \ref 
           PageSystemMultiPassMaterial for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING MultiPassMaterial : public MultiPassMaterialBase
{
  private:

    typedef MultiPassMaterialBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

    virtual void       draw              (DrawFunctor& func,
                                          DrawActionBase * action );

    virtual void       draw              (Geometry* geo,
                                          DrawActionBase * action);

    virtual StatePtr   makeState         (void);

    virtual void       rebuildState      (void);
    virtual StatePtr   getState          (UInt32 index = 0);
    virtual bool       isMultiPass       (void) const;
    virtual UInt32     getNPasses        (void) const;

    virtual bool       isTransparent     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void addMaterial(MaterialPtr mat);
    void subMaterial(MaterialPtr mat);

    bool hasMaterial(MaterialPtr mat);

#ifdef OSG_2_PREP
    void subMaterialByObj(MaterialPtr value);
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MultiPassMaterialBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiPassMaterial(void);
    MultiPassMaterial(const MultiPassMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiPassMaterial(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MultiPassMaterialBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MultiPassMaterial &source);
};

typedef MultiPassMaterial *MultiPassMaterialP;

OSG_END_NAMESPACE

#include "OSGMultiPassMaterialBase.inl"
#include "OSGMultiPassMaterial.inl"

#define OSGMULTIPASSMATERIAL_HEADER_CVSID "@(#)$Id: OSGMultiPassMaterial.h,v 1.5 2009/01/28 03:06:14 vossg Exp $"

#endif /* _OSGMULTIPASSMATERIAL_H_ */
