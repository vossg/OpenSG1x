/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

inline    
void Geometry::invalidateDlistCache(void)
{
    Window::refreshGLObject( getGLId() );
}

/*------------------------------ access -----------------------------------*/

inline
void Geometry::setTypes(const GeoPTypesPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTypes.getValue() != NullFC)
    {
        beginEditCP(_sfTypes.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTypes.getValue()->subParent(thisP);
        }
        endEditCP  (_sfTypes.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTypes.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TypesFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfTypes.setValue(value);
}

inline
void Geometry::setLengths(const GeoPLengthsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfLengths.getValue() != NullFC)
    {
        beginEditCP(_sfLengths.getValue(), Attachment::ParentsFieldMask);
        {
            _sfLengths.getValue()->subParent(thisP);
        }
        endEditCP  (_sfLengths.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfLengths.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(LengthsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfLengths.setValue(value);
}

inline
void Geometry::setPositions(const GeoPositionsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfPositions.getValue() != NullFC)
    {
        beginEditCP(_sfPositions.getValue(), Attachment::ParentsFieldMask);
        {
            _sfPositions.getValue()->subParent(thisP);
        }
        endEditCP  (_sfPositions.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfPositions.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(PositionsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfPositions.setValue(value);
}

inline
void Geometry::setNormals(const GeoNormalsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfNormals.getValue() != NullFC)
    {
        beginEditCP(_sfNormals.getValue(), Attachment::ParentsFieldMask);
        {
            _sfNormals.getValue()->subParent(thisP);
        }
        endEditCP  (_sfNormals.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfNormals.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(NormalsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfNormals.setValue(value);
}

inline
void Geometry::setColors(const GeoColorsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfColors.getValue() != NullFC)
    {
        beginEditCP(_sfColors.getValue(), Attachment::ParentsFieldMask);
        {
            _sfColors.getValue()->subParent(thisP);
        }
        endEditCP  (_sfColors.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfColors.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(ColorsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfColors.setValue(value);
}

inline
void Geometry::setSecondaryColors(const GeoColorsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfSecondaryColors.getValue() != NullFC)
    {
        beginEditCP(_sfSecondaryColors.getValue(), Attachment::ParentsFieldMask);
        {
            _sfSecondaryColors.getValue()->subParent(thisP);
        }
        beginEditCP(_sfSecondaryColors.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfSecondaryColors.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(SecondaryColorsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfSecondaryColors.setValue(value);
}

inline
void Geometry::setTexCoords(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords.getValue()->subParent(thisP);
        }
        endEditCP  (_sfTexCoords.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoordsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords.setValue(value);
}

inline
void Geometry::setTexCoords1(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords1.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords1.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords1.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords1.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords1.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoords1FieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords1.setValue(value);
}

inline
void Geometry::setTexCoords2(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords2.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords2.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords2.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords2.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords2.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoords2FieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords2.setValue(value);
}

inline
void Geometry::setTexCoords3(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords3.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords3.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords3.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords3.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords3.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoords3FieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords3.setValue(value);
}

inline
void Geometry::setTexCoords4(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords4.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords4.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords4.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords4.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords4.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoords4FieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords4.setValue(value);
}

inline
void Geometry::setTexCoords5(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords5.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords5.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords5.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords5.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords5.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoords5FieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords5.setValue(value);
}

inline
void Geometry::setTexCoords6(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords6.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords6.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords6.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords6.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords6.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoords6FieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords6.setValue(value);
}

inline
void Geometry::setTexCoords7(const GeoTexCoordsPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfTexCoords7.getValue() != NullFC)
    {
        beginEditCP(_sfTexCoords7.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTexCoords7.getValue()->subParent(thisP);
        }
        beginEditCP(_sfTexCoords7.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTexCoords7.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TexCoords7FieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        beginEditCP(value, Attachment::ParentsFieldMask);
    }

    _sfTexCoords7.setValue(value);
}

inline
void Geometry::setIndices(const GeoIndicesPtr &value)
{
    GeometryPtr thisP = getPtr();

    addRefCP(value);

    if(_sfIndices.getValue() != NullFC)
    {
        beginEditCP(_sfIndices.getValue(), Attachment::ParentsFieldMask);
        {
            _sfIndices.getValue()->subParent(thisP);
        }
        endEditCP  (_sfIndices.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfIndices.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(IndicesFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfIndices.setValue(value);
}

inline
void Geometry::setMaterial(const MaterialPtr &value)
{
    setRefdCP(_sfMaterial.getValue(), value);
}


OSG_END_NAMESPACE

#define OSGGEOMETRY_INLINE_CVSID "@(#)$Id: $"

