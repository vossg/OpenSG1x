

#include <fstream>
#include <math.h>
#include <strings.h>

#include "OOCOSGFeeder.h"
#include "MaterialPool.h"

#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGPrimitiveIterator.h>
#include <OpenSG/OSGTriangleIterator.h>

OSG_USING_NAMESPACE;

OOCOSGFeeder::OOCOSGFeeder(OSG::NodePtr root) :
    OOCFeeder(NULL, 0)
{
    _root = root;
}

OOCOSGFeeder::OOCOSGFeeder(char *filenames[], int nf) :
    OOCFeeder(filenames, nf),
    _root(NullFC)
{
    if(nf == 1 && _filenames[0].find(".list") == _filenames[0].size() - 5)
    {
        std::string fn(_filenames[0]);
        std::ifstream list(fn.c_str());
        char line[2048];
        
        _filenames.clear();
        
        while(list.good())
        {
            list.getline(line,2048);
            std::ifstream tf(line);
            if(tf.good())
                _filenames.push_back(line);
        }
        
        SLOG << "Read " << _filenames.size() << " files from " << fn 
             << endLog;
    }
}

OOCOSGFeeder::~OOCOSGFeeder()
{
}

void OOCOSGFeeder::feedBoth(GeoReceiver *rec, GeoReceiver::pntRec pfunc, 
                              GeoReceiver::triRec tfunc)
{
    _rec = rec;
    _pfunc = pfunc;
    _tfunc = tfunc;
    _pntindexbase = 0;
    
    _pntprog = _triprog = 0;
    _nextpntprog = _nexttriprog = 0.f;
    
    if(_npts != 0)
        SLOG << "Progress: ";
    
    if(_root != NullFC)
    {
        traverse(_root, 
                 osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE,
                                                     OOCOSGFeeder,
                                                     NodePtr>(
                                                         this, 
                                                         &OOCOSGFeeder::enter));
    }
    else
    {
        for(UInt32 f = 0; f < _filenames.size(); ++f)
        {
            NodePtr root;

            _poss.clear();

            root = SceneFileHandler::the().read(_filenames[f].c_str(), NULL);

            if(root == NullFC)
            {
                FWARNING(("OOCOSGFeeder::doFeed: couldn't load %s, ignored!\n",
                            _filenames[f].c_str()));
                continue;
            }

            traverse(root, 
                 osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE,
                                                     OOCOSGFeeder,
                                                     NodePtr>(
                                                         this, 
                                                         &OOCOSGFeeder::enter));
        
            subRefCP(root);
        }
    }
    
    if(_npts != 0)
        PLOG << "100%" << endLog;
}


Action::ResultE OOCOSGFeeder::enter(NodePtr& node)
{
    GeometryPtr geo = GeometryPtr::dcast(node->getCore());
    
    if(geo == NullFC)
        return Action::Continue;
    
    GeoPositionsPtr pos = geo->getPositions();
    UInt32 pntindexbase;
    
    if(_poss.find(pos) != _poss.end())
    {
        pntindexbase = _poss[pos];
        pos = NullFC;
    }
    else
    {
        pntindexbase = _pntindexbase;
        _poss[pos]   = _pntindexbase;
        _pntindexbase += pos->getSize();
    }   
    
    UInt32 matind = MaterialPool::addMaterial(geo->getMaterial());

    if(pos != NullFC)
    {
        if(_pfunc != NULL)
        {
            Pnt3f p;
            UInt32 s = pos->getSize();
            
            for(UInt32 i = 0; i < s; ++i)
            {
                if(_npts != 0)
                {
                    ++_pntprog;
                    
                    Real32 prog = _pntprog / (Real32)_npts;
                    if(prog > _nextpntprog)
                    {
                        PLOG << _nextpntprog * 100 << "%..";
                        _nextpntprog += 0.1;
                    }
                }
                
                pos->getValue(p, i);
                
                _pfunc(_rec, p);
            }            
        }
    }
    
    if(_tfunc != NULL)
    {
        TriangleIterator it, end = geo->endTriangles();

        for(it = geo->beginTriangles(); 
            it != end; 
            ++it)
        {
            if(_ntris != 0)
            {
                ++_triprog;

                Real32 prog = _triprog / (Real32)_ntris;
                if(prog > _nexttriprog)
                {
                    PLOG << _nexttriprog * 100 << "%..";
                    _nexttriprog += 0.1;
                }
            }
                
            _tfunc(_rec, it.getPositionIndex(0) + pntindexbase, 
                         it.getPositionIndex(1) + pntindexbase, 
                         it.getPositionIndex(2) + pntindexbase,
                         matind);
        }
    }
    
    return Action::Continue;
}
