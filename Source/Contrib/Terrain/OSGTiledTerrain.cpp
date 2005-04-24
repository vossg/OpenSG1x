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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGTiledTerrain.h"
#include "OSGTerrain.h"
#include "OSGRenderAction.h"
#include "OSGImage.h"
#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TiledTerrain
Tiled terrain node core
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TiledTerrain::initMethod (void)
{
#if 0
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            FCPtr<MaterialGroupPtr, TiledTerrain>, 
            CNodePtr          ,  
            Action           *>(&TiledTerrain::drawEnter));
#endif  
    RenderAction::registerEnterDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            FCPtr<MaterialGroupPtr, TiledTerrain>, 
            CNodePtr          ,  
            Action           *>(&TiledTerrain::renderEnter));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TiledTerrain::TiledTerrain(void) :
    Inherited()
{
}

TiledTerrain::TiledTerrain(const TiledTerrain &source) :
    Inherited(source)
{
}

TiledTerrain::~TiledTerrain(void)
{
}

/*----------------------------- class specific ----------------------------*/

inline MaterialPtr cloneMaterial (const MaterialPtr& mat)
{
   ChunkMaterialPtr m = ChunkMaterialPtr::dcast(mat);
   ChunkMaterialPtr clone = ChunkMaterial::create();
   beginEditCP(clone);
   for (MFStateChunkPtr::const_iterator it=m->getChunks().begin();
	it != m->getChunks().end();
	++it) {
      clone->addChunk(*it);
   }
   endEditCP(clone);
   return clone;
}


void TiledTerrain::changed(BitVector whichField, UInt32 origin)
{
    // GeoMorphing is copied into each terrain node here
    // EyePointValid is set true here
    // EyePoint is calculated in ::renderEnter and copied into each terrain node
    // PerPixelLighting is copied into each terrain node here
    // UpdateTerrain is copied into each terrain node in ::renderEnter
    // Detail is copied into each terrain node here
    // BorderDetail is set to 1 here

    TiledTerrainPtr thisPtr(this);
    // changed HeightData
    // * update HeightError and HeightQuad
    if ((whichField & HeightTilesFieldMask) && getMFHeightTiles()->size() > 0) {
       if (getParents()[0] != NullFC) { // parent must be set!
	  while (getParents() [0]->getNChildren() > 0) {
	     getParents() [0]->subChild(0);
	  }
	  Real32 step   = (getHeightTiles(0)->getWidth()-1)*getVertexSpacing();
	  Real32 tstepx = 1.0f/getSizeX();
	  Real32 tstepy = 1.0f/getSizeY();
	  beginEditCP(getParents()[0]);
	  UInt32 i, j;
	  const UInt32 roi = getSizeROI()+getSizeROI()+1;
	  // mention: order of loops!
	  for (j=0; j<roi; ++j) {
	    for (i=0; i<roi; ++i) {
	       TerrainPtr terrain = Terrain::create();
	       beginEditCP(terrain, Terrain::VertexSpacingFieldMask | Terrain::HeightScaleFieldMask | Terrain::GeoMorphingFieldMask | Terrain::DetailFieldMask | Terrain::BorderDetailFieldMask | Terrain::EyePointValidFieldMask | Terrain::UpdateTerrainFieldMask | Terrain::HeightDataFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask
			   | Terrain::OriginTexXFieldMask | Terrain::OriginTexYFieldMask | Terrain::TexSpacingFieldMask | Terrain::TexYSpacingFieldMask);
	       terrain->setVertexSpacing(getVertexSpacing());
	       terrain->setHeightScale  (getHeightScale());
	       terrain->setGeoMorphing  (getGeoMorphing());
	       terrain->setDetail       (getDetail());
	       terrain->setBorderDetail (1);
	       terrain->setEyePointValid(true);
	       terrain->setUpdateTerrain(getUpdateTerrain());
	       terrain->setPerPixelLighting(getPerPixelLighting());
	       NodePtr node = Node::create();
	       beginEditCP(node);
	       node->setCore(terrain);
	       // activate the roi*roi tiles for current point (getCurrentX()=getSizeROI(),getCurrentY()=getSizeROI())
	       if (i < getSizeX() && j < getSizeY()) {
		 terrain->setHeightData(getHeightTiles(j*getSizeX()+i));
		 terrain->setOriginX(i*step);
		 terrain->setOriginY(j*step);
		 node->setActive(true);
	       } else {
		 node->setActive(false);
	       }
	       endEditCP  (terrain, Terrain::VertexSpacingFieldMask | Terrain::HeightScaleFieldMask | Terrain::GeoMorphingFieldMask | Terrain::DetailFieldMask | Terrain::BorderDetailFieldMask | Terrain::EyePointValidFieldMask | Terrain::UpdateTerrainFieldMask | Terrain::HeightDataFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask
			   | Terrain::OriginTexXFieldMask | Terrain::OriginTexYFieldMask | Terrain::TexSpacingFieldMask | Terrain::TexYSpacingFieldMask);
	       endEditCP  (node);
	       getParents()[0]->addChild(node);
	       addRefCP(node);
	     }
	  }
	  endEditCP(getParents()[0]);
       }
       beginEditCP(thisPtr, CurrentXFieldMask | CurrentYFieldMask);
       setCurrentX(getSizeROI());
       setCurrentY(getSizeROI());
       endEditCP(thisPtr, CurrentXFieldMask | CurrentYFieldMask);
    }
    if (((whichField & MaterialFieldMask) || (whichField & PerPixelLightingFieldMask))) {
       Real32 tstepx = 1.0f/getSizeX();
       Real32 tstepy = 1.0f/getSizeY();
       UInt32 i, j;
       const UInt32 roi = getSizeROI()+getSizeROI()+1;
       for (j=0; j<roi; ++j) {
	 for (i=0; i<roi; ++i) {
	    NodePtr    node = getParents()[0]->getChild(j*roi+i);
	    TerrainPtr terrain = TerrainPtr::dcast(node->getCore());
	    if (terrain == NullFC) {
	      continue;
	    }
	    beginEditCP(terrain,  
			Terrain::OriginTexXFieldMask | Terrain::OriginTexYFieldMask | Terrain::TexSpacingFieldMask | Terrain::TexYSpacingFieldMask 
			| Terrain::MaterialFieldMask | Terrain::PerPixelLightingFieldMask);
	    if (getMaterial() == NullFC) { // use material of MFHeightTextures
	       if (getHeightTextures().size() > j*getSizeX()+i
		   && i < getSizeX() && j < getSizeY()) {	      
	 	  terrain->setMaterial(getHeightTextures(j*getSizeX()+i));
	       }
	    } else { // use material of this MaterialGroup
	       MaterialPtr mat = cloneMaterial(getMaterial());
	       terrain->setMaterial(mat);
	       terrain->setOriginTexX(i*tstepx);
	       terrain->setOriginTexY(j*tstepy);
	       terrain->setTexSpacing (tstepx);
	       terrain->setTexYSpacing(tstepy);
	    }
	    terrain->setPerPixelLighting(getPerPixelLighting());
	    endEditCP(terrain, 
		      Terrain::OriginTexXFieldMask | Terrain::OriginTexYFieldMask | Terrain::TexSpacingFieldMask | Terrain::TexYSpacingFieldMask 
		      | Terrain::MaterialFieldMask | Terrain::PerPixelLightingFieldMask);
	 }
       }
    }
    if ((whichField & GeoMorphingFieldMask)) {
       const UInt32 roi  = getSizeROI()+getSizeROI()+1;
       const UInt32 roi2 = roi*roi;
       for (UInt32 i=0; i<roi2; ++i) {
	  NodePtr    node = getParents()[0]->getChild(i);
	  TerrainPtr terrain = TerrainPtr::dcast(node->getCore());
	  if (terrain == NullFC) {
	    continue;
	  }
	  beginEditCP(terrain, Terrain::GeoMorphingFieldMask);
	  terrain->setGeoMorphing(getGeoMorphing());
	  endEditCP  (terrain, Terrain::GeoMorphingFieldMask);
       }
    }
    if ((whichField & DetailFieldMask)) {
       const UInt32 roi  = getSizeROI()+getSizeROI()+1;
       const UInt32 roi2 = roi*roi;
       for (UInt32 i=0; i<roi2; ++i) {
	  NodePtr    node = getParents()[0]->getChild(i);
	  TerrainPtr terrain = TerrainPtr::dcast(node->getCore());
	  if (terrain == NullFC) {
	    continue;
	  }
	  beginEditCP(terrain, Terrain::DetailFieldMask);
	  terrain->setDetail(getDetail());
	  endEditCP  (terrain, Terrain::DetailFieldMask);
       }
    }
    Inherited::changed(whichField, origin);
}

inline void reorderChilds (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num;
   for (Int32 i=0; i<num2; ++i) {
      parent->addChild(order[i]);
      changedCP(order[i]);
   }
}
inline void subAllChilds (const NodePtr& parent, NodePtr order[], Int32 num)
{
   //Int32 num2 = num*num;
   while (parent->getNChildren() > 0) {
      parent->subChild(0);
   }
}
inline void caseChilds_n1n1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=0, k=0; i<num; ++i, ++k) {
      order[k] = parent->getChild(num2+i);
   }
   for (i=0; i<num-1; ++i) {
      order[k] = parent->getChild(i*num+num-1);
      for (j=0, ++k; j<num-1; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
      }
   }
   subAllChilds(parent, order, num);
}
inline void caseChilds_n10 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=0, k=0; i<num; ++i) {
      order[k] = parent->getChild(i*num+num-1);
      for (j=0, ++k; j<num-1; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
     }
   }
   subAllChilds(parent, order, num);
}
inline void caseChilds_n1p1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=1, k=0; i<num; ++i) {
      order[k] = parent->getChild(i*num+num-1);
      for (j=0, ++k; j<num-1; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
      }
   }
   for (i=0; i<num; ++i, ++k) {
      order[k] = parent->getChild(i);
   }
   subAllChilds(parent, order, num);
}

inline void caseChilds_0n1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=0, k=0; i<num; ++i, ++k) {
      order[k] = parent->getChild(num2+i);
   }
   for (i=0; i<num-1; ++i) {
      for (j=0; j<num; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
      }
   }
   subAllChilds(parent, order, num);
}
inline void caseChilds_0p1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=1, k=0; i<num; ++i) {
      for (j=0; j<num; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
      }
   }
   for (i=0; i<num; ++i, ++k) {
      order[k] = parent->getChild(i);
   }
   subAllChilds(parent, order, num);
}

inline void caseChilds_p1n1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=0, k=0; i<num; ++i, ++k) {
      order[k] = parent->getChild(num2+i);
   }
   for (i=0; i<num-1; ++i, ++k) {
      for (j=1; j<num; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
      }
      order[k] = parent->getChild(i*num);
   }
   subAllChilds(parent, order, num);
}
inline void caseChilds_p10 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=0, k=0; i<num; ++i, ++k) {
      for (j=1; j<num; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
      }
      order[k] = parent->getChild(i*num);
   }
   subAllChilds(parent, order, num);
}
inline void caseChilds_p1p1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   for (i=1, k=0; i<num; ++i, ++k) {
      for (j=1; j<num; ++j, ++k) {
	 order[k] = parent->getChild(i*num+j);
      }
      order[k] = parent->getChild(i*num);
   }
   for (i=0; i<num; ++i, ++k) {
      order[k] = parent->getChild(i);
   }
   subAllChilds(parent, order, num);
}

Action::ResultE TiledTerrain::renderEnter (Action* action)
{  
   NodePtr    node;
   TerrainPtr core;
   RenderAction* da = dynamic_cast<RenderAction*>(action);
   if (da != NULL 
       && getUpdate() 
       && getSizeX() > 0 && getSizeY() > 0) { // dynamic tesselation
      const FrustumVolume& frustum = da->getFrustum();
      Matrix camera  = da->getCameraToWorld();
      Matrix toworld = da->top_matrix();
      //action->getActNode()->getToWorld(toworld);
      toworld.invert();
      camera.multLeft(toworld);

      // choose tile
      Real32 step   = (getHeightTiles(0)->getWidth()-1)*getVertexSpacing();
      Real32 tstepx = 1.0f/getSizeX();
      Real32 tstepy = 1.0f/getSizeY();
      // tiling cs is [0, getSizeX()*getWidth()]*[0, getSizeY()*getWidth()]
      Pnt3f eyePoint(camera[3][0], camera[3][1], camera[3][2]);
      // set eye point for all terrain child nodes
      const Int32 roi  = getSizeROI()+getSizeROI()+1;
      const Int32 roi2 = roi*roi;
      for (UInt32 i=0; i<roi2; ++i) {
	 node = getParents()[0]->getChild(i);
	 core = TerrainPtr::dcast(node->getCore());
	 beginEditCP(core, Terrain::EyePointFieldMask | Terrain::UpdateTerrainFieldMask);
	 core->setEyePoint(eyePoint);
	 core->setUpdateTerrain(getUpdateTerrain());
	 endEditCP  (core, Terrain::EyePointFieldMask | Terrain::UpdateTerrainFieldMask);
      }

      // find tile (x, y) for current eye point
      Int32 x = Int32((eyePoint[0])/step);
      Int32 y = Int32((eyePoint[2])/step);
      x = osgMax(x, 0);
      x = osgMin(x, Int32(getSizeX()-1));
      y = osgMax(y, 0);
      y = osgMin(y, Int32(getSizeY()-1));

      // change tiling to tile (x, y)
      if (x != getCurrentX() || y != getCurrentY()) {
	 if (x < getCurrentX()-1) {
	    x = getCurrentX()-1;
	 } else if (x > getCurrentX()+1) {
	    x = getCurrentX()+1;
	 }
	 if (y < getCurrentY()-1) { 
	    y = getCurrentY()-1;
	 } else if (y > getCurrentY()+1) {
	    y = getCurrentY()+1;
	 }
	 SNOTICE << "current (" << getCurrentX() << "," << getCurrentY() << ")->(" << x << "," << y << ")" << std::endl;

	 Int32 i, j;
	 NodePtr order[49];
	 assert(roi*roi <= 49);
	 beginEditCP(getParents()[0], Node::ChildrenFieldMask);
	 switch (x - getCurrentX()) {
	 case -1:
	   switch (y - getCurrentY()) {
	   case -1: {
	     caseChilds_n1n1(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<=getSizeROI(); ++i) {
	        node = order[i+getSizeROI()];
		if (y-getSizeROI() >= 0 && x+i >= 0 && x+i < getSizeX()) {
		   node->setActive(true);
		   core = TerrainPtr::dcast(node->getCore());
		   beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		   core->setHeightData(getHeightTiles((y-getSizeROI())*getSizeX() + x+i));
		   if (getMaterial() == NullFC) {
		      core->setMaterial(getHeightTextures((y-getSizeROI())*getSizeX() + x+i));
		   } else {
		      core->setOriginTexX((x+i)*tstepx);
		      core->setOriginTexY((y-getSizeROI())*tstepy);
		   }
		   core->setOriginX((x+i)*step);
		   core->setOriginY((y-getSizeROI())*step);
		   endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		   node->setActive(false);
		}
	     }
	     for (i=-getSizeROI()+1; i<=getSizeROI(); ++i) {
	        node = order[(i+getSizeROI())*roi];
		if (x-getSizeROI() >= 0 && y+i >= 0 && y+i < getSizeY()) {
		   node->setActive(true);
		   core = TerrainPtr::dcast(node->getCore());
		   beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		   core->setHeightData(getHeightTiles((y+i)*getSizeX() + (x-getSizeROI())));
		   if (getMaterial() == NullFC) {
		      core->setMaterial(getHeightTextures((y+i)*getSizeX() + x-getSizeROI()));
		   } else {
		      core->setOriginTexX((x-getSizeROI())*tstepx);
		      core->setOriginTexY((y+i)*tstepy);
		   }
		   core->setOriginX((x-getSizeROI())*step);
		   core->setOriginY((y+i)*step);
		   endEditCP  (core, Terrain::HeightDataFieldMask  | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		   node->setActive(false);
		}
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   case 0: {
	     caseChilds_n10(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<=getSizeROI(); ++i) {
	        node = order[(i+getSizeROI())*roi];
		if (x-getSizeROI() >= 0 && y+i >= 0 && y+i < getSizeY()) {
		   node->setActive(true);
		   core = TerrainPtr::dcast(node->getCore());
		   beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		   core->setHeightData(getHeightTiles((y+i)*getSizeX() + x-getSizeROI()));
		   if (getMaterial() == NullFC) {
		     core->setMaterial(getHeightTextures((y+i)*getSizeX() + x-getSizeROI()));
		   } else {
		     core->setOriginTexX((x-getSizeROI())*tstepx);
		     core->setOriginTexY((y+i)*tstepy);
		   }
		   core->setOriginX((x-getSizeROI())*step);
		   core->setOriginY((y+i)*step);
		   endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		  node->setActive(false);
		}
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   case 1: {
	     caseChilds_n1p1(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<getSizeROI(); ++i) {
	       node = order[(i+getSizeROI())*roi];
	       if (x-getSizeROI() >= 0 && y+i >= 0 && y+i < getSizeY()) {
	 	  node->setActive(true);
		  core = TerrainPtr::dcast(node->getCore());
		  beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		  core->setHeightData(getHeightTiles((y+i)*getSizeX() + x-getSizeROI()));
		  if (getMaterial() == NullFC) {
		    core->setMaterial(getHeightTextures((y+i)*getSizeX() + x-getSizeROI()));
		  } else {
		    core->setOriginTexX((x-getSizeROI())*tstepx);
		    core->setOriginTexY((y+i)*tstepy);
		  }
		  core->setOriginX((x-getSizeROI())*step);
		  core->setOriginY((y+i)*step);
		  endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
	       } else {
		 node->setActive(false);
	       }
	     }
	     for (j=-getSizeROI(); j<=getSizeROI(); ++j) {
	       node = order[roi2-roi+j+getSizeROI()];
	       if (x+j >= 0 && x+j < getSizeX() && y+getSizeROI() < getSizeY()) {
		  node->setActive(true);
		  core = TerrainPtr::dcast(node->getCore());
		  beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		  core->setHeightData(getHeightTiles((y+getSizeROI())*getSizeX() + x+j));
		  if (getMaterial() == NullFC) {
		    core->setMaterial(getHeightTextures((y+getSizeROI())*getSizeX() + x+j));
		  } else {
		    core->setOriginTexX((x+j)*tstepx);
		    core->setOriginTexY((y+getSizeROI())*tstepy);
		  }
		  core->setOriginX((x+j)*step);
		  core->setOriginY((y+getSizeROI())*step);
		  endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
	       } else {
		 node->setActive(false);
	       }
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   }
	   break;
	 case 0:
	   switch (y - getCurrentY()) {
	   case -1: {
	     caseChilds_0n1(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<=getSizeROI(); ++i) {
	        node = order[i+getSizeROI()];
		if (x+i >= 0 && x+i < getSizeX() && y-getSizeROI() >= 0) {
		  node->setActive(true);
		  core = TerrainPtr::dcast(node->getCore());
		  beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		  core->setHeightData(getHeightTiles((y-getSizeROI())*getSizeX() + x+i));
		  if (getMaterial() == NullFC) {
		    core->setMaterial(getHeightTextures((y-getSizeROI())*getSizeX() + x+i));
		  } else {
		    core->setOriginTexX((x+i)*tstepx);
		    core->setOriginTexY((y-getSizeROI())*tstepy);
		  }
		  core->setOriginX((x+i)*step);
		  core->setOriginY((y-getSizeROI())*step);
		  endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		  node->setActive(false);
		}
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   case 1: {
	     caseChilds_0p1(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<=getSizeROI(); ++i) {
	        node = order[roi2-roi+(i+getSizeROI())];
		if (x+i >= 0 && x+i < getSizeX() && y+getSizeROI() < getSizeY()) {
		  node->setActive(true);
		  core = TerrainPtr::dcast(node->getCore());
		  beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		  core->setHeightData(getHeightTiles((y+getSizeROI())*getSizeX() + x+i));
		  if (getMaterial() == NullFC) {
		    core->setMaterial(getHeightTextures((y+getSizeROI())*getSizeX() + x+i));
		  } else {
		    core->setOriginTexX((x+i)*tstepx);
		    core->setOriginTexY((y+getSizeROI())*tstepy);
		  }
		  core->setOriginX((x+i)*step);
		  core->setOriginY((y+getSizeROI())*step);
		  endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		  node->setActive(false);
		}
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   }
	   break;
	 case +1:
	   switch (y - getCurrentY()) {
	   case -1: {
	     caseChilds_p1n1(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<=getSizeROI(); ++i) {
	        node = order[i+getSizeROI()];
		if (x+i >= 0 && x+i < getSizeX() && y-getSizeROI() >= 0) {
		  node->setActive(true);
		  core = TerrainPtr::dcast(node->getCore());
		  beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		  core->setHeightData(getHeightTiles((y-getSizeROI())*getSizeX() + x+i));
		  if (getMaterial() == NullFC) {
		    core->setMaterial(getHeightTextures((y-getSizeROI())*getSizeX() + x+i));
		  } else {
		    core->setOriginTexX((x+i)*tstepx);
		    core->setOriginTexY((y-getSizeROI())*tstepy);
		  }
		  core->setOriginX((x+i)*step);
		  core->setOriginY((y-getSizeROI())*step);
		  endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		  node->setActive(false);
		}
	     }
	     for (i=-getSizeROI()+1; i<=getSizeROI(); ++i) {
	        node = order[(i+getSizeROI())*roi+(roi-1)];
		if (x+getSizeROI() < getSizeX() && y+i >= 0 && y+i < getSizeY()) {
		   node->setActive(true);
		   core = TerrainPtr::dcast(node->getCore());
		   beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		   core->setHeightData(getHeightTiles((y+i)*getSizeX() + (x+getSizeROI())));
		   if (getMaterial() == NullFC) {
		     core->setMaterial(getHeightTextures((y+i)*getSizeX() + x+getSizeROI()));
		   } else {
		     core->setOriginTexX((x+getSizeROI())*tstepx);
		     core->setOriginTexY((y+i)*tstepy);
		   }
		   core->setOriginX((x+getSizeROI())*step);
		   core->setOriginY((y+i)*step);
		   endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		   node->setActive(false);
		}
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   case 0: {
	     caseChilds_p10(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<=getSizeROI(); ++i) {
	       node = order[(i+getSizeROI())*roi+roi-1];
	       if (x+getSizeROI() < getSizeX() && y+i >= 0 && y+i < getSizeY()) {
		 node->setActive(true);
		 core = TerrainPtr::dcast(node->getCore());
		 beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		 core->setHeightData(getHeightTiles((y+i)*getSizeX() + x+getSizeROI()));
		 if (getMaterial() == NullFC) {
		   core->setMaterial(getHeightTextures((y+i)*getSizeX() + x+getSizeROI()));
		 } else {
		   core->setOriginTexX((x+getSizeROI())*tstepx);
		   core->setOriginTexY((y+i)*tstepy);
		 }
		 core->setOriginX((x+getSizeROI())*step);
		 core->setOriginY((y+i)*step);
		 endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
	       } else {
		 node->setActive(false);
	       }
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   case 1: {
	     caseChilds_p1p1(getParents()[0], order, roi);
	     for (i=-getSizeROI(); i<getSizeROI(); ++i) {
	       node = order[(i+getSizeROI())*roi+roi-1];
	       if (x-getSizeROI() >= 0 && y+i >= 0 && y+i < getSizeY()) {
		 node->setActive(true);
		 core = TerrainPtr::dcast(node->getCore());
		 beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		 core->setHeightData(getHeightTiles((y+i)*getSizeX() + x-getSizeROI()));
		 if (getMaterial() == NullFC) {
		   core->setMaterial(getHeightTextures((y+i)*getSizeX() + x-getSizeROI()));
		 } else {
		   core->setOriginTexX((x-getSizeROI())*tstepx);
		   core->setOriginTexY((y+i)*tstepy);
		 }
		 core->setOriginX((x-getSizeROI())*step);
		 core->setOriginY((y+i)*step);
		 endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
	       } else {
		 node->setActive(false);
	       }
	     }
	     for (j=-getSizeROI(); j<=getSizeROI(); ++j) {
	        node = order[roi2-roi+(j+getSizeROI())];
		if (y+getSizeROI() < getSizeY() && x+j >= 0 && x+j < getSizeX()) {
		   node->setActive(true);
		   core = TerrainPtr::dcast(node->getCore());
		   beginEditCP(core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		   core->setHeightData(getHeightTiles((y+getSizeROI())*getSizeX() + x+j));
		   if (getMaterial() == NullFC) {
		     core->setMaterial(getHeightTextures((y+getSizeROI())*getSizeX() + x+j));
		   } else {
		     core->setOriginTexX((x+j)*tstepx);
		     core->setOriginTexY((y+getSizeROI())*tstepy);
		   }
		   core->setOriginX((x+j)*step);
		   core->setOriginY((y+getSizeROI())*step);
		   endEditCP  (core, Terrain::HeightDataFieldMask | Terrain::MaterialFieldMask | Terrain::OriginXFieldMask | Terrain::OriginYFieldMask);
		} else {
		  node->setActive(false);
		}
	     }
	     reorderChilds(getParents()[0], order, roi);
	     break;
	   }
	   }
	   break;
	 }
	 endEditCP(getParents()[0], Node::ChildrenFieldMask);

	 TiledTerrainPtr thisPtr(this);
	 beginEditCP(thisPtr, CurrentXFieldMask | CurrentYFieldMask);
	 setCurrentX(x); 
	 setCurrentY(y); 
	 endEditCP  (thisPtr, CurrentXFieldMask | CurrentYFieldMask);
#ifdef OSG_DEBUG
	 UInt32 dup;
	 for (UInt32 i=0; i<roi2; ++i) {
	   node = getParents()[0]->getChild(i);
	   core = TerrainPtr::dcast(node->getCore());
	   if (node->getActive()) {
	     std::cout << "tile " << i << "(" << core->getOriginX() << "," << core->getOriginY() << "):";
	     dup = 0;
	     for (UInt32 j=0; j<roi2; ++j) {
	       NodePtr    node2 = getParents()[0]->getChild(j);
	       TerrainPtr core2 = TerrainPtr::dcast(node2->getCore());
	       if (node2->getActive() && core->getOriginX() == core2->getOriginX() && core->getOriginY() == core2->getOriginY()) {
		 std::cout << " " << j; 
		 ++dup;
	       }
	     }
	     std::cout << std::endl;
	     if (dup > 1) {
	       SFATAL << "tile has " << dup-1 << " duplicates!" << std::endl;
	     }
	   }
	 }
#endif
      }
   }

   UInt32 numIndis = 0;
   UInt32 numFans = 0;
   for (UInt32 i=0; i<getParents()[0]->getNChildren(); ++i) {
     node = getParents()[0]->getChild(i);
     if (node != NullFC) {
     core = TerrainPtr::dcast(node->getCore());
     if (core != NullFC && core->getIndices() != NullFC) {
        numIndis += core->getIndices()->size();
	numFans  += core->getTypes()->size();
     }
     }
   }
   SNOTICE << numIndis/3 << " triangles in " << numFans << " fans" << std::endl; 
   return Action::Continue;
}

void TiledTerrain::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TiledTerrain NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGTiledTerrain.cpp,v 1.1 2005/04/24 19:45:49 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGTILEDTERRAINBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTILEDTERRAINBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTILEDTERRAINFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

