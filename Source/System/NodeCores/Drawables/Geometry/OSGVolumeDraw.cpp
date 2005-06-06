/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGLog.h>
#include <OSGBoxVolume.h>
#include <OSGSphereVolume.h>
#include <OSGFrustumVolume.h>
#include <OSGCylinderVolume.h>
#include <OSGSimpleGeometry.h>
#include <OSGRenderAction.h>

#include "OSGVolumeDraw.h"

OSG_USING_NAMESPACE


/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Draw the given DynamicVolume using direct OpenGL calls.
*/
OSG_SYSTEMLIB_DLLMAPPING
void OSG::drawVolume(const DynamicVolume &volume)
{
    const Volume *v = &volume.getInstance();
    const BoxVolume *bv;
    const SphereVolume *sv;
    const CylinderVolume *cv;
    const FrustumVolume *fv;

    if((bv = dynamic_cast<const BoxVolume*>(v)))
    {
        drawVolume(*bv);
    }
    else if((sv = dynamic_cast<const SphereVolume*>(v)))
    {
        drawVolume(*sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume*>(v)))
    {
        drawVolume(*cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume*>(v)))
    {
        drawVolume(*fv);
    }
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Draw the given BoxVolume using direct OpenGL calls.
*/
OSG_SYSTEMLIB_DLLMAPPING 
void OSG::drawVolume(const BoxVolume &volume)
{
    Pnt3f min,max;
    volume.getBounds(min, max);

    glBegin(GL_LINE_LOOP);
    glVertex3f(min[0], min[1], min[2]);   
    glVertex3f(max[0], min[1], min[2]);   
    glVertex3f(max[0], max[1], min[2]);   
    glVertex3f(min[0], max[1], min[2]);   
    glVertex3f(min[0], min[1], min[2]);   
    glVertex3f(min[0], min[1], max[2]);   
    glVertex3f(max[0], min[1], max[2]);   
    glVertex3f(max[0], max[1], max[2]);   
    glVertex3f(min[0], max[1], max[2]);   
    glVertex3f(min[0], min[1], max[2]);   
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(min[0], max[1], min[2]);   
    glVertex3f(min[0], max[1], max[2]);   
    glVertex3f(max[0], max[1], min[2]);   
    glVertex3f(max[0], max[1], max[2]);   
    glVertex3f(max[0], min[1], min[2]);   
    glVertex3f(max[0], min[1], max[2]);   
    glEnd();

    return;
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Draw the given SphereVolume using direct OpenGL calls.
    
    NOTE: Not implemented yet!
*/
OSG_SYSTEMLIB_DLLMAPPING 
void OSG::drawVolume(const SphereVolume &OSG_CHECK_ARG(volume))
{
    FWARNING(("drawVolume(SphereVolume): not implemented yet!\n"));
    return;
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Draw the given FrustumVolume using direct OpenGL calls by intersecting
    near/far with the pairwise intersection of left/right and top/bottom.
*/
OSG_SYSTEMLIB_DLLMAPPING 
void OSG::drawVolume(const FrustumVolume &volume)
{
    Line lines[4];
    
    // calc the intersection lines between left/right/bottom/top
    if(volume.getLeft().intersect(volume.getTop(), lines[0]) == false)
    {
        FWARNING(("drawVolume(Frustum): left & top parallel ?!?\n"));
        return;
    }
    
    if(volume.getLeft().intersect(volume.getBottom(), lines[1]) == false)
    {
        FWARNING(("drawVolume(Frustum): left & bottom parallel ?!?\n"));
        return;
    }
    
    if(volume.getRight().intersect(volume.getTop(), lines[2]) == false)
    {
        FWARNING(("drawVolume(Frustum): right & top parallel ?!?\n"));
        return;
    }
    
    if(volume.getRight().intersect(volume.getBottom(), lines[3]) == false)
    {
        FWARNING(("drawVolume(Frustum): right & bottom parallel ?!?\n"));
        return;
    }
    
    // calc the intersection points
    Pnt3f pnts[8];
    
    if(volume.getNear().intersectInfinite(lines[0], pnts[0]) == false)
    {
        FWARNING(("drawVolume(Frustum): near & left/top parallel ?!?\n"));
        return;
    }
    
    if(volume.getFar().intersectInfinite(lines[0], pnts[1]) == false)
    {
        FWARNING(("drawVolume(Frustum): far & left/top parallel ?!?\n"));
        return;
    }
    
    if(volume.getNear().intersectInfinite(lines[1], pnts[2]) == false)
    {
        FWARNING(("drawVolume(Frustum): near & left/bottom parallel ?!?\n"));
        return;
    }
    
    if(volume.getFar().intersectInfinite(lines[1], pnts[3]) == false)
    {
        FWARNING(("drawVolume(Frustum): far & left/bottom parallel ?!?\n"));
        return;
    }
    
    if(volume.getNear().intersectInfinite(lines[2], pnts[4]) == false)
    {
        FWARNING(("drawVolume(Frustum): near & right/top parallel ?!?\n"));
        return;
    }
    
    if(volume.getFar().intersectInfinite(lines[2], pnts[5]) == false)
    {
        FWARNING(("drawVolume(Frustum): far & right/top parallel ?!?\n"));
        return;
    }
    
    if(volume.getNear().intersectInfinite(lines[3], pnts[6]) == false)
    {
        FWARNING(("drawVolume(Frustum): near & right/bottom parallel ?!?\n"));
        return;
    }
    
    if(volume.getFar().intersectInfinite(lines[3], pnts[7]) == false)
    {
        FWARNING(("drawVolume(Frustum): far & right/bottom parallel ?!?\n"));
        return;
    }
    
    // got the points, draw them

    glBegin(GL_LINE_LOOP);
    glVertex3fv(pnts[0].getValues());
    glVertex3fv(pnts[1].getValues());
    glVertex3fv(pnts[3].getValues());
    glVertex3fv(pnts[2].getValues());
    glVertex3fv(pnts[6].getValues());
    glVertex3fv(pnts[7].getValues());
    glVertex3fv(pnts[5].getValues());
    glVertex3fv(pnts[4].getValues());
    glEnd();

    glBegin(GL_LINES);
    glVertex3fv(pnts[0].getValues());
    glVertex3fv(pnts[2].getValues());
    glVertex3fv(pnts[1].getValues());
    glVertex3fv(pnts[5].getValues());
    glVertex3fv(pnts[2].getValues());
    glVertex3fv(pnts[6].getValues());
    glVertex3fv(pnts[4].getValues());
    glVertex3fv(pnts[6].getValues());
    glEnd();

    return;
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Draw the given CylinderVolume using direct OpenGL calls.
    
    NOTE: Not implemented yet!
*/
OSG_SYSTEMLIB_DLLMAPPING 
void OSG::drawVolume(const CylinderVolume &OSG_CHECK_ARG(volume))
{
    FWARNING(("drawVolume(CylinderVolume): not implemented yet!\n"));
    return;
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Wrapper class for volume drawing. An instance of this class is dropped into
    the DrawTree and automaticaly destructs itself after it's drawn.
*/
class VolumeDrawWrapper
{
  public:
  
    VolumeDrawWrapper(const DynamicVolume &vol, Color3f col) : 
        _vol(vol), _col(col)
    {}
    
    ~VolumeDrawWrapper()
    {}
    
    static void drop(DrawActionBase *action, NodePtr node, Color3f col)
    {
        node->updateVolume();
        
        drop(action, node->getVolume(), col);
    }
    
    static void drop(DrawActionBase *action, const DynamicVolume &volume, Color3f col)
    {
        VolumeDrawWrapper * vdw = new VolumeDrawWrapper(volume, col);

        Material::DrawFunctor func;
        func = osgTypedMethodFunctor1ObjPtr(vdw, &VolumeDrawWrapper::draw);
    
        RenderAction *ra = dynamic_cast<RenderAction*>(action);
        
        ra->dropFunctor(func, getDefaultUnlitMaterial().getCPtr());
    }
    
  private:
  
    Action::ResultE draw(DrawActionBase *)
    {
        glColor3fv(_col.getValuesRGB());
        drawVolume(_vol);
        
        // self-destruct
        delete this;
        
        return Action::Continue;
    }
    
    DynamicVolume _vol;  
    Color3f _col; 
};

/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Draw the local Bounding Volume of the current Node given in the Action.
*/
OSG_SYSTEMLIB_DLLMAPPING 
void OSG::dropVolume(DrawActionBase *action, NodePtr node, Color3f col)
{
    VolumeDrawWrapper::drop(action, node, col);
    return;
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions
    Draw the volume.
*/
OSG_SYSTEMLIB_DLLMAPPING 
void OSG::dropVolume(DrawActionBase *action, const DynamicVolume &volume, Color3f col)
{
    VolumeDrawWrapper::drop(action, volume, col);
    return;
}
