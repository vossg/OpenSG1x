/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include <OSGConfig.h>
#include "OSGNFIOGeometry.h"
#include "OSGNFIOFactory.h"

#include "OSGNFIOQuantizer.h"
#include "OSGNFIOBitPacker.h"

#include <OSGLog.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NFIOGeometry
           reads and writes a geometry node.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NFIOGeometry NFIOGeometry::_the;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOGeometry::NFIOGeometry(void) :
    NFIOBase("Geometry")
{
    _version = 100;
}

/*------------------------------ destructor -------------------------------*/

NFIOGeometry::~NFIOGeometry(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

FieldContainerPtr NFIOGeometry::readFC(const std::string &/*typeName*/)
{
    FDEBUG(("NFIOGeometry::readFC\n"));
    
    GeometryPtr geo = Geometry::create();
    
    UInt16 version;
    _in->getValue(version);
    
    std::string fieldName;
    
    fieldName = readFCFields(geo, "", "'qpositions' 'qnormals'"
                                      " 'qtexCoords' 'pindices'");
    
    if(fieldName.empty())
        return geo;

    // qpositions
    if(fieldName == "qpositions")
    {
        readQuantizedPositions(geo);
        _in->getValue(fieldName);
        if(fieldName.empty())
            return geo;
    }
    
    // qnormals
    if(fieldName == "qnormals")
    {
        readQuantizedNormals(geo);
        _in->getValue(fieldName);
        if(fieldName.empty())
            return geo;
    }
    
    // qtexCoords
    if(fieldName == "qtexCoords")
    {
        readQuantizedTexCoords(geo);
        _in->getValue(fieldName);
        if(fieldName.empty())
            return geo;
    }
    
    // indices
    if(fieldName == "pindices")
    {
        readPackedIndices(geo);
        _in->getValue(fieldName);
        if(fieldName.empty())
            return geo;
    }
    
    return geo;
}

void NFIOGeometry::readQuantizedPositions(GeometryPtr &geo)
{
    // read quantized normals.
    
    std::string fieldType;
    _in->getValue(fieldType);
    
    GeoPositions3fPtr positions = GeoPositions3f::create();
    readQuantizedVectors<Pnt3f>(positions);
    
    beginEditCP(geo, Geometry::PositionsFieldMask);
        geo->setPositions(positions);
    endEditCP(geo, Geometry::PositionsFieldMask);
}

void NFIOGeometry::readQuantizedNormals(GeometryPtr &geo)
{
    // read quantized normals.
    
    std::string fieldType;
    _in->getValue(fieldType);
    
    GeoNormals3fPtr normals = GeoNormals3f::create();
    readQuantizedVectors<Vec3f>(normals);
    
    beginEditCP(geo, Geometry::NormalsFieldMask);
        geo->setNormals(normals);
    endEditCP(geo, Geometry::NormalsFieldMask);
}

void NFIOGeometry::readQuantizedTexCoords(GeometryPtr &geo)
{
    // read quantized texcoords.
    
    std::string fieldType;
    _in->getValue(fieldType);
    
    GeoTexCoords2fPtr texcoords = GeoTexCoords2f::create();
    readQuantizedVectors<Vec2f>(texcoords);
    
    beginEditCP(geo, Geometry::TexCoordsFieldMask);
        geo->setTexCoords(texcoords);
    endEditCP(geo, Geometry::TexCoordsFieldMask);
}

void NFIOGeometry::readPackedIndices(GeometryPtr &geo)
{
    // read packed indices.
    
    std::string fieldType;
    _in->getValue(fieldType);

    UInt32 size = 0;
    UInt32 max = 0;
    UInt32 indices_size = 0;
    UInt32 noe = 0;

    _in->getValue(size);
    _in->getValue(max);
    _in->getValue(indices_size);
    _in->getValue(noe);

    GeoIndicesPtr indices;
    bool using_16bit = false;
    if(getOptions().unpack16BitIndices())
    {
        // auto create 16 bit indices?
        if(max > TypeTraits<UInt16>::getMax())
        {
            indices = GeoIndicesUI32::create();
        }
        else
        {
            using_16bit = true;
            indices = GeoIndicesUI16::create();
        }
    }
    else
    {
        indices = GeoIndicesUI32::create();
    }

    std::vector<UInt8> buffer;
    buffer.reserve(noe);
    UInt8 v;
    for(UInt32 i=0;i<noe;++i)
    {
        _in->getValue(v);
        buffer.push_back(v);
    }

    if(using_16bit)
    {
        MFUInt16 *ind = GeoIndicesUI16Ptr::dcast(indices)->getFieldPtr();
        ind->reserve(indices_size);
        beginEditCP(indices);
            BitUnpacker unpacker(buffer, max);
            for(UInt32 i=0;i<indices_size;++i)
                ind->push_back(UInt16(unpacker.unpack()));
        endEditCP(indices);
    }
    else
    {
        MFUInt32 *ind = GeoIndicesUI32Ptr::dcast(indices)->getFieldPtr();
        ind->reserve(indices_size);
        beginEditCP(indices);
            BitUnpacker unpacker(buffer, max);
            for(UInt32 i=0;i<indices_size;++i)
                ind->push_back(unpacker.unpack());
        endEditCP(indices);
    }

    beginEditCP(geo, Geometry::IndicesFieldMask);
        geo->setIndices(indices);
    endEditCP(geo, Geometry::IndicesFieldMask);
}

template<class VecType, class GeoPropType> 
void NFIOGeometry::readQuantizedVectors(const GeoPropType &prop)
{
    UInt32 size = 0;
    UInt8 res = 0;
    Real32 min = 0;
    Real32 max = 0;
    UInt32 d = prop->getDimension();
    UInt32 noe = 0;
    
    _in->getValue(size); // size
    _in->getValue(res);
    _in->getValue(min);
    _in->getValue(max);
    _in->getValue(noe);
    
    prop->getFieldPtr()->reserve(noe);
    beginEditCP(prop);
    VecType t;
    
    if(res == Quantizer::QRES_8BIT)
    {
        Quantizer quantizer(min, max, res);
        UInt8 qv;
        for(UInt32 i=0;i<noe;++i)
        {
            for(UInt32 j=0;j<d;++j)
            {
                _in->getValue(qv);
                t[j] = quantizer.decode(qv);
            }
            prop->addValue(t);
        }
    }
    else if(res == Quantizer::QRES_16BIT)
    {
        Quantizer quantizer(min, max, res);
        UInt16 qv;
        for(UInt32 i=0;i<noe;++i)
        {
            for(UInt32 j=0;j<d;++j)
            {
                _in->getValue(qv);
                t[j] = quantizer.decode(qv);
            }
            prop->addValue(t);
        }
    }
    else if (res == Quantizer::QRES_24BIT)
    {
        Quantizer quantizer(min, max, res);
        UInt32 qv;
        UInt16 qvl;
        UInt8  qvh;
        for(UInt32 i=0;i<noe;++i)
        {
            for(UInt32 j=0;j<d;++j)
            {
                _in->getValue(qvl);
                _in->getValue(qvh);
                qv = ((qvl | (qvh << 16)) & 0x00ffffff);
                t[j] = quantizer.decode(qv);
            }
            prop->addValue(t);
        }
    }
    endEditCP(prop);
}

// ------------------------ writer ----------------------------

void NFIOGeometry::writeFC(const FieldContainerPtr &fc)
{
    FDEBUG(("NFIOGeometry::witeFC\n"));
    
    GeometryPtr geo = GeometryPtr::dcast(fc);
    
    _out->putValue(_version);

    std::string exclude = "";
    
    if(getOptions().quantizePositions() != 0)
        exclude += "'positions'";
    if(getOptions().quantizeNormals() != 0)
        exclude += "'normals'";
    if(getOptions().quantizeTexCoords() != 0)
        exclude += "'texCoords'";
    if(getOptions().packIndices())
        exclude += "'indices'";
    
    writeFCFields(geo, exclude, false);
    
    if(getOptions().quantizePositions() != Quantizer::QRES_OFF)
        writeQuantizedPositions(geo, getOptions().quantizePositions());
    
    if(getOptions().quantizeNormals() != Quantizer::QRES_OFF)
        writeQuantizedNormals(geo, getOptions().quantizeNormals());
    
    if(getOptions().quantizeTexCoords() != Quantizer::QRES_OFF)
        writeQuantizedTexCoords(geo, getOptions().quantizeTexCoords());
    
    if(getOptions().packIndices())
        writePackedIndices(geo);

    writeEndMarker();
}

void NFIOGeometry::writeQuantizedPositions(const GeometryPtr &geo, UInt8 res)
{
    GeoPositions3fPtr positions = GeoPositions3fPtr::dcast(geo->getPositions());
    
    if(positions != NullFC)
    {
        writeQuantizedVectors<Pnt3f>(positions, "qpositions", "QMFUInt83f", res);
    }
}


void NFIOGeometry::writeQuantizedNormals(const GeometryPtr &geo, UInt8 res)
{
    GeoNormals3fPtr normals = GeoNormals3fPtr::dcast(geo->getNormals());
    
    if(normals != NullFC)
    {
        writeQuantizedVectors<Vec3f>(normals, "qnormals", "QMFUInt83f", res);
    }
}

void NFIOGeometry::writeQuantizedTexCoords(const GeometryPtr &geo, UInt8 res)
{
    GeoTexCoords2fPtr texcoords = GeoTexCoords2fPtr::dcast(geo->getTexCoords());
    
    if(texcoords != NullFC)
    {
        writeQuantizedVectors<Vec2f>(texcoords, "qtexCoords", "QMFUInt82f", res);
    }
}

void NFIOGeometry::writePackedIndices(const GeometryPtr &geo)
{
    // write packed indices.

    GeoIndicesPtr indices = geo->getIndices();
    
    if(indices != NullFC)
    {
        _out->putValue(std::string("pindices"));
        _out->putValue(std::string("PMFUInt8"));
        
        // get max index.
        UInt32 max = 0;
        UInt32 indices_size = indices->getSize();
        for(UInt32 i=0;i<indices_size;++i)
        {
            UInt32 v = indices->getValue(i);
            if(v > max)
                max = v;
        }
        
        BitPacker packer(indices_size, max);
        for(UInt32 i=0;i<indices_size;++i)
            packer.pack(indices->getValue(i));
        
        std::vector<UInt8> &buffer = packer.getBuffer();
       
        UInt32 noe = buffer.size();
        UInt32 size = sizeof(UInt32) + sizeof(UInt32) + sizeof(UInt8) * noe;
        _out->putValue(size);
        _out->putValue(max);
        _out->putValue(indices_size);
        _out->putValue(noe);
        for(UInt32 i=0;i<noe;++i)
            _out->putValue(buffer[i]);
    }
}

template<class VecType, class GeoPropType>
void NFIOGeometry::writeQuantizedVectors(const GeoPropType &prop,
                                         const std::string &fieldName,
                                         const std::string &fieldType,
                                         UInt8 res)
{
    UInt32 noe = prop->getSize();
        
    if(noe > 0)
    {
        UInt32 d = prop->getDimension();
        Real32 min = FLT_MAX;
        Real32 max = -FLT_MAX;
        VecType v;
        
        for(UInt32 i=0;i<noe;++i)
        {
            v = prop->getValue(i);
            for(UInt32 j=0;j<d;++j)
            {
                if(v[j] < min)
                    min = v[j];
                if(v[j] > max)
                    max = v[j];
            }
        }
        
        _out->putValue(fieldName);
        _out->putValue(fieldType);
        
        UInt32 size = 0;
        if(res == Quantizer::QRES_8BIT)
        {
            size = sizeof(UInt8) * d * noe + sizeof(UInt8) +
                   sizeof(Real32) + sizeof(Real32) + sizeof(UInt32);
        }
        else if(res == Quantizer::QRES_16BIT)
        {
            size = sizeof(UInt16) * d * noe + sizeof(UInt8) +
                   sizeof(Real32) + sizeof(Real32) + sizeof(UInt32);
        }
        else if(res == Quantizer::QRES_24BIT)
        {
            size = (sizeof(UInt16) + sizeof(UInt8)) * d * noe + sizeof(UInt8) +
                    sizeof(Real32) + sizeof(Real32) + sizeof(UInt32);
        }
        
        _out->putValue(size); // size
        _out->putValue(res);
        _out->putValue(min);
        _out->putValue(max);
        _out->putValue(noe);
        
        if(res == Quantizer::QRES_8BIT)
        {
            Quantizer quantizer(min, max, res);
            UInt8 qv;
            for(UInt32 i=0;i<noe;++i)
            {
                v = prop->getValue(i);
                for(UInt32 j=0;j<d;++j)
                {
                    qv = quantizer.encode(v[j]);
                    _out->putValue(qv);
                }
            }
        }
        else if(res == Quantizer::QRES_16BIT)
        {
            Quantizer quantizer(min, max, res);
            UInt16 qv;
            for(UInt32 i=0;i<noe;++i)
            {
                v = prop->getValue(i);
                for(UInt32 j=0;j<d;++j)
                {
                    qv = quantizer.encode(v[j]);
                    _out->putValue(qv);
                }
            }
        }
        else if(res == Quantizer::QRES_24BIT)
        {
            Quantizer quantizer(min, max, res);
            UInt32 qv;
            UInt16 qvl;
            UInt8  qvh;
            for(UInt32 i=0;i<noe;++i)
            {
                v = prop->getValue(i);
                for(UInt32 j=0;j<d;++j)
                {
                    qv = quantizer.encode(v[j]);
                    qvl = (qv & 0x0000ffff);
                    qvh = ((qv >> 16) & 0x000000ff);
                    _out->putValue(qvl);
                    _out->putValue(qvh);
                }
            }
        }
    }
}

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNFIOGeometry.cpp,v 1.5 2005/09/30 21:27:48 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGNFIOGEOMETRY_HEADER_CVSID;
}
