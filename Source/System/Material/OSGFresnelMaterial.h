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

#ifndef _OSGFRESNELMATERIAL_H_
#define _OSGFRESNELMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGTexGenChunk.h>
#include <OSGBlendChunk.h>
#include <OSGImage.h>

#include <OSGFresnelMaterialBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief FresnelMaterial class. See \ref
           PageKernelFresnelMaterial for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING FresnelMaterial : public FresnelMaterialBase
{
  private:

    typedef FresnelMaterialBase Inherited;

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

    virtual StatePtr    makeState       (void);
    virtual void        rebuildState    (void);
    virtual bool        isTransparent   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Texture specific                              */
    /*! \{                                                                 */
    
    void setImage           (ImagePtr &pImage);
      
      
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FresnelMaterialBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FresnelMaterial(void);
    FresnelMaterial(const FresnelMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FresnelMaterial(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    void prepareLocalChunks(void);
    void updateFresnel(void);

    friend class FieldContainer;
    friend class FresnelMaterialBase;

    static void initMethod(void);

    MaterialChunkPtr       _materialChunk;
    TextureChunkPtr        _textureChunk;
    TexGenChunkPtr         _texGenChunk;
    BlendChunkPtr          _blendChunk;
    ImagePtr               _img;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FresnelMaterial &source);
};

typedef FresnelMaterial *FresnelMaterialP;

OSG_END_NAMESPACE

#include <OSGFresnelMaterialBase.inl>
#include <OSGFresnelMaterial.inl>

#define OSGFRESNELMATERIAL_HEADER_CVSID "@(#)$Id: OSGFresnelMaterial.h,v 1.2 2004/02/05 21:49:58 a-m-z Exp $"

#endif /* _OSGFRESNELMATERIAL_H_ */
