// OpenSG example: ClipPlaneCaps
//
// Demonstrates the use of the ClipPlaneChunk, and StencilChunk for capping
// of clipped geometry (e.g. to make a clipped object appear solid).
// See the comments in main() for details on the scene setup used to make this
// work.

#include <vector>

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGClipPlaneChunk.h>
#include <OpenSG/OSGStencilChunk.h>

OSG_USING_NAMESPACE

typedef std::vector<NodePtr> VecNodesT;


struct ClipPlaneData
{
    Vec4f _equation;
    bool  _enabled;
};
typedef std::vector<ClipPlaneData> VecClipPlaneData;


struct ClipPlaneDetails
{
    ClipPlaneChunkPtr  _clipPlaneChunk;
    NodePtr            _clipPlaneBeacon;
    NodePtr            _planeTrafoNode;
    MaterialGroupPtr   _materialCore;
};
typedef std::vector<ClipPlaneDetails> VecClipPlaneDetailsT;

// global state
VecClipPlaneDetailsT  vecClipPlaneDetails;
VecClipPlaneData      vecClipPlaneData;
SimpleSceneManager   *mgr;

// the number of clipping planes supported by the demo
const int iNumClipPlanes = 2;

void createClipPlaneDetails(void)
{
    for (int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneDetails details;

        //
        // Create clip plane chunk
        //
        details._clipPlaneChunk = ClipPlaneChunk::create();
        addRefCP(details._clipPlaneChunk);
        {
            CPEditor guard(details._clipPlaneChunk);
            details._clipPlaneChunk->setEquation(Vec4f(1,0,0,0));
            details._clipPlaneChunk->setEnable(false);

            details._clipPlaneBeacon = Node::create();
            addRefCP(details._clipPlaneBeacon);
            details._clipPlaneChunk->setBeacon(details._clipPlaneBeacon);
        }

        //
        // Create plane geometry
        //
        NodePtr planeGeoNode = makePlane(10.f, 10.f, 128, 128);

        Matrix mat;
        mat.setIdentity();

        TransformPtr transfCore = Transform::create();
        {
            CPEditAll(transfCore);
            transfCore->setMatrix(mat);
        }

        details._planeTrafoNode = Node::create();
        addRefCP(details._planeTrafoNode);
        {
            CPEditor guard(details._planeTrafoNode);
            details._planeTrafoNode->setCore(transfCore);
            details._planeTrafoNode->addChild(planeGeoNode);
        }

        //
        // Create stencil material core
        //
        StencilChunkPtr stencilChunk = StencilChunk::create();
        {
            CPEditAll(stencilChunk);
            stencilChunk->setClearBuffer(1);
            stencilChunk->setStencilFunc(GL_NEVER);
            stencilChunk->setStencilValue(1);
            stencilChunk->setStencilMask(1);
            stencilChunk->setStencilOpFail(GL_INVERT);
            stencilChunk->setStencilOpZFail(GL_INVERT);
            stencilChunk->setStencilOpZPass(GL_INVERT);
        }
        ChunkMaterialPtr mat1 = ChunkMaterial::create();
        {
            CPEditAll(mat1);
            mat1->addChunk(stencilChunk);
            mat1->addChunk(details._clipPlaneChunk);
            mat1->setSortKey(2*i + 0);
        }

        details._materialCore = MaterialGroup::create();
        addRefCP(details._materialCore);
        {
            CPEditor guard(details._materialCore);
            details._materialCore->setMaterial(mat1);
        }

        vecClipPlaneDetails.push_back(details);
    }
}

void destroyClipPlaneDetails(void)
{
    for (int i = 0; i < iNumClipPlanes; ++i)
    {
        subRefCP(vecClipPlaneDetails[i]._clipPlaneChunk);
        subRefCP(vecClipPlaneDetails[i]._clipPlaneBeacon);
        subRefCP(vecClipPlaneDetails[i]._planeTrafoNode);
        subRefCP(vecClipPlaneDetails[i]._materialCore);
    }
    vecClipPlaneDetails.clear();
}

void updateClipPlanes(const VecClipPlaneData& vec)
{
    int sz  = vec.size();

    for (int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneChunkPtr &clipPlaneChunk =
            vecClipPlaneDetails[i]._clipPlaneChunk;

        CPEditAll(clipPlaneChunk);
        clipPlaneChunk->setEnable(false);

        if(i < sz)
        {
            const ClipPlaneData& data = vec[i];

            clipPlaneChunk->setEquation(data._equation);
            clipPlaneChunk->setEnable(data._enabled);

            Matrix rotMat;
            Vec4f v1(0.f, 0.f, -1.f, 0.f);
            Quaternion q(v1, data._equation);
            rotMat.setTransform(q);
            
            Matrix mat;
            Vec3f v2(0.0f, 0.0f, data._equation[3]);
            mat.setTranslate(v2);
            
            mat.multLeft(rotMat);

            TransformPtr transformCore =
                TransformPtr::dcast(
                    vecClipPlaneDetails[i]._planeTrafoNode->getCore());
            {
                CPEditAll(transformCore);
                transformCore->setMatrix(mat);
            }
        }
    }
}


// redraw the window
void display(void)
{
    // render

    mgr->redraw();

    // all done, swap -- need to do this by hand as we are using a PassiveWindow
    glutSwapBuffers();
}

// react to size changes
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

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int, int)
{
    static Real32 val0 = 0.f;
    static Real32 val1 = 0.f;
    switch(k)
    {
        case 'a':
        {
            vecClipPlaneData[0]._enabled = !vecClipPlaneData[0]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
        case 's':
        {
            vecClipPlaneData[1]._enabled = !vecClipPlaneData[1]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
        case 'y':
        case 'z':
        {
            val0 -= 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
        case 'x':
        {
            val0 += 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
        case 'n':
        {
            val1 -= 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
        case 'm':
        {
            val1 += 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;

        case 27:
        {
            destroyClipPlaneDetails();
            osgExit();
            exit(0);
        }
        break;
    }
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);

    glutCreateWindow("OpenSG - ClipPlaneCaps");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin = PassiveWindow::create();
    pwin->init();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin);

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
    //    mat1 : has a stencil chunk that clears the stencil buffer first,
    //           than does the inversion, and has
    //           a clip plane chunk that enables one clip plane. Sortkey 0.
    //    mat2 : has a stencil chunk and settings for drawing the clip plane
    //           geometry. All clip planes but the
    //           one coincident with the plane are activated. Sortkey 1.
    //    mat3 : the material used for the actual geometry. All clip planes
    //           are activated. Sortkey 3.
    //
    //    For each active clip plane copies of the left two branches need to
    //    be added.
    //

    //
    // Implementation details:
    //      For each clipplane we provide a ClipPlaneChunk, a MaterialGroup
    //      mat1 and the plane geometry geo2
    //      conveniently in a vector of type VecClipPlaneDetailsT. The next
    //      function call initializes this
    //      data structure. Later on, we provide actual details for the
    //      vector elements.
    //
    createClipPlaneDetails();


    GeometryPtr geo1 = makeTorusGeo(0.5, 3, 8, 16);

    NodePtr geometryNode = Node::create();
    {
        CPEditAll(geometryNode);
        geometryNode->setCore(geo1);
    }

    VecNodesT vecMaterialNodes1;
    VecNodesT vecMaterialNodes2;
    for (int i = 0; i < iNumClipPlanes; ++i)
    {
        NodePtr geomNode = Node::create();
        {
            CPEditAll(geomNode);
            geomNode->setCore(geo1);
        }

        NodePtr materialNode1 = Node::create();
        {
            MaterialGroupPtr mgrp1 = vecClipPlaneDetails[i]._materialCore;

            CPEditAll(materialNode1);
            materialNode1->setCore(mgrp1);
            materialNode1->addChild(geomNode);
        }
        vecMaterialNodes1.push_back(materialNode1);


        NodePtr materialNode2 = Node::create();
        {
            StencilChunkPtr stencilChunk = StencilChunk::create();
            {
                CPEditAll(stencilChunk);
                stencilChunk->setClearBuffer(2);
                stencilChunk->setStencilFunc(GL_EQUAL);
                stencilChunk->setStencilValue(1);
                stencilChunk->setStencilMask(1);
                stencilChunk->setStencilOpFail(GL_KEEP);
                stencilChunk->setStencilOpZFail(GL_ZERO);
                stencilChunk->setStencilOpZPass(GL_ZERO);
            }

            SimpleMaterialPtr mat2 = SimpleMaterial::create();
            {
                CPEditAll(mat2);
                mat2->setDiffuse(Color3f(0,1,0));
                mat2->setSpecular(Color3f(1,1,1));
                mat2->setLit(true);

                for (int j = 0; j < iNumClipPlanes; ++j) {
                    if (i != j)
                        mat2->addChunk(vecClipPlaneDetails[j]._clipPlaneChunk);
                }
                mat2->addChunk(stencilChunk);
                mat2->setSortKey(2*i + 1);
            }

            MaterialGroupPtr mgrp2 = MaterialGroup::create();
            {
                CPEditAll(mgrp2);
                mgrp2->setMaterial(mat2);
            }

            CPEditAll(materialNode2);
            materialNode2->setCore(mgrp2);
            materialNode2->addChild(vecClipPlaneDetails[i]._planeTrafoNode);
        }
        vecMaterialNodes2.push_back(materialNode2);
    }

    NodePtr materialNode3 = Node::create();
    {
        SimpleMaterialPtr mat3 = SimpleMaterial::create();
        {
            CPEditAll(mat3);

            mat3->setDiffuse(Color3f(1,0,0));
            mat3->setSpecular(Color3f(1,1,1));
            mat3->setLit(true);

            for (int i = 0; i < iNumClipPlanes; ++i)
            {
                mat3->addChunk(vecClipPlaneDetails[i]._clipPlaneChunk);
            }
            mat3->setSortKey(2*(iNumClipPlanes-1) + 2);
        }

        MaterialGroupPtr mgrp3 = MaterialGroup::create();
        {
            CPEditAll(mgrp3);
            mgrp3->setMaterial(mat3);
        }

        CPEditAll(materialNode3);
        materialNode3->setCore(mgrp3);
        materialNode3->addChild(geometryNode);
    }

        // create the scene
    NodePtr scene = Node::create();
    {
        CPEditAll(scene);
        scene->setCore(Group::create());

        for (int i = 0; i < iNumClipPlanes; ++i)
        {
            scene->addChild(vecMaterialNodes1[i]);
            scene->addChild(vecMaterialNodes2[i]);
        }

        scene->addChild(materialNode3);
    }

    //
    // Build concrete clipping planes
    //
    ClipPlaneData data1;
    ClipPlaneData data2;

    data1._equation = Vec4f(0,0,1,0);
    data1._enabled  = true;

    data2._equation = Vec4f(1,0,0,0);
    data2._enabled  = true;

    vecClipPlaneData.push_back(data1);
    vecClipPlaneData.push_back(data2);

    updateClipPlanes(vecClipPlaneData);

    // tell the manager what to manage
    mgr->setRoot(scene);

    // show the whole scene
    mgr->showAll();
    mgr->redraw();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
