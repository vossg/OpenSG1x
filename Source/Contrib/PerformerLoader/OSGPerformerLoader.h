

#ifndef OSG_PERFORMER_LOADER_H
#define OSG_PERFORMER_LOADER_H

#include <map>

#include <OSGConfig.h>
#include <OSGNode.h>
#include <OSGMaterial.h>
#include <OSGGeometry.h>
#include <OSGStateChunk.h>

#include <Performer/pf.h>
#include <Performer/pr/pfGeoArray.h>

class PerformerLoader
{ 
public:

    PerformerLoader(void);

    ~PerformerLoader();

    OSG::NodePtr load(const OSG::Char8 *fileName);

    bool setHighestLODOnly(bool val = true);
    
private:

    OSG::NodePtr traverse(pfNode *node);
    OSG::GeometryPtr traverseGSet(OSG::NodePtr node, pfGeoSet *geode);
    OSG::GeometryPtr traverseGArray(OSG::NodePtr node, pfGeoArray *geode);
    OSG::MaterialPtr traverseGState(OSG::NodePtr node, pfGeoState *gstate);
    
    std::map<pfNode     *, OSG::NodePtr>        _nodes;
    std::map<pfGeoState *, OSG::MaterialPtr>    _materials;  
    std::map<pfGeoSet   *, OSG::GeometryPtr>    _geometries;  
    std::map<std::pair<void*, void*>, OSG::StateChunkPtr>  _chunks;  
    
    // Configuration options
    
    bool _highestLODOnly;
    
};

#endif // OSG_PERFORMER_LOADER_H
