

#include <OSGBaseFunctions.h>
#include <OSGVRMLObjectFactory.h>
#include <OSGVRMLLoader.h>
#include <OSGVRMLToOSGAction.h>
//#include <VSCVRMLBindings.h>
//#include <VSCVRMLNodeBinder.h>
#include <OSGVRMLNode.h>
#include <OSGVRMLNodeAttachment.h>
#include <OSGVRMLTextureCoordinate.h>
#include <OSGVRMLGroup.h>
#include <OSGVRMLColor.h>
#include <OSGVRMLCoordinate.h>
#include <OSGVRMLNormal.h>

#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainer.h>
//#include <OSGOSGWriter.h>

#include <ostream>

int main(int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    fprintf(stderr, "VRMLLoader Test started\n");

    OSG::VRMLNode::getClassType().dump();
    OSG::VRMLNodeAttachment::getClassType().dump();
    OSG::VRMLTextureCoordinate::getClassType().dump();
    OSG::VRMLGroup::getClassType().dump();
    OSG::VRMLColor::getClassType().dump();
    OSG::VRMLCoordinate::getClassType().dump();
    OSG::VRMLNormal::getClassType().dump();

    OSG::VRMLLoader *pFile = new OSG::VRMLLoader;

    pFile->scanFile(argv[1], 0);

    OSG::VRMLToOSGAction                   aVRMLToOSG;

    OSG::FieldContainerPtr                 pFC         = OSG::NullFC;
//    VRMLBindings::VSCNodeBinderPtr pNodeBinder = NULL;

    aVRMLToOSG.setNameNodeMap(pFile->getNameNodeMap());
    
    aVRMLToOSG.apply(pFile->getFileTree());

/*
    pNodeBinder = pFile->getFileTree()->getBinder();
    
    if(pNodeBinder != NULL)
    {
        pFC = pNodeBinder->getFCPtr();  
        
        if(pFC != OSG::NullFC)
        {
            ofstream outFileStream("test.osg");
            
            if(! outFileStream)
            {
                cerr << "Can not open output stream to file: " 
                     << "test.osg" << endl;
                return -1;
            }
            
            cerr << "STARTING PRINTOUT:" << endl;
            OSG::OSGWriter writer(outFileStream, 4);
            writer.write(pFC);
        }
        else
        {
            fprintf(stderr, "FCPtr NULL\n");
        }
    }
    else
    {
        fprintf(stderr, "Binder NULL\n");
    }
*/

    fprintf(stderr, "VRMLLoader Test ended \n");

//    VSC::vscExit();
    return 0;
}
