/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include "OSGLight.h"

OSG_USING_NAMESPACE

/*! \class osg::Light
    \ingroup GrpSystemNodeCoresLights
    
    Light is the base class for all the light source nodes.
    It contains the field for the general light source attributes 
    (AmbientColor, DiffuseColor, SpecularColor, Beacon). The Beacon 
    defines the reference coordinate system for the lightsource, while 
    the position in the graph defines the objects that are lit.
*/


/*-------------------------------------------------------------------------*/
/*                                Set                                      */

void Light::setAmbient(Real32 rRed, 
                       Real32 rGreen, 
                       Real32 rBlue, 
                       Real32 rAlpha)
{
    _sfAmbient.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void Light::setDiffuse(Real32 rRed, 
                       Real32 rGreen, 
                       Real32 rBlue, 
                       Real32 rAlpha)
{
    _sfDiffuse.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void Light::setSpecular(Real32 rRed, 
                        Real32 rGreen, 
                        Real32 rBlue, 
                        Real32 rAlpha)
{
    _sfSpecular.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

/*-------------------------------------------------------------------------*/
/*                             Chunk                                       */

LightChunkPtr Light::getChunk(void)
{
    return _pChunk;
}

void Light::makeChunk(void)
{
    if(_pChunk == NullFC)
    {
        _pChunk = LightChunk::create();
    }

    _pChunk->setAmbient (getAmbient ());
    _pChunk->setDiffuse (getDiffuse ());
    _pChunk->setSpecular(getSpecular());
}

/*-------------------------------------------------------------------------*/
/*                             Sync                                     */

void Light::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void Light::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Light::Light(void) :
     Inherited(),
    _pChunk   (NullFC)
{
}

Light::Light(const Light &source) :
     Inherited(source),
    _pChunk   (source._pChunk)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Light::~Light(void)
{
    if(_pChunk != NullFC)
        subRefCP(_pChunk);
}

/*-------------------------------------------------------------------------*/
/*                               Drawing                                   */
    
Action::ResultE Light::drawEnter(Action *action)
{
    DrawAction *da    = dynamic_cast<DrawAction *>(action);
    GLenum      light = GL_LIGHT0 + da->getLightCount();
    
    da->incLightCount();
    
    glEnable (light);
    
    glLightfv(light, GL_DIFFUSE , _sfDiffuse. getValue().getValuesRGBA());
    glLightfv(light, GL_AMBIENT , _sfAmbient. getValue().getValuesRGBA());
    glLightfv(light, GL_SPECULAR, _sfSpecular.getValue().getValuesRGBA());

    glLightf( light, 
              GL_CONSTANT_ATTENUATION, 
             _sfConstantAttenuation.getValue() );
    glLightf( light,
              GL_LINEAR_ATTENUATION,   
             _sfLinearAttenuation.getValue()   );
    glLightf( light,
              GL_QUADRATIC_ATTENUATION,   
             _sfQuadraticAttenuation.getValue());

    // add the matrix to get into the beacon's coordinate system onto the stack

    Matrix fromworld;
    Matrix tobeacon;

    action->getActNode()->getToWorld(fromworld);
    fromworld.invert();

    NodePtr beacon = getBeacon();

    if(beacon == NullFC)
    {
        SINFO << "draw: no beacon set!" << std::endl;

        glPushMatrix();
    }
    else
    {
        getBeacon()->getToWorld(tobeacon);
    
        tobeacon.mult(fromworld);
    
        glPushMatrix();
        glMultMatrixf(tobeacon.getValues());
    }
    
    da->selectVisibles();
    
    return Action::Continue;
}
    
Action::ResultE Light::drawLeave(Action *action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);
     
    da->decLightCount();

    GLenum light = GL_LIGHT0 + da->getLightCount();
   
    glDisable(light);
   
    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

Action::ResultE Light::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    // ok we can cull the light only when it is invisible and has
    // no LightEnv parent and local lights are enabled!
    if (pAction->pushVisibility())
    {
        if(pAction->getLightEnvsLightsState().empty() &&
           pAction->selectVisibles() == 0 &&
           pAction->getLocalLights())
        {
            pAction->popVisibility();
            return Action::Skip;
        }
    }

    pAction->dropLight(this);

    return Action::Continue;
}

Action::ResultE Light::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->undropLight(this);

    pAction->popVisibility();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

//! initialize the static features of the class, e.g. action callbacks

void Light::initMethod(void)
{
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGLIGHT_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGLIGHT_INLINE_CVSID;
}

