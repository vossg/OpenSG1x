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

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

/*------------------------------ access -----------------------------------*/

inline
void Particles::setPositions(const GeoPositionsPtr &value)
{
    ParticlesPtr thisP(*this);

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
void Particles::setSecPositions(const GeoPositionsPtr &value)
{
    ParticlesPtr thisP(*this);

    addRefCP(value);

    if(_sfSecPositions.getValue() != NullFC)
    {
        beginEditCP(_sfSecPositions.getValue(), Attachment::ParentsFieldMask);
        {
            _sfSecPositions.getValue()->subParent(thisP);
        }
        endEditCP  (_sfSecPositions.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfSecPositions.getValue());
    }

    if(value != NullFC)
    {
        thisP.setParentFieldPos(SecPositionsFieldId);

        beginEditCP(value, Attachment::ParentsFieldMask);
        {
            value->addParent(thisP);
        }
        endEditCP  (value, Attachment::ParentsFieldMask);
    }

    _sfSecPositions.setValue(value);
}

inline
void Particles::setColors(const GeoColorsPtr &value)
{
    ParticlesPtr thisP(*this);

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
void Particles::setNormals(const GeoNormalsPtr &value)
{
    ParticlesPtr thisP(*this);

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
void Particles::setMaterial(const MaterialPtr &value)
{
    setRefdCP(_sfMaterial.getValue(), value);
}

OSG_END_NAMESPACE

#define OSGPARTICLES_INLINE_CVSID "@(#)$Id: OSGParticles.inl,v 1.1 2002/01/04 17:05:03 dirk Exp $"

