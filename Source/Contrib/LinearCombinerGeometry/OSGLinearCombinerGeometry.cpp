/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGRenderAction.h>

#include "OSGLinearCombinerGeometry.h"

OSG_USING_NAMESPACE

/*! \class osg::LinearCombinerGeometry

*/

/*----------------------- constructors & destructors ----------------------*/

LinearCombinerGeometry::LinearCombinerGeometry(void) :
    Inherited()
{
}

LinearCombinerGeometry::LinearCombinerGeometry(const LinearCombinerGeometry &source) :
    Inherited(source)
{
}

LinearCombinerGeometry::~LinearCombinerGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LinearCombinerGeometry::initMethod (void)
{
    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          LinearCombinerGeometryPtr  ,
                                          CNodePtr     ,
                                          Action      *>(&LinearCombinerGeometry::render));
}

void LinearCombinerGeometry::changed(BitVector whichField, UInt32 origin)
{
    if((whichField & WeightsFieldMask) != 0)
    {
		if(getRecalconrender())
			recalculateGeometry();
		else
			setPositionsdirty(true);
    }
    if((whichField & SrcpositionsFieldMask) != 0)
    {
		recalculateBoundingVolumes();
		recalculateAllgeometry3f();
		if(getRecalconrender())
			recalculateGeometry();
		else
			setPositionsdirty(true);
    }
    Inherited::changed(whichField, origin);
}

void LinearCombinerGeometry::adjustVolume( Volume & volume )
{
	Pnt3f	vmin(0,0,0), vmax(0,0,0);
	    
    volume.setValid();
    volume.setEmpty();

    if ( getPositions() == NullFC )
        return;                  // Node has no points, no volume

    UInt32 nsrcvol = getSrcvolumes().size();
    for(int index=0; index < nsrcvol; index++)
	{
		Real32 weight = getWeights(index);
		if(weight < 0.0) 
		// swap min and max
		{
			vmin += getSrcvolumes(index).getMax().subZero() * weight;
			vmax += getSrcvolumes(index).getMin().subZero() * weight;
		}
		else
		// everything normal
		{
			vmax += getSrcvolumes(index).getMax().subZero() * weight;
			vmin += getSrcvolumes(index).getMin().subZero() * weight;
		}
	}
	
	volume.extendBy(vmin);
	volume.extendBy(vmax);
}

Action::ResultE LinearCombinerGeometry::render(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    if(getPositionsdirty())
    	recalculateGeometry();
    
    pAction->dropGeometry(this);

    return Action::Continue;
}

void LinearCombinerGeometry::recalculateAllgeometry3f() {
	MFGeoPositionsPtr::iterator posit, posend;
	GeoPositions3fPtr target;
	
	posit = getMFSrcpositions()->begin();
	posend = getMFSrcpositions()->end();
	
	// for all positions try to cast to GeoPositions3f
	for(;posit != posend; posit++)
	{
		target = GeoPositions3fPtr::dcast(*posit);
		if(target != NullFC) {
			setAllgeometries3f(false);
			return;
		}
	}
	setAllgeometries3f(true);
}

void LinearCombinerGeometry::recalculateBoundingVolumes()
{
	if(!getSrcvolumes().empty()) getSrcvolumes().clear();
	
	MFGeoPositionsPtr::iterator posit, posend;
	
	posit = getMFSrcpositions()->begin();
	posend = getMFSrcpositions()->end();
	
	// for all positions recalculate Dynamic Volume
	for(;posit != posend; posit++)
	{
		DynamicVolume vol;
		
		for(int index=0; index < (*posit)->getSize(); index++)
		{
			vol.extendBy( (*posit)->getValue(index) );
		}
		
		getSrcvolumes().push_back(vol);
	}
}

void LinearCombinerGeometry::recalculateGeometry()
{
	// check sanity
	if(getPositions() == NullFC) {
		SWARNING << "LinearCombinerGeometry: no geometry set" << std::endl;
		return;
	}
	if(getMFWeights()->size() != getMFSrcpositions()->size())
	{
		SWARNING << "LinearCombinerGeometry: weights.size() doesn't match srcpositions.size()" << std::endl;
		return;
	}
		
	std::vector<Real32> 			weights;

	if(getAllgeometries3f())
	{
		std::vector<GeoPositions3fPtr> 	positions;
		GeoPositions3fPtr				dstpositions = GeoPositions3fPtr::dcast(getPositions());
	
		// Collect all positions that have a weight != 0
		for(int index=0; index < getMFWeights()->size(); index++)
		{
			if(getWeights(index) != 0.0) {
				weights.push_back(getWeights(index));
				positions.push_back(GeoPositions3fPtr::dcast(getSrcpositions(index)));
			}
		}
		
		// interpolate all points
		beginEditCP(dstpositions);
		dstpositions->resize(positions[0]->getSize());
		for(int index=0; index < positions[0]->getSize(); index++)
		{
			std::vector<Real32>::iterator wit, wend;
			std::vector<GeoPositions3fPtr>::iterator pit;
			
			wit = weights.begin();
			wend = weights.end();
			pit = positions.begin();
			
			// from all sources with weight != 0
			Pnt3f p(0,0,0);
			for(;wit != wend; wit++)
			{
				p += (*pit)->getValue(index).subZero() * *wit;
				pit++;
			}
			// set point
			dstpositions->setValue(p, index);
		}
		endEditCP(dstpositions);
	}
	else
	{
		std::vector<GeoPositionsPtr> 	positions;
		GeoPositions3fPtr				dstpositions = GeoPositions3fPtr::dcast(getPositions());
	
		// Collect all positions that have a weight != 0
		for(int index=0; index < getMFWeights()->size(); index++)
		{
			if(getWeights(index) != 0.0) {
				weights.push_back(getWeights(index));
				positions.push_back(getSrcpositions(index));
			}
		}
		
		// interpolate all points
		beginEditCP(dstpositions);
		dstpositions->resize(positions[0]->getSize());
		for(int index=0; index < positions[0]->getSize(); index++)
		{
			std::vector<Real32>::iterator wit, wend;
			std::vector<GeoPositionsPtr>::iterator pit;
			
			wit = weights.begin();
			wend = weights.end();
			pit = positions.begin();
			
			// from all sources with weight != 0
			Pnt3f p(0,0,0);
			for(;wit != wend; wit++)
			{
				p += (*pit)->getValue(index).subZero() * *wit;
				pit++;
			}
			// set point
			dstpositions->setValue(p, index);
		}
		endEditCP(dstpositions);
	}
	
	setPositionsdirty(false);
}

void LinearCombinerGeometry::addGeometry( GeometryPtr source, Real32 weight)
{
	if(getPositions() == NullFC) {
		initWithGeometry(source);
		return;	
	}
	
    GeometryPtr destination = (GeometryPtr)this;
    
    // add positions to srcpositions
	beginEditCP(destination, LinearCombinerGeometry::WeightsFieldMask | LinearCombinerGeometry::SrcpositionsFieldMask);
		getMFWeights()->push_back(weight);
		getMFSrcpositions()->push_back(source->getPositions());
	endEditCP(destination, LinearCombinerGeometry::WeightsFieldMask | LinearCombinerGeometry::SrcpositionsFieldMask);
}

void LinearCombinerGeometry::initWithGeometry( GeometryPtr source)
{
	// Copy references to data from geometry and set srcpositions
    LinearCombinerGeometryPtr destination =
                                LinearCombinerGeometryPtr(this);

    beginEditCP(destination);
    {
	    destination->setNormals(source->getNormals());
	    destination->setTypes(source->getTypes());
	    destination->setLengths(source->getLengths());
	    destination->setPositions(GeoPositions3f::create());
	    destination->setColors(source->getColors());
	    destination->setSecondaryColors(source->getSecondaryColors());
	    destination->setTexCoords(source->getTexCoords());
	    destination->setTexCoords1(source->getTexCoords1());
	    destination->setTexCoords2(source->getTexCoords2());
	    destination->setTexCoords3(source->getTexCoords3());
	    destination->setIndices(source->getIndices());
	    destination->setMaterial(source->getMaterial());
	    destination->setDlistCache(source->getDlistCache());
	    destination->getMFIndexMapping()->setValues(*(source->getMFIndexMapping()));

	    // Set first source geometry
	    destination->getMFWeights()->push_back(1.0);
	    destination->getMFSrcpositions()->push_back(source->getPositions());
    }
    endEditCP(destination);

   	recalculateBoundingVolumes();
}

NodePtr OSG::createLinearCombinerStructure(NodePtr source)
{
	if(source == NullFC) return NullFC;
	
	NodePtr dest = Node::create();
	NodeCorePtr core = source->getCore();
	GeometryPtr geo = GeometryPtr::dcast(core);
	
	if(geo != NullFC) {
		LinearCombinerGeometryPtr lingeo = LinearCombinerGeometry::create();
		lingeo->initWithGeometry(geo);
		core = lingeo;	
	}
	
	beginEditCP(dest, Node::CoreFieldMask);
	{
		dest->setCore(core);
	}
	endEditCP(dest, Node::CoreFieldMask);
	
	// recurse
	for(int index=0; index < source->getNChildren(); index++)
	{
		NodePtr node = createLinearCombinerStructure(source->getChild(index));
		if(node != NullFC) 
		{
			beginEditCP(dest, Node::ChildrenFieldMask);	
			{
				dest->addChild(node);
			}
			endEditCP(dest, Node::ChildrenFieldMask);	
		}	
	}
		
	return dest;
}

void OSG::addToLinearCombinerStructure(NodePtr source, NodePtr dest)
{
	if(source == NullFC || dest == NullFC) return;
	
	GeometryPtr geo = GeometryPtr::dcast(source->getCore());
	LinearCombinerGeometryPtr lingeo = LinearCombinerGeometryPtr::dcast(dest->getCore());
	
	if(lingeo != NullFC) {
		if(geo == NullFC) {
			SWARNING << "addToLinearCombinerStructure: Tree structure of src and dest differs" << std::endl;
			return;
		}
		
		lingeo->addGeometry(geo);
	}
	
	// recurse
	if(source->getNChildren() != dest->getNChildren()) {
		SWARNING << "addToLinearCombinerStructure(): source and dest have different number of children" << std::endl;	
		return;
	}
	
	for(int index=0; index < source->getNChildren(); index++)
	{
		addToLinearCombinerStructure(source->getChild(index), dest->getChild(index));
	}
}

void OSG::getLinearCombinerCores(std::vector<LinearCombinerGeometryPtr> &cores, NodePtr node)
{
	LinearCombinerGeometryPtr lincore = LinearCombinerGeometryPtr::dcast(node->getCore());
	
	if(lincore != NullFC)
	{
		cores.push_back(lincore);
	}
	
	// recurse
	
	for(int index=0; index < node->getNChildren(); index++)
	{
		getLinearCombinerCores(cores, node->getChild(index));
	}
}

void LinearCombinerGeometry::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LinearCombinerGeometry NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.15 2002/10/25 13:09:36 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGLINEARCOMBINERGEOMETRYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLINEARCOMBINERGEOMETRYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLINEARCOMBINERGEOMETRYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

