/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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
#include "OSGNodePtr.h"
#include "OSGPrimitiveIterator.h"

OSG_USING_NAMESPACE



/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PrimitiveIterator
    \ingroup GrpSystemDrawablesGeometryIterators
    
    Geometry Iterator for primitives. See \ref 
    PageSystemGeometryIterators for a description.

*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \var osg::PrimitiveIterator::_geo;

    The geometry being iterated.
*/

/*! \var osg::PrimitiveIterator::_ended;

    Flag whether the iterator has reached the end.
*/

/*! \var osg::PrimitiveIterator::_primIndex;

    Index of the currently iterated primitive. Returned by getIndex().
*/

/*! \var osg::PrimitiveIterator::_actPointIndex;

    The base of the indices used for this primitive.
*/

/*! \var osg::PrimitiveIterator::_actPrimType;

    Type of the current primitive.
*/

/*! \var osg::PrimitiveIterator::_actPrimLength;

    Length of the current primitive.
*/

/*! \var osg::PrimitiveIterator::_types;

    Cache variable for quick access to the Types Property of the iterated
    osg::Geometry.
*/

/*! \var osg::PrimitiveIterator::_lengths;

    Cache variable for quick access to the Lengths Property of the iterated
    osg::Geometry.
*/

/*! \var osg::PrimitiveIterator::_indices;

    Cache variable for quick access to the Indices Property of the iterated
    osg::Geometry.
*/

/*! \var osg::PrimitiveIterator::_nmappings;

    Cache variable for quick access to the length of the IndexMapping field of
    the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_positionIndex;

    Cache variable for quick access to the mapping index of positions for
    the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_normalIndex;

    Cache variable for quick access to the mapping index of normals for
    the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_colorIndex;

    Cache variable for quick access to the mapping index of colors for
    the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_secondaryColorIndex;

    Cache variable for quick access to the mapping index of secondary 
    colors for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex;

    Cache variable for quick access to the mapping index of texture coordinates
    for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex1;

    Cache variable for quick access to the mapping index of second texture 
    coordinates for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex2;

    Cache variable for quick access to the mapping index of third texture 
    coordinates for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex3;

    Cache variable for quick access to the mapping index of fourth texture 
    coordinates for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex4;

    Cache variable for quick access to the mapping index of fifth texture 
    coordinates for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex5;

    Cache variable for quick access to the mapping index of sixth texture 
    coordinates for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex6;

    Cache variable for quick access to the mapping index of seventh texture 
    coordinates for the iterated osg::Geometry .
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex7;

    Cache variable for quick access to the mapping index of eighth texture 
    coordinates for the iterated osg::Geometry .
*/

#endif // only include in dev docs

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char PrimitiveIterator::cvsid[] = "@(#)$Id: OSGPrimitiveIterator.cpp,v 1.17 2001/11/01 05:55:06 vossg Exp $";

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

PrimitiveIterator::PrimitiveIterator(void) :
    _geo                (      ), 
    _ended              (  true),
    _primIndex          (     0), 
    _actPointIndex      (     0),
    _actPrimType        (     0), 
    _actPrimLength      (     0),
    _types              (NullFC), 
    _lengths            (NullFC), 
    _indices            (NullFC), 
    _nmappings          (     0),
    _positionIndex      (    -1), 
    _normalIndex        (    -1), 
    _colorIndex         (    -1), 
    _secondaryColorIndex(    -1), 
    _texcoordsIndex     (    -1),
    _texcoordsIndex1    (    -1),
    _texcoordsIndex2    (    -1),
    _texcoordsIndex3    (    -1),
    _texcoordsIndex4    (    -1),
    _texcoordsIndex5    (    -1),
    _texcoordsIndex6    (    -1),
    _texcoordsIndex7    (    -1)
{
}

/*! This constructor creates an iterator for the given node. It is useful to
    create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use Geometry::beginPrimitives() resp. Geometry::endPrimitives()
    to create an iterator.
*/
PrimitiveIterator::PrimitiveIterator(const GeometryPtr& geo) :
    _geo                (      ), 
    _ended              (  true),
    _primIndex          (     0), 
    _actPointIndex      (     0),
    _actPrimType        (     0), 
    _actPrimLength      (     0),
    _types              (NullFC), 
    _lengths            (NullFC), 
    _indices            (NullFC), 
    _nmappings          (     0),
    _positionIndex      (    -1), 
    _normalIndex        (    -1), 
    _colorIndex         (    -1), 
    _secondaryColorIndex(    -1), 
    _texcoordsIndex     (    -1),
    _texcoordsIndex1    (    -1),
    _texcoordsIndex2    (    -1),
    _texcoordsIndex3    (    -1),
    _texcoordsIndex4    (    -1),
    _texcoordsIndex5    (    -1),
    _texcoordsIndex6    (    -1),
    _texcoordsIndex7    (    -1)
{
    setGeo(geo);
}

/*! This constructor creates an iterator for the given Node, which has to have
    a Geometry core. It is useful to create an iterator to be used to seek()
    to a specific indexed face. Otherwise, use Geometry::beginPrimitives()
    resp. Geometry::endPrimitives() to create an iterator.
*/
PrimitiveIterator::PrimitiveIterator(const NodePtr& geo) :
    _geo                (      ), 
    _ended              (  true),
    _primIndex          (     0), 
    _actPointIndex      (     0),
    _actPrimType        (     0), 
    _actPrimLength      (     0),
    _types              (NullFC), 
    _lengths            (NullFC), 
    _indices            (NullFC), 
    _nmappings          (     0),
    _positionIndex      (    -1), 
    _normalIndex        (    -1), 
    _colorIndex         (    -1), 
    _secondaryColorIndex(    -1), 
    _texcoordsIndex     (    -1),
    _texcoordsIndex1    (    -1),
    _texcoordsIndex2    (    -1),
    _texcoordsIndex3    (    -1),
    _texcoordsIndex4    (    -1),
    _texcoordsIndex5    (    -1),
    _texcoordsIndex6    (    -1),
    _texcoordsIndex7    (    -1)
{
    setGeo(geo);
}


PrimitiveIterator::PrimitiveIterator(const PrimitiveIterator &source) :
    _geo                (source._geo                ),
    _ended              (source._ended              ),
    _primIndex          (source._primIndex          ), 
    _actPointIndex      (source._actPointIndex      ),
    _actPrimType        (source._actPrimType        ), 
    _actPrimLength      (source._actPrimLength      ),  
    _types              (source._types              ), 
    _lengths            (source._lengths            ), 
    _indices            (source._indices            ), 
    _nmappings          (source._nmappings          ),
    _positionIndex      (source._positionIndex      ),
    _normalIndex        (source._normalIndex        ),
    _colorIndex         (source._colorIndex         ),
    _secondaryColorIndex(source._secondaryColorIndex),
    _texcoordsIndex     (source._texcoordsIndex     ),
    _texcoordsIndex1    (source._texcoordsIndex1    ),
    _texcoordsIndex2    (source._texcoordsIndex2    ),
    _texcoordsIndex3    (source._texcoordsIndex3    ),
    _texcoordsIndex4    (source._texcoordsIndex4    ),
    _texcoordsIndex5    (source._texcoordsIndex5    ),
    _texcoordsIndex6    (source._texcoordsIndex6    ),
    _texcoordsIndex7    (source._texcoordsIndex7    )
{
}

PrimitiveIterator::~PrimitiveIterator(void)
{
}


/*------------------------------- Set -----------------------------------*/

/*! Switch the iterator to a new geometry. Automatically sets it to the
    beginning.
*/
void PrimitiveIterator::setGeo(const GeometryPtr& geo)
{
    OSG_ASSERT(geo != NullFC);

    _geo     = geo;
    _types   = geo->getTypes();
    _lengths = geo->getLengths();
    _indices = geo->getIndices();
    
    setToBegin();
}


/*! Switch the iterator to a new geometry. Automatically sets it to the
    beginning.
*/
void PrimitiveIterator::setGeo(const NodePtr& geo)
{
    GeometryPtr gc = GeometryPtr::dcast(geo->getCore());
    
    if(gc == NullFC)
    {
        FWARNING(("PrimitiveIterator::setGeo: called for NodePtr which "
                  "is not a Geometry!\n"));
    }
    else
    {
        setGeo(gc);
    }
}

/*---------------------------- Operators ---------------------------------*/

/*! Increment the iterator and move it to the next primitive. It does not
    change if it already is at the end.
    
    \dev Also updates the cache variables _actPointIndex, _actPrimType and
    _actPrimLength. \enddev
*/
void PrimitiveIterator::operator++()
{
    if(isAtEnd())
    {
        return;
    }

    _actPointIndex += _actPrimLength;
    
    ++_primIndex;

    if(_primIndex >= _types->getSize())
    {
        _ended = true;
    }
    else
    {
        _actPrimType = _types->getValue(_primIndex);
        if(_lengths != NullFC)
        {
            _actPrimLength = _lengths->getValue(_primIndex);
        }
        else if(_indices != NullFC)
        {
            _actPrimLength = _indices->getSize() / _nmappings;
        }
        else
        {
            _actPrimLength = _geo->getPositions()->getSize() / _nmappings;
        }
    }
}

/*! Set the iterator to the beginning of the attached Geometry. Is primarily
    used by osg::Geometry::beginPrimitives, but can also be used to quickly
    recycle an iterator.
*/
void PrimitiveIterator::setToBegin(void)
{
    _primIndex           = 0;
    _actPointIndex       = 0;
    _ended               = false;
    _nmappings           = _geo->getIndexMapping().size();
    _positionIndex       = _geo->calcMappingIndex(Geometry::MapPosition);
    _normalIndex         = _geo->calcMappingIndex(Geometry::MapNormal);
    _colorIndex          = _geo->calcMappingIndex(Geometry::MapColor);
    _secondaryColorIndex = _geo->calcMappingIndex(Geometry::MapSecondaryColor);
    _texcoordsIndex      = _geo->calcMappingIndex(Geometry::MapTexCoords);
    _texcoordsIndex1     = _geo->calcMappingIndex(Geometry::MapTexCoords1);
    _texcoordsIndex2     = _geo->calcMappingIndex(Geometry::MapTexCoords2);
    _texcoordsIndex3     = _geo->calcMappingIndex(Geometry::MapTexCoords3);
    _texcoordsIndex4     = _geo->calcMappingIndex(Geometry::MapTexCoords4);
    _texcoordsIndex5     = _geo->calcMappingIndex(Geometry::MapTexCoords5);
    _texcoordsIndex6     = _geo->calcMappingIndex(Geometry::MapTexCoords6);
    _texcoordsIndex7     = _geo->calcMappingIndex(Geometry::MapTexCoords7);

    if(_nmappings == 0)
        _nmappings = 1;
                  
    if(_types != NullFC && _types->getSize() > 0)
    {
        _actPrimType = _types->getValue(_primIndex);
        if(_lengths != NullFC)
        {
            _actPrimLength = _lengths->getValue(_primIndex);
        }
        else if(_indices != NullFC)
        {
            _actPrimLength = _indices->getSize() / _nmappings;
        }
        else
        {
            _actPrimLength = _geo->getPositions()->getSize() / _nmappings;
        }
    }
    else
    {
        setToEnd();
    }
}

/*! Set the iterator to the end of the attached Geometry. Is primarily used by
    osg::Geometry::endPrimitives, but can also be used to quickly recycle an
    iterator.
*/
void PrimitiveIterator::setToEnd(void)
{
    if(_types != NullFC)
        _primIndex = _types->getSize();
    else
        _primIndex = 0;
    _actPointIndex = 0;
    _ended = true;
}

/*! Seek the iterator to a specific primitive indicated by its index. 

    This is primarily used in conjunction with 
    osg::PrimitiveIterator::getIndex to record a position in the iteration and
    later return to it.
*/
void PrimitiveIterator::seek(Int32 index)
{   
    _actPointIndex = 0;
    _ended = false;

    if(index >= Int32(_types->getSize()))
    {
        _primIndex = _types->getSize();
        _ended = true;
    }
    else
    {
        _primIndex = osgMax(0, index);   
        
        for(UInt32 j = 0; j < _primIndex; j++)
            _actPointIndex += _lengths->getValue(j);
            
        _actPrimType = _types->getValue(_primIndex);
        _actPrimLength = _lengths->getValue(_primIndex);
    }
}

/*-------------------------- assignment -----------------------------------*/

PrimitiveIterator& PrimitiveIterator::operator =(const PrimitiveIterator &source)
{
    if(this == &source)
        return *this;
    
    this->_geo                  = source._geo;
    this->_primIndex            = source._primIndex;
    this->_actPrimType          = source._actPrimType;
    this->_actPrimLength        = source._actPrimLength;
    this->_actPointIndex        = source._actPointIndex;
    this->_types                = source._types;
    this->_lengths              = source._lengths;
    this->_indices              = source._indices;
    this->_ended                = source._ended;
    this->_nmappings            = source._nmappings;
    this->_positionIndex        = source._positionIndex;
    this->_normalIndex          = source._normalIndex;
    this->_colorIndex           = source._colorIndex;
    this->_secondaryColorIndex  = source._colorIndex;
    this->_texcoordsIndex       = source._texcoordsIndex;
    this->_texcoordsIndex1      = source._texcoordsIndex1;
    this->_texcoordsIndex2      = source._texcoordsIndex2;
    this->_texcoordsIndex3      = source._texcoordsIndex3;
    this->_texcoordsIndex4      = source._texcoordsIndex4;
    this->_texcoordsIndex5      = source._texcoordsIndex5;
    this->_texcoordsIndex6      = source._texcoordsIndex6;
    this->_texcoordsIndex7      = source._texcoordsIndex7;

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*! Compare two iterators. If the iterators are attached to different
    geometries a comparison in senseless, in that case false will be returned.
*/
bool PrimitiveIterator::operator <(const PrimitiveIterator &other) const
{
    return _geo       == other._geo &&
           _primIndex <= other._primIndex;
}

/*! Compare two iterators. If the iterators are attached to different
    geometries a comparison in senseless, in that case false will be returned.
*/
bool PrimitiveIterator::operator ==(const PrimitiveIterator &other) const
{
    return _ended     == other._ended &&
           _geo       == other._geo &&
           _primIndex == other._primIndex;
}

/*! Compare two iterators. If the iterators are attached to different
    geometries a comparison in senseless, in that case false will be returned.
*/
bool PrimitiveIterator::operator !=(const PrimitiveIterator &other) const
{
    return !(*this == other);
}
