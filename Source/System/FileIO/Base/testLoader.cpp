
#include "OSGConfig.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "OSGBaseFunctions.h"
#include "OSGNode.h"
#include "OSGSceneFileHandler.h"
#include "OSGRAWSceneFileType.h"

OSG_USING_NAMESPACE

int main (int argc, char **argv)
{
    NodePtr node;
    const char *fileName = (argc > 1) ? argv[1] : "test.raw";

    osgInit(argc, argv);

    std::list<const Char8 *> l;
    
    SceneFileHandler::the().getSuffixList(l,
                    SceneFileType::OSG_READ_SUPPORTED);
                    
    std::cout << "Formats supported for reading: ";
    std::copy(l.begin(), l.end(), std::ostream_iterator<std::string>(std::cout, ","));
    std::cout << std::endl;
     
    SceneFileHandler::the().getSuffixList(l,
                    SceneFileType::OSG_WRITE_SUPPORTED);
                    
    std::cout << "Formats supported for writing: ";
    std::copy(l.begin(), l.end(), std::ostream_iterator<std::string>(std::cout, ","));
    std::cout << std::endl;

    node = SceneFileHandler::the().read(fileName);

    node->updateVolume();

    Vec3f center;
    node->getVolume().getCenter(center);

    std::cerr << "Volume: center " << center << ", volume "
         << node->getVolume().getScalarVolume() << std::endl;


    return 0;
}
