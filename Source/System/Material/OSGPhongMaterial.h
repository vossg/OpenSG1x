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

#ifndef _OSGPHONGMATERIAL_H_
#define _OSGPHONGMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGMaterialChunk.h>
#include <OSGBlendChunk.h>
#include <OSGVertexProgramChunk.h>
#include <OSGFragmentProgramChunk.h>

#include <OSGPhongMaterialBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief PhongMaterial class. See \ref
           PageKernelPhongMaterial for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING PhongMaterial : public PhongMaterialBase
{
  private:

    typedef PhongMaterialBase Inherited;

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
  
    static ChunkMaterialPtr createChunkMaterial(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhongMaterialBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhongMaterial(void);
    PhongMaterial(const PhongMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhongMaterial(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    void prepareLocalChunks(void);
    void createFragmentProgram(void);

    friend class FieldContainer;
    friend class PhongMaterialBase;

    static void initMethod(void);
    
    static UInt32 _arbFragmentProgram;

    MaterialChunkPtr        _materialChunk;
    BlendChunkPtr           _blendChunk;
    VertexProgramChunkPtr   _vpChunk;
    FragmentProgramChunkPtr _fpChunk;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhongMaterial &source);
};

typedef PhongMaterial *PhongMaterialP;

OSG_END_NAMESPACE

#include <OSGPhongMaterialBase.inl>
#include <OSGPhongMaterial.inl>

#define OSGPHONGMATERIAL_HEADER_CVSID "@(#)$Id: OSGPhongMaterial.h,v 1.4 2003/10/10 15:38:50 a-m-z Exp $"

#endif /* _OSGPHONGMATERIAL_H_ */
