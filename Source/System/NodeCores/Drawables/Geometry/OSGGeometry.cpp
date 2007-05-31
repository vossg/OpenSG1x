/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                    *
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
#include <OSGChunkMaterial.h>
#include <OSGSimpleMaterial.h>
#include <OSGSimpleTexturedMaterial.h>
#include "OSGDrawable.h"
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGGeoPumpFactory.h"

#include <OSGIntersectActor.h>

#include "OSGPrimitiveIterator.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"
#include "OSGLineIterator.h"
#include "OSGEdgeIterator.h"

#include "OSGGeoPropPtrs.h"
OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Geometry
    \ingroup GrpSystemNodeCoresDrawablesGeometry

The base class for all Geometry node types, see \ref PageSystemGeometry for a
description.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt16 Geometry::MapPosition       = 1;
const UInt16 Geometry::MapNormal         = Geometry::MapPosition << 1;
const UInt16 Geometry::MapColor          = Geometry::MapNormal << 1;
const UInt16 Geometry::MapSecondaryColor = Geometry::MapColor << 1;
const UInt16 Geometry::MapTexCoords      = Geometry::MapSecondaryColor << 1;
const UInt16 Geometry::MapTexCoords1     = Geometry::MapTexCoords << 1;
const UInt16 Geometry::MapTexCoords2     = Geometry::MapTexCoords1 << 1;
const UInt16 Geometry::MapTexCoords3     = Geometry::MapTexCoords2 << 1;
const UInt16 Geometry::MapTexCoords4     = Geometry::MapTexCoords3 << 1;
const UInt16 Geometry::MapTexCoords5     = Geometry::MapTexCoords4 << 1;
const UInt16 Geometry::MapTexCoords6     = Geometry::MapTexCoords5 << 1;
const UInt16 Geometry::MapTexCoords7     = Geometry::MapTexCoords6 << 1;
const UInt16 Geometry::MapEmpty          = Geometry::MapTexCoords7 << 1;

std::vector<GeoVBO *> Geometry::_vbos;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! A little helper function to map the OpenGL primitive type to a name.
*/
const char *Geometry::mapType(UInt8 type)
{
    switch(type)
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
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void Geometry::initMethod(void)
{
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionHandler));

    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, GeometryPtr,
              CNodePtr, Action *>(&Geometry::intersect));

    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            GeometryPtr,
            NodeCorePtr,
            ActorBase::FunctorArgumentType &>(&Geometry::intersectActor),
        getClassType());

    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionHandler));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

Geometry::Geometry(void) :
    Inherited(),
    _numBytesOnGfxCard(0)
{
}

Geometry::Geometry(const Geometry &source) :
    Inherited(source),
    _numBytesOnGfxCard(source._numBytesOnGfxCard)
{
}

/*! The destructor automatically dereferences the used properties. If this
    Geometry was the last user that will automatically destroy them.
*/
Geometry::~Geometry(void)
{
}

void Geometry::onCreate(const Geometry *)
{
    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

    // !!! this temporary is needed to work around compiler problems(sgi)
    // CHECK CHECK

    //  TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
    if(Thread::getAspect() != _sfIgnoreGLForAspect.getValue())
    {
        GeometryPtr tmpPtr(*this);

        beginEditCP(tmpPtr, Geometry::GLIdFieldMask);

        setGLId(
            Window::registerGLObject(
                osgTypedMethodVoidFunctor2ObjCPtrPtr<GeometryPtr,
                                                     Window ,
                                                     UInt32>(tmpPtr,
                                                         &Geometry::handleGL),
                2));
        
        endEditCP(tmpPtr, Geometry::GLIdFieldMask);
    }
}

void Geometry::onDestroy(void)
{
    Inherited::onDestroy();

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

    if(_sfTexCoords4.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords4.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords4.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords4.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords4.getValue());
    }

    if(_sfTexCoords5.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords5.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords5.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords5.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords5.getValue());
    }

    if(_sfTexCoords6.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords6.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords6.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords6.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords6.getValue());
    }

    if(_sfTexCoords7.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords7.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords7.getValue()->subParent(thisP);
        }
        endEditCP(_sfTexCoords7.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords7.getValue());
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
    {
        Window::destroyGLObject(getGLId(), 2);
    }
}

/*------------------------------ access -----------------------------------*/

void Geometry::adjustVolume(Volume & volume)
{
    GeoPositionsPtr pos = getPositions();

    volume.setValid();
    volume.setEmpty();

    if(pos == NullFC)
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


/*! OpenGL object handler. Used for DisplayList caching.
*/
void Geometry::handleGL(Window* win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    UInt32 glid = 0;
    
    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        _numBytesOnGfxCard = getCachedGfxMemoryUsage();

        GeoPumpFactory::Index ind = GeoPumpFactory::the()->getIndex(this);
        // vbo is only supported for single index geometry (pump 129)
        bool vbo_supported = getVbo() && (ind == 129) && win->hasExtension(GeoPumpFactory::_arbVBO);
        bool created_vbo = false;
        if(mode == Window::initialize)
        {
            if(vbo_supported)
            {
                // reset the display list id.
                win->setGLObjectId(id, 0);
                // create the vbo objects.
                createVBO(win, id);
                created_vbo = true;
            }
            else
            {
                // create a display list.
                glid = glGenLists(1);
                win->setGLObjectId(id, glid);
                // reset the vbo id.
                win->setGLObjectId(id + 1, 0);
            }
        }

        glid = win->getGLObjectId(id);

        if(!vbo_supported)
        {
            // could be switched from vbo to display list rendering,
            // destroy old vbo
            destroyVBO(win, id);

            if(glid == 0)
            {
                // could be switched from vbo to display list rendering,
                // so we need to create a new display list!
                glid = glGenLists(1);
                win->setGLObjectId(id, glid);
            }

            glNewList(glid, GL_COMPILE);

            GeoPumpFactory::GeoPump p =
                GeoPumpFactory::the()->getGeoPump(win, ind);

            // call the pump
    
            if(p)
                p(win, this);
            else
            {
                SWARNING << "Geometry::handleGL: no Pump found for geometry "
                         << this
                         << std::endl;
            }
    
            glEndList();

            if(glGetError() == GL_OUT_OF_MEMORY)
            {
                SFATAL << "Geometry::handleGL: couldn't create display list (out of memory) skipping geometry "
                         << this
                         << std::endl;

                // destroy old list.
                glDeleteLists(glid, 1);
                win->setGLObjectId(id, 0);
            }
        }
        else
        {
            // could be switched from display list to vbo rendering,
            // destroy old display list.
            if(glid != 0)
            {
                glDeleteLists(glid, 1);
                // reset the display list id.
                win->setGLObjectId(id, 0);
            }
            if(!created_vbo)
            {
                updateVBO(win, id);
            }
        }
    }
    else if(mode == Window::destroy)
    {
        // delete vbo's and display lists.
        destroyVBO(win, id);

        glid = win->getGLObjectId(id);
        if(glid != 0)
        {
            glDeleteLists(glid, 1);
            // reset the display list id.
            win->setGLObjectId(id, 0);
        }
    }
    else if(mode == Window::finaldestroy)
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

    if(getTexCoords4() != NullFC)
    {
        getTexCoords4()->dump(uiIndent, bvFlags);
    }

    if(getTexCoords5() != NullFC)
    {
        getTexCoords5()->dump(uiIndent, bvFlags);
    }

    if(getTexCoords6() != NullFC)
    {
        getTexCoords6()->dump(uiIndent, bvFlags);
    }

    if(getTexCoords7() != NullFC)
    {
        getTexCoords7()->dump(uiIndent, bvFlags);
    }

    uiIndent -= 4;

    AttachmentContainer::dump(uiIndent, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE

/*! Find the property pointer for the given mapID, i.e.
osg::Geometry::MapPosition and relatives.
*/
GeoPropertyArrayInterface *Geometry::getProperty(Int32 mapID)
{
    GeoPropertyArrayInterface *pP = 0;

    switch(mapID)
    {
        case 0:
            pP = 0;
            break;
        case MapPosition:
            pP =(getPositions()       == NullFC) ? 0 : &(*getPositions());
            break;
        case MapNormal:
            pP =(getNormals()         == NullFC) ? 0 : &(*getNormals());
            break;
        case MapColor:
            pP =(getColors()          == NullFC) ? 0 : &(*getColors());
            break;
        case MapSecondaryColor:
            pP =(getSecondaryColors() == NullFC) ? 0 : &(*getSecondaryColors());
            break;
        case MapTexCoords:
            pP =(getTexCoords()       == NullFC) ? 0 : &(*getTexCoords());
            break;
        case MapTexCoords1:
            pP =(getTexCoords1()      == NullFC) ? 0 : &(*getTexCoords1());
            break;
        case MapTexCoords2:
            pP =(getTexCoords2()      == NullFC) ? 0 : &(*getTexCoords2());
            break;
        case MapTexCoords3:
            pP =(getTexCoords3()      == NullFC) ? 0 : &(*getTexCoords3());
            break;
        case MapTexCoords4:
            pP =(getTexCoords4()      == NullFC) ? 0 : &(*getTexCoords4());
            break;
        case MapTexCoords5:
            pP =(getTexCoords5()      == NullFC) ? 0 : &(*getTexCoords5());
            break;
        case MapTexCoords6:
            pP =(getTexCoords6()      == NullFC) ? 0 : &(*getTexCoords6());
            break;
        case MapTexCoords7:
            pP =(getTexCoords7()      == NullFC) ? 0 : &(*getTexCoords7());
            break;
        default:
            FFATAL(("Invalid mapID(%d) in Geometry::getProperty()\n",
                    mapID));
          break;
    }

    return pP;
}

#endif

/*! Calc the indices into the index field for the given attributes. This is the
    index of the given attribute's index in a multi-index block.

    Returns -1 for non- or single-indexed geometries, or if the given attribute
    is not used.
*/
Int16  Geometry::calcMappingIndex(UInt16 attrib) const
{
    UInt16 nmappings = getIndexMapping().size();
    Int16 i;

    for(i = nmappings - 1; i >= 0; i--)
    {
        if(getIndexMapping()[i] & attrib )
            break;
    }

    return i;
}



/*! Check if the geometry can be merged into this one, return true if yes
They need to have the same material and the same mappings or the same set of
attributes.
*/
bool Geometry::isMergeable( const GeometryPtr other )
{
    if (MergeIndex(other)!=-1 || getPositions()==NullFC) return true;
    else return false;
}

/*! Merge the geometry into this one, return true if successful.
*/
bool Geometry::merge( const GeometryPtr other )
{
    if (other == NullFC)
    {
        FDEBUG(("Geometry::merge: other = NullFC!!!\n"));
        return false;
    }
    //first check whethet the current geometry is empty
    //if empty just add everything from the other geometry
    if (getPositions()==NullFC)
    {
        if (other->getPositions()!=NullFC)
            setPositions(other->getPositions()->clone());

        if (other->getTypes()!=NullFC)
            setTypes(other->getTypes()->clone());

        if (other->getLengths()!=NullFC)
            setLengths(other->getLengths()->clone());

        if (other->getNormals()!=NullFC)
            setNormals(other->getNormals()->clone());

        if (other->getColors()!=NullFC)
            setColors(other->getColors()->clone());

        if (other->getSecondaryColors()!=NullFC)
            setSecondaryColors(other->getSecondaryColors()->clone());

        if (other->getTexCoords()!=NullFC)
            setTexCoords(other->getTexCoords()->clone());

        if (other->getTexCoords1()!=NullFC)
            setTexCoords1(other->getTexCoords1()->clone());

        if (other->getTexCoords2()!=NullFC)
            setTexCoords2(other->getTexCoords2()->clone());

        if (other->getTexCoords3()!=NullFC)
            setTexCoords3(other->getTexCoords3()->clone());

        if (other->getTexCoords4()!=NullFC)
            setTexCoords4(other->getTexCoords4()->clone());

        if (other->getTexCoords5()!=NullFC)
            setTexCoords5(other->getTexCoords5()->clone());

        if (other->getTexCoords6()!=NullFC)
            setTexCoords6(other->getTexCoords6()->clone());

        if (other->getTexCoords7()!=NullFC)
            setTexCoords7(other->getTexCoords7()->clone());

        if(other->getIndices()!=NullFC)
            setIndices(other->getIndices()->clone());

        if(other->getMFIndexMapping()!=NULL)
            getMFIndexMapping()->setValues(*(other->getMFIndexMapping()));

        setMaterial(other->getMaterial());
        setDlistCache(other->getDlistCache());

        return true;
    }


    //if not empty continue trying a normal merge
    Int16 mergetype = MergeIndex( other );

    if(mergetype >= 0 && mergetype <= 6)
    {
        // in this case we create 32 bit indices to have enough room for both geometries.
        if(GeoIndicesUI16Ptr::dcast(getIndices()) != NullFC)
        {
            GeoIndicesPtr indices = getIndices();
            UInt32 indices_size = indices->getSize();
            GeoIndicesUI32Ptr indicesUI32 = GeoIndicesUI32::create();
            MFUInt32 &dst = indicesUI32->getField();
            dst.reserve(indices_size);
            beginEditCP(indicesUI32);
                for (UInt32 i = 0; i < indices_size; ++i)
                    dst.push_back(indices->getValue(i));
            endEditCP(indicesUI32);
    
            beginEditCP((GeometryPtr)this, Geometry::IndicesFieldMask);
                setIndices(indicesUI32);
            endEditCP((GeometryPtr)this, Geometry::IndicesFieldMask);
        }
    }

    switch ( mergetype )
    {
    case 0: merge0( other ); break;
    case 1: merge1( other ); break;
    case 2: merge2( other ); break;
    case 3: merge3( other ); break;
    case 4: merge4( other ); break;
    case 5: merge5( other ); break;
    case 6: merge6( other ); break;
    default: return false;
    }
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Action::ResultE Geometry::drawPrimitives(DrawActionBase * action)
{
    // store glColor.
    Color4f color;
    if(getColors() != NullFC)
        glPushAttrib(GL_CURRENT_BIT);

    bool vbo_supported = false;
    if(getVbo())
    {
        vbo_supported = drawVBO(action->getWindow(), getGLId());
    }

    if(!vbo_supported)
    {
        if(getDlistCache() == true)
        {
            action->getWindow()->validateGLObject(getGLId());
            UInt32 glid = action->getWindow()->getGLObjectId(getGLId());
            if(glid != 0)
                glCallList(glid);
        }
        else
        {
            GeoPumpFactory::Index ind = GeoPumpFactory::the()->getIndex(this);
            GeoPumpFactory::GeoPump p =
                GeoPumpFactory::the()->getGeoPump(action->getWindow(), ind);
    
            // call the pump
    
            if(p)
                p(action->getWindow(), this);
            else
            {
                SWARNING << "draw: no Pump found for geometry "
                         << this
                         << std::endl;
            }
        }
    }

    // restore glColor.
    if(getColors() != NullFC)
        glPopAttrib();

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
                is = getIndices()->getSize() /(is ? is : 1);
            }
            coll->getElem(Drawable::statNVertices)->add(is);

            UInt32 primitiveCount = 0;
            if (getTypes() != NullFC) {
                primitiveCount = getTypes()->getSize();
            }
            coll->getElem(Drawable::statNPrimitives)->add(primitiveCount);
        }

        // check amount of memory on gfx card
        // count only primitives residing on the gfxcard
        if (vbo_supported || getDlistCache())
        {
            StatIntOnceElem *el = coll->getElem(Drawable::statNGeoBytes, false);
            if (el)
                coll->getElem(Drawable::statNGeoBytes)->add(getGLId(), _numBytesOnGfxCard);
        }
    }

    return Action::Continue;
}

UInt32 Geometry::getCachedGfxMemoryUsage(void)
{
    int nBytes = 0;

    // Lengths are int32 (4 Bbytes) or int16 (2 Bytes)
    if (getLengths() != NullFC)
    {
        if (GeoPLengthsUI32Ptr::dcast(getLengths()) != NullFC)
            nBytes += getLengths()->getSize()*4;
        else
            nBytes += getLengths()->getSize()*2;
    }

    // Indices are int32 (4 Bbytes) or int16 (2 Bytes)
    if (getIndices() != NullFC)
    {
        if (GeoIndicesUI32Ptr::dcast(getIndices()) != NullFC)
            nBytes += getIndices()->getSize()*4;
        else
            nBytes += getIndices()->getSize()*2;
    }

    // Positions are vec3f = 3 * 4 Bytes
    if (getPositions() != NullFC)
        nBytes += getPositions()->getSize()*12;

    // Normals are vec3f (3*4 Bytes) or vec3b(3*1 Byte)
    if (getNormals() != NullFC)
    {
        if (GeoNormals3fPtr::dcast(getNormals()) != NullFC)
            nBytes += getNormals()->getSize()*12;
        else
            nBytes += getNormals()->getSize()*3;
    }

    // Colors are vec4f = 4 * 4 Bytes
    if (getColors() != NullFC)
        nBytes += getColors()->getSize()*16;

    // SecondaryColors are vec4f = 4 * 4 Bytes
    if (getSecondaryColors() != NullFC)
        nBytes += getSecondaryColors()->getSize()*16;

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords()) != NullFC)
            nBytes += getTexCoords()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords()) != NullFC)
            nBytes += getTexCoords()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords()) != NullFC)
            nBytes += getTexCoords()->getSize()*8;
    }

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords1() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords1()) != NullFC)
            nBytes += getTexCoords1()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords1()) != NullFC)
            nBytes += getTexCoords1()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords1()) != NullFC)
            nBytes += getTexCoords1()->getSize()*8;
    }

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords2() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords2()) != NullFC)
            nBytes += getTexCoords2()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords2()) != NullFC)
            nBytes += getTexCoords2()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords2()) != NullFC)
            nBytes += getTexCoords2()->getSize()*8;
    }

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords3() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords3()) != NullFC)
            nBytes += getTexCoords3()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords3()) != NullFC)
            nBytes += getTexCoords3()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords3()) != NullFC)
            nBytes += getTexCoords3()->getSize()*8;
    }

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords4() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords4()) != NullFC)
            nBytes += getTexCoords4()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords4()) != NullFC)
            nBytes += getTexCoords4()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords4()) != NullFC)
            nBytes += getTexCoords4()->getSize()*8;
    }

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords5() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords5()) != NullFC)
            nBytes += getTexCoords5()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords5()) != NullFC)
            nBytes += getTexCoords5()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords5()) != NullFC)
            nBytes += getTexCoords5()->getSize()*8;
    }

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords6() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords6()) != NullFC)
            nBytes += getTexCoords6()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords6()) != NullFC)
            nBytes += getTexCoords6()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords6()) != NullFC)
            nBytes += getTexCoords6()->getSize()*8;
    }

    // TexCoords are vec4f (4*4 Bytes) or vec3f(3*4 Bytes) or vec2f (2*4 Bytes)
    if (getTexCoords7() != NullFC)
    {
        if (GeoTexCoords4fPtr::dcast(getTexCoords7()) != NullFC)
            nBytes += getTexCoords7()->getSize()*16;
        else if (GeoTexCoords3fPtr::dcast(getTexCoords7()) != NullFC)
            nBytes += getTexCoords7()->getSize()*12;
        else if (GeoTexCoords2fPtr::dcast(getTexCoords7()) != NullFC)
            nBytes += getTexCoords7()->getSize()*8;
    }
    
    return nBytes;
}

Action::ResultE Geometry::intersect(Action * action)
{
    IntersectAction     * ia = dynamic_cast<IntersectAction*>(action);
    const DynamicVolume  &dv = ia->getActNode()->getVolume(true);

    if(dv.isValid() && !dv.intersect(ia->getLine()))
    {
        return Action::Skip; //bv missed -> can not hit children
    }

    TriangleIterator it  = this->beginTriangles();
    TriangleIterator end = this->endTriangles  ();
    Real32 t;
    Vec3f norm;

    for(; it != end; ++it)
    {
        if(ia->getLine().intersect(it.getPosition(0),
                                     it.getPosition(1),
                                     it.getPosition(2), t, &norm))
        {
            ia->setHit(t, ia->getActNode(), it.getIndex(), norm);
        }
    }

    return Action::Continue;
}

NewActionTypes::ResultE
Geometry::intersectActor(ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor   *pIA         = dynamic_cast<IntersectActor *>(funcArg.getActor());
    Real32            scaleFactor = pIA->getScaleFactor();

    TriangleIterator  itTris      = this->beginTriangles();
    TriangleIterator  endTris     = this->endTriangles  ();

    Real32            hitDist;
    Vec3f             hitNormal;

    for(; itTris != endTris; ++itTris)
    {
        if(pIA->getRay().intersect(itTris.getPosition(0),
                                   itTris.getPosition(1),
                                   itTris.getPosition(2),
                                   hitDist,                &hitNormal) == true)
        {
            pIA->setHit(hitDist * scaleFactor, funcArg.getNode(),
                        itTris.getIndex(),     hitNormal        );
        }
    }

    pIA->setupChildrenPriorities();

    return NewActionTypes::Continue;
}

/*! React to field changes, take care of incrementing/decrementing the
    reference count of the changed properties.
*/
void Geometry::changed(BitVector whichField,
                       UInt32    origin   )
{
    if(whichField & TypesFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();

                if(_sfTypes.getValue()                    != NullFC &&
                   _sfTypes.getValue()->findParent(thisP) ==     -1 )
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
                   _sfLengths.getValue()->findParent(thisP) ==     -1 )
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
                   _sfPositions.getValue()->findParent(thisP) ==     -1 )
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
                   _sfNormals.getValue()->findParent(thisP) ==     -1 )
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
                   _sfColors.getValue()->findParent(thisP) ==     -1 )
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

    if(whichField & SecondaryColorsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();

                if(_sfSecondaryColors.getValue()                   != NullFC &&
                   _sfSecondaryColors.getValue()->findParent(thisP)==     -1 )
                {
                    GeoColorsPtr pColor = _sfSecondaryColors.getValue();

                    _sfSecondaryColors.setValue(NullFC);

                    setSecondaryColors(pColor);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfSecondaryColors.getValue());
            }
            else
            {
                GeoColorsPtr pColor = _sfSecondaryColors.getValue();

                _sfSecondaryColors.setValue(NullFC);

                setSecondaryColors(pColor);
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
                   _sfTexCoords.getValue()->findParent(thisP) ==     -1 )
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
                   _sfTexCoords1.getValue()->findParent(thisP) ==     -1 )
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
                   _sfTexCoords2.getValue()->findParent(thisP) ==     -1 )
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
                   _sfTexCoords3.getValue()->findParent(thisP) ==     -1 )
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

    if(whichField & TexCoords4FieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();

                if(_sfTexCoords4.getValue()                    != NullFC &&
                   _sfTexCoords4.getValue()->findParent(thisP) ==     -1 )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords4.getValue();

                    _sfTexCoords4.setValue(NullFC);

                    setTexCoords4(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords4.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords4.getValue();

                _sfTexCoords4.setValue(NullFC);

                setTexCoords4(pTexCoord);
            }
        }
    }

    if(whichField & TexCoords5FieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();

                if(_sfTexCoords5.getValue()                    != NullFC &&
                   _sfTexCoords5.getValue()->findParent(thisP) ==     -1 )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords5.getValue();

                    _sfTexCoords5.setValue(NullFC);

                    setTexCoords5(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords5.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords5.getValue();

                _sfTexCoords5.setValue(NullFC);

                setTexCoords5(pTexCoord);
            }
        }
    }

    if(whichField & TexCoords6FieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();

                if(_sfTexCoords6.getValue()                    != NullFC &&
                   _sfTexCoords6.getValue()->findParent(thisP) ==     -1 )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords6.getValue();

                    _sfTexCoords6.setValue(NullFC);

                    setTexCoords6(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords6.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords6.getValue();

                _sfTexCoords6.setValue(NullFC);

                setTexCoords6(pTexCoord);
            }
        }
    }

    if(whichField & TexCoords7FieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                GeometryPtr thisP = getPtr();

                if(_sfTexCoords7.getValue()                    != NullFC &&
                   _sfTexCoords7.getValue()->findParent(thisP) ==     -1 )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTexCoords7.getValue();

                    _sfTexCoords7.setValue(NullFC);

                    setTexCoords7(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTexCoords7.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTexCoords7.getValue();

                _sfTexCoords7.setValue(NullFC);

                setTexCoords7(pTexCoord);
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
                   _sfIndices.getValue()->findParent(thisP) ==     -1 )
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

    if(whichField & (IndicesFieldMask | LengthsFieldMask | 
                     TypesFieldMask   | IndexMappingFieldMask)
      )
    {
        updateLowHighIndices();
    }

#if 1

    if(Thread::getAspect() != _sfIgnoreGLForAspect.getValue())
    {
    // invalidate the dlist cache
        if(getDlistCache() || getVbo())
        {
            if(getGLId() == 0)
            {
                GeometryPtr tmpPtr(*this);
                
                beginEditCP(tmpPtr, Geometry::GLIdFieldMask);
                
                setGLId(
                    Window::registerGLObject(
                        osgTypedMethodVoidFunctor2ObjCPtrPtr<
                                GeometryPtr,
                                Window ,
                                UInt32>(tmpPtr,
                                        &Geometry::handleGL),
                        2));

                endEditCP(tmpPtr, Geometry::GLIdFieldMask);
            }

            // speed improvement don't recreate the display list
            // for a material change.
            if(whichField != MaterialFieldMask)
                Window::refreshGLObject(getGLId());
        }
        else
        {
            if(getGLId() != 0)
                Window::destroyGLObject(getGLId(), 2);
            
            setGLId(0);
        }
    }
#endif

    Inherited::changed(whichField, origin);
}

/*--------------------------- Triangle Iterator --------------------------------*/

/*! Return a TriangleIterator poiting to the beginning of the Geometry.
*/
TriangleIterator Geometry::beginTriangles(void) const
{
    TriangleIterator it(this->getPtr());

    it.setToBegin();

    return it;
}

/*! Return a TriangleIterator poiting to the end of the Geometry.
*/
TriangleIterator Geometry::endTriangles(void) const
{
    TriangleIterator it(this->getPtr());

    it.setToEnd();

    return it;
}

/*-------------------------- Primitive Iterator --------------------------------*/

/*! Return a PrimitiveIterator poiting to the beginning of the Geometry.
*/
PrimitiveIterator Geometry::beginPrimitives(void) const
{
    PrimitiveIterator it(this->getPtr());

    it.setToBegin();

    return it;
}

/*! Return a PrimitiveIterator poiting to the end of the Geometry.
*/
PrimitiveIterator Geometry::endPrimitives(void) const
{
    PrimitiveIterator it(this->getPtr());

    it.setToEnd();

    return it;
}

/*---------------------------- Face Iterator ---------------------------------*/

/*! Return a FaceIterator poiting to the beginning of the Geometry.
*/
FaceIterator Geometry::beginFaces(void) const
{
    FaceIterator it(this->getPtr());

    it.setToBegin();

    return it;
}

/*! Return a FaceIterator poiting to the end of the Geometry.
*/
FaceIterator Geometry::endFaces(void) const
{
    FaceIterator it(this->getPtr());

    it.setToEnd();

    return it;
}

/*---------------------------- Line Iterator ---------------------------------*/

/*! Return a LineIterator poiting to the beginning of the Geometry.
*/
LineIterator Geometry::beginLines(void) const
{
    LineIterator it(this->getPtr());

    it.setToBegin();
    
    return it;
}

/*! Return a LineIterator poiting to the end of the Geometry.
*/
LineIterator Geometry::endLines(void) const
{
    LineIterator it(this->getPtr());

    it.setToEnd();
    
    return it;
}

/*---------------------------- Edge Iterator ---------------------------------*/

/*! Return a EdgeIterator poiting to the beginning of the Geometry.
*/
EdgeIterator Geometry::beginEdges(void) const
{
    EdgeIterator it(this->getPtr());

    it.setToBegin();
    
    return it;
}

/*! Return a EdgeIterator poiting to the end of the Geometry.
*/
EdgeIterator Geometry::endEdges(void) const
{
    EdgeIterator it(this->getPtr());

    it.setToEnd();
    
    return it;
}


/*! Clone the geometry, i.e. create a new Geometry that uses all the same
    properties the given one uses.
*/

GeometryPtr Geometry::clone(void)
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

        if(getTexCoords4() != NullFC)
        {
            geo->setTexCoords4(getTexCoords4()->clone());
        }

        if(getTexCoords5() != NullFC)
        {
            geo->setTexCoords5(getTexCoords5()->clone());
        }

        if(getTexCoords6() != NullFC)
        {
            geo->setTexCoords6(getTexCoords6()->clone());
        }

        if(getTexCoords7() != NullFC)
        {
            geo->setTexCoords7(getTexCoords7()->clone());
        }

        if(getIndices() != NullFC)
        {
            geo->setIndices(getIndices()->clone());
        }

        if(getMFIndexMapping() != NULL)
        {
            geo->getMFIndexMapping()->setValues(*getMFIndexMapping());
        }

        geo->setMaterial(getMaterial());
        geo->setDlistCache(getDlistCache());
    }
    endEditCP(geo);

    return geo;
}

bool Geometry::CompareMaterials(MaterialPtr m1, MaterialPtr m2)
{
    if(m1 == m2)
        return true;
        
    ChunkMaterialPtr cm1=ChunkMaterialPtr::dcast(m1);
    ChunkMaterialPtr cm2=ChunkMaterialPtr::dcast(m2);

    if (cm1==NullFC || cm2==NullFC) return false;

    MFStateChunkPtr &chunks1=cm1->getChunks();
    MFStateChunkPtr &chunks2=cm2->getChunks();

    if (chunks1.size()!=chunks2.size()) return false;

    MFStateChunkPtr::iterator matIt  = chunks1.begin();
    MFStateChunkPtr::iterator matEnd = chunks1.end ();

    MFStateChunkPtr::iterator i;

    while (matIt!=matEnd)
    {
        i = chunks2.find(*matIt);

        if (i == chunks2.end()) return false;

        ++matIt;
    }

    if(cm1->getState() == NullFC)
        cm1->rebuildState();
    if(cm2->getState() == NullFC)
        cm2->rebuildState();
    
    MFStateChunkPtr &statechunks1=cm1->getState()->getChunks();
    MFStateChunkPtr &statechunks2=cm2->getState()->getChunks();

    if (statechunks1.size()!=statechunks2.size()) return false;

    matIt  = statechunks1.begin();
    matEnd = statechunks1.end ();

    while (matIt!=matEnd)
    {
        i = statechunks2.find(*matIt);

        if (i == statechunks2.end()) return false;

        ++matIt;
    }

    return true;
}

/*! Checks if geometry can be merged into this one.
return -1 if merging is not possible.
0 - geometries are identical ( use merge0 )
1 - ...
2 - ...
3 - ...
...

They need to have the same material and the same set of
attributes.
*/
Int16 Geometry::MergeIndex( const GeometryPtr other )
{
    //if ( getMaterial() != other->getMaterial() ) return -1;
    if (!CompareMaterials(getMaterial(),other->getMaterial())) return -1;


    //compare the existing attributes
    if ( ( (        getNormals()            != NullFC ) ^
           ( other->getNormals()            != NullFC )
        ) ||
        ( (        getColors()              != NullFC ) ^
          ( other->getColors()              != NullFC )
        ) ||
        ( (        getSecondaryColors()     != NullFC ) ^
          ( other->getSecondaryColors()     != NullFC )
        ) ||
        ( (        getTexCoords()           != NullFC ) ^
          ( other->getTexCoords()           != NullFC )
        ) ||
        ( (        getTexCoords1()          != NullFC ) ^
          ( other->getTexCoords1()          != NullFC )
        ) ||
        ( (        getTexCoords2()          != NullFC ) ^
          ( other->getTexCoords2()          != NullFC )
        ) ||
        ( (        getTexCoords3()          != NullFC ) ^
          ( other->getTexCoords3()          != NullFC )
        ) ||
        ( (        getTexCoords4()          != NullFC ) ^
          ( other->getTexCoords4()          != NullFC )
        ) ||
        ( (        getTexCoords5()          != NullFC ) ^
          ( other->getTexCoords5()          != NullFC )
        ) ||
        ( (        getTexCoords6()          != NullFC ) ^
          ( other->getTexCoords6()          != NullFC )
        ) ||
        ( (        getTexCoords7()          != NullFC ) ^
          ( other->getTexCoords7()          != NullFC )
        ) )
        return -1;

    /*at this point the geometries should have
    the same material and attributes
    so they should be mergeable
    remains to check indexing.
    */
    UInt16 nmap  = getIndexMapping().size();
    UInt16 onmap = other->getIndexMapping().size();

    if ( nmap == onmap ) return 0;
    else
    {
        //non-indexed in single-indexed
        if ( nmap == 1 && onmap == 0 ) return 1;
        //single-indexed in non-indexed
        if ( nmap == 0 && onmap == 1 ) return 2;

        //non-indexed in multi-indexed
        if ( nmap > 1 && onmap == 0 ) return 3;
        //multi-indexed in non-indexed
        if ( nmap == 0 && onmap > 1 ) return 4;

        //single-indexed in multi-indexed
        if ( nmap > 1 && onmap == 1 ) return 5;
        //multi-indexed in single-indexed
        if ( nmap == 1 && onmap > 1 ) return 6;
    }

    //hmm...another case?
    return -1;
}

#define copyAttrib(Name, TypeT, Type) \
    { \
    Geo ## TypeT ## Ptr prop1 = Geo ## TypeT ## Ptr::dcast(get ## Type ()); \
    Geo ## TypeT ## Ptr prop2 = Geo ## TypeT ## Ptr::dcast(other->get ## Type ()); \
    if(prop1 != NullFC && prop2 != NullFC) \
    { \
        beginEditCP(prop1); \
        Name##Base = prop1->getSize(); \
        prop1->resize(Name##Base + prop2->getSize()); \
        for(i = 0; i < prop2->getSize(); ++i) \
            prop1->getField()[Name##Base + i] = prop2->getField()[i]; \
        endEditCP(prop1); \
    } \
    }

#define copyAllAttrib \
{ \
    copyAttrib(pos, Positions2f, Positions) \
    copyAttrib(pos, Positions3f, Positions) \
    copyAttrib(pos, Positions4f, Positions) \
    copyAttrib(pos, Positions2d, Positions) \
    copyAttrib(pos, Positions3d, Positions) \
    copyAttrib(pos, Positions4d, Positions) \
    copyAttrib(pos, Positions2s, Positions) \
    copyAttrib(pos, Positions3s, Positions) \
    copyAttrib(pos, Positions4s, Positions) \
    copyAttrib(type, PTypesUI8, Types) \
    copyAttrib(length, PLengthsUI8, Lengths) \
    copyAttrib(length, PLengthsUI16, Lengths) \
    copyAttrib(length, PLengthsUI32, Lengths) \
    copyAttrib(normal, Normals3f, Normals) \
    copyAttrib(normal, Normals3s, Normals) \
    copyAttrib(normal, Normals3b, Normals) \
    copyAttrib(color, Colors3f, Colors) \
    copyAttrib(color, Colors4f, Colors) \
    copyAttrib(color, Colors3ub, Colors) \
    copyAttrib(color, Colors4ub, Colors) \
    copyAttrib(seccolor, Colors3f, SecondaryColors) \
    copyAttrib(seccolor, Colors4f, SecondaryColors) \
    copyAttrib(seccolor, Colors3ub, SecondaryColors) \
    copyAttrib(seccolor, Colors4ub, SecondaryColors) \
    copyAttrib(texcoord, TexCoords1f, TexCoords) \
    copyAttrib(texcoord, TexCoords2f, TexCoords) \
    copyAttrib(texcoord, TexCoords3f, TexCoords) \
    copyAttrib(texcoord, TexCoords4f, TexCoords) \
    copyAttrib(texcoord1, TexCoords1f, TexCoords1) \
    copyAttrib(texcoord1, TexCoords2f, TexCoords1) \
    copyAttrib(texcoord1, TexCoords3f, TexCoords1) \
    copyAttrib(texcoord1, TexCoords4f, TexCoords1) \
    copyAttrib(texcoord2, TexCoords1f, TexCoords2) \
    copyAttrib(texcoord2, TexCoords2f, TexCoords2) \
    copyAttrib(texcoord2, TexCoords3f, TexCoords2) \
    copyAttrib(texcoord2, TexCoords4f, TexCoords2) \
    copyAttrib(texcoord3, TexCoords1f, TexCoords3) \
    copyAttrib(texcoord3, TexCoords2f, TexCoords3) \
    copyAttrib(texcoord3, TexCoords3f, TexCoords3) \
    copyAttrib(texcoord3, TexCoords4f, TexCoords3) \
    copyAttrib(texcoord4, TexCoords1f, TexCoords4) \
    copyAttrib(texcoord4, TexCoords2f, TexCoords4) \
    copyAttrib(texcoord4, TexCoords3f, TexCoords4) \
    copyAttrib(texcoord4, TexCoords4f, TexCoords4) \
    copyAttrib(texcoord5, TexCoords1f, TexCoords5) \
    copyAttrib(texcoord5, TexCoords2f, TexCoords5) \
    copyAttrib(texcoord5, TexCoords3f, TexCoords5) \
    copyAttrib(texcoord5, TexCoords4f, TexCoords5) \
    copyAttrib(texcoord6, TexCoords1f, TexCoords6) \
    copyAttrib(texcoord6, TexCoords2f, TexCoords6) \
    copyAttrib(texcoord6, TexCoords3f, TexCoords6) \
    copyAttrib(texcoord6, TexCoords4f, TexCoords6) \
    copyAttrib(texcoord7, TexCoords1f, TexCoords7) \
    copyAttrib(texcoord7, TexCoords2f, TexCoords7) \
    copyAttrib(texcoord7, TexCoords3f, TexCoords7) \
    copyAttrib(texcoord7, TexCoords4f, TexCoords7) \
    beginEditCP((GeometryPtr)this); \
    setDlistCache(other->getDlistCache()); \
    setVbo(other->getVbo()); \
    endEditCP((GeometryPtr)this); \
}

//merge two identical geometries
void Geometry::merge0( const GeometryPtr other )
{
    UInt32 posBase = 0,typeBase = 0,lengthBase = 0,normalBase = 0,colorBase = 0,
           seccolorBase = 0,texcoordBase = 0,texcoord1Base = 0,texcoord2Base = 0,
           texcoord3Base = 0, texcoord4Base = 0, texcoord5Base = 0, texcoord6Base = 0,
           texcoord7Base = 0;

    // append the data
    UInt32 i;

    copyAllAttrib;

    if ( getIndices() != NullFC )
    {
        // indices

        GeoIndicesPtr ind  =        getIndices();
        GeoIndicesPtr oind = other->getIndices();

        beginEditCP( ind );

        UInt32 indBase = ind->getSize();
        ind->resize( indBase + oind->getSize() );

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

            if ( ( mind = calcMappingIndex( MapPosition ) ) >= 0 )
                offsets[ mind ] = posBase;

            if ( ( mind = calcMappingIndex( MapNormal ) ) >= 0 )
                offsets[ mind ] = normalBase;

            if ( ( mind = calcMappingIndex( MapColor ) ) >= 0 )
                offsets[ mind ] = colorBase;

            if ( ( mind = calcMappingIndex( MapSecondaryColor ) ) >= 0 )
                offsets[ mind ] = seccolorBase;

            if ( ( mind = calcMappingIndex( MapTexCoords ) ) >= 0 )
                offsets[ mind ] = texcoordBase;

            if ( ( mind = calcMappingIndex( MapTexCoords1 ) ) >= 0 )
                offsets[ mind ] = texcoord1Base;

            if ( ( mind = calcMappingIndex( MapTexCoords2 ) ) >= 0 )
                offsets[ mind ] = texcoord2Base;

            if ( ( mind = calcMappingIndex( MapTexCoords3 ) ) >= 0 )
                offsets[ mind ] = texcoord3Base;

            if ( ( mind = calcMappingIndex( MapTexCoords4 ) ) >= 0 )
                offsets[ mind ] = texcoord4Base;

            if ( ( mind = calcMappingIndex( MapTexCoords5 ) ) >= 0 )
                offsets[ mind ] = texcoord5Base;

            if ( ( mind = calcMappingIndex( MapTexCoords6 ) ) >= 0 )
                offsets[ mind ] = texcoord6Base;

            if ( ( mind = calcMappingIndex( MapTexCoords7 ) ) >= 0 )
                offsets[ mind ] = texcoord7Base;

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
}


//merges non-indexed geometry in single-indexed one
void Geometry::merge1( const GeometryPtr other )
{
    UInt32 posBase,typeBase,lengthBase,normalBase,colorBase,
           seccolorBase,texcoordBase,texcoord1Base,texcoord2Base,
           texcoord3Base, texcoord4Base, texcoord5Base, texcoord6Base,
           texcoord7Base;

    UInt32 i;

    copyAllAttrib;

    GeoIndicesPtr ind = getIndices();

    UInt32 indBase = ind->getSize();
    ind->resize(indBase + other->getPositions()->getSize());

    beginEditCP(ind);

    for (i = 0; i < other->getPositions()->getSize(); i++ )
        ind->setValue( i + posBase, indBase + i );

    endEditCP( ind );
}

//merges single-indexed geometry in non-indexed one
//the non-indexed geometry is converted to single-indexed
void Geometry::merge2( const GeometryPtr other )
{
    UInt32 posBase,typeBase,lengthBase,normalBase,colorBase,
           seccolorBase,texcoordBase,texcoord1Base,texcoord2Base,
           texcoord3Base, texcoord4Base, texcoord5Base, texcoord6Base,
           texcoord7Base;

    UInt32 i;

    copyAllAttrib;

    GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
    beginEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);

    indices->resize(posBase + other->getIndices()->getSize());

    for (i = 0; i < posBase; i++)
        indices->setValue(i, i);

    for (i = 0; i < other->getIndices()->getSize(); i++)
        indices->setValue(posBase + other->getIndices()->getValue(i), posBase + i);

    endEditCP  (indices, GeoIndicesUI32::GeoPropDataFieldMask);

    beginEditCP((GeometryPtr)this, Geometry::IndicesFieldMask);

    setIndices(indices);

    endEditCP((GeometryPtr)this, Geometry::IndicesFieldMask);
}

//merges non-indexed geometry in multi-indexed one
void Geometry::merge3( const GeometryPtr other )
{
    UInt32 posBase,typeBase,lengthBase,normalBase,colorBase,
           seccolorBase,texcoordBase,texcoord1Base,texcoord2Base,
           texcoord3Base, texcoord4Base, texcoord5Base, texcoord6Base,
           texcoord7Base;

    UInt32 i;

    copyAllAttrib;

    // indices
    GeoIndicesPtr ind = getIndices();
    UInt16 nmap = getIndexMapping().size();
    Int16 mind;
    UInt32 indBase = ind->getSize();
    ind->resize( indBase + other->getPositions()->getSize()*nmap );

    beginEditCP( ind );

    for (i = 0; i < other->getPositions()->getSize(); i++)
    {
        if ( ( mind = calcMappingIndex( MapPosition ) ) >= 0 )
            ind->setValue(posBase + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapNormal ) ) >= 0 )
            ind->setValue(normalBase + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapColor ) ) >= 0 )
            ind->setValue(colorBase + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapSecondaryColor ) ) >= 0 )
            ind->setValue(seccolorBase + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords ) ) >= 0 )
            ind->setValue(texcoordBase + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords1 ) ) >= 0 )
            ind->setValue(texcoord1Base + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords2 ) ) >= 0 )
            ind->setValue(texcoord2Base + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords3 ) ) >= 0 )
            ind->setValue(texcoord3Base + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords4 ) ) >= 0 )
            ind->setValue(texcoord4Base + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords5 ) ) >= 0 )
            ind->setValue(texcoord5Base + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords6 ) ) >= 0 )
            ind->setValue(texcoord6Base + i, indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords7 ) ) >= 0 )
            ind->setValue(texcoord7Base + i, indBase + i*nmap + mind);
    }

    endEditCP( ind );
}

//merges multi-indexed geometry in non-indexed one
//the non-indexed geometry is converted to multi-indexed
void Geometry::merge4( const GeometryPtr other )
{
    UInt32 posBase = 0,typeBase = 0,lengthBase = 0,normalBase = 0,colorBase = 0,
           seccolorBase = 0,texcoordBase = 0,texcoord1Base = 0,texcoord2Base = 0,
           texcoord3Base = 0, texcoord4Base = 0, texcoord5Base = 0, texcoord6Base = 0,
           texcoord7Base = 0;

    UInt32 i;

    copyAllAttrib;

    GeoIndicesPtr oind = other->getIndices();
    UInt16 nmap = other->getIndexMapping().size();
    Int16 mind;
    GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
    beginEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);

    indices->resize( posBase*nmap + oind->getSize() );

    for (i = 0; i < posBase; i++)
    {
        if ( ( mind = calcMappingIndex( MapPosition ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapNormal ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapColor ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapSecondaryColor ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords1 ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords2 ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords3 ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords4 ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords5 ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords6 ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords7 ) ) >= 0 )
            indices->setValue(i, i*nmap + mind);
    }

    for (i = 0; i < other->getIndices()->getSize(); i++)
        indices->setValue(posBase*nmap + other->getIndices()->getValue(i), posBase*nmap + i);

    endEditCP  (indices, GeoIndicesUI32::GeoPropDataFieldMask);

    beginEditCP((GeometryPtr)this, Geometry::IndicesFieldMask);

    setIndices(indices);

    endEditCP((GeometryPtr)this, Geometry::IndicesFieldMask);
}

//merges single-indexed geometry in multi-indexed one
void Geometry::merge5( const GeometryPtr other )
{
    UInt32 posBase,typeBase,lengthBase,normalBase,colorBase,
           seccolorBase,texcoordBase,texcoord1Base,texcoord2Base,
           texcoord3Base, texcoord4Base, texcoord5Base, texcoord6Base,
           texcoord7Base;

    UInt32 i;

    copyAllAttrib;

    // indices
    GeoIndicesPtr ind = getIndices();
    GeoIndicesPtr oind = other->getIndices();
    UInt16 nmap = getIndexMapping().size();
    Int16 mind;
    UInt32 indBase = ind->getSize();
    ind->resize( indBase + oind->getSize()*nmap );

    beginEditCP( ind );

    for (i = 0; i < oind->getSize(); i++)
    {
        if ( ( mind = calcMappingIndex( MapPosition ) ) >= 0 )
            ind->setValue(posBase + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapNormal ) ) >= 0 )
            ind->setValue(normalBase + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapColor ) ) >= 0 )
            ind->setValue(colorBase + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapSecondaryColor ) ) >= 0 )
            ind->setValue(seccolorBase + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords ) ) >= 0 )
            ind->setValue(texcoordBase + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords1 ) ) >= 0 )
            ind->setValue(texcoord1Base + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords2 ) ) >= 0 )
            ind->setValue(texcoord2Base + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords3 ) ) >= 0 )
            ind->setValue(texcoord3Base + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords4 ) ) >= 0 )
            ind->setValue(texcoord4Base + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords5 ) ) >= 0 )
            ind->setValue(texcoord5Base + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords6 ) ) >= 0 )
            ind->setValue(texcoord6Base + oind->getValue(i), indBase + i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords7 ) ) >= 0 )
            ind->setValue(texcoord7Base + oind->getValue(i), indBase + i*nmap + mind);
    }

    endEditCP( ind );
}

//merges multi-indexed geometry in single-indexed one
//the single-indexed geometry is converted to multi-indexed
void Geometry::merge6( const GeometryPtr other )
{
    UInt32 posBase,typeBase,lengthBase,normalBase,colorBase,
           seccolorBase,texcoordBase,texcoord1Base,texcoord2Base,
           texcoord3Base, texcoord4Base, texcoord5Base, texcoord6Base,
           texcoord7Base;

    UInt32 i;

    copyAllAttrib;

    // indices
    GeoIndicesPtr ind = getIndices();
    GeoIndicesPtr indclone = getIndices()->clone();
    GeoIndicesPtr oind = other->getIndices();
    UInt16 nmap = other->getIndexMapping().size();
    Int16 mind;
    UInt32 indBase = ind->getSize();
    ind->resize( indBase*nmap + oind->getSize() );

    beginEditCP( ind );

    for (i = 0; i < indclone->getSize(); i++)
    {
        if ( ( mind = calcMappingIndex( MapPosition ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapNormal ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapColor ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapSecondaryColor ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords1 ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords2 ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords3 ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords4 ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords5 ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords6 ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);

        if ( ( mind = calcMappingIndex( MapTexCoords7 ) ) >= 0 )
            ind->setValue(indclone->getValue(i), i*nmap + mind);
    }

    for (i = 0; i < oind->getSize(); i++)
        ind->setValue(oind->getValue(i), indBase*nmap + i);

    endEditCP( ind );
}


bool Geometry::updateLowHighIndices( void )
{
    // Are we single-indexed or incomplete?
    if(getTypes  () == NullFC || getTypes  ()->size() == 0)
        return true;

    UInt32 primcount = getTypes()->size();
        
    if(getLengths() == NullFC || getLengths()->size() < primcount ||
       getIndices() == NullFC || getIndices()->size() == 0 ||
       getIndexMapping().size() > 1 
      )
        return true;
        
    GeoIndicesPtr indP = getIndices();
    
    UInt32 low, high, mini, maxi, cur;
    
    GeometryPtr self(this);
    beginEditCP(self, LowindicesFieldMask |
                      HighindicesFieldMask |
                      MinindexFieldMask |
                      MaxindexFieldMask);
                      
    
    getLowindices().resize(primcount);
    getHighindices().resize(primcount);
    mini = 0xffffffffU;
    maxi = 0;

    for (UInt32 i = 0, cur = 0; i < primcount; i++)
    {
        UInt32 l;
        getLengths()->getValue(l, i);
        
        low = 0xffffffffU;
        high = 0;
        
        for (UInt32 j = 0; j < l; ++j, ++cur)
        {
            if(cur >= indP->size())
                break;

            UInt32 ind;
            indP->getValue(ind, cur);
            
            if(ind < low ) low  = ind;
            if(ind > high) high = ind;
            if(ind < mini) mini = ind;
            if(ind > maxi) maxi = ind;
        }
        
        getLowindices()[i]  = low;
        getHighindices()[i] = high;
    }
    
    setMinindex(mini);
    setMaxindex(maxi);
    
    endEditCP(self,   LowindicesFieldMask |
                      HighindicesFieldMask |
                      MinindexFieldMask |
                      MaxindexFieldMask);
    
    return false;
}

void Geometry::createVBO(Window *win, UInt32 id)
{
    // we create a index in the range of 1 -n 0 is reserved!

    if(_vbos.capacity() > _vbos.size())
    {
        _vbos.push_back(new GeoVBO(win, this));
        win->setGLObjectId(id + 1, _vbos.size());
        return;
    }

    // search for a empty one
    for(UInt32 i=0;i<_vbos.size();++i)
    {
        if(_vbos[i] == NULL)
        {
            _vbos[i] = new GeoVBO(win, this);
            win->setGLObjectId(id + 1, i + 1);
            return;
        }
    }

    _vbos.push_back(new GeoVBO(win, this));
    win->setGLObjectId(id + 1, _vbos.size());
}

void Geometry::destroyVBO(Window *win, UInt32 id)
{
    UInt32 i = win->getGLObjectId(id + 1);

    if(i == 0)
        return;

    --i;

    if(i < _vbos.size())
    {
        delete _vbos[i];
        _vbos[i] = NULL;
    }
    win->setGLObjectId(id + 1, 0);
}

void Geometry::updateVBO(Window *win, UInt32 id)
{
    UInt32 i = win->getGLObjectId(id + 1);

    if(i == 0) // invalid not created yet.
    {
        // create a new one.
        createVBO(win, id);
        return;
    }

    --i;

    if(i < _vbos.size())
    {
        GeoVBO *vbo = _vbos[i];
        if(vbo != NULL)
        {
            vbo->update();
        }
    }
}

bool Geometry::drawVBO(Window *win, UInt32 id)
{
    win->validateGLObject(id);
    UInt32 i = win->getGLObjectId(id + 1);
    if(i == 0)
    {
        // couldn't create a vbo in handleGL.
        return false;
    }

    --i;

    if(i < _vbos.size())
    {
        GeoVBO *vbo = _vbos[i];
        if(vbo != NULL)
            vbo->draw();
    }
    return true;
}

//#undef copyAttrib
//#undef copyAllAttrib


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGGEOMETRY_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOMETRY_INLINE_CVSID;
}

