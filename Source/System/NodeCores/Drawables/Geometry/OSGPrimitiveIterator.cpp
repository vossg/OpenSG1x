/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000,2001 by the OpenSG Forum                   *
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
    
Iterate the primitives. See \ref PageSystemPrimitiveIterator for details.

*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \var osg::PrimitiveIterator::_geo;

    The geometry being iterated.
*/

/*! \var osg::PrimitiveIterator::_ended;

    Flag whether the iterator has reached the end.
*/

/*! \var osg::PrimitiveIterator::_primIndex;
*/

/*! \var osg::PrimitiveIterator::_actPointIndex;
*/

/*! \var osg::PrimitiveIterator::_actPrimType;
*/

/*! \var osg::PrimitiveIterator::_actPrimLength;
*/

/*! \var osg::PrimitiveIterator::_types;
*/

/*! \var osg::PrimitiveIterator::_lengths;
*/

/*! \var osg::PrimitiveIterator::_indices;
*/

/*! \var osg::PrimitiveIterator::_nmappings;
*/

/*! \var osg::PrimitiveIterator::_positionIndex;
*/

/*! \var osg::PrimitiveIterator::_normalIndex;
*/

/*! \var osg::PrimitiveIterator::_colorIndex;
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex;
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex1;
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex2;
*/

/*! \var osg::PrimitiveIterator::_texcoordsIndex3;
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
    _geo            (      ), 
    _ended          (  true),
    _primIndex      (     0), 
    _actPointIndex  (     0),
    _actPrimType    (     0), 
    _actPrimLength  (     0),
    _types          (NullFC), 
    _lengths        (NullFC), 
    _indices        (NullFC), 
    _nmappings      (     0),
    _positionIndex  (    -1), 
    _normalIndex    (    -1), 
    _colorIndex     (    -1), 
    _texcoordsIndex (    -1),
    _texcoordsIndex1(    -1),
    _texcoordsIndex2(    -1),
    _texcoordsIndex3(    -1)
{
}

/*! This constructor creates an iterator for the given node. It is useful to
    create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use Geometry::beginPrimitives() resp. Geometry::endPrimitives()
    to create an iterator.
*/
PrimitiveIterator::PrimitiveIterator(const GeometryPtr& geo) :
    _geo            (      ), 
    _ended          (  true),
    _primIndex      (     0), 
    _actPointIndex  (     0),
    _actPrimType    (     0), 
    _actPrimLength  (     0),
    _types          (NullFC), 
    _lengths        (NullFC), 
    _indices        (NullFC), 
    _nmappings      (     0),
    _positionIndex  (    -1), 
    _normalIndex    (    -1), 
    _colorIndex     (    -1), 
    _texcoordsIndex (    -1),
    _texcoordsIndex1(    -1),
    _texcoordsIndex2(    -1),
    _texcoordsIndex3(    -1)
{
    setGeo(geo);
}

/*! This constructor creates an iterator for the given geometry. It is useful
    to create an iterator to be used to seek() to a specific indexed face. 
    Otherwise, use Geometry::beginPrimitives() resp. Geometry::endPrimitives()
    to create an iterator.
*/
PrimitiveIterator::PrimitiveIterator(const NodePtr& geo) :
    _geo            (      ), 
    _ended          (  true),
    _primIndex      (     0), 
    _actPointIndex  (     0),
    _actPrimType    (     0), 
    _actPrimLength  (     0),
    _types          (NullFC), 
    _lengths        (NullFC), 
    _indices        (NullFC), 
    _nmappings      (     0),
    _positionIndex  (    -1), 
    _normalIndex    (    -1), 
    _colorIndex     (    -1), 
    _texcoordsIndex (    -1),
    _texcoordsIndex1(    -1),
    _texcoordsIndex2(    -1),
    _texcoordsIndex3(    -1)
{
    setGeo(geo);
}


PrimitiveIterator::PrimitiveIterator(const PrimitiveIterator &source) :
    _geo            (source._geo            ),
    _ended          (source._ended          ),
    _primIndex      (source._primIndex      ), 
    _actPointIndex  (source._actPointIndex  ),
    _actPrimType    (source._actPrimType    ), 
    _actPrimLength  (source._actPrimLength  ),  
    _types          (source._types          ), 
    _lengths        (source._lengths        ), 
    _indices        (source._indices        ), 
    _nmappings      (source._nmappings      ),
    _positionIndex  (source._positionIndex  ),
    _normalIndex    (source._normalIndex    ),
    _colorIndex     (source._colorIndex     ),
    _texcoordsIndex (source._texcoordsIndex ),
    _texcoordsIndex1(source._texcoordsIndex1),
    _texcoordsIndex2(source._texcoordsIndex2),
    _texcoordsIndex3(source._texcoordsIndex3)  
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
    setGeo(GeometryPtr::dcast(geo->getCore()));
}

/*---------------------------- Operators ---------------------------------*/

/*! Increment the iterator and move it to the next primitive. It does not
    change if it already is at the end.
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


void PrimitiveIterator::setToBegin(void)
{
    _primIndex       = 0;
    _actPointIndex   = 0;
    _ended           = false;
    _nmappings       = _geo->getIndexMapping().size();
    _positionIndex   = _geo->calcMappingIndex(Geometry::MapPosition);
    _normalIndex     = _geo->calcMappingIndex(Geometry::MapNormal);
    _colorIndex      = _geo->calcMappingIndex(Geometry::MapColor);
    _texcoordsIndex  = _geo->calcMappingIndex(Geometry::MapTexCoords);
    _texcoordsIndex1 = _geo->calcMappingIndex(Geometry::MapTexCoords1);
    _texcoordsIndex2 = _geo->calcMappingIndex(Geometry::MapTexCoords2);
    _texcoordsIndex3 = _geo->calcMappingIndex(Geometry::MapTexCoords3);

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

    if(index >= _types->getSize())
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
    
    this->_geo              = source._geo;
    this->_primIndex        = source._primIndex;
    this->_actPrimType      = source._actPrimType;
    this->_actPrimLength    = source._actPrimLength;
    this->_actPointIndex    = source._actPointIndex;
    this->_types            = source._types;
    this->_lengths          = source._lengths;
    this->_indices          = source._indices;
    this->_ended            = source._ended;
    this->_nmappings        = source._nmappings;
    this->_positionIndex    = source._positionIndex;
    this->_normalIndex      = source._normalIndex;
    this->_colorIndex       = source._colorIndex;
    this->_texcoordsIndex   = source._texcoordsIndex;
    this->_texcoordsIndex1  = source._texcoordsIndex1;
    this->_texcoordsIndex2  = source._texcoordsIndex2;
    this->_texcoordsIndex3  = source._texcoordsIndex3;

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool PrimitiveIterator::operator <(const PrimitiveIterator &other) const
{
    return _geo       == other._geo &&
           _primIndex <= other._primIndex;
}

bool PrimitiveIterator::operator ==(const PrimitiveIterator &other) const
{
    return _ended     == other._ended &&
           _geo       == other._geo &&
           _primIndex == other._primIndex;
}

bool PrimitiveIterator::operator !=(const PrimitiveIterator &other) const
{
    return !(*this == other);
}
