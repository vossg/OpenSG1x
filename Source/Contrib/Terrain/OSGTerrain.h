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

#ifndef _OSGTERRAIN_H_
#define _OSGTERRAIN_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGTerrainBase.h>
#include <OSGSHLChunk.h>
#include <OSGVertexProgramChunk.h>
#include <OSGFragmentProgramChunk.h>

OSG_BEGIN_NAMESPACE

/*! \brief Terrain class. See \ref 
           PageExperimentalTerrain for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING Terrain : public TerrainBase
{
  private:

    typedef TerrainBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TerrainBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Terrain(void);
    Terrain(const Terrain &source);

    /*! \}                                                                 */
    VertexProgramChunkPtr   createVPChunk () const;
    FragmentProgramChunkPtr createFPChunk () const;
    SHLChunkPtr  createSHLChunk () const;
    ImagePtr     createNormalMap () const;
    void         addMaterialChunks () const;
    Real32       getHeightDataScaled (UInt32 i) const;
    void         getVertex (UInt32 i, Pnt3f& point) const;
    const Pnt3f& getVertex (UInt32 i) const;
    Real32       getHeightAboveGround (const Pnt3f& eye);
    Real32       getHeight(Int32 index, Int32 width, Int32 dirToFather, Int32 neswc, Real32 blend,
			   Real32 rhNW, Real32 rhNE, Real32 rhSW, Real32 rhSE);
    Real32       calcSubDiv(Int32 nodeIndex, Int32 width);
    Real32       calcBlend(Real32 subDiv);

    UInt32 getNumVertices () const;
    void   calcD2ErrorMatrix ();
    void   calcD2ErrorMatrixRec(Int32 centerX, Int32 centerZ, Int32 width, Int32 level);
    Real32 calcD2Value       (Int32 centerX, Int32 centerZ, Int32 width);
    void   propagateD2Errors ();

    void            deleteNode (Int32 index, Int32 width);
    void            triangulateMeshRec (const FrustumVolume& frustum, 
					Int32 c, Int32 width, Int32 level);
    bool            renderMeshRec (const FrustumVolume& frustum, 
				   Int32 x, Int32 z, Int32 width, Int32 level, Int32 dirToFather,
				   Real32 rhNW, Real32 rhNE, Real32 rhSW, Real32 rhSE);
    void            createFanAround (Int32 x, Int32 z, Int32 width, bool* corners, bool isLeaf,
				     Real32 hC,  Real32 hN,  Real32 hS,  Real32 hW,  Real32 hE,
				     Real32 hNW, Real32 hNE, Real32 hSW, Real32 hSE);
    void            setInterleaved(Int32 index, Real32 height);

    Action::ResultE renderEnter  (Action* action);
    void            adjustVolume (Volume& volume);

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Terrain(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TerrainBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Terrain &source);
};

typedef Terrain *TerrainP;

OSG_END_NAMESPACE

#include <OSGTerrainBase.inl>
#include <OSGTerrain.inl>

#define OSGTERRAIN_HEADER_CVSID "@(#)$Id: OSGTerrain.h,v 1.1 2005/04/24 19:45:49 dirk Exp $"

#endif /* _OSGTERRAIN_H_ */
