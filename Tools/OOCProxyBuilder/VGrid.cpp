// Main file for Vertex Grid class

extern "C"
{
#include <metis.h>
}

#include <ANN/ANN.h>

#include <OpenSG/OSGLog.h>

#include "VGrid.h"


VGrid::VGrid(const Vec3f &bblow, const Vec3f &bbhigh, UInt16 xdiv, UInt16 ydiv, UInt16 zdiv)
{
    initialize(bblow, bbhigh, xdiv, ydiv, zdiv);
}



VGrid::VGrid(const Vec3f &bblow, const Vec3f &bbhigh, UInt32 nnodes)
{
    Vec3f delta = bbhigh - bblow;
    Real32 div;
    
    div = osgpow( nnodes / (delta[0] * delta[1] * delta[2]), 1.f/3.f);
    
    initialize(bblow, bbhigh, UInt16(div * delta[0]), 
                              UInt16(div * delta[1]), 
                              UInt16(div * delta[2]));
}


void VGrid::initialize(const Vec3f &bblow, const Vec3f &bbhigh, 
                    UInt16 xdiv, UInt16 ydiv, UInt16 zdiv)
{         
    _map.clear();
    
    SLOG << "VGrid::initialize: (" << bblow << ") to (" 
         << bbhigh << ") Div:" << xdiv << "," << ydiv << ","
         << zdiv << " (" << xdiv * ydiv * zdiv << " Nodes)" << endLog;
   
    _bblow = bblow;
    _bbhigh = bbhigh;
    
    _xdiv = xdiv;
    _ydiv = ydiv;   
    _zdiv = zdiv;
 
    Vec3f delta = bbhigh - bblow + Vec3f(Eps,Eps,Eps);
    
    _xbase = bblow.x();
    _xscale = xdiv / delta.x();
    _ybase = bblow.y();
    _yscale = ydiv / delta.y();
    _zbase = bblow.z();
    _zscale = zdiv / delta.z();
    
    _ystep = xdiv;
    _zstep = xdiv * ydiv;
}

void VGrid::insert(GeoReceiver *rec, const Pnt3f &pnt)
{
    VGrid *me = reinterpret_cast<VGrid *>(rec);
    
    UInt32 id = me->map(pnt);
    
    me->_map[id].nvert ++;
}

void VGrid::print(std::ostream &str)
{
    NodeMap::const_iterator it;
    
    UInt32 usedverts = 0;
    
    for(it = _map.begin(); it != _map.end(); ++it)
    {
        const NodeMap::value_type val(*it);
        
        usedverts += val.second.nvert;
   }
   
   str << "VGrid: Used " << _map.size() << " out of " 
        << _xdiv * _ydiv *_zdiv
       << " Nodes. Average number of verts/node: " 
       << usedverts / _map.size();
}

// add neighbour to inds adjcny list. Each vert has max k neighbours
// return -1 if full, index if suceeded

const int unusedAdj = -100;

static int addIndex(idxtype *adjcny, int k, int ind, int neighbour)
{
    //FNOTICE(("addIndex %d %d:", ind, neighbour));
    
    int j;
    // Is it in adjacency list already?
    for(j = ind * k; j < (ind + 1) * k; ++j)
        if(adjcny[j] == neighbour)
            break;

    if(j != (ind + 1) * k) // Yes, ignore it
    {
        //FNOTICE(("found\n"));
        return -1;
    }
    
    // Add it to inds adjacency list, if a free spot is available
    for(j = ind * k; j < (ind + 1) * k; ++j)
        if(adjcny[j] == unusedAdj)
            break;

    if(j == (ind + 1) * k) // Couldn't find a free spot
    {
        //FNOTICE(("full\n"));
        return -1;
    }

    //FNOTICE(("at %d\n", j - ind * k));
    
    return j;
}
 
static int usedIndexCount(idxtype *adjcny, int k, int ind)
{
    int cnt = 0;
    
    for(int j = ind * k; j < (ind + 1) * k; ++j)
        if(adjcny[j] != unusedAdj)
            ++cnt;    
    return cnt;
}
 

void VGrid::partition(int nparts)
{
    if(nparts < 1)
    {
        FWARNING(("VGrid::partition: Can't create no partition!\n"));
        return;
    }
    if(nparts < 2)
    {
        FWARNING(("VGrid::partition: 1 partition specified. Doing nothing!\n"));
        return;
    }
    
    // Turn our grid into an AAN graph

	ANNpointArray		dataPts;				// data points
	ANNkd_tree*			kdTree;					// search structure
    
	dataPts = annAllocPts(_map.size(), 3);    // allocate data points
    
    UInt32 *mapids = new UInt32 [_map.size()];
    
    NodeMap::const_iterator it;
    int nPts = 0;
    
    for(it = _map.begin(); it != _map.end(); ++it)
    {
        const NodeMap::value_type &val(*it);
        
        Pnt3f p = unmap(val.first);
        
        mapids[nPts] = val.first;
        
        dataPts[nPts][0] = p[0];
        dataPts[nPts][1] = p[1];
        dataPts[nPts][2] = p[2];
        ++nPts;
   }
   
    SNOTICE << "Building KDTree" << endLog;
    
	kdTree = new ANNkd_tree(					// build search structure
					dataPts,					// the data points
					nPts,						// number of points
					3);						    // dimension of space

    // Now find k nearest neighbours for each cell
    
    // Find maxk neighbours, keep at least mink. If less than mink found,
    // increase buffer and retry
    
    const int mink = 6, maxk = 10;
    int buffersize = 4;

    double			    eps     = 0;            // error bound
	ANNpoint			queryPt;				// query point

    std::vector<ANNidx> nnIdx;
    std::vector<ANNdist> dists;    
    nnIdx.resize(maxk + buffersize);
    dists.resize(maxk + buffersize);

	queryPt = annAllocPt(3);					// allocate query point

    UInt32 ind = 0;
    
    if(0)
    {
    for(it = _map.begin(); it != _map.end(); ++it, ++ind)
    {
        const NodeMap::value_type &val(*it);
        
        Pnt3f p = unmap(val.first);
        
        queryPt[0] = p[0];
        queryPt[1] = p[1];
        queryPt[2] = p[2];
        
		kdTree->annkSearch(						// search
				queryPt,						// query point
				maxk,							// number of near neighbors
				&nnIdx[0],						// nearest neighbors (returned)
				&dists[0],						// distance (returned)
				eps);							// error bound
        
        
		std::cout << ind << " Node " << val.first << " (" << p << ")" << std::endl;
		for (int i = 0; i < maxk; i++) {			// print summary
			dists[i] = sqrt(dists[i]);			// unsquare distance
			std::cout << "\t" << nnIdx[i] << "\t" << dists[i] << " ";
		}        
        std::cout << std::endl;
    }
    }
     
    // Some consistency tests, to diagnose crashes
    if(0)
    {
    ind = 0;
    for(it = _map.begin(); it != _map.end(); ++it, ++ind)
    {
        const NodeMap::value_type &val(*it);
        
        Pnt3f p = unmap(val.first);
        
        queryPt[0] = p[0];
        queryPt[1] = p[1];
        queryPt[2] = p[2];
        
		kdTree->annkSearch(						// search
				queryPt,						// query point
				maxk,							// number of near neighbors
				&nnIdx[0],						// nearest neighbors (returned)
				&dists[0],						// distance (returned)
				eps);							// error bound
        
		for (int i = 0; i < maxk; i++) 
        {
            if(nnIdx[i] < 0 || nnIdx[i] > nPts)
            {
                FWARNING(("VGrid::partition: nnIdx[i] = %d!\n", nnIdx[i]));
            }
		}        
    }
    }
  
    // Now feed the nearest-neighbour graph to METIS for partitioning
   
    idxtype *xadj;
    idxtype *adjncy;
    idxtype *vwgt;
   
    xadj = new idxtype [nPts + 1];
    adjncy = new idxtype [nPts * maxk];
    // Clear adjncy to -1
    for(ind = 0; ind < nPts * maxk; ++ind)
        adjncy[ind] = unusedAdj;
        
    vwgt = new idxtype [nPts];
    
    ind = 0;
   
    SNOTICE << "Building Metis" << endLog;
    
    int adj = 0;
    int bufsum = 0;
       
    for(it = _map.begin(); it != _map.end(); ++it, ++ind)
    {
        const NodeMap::value_type &val(*it);
        
        Pnt3f p = unmap(val.first);
        
        queryPt[0] = p[0];
        queryPt[1] = p[1];
        queryPt[2] = p[2];
        
        int buffer = 4;
        bool done = false;
        do
        {
            // ANN is approximate
            // So we need to find nearest neighbours until we have mink
            // useable neighbours found
            
		    kdTree->annkSearch(			// search
				    queryPt,			// query point
				    maxk + buffer,	    // number of near neighbors
				    &nnIdx[0],			// nearest neighbors (returned)
				    &dists[0],			// distance (returned)
				    eps);				// error bound

            xadj[ind] = ind * maxk;
            vwgt[ind] = val.second.nvert;

		    for (int i = 0; i < maxk + buffer; i++) 
            {
                if(nnIdx[i] == ind)
                    continue; // Ignore self-loops

                int j1, j2;
                j1 = addIndex(adjncy, maxk, ind, nnIdx[i]);
                j2 = addIndex(adjncy, maxk, nnIdx[i], ind);

                if(j1 < 0)
                    continue; // ind full

                if(j2 < 0)
                    continue; // nnIdx[i] full

                adjncy[j1] = nnIdx[i];
                adjncy[j2] = ind;
		    }
            
            // Do we have enough indices?
            if(usedIndexCount(adjncy, maxk, ind) >= mink)
            {
                done = true;
            }
            else
            {
                buffer = osgMin(int(buffer * 1.5), nPts - maxk);
                if(buffer > buffersize)
                {
                    buffersize = buffer;
                    nnIdx.resize(maxk + buffersize);
                    dists.resize(maxk + buffersize);
                    FINFO(("Buffer resized to %d (at %d / %d)!\n", 
                                buffersize, ind, nPts));
                }
            }
        }
        while(!done);
        bufsum += buffer;
    }
    xadj[ind] = ind * maxk;

    FNOTICE(("Average buffer used: %d\n", bufsum / nPts));
   
    // Cleanup the Metis graph: remove unused indices
    SNOTICE << "Cleanup Metis" << endLog;
    
    int removed = 0;
    int writeind = 0, readind = 0;
    
    for(int i = 0; i < nPts; ++i)
    {
        for(int j = 0; j < maxk; ++j, ++readind)
        {
            if(adjncy[readind] == unusedAdj)
            {
                ++removed;
            }
            else
            {   
                adjncy[writeind] = adjncy[readind];
                ++writeind;
            }
        }
        xadj[i+1] -= removed;
    } 
    
    SNOTICE << "Removed " << removed << " of " << nPts * maxk 
            << " indices" << endLog;
    
    
    // Write the graph to a Metis file for testing
    if(0)
    {
        FILE *f;
        f = fopen("mytest.mgraph","w");
        
        fprintf(f, "%d %d 10 1\n", nPts, xadj[nPts] / 2);
        
        for(UInt32 i = 0; i < nPts; ++i)
        {
            fprintf(f, "%d ", vwgt[i]);
            
            for (int j = xadj[i]; j < xadj[i+1]; j++) 
            {
                fprintf(f, "%d ", adjncy[j] + 1);
		    }  
            fprintf(f, "\n");     
        }
        fclose(f);
    }


    idxtype wghtflag = 2;
    idxtype numflag = 0;
    idxtype options[5] = {0,0,0,0,0};
    idxtype edgecut;
    idxtype * part;
    
    part = new idxtype [nPts];
   
    SNOTICE << "Partitioning (" << nparts << ")" << endLog;

#if 1 // This has crashed on me...    
    METIS_PartGraphKway(&nPts, xadj, adjncy, vwgt, NULL, &wghtflag,
        &numflag, &nparts, options, &edgecut, part);
#elif 1 // Try another one...
    METIS_PartGraphVKway(&nPts, xadj, adjncy, vwgt, NULL, &wghtflag,
        &numflag, &nparts, options, &edgecut, part);
#endif
   
    SNOTICE << "Done" << endLog;

    // Assign the partitioning to the grid cells

    // Print the Partitioning
    
    for(UInt32 j = 0; j < nparts; ++j)
    {
        for(UInt32 i = 0; i < nPts; ++i)
        {
            if(part[i] == j)
            {
                _map[mapids[i]].part = j;
            }
        }
    }
    
    if(0)
    {
    for(UInt32 j = 0; j < nparts; ++j)
    {
        std::cout << "Partition " << j << std::endl;
        
        for(UInt32 i = 0; i < nPts; ++i)
        {
            if(part[i] == j)
            {
                std::cout << " " << i << " (" 
                          << dataPts[i][0] << ","
                          << dataPts[i][1] << ","
                          << dataPts[i][2] << ")"
                          ;
            }
        }
        std::cout << std::endl;
    }
    }
    
    {
    UInt32 minv = 1L<<30, maxv = 0;
    
    for(UInt32 j = 0; j < nparts; ++j)
    {
        UInt32 vcnt = 0;
        
        for(UInt32 i = 0; i < nPts; ++i)
        {
            if(part[i] == j)
            {
                vcnt += _map[mapids[i]].nvert;
            }
        }
        
        if(vcnt > maxv) maxv = vcnt;
        if(vcnt < minv) minv = vcnt;        
    }
    SNOTICE << "Minv: " << minv << ", Maxv: " << maxv << endLog;
    }
    
    // Now clean up
    
    delete kdTree;
	annDeallocPts(dataPts);
	annDeallocPt(queryPt);
    
    annClose();
    
    delete [] mapids;
    delete [] xadj;
    delete [] adjncy;
    delete [] vwgt;
    delete [] part;
}
