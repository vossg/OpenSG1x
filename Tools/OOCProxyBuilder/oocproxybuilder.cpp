// Out-of-core mesh partitioning and clustering tool
// Based on the algorithm described in "Out-of-Core Compression of Gigantic
// Polygon Meshes" by Martin Isenburg and Stefan Gumhold (SIGGRAPH 2003)
// Uses the METIS and ANN libraries for the graph partitioning step, see 
// their respective licenses for usage restrictions

#include <ostream>
#include <fstream>

#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGTriangleIterator.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGGraphOpSeq.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGProxyGroup.h>
#include <OpenSG/OSGSimpleMaterial.h>

#include "MaterialPool.h"

#include "GeoReceiver.h"
#include "BBoxGeoRec.h"
#include "VGrid.h"
#include "SplitGeoRec.h"

#include "OOCFeeder.h"
#include "OOCOSGFeeder.h"
#include "OOCPLYFeeder.h"
#include "OOCSMBFeeder.h"

using namespace std;
OSG_USING_NAMESPACE;


// Global data


bool random_color = false;
bool concurrent = false;
UInt32 vertPerPart = 60000;
UInt32 nparts = 0;
std::string outformat = "osb";
std::string tmppath = ".";
UInt32 pagesize = 512;
UInt32 npages = 2048;
UInt32 nthreads = 0;
GraphOpSeq opseq;
std::string filebasename;    
SplitGeoRec *split;

// Helper classes

class PrintGeoRec : public GeoReceiver
{
  public:
  
    PrintGeoRec() : _nvert(0), _ntri(0) {}
    
    static void pnt(GeoReceiver *obj, const Pnt3f &pnt)
    {
        PrintGeoRec *me = reinterpret_cast<PrintGeoRec *>(obj);
        
        SLOG << "Pnt " << me->_nvert << " = (" << pnt << ")" 
                  << endLog;
        
        me->_nvert++;
    }
    
    static void tri(GeoReceiver *obj, UInt32 i1, UInt32 i2, 
                                             UInt32 i3, UInt32 mat)
    {
        PrintGeoRec *me = reinterpret_cast<PrintGeoRec *>(obj);
        
        SLOG << "Tri " << me->_ntri << " = (" << i1
                  << ", " << i2 << ", " << i3 << ") Mat " << mat
                  << endLog;
        
        me->_ntri++;    
    }

    virtual void print(std::ostream &s)
    {
    }
    
  private:
  
    UInt32 _nvert;
    UInt32 _ntri; 
};

class CreateGeoRec : public GeoReceiver
{
  public:
  
    CreateGeoRec(void) : 
        _ntris(0),
        _nvert(0)   
    {
        beginEditCP(_pos);
        _pos = GeoPositions3f::create();
    }
    
    static void pnt(GeoReceiver *obj, const Pnt3f &pnt)
    {
        CreateGeoRec *me = reinterpret_cast<CreateGeoRec *>(obj);

        FDEBUG(("CreateGeoRec::pnt(%d): (%.2f, %2.f, %.2f)\n",
                        me->_nvert, pnt[0], pnt[1], pnt[2]));

        me->_pos->push_back(pnt);        
        
        me->_nvert++;    
    }
    
    static void tri(GeoReceiver *obj, UInt32 i1, UInt32 i2, 
                                      UInt32 i3, UInt32 mat)
    {
        CreateGeoRec *me = reinterpret_cast<CreateGeoRec *>(obj);

        GeoIndicesPtr ind = me->_ind[mat];
        
        if(ind == NullFC)
        {   

            FDEBUG(("CreateGeoRec::tri(%d): new ind for mat %d\n",
                        me->_ntris, mat));
            ind = GeoIndicesUI32::create();
            beginEditCP(ind);
            me->_ind[mat] = ind;
        }

        FDEBUG(("CreateGeoRec::tri(%d): (%d %d %d) (mat %d)\n",
                        me->_ntris, i1, i2, i3, mat));
        ind->push_back(i1);        
        ind->push_back(i2);        
        ind->push_back(i3);        
        
        me->_ntris++;    
    }
    
    NodePtr createScene(void)
    {
        endEditCP(_pos);
        
        std::map<UInt32, GeoIndicesPtr>::iterator it, end;
        end = _ind.end();
        
        NodePtr scene;
        
        if(_ind.size() == 1)
        {
            scene = makeNodeFor(createGeo(_ind.begin()->first));
        }
        else
        {
            scene = makeNodeFor(Group::create());
            beginEditCP(scene);
            
            for(it = _ind.begin(); it != end; ++it)
            {
                scene->addChild(makeNodeFor(createGeo(it->first)));
            }
            
            endEditCP(scene);
        }
        
        return scene;
    }

    UInt32 getNVert(void)
    {
        return _nvert;
    }

    UInt32 getNTris(void)
    {
        return _ntris;
    }
    
    virtual void print(std::ostream &s)
    {
    }
    
  private:
  
    GeoPositionsPtr _pos;
    std::map<UInt32, GeoIndicesPtr> _ind; 
    
    UInt32 _ntris, _nvert;

    
    GeometryPtr createGeo(UInt32 mat)
    {
        GeoIndicesPtr ind = _ind[mat];
        
        FDEBUG(("CreateGeoRec::createGeo: Mat %d: %d inds (%d tris)\n",
                mat, ind->getSize(), ind->getSize()/3));
                
        endEditCP(ind);

        GeometryPtr geo = Geometry::create();

        GeoPLengthsUI32Ptr len = GeoPLengthsUI32::create();
        beginEditCP(len);
        len->push_back(ind->getSize());
        endEditCP(len);

        GeoPTypesUI8Ptr typ = GeoPTypesUI8::create();
        beginEditCP(typ);
        typ->push_back(GL_TRIANGLES);
        endEditCP(typ);

        beginEditCP(geo);
        if(random_color)
        {
            SimpleMaterialPtr mat = SimpleMaterial::create();
            beginEditCP(mat);
            Color3f c(  drand48() * .7f + .3f,
                        drand48() * .7f + .3f,
                        drand48() * .7f + .3f);
            mat->setDiffuse(c);
            mat->setSpecular(Color3f(1.f,1.f,1.f));
            mat->setShininess(10.f);                        
            endEditCP(mat);
            geo->setMaterial(mat);
        }
        else
        {
            geo->setMaterial(MaterialPool::getMaterial(mat));
        }
        geo->setPositions(_pos);
        geo->setIndices(ind);
        geo->setLengths(len);
        geo->setTypes(typ);
        
        geo->getIndexMapping().push_back(Geometry::MapPosition);
        endEditCP(geo);

        calcVertexNormals(geo);
        //calcFaceNormals(geo);
        createSingleIndex(geo);

        return geo;
    }


};

void usage(void)
{
    cerr 
    << "oocproxybuilder: {opt}* infile+" << endl
    << "Transform a model into a group of proxies" << endl
    << "Possible options:" << endl
    << "-v <num>: number of vertices per partition (Def: 60000)" << endl
    << "      Note that it will only approximated and might be +/- 10%" << endl
    << "-of 'ext': output format (Def: osb)" << endl
    << "-tmp 'path': path for .ooc temp files (Def: .)" << endl
    << "-go 'GraphSeq string': GraphOpSeq to run on each partial model" << endl
    << "          (Def: \"Stripe() GeoType(filter=Ind+Len)\")" << endl
    << "-con : mark ProxyGroups for concurrent loading (Def: off)" << endl
    << "-rc  : assign a random color to each partition (Def: off)" << endl
    << "-ps  : RandomAccessFile pagesize (Def: 512)" << endl
    << "-np  : RandomAccessFile npages (Def: 2048)" << endl
    ;
    
    exit(1);
}

struct partStats
{
    int vertmin;
    int vertmax;
    int vertsum;
    int trimin;
    int trimax;
    int trisum;

    partStats()
    : vertmin(0), vertmax(0), vertsum(0),
      trimin(0), trimax(0), trisum(0)
    {}

    partStats(int vmin, int vmax, int vsum, int tmin, int tmax, int tsum)
    : vertmin(vmin), vertmax(vmax), vertsum(vsum),
      trimin(vmin), trimax(vmax), trisum(vsum)
    {}

    partStats(int vcount, int tcount)
    : vertmin(vcount), vertmax(vcount), vertsum(vcount),
      trimin(tcount), trimax(tcount), trisum(tcount)
    {}
           
    void operator += (partStats &other)
    {
        vertmin = osgMin(vertmin, other.vertmin);
        vertmax = osgMax(vertmax, other.vertmax);
        vertsum += other.vertsum;
        trimin  = osgMin(trimin, other.trimin);
        trimax  = osgMax(trimax, other.trimax);
        trisum  += other.trisum;
    }
};

ProxyGroupPtr createPart(int i, partStats &stats)
{
    CreateGeoRec r;

    SLOG << "Assembling geometry for part " << i + 1 << " of "
         << nparts << endLog;

    split->feedResults(i, &r, &CreateGeoRec::pnt, &CreateGeoRec::tri);

    SLOG << "Got " << r.getNVert() << " verts, " 
                   << r.getNTris() << " tris, creating object..." << endLog;

    partStats s(r.getNVert(), r.getNTris());
    stats += s;

    char name[filebasename.size() + 20];
    sprintf(name, "%s_%04d.%s", filebasename.c_str(), i, outformat.c_str());

    NodePtr node = r.createScene();

    SLOG << "Running graph ops..." << endLog;
    opseq.run(node);

    SLOG << "Writing..." << endLog;
    SceneFileHandler::the().write(node, name);

    // Wrap it in a ProxyGroup and keep it

    ProxyGroupPtr proxy = ProxyGroup::create();

    beginEditCP(proxy);
    proxy->setVolume(node->getVolume(true));
    proxy->setUrl(name);
    proxy->setIndices(r.getNTris() * 3);
    proxy->setTriangles(r.getNTris());
    proxy->setPositions(r.getNVert());
    proxy->setGeometries(1);
    proxy->setConcurrentLoad(concurrent);
    endEditCP(proxy);

    subRefCP(node);
    
    return proxy;
}  

// Multi-threading stuff

struct ThreadData
{
    // Input Data
    Thread* thread;
    int firstPart, nParts;
    
    // Output Data
    partStats stats;
    std::vector<ProxyGroupPtr> proxies;  
};

void runThread(void *args)
{
    ThreadData *data = reinterpret_cast<ThreadData *>(args);
    
    for(int i = 0; i < data->nParts; ++i)
    {
        data->proxies.push_back(createPart(i + data->firstPart, data->stats));
    }
}

// Main program

int main(int argc, char *argv[])
{
    osgInit(argc,argv);

    osgLog().addHeaderElem(LOG_TIMESTAMP_HEADER);
    
    std::string opstring("Stripe() GeoType(filter=Ind+Len)");
   
    while(argc > 1 && argv[1][0] == '-')
    {
        if(!strcmp(argv[1], "-go"))
        {
            opstring = argv[2];
            SLOG << "opt: graphop seq set to " << opstring
                 << endLog;
            argc -= 2, argv += 2;
        }
        else if(!strcmp(argv[1], "-of"))
        {
            outformat = argv[2];
            SLOG << "opt: output format set to " << outformat
                 << endLog;
            argc -= 2, argv += 2;
        }
        else if(!strcmp(argv[1], "-tmp"))
        {
            tmppath = argv[2];
            SLOG << "opt: tmp path set to " << tmppath
                 << endLog;
            argc -= 2, argv += 2;
        }
        else if(!strcmp(argv[1], "-v"))
        {
            vertPerPart = atoi(argv[2]);
            SLOG << "opt: splitting into partition with " << vertPerPart
                 << " vertices" << endLog;
            argc -= 2, argv += 2;
        }
        else if(!strcmp(argv[1], "-pa"))
        {
            nparts = atoi(argv[2]);
            SLOG << "opt: splitting into " << nparts
                 << " parts" << endLog;
            argc -= 2, argv += 2;
        }
        else if(!strcmp(argv[1], "-ps"))
        {
            pagesize = atoi(argv[2]);
            SLOG << "opt: RAFile pagesize set to " << pagesize
                 << endLog;
            argc -= 2, argv += 2;
        }
        else if(!strcmp(argv[1], "-np"))
        {
            npages = atoi(argv[2]);
            SLOG << "opt: RAFile npages set to " << npages
                 << endLog;
            argc -= 2, argv += 2;
        }
        else if(!strcmp(argv[1], "-rc"))
        {
            random_color = true;
            SLOG << "opt: random coloring activated" << endLog;
            argc -= 1, argv += 1;
        }
        else if(!strcmp(argv[1], "-con"))
        {
            concurrent = true;
            SLOG << "opt: concurrent loading Proxy activated" << endLog;
            argc -= 1, argv += 1;
        }
        else if(!strcmp(argv[1], "-nt"))
        {
            nthreads = atoi(argv[2]);
            SLOG << "opt: use " << nthreads
                 << " threads for geometry creation" << endLog;
            argc -= 2, argv += 2;
            SLOG << "WARNING: multi-threading doesn't work with all" 
                 << " file formats (notably OSB)!" <<  endLog;
        }
        else
        {
            usage();
        }
    }
    
    
    opseq.setGraphOps(opstring.c_str());
     
    OOCFeeder *feeder = NULL;
    NodeRefPtr geo;
   
    if(argc == 1)
    {
        //geo = makeLatLongSphere(4, 4, 2);
        //geo = makeTorus(.5, 1.5, 20, 20);
        geo = makeBox(1,1,1, 2,2,1);
        
        filebasename = "test";
        
        feeder = new OOCOSGFeeder(geo);
    }
    else
    {       
        filebasename = argv[1];
        
        int i = filebasename.rfind(".");
        
        if(!filebasename.compare(i,3,".gz"))
            i = filebasename.rfind(".", i - 1);
        
        if(!filebasename.compare(i,4,".ply"))
        {
            SLOG << "Found PLY, running out of core..." << endLog;
            
            feeder = new OOCPLYFeeder(argv+1, argc - 1);
        }
        else
        if(!filebasename.compare(i,4,".smb"))
        {
            SLOG << "Found SMB, running out of core..." << endLog;
            
            feeder = new OOCSMBFeeder(argv+1, argc - 1);
        }
        else
        {
            SLOG << "Generic format, using piece load feeder..." << endLog;

            feeder = new OOCOSGFeeder(argv+1, argc - 1);
        }
        
        if(i != std::string::npos)
            filebasename.erase(i);
            
        if((i = filebasename.rfind("/")) != std::string::npos)
        {
            filebasename.erase(filebasename.begin(), filebasename.begin() + i + 1);
        }
    }
     
    SLOG << "Calculating BBox..." << endLog;
   
    // Pass 1: Calc BBox and count vertices
    Vec3f bblow, bbhigh;
    UInt32 npts;
#if 0
    BBoxGeoRec bb;
    
    feeder->feedPoints(&bb, &BBoxGeoRec::receive);
    bblow = bb.getLow();
    bbhigh = bb.getHigh();
    npts = bb.getNPts();
    
    SLOG << "done: " << bb << endLog;
#else
    feeder->calcBasics();
    bblow = feeder->getBBMin();
    bbhigh = feeder->getBBMax();
    npts = feeder->getNPoints();
    
    SLOG << "done: " << npts << " pts, (" << bblow << ")-(" << bbhigh 
         << ")" << endLog;
   
#endif    
    
    // Pass 2: Build and partition grid
     
    SLOG << "Building vertex grid..." << endLog;
    
    VGrid *grid = new VGrid(bblow, bbhigh, 
                            osgMin(npts, UInt32(10000000)));
    
    feeder->feedPoints(grid, &VGrid::insert);
    
    SLOG << "Vertex Grid done: " << *grid << endLog;
    
    if(nparts == 0)
        nparts = int(ceil(npts / (Real32)vertPerPart));
     
    SLOG << "Partitioning into " << nparts << " parts..." << endLog;
    
    grid->partition(nparts);
     
    SLOG << "Partitioning done" << endLog;
   
    // Pass 3: Build split geometry files and cluster-index file
     
    SLOG << "Running Point splitting..." << endLog;
   
    std::string tname = tmppath + '/' + filebasename;
    split = new SplitGeoRec(nparts, grid, tname);
    
    feeder->feedPoints(split, &SplitGeoRec::splitPnts);

    split->finishPnts(pagesize, npages);
     
    SLOG << "Point splitting done" << endLog;
 
    // Pass 4: Add triangles to split files, adding new verts if necessary
    // This takes the most time, as it needs to random access the vertices
    
    SLOG << "Running Face splitting..." << endLog;
  
    feeder->feedTris(split, &SplitGeoRec::splitTris);
     
    SLOG << "Face splitting done..." << endLog;
  
    // Pass 5: Fixup newly added verts
      
    SLOG << "Running Point fixup..." << endLog;
 
    feeder->feedPoints(split, &SplitGeoRec::fixPnts);
    
    SLOG << "Point fixup done..." << endLog;
  
    SLOG << *split << endLog;
  
    split->finishFixups();
    
    delete grid; // Don't need it any more
    
    // At this point the split files contain everything that's needed
    // to create the geometry. Do it.
      
    SLOG << "Creating Geometry..." << endLog;

    if(0)
    {
        for(UInt32 i = 0; i < nparts; ++i)
        {
            PrintGeoRec p;

            SLOG << "Partition " << i << endLog;

            split->feedResults(i, &p, &PrintGeoRec::pnt, &PrintGeoRec::tri);
        }
    }
    
    if (nthreads > 0)
    {       
        std::vector<ThreadData> threads;
        
        threads.resize(nthreads);
        
        // Divide the work
        for(int i = 0; i < nthreads; ++i)
        {
            threads[i].firstPart = (int)(nparts * i / (Real32) nthreads);
            threads[i].nParts = (int)(nparts * (i+1) / (Real32) nthreads) - 
                                 threads[i].firstPart;
            
        }
        
        // Start the threads       
        for(int j = 0; j < nthreads; ++j)
        {            	
	        threads[j].thread = dynamic_cast<Thread *>
                            (ThreadManager::the()->getThread(NULL));

            threads[j].thread->runFunction(runThread, 0, &threads[j]);
        }

        // Wait for them to finish       
        for(int j = 0; j < nthreads; ++j)
        {            	
             OSG::Thread::join(threads[j].thread);  
        }     
        
        // Merge the results
        GroupPtr group;
        group = Group::create();
        NodePtr gnode = makeNodeFor(group);
        
        partStats stats;
        
        beginEditCP(gnode);
        
        for(UInt32 i = 0; i < nthreads; ++i)
        {
            for(UInt32 j = 0; j < threads[i].proxies.size(); ++j)
            {
                gnode->addChild(makeNodeFor(threads[i].proxies[j]));
            }
            stats += threads[i].stats;
        }  
        
        endEditCP(gnode);

        SLOG << "Vertices (min/avg/max):" << stats.vertmin << " " 
             << stats.vertsum / nparts
             << " " << stats.vertmax << endLog;
        SLOG << "Triangles (min/avg/max):" << stats.trimin << " " 
             << stats.trisum / nparts
             << " " << stats.trimax << endLog;
           
        char name[filebasename.size() + 20];
        sprintf(name, "%s_prox.%s", filebasename.c_str(), outformat.c_str());

        SLOG << "Writing *_prox..." << endLog;
        SceneFileHandler::the().write(gnode, name);
    }
    else // Create Geometry & ProxyGroup
    {
        GroupPtr group;
        group = Group::create();
        NodePtr gnode = makeNodeFor(group);
        
        partStats stats;
        
        beginEditCP(gnode);
        
        for(UInt32 i = 0; i < nparts; ++i)
        {
            ProxyGroupPtr proxy = createPart(i, stats);

            gnode->addChild(makeNodeFor(proxy));
        }  
        
        endEditCP(gnode);

        SLOG << "Vertices (min/avg/max):" << stats.vertmin << " " 
             << stats.vertsum / nparts
             << " " << stats.vertmax << endLog;
        SLOG << "Triangles (min/avg/max):" << stats.trimin << " " 
             << stats.trisum / nparts
             << " " << stats.trimax << endLog;
           
        char name[filebasename.size() + 20];
        sprintf(name, "%s_prox.%s", filebasename.c_str(), outformat.c_str());

        SLOG << "Writing *_prox..." << endLog;
        SceneFileHandler::the().write(gnode, name);
    }
    
    split->finish();

    // Done
    
    osgExit();
    
    return 0;
}
