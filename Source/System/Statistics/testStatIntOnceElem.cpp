#include <iostream>
#include <unistd.h>

#include <string>

#include "OSGStatElem.h"
#include "OSGStatCollector.h"
#include "OSGStatElemDesc.h"
#include "OSGStatIntOnceElem.h"

OSG::StatElemDesc<OSG::StatIntOnceElem> fooDesc ("foo","foo desc");

int main (int argc, char **argv)
{
    OSG::StatCollector collector;
    OSG::StatIntOnceElem *elem;

    elem = collector.getElem(fooDesc);
       
    std::cerr << "Start:" << elem->getValue() << std::endl;
      
    elem->inc(0);
    std::cerr << "After inc(0):" << elem->getValue() << std::endl;
      
    elem->inc(0);
    std::cerr << "After inc(0):" << elem->getValue() << std::endl;
       
    elem->add(1,5);
    std::cerr << "After add(1,5):" << elem->getValue() << std::endl;
       
    elem->sub(1,2);
    std::cerr << "After sub(1,2):" << elem->getValue() << std::endl;

    elem->reset();
    std::cerr << "After reset:" << elem->getValue() << std::endl;
      
    elem->inc(0);
    std::cerr << "After inc(0):" << elem->getValue() << std::endl;
       
    elem->sub(1,2);
    std::cerr << "After sub(1,2):" << elem->getValue() << std::endl;
    
    exit(0);
}
