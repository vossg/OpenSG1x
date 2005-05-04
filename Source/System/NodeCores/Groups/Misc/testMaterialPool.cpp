// OpenSG example: testMaterialPool
//
// Demonstrates the use of the MaterialPool
// With this node you can handle very easy material libraries.

// Headers
#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGSFSysTypes.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>
#include <OSGMaterialPool.h>
#include <OSGNode.h>
#include <OSGSimpleMaterial.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    NodePtr mpNode = Node::create();
    MaterialPoolPtr mp = MaterialPool::create();
    beginEditCP(mpNode);
        mpNode->setCore(mp);
    endEditCP(mpNode);

    // create some materials
    SimpleMaterialPtr mat1 = SimpleMaterial::create();
    beginEditCP(mat1);
        mat1->setAmbient(Color3f(0.2, 0.2, 0.2));
        mat1->setDiffuse(Color3f(1,0,0));
    endEditCP(mat1);

    SimpleMaterialPtr mat2 = SimpleMaterial::create();
    beginEditCP(mat2);
        mat2->setAmbient(Color3f(0.2, 0.2, 0.2));
        mat2->setDiffuse(Color3f(0,1,0));
    endEditCP(mat2);
    
    // this adds a material to the material pool. You can also add
    // all materials from a subtree via mp->add(node)
    beginEditCP(mp);
        mp->add(mat1);
        mp->add(mat2);
    endEditCP(mp);

    // now write the material pool out.
    SceneFileHandler::the().write(mpNode, "materials.osb");

    osgExit();

    return 0;
}
