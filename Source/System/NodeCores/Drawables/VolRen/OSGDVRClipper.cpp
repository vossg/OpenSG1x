
#include <OSGDVRClipObjects.h>
#include <OSGDVRTriangle.h>
#include <OSGDVRClipper.h>
#include <OSGDVRVolume.h>
#include <OSGDVRRenderSlice.h>

#if !defined(darwin)
#include <malloc.h>
#endif

#include <stdlib.h>

OSG_USING_NAMESPACE

static void OSG_APIENTRY errorCallback        (GLenum   errorCode);
static void OSG_APIENTRY beginCallback        (GLenum   which, 
                                               void    *data);
static void OSG_APIENTRY endCallback          (void    *data);
static void OSG_APIENTRY vertexCallback       (GLvoid  *vertexData, 
                                               void    *data);
static void OSG_APIENTRY vertexCombineCallback(GLdouble *, 
                                               GLdouble **, 
                                               GLfloat  *, 
                                               GLdouble **, 
                                               void     *data);

DVRClipper::DVRClipper(void)
{
    myTess = NULL;
    // allocate temp. storage for 6 vertex positions and texture coordinates
    sliceVertexData = (GLdouble*)malloc(6*6*sizeof(GLdouble));

    numAddPerVertexAttr  = 0;
    hasTesselatorSupport = false;
}

DVRClipper::~DVRClipper(void)
{
    if(myTess)
        gluDeleteTess(myTess);

    free(sliceVertexData);
}

void DVRClipper::setReferencePlane(const Plane &rP)
{
    FDEBUG(("pre DVRVolume::setRefPlane - %f %f %f : %f\n",
            rP.getNormal()[0], 
            rP.getNormal()[1], 
            rP.getNormal()[2], 
            rP.getDistanceFromOrigin()));

    refPlane.set(rP.getNormal(), rP.getDistanceFromOrigin());
    
    FDEBUG(("post DVRVolume::setRefPlane - %f %f %f : %f\n",
            refPlane.getNormal()[0], 
            refPlane.getNormal()[1], 
            refPlane.getNormal()[2], 
            refPlane.getDistanceFromOrigin()));
}

const Plane &DVRClipper::getReferencePlane() const
{
    return refPlane;
}


bool DVRClipper::setNumAddPerVertexAttr(
    DVRVolume *volume, 
    UInt32     additionalPerVertexAttributes)
{
    numAddPerVertexAttr = additionalPerVertexAttributes;

    sliceVertexData = (GLdouble*) realloc(
        sliceVertexData,
        6 * (6 + additionalPerVertexAttributes) * sizeof(GLdouble));
  
    if(!sliceVertexData)
        return false;

    // get clip objects
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);
  
    if(clipObjects == NullFC)
        return true;

    for(UInt32 i = 0; i < clipObjects->count(); i++)
    {    
        DVRClipGeometryPtr clipObject = clipObjects->get(i);

        if(!clipObject->setNumAddPerVertexAttr(additionalPerVertexAttributes))
            return false;      
    }  
    return true;
}


void DVRClipper::initialize(DVRVolume *volume)
{
    if(volume == NULL)
        return;
 
    // get clip objects
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);
  
    if(clipObjects == NullFC)
        return;
  
    if(!hasTesselatorSupport)
    {
        // check for glu tesselator support
        hasTesselatorSupport = (atof((char*)gluGetString(GLU_VERSION)) >= 1.2);
        
        if(!hasTesselatorSupport)
            return;
    }

    if(myTess == NULL)
    {
        myTess = gluNewTess();

        // registering callback functions for glu tesselator...
        gluTessCallback(myTess, 
                        GLU_TESS_COMBINE_DATA, 
                        reinterpret_cast<OSGGLUfuncptr>(vertexCombineCallback));

        gluTessCallback(myTess, 
                        GLU_TESS_VERTEX_DATA, 
                        reinterpret_cast<OSGGLUfuncptr>(vertexCallback));

        gluTessCallback(myTess, 
                        GLU_TESS_BEGIN_DATA,
                        reinterpret_cast<OSGGLUfuncptr>(beginCallback));

        gluTessCallback(myTess, 
                        GLU_TESS_END_DATA, 
                        reinterpret_cast<OSGGLUfuncptr>(endCallback));

        gluTessCallback(myTess, 
                        GLU_TESS_ERROR, 
                        reinterpret_cast<OSGGLUfuncptr>(errorCallback));
    
    }
  
}

void DVRClipper::reset(DVRVolume *volume)
{
    if(volume == NULL || !hasTesselatorSupport)
        return;
 
    // get clip objects
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);
  
    if(clipObjects == NullFC)
        return;
  
    // set tesselator properties according to clip mode
    if(clipObjects->getClipMode() == DVRClipObjects::Intersection)
    {
        gluTessProperty(myTess, 
                        GLU_TESS_WINDING_RULE, 
                        GLU_TESS_WINDING_ABS_GEQ_TWO);
    }
    else
    {
        gluTessProperty(myTess, 
                        GLU_TESS_WINDING_RULE, 
                        GLU_TESS_WINDING_POSITIVE);
    }
  
    // reset local data
    for(UInt32 i = 0; i < clipObjects->count(); i++)
    {    
        // reset i-th clip object
        DVRClipGeometryPtr clipObject = clipObjects->get(i);

        clipObject->resetLocalData     ();  
        clipObject->computeSeedVertices();
    }
}

void DVRClipper::clipSlice(      DVRVolume      *volume,
                                 DVRSlice       &unclippedSlice, 
                           const Vec3f          &slicingNormal, 
                                 Real32          dist2RefPlane,
                                 DVRRenderSlice &clippedSlice)
{
    const Vec3f &texScale     = unclippedSlice.getTextureScale    ();
    const Vec3f &texTranslate = unclippedSlice.getTextureTranslate();

    // get clip objects
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);

    // nothing to clip with?
    if(clipObjects == NullFC)
    {
        DVRRenderSlicePrimitive *newPrimitive =  new DVRRenderSlicePrimitive();

        newPrimitive->type = GL_TRIANGLE_FAN;

        for(UInt32 i = 0; i < unclippedSlice.getVertexCount(); i++)
        {
            UInt32 idx = (6+numAddPerVertexAttr)*i;
            sliceVertexData[idx    ] = 
                unclippedSlice.getVertex(i).getValues()[0];

            sliceVertexData[idx + 1] = 
                unclippedSlice.getVertex(i).getValues()[1];

            sliceVertexData[idx + 2] =
                unclippedSlice.getVertex(i).getValues()[2];


            // set (standard) texture coordinates
            sliceVertexData[idx + 3] = 
                texScale[0] * 
                unclippedSlice.getVertex(i).getValues()[0] + 
                texTranslate[0];

            sliceVertexData[idx + 4] = 
                texScale[1] * 
                unclippedSlice.getVertex(i).getValues()[1] + 
                texTranslate[1];

            sliceVertexData[idx + 5] = 
                texScale[2] * 
                unclippedSlice.getVertex(i).getValues()[2] + 
                texTranslate[2];      

            newPrimitive->vertices.push_back(&sliceVertexData[idx]);
        }

        clippedSlice.push_back(newPrimitive);
        
        return;
    }

    if(!hasTesselatorSupport)
        return;

    // render colored contours only (usefull for debugging)
    if(clipObjects->getDoContours())
    {
        glDisable(GL_TEXTURE   );
        glDisable(GL_LIGHTING  );

        glBegin  (GL_LINE_STRIP);  
        {
            int col = 0;
            
            for(UInt32 i = 0; i < unclippedSlice.getVertexCount(); i++)
            {      
                glColor3f(col % 3 == 0 ? 1.0f : 0.0f, 
                          col % 3 == 1 ? 1.0f : 0.0f, 
                          col % 3 == 2 ? 1.0f : 0.0f);
                
                col++;
                
                glVertex3fv(unclippedSlice.getVertex(i).getValues());
            }
        }
        glEnd();
   
        bool clipAwayOutside = 
            clipObjects->getClipMode() == DVRClipObjects::Difference;
    
        for(UInt32 i = 0; i < clipObjects->count(); i++)
        {
            // get i-th clip object
            DVRClipGeometryPtr clipObject = clipObjects->get(i);
      
            // compute the contours of the triangles intersecting the 
            // current slice

            const DVRTriangleList &contours = 
                clipObject->getContours(dist2RefPlane,
                                        !clipAwayOutside,
                                        slicingNormal);     
      
            if(!contours.empty())
            {
                DVRTriangle *current;
                DVRTriangle *contourStart;
	
                // iterate over all contours
                DVRTriangleList::const_iterator contoursIt;

                for(contoursIt  = contours.begin(); 
                    contoursIt != contours.end  (); 
                    contoursIt++)
                { 
                    contourStart = current = *contoursIt;	 
	  
                    glBegin(GL_LINE_STRIP);	  
                    {
                        int col = 0;
                        
                        // iterate over all triangles in the current contour
                        do
                        {	    	   
                            glColor3f(col % 3 == 0 ? 1.0f : 0.0f, 
                                      col % 3 == 1 ? 1.0f : 0.0f, 
                                      col % 3 == 2 ? 1.0f : 0.0f);

                            col++;

                            glVertex3dv(current->cutPoint);

                            current = current->contourNeighbour;

                        } while(current!= contourStart);
                    }
                    glEnd();
                }
            }
        }
        
        glEnable(GL_TEXTURE );
        glEnable(GL_LIGHTING);
        
    }
    else
    {
        // tesselate and render the clipped slices

        // set the slice normal for tesselation
        gluTessNormal(myTess, 
                      slicingNormal[0], 
                      slicingNormal[1], 
                      slicingNormal[2]);    
        
        clippedSlice.clear();
        
        gluTessBeginPolygon(myTess, &clippedSlice);
    
        // set the slice's base contour
        gluTessBeginContour(myTess);
        
        for(UInt32 i = 0; i < unclippedSlice.getVertexCount(); i++)
        {       
            UInt32 idx = (6 + numAddPerVertexAttr) * i;

            sliceVertexData[idx    ] = 
                unclippedSlice.getVertex(i).getValues()[0];

            sliceVertexData[idx + 1] = 
                unclippedSlice.getVertex(i).getValues()[1];

            sliceVertexData[idx + 2] = 
                unclippedSlice.getVertex(i).getValues()[2];

            // set (standard) texture coordinates
            sliceVertexData[idx + 3] = 
                texScale[0] *
                unclippedSlice.getVertex(i).getValues()[0] + 
                texTranslate[0];

            sliceVertexData[idx + 4] = 
                texScale[1] * 
                unclippedSlice.getVertex(i).getValues()[1] + 
                texTranslate[1];

            sliceVertexData[idx + 5] = 
                texScale[2] * 
                unclippedSlice.getVertex(i).getValues()[2] +
                texTranslate[2];

            gluTessVertex(myTess, 
                          &sliceVertexData[idx], 
                          &sliceVertexData[idx]);
        }
        
        gluTessEndContour(myTess);
        
        // set contours of clip objects
        if(clipObjects->getClipMode() != DVRClipObjects::Off)
        {
            // get clip mode
            bool clipAwayOutside = 
                clipObjects->getClipMode() == DVRClipObjects::Difference;
      
            // add the contours of the intersections of the clip geometries 
            // with the slice
            for(UInt32 i = 0; i < clipObjects->count(); i++)
            {
                // get i-th clip object
                DVRClipGeometryPtr clipObject = clipObjects->get(i);
	
                // compute the contours of the triangles intersecting 
                // the current slice

                const DVRTriangleList &contours = 
                    clipObject->getContours( dist2RefPlane,
                                            !clipAwayOutside,
                                             slicingNormal);       
	
                if(!contours.empty())
                {
                    DVRTriangle *current;
                    DVRTriangle *contourStart;
	  
                    // iterate over all contours
                    DVRTriangleList::const_iterator contoursIt;

                    for(contoursIt  = contours.begin(); 
                        contoursIt != contours.end  (); 
                        contoursIt++)
                    { 
                        contourStart = current = *contoursIt;
	    	    
                        // start new contour
                        gluTessBeginContour(myTess);
	    
                        // iterate over all triangles in the current contour
                        do
                        {	    
                            // set (standard) texture coordinates
                            current->cutPoint[3] = 
                                texScale[0] * 
                                current->cutPoint[0] + 
                                texTranslate[0];

                            current->cutPoint[4] = 
                                texScale[1] * 
                                current->cutPoint[1] + 
                                texTranslate[1];

                            current->cutPoint[5] = 
                                texScale[2] * 
                                current->cutPoint[2] + 
                                texTranslate[2];

                            if(!current->cutPoint)
                                std::cerr << "WTF: cutPoint is NULL"
                                          << std::endl;

                            gluTessVertex(myTess, 
                                          current->cutPoint, 
                                          current->cutPoint);

                            current = current->contourNeighbour;

                        } while(current != contourStart);
	    
                        gluTessEndContour(myTess);
                    }
                }
            }
        }
        
        gluTessEndPolygon(myTess);
    }
}

void OSG_APIENTRY errorCallback(GLenum errorCode)
{
    SFATAL << "Error " 
           << gluErrorString(errorCode) 
           << " occured during tesselation!" 
           << std::endl;
}

void OSG_APIENTRY beginCallback(GLenum which, void *data)
{
    DVRRenderSlice *sliceData = (DVRRenderSlice *) data; 
  
    if(sliceData->directRender)
    {
        glBegin(which);
    }
    else
    {
        DVRRenderSlicePrimitive *newPrimitive = new DVRRenderSlicePrimitive();

        newPrimitive->vertices.reserve(3); 

        newPrimitive->type = which;

        sliceData->push_back(newPrimitive);
    }
}

void OSG_APIENTRY endCallback(void *data)
{
    DVRRenderSlice *sliceData = (DVRRenderSlice *) data; 

    if(sliceData->directRender)
    {
        glEnd();
    }
}

void OSG_APIENTRY vertexCallback(GLvoid *vertexData, void *data)
{
    GLdouble       *v         = (GLdouble       *) vertexData;

    DVRRenderSlice *sliceData = (DVRRenderSlice *) data; 

    if(sliceData->directRender)
    {
        switch(sliceData->orientation)
        {
            case DVRRenderSlice::UNDEFINED: // 3D texture
                glTexCoord3dv(&v[3]);
                break;

            case DVRRenderSlice::XY:
                glTexCoord2d(v[3], v[4]);
                break;

            case DVRRenderSlice::XZ:
                glTexCoord2d(v[3], v[5]);
            break;

            case DVRRenderSlice::YZ:
                glTexCoord2d(v[4], v[5]);
                break;

            default:
                break;
        }
        glVertex3dv(v);
    }
    else
    {
        sliceData->back()->vertices.push_back(v);
    }
}

void OSG_APIENTRY vertexCombineCallback(GLdouble  *coords, 
                                        GLdouble  *vertexData[4], 
                                        GLfloat    weight    [4], 
                                        GLdouble **dataOut, 
                                        void      *data         )
{
    DVRRenderSlice *sliceData = (DVRRenderSlice *) data;

    // allocate additional memory if neccessary
    if(sliceData->maxVertexCombineData <= sliceData->numVertexCombineData)
    {
        if(sliceData->maxVertexCombineData == 0)
            sliceData->maxVertexCombineData = 2;
        else
            sliceData->maxVertexCombineData *= 2;

        sliceData->vertexCombineData = 
            (GLdouble *) realloc(sliceData->vertexCombineData,
                                 (6                              + 
                                  sliceData->numPerVertexData)   * 
                                 sliceData->maxVertexCombineData * 
                                 sizeof(GLdouble));

        FDEBUG(("realloc vd %i\n",sliceData->numVertexCombineData));
    }
    
    GLdouble *vertex = 
        &(sliceData->vertexCombineData[
              (6 + sliceData->numPerVertexData) *
              sliceData->numVertexCombineData   ]);

    sliceData->numVertexCombineData++;
  
    vertex[0] = coords[0];
    vertex[1] = coords[1];
    vertex[2] = coords[2];

    // linearly interpolate per vertex data (texcoords, color, etc.)
    // there is at least one 3D texture coordinate given, that is 
    // numPerVertexData == 0 

    for(UInt32 i = 0; i < 3+sliceData->numPerVertexData; i++)
    {
        vertex[i+3] = 0.0;
    }

    for(UInt32 j = 0; j < 4; j++)
    {
        // this should never ever happen according to the GLU specification...
        if(vertexData[j] == NULL)
            continue;

        for(UInt32 i = 0; i < 3+sliceData->numPerVertexData; i++)
        {
            vertex[i + 3] += weight[j] * vertexData[j][i + 3];
        }
    }

    *dataOut = vertex;
}
