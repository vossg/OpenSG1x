#include <iostream>

#include <OSGStatElem.h>
#include <OSGStatCollector.h>
#include <OSGStatElemDesc.h>
#include <OSGStatTimeElem.h>
#include <OSGStatRealElem.h>
#include <OSGStatIntElem.h>
#include <OSGTime.h>
#include <OSGDrawActionBase.h>

#include <string>

OSG_USING_NAMESPACE

StatElemDesc<StatIntElem > fooDesc ("foo","foo desc");
StatElemDesc<StatRealElem> barDesc ("bar","bar desc");

int main (int argc, char **argv)
{
    StatCollector collector;
    UInt32 count = 100000,i;
    Time start,stop;
    DrawActionBaseP dummy = (DrawActionBaseP) DrawActionBase::create();
    dummy->setStatistics(&collector);
    
    start = getSystemTime();
    for(i = 0; i < count; ++i)
    {
        dummy->getStatistics()->getElem(fooDesc)->inc();
    }
    stop = getSystemTime();    
    std::cerr << "Int(inc): " << (stop-start)/count << "sec" << std::endl;
    
    start = getSystemTime();
    for(i = 0; i < count; ++i)
    {
        dummy->getStatistics()->getElem(fooDesc,false)->inc();
    }
    stop = getSystemTime();    
    std::cerr << "Int(inc): " << (stop-start)/count << "sec" << std::endl;

    start = getSystemTime();
    for(i = 0; i < count; ++i)
    {
        dummy->getStatistics()->getElem(barDesc)->set(3.141);
    }
    stop = getSystemTime();
    
    std::cerr << "Real(set): " << (stop-start)/count << "sec" << std::endl;

    return 0;
}
