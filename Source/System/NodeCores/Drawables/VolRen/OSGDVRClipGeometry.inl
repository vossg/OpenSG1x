/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

#include <OSGConfig.h>
#include <OSGDVRVertex.h>
#include <OSGDVRTriangle.h>

OSG_BEGIN_NAMESPACE

inline
bool DVRClipGeometry::isLocalMinimum(DVRVertex &vertex)
{  
    for(MFInt32::const_iterator triIdx  = vertex.adjacentTriangles.begin(); 
                                triIdx != vertex.adjacentTriangles.end  (); 
                                triIdx++)
    {
        const Int32 *vertIndices = _mfTriangles[*triIdx].vertices;

        for(unsigned int j = 0; j < 3; j++)
        {
            if (&_mfVertices[vertIndices[j]] != &vertex)
            {
                if(_mfVertices[vertIndices[j]].isCloser(
                       vertex.refPlaneDistance))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

inline
void DVRClipGeometry::renderTriangle(const DVRTriangle &tri) const
{
    glBegin(GL_TRIANGLES);
    {
        for(unsigned int i = 0; i < 3; i++)
            glVertex3fv(
                _mfVertices[tri.vertices[i]].transformedPos.getValues());
    }
    glEnd();
}

inline
bool DVRClipGeometry::isBehindPlane(DVRTriangle &tri,
                                    Real32       dist2RefPlane)
{
    bool switched;
    bool v[3];

    for(unsigned int i = 0; i < 3; i++)
    {
        v[i] = 
            _mfVertices[tri.vertices[i]].isBehindPlane(dist2RefPlane,switched);
    }

    return (v[0] && v[1] && v[2]);
}

inline
Pnt3f DVRClipGeometry::interpolate(DVRTriangle *tri, 
                                   Int32        v1, 
                                   Int32        v2, 
                                   Real32       dist2RefPlane)
{
    float weight = 

        ((_mfVertices[tri->vertices[v2]].refPlaneDistance - 
          dist2RefPlane                                    ) /
         (_mfVertices[tri->vertices[v2]].refPlaneDistance - 
          _mfVertices[tri->vertices[v1]].refPlaneDistance  ));
    
  if(weight == 1.0)
  {
      // sorry, but without this we will have some really bad flickering...
      weight += 0.000001;
  }
  
  return 
      (_mfVertices[tri->vertices[v1]].transformedPos * weight) +  
      (_mfVertices[tri->vertices[v2]].transformedPos * (1.0f - 
                                                        weight)).subZero();
}


OSG_END_NAMESPACE

#define OSGDVRCLIPGEOMETRY_INLINE_CVSID "@(#)$Id: $"

