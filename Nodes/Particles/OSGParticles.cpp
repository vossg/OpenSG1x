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

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGParticles.cpp,v 1.5 2002/01/10 21:14:10 dirk Exp $";
    static char cvsid_hpp[] = OSGPARTICLES_HEADER_CVSID;
    static char cvsid_inl[] = OSGPARTICLES_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::Particles

Particles are small graphical objects that are primarily defined by their
position. Other attributes like color and size can be defined, too.

Usually they are rendered as viewer-aligned quads, but other modes are
possible.
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
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,
                                ParticlesPtr,
                                Action *>(&Particles::draw));

    RenderAction::registerEnterDefault( getClassType(),
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,
                                ParticlesPtr,
                                Action *>(&Particles::render));
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


// pump functions

static void drawLinesSingleSize(Particles *part, DrawActionBase *)
{
    // some variables for faster access
    GeoPositionsPtr  pos  = part->getPositions();
    GeoPositionsPtr  secpos  = part->getSecPositions();
    GeoColorsPtr     col  = part->getColors();
    MFVec3f         *size = part->getMFSizes();

    // draw the particles
    Pnt3f   p;
    Real32  s;
    Color3f c;   // !!! TODO Colors with alpha are not handled yet

    if(size->getSize() == 0)
    {
        s = 1;
    }
    else if(size->getSize() == 1)
    {
        s = size->getValue(0)[0];
    }
    else
        s = 1;

    GLfloat lw;
    glGetFloatv(GL_LINE_WIDTH, &lw);
    glLineWidth(s);
    
    if(col != NullFC && col->getSize() == 1)
    {
        glColor3fv( (GLfloat*) col->getValue(0).getValuesRGB() );
    }

    glBegin(GL_LINES);
    
    for(UInt32 i = 0; i < pos->getSize(); i++)
    {
        if(col != NullFC && col->getSize() == pos->getSize())
        {
            col->getValue(c, i);
            glColor3fv((GLfloat*) c.getValuesRGB());
        }

        pos->getValue(p, i);
        glVertex3fv((GLfloat*)p.getValues());
        secpos->getValue(p, i);
        glVertex3fv((GLfloat*)p.getValues());
    }
      
    glEnd();
    
    if(osgabs(s-lw)>Eps)
        glLineWidth(lw);
}

static void drawViewDirQuads(Particles *part, DrawActionBase *action)
{

    // some variables for faster access
    GeoPositionsPtr  pos  = part->getPositions();
    GeoColorsPtr     col  = part->getColors();
    MFVec3f         *size = part->getMFSizes();

    // get ModelView matrix to define the direction vectors
    Matrix modelview,toWorld;
    action->getCamera()->getBeacon()->getToWorld(modelview);
    // transforms can't work yet, getActNode returns garbage for RenderAction
    //action->getActNode()->getToWorld(toWorld);
    modelview.invert();
    //toWorld.invert();
    //modelview.mult(toWorld);
    modelview.transpose();

    // Direction vectors
    Vec4f  d1, d2, d3, d4;

    d1 = -1.0f * modelview[0] + -1.0f * modelview[1];
    d2 =  1.0f * modelview[0] + -1.0f * modelview[1];
    d3 =  1.0f * modelview[0] +  1.0f * modelview[1];
    d4 = -1.0f * modelview[0] +  1.0f * modelview[1];

    // draw the particles
    Pnt3f   p;
    Real32  s;
    Color3f c;   // !!! TODO Colors with alpha are not handled yet

    if(size->getSize() == 0)
    {
        s = 0.5f;
    }
    else if(size->getSize() == 1)
    {
        s = size->getValue(0)[0]/2.f;
    }

    if(col != NullFC && col->getSize() == 1)
    {
        glColor3fv( (GLfloat*) col->getValue(0).getValuesRGB() );
    }

    glBegin(GL_QUADS);

    for(UInt32 i = 0; i < pos->getSize(); i++)
    {
        if(col != NullFC && col->getSize() == pos->getSize())
        {
            col->getValue(c, i);
            glColor3fv((GLfloat*) c.getValuesRGB());
        }

        if(size->getSize() == pos->getSize())
            s = size->getValue(i)[0]/2.f;

        pos->getValue(p, i);

        glTexCoord2f(0,0);
        glVertex3f( p[0] + d1[0]*s, p[1] + d1[1]*s, p[2] + d1[2]*s);

        glTexCoord2f(1,0);
        glVertex3f( p[0] + d2[0]*s, p[1] + d2[1]*s, p[2] + d2[2]*s);

        glTexCoord2f(1,1);
        glVertex3f( p[0] + d3[0]*s, p[1] + d3[1]*s, p[2] + d3[2]*s);

        glTexCoord2f(0,1);
        glVertex3f( p[0] + d4[0]*s, p[1] + d4[1]*s, p[2] + d4[2]*s);
    }

    glEnd();
}

static void drawViewDirQuadsIndexed(Particles *part, DrawActionBase *action,
    Int32 *index, UInt32 length)
{

    // some variables for faster access
    GeoPositionsPtr  pos  = part->getPositions();
    GeoColorsPtr     col  = part->getColors();
    MFVec3f         *size = part->getMFSizes();
    MFReal32        *texzs= part->getMFTextureZs();

    // get ModelView matrix to define the direction vectors
    Matrix modelview;
    action->getCamera()->getBeacon()->getToWorld(modelview);
    modelview.invert();
    modelview.mult(action->getActNode()->getToWorld());
    modelview.transpose();

    // Direction vectors
    Vec4f  d1, d2, d3, d4;

    d1 = -1.0f * modelview[0] + -1.0f * modelview[1];
    d2 =  1.0f * modelview[0] + -1.0f * modelview[1];
    d3 =  1.0f * modelview[0] +  1.0f * modelview[1];
    d4 = -1.0f * modelview[0] +  1.0f * modelview[1];

    // draw the particles
    Pnt3f   p;
    Real32  s;
    Color3f c;   // !!! TODO Colors with alpha are not handled yet
    Real32  z;
    
    if(size->getSize() == 0)
    {
        s = 0.5f;
    }
    else if(size->getSize() == 1)
    {
        s = size->getValue(0)[0]/2.f;
    }
    
    if(texzs->getSize() == 0)
    {
        z = 0.f;
    }
    else if(texzs->getSize() == 1)
    {
        z = texzs->getValue(0);
    }

    if(col != NullFC && col->getSize() == 1)
    {
        glColor3fv( (GLfloat*) col->getValue(0).getValuesRGB() );
    }

    glBegin(GL_QUADS);

    Int32 i;
    for(UInt32 ii = 0; ii < length; ++ii)
    {
        i = index[ii];
        
        if(i < 0 || i > pos->getSize())
            continue;
            
        if(col != NullFC && col->getSize() == pos->getSize())
        {
            col->getValue(c, i);
            glColor3fv((GLfloat*) c.getValuesRGB());
        }

        if(size->getSize() == pos->getSize())
            s = size->getValue(i)[0]/2.f;

        if(texzs->getSize() == pos->getSize())
            z = texzs->getValue(i);

        pos->getValue(p, i);

        glTexCoord3f(0, 0, z);
        glVertex3f( p[0] + d1[0]*s, p[1] + d1[1]*s, p[2] + d1[2]*s);

        glTexCoord3f(1, 0, z);
        glVertex3f( p[0] + d2[0]*s, p[1] + d2[1]*s, p[2] + d2[2]*s);

        glTexCoord3f(1, 1, z);
        glVertex3f( p[0] + d3[0]*s, p[1] + d3[1]*s, p[2] + d3[2]*s);

        glTexCoord3f(0, 1, z);
        glVertex3f( p[0] + d4[0]*s, p[1] + d4[1]*s, p[2] + d4[2]*s);
    }

    glEnd();
}

static void drawArrows(Particles *part, DrawActionBase *)
{
    // some variables for faster access
    GeoPositionsPtr  pos     = part->getPositions();
    GeoPositionsPtr  secpos  = part->getSecPositions();
    GeoColorsPtr     col     = part->getColors();
    GeoNormalsPtr    norm    = part->getNormals();
    MFVec3f         *size    = part->getMFSizes();

    // draw the particles
    Pnt3f   p,sp;
    Color3f c;   // !!! TODO Colors with alpha are not handled yet
    Vec3f   s;
    Vec3f   n;
    
    if(size->getSize() == 0)
    {
        s.setValues(1,1,1);
    }
    else if(size->getSize() == 1)
    {
        s=size->getValue(0);
    }
    
    if(norm->getSize() == 0)
    {
        n.setValues(0,1,0);
    }
    else if(norm->getSize() == 1)
    {
        norm->getValue(n,0);
        n.normalize();
    }

    if(col != NullFC && col->getSize() == 1)
    {
        glColor3fv( (GLfloat*) col->getValue(0).getValuesRGB() );
    }

    for(UInt32 i = 0; i < pos->getSize(); i++)
    {
        if(col != NullFC && col->getSize() == pos->getSize())
        {
            col->getValue(c, i);
            glColor3fv((GLfloat*) c.getValuesRGB());
        }

        if(norm != NullFC && norm->getSize() == pos->getSize())
        {
            norm->getValue(n,i);
            n.normalize();
        }

        if(size->getSize() == pos->getSize())
            s=size->getValue(i);

        pos->getValue(p, i);
        secpos->getValue(sp, i);

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

}

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
    Matrix modelview;
    action->getCamera()->getBeacon()->getToWorld(modelview);
    modelview.invert();
    //modelview.mult(actnode->getToWorld());
    //modelview.transpose();
    
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
    for(UInt32 i = 0; i<size; i++)
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
        
        modelview.mult(p);      // !!! optimize me. transform the viewer into
                                // the local coord system instead. 
        
        list[len]._value = p[2];
        
        len++;
    }
    
    list.resize(len);
    sort(list.begin(),list.end());
    
    if(index == NULL)
        index=new Int32[len];
    
    for(UInt32 i=0; i<len; i++)
    {
        index[i]=list[i]._index;
    }
        
    return index;    
}


/** \brief Actions
 */

Action::ResultE Particles::draw(Action * action )
{
    DrawAction *a = dynamic_cast<DrawAction*>(action);
    Material::DrawFunctor func;

    func=osgMethodFunctor1Ptr(&(*this), &Particles::doDraw);

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
        FWARNING(("Particles::draw: inconsistent attributes (%d %d %d)!",
                    pos->getSize(), size->getSize(),
                    (col != NullFC)? col->getSize() : -1));
        return Action::Continue;
    }

    switch(_sfMode.getValue())
    {
    case Lines:         drawLinesSingleSize(this, action);
                        break;
    case ViewDirQuads:  if(_sfDrawOrder.getValue()!=Particles::Any)
                        {
                            Int32 *index;
                            UInt32 length = pos->getSize();
                            
                            if(getDynamic())
                            {
                                index=calcIndex(action,length);
                            }
                            else
                            {
                                if(! getBsp().created())
                                {
                                    getBsp().build(this);
                                    
                                    static Bool dodump=false;
                                    if(dodump)
                                        getBsp().dump();
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
                            drawViewDirQuadsIndexed(this, action, index, length);
                            delete [] index;
                        }
                        else if (getIndices().getSize() > 0)
                        {
                            Int32 *index;
                            UInt32 length = pos->getSize();
                            
                            index=calcIndex(action,length);
                            drawViewDirQuadsIndexed(this, action, index, length);
                        }
                        else
                        {
                            drawViewDirQuads(this, action);
                        }
                        break;
    case Arrows:        drawArrows(this, action);
                        break;
    default:            FWARNING(("Particles::doDraw: unknown mode %d!\n",
                                  _sfMode.getValue()));
                        break;  
    }
   
    return Action::Continue;
}

Action::ResultE Particles::render(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Material::DrawFunctor func;
    func=osgMethodFunctor1Ptr(this, &Particles::doDraw);

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
