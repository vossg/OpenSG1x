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

#include "OSGConfig.h"
#include <OSGGL.h>

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>
#include <OSGRenderAction.h>
#include <OSGMaterial.h>
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGGeoPumpFactory.h"

#include "OSGPrimitiveIterator.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"

#include "OSGGeoPropPtrs.h"
OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup GeometryLib OpenSG Geometry Lib
    \ingroup NodeCores

The basic polygonal geometry library.

*/

/*! \class osg::Geometry

The base class for all Geometry node types. Defines the common interface
for all geometry, so for general tools use these interfaces. They are pretty general
and minimal though, so don't expect them to be blindingly fast.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Geometry::cvsid[] = "@(#)$Id: $";

    
const UInt16 Geometry::MapPosition   = 1;
const UInt16 Geometry::MapNormal     = Geometry::MapPosition << 1;
const UInt16 Geometry::MapColor      = Geometry::MapNormal << 1;
const UInt16 Geometry::MapTexcoords  = Geometry::MapColor << 1;
const UInt16 Geometry::MapTexcoords2 = Geometry::MapTexcoords << 1;
const UInt16 Geometry::MapTexcoords3 = Geometry::MapTexcoords2 << 1;
const UInt16 Geometry::MapTexcoords4 = Geometry::MapTexcoords3 << 1;
const UInt16 Geometry::MapEmpty      = Geometry::MapTexcoords4 << 1;


StatElemDesc<StatIntElem>  Geometry::statNTriangles("NTriangles",
"number of rendered triangles");
StatElemDesc<StatIntElem>  Geometry::statNLines("NLines",
"number of rendered lines");
StatElemDesc<StatIntElem>  Geometry::statNPoints("NPoints",
"number of rendered points");
StatElemDesc<StatIntElem>  Geometry::statNVertices("NVertices",
"number of transformed vertices");


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

const char *Geometry::mapType( UInt8 type )
{
    switch ( type )
    {
    case GL_POINTS:         return "Points";
    case GL_LINES:          return "Lines";
    case GL_LINE_LOOP:      return "LineLoop";
    case GL_LINE_STRIP:     return "LineStrip";
    case GL_TRIANGLES:      return "Triangles";
    case GL_TRIANGLE_STRIP: return "TriangleStrip";
    case GL_TRIANGLE_FAN:   return "TriangleFan";
    case GL_QUADS:          return "Quads";
    case GL_QUAD_STRIP:     return "QuadStrip";
    case GL_POLYGON:        return "Polygon";
    }
    
    return "Unknown Primitive";
}
    
/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void Geometry::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GeometryPtr , 
                                          CNodePtr    ,
                                          Action     *>(&Geometry::doDraw));

    IntersectAction::registerEnterDefault( getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GeometryPtr ,  
                                          CNodePtr    , 
                                          Action     *>(&Geometry::intersect));

    RenderAction::registerEnterDefault( getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GeometryPtr  ,  
                                          CNodePtr     , 
                                          Action      *>(&Geometry::render));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Geometry::Geometry(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Geometry::Geometry(const Geometry &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Geometry::~Geometry(void)
{
    GeometryPtr thisP = getPtr();

    if(_sfTypes.getValue() != NullFC)
    {
        beginEditCP(_sfTypes.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTypes.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTypes.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTypes.getValue());
    }

    if(_sfLengths.getValue() != NullFC)
    {
        beginEditCP(_sfLengths.getValue(), Attachment::ParentsFieldMask);
        {
            _sfLengths.getValue()->subParent(thisP);
        }
        beginEditCP(_sfLengths.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfLengths.getValue());
    }

    if(_sfPositions.getValue() != NullFC)
    {
        beginEditCP(_sfPositions.getValue(), Attachment::ParentsFieldMask);
        {
            _sfPositions.getValue()->subParent(thisP);
        }
        beginEditCP(_sfPositions.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfPositions.getValue());
    }

    if(_sfNormals.getValue() != NullFC)
    {
        beginEditCP(_sfNormals.getValue(), Attachment::ParentsFieldMask);
        {
            _sfNormals.getValue()->subParent(thisP);
        }
        beginEditCP(_sfNormals.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfNormals.getValue());
    }

    if(_sfColors.getValue() != NullFC)
    {
        beginEditCP(_sfColors.getValue(), Attachment::ParentsFieldMask);
        {
            _sfColors.getValue()->subParent(thisP);
        }
        beginEditCP(_sfColors.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfColors.getValue());
    }

    if(_sfTexCoords.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords.getValue());
    }

    if(_sfIndices.getValue() != NullFC)
    {
        beginEditCP(_sfIndices.getValue(), Attachment::ParentsFieldMask);
        {
            _sfIndices.getValue()->subParent(thisP);
        }
        beginEditCP(_sfIndices.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfIndices.getValue());
    }

    subRefCP(_sfMaterial.getValue());
}

/** \brief instance initialization
 */

void Geometry::onCreate( const Geometry * )
{
    // !!! this temporary is needed to work around compiler problems (sgi)
    // CHECK CHECK
    //  TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
    GeometryPtr tmpPtr(*this);

    beginEditCP( tmpPtr, Geometry::GLIdFieldMask );

    setGLId(
        Window::registerGLObject( 
            osgTypedMethodVoidFunctor2ObjCPtrPtr<GeometryPtr, 
                                                 Window , 
                                                 UInt32>(tmpPtr, 
                                                         &Geometry::handleGL),
            1));

    endEditCP( tmpPtr, Geometry::GLIdFieldMask );
}

/*------------------------------ access -----------------------------------*/

void Geometry::adjustVolume( Volume & volume )
{
    GeoPositionsPtr pos = getPositions();
    
    volume.setValid();
    volume.setEmpty();

    if ( pos == NullFC )
        return;                 // Node has no points, no volume

    PrimitiveIterator it;

    for(it = this->beginPrimitives(); it != this->endPrimitives(); ++it)
    {
        for(UInt32 v=0; v < it.getLength(); ++v)
        {
            volume.extendBy(it.getPosition(v));
        }
    }
}

/*---------------------------- pointer ------------------------------------*/

GeometryPtr Geometry::getPtr(void) const
{
    return GeometryPtr(*this);
}


// GL object handler
// put the geometry into a display list
void Geometry::handleGL( Window* win, UInt32 idstatus )
{
    Window::GLObjectStatusE mode;
    UInt32 id;
   
    Window::unpackIdStatus(idstatus, id, mode);
    
    if ( mode == Window::initialize || mode == Window::needrefresh ||
         mode == Window::reinitialize )
    {       
        glNewList( id, GL_COMPILE );
        
        GeoPumpFactory::Index ind = GeoPumpFactory::the()->getIndex( this );
        GeoPumpFactory::GeoPump p = 
            GeoPumpFactory::the()->getGeoPump( win, ind );

        // call the pump

        if ( p )
            p( win, this );
        else
        {
            SWARNING << "Geometry::handleGL: no Pump found for geometry " << this << endl;
        }
        
        glEndList();
    }
    else if ( mode == Window::destroy )
    {
        glDeleteLists( id, 1 );
    }
    else if ( mode == Window::finaldestroy )
    {
        //SWARNING << "Last geometry user destroyed" << endl;
    }
    else
    {
        SWARNING << "Geometry(" << this << "::handleGL: Illegal mode: " 
             << mode << " for id " << id << endl;
    }
    
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Geometry::dump(      UInt32    uiIndent, 
                    const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE

/** \brief find the property pointer for the givem mapID
 */

AbstractGeoPropertyInterface *Geometry::getProperty(Int32 mapID)
{
    AbstractGeoPropertyInterface *pP = 0;
    
    switch (mapID) 
    {
        case 0:
            pP = 0;
            break;
        case MapPosition:
            pP = (getPositions() == NullFC) ? 0 : &(*getPositions());
            break;
        case MapNormal:
            pP = (getNormals() == NullFC) ? 0 : &(*getNormals());
            break;
        case MapColor:
            pP = (getColors() == NullFC) ? 0 : &(*getColors());
            break;
        case MapTexcoords:
            pP = (getTexCoords() == NullFC) ? 0 : &(*getTexCoords());
            break;
            // TODO; multitexture stuff
            /*
              case MapTexcoords2:
              pP = (getTexCoords2() == NullFC) ? 0 : &(*getTexCoords2());
              break;
              case MapTexcoords3:
              pP = (getTexCoords3() == NullFC) ? 0 : &(*getTexCoords3());
              break;
              case MapTexcoords4:
              pP = (getTexCoords4() == NullFC) ? 0 : &(*getTexCoords4());
              break;
            */
        default:
            FFATAL(("Invalid mapID (%d) in Geometry::getProperty()\n", 
                    mapID));
          break;
    }
    
    return pP;
}

#endif

/** \brief calc the indices into the index field for the given attributes
 */

Int16  Geometry::calcMappingIndex( UInt16 attrib ) const
{
    const UInt16 *mappings = &getIndexMapping().getValues()[0];
    UInt16 nmappings = getIndexMapping().size();
    
    int i;
    for ( i = nmappings-1; i >= 0; i-- )
    {
    if ( mappings[i] & attrib  ) 
        break;
    }   
    
    return i;
}

    

/** check if the geometry can be merged into this one, return true if yes 
  They need to have the same material and the same mappings or the same set of
  attributes.
*/
bool Geometry::isMergeable( const GeometryPtr other )
{
    if ( getMaterial()            != other->getMaterial()            ||
         getIndexMapping().size() != other->getIndexMapping().size()  )
        return false;
    
    UInt16 i;
    
    // this could be better if resorting was checked too. later.
    for ( i=0; i < getIndexMapping().size(); i++ )
        if ( getIndexMapping()[i] != other->getIndexMapping()[i] )
            return false;
    
    // if no index mapping, compare the existing properties
    if ( ! getIndexMapping().size() )
    {
        if ( ( (        getNormals()   != NullFC ) ^
               ( other->getNormals()   != NullFC ) 
             ) ||
             ( (        getColors()    != NullFC ) ^
               ( other->getColors()    != NullFC ) 
             ) ||
             ( (        getTexCoords() != NullFC ) ^
               ( other->getTexCoords() != NullFC ) 
           ) )
            return false;    
    }
    
    return true;
}

/** merge the geometry into this one, return true if successful */

bool Geometry::merge( const GeometryPtr other )
{
    if ( ! isMergeable( other ) )
        return false;
    
    // append the data
    UInt32 i;
    
    // Base indices for the new data
    UInt32 posBase, normalBase, colorBase, texcoordBase, indBase, typeBase,
           lengthBase;

    // this is generic, but not very efficient. 
    // specialize if you need more speed

#define copyAttrib( NAME, APTR, GETFUNC )               \
{                                                       \
    APTR NAME    =        GETFUNC();                    \
    APTR o##NAME = other->GETFUNC();                    \
                                                        \
    beginEditCP( NAME );                                \
    NAME##Base = NAME->getSize();                       \
    NAME->resize( NAME##Base + o##NAME->getSize() );    \
                                                        \
    for ( i = 0; i < o##NAME->getSize(); i++ )          \
        NAME->setValue( o##NAME->getValue( i ), NAME##Base + i );       \
                                                        \
    endEditCP( NAME );                                  \
}

    copyAttrib( pos, GeoPositionsPtr, getPositions );
    copyAttrib( type, GeoPTypesPtr, getTypes );
    copyAttrib( length, GeoPLengthsPtr, getLengths );
    
    // this is not perfect, I should test the index mapping if the property
    // is used at all and not blindly copy it. later.
    if ( getNormals() != NullFC )
        copyAttrib( normal, GeoNormalsPtr, getNormals );
    
    if ( getColors() != NullFC )
        copyAttrib( color, GeoColorsPtr, getColors );
    
    if ( getTexCoords() != NullFC )
        copyAttrib( texcoord, GeoTexCoordsPtr, getTexCoords );

#undef copyAttrib
    
    // now the fun part: indices
    
    // do we have indices? if not, we're done
    if ( getIndices() != NullFC )
    {
        // indices
        GeoIndicesPtr ind  =        getIndices();
        GeoIndicesPtr oind = other->getIndices();

        indBase = ind->getSize();
        ind->resize( indBase + oind->getSize() ); 

        beginEditCP( ind );
        
        // single index?
        if ( getIndexMapping().size() < 2 )
        {
            for ( i = 0; i < oind->getSize(); i++ )
                ind->setValue( oind->getValue(i) + posBase, indBase + i );          
        }
        else // multi-index
        {
            UInt32 * offsets = new UInt32 [ getIndexMapping().size() ];
            Int16 mind;
            UInt16 nmap = getIndexMapping().size();
            UInt16 j;
            
            // should do a sanity check if they're the same for everything
            // that's together, but logically they have to be, as they all 
            // use the same index
            
            if ( ( mind = calcMappingIndex( MapPosition ) ) >= 0 )
                offsets[ mind ] = posBase;
            
            if ( ( mind = calcMappingIndex( MapNormal ) ) >= 0 )
                offsets[ mind ] = normalBase;
            
            if ( ( mind = calcMappingIndex( MapColor ) ) >= 0 )
                offsets[ mind ] = colorBase;
            
            if ( ( mind = calcMappingIndex( MapTexcoords ) ) >= 0 )
                offsets[ mind ] = texcoordBase;
                
            // bump every index by its offset
            for ( i = 0, j = 0; i < oind->getSize(); 
                  i++, j = ( j + 1 ) % nmap )
            {
                ind->setValue(oind->getValue(i) + offsets[j], 
                              indBase + i );
            }

            delete [] offsets;
        }
        
        endEditCP( ind );
    }
    
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
Action::ResultE Geometry::doDraw(Action * action )
{
    DrawAction *a = dynamic_cast<DrawAction*>(action);

    if(a->getMaterial() != NULL)
    {
        a->getMaterial()->draw(this, a);
    }
    else if ( getMaterial() != NullFC )
    {
        getMaterial()->draw( this, a );
    }
    else
    {
        draw( a );
    }
    return Action::Continue;
}
    
Action::ResultE Geometry::draw(DrawActionBase * action)
{
    if ( getDlistCache() == true )
    {
        action->getWindow()->validateGLObject( getGLId() );
        glCallList( getGLId() );
    }
    else
    {
        GeoPumpFactory::Index ind = GeoPumpFactory::the()->getIndex( this );
        GeoPumpFactory::GeoPump p = 
            GeoPumpFactory::the()->getGeoPump( action->getWindow(), ind );

        // call the pump

        if ( p )
            p( action->getWindow(), this );
        else
        {
            SWARNING << "draw: no Pump found for geometry " << this << endl;
        }
    }
    
    StatCollector *coll = action->getStatistics();

    if(coll != NULL)
    {
        StatIntElem *el = coll->getElem(statNTriangles,false);
        if(el)
        {
            GeometryPtr geo(this);
            UInt32 ntri,nl,np,is;
            
            calcPrimitiveCount(geo, ntri, nl, np);
            el->add(ntri);
            coll->getElem(statNLines)->add(nl);
            coll->getElem(statNLines)->add(np);
            
            if(getIndices() == NullFC)
            {
                is = getPositions()->getSize();
            }
            else
            {
                is = getIndexMapping().size();
                is = getIndices()->getSize() / ( is ? is : 1 );
            }
            coll->getElem(statNVertices)->add(is);
        }
    }
    
    return Action::Continue;
}

Action::ResultE Geometry::intersect(Action * action )
{ 
    IntersectAction     * ia = dynamic_cast<IntersectAction*>(action);
    const DynamicVolume  &dv = ia->getActNode()->getVolume();
    
    if( dv.isValid() && !dv.intersect(ia->getLine()) )
    {
        return Action::Skip; //bv missed -> can not hit children
    }
    
    TriangleIterator it;
    Real32 t;
    Vec3f norm;
    
    for( it = this->beginTriangles(); it != this->endTriangles(); ++it )
    {
        if( ia->getLine().intersect( it.getPosition(0),
                                     it.getPosition(1),
                                     it.getPosition(2), t, &norm) )
        {
            ia->setHit( t, ia->getActNode(), it.getIndex(), norm );
        }
    }
    
    return Action::Continue;
}
        


Action::ResultE Geometry::render(Action *action)
{
//    fprintf(stderr, "Geometry::render\n");

    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->dropGeometry(this);

    return Action::Continue;
}



/** \brief react to field changes
 */

void Geometry::changed(BitVector whichField, ChangeMode OSG_CHECK_ARG(from))
{
    if(whichField & PositionsFieldMask)
    {
        for(UInt32 i = 0; i < _parents.size(); i++)
        {
            _parents[i]->invalidateVolume();
        }            
    }

    // invalidate the dlist cache
    if (getDlistCache())
        Window::refreshGLObject( getGLId() );
}

    
/** Triangle iterator functions */
    

TriangleIterator Geometry::beginTriangles( void ) const
{
    TriangleIterator it( this->getPtr() );

    it.setToBegin();
    
    return it;
}


TriangleIterator Geometry::endTriangles  ( void ) const
{
    TriangleIterator it( this->getPtr() );

    it.setToEnd();
    
    return it;
}
    
/** Primitive iterator functions */
    

PrimitiveIterator Geometry::beginPrimitives( void ) const
{
    PrimitiveIterator it( this->getPtr() );

    it.setToBegin();
    
    return it;
}


PrimitiveIterator Geometry::endPrimitives  ( void ) const
{
    PrimitiveIterator it( this->getPtr() );

    it.setToEnd();
    
    return it;
}
    
/** Face iterator functions */
    

FaceIterator Geometry::beginFaces( void ) const
{
    FaceIterator it( this->getPtr() );

    it.setToBegin();
    
    return it;
}


FaceIterator Geometry::endFaces  ( void ) const
{
    FaceIterator it( this->getPtr() );

    it.setToEnd();
    
    return it;
}


/** clone the geometry */

GeometryPtr Geometry::clone( void )
{
    GeometryPtr geo = Geometry::create();
//  FieldContainerFactory * fcf = FieldContainerFactory::the();
    
    // create copies of the attributes

    beginEditCP( geo );
    
    geo->setTypes    ( getTypes    ()->clone() );
    geo->setLengths  ( getLengths  ()->clone() );
    geo->setPositions( getPositions()->clone() );
    geo->setNormals  ( getNormals  ()->clone() );
    geo->setColors   ( getColors   ()->clone() );
    geo->setTexCoords( getTexCoords()->clone() );
    geo->setIndices  ( getIndices  ()->clone() );
    
    geo->getMFIndexMapping()->setValues( *getMFIndexMapping() );

    geo->setMaterial  ( getMaterial  () );
    geo->setDlistCache( getDlistCache() );
    
    return geo;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

