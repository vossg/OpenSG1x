#include <OSGConfig.h>

#include <iostream>

#include <OSGBaseFunctions.h>
#include <OSGLog.h>

using namespace OSG;

bool initFuncWrapperFunc(void)
{
    std::cerr << "initFuncWrapperFunc called" << std::endl;
    return true;
}

static InitFuncWrapper testInitFuncWrapper(initFuncWrapperFunc);


bool staticInitFuncWrapperFunc(void)
{
    std::cerr << "staticInitFuncWrapperFunc called" << std::endl;
    return true;
}

static StaticInitFuncWrapper testStaticInitFuncWrapper(staticInitFuncWrapperFunc);


bool initTestFunc(void)
{
    std::cerr << "initTestFunc called" << std::endl;
    return true;
}

struct InitTest
{
    InitTest() 
    { 
        addInitFunction(initTestFunc); 
    }
};

static InitTest initDummy;

int main (int argc, char **argv) 
{
    std::cerr << "Main started" << std::endl;
    
    osgInit(argc,argv);

    std::cerr << "osgInit called" << std::endl;
    
    osgExit();

    std::cerr << "osgExit called" << std::endl;

    return 0;
}



