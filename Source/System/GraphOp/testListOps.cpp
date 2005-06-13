#include <OSGConfig.h>

#include <OSGGraphOpFactory.h>

using namespace OSG;

/* */
int main(int argc, char *argv[])
{
    osgInit(argc, argv);
    
    GraphOpFactory &fac = GraphOpFactory::the();
    
    std::cout << "Registered GraphOps:" << std::endl;
    
    for(GraphOpFactory::iterator it = fac.begin(); it != fac.end();
        ++it)
    {
        std::cout << it->second->usage() << std::endl;
    }
   
    return 0;
}
