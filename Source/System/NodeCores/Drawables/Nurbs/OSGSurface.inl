/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void Surface::setControlPoints(const GeoPositionsPtr &value)
{
    SurfacePtr thisP(*this);

    addRefCP(value);

    if(_sfControlPoints.getValue() != NullFC)
    {
        beginEditCP(_sfControlPoints.getValue(), Attachment::ParentsFieldMask);
        {
            _sfControlPoints.getValue()->subParent(thisP);
        }
        endEditCP  (_sfControlPoints.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfControlPoints.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(ControlPointsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfControlPoints.setValue(value);
}

inline
void Surface::setTextureControlPoints(const GeoTexCoordsPtr &value)
{
    SurfacePtr thisP(*this);

    addRefCP(value);

    if(_sfTextureControlPoints.getValue() != NullFC)
    {
        beginEditCP(_sfTextureControlPoints.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTextureControlPoints.getValue()->subParent(thisP);
        }
        endEditCP  (_sfTextureControlPoints.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTextureControlPoints.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(TextureControlPointsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfTextureControlPoints.setValue(value);
}

OSG_END_NAMESPACE

#define OSGSURFACE_INLINE_CVSID "@(#)$Id: OSGSurface.inl,v 1.2 2006-11-09 20:59:39 edhellon Exp $"

