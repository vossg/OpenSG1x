#include <iostream>

#include <OSGStatElem.h>
#include <OSGStatCollector.h>
#include <OSGStatElemDesc.h>
#include <OSGStatElemTypes.h>

#include <string>

osg::StatElemDesc<osg::StatTimeElem  > fpsDesc ("fps","fps desc");
osg::StatElemDesc<osg::StatIntElem   > fooDesc ("foo","foo desc");
osg::StatElemDesc<osg::StatRealElem  > barDesc ("bar","bar desc");
osg::StatElemDesc<osg::StatStringElem> bazDesc ("baz","baz desc");

int main (int argc, char **argv)
{
    osg::StatCollector collector;
    osg::StatElem *elem;
    osg::Int32 fpsID = fpsDesc.getID();
    std::string str;

    elem = collector.getElem(fpsID);

    collector.getElem(fpsDesc)->start();
    collector.getElem(fooDesc)->inc();
    collector.getElem(barDesc)->set(2.0);
    collector.getElem(bazDesc)->set("HUGO");

    collector.getElem(fpsDesc)->stop();
    
    elem->putToString(str);
    cerr << "Time out: " << str << endl;
    
    elem->putToString(str, "Format: %f");
    cerr << "Time formatted out: " << str << endl;
    
    elem->putToString(str, "Format: %ms");
    cerr << "Time ms formatted out: " << str << endl;
    
    elem->putToString(str, "Format: %r.2f 1/s");
    cerr << "Time r formatted out: " << str << endl;

    collector.getElem(fooDesc)->putToString(str);
    cerr << "Int out: " << str << endl;

    collector.getElem(fooDesc)->putToString(str, "Format: %04d");
    cerr << "Int formatted out: " << str << endl;

    collector.getElem(barDesc)->putToString(str);
    cerr << "Real out: " << str << endl;

    collector.getElem(barDesc)->putToString(str, "Format: %4.2f");
    cerr << "Real formatted out: " << str << endl;

    collector.getElem(bazDesc)->putToString(str);
    cerr << "String out: " << str << endl;

    collector.getElem(bazDesc)->putToString(str, "Format: '%s'");
    cerr << "String formatted out: " << str << endl;

    collector.putToString(str);
    cerr << "Collector data:" << endl << str << endl;
 
    const osg::Char8 *c = str.c_str();
    collector.getFromString(c);
    collector.putToString(str);
    cerr << "Collector data:" << endl << str << endl;
    
    osg::StatElemDescBase::printAll();
}
