#include <iostream>

#include <OSGStatElem.h>
#include <OSGStatCollector.h>
#include <OSGStatElemDesc.h>
#include <OSGStatTimeElem.h>
#include <OSGStatRealElem.h>
#include <OSGStatIntElem.h>

#include <string>

osg::StatElemDesc fpsDesc ("fps","fps desc", osg::StatTimeElem::create);
osg::StatElemDesc fooDesc ("foo","foo desc", osg::StatIntElem::create);
osg::StatElemDesc barDesc ("bar","bar desc", osg::StatRealElem::create);

int main (int argc, char **argv)
{
    osg::StatCollector collector;
    osg::StatElem *elem;
    osg::Int32 fpsID = fpsDesc.getID();
    std::string str;

    elem = collector.getElem(fpsID);

    collector.getElem<osg::StatTimeElem> (fpsDesc)->start();
    collector.getElem<osg::StatIntElem>  (fooDesc)->inc();
    collector.getElem<osg::StatRealElem> (barDesc)->set(2.0);

    collector.getElem<osg::StatTimeElem> (fpsDesc)->stop();
    collector.getElem ( fpsDesc )->putToString ( str );
    cerr << "Time out: " << str << endl;

    collector.getElem ( fooDesc )->putToString ( str );
    cerr << "Int  out: " << str << endl;

    collector.getElem ( barDesc )->putToString ( str );
    cerr << "Real out: " << str << endl;

    osg::StatElemDesc::printAll();
}
