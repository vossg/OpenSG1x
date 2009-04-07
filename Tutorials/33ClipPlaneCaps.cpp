// OpenSG example: ClipPlaneCaps
//
// Demonstrates the use of the ClipPlaneChunk, StencilChunk for capping of 
// clipped geometry
//
// This examples allows creation of a box and a torus. Additionally, two clip
// planes can be set up. On clipping the geometry caps are used to repair the
// clipped geometry.
//
// User interface:
//  a) mouse => standard navigator
//  b) keyboard =>
//      '1': enable/disable clip plane 0
//      '2': enable/disable clip plane 1
//      '3': enable/disable box geometry
//      '4': enable/disable torus geometry
//      'n': move clip plane 0 opposite to the normal direction of the plane
//      'm': move clip plane 0 in the normal direction of the plane
//      ',': move clip plane 1 opposite to the normal direction of the plane
//      '.': move clip plane 1 in the normal direction of the plane
//      'q': move box in -x direction
//      'w': move box in +x direction
//      'a': move box in -y direction
//      's': move box in +y direction
//      'y': move box in -z direction
//      'x': move box in +z direction
//      'e': move torus in -x direction
//      'r': move torus in +x direction
//      'd': move torus in -y direction
//      'f': move torus in +y direction
//      'c': move torus in -z direction
//      'v': move torus in +z direction
//
// Example contributed by Johannes Brunen.

#include <vector>

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGMultiSwitch.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGStateSortingGroup.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGClipPlaneChunk.h>
#include <OpenSG/OSGStencilChunk.h>
#include <OpenSG/OSGInverseTransform.h>
#include <OpenSG/OSGDepthChunk.h>

OSG_USING_NAMESPACE

typedef std::vector<NodePtr> VecNodesT; // convenience type

//
// transport container for the actual clip plane data
//
struct ClipPlaneData
{
    Vec4f _equation;
    bool  _enabled;
};

typedef std::vector<ClipPlaneData> VecClipPlaneData;

//
// for each clip plane these data are necessary
//
struct ClipPlaneDetails
{
    ClipPlaneChunkPtr  _clipPlaneChunk;
    osg::GeometryPtr   _planeGeometryCore;
    osg::TransformPtr  _planeTrafoCore;
    Color3f            _planeColor;
};

typedef std::vector<ClipPlaneDetails> VecClipPlaneDetailsT;

//
// global state
//
VecClipPlaneData      vecClipPlaneData;      // transport clip plane info
VecClipPlaneDetailsT  vecClipPlaneDetails;   // opensg clip plane state
VecNodesT             vecGeometries;         // box and torus

SimpleSceneManager   *mgr;
NodePtr               scene;

//
// the number of clipping planes supported by the demo. Define a plane color
// for each.
//
const int iNumClipPlanes = 2;
Color3f planeCol[iNumClipPlanes] = { Color3f(0,1,0), Color3f(0,0,1) };

//
// Build the global clip plane state
//
void createClipPlaneDetails(void)
{
    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneDetails details;

        //
        // Create clip plane chunk
        //
        NodePtr clipPlaneBeacon = Node::create();
        addRefCP(clipPlaneBeacon);

        details._clipPlaneChunk = ClipPlaneChunk::create();
        addRefCP(details._clipPlaneChunk);
        {
            CPEditor guard(details._clipPlaneChunk);
            details._clipPlaneChunk->setEquation(Vec4f(1,0,0,0));
            details._clipPlaneChunk->setEnable(false);
            details._clipPlaneChunk->setBeacon(clipPlaneBeacon);
        }

        //
        // Create plane geometry
        //
        details._planeGeometryCore = makePlaneGeo(100.f, 100.f, 128, 128);
        addRefCP(details._planeGeometryCore);

        //
        // Create plane transformation core
        //
        Matrix mat;
        mat.setIdentity();

        details._planeTrafoCore = Transform::create();
        addRefCP(details._planeTrafoCore);
        {
            CPEditor guard(details._planeTrafoCore);
            details._planeTrafoCore->setMatrix(mat);
        }

        //
        // Define plane color
        //
        details._planeColor = planeCol[i];


        vecClipPlaneDetails.push_back(details);
    }
}

//
// Clean up code
//
void destroyClipPlaneDetails(void)
{
    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        subRefCP(vecClipPlaneDetails[i]._clipPlaneChunk->getBeacon());
        subRefCP(vecClipPlaneDetails[i]._clipPlaneChunk);
        subRefCP(vecClipPlaneDetails[i]._planeGeometryCore);
        subRefCP(vecClipPlaneDetails[i]._planeTrafoCore);
    }
    vecClipPlaneDetails.clear();
}

//
// In  case the clip plane data change this function is called
//
void updateClipPlanes(const VecClipPlaneData& vec)
{
    int sz  = vec.size();

    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneChunkPtr& clipPlaneChunk = vecClipPlaneDetails[i]._clipPlaneChunk;
        CPEditor guard(clipPlaneChunk);
        clipPlaneChunk->setEnable(false);

        if(i < sz)
        {
            const ClipPlaneData& data = vec[i];

            //
            // Update the clip plane chunk
            //
            clipPlaneChunk->setEquation(data._equation);
            clipPlaneChunk->setEnable(data._enabled);

            //
            // and the plane transform core
            //
            Matrix rotMat;
            Vec4f v1(0.f, 0.f, -1.f, 0.f);
            Quaternion q(v1, data._equation);
            rotMat.setTransform(q);

            Matrix mat;
            Vec3f v2(0.0f, 0.0f, data._equation[3]);
            mat.setTranslate(v2);

            mat.multLeft(rotMat);

            {
                CPEditor guard(vecClipPlaneDetails[i]._planeTrafoCore);
                vecClipPlaneDetails[i]._planeTrafoCore->setMatrix(mat);
            }
        }
    }
}

//
// build geometry scenegraph Tree
//
//
// We need 3 material groups for the clip plane capping trick:
//
//                        scene
//                          |
//     +--------------------+--------------------+
//     |                    |                    |
//  group1 (mat1)        group2 (mat2)        group3 (mat3)
//     |                    |                    |
// geometry (geo1)      geometry (geo2)      geometry (geo1)
//
//    geo1 : actual geometry to draw
//    geo2 : plane geometry coincident with the clip plane
//
//    mat1 : has a stencil chunk that clears the stencil buffer first, than 
//           does the inversion, and has a clip plane chunk that enables one
//           clip plane. Sortkey 0.
//    mat2 : has a stencil chunk and settings for drawing the clip plane 
//           geometry. All clip planes but the one coincident with the plane
//           are activated. Sortkey 1.
//    mat3 : the material used for the actual geometry. All clip planes are 
//           activated. Sortkey 3.
//
//    For each active clip plane copies of the left two branches need to be 
//    added.
//
NodePtr buildGeoTree(NodePtr scene, GeometryPtr geo1, const Matrix& matrix)
{
    // if using a sort key, for each geometry we must ensure that the sortkeys
    // are independent. However, using a StateSortingGroup parent node does
    // make the use of sortkeys not necessary.
    static int k = 0;

    //
    // Parent nodes for the left two branches
    //
    VecNodesT vecMaterialNodes1;
    VecNodesT vecMaterialNodes2;

    for (int i = 0; i < iNumClipPlanes; ++i) // foreach clip plane
    {
        //
        // Branch 1: Imprint the geometry clip plane intersection into the 
        //           stencil buffer.
        //
        NodePtr geomNode = Node::create();
        {
            CPEditor guard(geomNode);
            geomNode->setCore(geo1);
        }

        NodePtr materialNode1 = Node::create();
        {
            //
            // Create stencil material core
            //
            StencilChunkPtr stencilChunk1 = StencilChunk::create();
            {
                CPEditor guard(stencilChunk1);
                stencilChunk1->setClearBuffer(1);
                stencilChunk1->setStencilFunc(GL_NEVER);
                stencilChunk1->setStencilValue(1);
                stencilChunk1->setStencilMask(1);
                stencilChunk1->setStencilOpFail(GL_INVERT);
                stencilChunk1->setStencilOpZFail(GL_INVERT);
                stencilChunk1->setStencilOpZPass(GL_INVERT);
            }
            ChunkMaterialPtr mat1 = ChunkMaterial::create();
            {
                CPEditor guard(mat1);
                mat1->addChunk(stencilChunk1);
                mat1->addChunk(vecClipPlaneDetails[i]._clipPlaneChunk);
                //mat1->setSortKey(k*(2*iNumClipPlanes + 1) + 2*i + 0);
            }

            MaterialGroupPtr mgrp1 = MaterialGroup::create();
            {
                CPEditor guard(mgrp1);
                mgrp1->setMaterial(mat1);
            }

            CPEditor guard(materialNode1);
            materialNode1->setCore(mgrp1);
            materialNode1->addChild(geomNode);  // the primary geometry
        }
        vecMaterialNodes1.push_back(materialNode1);

        //
        // Branch 2: Draw plane at places were the stencil buffer is set
        //
        NodePtr materialNode2 = Node::create();
        {
            StencilChunkPtr stencilChunk2 = StencilChunk::create();
            {
                CPEditor guard(stencilChunk2);
                stencilChunk2->setStencilFunc(GL_EQUAL);
                stencilChunk2->setStencilValue(1);
                stencilChunk2->setStencilMask(1);
                stencilChunk2->setStencilOpFail(GL_KEEP);
                stencilChunk2->setStencilOpZFail(GL_ZERO);
                stencilChunk2->setStencilOpZPass(GL_ZERO);
            }

            SimpleMaterialPtr mat2 = SimpleMaterial::create();
            {
                CPEditor guard(mat2);
                mat2->setDiffuse(vecClipPlaneDetails[i]._planeColor);
                mat2->setSpecular(Color3f(1,1,1));
                mat2->setLit(true);
                //
                // Do clip the plane with all clip planes but the one coincident
                // with the plane.
                //
                for(int j = 0; j < iNumClipPlanes; ++j)
                {
                    if(i != j)
                        mat2->addChunk(vecClipPlaneDetails[j]._clipPlaneChunk);
                }
                mat2->addChunk(stencilChunk2);
                //mat2->setSortKey(k*(2*iNumClipPlanes + 1) + 2*i + 1);
            }

            NodePtr planeGeoNode = Node::create();
            {
                CPEditor guard(planeGeoNode);
                planeGeoNode->setCore(vecClipPlaneDetails[i]._planeGeometryCore);
            }

            NodePtr planeTrafoNode = Node::create();
            {
                CPEditor guard(planeTrafoNode);
                planeTrafoNode->setCore(vecClipPlaneDetails[i]._planeTrafoCore);
                planeTrafoNode->addChild(planeGeoNode);
            }
            //
            // Neutralize the summed up transformation at this point in the 
            // scenegraph since we are describing the plane in the same frame 
            // as the clip planes, i.e. world coordinates.
            //
            NodePtr planeRootNode = Node::create();
            {
                CPEditor guard(planeRootNode);
                planeRootNode->setCore(InverseTransform::create());
                planeRootNode->addChild(planeTrafoNode);
            }

            MaterialGroupPtr mgrp2 = MaterialGroup::create();
            {
                CPEditor guard(mgrp2);
                mgrp2->setMaterial(mat2);
            }

            CPEditor guard(materialNode2);
            materialNode2->setCore(mgrp2);
            materialNode2->addChild(planeRootNode); // plane geometry
        }
        vecMaterialNodes2.push_back(materialNode2);
    }

    //
    // Finally, set up a branch for drawing the primary geometry
    //
    NodePtr materialNode3 = Node::create();
    {
        SimpleMaterialPtr mat3 = SimpleMaterial::create();
        {
            CPEditor guard(mat3);

            mat3->setDiffuse(Color3f(1,0,0));
            mat3->setSpecular(Color3f(1,1,1));
            mat3->setLit(true);
            //
            // Clip the geometry with each clip plane
            //
            for (int i = 0; i < iNumClipPlanes; ++i) {
                mat3->addChunk(vecClipPlaneDetails[i]._clipPlaneChunk);
            }
            //mat3->setSortKey(k*(2*iNumClipPlanes + 1) + iNumClipPlanes * 2);
        }

        MaterialGroupPtr mgrp3 = MaterialGroup::create();
        {
            CPEditor guard(mgrp3);
            mgrp3->setMaterial(mat3);
        }

        NodePtr geometryNode = Node::create();
        {
            CPEditor guard(geometryNode);
            geometryNode->setCore(geo1);
        }

        CPEditor guard(materialNode3);
        materialNode3->setCore(mgrp3);
        materialNode3->addChild(geometryNode);
    }

    //
    // The multi switch core is not actually used in this
    // example. However it could be used to define multiple
    // render branches and selectively activate and deactivate
    // them in a given context.
    //
    MultiSwitchPtr selectCore = MultiSwitch::create();
    {
        CPEditor guard(selectCore);
        selectCore->setSwitchMode(MultiSwitch::ALL);
    }
    //
    // Add the branches to some parent node.
    //
    NodePtr selectNode = Node::create();
    {
        CPEditor guard(selectNode);
        selectNode->setCore(selectCore);

        for (int i = 0; i < iNumClipPlanes; ++i)
        {
            selectNode->addChild(vecMaterialNodes1[i]);
            selectNode->addChild(vecMaterialNodes2[i]);
        }
        selectNode->addChild(materialNode3);
    }
    //
    // In order to avoid sort keys which grow with the number of primary
    // geometry nodes, a node carrying a StateSortingGroup core is inserted
    // into the tree.
    //
    StateSortingGroupPtr stateSortGroupCore = StateSortingGroup::create();

    NodePtr stateSortGroupNode = Node::create();
    {
        CPEditor guard(stateSortGroupNode);
        stateSortGroupNode->setCore(stateSortGroupCore);
        stateSortGroupNode->addChild(selectNode);
    }
    //
    // Finally, the geometry should be transformable
    //
    TransformPtr transfCore = Transform::create();
    {
        CPEditor guard(transfCore);
        transfCore->setMatrix(matrix);
    }

    NodePtr trafoNode = Node::create();
    {
        CPEditor guard(trafoNode);
        trafoNode->setCore(transfCore);
        trafoNode->addChild(stateSortGroupNode);
        //trafoNode->addChild(selectNode); // if using sort keys use this 
                                           // instead of the former line.
    }

    k++;

    return trafoNode;
}

//
// redraw the window
//
void display(void)
{      
    // render
    
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w,h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int, int)
{
    static Real32 val0 = 0.f;
    static Real32 val1 = 0.f;

    static Real32 x1 = 0.f;
    static Real32 y1 = 0.f;
    static Real32 z1 = 0.f;

    static Real32 x2 = 0.f;
    static Real32 y2 = 0.f;
    static Real32 z2 = 0.f;

    switch(k)
    {
    case '1':   // enable/disable clip plane 0
        {
            vecClipPlaneData[0]._enabled = !vecClipPlaneData[0]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '2':   // enable/disable clip plane 1
        {
            vecClipPlaneData[1]._enabled = !vecClipPlaneData[1]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '3':   // enable/disable box geometry
        {
            CPEditor guard(scene);
            if (vecGeometries[0] == NullFC)
            {
                Matrix matrix;
                Vec3f v(10.f,  0.f, 15.f);
                matrix.setTranslate(v);
                vecGeometries[0] = buildGeoTree(scene, makeBoxGeo(15, 15, 15, 1, 1, 1), matrix);
                scene->addChild(vecGeometries[0]);
            }
            else
            {
                scene->subChild(vecGeometries[0]);
                vecGeometries[0] = NullFC;
            }

            mgr->showAll();
            mgr->redraw();
        }
        break;
    case '4':   // enable/disable torus geometry
        {
            CPEditor guard(scene);
            if (vecGeometries[1] == NullFC)
            {
                Matrix matrix;
                Vec3f v( 0.f, 10.f, 0.f);
                matrix.setTranslate(v);
                vecGeometries[1] = buildGeoTree(scene, makeTorusGeo(2, 6, 8, 16), matrix);

                scene->addChild(vecGeometries[1]);
            }
            else
            {
                scene->subChild(vecGeometries[1]);
                vecGeometries[1] = NullFC;
            }

            mgr->showAll();
            mgr->redraw();
        }
        break;
    case 'n':   // move clip plane 0 opposite to the normal direction of the plane
        {
            val0 -= 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'm':   // move clip plane 0 in the normal direction of the plane
        {
            val0 += 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case ',':   // move clip plane 1 opposite to the normal direction of the plane
        {
            val1 -= 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '.':   // move clip plane 1 in the normal direction of the plane
        {
            val1 += 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'q':   // move box in -x direction
        {
            x1 -= 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[0]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'w':   // move box in +x direction
        {
            x1 += 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[0]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'a':   // move box in -y direction
        {
            y1 -= 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[0]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 's':   // move box in +y direction
        {
            y1 += 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[0]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'z':
    case 'y':   // move box in -z direction
        {
            z1 -= 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[0]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'x':   // move box in +z direction
        {
            z1 += 0.2f;

            Matrix matrix;
            Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[0]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'e':   // move torus in -x direction
        {
            x2 -= 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[1]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'r':   // move torus in +x direction
        {
            x2 += 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[1]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'd':   // move torus in -y direction
        {
            y2 -= 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[1]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'f':   // move torus in +y direction
        {
            y2 += 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[1]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'c':   // move torus in -z direction
        {
            z2 -= 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[1]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 'v':   // move torus in +z direction
        {
            z2 += 0.2f;

            Matrix matrix;
            Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NullFC)
            {
                TransformPtr transformCore = TransformPtr::dcast(vecGeometries[1]->getCore());
                {
                    CPEditor guard(transformCore);
                    transformCore->setMatrix(matrix);
                }
            }
        }
        break;
    case 27:
        {
            osgExit();
            exit(0);
        }
    }
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
    
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin=PassiveWindow::create();
    pwin->init();
     
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin);

    //
    // Implementation details:
    //      For each clip plane we provide a ClipPlaneChunk, the plane geometry,
    //      the plane transform core and at least a plane color conveniently in 
    //      a vector of type VecClipPlaneDetailsT. The next function call 
    //      initializes this data structure.
    //
    createClipPlaneDetails();

    //
    // The scene
    //
    scene = Node::create();
    {
        CPEditor guard(scene);
        scene->setCore(Group::create());
    }

    //
    // A place for accessing the box and torus.
    //
    vecGeometries.push_back(NullFC);
    vecGeometries.push_back(NullFC);

    //
    // Build concrete clipping planes and update the clip plane details.
    //
    ClipPlaneData data1;
    ClipPlaneData data2;

    data1._equation = Vec4f(0,0,1,0);
    data1._enabled  = true;

    data2._equation = Vec4f(1,0,0,0);
    data2._enabled  = false;

    vecClipPlaneData.push_back(data1);
    vecClipPlaneData.push_back(data2);

    updateClipPlanes(vecClipPlaneData);

    keyboard('3',-1,-1);
    keyboard('4',-1,-1);

    // tell the manager what to manage
    mgr->setRoot(scene);
    
    // show the whole scene
    mgr->showAll();
    mgr->redraw();
   
    pwin->dumpExtensions();
    
    // GLUT main loop
    glutMainLoop();

    //
    // Clean up the global held data
    //
    destroyClipPlaneDetails();

    return 0;
}
