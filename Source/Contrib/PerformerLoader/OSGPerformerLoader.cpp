
#include <string>
using namespace std;

#include "OSGPerformerLoader.h"

// Include Performer Headers

#include <Performer/pfdu.h>
#include <Performer/pf/pfNode.h>
#include <Performer/pf/pfGroup.h>
#include <Performer/pf/pfGeode.h>
#include <Performer/pf/pfScene.h>
#include <Performer/pf/pfLayer.h>
#include <Performer/pf/pfLOD.h>
#include <Performer/pf/pfBillboard.h>
#include <Performer/pf/pfParaSurface.h>
#include <Performer/pf/pfLightSource.h>
#include <Performer/pf/pfSCS.h>
#include <Performer/pf/pfDCS.h>

#include <Performer/pr/pfMaterial.h>
#include <Performer/pr/pfTexture.h>

// Include OpenSG Headers

#include <OSGGL.h>
#include <OSGNodePtr.h>
#include <OSGGeometry.h>
#include <OSGGeoPropPtrs.h>
#include <OSGGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGTransform.h>
#include <OSGDistanceLOD.h>
#include <OSGSimpleAttachments.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>

#include <OSGSceneFileHandler.h>

using namespace OSG; // !!! ??? OSG_USING_NAMESPACE didn't work

PerformerLoader::PerformerLoader(void)
{
}

PerformerLoader::~PerformerLoader()
{

}

bool PerformerLoader::setHighestLODOnly(bool val)
{
    bool oldval = _highestLODOnly;
    _highestLODOnly = val;
    
    return oldval;
}

NodePtr PerformerLoader::load(const Char8 *fileName)
{
    pfNode *proot;
    
    proot = pfdLoadFile(fileName);
    
    if(proot == NULL)
    {
        FWARNING(("PerformerLoader::load: error loading '%s'!\n", fileName));
        return NullFC;
    }

    _nodes.clear();
    _materials.clear();
    _geometries.clear();
    _chunks.clear();
    
    NodePtr oroot;
    
    oroot = traverse(proot);

    pfDelete(proot);

    if(getName(oroot) == NULL)
    {
        setName(oroot, fileName);
    }
    
    _nodes.clear();
    _materials.clear();
    _geometries.clear();
    _chunks.clear();
    
    return oroot;
}


// Performer -> OpenSG functions

NodePtr PerformerLoader::traverse(pfNode *node)
{
    FINFO(("PfL:traverse: traversing \"%s\": %p (%s)\n", 
        node->getName()?node->getName():"Unnamed",
        node, pfGetTypeName(node)));    
    
    if(_nodes.find(node) != _nodes.end())
    {
        FINFO(("PfL:traverse: found in nodemap as %p.\n",
                _nodes[node].getCPtr()));    
        
        return cloneTree(_nodes[node]);
    }
    
    NodePtr n = Node::create();
    NodeCorePtr core = NullFC; 
    
    beginEditCP(n);
    
    setName(n, node->getName());
    
	if (node->getType()->isDerivedFrom(pfGroup::getClassType()))
	{
        pfGroup *group = dynamic_cast<pfGroup *>(node);
        
        int ind = 0;
        int num = group->getNumChildren();

	    if (node->getType()->isDerivedFrom(pfLOD::getClassType()))
	    {
            if(_highestLODOnly)
            {
                num = osgMin(num, 1);
                core = Group::create();
            }
            else
            {
                pfLOD *lod = dynamic_cast<pfLOD *>(node);

                DistanceLODPtr l = DistanceLOD::create();

                beginEditCP(l);

                for(int i = 0; i < lod->getNumRanges(); ++i)
                {
                    l->getRange().push_back(lod->getRange(i));
                }

                endEditCP(l);

                core = l;
            }
	    }
	    else if (node->getType()->isDerivedFrom(pfSCS::getClassType()))
	    {
            pfSCS *scs = dynamic_cast<pfSCS *>(node);
            
            if (node->getType()->isDerivedFrom(pfDCS::getClassType()))
            {
            }
            
            pfMatrix pmat;            
            scs->getMat(pmat);
            
            Matrix omat;
            
            omat.setValue( pmat[0][0], pmat[0][1], pmat[0][2], pmat[0][3], 
                           pmat[1][0], pmat[1][1], pmat[1][2], pmat[1][3], 
                           pmat[2][0], pmat[2][1], pmat[2][2], pmat[2][3], 
                           pmat[3][0], pmat[3][1], pmat[3][2], pmat[3][3]);
            
            omat.transpose();
            
            TransformPtr t = Transform::create();
            
            beginEditCP(t);
            t->setMatrix(omat);
            endEditCP(t);
            
            core = t;
	    }
	    else if (node->getType()->isDerivedFrom(pfScene::getClassType()))
	    {
            FWARNING(("PerformerLoader::traverse: encountered scene "
                      "group!\n"));
 	    }
	    else if (node->getType()->isDerivedFrom(pfLayer::getClassType()))
	    {
            FWARNING(("PerformerLoader::traverse: encountered layer "
                      "group!\n"));
	    }
        else if (node->getType() != pfGroup::getClassType())
        {
            FWARNING(("PerformerLoader::traverse: encountered unknown group"
                    " node of type %s\n", pfGetTypeName(node)));
            core = Group::create();
        }
        else
        {
            core = Group::create();
        }

	    for (;ind < num; ind++)
        {
            NodePtr cn = traverse(group->getChild(ind));
            if(cn != NullFC)
                n->addChild(cn);
        }
	}
	else if (node->getType()->isDerivedFrom(pfGeode::getClassType()))
	{
        pfGeode *geode = dynamic_cast<pfGeode *>(node);
        int num;
        
	    if (node->getType()->isDerivedFrom(pfBillboard::getClassType()))
	    {
		    num = geode->getNumGSets();
	    }
	    else if(node->getType()->isDerivedFrom(pfParaSurface::getClassType()))
	    {
            FWARNING(("PerformerLoader::traverse: encountered parametric"
                    " surface %s\n", pfGetTypeName(node)));
	    }
	    else
		    num = geode->getNumGSets();

        if(num == 1)
        {
            core = traverseGSet(n, geode->getGSet(0));
        }
        else
        {
            core = Group::create();
            
	        for (int i = 0; i < num; i++)
            {
		        GeometryPtr geo = traverseGSet(n, geode->getGSet(i));
                
                if(geo != NullFC)
                {
                    n->addChild(makeNodeFor(geo));
                }
            }
        }
	}
	else if (node->getType()->isDerivedFrom(pfLightSource::getClassType()))
	{
        FWARNING(("PerformerLoader::traverse: encountered light source!\n"));
        
	}
	else
	{
        FWARNING(("PerformerLoader::traverse: encountered unhandled node"
                " of type %s\n", pfGetTypeName(node)));
        return NullFC;
	}    
    
    if(core != NullFC)
    {
        n->setCore(core);
    }
    else
    {
        n->setCore(Group::create());
        FWARNING(("PerformerLoader::traverse: couldn't create core!\n"));
    }
    endEditCP(n);
    
    _nodes[node] = n;

    FINFO(("PfL:traverse: adding \"%s\": %p to nodelist using %p\n", 
        node->getName()?node->getName():"Unnamed",
        node, n.getCPtr()));    
    
    return n;
}


GeometryPtr PerformerLoader::traverseGSet(NodePtr node, pfGeoSet *gset)
{
    FINFO(("PerformerLoader::traverseGSet: traversing %p: ", gset));
    
    if(gset->getType()->isDerivedFrom(pfGeoArray::getClassType()))
    {
        return traverseGArray(node, dynamic_cast<pfGeoArray*>(gset));
    }
    
    pfGeoState *gstate = gset->getGState();

    int primtype, primcount, vertcount;

    primtype = gset->getPrimType();
    primcount = gset->getNumPrims();

    FINFO(("pt %d, pc %d ", primtype, primcount));

    int lencount, *lenlist;
    if (lenlist = gset->getPrimLengths())
	{
        int i;
	    for (i = 0, lencount = 0; i < primcount; i++)
		    lencount += PF_ABS(lenlist[i]);
	}	
    
    // Map Performer to OpenGL primtype
    UInt32 oprimtype = GL_POINTS;
    
    static int pprimtypes[] = { PFGS_POINTS, PFGS_LINES, PFGS_TRIS,
                                PFGS_QUADS, PFGS_LINESTRIPS, PFGS_TRISTRIPS, 
                                PFGS_TRIFANS, PFGS_POLYS, 
                                PFGS_FLAT_LINESTRIPS, PFGS_FLAT_TRISTRIPS, 
                                PFGS_FLAT_TRIFANS, -1};
    static int oprimtypes[] = { GL_POINTS, GL_LINES, GL_TRIANGLES,
                                GL_QUADS, GL_LINE_STRIP, GL_TRIANGLE_STRIP, 
                                GL_TRIANGLE_FAN, GL_POLYGON,
                                GL_LINE_STRIP, GL_TRIANGLE_STRIP, 
                                GL_TRIANGLE_FAN };
    
    for (UInt16 i = 0; pprimtypes[i] != -1; ++i)
        if(pprimtypes[i] == primtype)
            oprimtype = oprimtypes[i];
    
    int cn_buffer = 0;
    
    switch (primtype)
	{
	    case PFGS_POINTS:       vertcount = primcount;
                                primcount = 1;
		                        break;
	    case PFGS_LINES:        vertcount = primcount * 2;
		                        primcount = 1;
		                        break;
	    case PFGS_TRIS:         vertcount = primcount * 3;
		                        primcount = 1;
		                        break;
	    case PFGS_QUADS:        vertcount = primcount * 4;
		                        primcount = 1;
		                        break;
	    case PFGS_LINESTRIPS:
	    case PFGS_TRISTRIPS:
	    case PFGS_TRIFANS:
	    case PFGS_POLYS:        vertcount = lencount;
		                        break;
	    case PFGS_FLAT_LINESTRIPS:
            FDEBUG(("PerformerLoader::traverseGSet: found "
                      "primitive PFGS_FLAT_LINESTRIPS, will split into"
                      "individual lines!\n"));
            cn_buffer = 1;
            vertcount = lencount;
            break;
	    case PFGS_FLAT_TRISTRIPS:
            FDEBUG(("PerformerLoader::traverseGSet: found "
                      "primitive PFGS_FLAT_TRISTRIPS!\n"));
            cn_buffer = 2;
            vertcount = lencount;
            break;
	    case PFGS_FLAT_TRIFANS:
            FDEBUG(("PerformerLoader::traverseGSet: found "
                      "primitive PFGS_FLAT_TRIFANS!\n"));
            cn_buffer = 2;
            vertcount = lencount;
            break;
	}

    FINFO(("vc %d ", vertcount));
    
    // Fill the Geometry
    GeometryPtr ogeo = Geometry::create();
    
    beginEditCP(ogeo);
    
    if(gstate)
    {
        ogeo->setMaterial(traverseGState(node, gstate));       
    }
    else
    {
        ogeo->setMaterial(NullFC);
    }

    GeoPTypesPtr otypes = GeoPTypesUI8::create();

    beginEditCP(otypes);
     
    if (lenlist = gset->getPrimLengths())
	{
        GeoPLengthsUI32Ptr olens  = GeoPLengthsUI32::create();
        beginEditCP(olens);
	    for (int i = 0; i < primcount; i++)
        {
            otypes->push_back(oprimtype);
            olens->push_back(lenlist[i]);
        }
        endEditCP(olens);
        ogeo->setLengths(olens);
	}	
    else
    {
        otypes->push_back(oprimtype);
        lenlist = &vertcount;
        lencount = vertcount;
        if(primcount != 1)
            FWARNING(("PerformerLoader::traverseGSet: No lens, but "
                      "primcount=%d.\n", primcount));
    }

    endEditCP(otypes);

    ogeo->setTypes(otypes);
    
    // Convert the geo attributes

    int pmin, pmax;
    pfVec3 *pverts;
    ushort *pinds;
    
    GeoPositions3fPtr opos = GeoPositions3f::create();
    GeoIndicesUI16Ptr oind = GeoIndicesUI16::create();
    
    beginEditCP(opos);
    beginEditCP(oind);
       
    gset->getAttrLists(PFGS_COORD3, (void**)&pverts, &pinds);
    if(pverts)
    {
        if(pinds)
        {
            FINFO(("Vi %d-%d ", pmin, pmax));
            
            gset->getAttrRange(PFGS_COORD3, &pmin, &pmax);
            
            for(UInt32 i = 0; i < pmax+1; ++i)
                opos->push_back(Vec3f(pverts[i].vec));
            
            for(UInt32 i = 0; i < vertcount; ++i)
                oind->push_back(pinds[i]);
        }
        else
        {            
            FINFO(("V "));
            
            for(UInt32 i = 0; i < vertcount; ++i)
                opos->push_back(Vec3f(pverts[i].vec));           
        }
    }
    endEditCP(opos);
    endEditCP(oind);
    
    ogeo->setPositions(opos);
    
    if(oind->size())
    {
        ogeo->setIndices(oind);
    }
    else
    {
        subRefCP(oind);
    }
 
    int bind;
    
   
    // Normals
    if((bind = gset->getAttrBind(PFGS_NORMAL3)) != PFGS_OFF)
    {
        if(bind == PFGS_PER_PRIM)
        {
            FNOTICE(("PerformerLoader::traverseGSet: found PER_PRIM binding "
                     "for normals, ignoring them.\n"));
        }
        else if(bind == PFGS_OVERALL)
        {
            FINFO(("NO "));
            GeoNormals3fPtr onorm = GeoNormals3f::create();

            beginEditCP(onorm);
            pfVec3 *pnorms;
            gset->getAttrLists(PFGS_NORMAL3, (void**)&pnorms, &pinds);

            if(pnorms)
            {
                Vec3f c;
                c.setValues(pnorms[0].vec[0], pnorms[0].vec[1],
                                pnorms[0].vec[2]);
#if 0 // This assumes a single normal is used as overall. Not true for 1.x
                onorm->getField().push_back(c);
#else
                for(int i = 0; i < vertcount; ++i)
                    onorm->getField().push_back(c);
#endif            
            }

            endEditCP(onorm);

            ogeo->setNormals(onorm);
        }
        else
        {
            GeoNormals3fPtr onorm = GeoNormals3f::create();

            beginEditCP(onorm);

            pfVec3 *pnorms;
            ushort *pninds;
             
            gset->getAttrLists(PFGS_NORMAL3, (void**)&pnorms, &pninds);
            
            if(pnorms)
            {
                if(pninds)
                {
                    int pcmin, pcmax;
                    gset->getAttrRange(PFGS_NORMAL3, &pcmin, &pcmax);
            
                    FINFO(("NI %d-%d ", pcmin, pcmax));

                    // Check indices
                    if(pcmax != pmax)   
                        FWARNING(("Normal pmax %d != pmax %d!\n", 
                                    pcmax, pmax));
                                    
                    for(int i = 0; i < pcmax; ++i)
                    {
                        if(pinds[i] != pninds[i])
                            FWARNING(("Normal Index %d (%d) != vind (%d)!\n",
                                i, pninds[i], pinds[i]));
                    }
                    
                    int ind = 0;
                    for(int j = 0; j < primcount; ++j)
                    {
                        Vec3f c;
                        c.setValues(pnorms[0].vec[0], pnorms[0].vec[1],
                                    pnorms[0].vec[2]);
                        for(UInt32 i = 0; i < cn_buffer; ++i)
                        {
                            onorm->getField().push_back(c);
                        }

                        for(UInt32 i = 0; i < lenlist[j] - cn_buffer; 
                            ++i, ++ind)
                        {
                            Vec3f c;
                            c.setValues(pnorms[ind].vec[0], 
                                        pnorms[ind].vec[1],
                                        pnorms[ind].vec[2]);
                            onorm->getField().push_back(c);
                        }
                    }
                }
                else
                {
                    FINFO(("N "));
                    
                    int ind = 0;
                    for(int j = 0; j < primcount; ++j)
                    {
                        Vec3f c;
                        c.setValues(pnorms[0].vec[0], pnorms[0].vec[1],
                                    pnorms[0].vec[2]);
                        for(UInt32 i = 0; i < cn_buffer; ++i)
                        {
                            onorm->getField().push_back(c);
                        }

                        for(UInt32 i = 0; i < lenlist[j] - cn_buffer; 
                            ++i, ++ind)
                        {
                            Vec3f c;
                            c.setValues(pnorms[ind].vec[0], 
                                        pnorms[ind].vec[1],
                                        pnorms[ind].vec[2]);
                            onorm->getField().push_back(c);
                        }
                    }
                }
            }    
            endEditCP(onorm);

            ogeo->setNormals(onorm);
        }
    }

    // Colors
    if((bind = gset->getAttrBind(PFGS_COLOR4)) != PFGS_OFF)
    {
        if(bind == PFGS_PER_PRIM)
        {
            FNOTICE(("PerformerLoader::traverseGSet: found PER_PRIM binding "
                     "for colors, ignoring them.\n"));
        }
        else if(bind == PFGS_OVERALL)
        {
            FINFO(("CO "));
            GeoColors4fPtr ocols = GeoColors4f::create();

            beginEditCP(ocols);
            pfVec4 *pcols;
            gset->getAttrLists(PFGS_COLOR4, (void**)&pcols, &pinds);

            if(pcols)
            {
                Color4f c;
                c.setValuesRGBA(pcols[0].vec[0], pcols[0].vec[1],
                                pcols[0].vec[2], pcols[0].vec[3]);
#if 0 // This assumes a single colors is used as overall. Not true for 1.x
                ocols->getField().push_back(c);
#else
                for(int i = 0; i < vertcount; ++i)
                    ocols->getField().push_back(c);
#endif            
            }

            endEditCP(ocols);

            ogeo->setColors(ocols);
        }
        else
        {
            GeoColors4fPtr ocols = GeoColors4f::create();

            beginEditCP(ocols);

            pfVec4 *pcols;
            ushort *pcinds;
             
            gset->getAttrLists(PFGS_COLOR4, (void**)&pcols, &pcinds);
            
            if(pcols)
            {
                if(pcinds)
                {
                    int pcmin, pcmax;
                    gset->getAttrRange(PFGS_COLOR4, &pcmin, &pcmax);
                    
                    FINFO(("CI %d-%d ", pcmin, pcmax));

                    if(pcmax != pmax)   
                        FWARNING(("Color pmax %d != pmax %d!\n", 
                                    pcmax, pmax));
                                    
                    for(int i = 0; i < pcmax; ++i)
                    {
                        if(pinds[i] != pcinds[i])
                            FWARNING(("Color Index %d (%d) != vind (%d)!\n",
                                i, pcinds[i], pinds[i]));
                    }
                    
                    // !!! Indices ignored for now, assumed to be the same
                    // as for positions
                    
                    int ind = 0;
                    for(int j = 0; j < primcount; ++j)
                    {
                        Color4f c;
                        c.setValuesRGBA(pcols[0].vec[0], pcols[0].vec[1],
                                        pcols[0].vec[2], pcols[0].vec[3]);
                        for(UInt32 i = 0; i < cn_buffer; ++i)
                        {
                            ocols->getField().push_back(c);
                        }

                        for(UInt32 i = 0; i < lenlist[j] - cn_buffer; 
                            ++i, ++ind)
                        {
                            Color4f c;
                            c.setValuesRGBA(pcols[ind].vec[0], 
                                            pcols[ind].vec[1],
                                            pcols[ind].vec[2], 
                                            pcols[ind].vec[3]);
                            ocols->getField().push_back(c);
                        }
                    }
                }
                else
                {
                    FINFO(("C "));
                    
                    int ind = 0;
                    for(int j = 0; j < primcount; ++j)
                    {
                        Color4f c;
                        c.setValuesRGBA(pcols[0].vec[0], pcols[0].vec[1],
                                        pcols[0].vec[2], pcols[0].vec[3]);
                        for(UInt32 i = 0; i < cn_buffer; ++i)
                        {
                            ocols->getField().push_back(c);
                        }

                        for(UInt32 i = 0; i < lenlist[j] - cn_buffer; 
                            ++i, ++ind)
                        {
                            Color4f c;
                            c.setValuesRGBA(pcols[ind].vec[0], 
                                            pcols[ind].vec[1],
                                            pcols[ind].vec[2], 
                                            pcols[ind].vec[3]);
                            ocols->getField().push_back(c);
                        }
                    }
                }
            }    
            endEditCP(ocols);

            ogeo->setColors(ocols);
        }
    }
    
   
    // Texture coordinates
    if((bind = gset->getAttrBind(PFGS_TEXCOORD2)) != PFGS_OFF)
    {
        if(bind == PFGS_PER_PRIM)
        {
            FNOTICE(("PerformerLoader::traverseGSet: found PER_PRIM binding "
                     "for texcoords, ignoring them.\n"));
        }
        else if(bind == PFGS_OVERALL)
        {
            FINFO(("TO "));
            GeoTexCoords2fPtr otexc = GeoTexCoords2f::create();

            beginEditCP(otexc);
            pfVec2 *ptexcs;
            gset->getAttrLists(PFGS_TEXCOORD2, (void**)&ptexcs, &pinds);

            if(ptexcs)
            {
                Vec2f tc;
                tc.setValues(ptexcs[0].vec[0], ptexcs[0].vec[1]);
#if 0 // This assumes a single texcal is used as overall. Not true for 1.x
                otexc->getField().push_back(tc);
#else
                for(int i = 0; i < vertcount; ++i)
                    otexc->getField().push_back(tc);
#endif            
            }

            endEditCP(otexc);

            ogeo->setTexCoords(otexc);
        }
        else
        {
            GeoTexCoords2fPtr otexc = GeoTexCoords2f::create();

            beginEditCP(otexc);

            pfVec2 *ptexcs;
            ushort *ptexinds;
             
            gset->getAttrLists(PFGS_TEXCOORD2, (void**)&ptexcs, &ptexinds);
            
            if(ptexcs)
            {
                if(ptexinds)
                {
                    int pcmin, pcmax;
                    gset->getAttrRange(PFGS_TEXCOORD2, &pcmin, &pcmax);
            
                    FINFO(("TI %d-%d ", pcmin, pcmax));

                    // Check indices
                    if(pcmax != pmax)   
                        FWARNING(("TexCoord pmax %d != pmax %d!\n", 
                                    pcmax, pmax));
                                    
                    for(int i = 0; i < pcmax; ++i)
                    {
                        if(pinds[i] != ptexinds[i])
                            FWARNING(("TexCoord Index %d (%d) != vind (%d)!\n",
                                i, ptexinds[i], pinds[i]));
                    }
                    
                    int ind = 0;
                    for(int j = 0; j < primcount; ++j)
                    {
                        Vec2f tc;
                        tc.setValues(ptexcs[0].vec[0], ptexcs[0].vec[1]);
                        for(UInt32 i = 0; i < cn_buffer; ++i)
                        {
                            otexc->getField().push_back(tc);
                        }

                        for(UInt32 i = 0; i < lenlist[j] - cn_buffer; 
                            ++i, ++ind)
                        {
                            Vec2f tc;
                            tc.setValues(ptexcs[ind].vec[0], 
                                         ptexcs[ind].vec[1]);
                            otexc->getField().push_back(tc);
                        }
                    }
                }
                else
                {
                    FINFO(("T "));
                    
                    int ind = 0;
                    for(int j = 0; j < primcount; ++j)
                    {
                        Vec2f tc;
                        tc.setValues(ptexcs[0].vec[0], ptexcs[0].vec[1]);
                        for(UInt32 i = 0; i < cn_buffer; ++i)
                        {
                            otexc->getField().push_back(tc);
                        }

                        for(UInt32 i = 0; i < lenlist[j] - cn_buffer; 
                            ++i, ++ind)
                        {
                            Vec2f tc;
                            tc.setValues(ptexcs[ind].vec[0], 
                                         ptexcs[ind].vec[1]);
                            otexc->getField().push_back(tc);
                        }
                    }
                }
            }    
            endEditCP(otexc);

            ogeo->setTexCoords(otexc);
        }
    }


    FINFO(("\n"));

    endEditCP(ogeo);
   
//FINFO(("PerformerLoader::Geo dump %p\n", gset));
//ogeo->dump();
     
    return ogeo;
}

GeometryPtr PerformerLoader::traverseGArray(NodePtr node, pfGeoArray *gset)
{
    FINFO(("PerformerLoader::traverseGArray: traversing %p\n", gset));
    
    return NullFC;
}

MaterialPtr PerformerLoader::traverseGState(NodePtr node, pfGeoState *gstate)
{
    FDEBUG(("PerformerLoader::traverseGState: traversing %p\n", gstate));
    
    if(_materials.find(gstate) != _materials.end())
    {
        FDEBUG(("PfL:traverseGState: found in matmap.\n"));    
        
        return _materials[gstate];
    }

    ChunkMaterialPtr mat = ChunkMaterial::create();
    beginEditCP(mat);
    
	uint64_t inherit;
	inherit = gstate->getInherit();
    
    static int pcolormode[] = { PFMTL_CMODE_AMBIENT_AND_DIFFUSE,
                                PFMTL_CMODE_AMBIENT,
                                PFMTL_CMODE_DIFFUSE,
                                PFMTL_CMODE_EMISSION,
                                PFMTL_CMODE_SPECULAR,
                                PFMTL_CMODE_OFF,
                                -1
                              };
    static int ocolormode[] = { GL_AMBIENT_AND_DIFFUSE,
                                GL_AMBIENT,
                                GL_DIFFUSE,
                                GL_EMISSION,
                                GL_SPECULAR,
                                GL_NONE
                              };

    pair<void *, void*> key;
    
    if((inherit & (PFSTATE_FRONTMTL | PFSTATE_BACKMTL)) != 
                  (PFSTATE_FRONTMTL | PFSTATE_BACKMTL)
      )
    {
        MaterialChunkPtr matc;
        
        key.first = NULL;
	    if (!(inherit & PFSTATE_FRONTMTL))
            key.first = gstate->getAttr(PFSTATE_FRONTMTL);

        key.second = NULL;
	    if (!(inherit & PFSTATE_BACKMTL))
            key.second = gstate->getAttr(PFSTATE_BACKMTL);

        if(_chunks.find(key) != _chunks.end())
        {    
            matc = MaterialChunkPtr::dcast(_chunks[key]);
        }
        else
        {
            matc = MaterialChunk::create();
            beginEditCP(matc);  

	        if (!(inherit & PFSTATE_FRONTMTL))
	        {
                pfMaterial *mat = (pfMaterial*)gstate->getAttr(PFSTATE_FRONTMTL);

                float r,g,b,a;
                a = mat->getAlpha();

                mat->getColor(PFMTL_AMBIENT, &r, &g, &b);        
                matc->setAmbient(Color4f(r,g,b,0));

                mat->getColor(PFMTL_DIFFUSE, &r, &g, &b);        
                matc->setDiffuse(Color4f(r,g,b,a));

                mat->getColor(PFMTL_SPECULAR, &r, &g, &b);        
                matc->setSpecular(Color4f(r,g,b,0));

                mat->getColor(PFMTL_EMISSION, &r, &g, &b);        
                matc->setEmission(Color4f(r,g,b,0));

                matc->setShininess(mat->getShininess());

                int cm = mat->getColorMode(PFMTL_FRONT);
                UInt32 om = GL_NONE;
                for (UInt16 i = 0; pcolormode[i] != -1; ++i)
                    if(pcolormode[i] == cm)
                        om = ocolormode[i];

                matc->setColorMaterial(om);
	        }

	        if (!(inherit & PFSTATE_BACKMTL))
	        {
                pfMaterial *mat = (pfMaterial*)gstate->getAttr(PFSTATE_BACKMTL);

                matc->setBackMaterial(true);
                float r,g,b,a;
                a = mat->getAlpha();

                mat->getColor(PFMTL_AMBIENT, &r, &g, &b);        
                matc->setBackAmbient(Color4f(r,g,b,0));

                mat->getColor(PFMTL_DIFFUSE, &r, &g, &b);        
                matc->setBackDiffuse(Color4f(r,g,b,a));

                mat->getColor(PFMTL_SPECULAR, &r, &g, &b);        
                matc->setBackSpecular(Color4f(r,g,b,0));

                mat->getColor(PFMTL_EMISSION, &r, &g, &b);        
                matc->setBackEmission(Color4f(r,g,b,0));

                matc->setBackShininess(mat->getShininess());

                int cm = mat->getColorMode(PFMTL_FRONT);
                UInt32 om = GL_NONE;
                for (UInt16 i = 0; pcolormode[i] != -1; ++i)
                    if(pcolormode[i] == cm)
                        om = ocolormode[i];

                matc->setBackColorMaterial(om);
	        }

            endEditCP(matc);
        }

        mat->addChunk(matc);
    }
    
    
    if((inherit & (PFSTATE_TEXTURE | PFSTATE_TEXENV)) !=
                  (PFSTATE_TEXTURE | PFSTATE_TEXENV)
      )
    {
        TextureChunkPtr texc;
        
        for(int t = 0; t < PF_MAX_TEXTURES; ++t)
        {
            if(gstate->getMultiAttr(PFSTATE_TEXTURE, t) == NULL)
                continue;
            
            key.first = NULL;
	        if (!(inherit & PFSTATE_TEXTURE) && 
                  gstate->getMultiAttr(PFSTATE_TEXTURE, t))
                key.first = gstate->getMultiAttr(PFSTATE_TEXTURE, t);

            key.second = NULL;
	        if (!(inherit & PFSTATE_TEXENV) && 
                  gstate->getMultiAttr(PFSTATE_TEXENV, t))
                key.second = gstate->getMultiAttr(PFSTATE_TEXENV, t);

            if(_chunks.find(key) != _chunks.end())
            {    
                texc = TextureChunkPtr::dcast(_chunks[key]);
            }
            else
            {
                texc = TextureChunk::create();
                beginEditCP(texc);  

	            if (!(inherit & PFSTATE_TEXTURE))
	            {
                    pfTexture *tex = 
                        (pfTexture*)gstate->getMultiAttr(PFSTATE_TEXTURE, t);
	            
                    unsigned int* pdata;
                    int pf, w, h, d, type, comp, sides;
                    UInt32 intformat = 0, extformat = 0;
                    
                    tex->getImage(&pdata, &comp, &w, &h, &d);                  

                    sides = tex->getFormat(PFTEX_CUBE_MAP) ? 6 : 1;
                    pf    = tex->getFormat(PFTEX_IMAGE_FORMAT);
                    
                    if(pf == 0x7fff)
                    {
                        switch(comp)
                        {
                        case 1: pf = Image::OSG_L_PF;      break;
                        case 2: pf = Image::OSG_LA_PF;     break;
                        case 3: pf = Image::OSG_RGB_PF;    break;
                        case 4: pf = Image::OSG_RGBA_PF;   break;
                        }
                    }
                    
                    switch(tex->getFormat(PFTEX_EXTERNAL_FORMAT))
                    {
                    case PFTEX_PACK_8:  type = Image::OSG_UINT8_IMAGEDATA;
                                        break;
                    case PFTEX_PACK_16: type = Image::OSG_UINT16_IMAGEDATA;
                                        break;
                    default:            
                        type = Image::OSG_UINT8_IMAGEDATA;
                        FWARNING(("PerformerLoader::traverseGState: "
                                  "Unknown tex format %d!\n",
                                   tex->getFormat(PFTEX_EXTERNAL_FORMAT)));
                        extformat = tex->getFormat(PFTEX_EXTERNAL_FORMAT);
                        break;
                    }
                    
                    intformat = tex->getFormat(PFTEX_INTERNAL_FORMAT);
                    
                    
                    ImagePtr img = Image::create();
                    beginEditCP(img);
                    
                    img->set(pf, w, h, d, 1, 1, 0, NULL, type, 1, sides);
                    
                    if(sides == 1)
                    {
                        memcpy(img->getData(), pdata, img->getSize());
                    }
                    else
                    {
                        FWARNING(("PerformerLoader::traverseGState: "
                                  "CubeTex not impl yet!\n"));
                    }
                    
                    endEditCP(img);
                    
                    texc->setImage(img);
                    
                    texc->setInternalFormat(intformat);
                    
                    texc->setWrapS(tex->getRepeat(PFTEX_WRAP_S));
                    texc->setWrapT(tex->getRepeat(PFTEX_WRAP_T));
                    texc->setWrapR(tex->getRepeat(PFTEX_WRAP_R));
 
                    static int ptexfilter[] = { PFTEX_POINT,
                                                PFTEX_LINEAR,
                                                PFTEX_BILINEAR,
                                                PFTEX_TRILINEAR,
                                                PFTEX_QUADLINEAR,
                                                PFTEX_MIPMAP_POINT,
                                                PFTEX_MIPMAP_LINEAR,
                                                PFTEX_MIPMAP_BILINEAR,
                                                PFTEX_MIPMAP_TRILINEAR,
                                                PFTEX_MIPMAP_QUADLINEAR,
                                                -1
                                              };
                    static int otexfilter[] = { GL_NEAREST,
                                                GL_LINEAR,
                                                GL_LINEAR,
                                                GL_LINEAR,
                                                GL_LINEAR,
                                                GL_NEAREST_MIPMAP_NEAREST,
                                                GL_NEAREST_MIPMAP_LINEAR,
                                                GL_LINEAR_MIPMAP_NEAREST,
                                                GL_LINEAR_MIPMAP_LINEAR,
                                                GL_LINEAR_MIPMAP_LINEAR
                                              };

                    int ptf = tex->getFilter(PFTEX_MINFILTER);
                    UInt32 otf = GL_NONE;
                    for (UInt16 i = 0; ptexfilter[i] != -1; ++i)
                        if(ptexfilter[i] == ptf)
                            otf = otexfilter[i];
                    texc->setMinFilter(otf);

                    ptf = tex->getFilter(PFTEX_MAGFILTER);
                    otf = GL_NONE;
                    for (UInt16 i = 0; ptexfilter[i] != -1; ++i)
                        if(ptexfilter[i] == ptf)
                            otf = otexfilter[i];
                    texc->setMagFilter(otf);
                }

	            if (!(inherit & PFSTATE_TEXENV))
	            {
                    pfTexEnv *te = 
                        (pfTexEnv*)gstate->getMultiAttr(PFSTATE_TEXENV, t);
	                
                    if(te != NULL)
                    {
                        texc->setEnvMode(te->getMode());

                        float r,g,b,a;
                        te->getBlendColor(&r,&g,&b,&a);

                        texc->setEnvColor(Color4f(r,g,b,a));
                    }
	            }

                endEditCP(texc);
            }

            mat->addChunk(texc);
        } // for t
    }
 
    /* Unhandled: lightmodel, lights, fog, texgen, texlod, vtxprog, fragprog,
                  gprogparms, colortable, highlight, lpointstate, shadprog
    */

    endEditCP(mat);
    
    _materials[gstate] = mat;
    
    return mat;
}



