#include <iostream>
#include <unistd.h>

#include <OSGStatElem.h>
#include <OSGStatCollector.h>
#include <OSGStatElemDesc.h>
#include <OSGStatElemTypes.h>

#include <string>

OSG::StatElemDesc<OSG::StatTimeElem  > fpsDesc ("fps","fps desc");
OSG::StatElemDesc<OSG::StatIntElem   > fooDesc ("foo","foo desc");
OSG::StatElemDesc<OSG::StatRealElem  > barDesc ("bar","bar desc");
OSG::StatElemDesc<OSG::StatStringElem> bazDesc ("baz","baz desc");

int main (int argc, char **argv)
{
    OSG::StatCollector collector;
    OSG::StatElem *elem;
    OSG::Int32 fpsID = fpsDesc.getID();
    std::string str;

    elem = collector.getElem(fpsID);

    collector.getElem(fpsDesc)->start();
    collector.getElem(fooDesc)->inc();
    collector.getElem(barDesc)->set(2.0);
    collector.getElem(bazDesc)->set("HUGO");

    osgsleep(200);

    collector.getElem(fpsDesc)->stop();
    
    std::cerr << "Time real: " << elem->getValue() << std::endl;
    
    elem->putToString(str);
    std::cerr << "Time out: " << str << std::endl;
    
    elem->putToString(str, "Format: %f");
    std::cerr << "Time formatted out: " << str << std::endl;
    
    elem->putToString(str, "Format: %ms");
    std::cerr << "Time ms formatted out: " << str << std::endl;
    
    elem->putToString(str, "Format: %r.2f 1/s");
    std::cerr << "Time r formatted out: " << str << std::endl;
    
    std::cerr << "Int real: "
              << collector.getElem(fooDesc)->getValue() 
              << std::endl;

    collector.getElem(fooDesc)->putToString(str);
    std::cerr << "Int out: " << str << std::endl;

    collector.getElem(fooDesc)->putToString(str, "Format: %04d");
    std::cerr << "Int formatted out: " << str << std::endl;
    
    std::cerr << "Real real: " 
              << collector.getElem(barDesc)->getValue() 
              << std::endl;

    collector.getElem(barDesc)->putToString(str);
    std::cerr << "Real out: " << str << std::endl;

    collector.getElem(barDesc)->putToString(str, "Format: %4.2f");
    std::cerr << "Real formatted out: " << str << std::endl;

    collector.getElem(bazDesc)->putToString(str);
    std::cerr << "String out: " << str << std::endl;

    collector.getElem(bazDesc)->putToString(str, "Format: '%s'");
    std::cerr << "String formatted out: " << str << std::endl;

    collector.putToString(str);
    std::cerr << "Collector data:" << std::endl << str << std::endl;
 
    const OSG::Char8 *c = str.c_str();
    collector.getFromString(c);
    collector.putToString(str);
    std::cerr << "Collector data:" << std::endl << str << std::endl;
    
    OSG::StatElemDescBase::printAll();
}
