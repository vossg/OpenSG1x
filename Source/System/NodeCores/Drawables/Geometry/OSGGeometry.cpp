/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include "OSGDrawable.h"
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

/*! \class osg::Geometry
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
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

    
const UInt16 Geometry::MapPosition       = 1;
const UInt16 Geometry::MapNormal         = Geometry::MapPosition << 1;
const UInt16 Geometry::MapColor          = Geometry::MapNormal << 1;
const UInt16 Geometry::MapSecondaryColor = Geometry::MapColor << 1;
const UInt16 Geometry::MapTexCoords      = Geometry::MapSecondaryColor << 1;
const UInt16 Geometry::MapTexCoords1     = Geometry::MapTexCoords << 1;
const UInt16 Geometry::MapTexCoords2     = Geometry::MapTexCoords1 << 1;
const UInt16 Geometry::MapTexCoords3     = Geometry::MapTexCoords2 << 1;
const UInt16 Geometry::MapEmpty          = Geometry::MapTexCoords3 << 1;


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
        endEditCP(_sfTypes.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTypes.getValue());
    }

    if(_sfLengths.getValue() != NullFC)
    {
        beginEditCP(_sfLengths.getValue(), Attachment::ParentsFieldMask);
        {
            _sfLengths.getValue()->subParent(thisP);
        }
        endEditCP(_sfLengths.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfLengths.getValue());
    }

    if(_sfPositions.getValue() != NullFC)
    {
        beginEditCP(_sfPositions.getValue(), Attachment::ParentsFieldMask);
        {
            _sfPositions.getValue()->subParent(thisP);
        }
        endEditCP(_sfPositions.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfPositions.getValue());
    }

    if(_sfNormals.getValue() != NullFC)
    {
        beginEditCP(_sfNormals.getValue(), Attachment::ParentsFieldMask);
        {
            _sfNormals.getValue()->subParent(thisP);
        }
        endEditCP(_sfNormals.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfNormals.getValue());
    }

    if(_sfColors.getValue() != NullFC)
    {
        beginEditCP(_sfColors.getValue(), Attachment::ParentsFieldMask);
        {
            _sfColors.getValue()->subParent(thisP);
        }
        endEditCP(_sfColors.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfColors.getValue());
    }

    if(_sfSecondaryColors.getValue() != NullFC)
    {
        beginEditCP(_sfSecondaryColors.getValue(), 
                        Attachment::ParentsFieldMask);
        {
            _sfSecondaryColors.getValue()->subParent(thisP);
        }
        endEditCP(_sfSecondaryColors.getValue(), 
                        Attachment::ParentsFieldMask);

        subRefCP(_sfSecondaryColors.getValue());
    }

    if(_sfTexCoords.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords.getValue());
    }

    if(_sfTexCoords1.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords1.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords1.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords1.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords1.getValue());
    }

    if(_sfTexCoords2.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords2.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords2.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords2.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords2.getValue());
    }

    if(_sfTexCoords3.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords3.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords3.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords3.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords3.getValue());
    }

    if(_sfIndices.getValue() != NullFC)
    {
        beginEditCP(_sfIndices.getValue(), Attachment::ParentsFieldMask);
        {
            _sfIndices.getValue()->subParent(thisP);
        }
        endEditCP(_sfIndices.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfIndices.getValue());
    }

    subRefCP(_sfMaterial.getValue());

    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

/** \brief instance initialization
 */

void Geometry::onCreate( const Geometry * )
{
    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

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
        return;                  // Node has no points, no volume

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
            SWARNING << "Geometry::handleGL: no Pump found for geometry " 
                     << this 
                     << std::endl;
        }
        
        glEndList();
    }
    else if ( mode == Window::destroy )
    {
        glDeleteLists( id, 1 );
    }
    else if ( mode == Window::finaldestroy )
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry(" << this << "::handleGL: Illegal mode: " 
             << mode << " for id " << id << std::endl;
    }
    
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Geometry::dump(      UInt32    uiIndent, 
                    const BitVector bvFlags) const
{
    UInt32 i;

    GeometryPtr thisP = getPtr();

    indentLog(uiIndent, PLOG);

    PLOG << "GeoCore" 
         << "("
         << thisP.getFieldContainerId()
         << ") : "
         << getType().getName()
         << " "
         << _attachmentMap.getValue().size()
         << " attachments | "
         << this
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    indentLog(uiIndent + 4, PLOG);
    PLOG << "Parents : " << std::endl;

    for(i = 0; i < _parents.size(); i++)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "           " << i << ") " << &(*(_parents[i])) << std::endl;
    }

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 4;

    if(getPositions() != NullFC)
    {
        getPositions()->dump(uiIndent, bvFlags);
    }

    if(getIndices() != NullFC)
    {
        getIndices()->dump(uiIndent, bvFlags);
    }

    if(getMaterial() != NullFC)
    {
        getMaterial()->dump(uiIndent, bvFlags);
    }

    if(getTypes() != NullFC)
    {
        getTypes()->dump(uiIndent, bvFlags);
    }

    if(getLengths() != NullFC)
    {
        getLengths()->dump(uiIndent, bvFlags);
    }

    if(getNormals() != NullFC)
    {
        getNormals()->dump(uiIndent, bvFlags);
    }

    if(getColors() != NullFC)
    {
        getColors()->dump(uiIndent, bvFlags);
    }

    if(getTexCoords() != NullFC)
    {
        getTexCoords()->dump(uiIndent, bvFlags);
    }

    if(getTexCoords1() != NullFC)
    {
        getTexCoords1()->dump(uiIndent, bvFlags);
    }

    if(getTexCoords2() != NullFC)
    {
        getTexCoords2()->dump(uiIndent, bvFlags);
    }

    if(getTexCoords3() != NullFC)
    {
        getTexCoords3()->dump(uiIndent, bvFlags);
    }

    uiIndent -= 4;

    AttachmentContainer::dump(uiIndent, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
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
        case MapTexCoords:
            pP = (getTexCoords() == NullFC) ? 0 : &(*getTexCoords());
            break;
        case MapTexCoords1:
            pP = (getTexCoords1() == NullFC) ? 0 : &(*getTexCoords1());
            break;
        case MapTexCoords2:
            pP = (getTexCoords2() == NullFC) ? 0 : &(*getTexCoords2());
            break;
        case MapTexCoords3:
            pP = (getTexCoords3() == NullFC) ? 0 : &(*getTexCoords3());
            break;
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
    UInt16 nmappings = getIndexMapping().size();
    Int16 i;

    for ( i = nmappings - 1; i >= 0; i-- )
      {
        if ( getIndexMapping()[i] & attrib  ) 
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
        if ( ( (        getNormals()            != NullFC ) ^
               ( other->getNormals()            != NullFC ) 
             ) ||
             ( (        getColors()             != NullFC ) ^
               ( other->getColors()             != NullFC ) 
             ) ||
             ( (        getSecondaryColors()    != NullFC ) ^
               ( other->getSecondaryColors()    != NullFC ) 
             ) ||
             ( (        getTexCoords()          != NullFC ) ^
               ( other->getTexCoords()          != NullFC ) 
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
        else  // multi-index
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
            
            if ( ( mind = calcMappingIndex( MapTexCoords ) ) >= 0 )
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
            SWARNING << "draw: no Pump found for geometry "
                     << this
                     << std::endl;
        }
    }
    
    StatCollector *coll = action->getStatistics();

    if(coll != NULL)
    {
        StatIntElem *el = coll->getElem(Drawable::statNTriangles,false);
        if(el)
        {
            GeometryPtr geo(this);
            UInt32 ntri,nl,np,is;
            
            calcPrimitiveCount(geo, ntri, nl, np);
            el->add(ntri);
            coll->getElem(Drawable::statNLines)->add(nl);
            coll->getElem(Drawable::statNLines)->add(np);
            
            if(getIndices() == NullFC)
            {
                if(getPositions() != NullFC)
                {
                    is = getPositions()->getSize();
                }
                else
                {
                    is = 0;
                }
            }
            else
            {
                is = getIndexMapping().size();
                is = getIndices()->getSize() / ( is ? is : 1 );
            }
            coll->getElem(Drawable::statNVertices)->add(is);
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
    // fprintf(stderr, "Geometry::render\n");

    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->dropGeometry(this);

    return Action::Continue;
}




/** \brief react to field changes
 */

void Geometry::changed(BitVector whichField, 
                       UInt32    origin    )
{
    if(whichField & TypesFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfTypes.getValue()                    != NullFC &&
                   _sfTypes.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoPTypesPtr pType = _sfTypes.getValue();
                    
                    _sfTypes.setValue(NullFC);
                    
                    setTypes(pType);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTypes.getValue());
            }
            else
            {
                GeoPTypesPtr pType = _sfTypes.getValue();
                
                _sfTypes.setValue(NullFC);
                
                setTypes(pType);
            }
        }
    }
    
    if(whichField & LengthsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfLengths.getValue()                    != NullFC &&
                   _sfLengths.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoPLengthsPtr pLength = _sfLengths.getValue();
                    
                    _sfLengths.setValue(NullFC);
                    
                    setLengths(pLength);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfLengths.getValue());
            }
            else
            {
                GeoPLengthsPtr pLength = _sfLengths.getValue();
                
                _sfLengths.setValue(NullFC);
                
                setLengths(pLength);
            }
        }
    }

    if(whichField & PositionsFieldMask)
    {
        for(UInt32 i = 0; i < _parents.size(); i++)
        {
            _parents[i]->invalidateVolume();
        }            

        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfPositions.getValue()                    != NullFC &&
                   _sfPositions.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoPositionsPtr pPos = _sfPositions.getValue();
                    
                    _sfPositions.setValue(NullFC);
                    
                    setPositions(pPos);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfPositions.getValue());
            }
            else
            {
                GeoPositionsPtr pPos = _sfPositions.getValue();
                
                _sfPositions.setValue(NullFC);
                
                setPositions(pPos);
            }
        }
        else
        {
        }
    }

    if(whichField & NormalsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfNormals.getValue()                    != NullFC &&
                   _sfNormals.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoNormalsPtr pNorm = _sfNormals.getValue();
                    
                    _sfNormals.setValue(NullFC);
                    
                    setNormals(pNorm);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfNormals.getValue());
            }
            else
            {
                GeoNormalsPtr pNorm = _sfNormals.getValue();
                
                _sfNormals.setValue(NullFC);
                
                setNormals(pNorm);
            }
        }
    }

    if(whichField & ColorsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfColors.getValue()                    != NullFC &&
                   _sfColors.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoColorsPtr pColor = _sfColors.getValue();
                    
                    _sfColors.setValue(NullFC);
                    
                    setColors(pColor);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfColors.getValue());
            }
            else
            {
                GeoColorsPtr pColor = _sfColors.getValue();
                
                _sfColors.setValue(NullFC);
                
                setColors(pColor);
            }
        }
    }

    if(whichField & TexCoordsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfTexCoords.getValue()                    != NullFC &&
                   _sfTexCoords.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords.getValue();
                    
                    _sfTexCoords.setValue(NullFC);
                    
                    setTexCoords(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords.getValue();
                
                _sfTexCoords.setValue(NullFC);
                
                setTexCoords(pTexCoord);
            }
        }
    }

    if(whichField & TexCoords1FieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfTexCoords1.getValue()                    != NullFC &&
                   _sfTexCoords1.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords1.getValue();
                    
                    _sfTexCoords1.setValue(NullFC);
                    
                    setTexCoords1(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords1.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords1.getValue();
                
                _sfTexCoords1.setValue(NullFC);
                
                setTexCoords1(pTexCoord);
            }
        }
    }

    if(whichField & TexCoords2FieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfTexCoords2.getValue()                    != NullFC &&
                   _sfTexCoords2.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords2.getValue();
                    
                    _sfTexCoords2.setValue(NullFC);
                    
                    setTexCoords2(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords2.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords2.getValue();
                
                _sfTexCoords2.setValue(NullFC);
                
                setTexCoords2(pTexCoord);
            }
        }
    }

    if(whichField & TexCoords3FieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfTexCoords3.getValue()                    != NullFC &&
                   _sfTexCoords3.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords3.getValue();
                    
                    _sfTexCoords3.setValue(NullFC);
                    
                    setTexCoords3(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords3.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords3.getValue();
                
                _sfTexCoords3.setValue(NullFC);
                
                setTexCoords3(pTexCoord);
            }
        }
    }

    if(whichField & IndicesFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();
                
                if(_sfIndices.getValue()                    != NullFC &&
                   _sfIndices.getValue()->findParent(thisP) ==     -1  )
                {
                    GeoIndicesPtr pIndex = _sfIndices.getValue();
                    
                    _sfIndices.setValue(NullFC);
                    
                    setIndices(pIndex);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfIndices.getValue());
            }
            else
            {
                GeoIndicesPtr pIndex = _sfIndices.getValue();
                
                _sfIndices.setValue(NullFC);
                
                setIndices(pIndex);
            }
        }
    }

    if(whichField & MaterialFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfMaterial.getValue());
            }
            else
            {
                MaterialPtr pMat = _sfMaterial.getValue();
                
                _sfMaterial.setValue(NullFC);
                
                setMaterial(pMat);
            }
        }
    }

    // invalidate the dlist cache
    if(getDlistCache())
    {
        if(getGLId() == 0)
        {
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
        
        Window::refreshGLObject(getGLId());
    }
    else 
    {
        if(getGLId() != 0)
            Window::destroyGLObject(getGLId(), 1);
        
        setGLId(0);
    }
    
    Inherited::changed(whichField, origin);
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
    
   //  create copies of the attributes

    beginEditCP(geo);
    {
        if(getTypes() != NullFC)
        {
            geo->setTypes(getTypes()->clone());
        }

        if(getLengths() != NullFC)
        {
            geo->setLengths(getLengths()->clone());
        }

        if(getPositions() != NullFC)
        {
            geo->setPositions(getPositions()->clone());
        }

        if(getNormals() != NullFC)
        {
            geo->setNormals(getNormals()->clone());
        }

        if(getColors() != NullFC)
        {
            geo->setColors(getColors()->clone());
        }

        if(getSecondaryColors() != NullFC)
        {
            geo->setSecondaryColors(getSecondaryColors()->clone());
        }

        if(getTexCoords() != NullFC)
        {
            geo->setTexCoords(getTexCoords()->clone());
        }

        if(getTexCoords1() != NullFC)
        {
            geo->setTexCoords1(getTexCoords1()->clone());
        }

        if(getTexCoords2() != NullFC)
        {
            geo->setTexCoords2(getTexCoords2()->clone());
        }

        if(getTexCoords3() != NullFC)
        {
            geo->setTexCoords3(getTexCoords3()->clone());
        }

        if(getIndices() != NullFC)
        {
            geo->setIndices(getIndices()->clone());
        }

        if(getMFIndexMapping() != NULL)
        {
            geo->getMFIndexMapping()->setValues(*getMFIndexMapping());
        }

        geo->setMaterial  (getMaterial  ());
        geo->setDlistCache(getDlistCache());
    }
    endEditCP  (geo);

    return geo;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

