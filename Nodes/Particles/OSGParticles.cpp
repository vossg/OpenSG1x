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
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGMaterial.h>
#include <OSGGeoPropPtrs.h>
#include <OSGCamera.h>

#include "OSGParticles.h"

#include <algorithm>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGParticles.cpp,v 1.16 2002/03/19 17:19:38 dirk Exp $";
    static char cvsid_hpp[] = OSGPARTICLES_HEADER_CVSID;
    static char cvsid_inl[] = OSGPARTICLES_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::Particles

The main idea of particles is to give a way of easily rendering large numbers
of simple geometric objects. Particles are mostly used together with partially
transparent textures to simulate fuzzy objects, but other uses are possible,
e.g. molecules as stick-and-sphere models, stars or arrows for flow-field
visualisations.

The Particles core can display different styles of particles and keeps all the
data needed to do all of them. Not every style uses all the data, and using
simpler setups can result in vastly improved performance (if it doesn't, add a
fast path to Particles::findDrawer ;).

The supported styles are:
  - Points
  - Lines
  - ViewDirQuads
  - Arrows

The available attributes are:

  - Positions
  - secPositions
  - Colors
  - Normals
  - Sizes
  - textureZs
  - Indices

The first 4 are realized similarly to the Geometry Properties, to allow unified
manipulation of data and sharing with geometry nodes. They can handle the same
data formats the geometry can handle.

The only attribute every paticle needs is the position. Some styles need other
attributes, too, but most are optional. Colors, Normals, Sizes and textureZs
can either be left empty, have a single element or have as many elements as
there are positions. If only a single element is given, it is used by all
particles, otherwise every particle has its own element. 

Points are rendered as simple GL_POINTS. Points use the positions, colors and
textureZs attributes. A single size can be given, but size per particle is not
supported (yet).

Lines are two-point lines between a position and the corresponding secPosition,
i.e. there have to be as many positions as secPositions.

XXXXX To be completed later XXXXX

There is also a single material that is used to draw the particles, and
an attribute to change the draw order of the particles.

\b Extensions
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

Particles::Particles(void) :
    Inherited()
{
}

//! Copy Constructor

Particles::Particles(const Particles &source) :
    Inherited(source)
{
}

//! Destructor

Particles::~Particles(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void Particles::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ParticlesPtr  ,
                                          CNodePtr      ,
                                          Action       *>(&Particles::draw));

    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ParticlesPtr  ,
                                          CNodePtr      ,
                                          Action       *>(&Particles::render));
}

//! react to field changes

void Particles::changed(BitVector whichField, ChangeMode OSG_CHECK_ARG(from))
{
    if(whichField & PositionsFieldMask)
    {
        for(UInt32 i = 0; i < _parents.size(); i++)
        {
            _parents[i]->invalidateVolume();
        }
        getBsp().destroy();
    }
}

//! output the instance for debug purposes

void Particles::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Particles NI" << endl;
}

//! Adjust the given volume to enclose the particles

void Particles::adjustVolume( Volume & volume )
{
    GeoPositionsPtr pos = getPositions();

    if ( pos == NullFC )
        return;                 // Node has no particles, no volume

    volume.setValid();
    volume.setEmpty();

    MFVec3f *sizes = getMFSizes();

    if(sizes->getSize() == pos->getSize())
    {
        Vec3f p;
        Real32 s;

        for(UInt32 i = 0; i < pos->getSize(); i++)
        {
            pos->getValue(p, i);
            // make the size bigger to accomodate rotations
            s=sizes->getValue(i)[0]*Sqrt2;

            p[0]+=s/2;
            p[1]+=s/2;
            p[2]+=s/2;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]-=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
            p[2]-=s;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]+=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
        }

    }
    else if(sizes->getSize() == 1)
    {
        Vec3f p;
        Real32 s,s2;
        // make the size bigger to accomodate rotations
        s=sizes->getValue(0)[0]*Sqrt2;
        s2=s/2;

        for(UInt32 i = 0; i < pos->getSize(); i++)
        {
            pos->getValue(p, i);

            p[0]+=s2;
            p[1]+=s2;
            p[2]+=s2;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]-=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
            p[2]-=s;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]+=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
        }

    }
    else
    {
        Vec3f p;

        for(UInt32 i = 0; i < pos->getSize(); i++)
        {
            pos->getValue(p, i);

            volume.extendBy(p);
        }
    }
}


/*---------------------------- pumps -----------------------------------*/

/*  The pumps use a trait system to create specialized code for important
    cases. The general idea is to keep decision out of the inner loops
    and make special versions for the most common data types. Not for
    everything, as that creates big time code bloat.
 */

class ParticleTraits
{
};

/*! Color trait base, keep the static data needed for color handling */

struct ColTraitBase : public ParticleTraits
{
    typedef void (OSG_APIENTRY *pumpFunc)( GLubyte * data );
    static const int formatBase;
    enum { numFormats = GL_DOUBLE - GL_BYTE + 1 };

    static char *formatNames[];

    static pumpFunc ColorFuncs[numFormats][4]; 
};

const int ColTraitBase::formatBase = GL_BYTE;

char *ColTraitBase::formatNames[] = 
{   "GL_BYTE", "GL_UNSIGNED_BYTE", "GL_SHORT", "GL_UNSIGNED_SHORT", 
    "GL_INT", "GL_UNSIGNED_INT", "GL_FLOAT", "GL_2_BYTES", 
    "GL_3_BYTES", "GL_4_BYTES", "GL_DOUBLE"
};

ColTraitBase::pumpFunc 
ColTraitBase::ColorFuncs[ColTraitBase::numFormats][4] = {
    { NULL, NULL, 
      (pumpFunc)glColor3bv, (pumpFunc)glColor4bv },   // GL_BYTE
    { NULL, NULL, 
      (pumpFunc)glColor3ubv,(pumpFunc)glColor4ubv },  // GL_UNSIGNED_BYTE
    { NULL, NULL, 
      (pumpFunc)glColor3sv, (pumpFunc)glColor4sv },   // GL_SHORT
    { NULL, NULL,  
      (pumpFunc)glColor3usv,(pumpFunc)glColor4usv },  // GL_UNSIGNED_SHORT
    { NULL, NULL,  
      (pumpFunc)glColor3iv, (pumpFunc)glColor4iv },   // GL_INT
    { NULL, NULL,  
      (pumpFunc)glColor3uiv,(pumpFunc)glColor4uiv },  // GL_UNSIGNED_INT
    { NULL, NULL,  
      (pumpFunc)glColor3fv, (pumpFunc)glColor4fv },   // GL_FLOAT
    { NULL, NULL, NULL, NULL },                       // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                       // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                       // GL_4_BYTES
    { NULL, NULL,  
      (pumpFunc)glColor3dv, (pumpFunc)glColor4dv },   // GL_DOUBLE
};

struct ColTraitNone : public ColTraitBase
{
    typedef UInt8 dataType; // no data needed, but can't instantiate void
    
    static inline void init(Particles *, DrawActionBase *, dataType &)
    {
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

struct ColTraitSingle : public ColTraitBase
{
    typedef UInt8 dataType; // no data needed, but can't instantiate void
    
    static inline void init(Particles *part, DrawActionBase *, dataType &)
    {
        GeoColorsPtr col = part->getColors();
 
        if(col != NullFC)
        {
            pumpFunc col_func;

            col_func = ColorFuncs[ col->getFormat() - formatBase ]
                                 [ col->getDimension() - 1 ];

            if(col_func == NULL)
            {
                SWARNING << "Particles " << part << "have illegal "
                         << "colors: " << col->getDimension()
                         << "D " << formatNames[col->getFormat() - formatBase]
                         << "!" << endl;
                return;
            }
            else
            {
                col_func((GLubyte*) col->getData());
            }
        }
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

struct ColTraitParticle : public ColTraitBase
{
    typedef struct
    {
        UInt8    *data;
        UInt32    stride;
        pumpFunc  func;
    } 
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        GeoColorsPtr col = part->getColors();

        data.data = col->getData();
        if((data.stride = col->getStride()) == 0)
            data.stride = col->getFormatSize() * col->getDimension();
        
        data.func = ColorFuncs[ col->getFormat() - formatBase ]
                              [ col->getDimension() - 1 ];
                             
        if(data.func == NULL)
        {
            SWARNING << "Particles " << part << "have illegal "
                     << "colors: " << col->getDimension()
                     << "D " << formatNames[ col->getFormat() - formatBase ]
                     << "!" << endl;
            return;
        }
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {   
        data.func((GLubyte*)(data.data + particle * data.stride));
        return false;
    }
    
    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

struct ColTraitGeneric : public ColTraitBase
{
    typedef struct
    {
        UInt8    *data;
        UInt32    stride;
        pumpFunc  func;
        bool      perParticle;
    } 
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        GeoColorsPtr col = part->getColors();
        
        data.perParticle = false;
        
        if(col != NullFC)
        {
            data.data = col->getData();
            if((data.stride = col->getStride()) == 0)
                data.stride = col->getFormatSize() * col->getDimension();

            data.func = ColorFuncs[ col->getFormat() - formatBase ]
                                  [ col->getDimension() - 1 ];

            if(data.func == NULL)
            {
                SWARNING << "Particles " << part << "have illegal "
                         << "colors: " << col->getDimension()
                         << "D " << formatNames[ col->getFormat() - formatBase ]
                         << "!" << endl;
                return;
            }
            
            if(col->getSize() == 1)
            {
                data.func((GLubyte*) col->getData());
            }
            else if(col->getSize() == part->getPositions()->getSize())
            {
                data.perParticle = true;
            }
        }
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {   
        if(data.perParticle == true)
            data.func((GLubyte*)(data.data + particle * data.stride));
        return false;
    }
        
    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

/*! Position Particle Traits */

struct PosTraitGeneric : public ParticleTraits
{
    typedef struct
    {
        GeoPositionsPtr pos;
        Pnt3f p;
    }
    dataType;
    
    static inline void init(Particles *, DrawActionBase *, dataType &data,
        GeoPositionsPtr &pos)
    {
        data.pos = pos;
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {
        data.pos->getValue(data.p, particle);
             
        return false;
    }
    
    static inline Pnt3f &position(dataType &data)
    {
        return data.p;
    }
    
    static inline void vertex(dataType &data, UInt32 , Vec4f &dir, 
                              Real32 s)
    {
        glVertex3f( data.p[0] + dir[0] * s, 
                    data.p[1] + dir[1] * s, 
                    data.p[2] + dir[2] * s);             
    }
    
    static inline void vertex(dataType &data)
    {
        glVertex3fv( (GLfloat*) data.p.getValues() );             
    }
};

struct PosTrait3f : public ParticleTraits
{
    typedef struct
    {
        MFPnt3f *pos;
        Pnt3f   *p;
    }
    dataType;
    
    static inline void init(Particles *, DrawActionBase *, dataType &data,
        GeoPositionsPtr &pos)
    {
        GeoPositions3fPtr pos3f = GeoPositions3fPtr::dcast(pos);
 
        data.pos  = pos3f->getFieldPtr();
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {
        data.p = &data.pos->getValue(particle);
        return false;
    }
    
    static inline Pnt3f &position(dataType &data)
    {
        return *data.p;
    }
    
    static inline void vertex(dataType &data, UInt32 , Vec4f &dir, Real32 s)
    {
        glVertex3f( (*data.p)[0] + dir[0] * s, 
                    (*data.p)[1] + dir[1] * s, 
                    (*data.p)[2] + dir[2] * s);             
    }
    
    static inline void vertex(dataType &data)
    {
        glVertex3fv( (GLfloat*) (*data.p).getValues() );             
    }
};

/*! Particle Size Traits */

struct SizeTraitGeneric : public ParticleTraits
{
    typedef struct
    {
        MFVec3f *sizes;
        Vec3f    s;
        bool     perParticle;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        data.sizes = part->getMFSizes();
        
        if(data.sizes != NULL)
        {
            if(data.sizes->getSize() == 1)
            {
                data.s = data.sizes->getValue(0);
                data.perParticle = false;
            }
            else if(data.sizes->getSize() == part->getPositions()->getSize())
            {
                data.perParticle = true;
            }
            else
            {
                data.s.setValues(1,1,1);
                data.perParticle = false;
            }           
        }
        else
        {
            data.s.setValues(1,1,1);
            data.perParticle = false;
        }           
    }
   
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline Vec3f &size(dataType &data, UInt32 particle)
    {
        if(data.perParticle)
                return data.sizes->getValue(particle);
        return data.s;
    }
};

struct SizeTraitSingle : public ParticleTraits
{
    typedef struct
    {
        Vec3f    s;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        data.s = part->getSizes().getValue(0);
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline Vec3f &size(dataType &data, UInt32)
    {
        return data.s;
    }
};

struct SizeTraitParticle : public ParticleTraits
{
    typedef struct
    {
        MFVec3f *sizes;
        Vec3f    s;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        data.sizes = part->getMFSizes();
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline Vec3f &size(dataType &data, UInt32 particle)
    {
        return data.sizes->getValue(particle);
    }
};

struct SizeTraitNone : public ParticleTraits
{
    typedef UInt8 dataType;
    
    static inline void init(Particles *, DrawActionBase *, dataType &)
    {
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline Vec3f &size(dataType &, UInt32 )
    {
        static Vec3f s(1,1,1);
        return s;
    }
};

/*! Particle Texture Traits */

struct TexTraitGeneric : public ParticleTraits
{
    typedef struct
    {
        MFReal32 *texzs;
        Real32    z;
        bool      perParticle;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        data.texzs = part->getMFTextureZs();
        
        data.perParticle = false;
        
        if(data.texzs != NULL)
        {
            if(data.texzs->getSize() == 1)
            {
                data.z = data.texzs->getValue(0);
             }
            else if(data.texzs->getSize() == part->getPositions()->getSize())
            {
                data.perParticle = true;
            }
            else
            {
                data.z = 0;
            }           
        }
        else
        {
            data.z = 0;
        }
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {       
        if(data.perParticle)
        {
            data.z = data.texzs->getValue(particle);
        }
        return false;
    }
    
    static inline void vertex(dataType &data)
    {
        glTexCoord1f(data.z);
    }
    
    static inline void vertex(dataType &data, UInt32 , Real32 u,
                                Real32 v)
    {
        glTexCoord3f(u, v, data.z);
    }
};

struct TexTraitParticle : public ParticleTraits
{
    typedef struct
    {
        MFReal32 *texzs;
        Real32    z;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        data.texzs = part->getMFTextureZs();
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {       
        data.z = data.texzs->getValue(particle);
        return false;
    }
    
    static inline void vertex(dataType &data)
    {
        glTexCoord1f(data.z);
    }
    
    static inline void vertex(dataType &data, UInt32 , Real32 u,
                                Real32 v)
    {
        glTexCoord3f(u, v, data.z);
    }
};

struct TexTraitSingle : public ParticleTraits
{
    typedef struct
    {
        Real32    z;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        data.z = part->getMFTextureZs()->getValue(0);
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline void vertex(dataType &data)
    {
        glTexCoord1f(data.z);
    }
    
    static inline void vertex(dataType &data, UInt32 , Real32 u,
                                Real32 v)
    {
        glTexCoord3f(u, v, data.z);
    }
};

struct TexTraitNone : public ParticleTraits
{
    typedef UInt8 dataType;
    
    static inline void init(Particles *, DrawActionBase *, dataType &)
    {
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline void vertex(dataType &, UInt32 )
    {
        glTexCoord1f(0);
    }
   
    static inline void vertex(dataType &, UInt32, Real32 u, Real32 v)
    {
        glTexCoord2f(u, v);
    }
};


/*! Position Particle Traits */

struct NormalTraitGeneric : public ParticleTraits
{
    typedef struct
    {
        GeoNormalsPtr norms;
        Vec3f         n;
        bool          perParticle;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        data.norms = part->getNormals();
        
        data.perParticle = false;
        
        if(data.norms != NullFC)
        {
            if(data.norms->getSize() == 1)
            {
                data.n = data.norms->getValue(0);
            }
            else if(data.norms->getSize() == part->getPositions()->getSize())
            {
                data.perParticle = true;
            }
            else
            {
                data.n.setValues(0,1,0);
            }           
        }
        else
        {
            data.n.setValues(0,1,0);
        }
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {
        if(data.perParticle)
            data.norms->getValue(data.n, particle);
             
        return false;
    }
    
    static inline Vec3f &normal(dataType &data)
    {
        return data.n;
    }
    
    static inline void normal(dataType &data, UInt32 )
    {
        glNormal3fv( (GLfloat*) data.n.getValues() );            
    }
};

struct NormalTraitGeneric3f : public ParticleTraits
{
    typedef struct
    {
        MFVec3f *norms;
        Vec3f   *n;
        bool     perParticle;
        Vec3f    const_n;
    }
    dataType;
    
    static inline void init(Particles *part, DrawActionBase *, dataType &data)
    {
        GeoNormals3fPtr norms3f = GeoNormals3fPtr::dcast(part->getNormals());
        
        data.norms = norms3f->getFieldPtr();
        
        data.perParticle = false;
        
        if(norms3f != NullFC)
        {
            if(norms3f->getSize() == 1)
            {
                data.n = &data.norms->getValue(0);
            }
            else if(data.norms->getSize() == part->getPositions()->getSize())
            {
                data.perParticle = true;
            }
            else
            {
                data.const_n.setValues(0,1,0);
                data.n = &data.const_n;
            }           
        }
        else
        {
            data.const_n.setValues(0,1,0);
            data.n = &data.const_n;
        }
    }
    
    static inline bool particle(dataType &data, UInt32 particle)
    {
        if(data.perParticle)
            data.n = &data.norms->getValue(particle);
             
        return false;
    }
    
    static inline Vec3f &normal(dataType &data)
    {
        return *data.n;
    }
    
    static inline void normal(dataType &data, UInt32 )
    {
        glNormal3fv( (GLfloat*) data.n->getValues() );            
    }
};

/* ParticlesDrawer base classes, define the common interface(s) */

struct OSG::ParticlesDrawer
{
    virtual void draw(Particles *part, DrawActionBase *action) = 0;

    virtual void drawIndexed(Particles *part, DrawActionBase *action,
                             Int32 *index, UInt32 length) = 0;
};

/* View-Dir aligned, indexed quad rendering */

template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawViewDirQuads : public ParticlesDrawer 
{
    virtual void drawIndexed(Particles *part, DrawActionBase *action, 
                          Int32 *index, UInt32 length)
    {
        // get ModelView matrix to define the direction vectors
        Matrix camera,toworld;
        action->getCamera()->getBeacon()->getToWorld(camera);
        action->getActNode()->getToWorld(toworld);
        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();       
        toworld.transpose();
        camera.multLeft(toworld);

        // Direction vectors
        Vec4f  d1, d2, d3, d4;

        d1 = -1.0f * camera[0] + -1.0f * camera[1];
        d2 =  1.0f * camera[0] + -1.0f * camera[1];
        d3 =  1.0f * camera[0] +  1.0f * camera[1];
        d4 = -1.0f * camera[0] +  1.0f * camera[1];

        // some variables for faster access
        GeoPositionsPtr  pos  = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, action, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        glBegin(GL_QUADS);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > pos->getSize())
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.;

            if(s == 0)
                continue;

            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d1, s);

            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d2, s);

            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d3, s);

            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d4, s);
        }

        glEnd();
    }

    virtual void draw(Particles *part, DrawActionBase *action)
    {
        // get ModelView matrix to define the direction vectors
        Matrix camera,toworld;
        action->getCamera()->getBeacon()->getToWorld(camera);
        action->getActNode()->getToWorld(toworld);
        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();       
        toworld.transpose();
        camera.multLeft(toworld);

        // Direction vectors
        Vec4f  d1, d2, d3, d4;

        d1 = -1.0f * camera[0] + -1.0f * camera[1];
        d2 =  1.0f * camera[0] + -1.0f * camera[1];
        d3 =  1.0f * camera[0] +  1.0f * camera[1];
        d4 = -1.0f * camera[0] +  1.0f * camera[1];

        // some variables for faster access
        GeoPositionsPtr pos = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, action, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        glBegin(GL_QUADS);

        UInt32 length = pos->getSize();
        
        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.;

            if(s == 0)
                continue;
                
            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d1, s);

            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d2, s);

            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d3, s);

            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d4, s);
        }

        glEnd();
    }
};


/* Viewer aligned, indexed quad rendering */

template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawViewerQuads : public ParticlesDrawer 
{
    virtual void drawIndexed(Particles *part, DrawActionBase *action, 
                          Int32 *index, UInt32 length)
    {
        // get ModelView matrix to define the direction vectors
        Matrix camera,toworld;
        action->getCamera()->getBeacon()->getToWorld(camera);
        action->getActNode()->getToWorld(toworld);
        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();       
        toworld.invert();
        camera.multLeft(toworld);

        // Viewer position & up
        Pnt3f  vpos(camera[3]);
        Vec3f  vup (camera[1]);
        vup.normalize();
        Vec3f  vdir,vnorm;

        // direction vector
        Vec4f d;
        
        // some variables for faster access
        GeoPositionsPtr  pos  = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, action, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        glBegin(GL_QUADS);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > pos->getSize())
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.;

            if(s == 0)
                continue;

            // calc viewer-relative coord system
            
            Pnt3f p = pos->getValue(i);  
            vdir = vpos - p;  
            vdir.normalize();         
            vnorm = vup.cross(vdir);
 
            d.setValues( -vnorm[0] - vup[0],
                         -vnorm[1] - vup[1],
                         -vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d, s);

            d.setValues(  vnorm[0] - vup[0],
                          vnorm[1] - vup[1],
                          vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d, s);

            d.setValues(  vnorm[0] + vup[0],
                          vnorm[1] + vup[1],
                          vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d, s);

            d.setValues( -vnorm[0] + vup[0],
                         -vnorm[1] + vup[1],
                         -vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d, s);
        }

        glEnd();
    }

    virtual void draw(Particles *part, DrawActionBase *action)
    {
        // get ModelView matrix to define the direction vectors
        Matrix camera,toworld;
        action->getCamera()->getBeacon()->getToWorld(camera);
        action->getActNode()->getToWorld(toworld);
        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();       
        toworld.invert();
        camera.multLeft(toworld);

        // Viewer position & up
        Pnt3f  vpos(camera[3]);
        Vec3f  vup (camera[1]);
        vup.normalize();
        Vec3f  vdir,vnorm;

        // direction vector
        Vec4f d;
        
        // some variables for faster access
        GeoPositionsPtr pos = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, action, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        glBegin(GL_QUADS);

        UInt32 length = pos->getSize();
        
        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.;

            if(s == 0)
                continue;

            // calc viewer-relative coord system
            
            Pnt3f p = pos->getValue(i);  
            vdir = vpos - p;  
            vdir.normalize();         
            vnorm = vup.cross(vdir);
 
            d.setValues( -vnorm[0] - vup[0],
                         -vnorm[1] - vup[1],
                         -vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d, s);

            d.setValues(  vnorm[0] - vup[0],
                          vnorm[1] - vup[1],
                          vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d, s);

            d.setValues(  vnorm[0] + vup[0],
                          vnorm[1] + vup[1],
                          vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d, s);

            d.setValues( -vnorm[0] + vup[0],
                         -vnorm[1] + vup[1],
                         -vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d, s);
        }

        glEnd();
    }
};



/* Single color lines between secPos and pos */

template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawLines : public ParticlesDrawer 
{
    virtual void draw(Particles *part, DrawActionBase *action)
    {
        // some variables for faster access
        GeoPositionsPtr  pos  = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, action, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        typename posTrait::dataType secPosData;
        posTrait::init(part, action, secPosData, part->getSecPositions());

        Real32 s = sizeTrait::size(sizeData, 0)[0];

        GLfloat lw;
        glGetFloatv(GL_LINE_WIDTH, &lw);
        glLineWidth(s);
          
        glBegin(GL_LINES);

        UInt32 length = pos->getSize();
        
        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(posTrait::particle(secPosData, i))
                continue;

            posTrait::vertex(posData);
            posTrait::vertex(secPosData);
        }

        glEnd();
    
        if(osgabs(s-lw)>Eps)
            glLineWidth(lw);
    }

    virtual void drawIndexed(Particles *part, DrawActionBase *action, 
                             Int32 *index, UInt32 length)
    {
        // some variables for faster access
        GeoPositionsPtr  pos  = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, action, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        typename posTrait::dataType secPosData;
        posTrait::init(part, action, secPosData, part->getSecPositions());

        Real32 s = sizeTrait::size(sizeData, 0)[0];

        GLfloat lw;
        glGetFloatv(GL_LINE_WIDTH, &lw);
        glLineWidth(s);
          
        glBegin(GL_LINES);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > pos->getSize())
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(posTrait::particle(secPosData, i))
                continue;

            posTrait::vertex(posData);
            posTrait::vertex(secPosData);
        }

        glEnd();
    
        if(osgabs(s-lw)>Eps)
            glLineWidth(lw);
    }
};

/*  Points at pos */

template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawPoints : public ParticlesDrawer 
{
    virtual void draw(Particles *part, DrawActionBase *action)
    {
        // some variables for faster access
        GeoPositionsPtr  pos  = part->getPositions();

        // init traits
        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename texTrait::dataType texData;
        texTrait::init(part, action, texData);

        sizeTrait::particle(sizeData, 0);
        Real32 s = sizeTrait::size(sizeData, 0)[0];

        GLfloat ps;
        glGetFloatv(GL_POINT_SIZE, &ps);
        glPointSize(s);
          
        glBegin(GL_POINTS);

        UInt32 length = pos->getSize();
        
        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle(colData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(texTrait::particle(texData, i))
                continue;

            texTrait::vertex(texData);
            posTrait::vertex(posData);
        }

        glEnd();
    
        if(osgabs(s-ps)>Eps)
            glPointSize(ps);
    }

    virtual void drawIndexed(Particles *part, DrawActionBase *action, 
                             Int32 *index, UInt32 length)
    {
        // some variables for faster access
        GeoPositionsPtr  pos  = part->getPositions();

        // init traits
        typename posTrait::dataType posData;
        posTrait::init(part, action, posData, part->getPositions());

        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        sizeTrait::particle(sizeData, 0);
        Real32 s = sizeTrait::size(sizeData, 0)[0];

        GLfloat ps;
        glGetFloatv(GL_POINT_SIZE, &ps);
        glPointSize(s);
          
        glBegin(GL_POINTS);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > pos->getSize())
                continue;

            if(colTrait::particle(colData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            posTrait::vertex(posData);
        }

        glEnd();
    
        if(osgabs(s-ps)>Eps)
            glPointSize(ps);
    }
};

/* Geometry traits for drawing objects */

struct GeoTraitArrow : public ParticleTraits
{
    typedef UInt8 dataType;
    
    static inline void init(Particles *, DrawActionBase *, dataType &)
    {
    }
    
    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }
    
    static inline void draw(dataType &, Pnt3f &p,
                            Vec3f &dx, Vec3f &dy, Vec3f &dz,
                            Vec3f &s)
    {
        dz*=s[2];
        dx*=s[0];
       
        glNormal3fv((GLfloat*) dy.getValues() );
        
        glBegin(GL_TRIANGLE_FAN);
        
        glVertex3fv((GLfloat*) p.getValues() );
        
        glVertex3f(p[0] + dz[0] * .5f + dx[0]      ,
                   p[1] + dz[1] * .5f + dx[1]      ,
                   p[2] + dz[2] * .5f + dx[2]      );

        glVertex3f(p[0] + dz[0] * .5f + dx[0] * .5 ,
                   p[1] + dz[1] * .5f + dx[1] * .5 ,
                   p[2] + dz[2] * .5f + dx[2] * .5 );

        glVertex3f(p[0] + dz[0]       + dx[0] * .5 ,
                   p[1] + dz[1]       + dx[1] * .5 ,
                   p[2] + dz[2]       + dx[2] * .5 );

        glVertex3f(p[0] + dz[0]       - dx[0] * .5 ,
                   p[1] + dz[1]       - dx[1] * .5 ,
                   p[2] + dz[2]       - dx[2] * .5 );

        glVertex3f(p[0] + dz[0] * .5f - dx[0] * .5 ,
                   p[1] + dz[1] * .5f - dx[1] * .5 ,
                   p[2] + dz[2] * .5f - dx[2] * .5 );

        glVertex3f(p[0] + dz[0] * .5f - dx[0]      ,
                   p[1] + dz[1] * .5f - dx[1]      ,
                   p[2] + dz[2] * .5f - dx[2]      );
       
        glEnd();
    }
};



/* Objects using the pos/secpos/normal coordinate system for rendering */

template <class posTrait, class colTrait, class sizeTrait, class normalTrait, 
          class geoTrait>
struct drawObjects : public ParticlesDrawer 
{
    virtual void draw(Particles *part, DrawActionBase *action)
    {
        // some variables for faster access
        GeoPositionsPtr pos = part->getPositions();

        // init traits
        typename geoTrait::dataType geoData;
        geoTrait::init(part, action, geoData);

        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, action, normalData);

        typename posTrait::dataType posData, secPosData;
        posTrait::init(part, action, posData   , part->getPositions());
        posTrait::init(part, action, secPosData, part->getSecPositions());

        UInt32 length = pos->getSize();
        
        for(UInt32 i = 0; i < length; ++i)
        {
            if(geoTrait::particle (geoData,  i))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle (posData,  i))
                continue;

            if(posTrait::particle (secPosData,  i))
                continue;

            // calc the coordinate system
            
            Pnt3f &p  = posTrait   ::position(posData   );
            Pnt3f &sp = posTrait   ::position(secPosData);
            Vec3f &n  = normalTrait::normal  (normalData);
           
            Vec3f dz(sp - p);
            dz.normalize();

            Vec3f dx(n.cross(dz));
            if(dx.isZero())
            {
                dx=Vec3f(1,0,0).cross(dz);
                if(dx.isZero())
                {
                    dx=Vec3f(0,1,0).cross(dz);
                    if(dx.isZero())
                    {
                        dx=Vec3f(0,0,1).cross(dz);
                    }
                    else
                    {
                        dx.setValues(0,0,0);
                    }
                }
            }
            dx.normalize();

            Vec3f dy(dx.cross(dz));

            // now draw the geometry;
            geoTrait::draw(geoData, p, dx, dy, dz, 
                           sizeTrait::size(sizeData, i));
        }
    }
    
    virtual void drawIndexed(Particles *part, DrawActionBase *action, 
                             Int32 *index, UInt32 length)
    {
        // some variables for faster access
        GeoPositionsPtr pos = part->getPositions();

        // init traits
        typename geoTrait::dataType geoData;
        geoTrait::init(part, action, geoData);

        typename colTrait::dataType colData;
        colTrait::init(part, action, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, action, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, action, normalData);

        typename posTrait::dataType posData, secPosData;
        posTrait::init(part, action, posData   , part->getPositions());
        posTrait::init(part, action, secPosData, part->getSecPositions());

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > pos->getSize())
                continue;

            if(geoTrait::particle (geoData,  i))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle (posData,  i))
                continue;

            if(posTrait::particle (secPosData,  i))
                continue;

            // calc the coordinate system
            
            Pnt3f &p  = posTrait   ::position(posData   );
            Pnt3f &sp = posTrait   ::position(secPosData);
            Vec3f &n  = normalTrait::normal  (normalData);
           
            Vec3f dz(sp - p);
            dz.normalize();

            Vec3f dx(n.cross(dz));
            if(dx.isZero())
            {
                dx=Vec3f(1,0,0).cross(dz);
                if(dx.isZero())
                {
                    dx=Vec3f(0,1,0).cross(dz);
                    if(dx.isZero())
                    {
                        dx=Vec3f(0,0,1).cross(dz);
                    }
                    else
                    {
                        dx.setValues(0,0,0);
                    }
                }
            }
            dx.normalize();

            Vec3f dy(dx.cross(dz));

            // now draw the geometry;
            geoTrait::draw(geoData, p, dx, dy, dz, 
                           sizeTrait::size(sizeData, i));
        }
    }
};

/* Sorting functions */


struct sorter
{
    sorter() {}

    sorter(Real32 value, Int32 index)
    {
        _value=value;
        _index=index;
    }

    bool operator<(const sorter &a) const
    {
        if(_value < a._value)
            return true;

        return false;
    }

    Real32 _value;
    Int32  _index;
};

Int32 *Particles::calcIndex(DrawActionBase *action, UInt32 &len, 
                            Int32 *index)
{ 
    // some variables for faster access
    GeoPositionsPtr  pos     = getPositions();
    MFInt32         *indices = getMFIndices();
 
    // get ModelView matrix to define the direction vectors
    Matrix camera,toworld;
    action->getCamera()->getBeacon()->getToWorld(camera);
    action->getActNode()->getToWorld(toworld);
    toworld.invert();
    camera.multLeft(toworld);

    Pnt3f refpoint(camera[3].getValues());
    
    Pnt3f p,q;
    UInt32 size;
    
    if(indices->getSize() > 0)
    {
        size = indices->getSize();
    }
    else
    {
        size = pos->getSize();
    }
   
    vector<sorter> list(size);
    
    len = 0;
    UInt32 i;
    for(i = 0; i<size; i++)
    {
        if(indices->getSize() > 0)
        {
            if(indices->getValue(i) < 0 || 
               indices->getValue(i) > pos->getSize())
                continue;
                
            list[len]._index = indices->getValue(i);
        }
        else
        {
            list[len]._index = i;         
        }
        
        pos->getValue(p,i);
        
        list[len]._value = - refpoint.dist2(p);
        
        len++;
    }
    
    list.resize(len);
    sort(list.begin(),list.end());
    
    if(index == NULL)
        index=new Int32[len];
    
    for(i = 0; i<len; i++)
    {
        index[i] = list[i]._index;
    }
        
    return index;    
}


/** \brief Actions
 */

Action::ResultE Particles::draw(Action * action )
{
    DrawAction *a = dynamic_cast<DrawAction*>(action);
    Material::DrawFunctor func;

    func=osgTypedMethodFunctor1ObjPtr(&(*this), &Particles::doDraw);

    if(a->getMaterial() != NULL)
    {
        a->getMaterial()->draw(func, a);
    }
    else if ( getMaterial() != NullFC )
    {
        getMaterial()->draw( func, a );
    }
    else
    {
        FWARNING(("Particles::draw:: no material!\n"));;
    }
    return Action::Continue;
}

Action::ResultE Particles::doDraw(DrawActionBase * action)
{
    // some variables for faster access
    GeoPositionsPtr  pos  = getPositions();
    GeoColorsPtr     col  = getColors();
    GeoNormalsPtr    norm = getNormals();
    MFVec3f         *size = getMFSizes();
 
    if((size   ->getSize() > 1 && size   ->getSize() != pos->getSize())  ||
       (col  != NullFC && col->getSize()  != 1 &&
                          col->getSize()  != pos->getSize())       ||
       (norm != NullFC && norm->getSize() != 1 &&
                          norm->getSize() != pos->getSize())
      )
    {
        FWARNING(("Particles::draw: inconsistent attributes "
                    "(p:%d s:%d c:%d)!\n",
                    pos->getSize(), size->getSize(),
                    (col != NullFC)? (int)col->getSize() : -1));
        return Action::Continue;
    }

    ParticlesDrawer *drawer = findDrawer();
    
    if(drawer == NULL)
    {
        FWARNING(("Particles 0x%lx: couldn't find drawer!\n", this));
        return Action::Continue;;
    }
    
    Int32 *index = NULL;
    UInt32 length = 0;
    bool freeIndex = false;
    
    if(_sfDrawOrder.getValue()!=Particles::Any)
    {
        if(getDynamic())
        {
            index=calcIndex(action,length);
        }
        else
        {
            if(! getBsp().created())
            {
                getBsp().build(this);
            }
            Matrix modelview,toworld;
            action->getCamera()->getBeacon()->getToWorld(
                                                modelview);
            action->getActNode()->getToWorld(toworld);

            toworld.invert();
            modelview.mult(toworld);

            Pnt3f ref(modelview[3][0],modelview[3][1],
                      modelview[3][2]);
            Vec3f refvec(  modelview[2][0],modelview[2][1],
                      modelview[2][2]);  

            index = getBsp().traverse(ref,length);
        }
        freeIndex = true;
    }
    else if (getIndices().getSize() > 0)
    {
        index  = &getMFIndices()->getValues()[0];
        length = getIndices().getSize();
    }

    if(index != NULL)
    {
        drawer->drawIndexed(this,action,index,length);
    }
    else
    {
        drawer->draw(this,action);   
    }
    
    if(freeIndex)
        delete [] index;
        
    return Action::Continue;
}

Action::ResultE Particles::render(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Material::DrawFunctor func;
    func=osgTypedMethodFunctor1ObjPtr(this, &Particles::doDraw);

    Material* m = a->getMaterial();

    if(m == NULL)
    {
        if(getMaterial() != NullFC)
        {
            m = getMaterial().getCPtr();
        }
        else
        {
            fprintf(stderr, "Particles::render: no Material!?!\n");
            return Action::Continue;
        }
    }

    a->dropFunctor(func, m);

    return Action::Continue;
}

/*! find the drawer object for the actual configuration of parameters */

ParticlesDrawer *Particles::findDrawer(void)
{
    UInt8 mode;
    enum { part = 0, sing, none } size,normal,color,tex;
    
    mode = getMode();
    
    // find the parameters' use
    
    size =   (getSizes().getSize()      == getPositions()->getSize()) ? part :
             (getSizes().getSize()      == 1                        ) ? sing : 
                                                                        none;
    normal = (getNormals() != NullFC && 
              getNormals()->getSize()   == getPositions()->getSize()) ? part :
             (getNormals() != NullFC && 
              getNormals()->getSize()   == 1                        ) ? sing : 
                                                                        none;
    color =  (getColors() != NullFC && 
              getColors()->getSize()    == getPositions()->getSize()) ? part :
             (getColors() != NullFC && 
              getColors()->getSize()    == 1                        ) ? sing : 
                                                                       none;
    tex =    (getTextureZs().getSize()  == getPositions()->getSize()) ? part :
             (getTextureZs().getSize()  == 1                        ) ? sing : 
                                                                        none;
    
    // check if the used types are common cases
    
    bool normalIs3f = (getNormals()   != NullFC && 
                       getNormals()->getFormat()      == GL_FLOAT);
                        
    bool colorIs3f  = (getColors()    != NullFC && 
                       getColors()->getFormat()       == GL_FLOAT && 
                       getColors()->getDimension()    == 3);
                        
    bool posIs3f    = (getPositions() != NullFC && 
                       getPositions()->getFormat()    == GL_FLOAT && 
                       getPositions()->getDimension() == 3);
    
    // now find the drawer
    
    // main difference: mode, as only a subset of the attributes is used
    // in the different modes
    
    // this is where to add fast pathes...
    // don't go overboard, as every path adds code, and code bloat is
    // easily obtained here.
    
    switch(mode)
    {
    case Points:
    {
        static ParticlesDrawer *fallback = 
                    new drawPoints<PosTraitGeneric,ColTraitGeneric,
                                   TexTraitGeneric,SizeTraitGeneric>;
        
        return fallback;
    }
        
    case Lines:
    {
        static ParticlesDrawer *fallback = 
                    new drawLines<PosTraitGeneric,ColTraitGeneric,
                                  TexTraitGeneric,SizeTraitGeneric>;
        
        return fallback;
    }
    
    case ViewDirQuads:
    {
        static ParticlesDrawer *fallback = 
                    new drawViewDirQuads<PosTraitGeneric,ColTraitGeneric,
                                         TexTraitGeneric,SizeTraitGeneric>;
        
        if(posIs3f && tex == none && size != none)
        {
            static ParticlesDrawer *pumps[] = {
              new drawViewDirQuads<PosTrait3f,ColTraitParticle,
                                   TexTraitNone,SizeTraitParticle>,
              new drawViewDirQuads<PosTrait3f,ColTraitSingle,
                                   TexTraitNone,SizeTraitParticle>,
              new drawViewDirQuads<PosTrait3f,ColTraitNone,
                                   TexTraitNone,SizeTraitParticle>,
                                   
              new drawViewDirQuads<PosTrait3f,ColTraitParticle,
                                   TexTraitNone,SizeTraitSingle>,
              new drawViewDirQuads<PosTrait3f,ColTraitSingle,
                                   TexTraitNone,SizeTraitSingle>,
              new drawViewDirQuads<PosTrait3f,ColTraitNone,
                                   TexTraitNone,SizeTraitSingle>,
              };
              
              return pumps[size * 3 + color];
        }
        
        return fallback;
    }
    
    case ViewerQuads:
    {
        static ParticlesDrawer *fallback = 
                    new drawViewerQuads<PosTraitGeneric,ColTraitGeneric,
                                         TexTraitGeneric,SizeTraitGeneric>;
        
        if(posIs3f && tex == none && size != none)
        {
            static ParticlesDrawer *pumps[] = {
              new drawViewerQuads<PosTrait3f,ColTraitParticle,
                                  TexTraitNone,SizeTraitParticle>,
              new drawViewerQuads<PosTrait3f,ColTraitSingle,
                                  TexTraitNone,SizeTraitParticle>,
              new drawViewerQuads<PosTrait3f,ColTraitNone,
                                  TexTraitNone,SizeTraitParticle>,
                                   
              new drawViewerQuads<PosTrait3f,ColTraitParticle,
                                  TexTraitNone,SizeTraitSingle>,
              new drawViewerQuads<PosTrait3f,ColTraitSingle,
                                  TexTraitNone,SizeTraitSingle>,
              new drawViewerQuads<PosTrait3f,ColTraitNone,
                                  TexTraitNone,SizeTraitSingle>,
              };
              
              return pumps[size * 3 + color];
        }
        
        return fallback;
    }
    
    case Arrows:
    {
        static ParticlesDrawer *fallback = 
                    new drawObjects<PosTraitGeneric,ColTraitGeneric, 
                                    SizeTraitGeneric,NormalTraitGeneric,
                                    GeoTraitArrow>;
        
        return fallback;
    }
    
    };

    
    if (normal) return NULL; // make picky compilers happy
    return NULL;
}
 
