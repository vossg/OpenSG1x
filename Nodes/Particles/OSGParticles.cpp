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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGMaterial.h>
#include <OSGGeoPropPtrs.h>

#include "OSGParticles.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGParticles.cpp,v 1.2 2002/01/04 18:29:39 jbehr Exp $";
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
    DrawAction * da = dynamic_cast<DrawAction *>(action);

    // some variables for faster access
    GeoPositionsPtr  pos  = getPositions();
    GeoColorsPtr     col  = getColors();
    MFVec3f         *size = getMFSizes();

    if((size->getSize() > 1 && size->getSize() != pos->getSize()) ||
       (col != NullFC && col->getSize() != 1 &&
                         col->getSize() != pos->getSize())
       )
    {
            SWARNING << "Particles::draw: inconsistent attributes!" << endl;
            return Action::Continue;
    }

    // get ModelView matrix to define the direction vectors
    Matrix modelview;
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)modelview.getValues());

    modelview.transpose();

    // Direction vectors
    Vec4f  d1, d2, d3, d4;

    d1 = -1.0f * modelview[0] + -1.0f * modelview[1];
    d2 =  1.0f * modelview[0] + -1.0f * modelview[1];
    d3 =  1.0f * modelview[0] +  1.0f * modelview[1];
    d4 = -1.0f * modelview[0] +  1.0f * modelview[1];

    glBegin(GL_QUADS);

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
        glColor3fv( (GLfloat*) col->getValue(0).getValueRef() );
    }

    for(UInt32 i = 0; i < pos->getSize(); i++)
    {
        if(col != NullFC && col->getSize() == pos->getSize())
        {
            col->getValue(c, i);
            glColor3fv((GLfloat*) c.getValueRef());
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

