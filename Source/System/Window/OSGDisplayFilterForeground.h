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

#ifndef _OSGDISPLAYFILTERFOREGROUND_H_
#define _OSGDISPLAYFILTERFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include "OSGDisplayFilterForegroundBase.h"

#include <OSGViewport.h>
#include <OSGViewport.h>
#include <OSGTextureChunk.h>
#include <OSGGeometry.h>
#include <OSGChunkMaterial.h>
#include <OSGComponentTransform.h>
#include <OSGBackground.h>
#include <OSGTextureTransformChunk.h>

OSG_BEGIN_NAMESPACE

/*! \brief DisplayFilterForeground class. See \ref 
           PageSystemDisplayFilterForeground for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING DisplayFilterForeground : public DisplayFilterForegroundBase
{
  private:

    typedef DisplayFilterForegroundBase Inherited;
    /*==========================  PUBLIC  =================================*/
  public:

    class OSG_SYSTEMLIB_DLLMAPPING DisplayFilterGroup {
    public:
        DisplayFilterGroup(bool readback,std::vector<ViewportPtr> &ports);
        virtual ~DisplayFilterGroup();
        TextureChunkPtr       getTexture   (void);
        GeometryPtr           getGeometry  (void);
        ChunkMaterialPtr      getMaterial  (void);
        ComponentTransformPtr getTransform (void);
        TextureTransformChunkPtr getTextureTransform (void);
        void                  createGrid   (UInt32 width,UInt32 height);
    protected:
        ViewportPtr              _vp;
        NodePtr                  _root;
        TextureChunkPtr          _texture;
        GeometryPtr              _geometry;
        ChunkMaterialPtr         _material;
        ComponentTransformPtr    _transform;
        BackgroundPtr            _background;
        TextureTransformChunkPtr _textureTransform;

    };

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
    /*! \name                   draw                                       */
    /*! \{                                                                 */

    virtual void draw( DrawActionBase * action, Viewport * port );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   correction group handling                  */
    /*! \{                                                                 */

    DisplayFilterGroup *findReadbackGroup(const std::string &name);
    DisplayFilterGroup *findOverlayGroup (const std::string &name);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DisplayFilterForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DisplayFilterForeground(void);
    DisplayFilterForeground(const DisplayFilterForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DisplayFilterForeground(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   correction group handling                  */
    /*! \{                                                                 */

    void clearGroups();

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    std::vector<ViewportPtr>                  _port;
    std::map<std::string,DisplayFilterGroup*> _group;
    std::vector<UInt32>                       _changedState;
    bool                                      _hasNonPowTwoTex;

    friend class FieldContainer;
    friend class DisplayFilterForegroundBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DisplayFilterForeground &source);
};

typedef DisplayFilterForeground *DisplayFilterForegroundP;

OSG_END_NAMESPACE

#include "OSGDisplayFilterForegroundBase.inl"
#include "OSGDisplayFilterForeground.inl"

#define OSGDISPLAYFILTERFOREGROUND_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.22 2004/08/03 05:53:03 dirk Exp $"

#endif /* _OSGDISPLAYFILTERFOREGROUND_H_ */
