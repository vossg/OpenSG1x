#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGBaseFunctions.h>
#include <OSGLog.h>

using namespace OSG;

bool initFuncWrapperFunc(void)
{
    cerr << "initFuncWrapperFunc called" << endl;
    return true;
}

static InitFuncWrapper testInitFuncWrapper(initFuncWrapperFunc);


bool staticInitFuncWrapperFunc(void)
{
    cerr << "staticInitFuncWrapperFunc called" << endl;
    return true;
}

static StaticInitFuncWrapper testStaticInitFuncWrapper(staticInitFuncWrapperFunc);


bool initTestFunc(void)
{
    cerr << "initTestFunc called" << endl;
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
    cerr << "Main started" << endl;
    
    osgInit(argc,argv);

    cerr << "osgInit called" << endl;
    
    osgExit();

    cerr << "osgExit called" << endl;

    return 0;
}



