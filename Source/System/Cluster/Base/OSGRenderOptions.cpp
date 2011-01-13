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

#include <OSGConfig.h>
#include <OSGGLEXT.h>

#include "OSGRenderOptions.h"
#include "OSGRenderAction.h"

// the following tokens are not defined under WIN
#ifndef GL_NV_multisample_filter_hint
# define GL_MULTISAMPLE_FILTER_HINT_NV     0x8534
#endif

#ifndef GL_VERSION_1_3
# define GL_MULTISAMPLE                    0x809D
# define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
# define GL_SAMPLE_ALPHA_TO_ONE            0x809F
# define GL_SAMPLE_COVERAGE                0x80A0
# define GL_SAMPLE_BUFFERS                 0x80A8
# define GL_SAMPLES                        0x80A9
# define GL_SAMPLE_COVERAGE_VALUE          0x80AA
# define GL_SAMPLE_COVERAGE_INVERT         0x80AB
# define GL_MULTISAMPLE_BIT                0x20000000
#endif

OSG_USING_NAMESPACE


/*!
 * \brief
 * \param
 * \return
 */
RenderOptions::RenderOptions(void) :
    Inherited(),
    _changed(0),
    _last_changed(0),
    _gl_version(0.0f),
    _polygon_mode(GL_FILL),
    _backface_culling(false),
    _two_sided_lighting(false),
    _spec_tex_lighting(false)
{
}

/*!
 * \brief
 * \param
 * \return
 */
RenderOptions::RenderOptions(const RenderOptions &source) :
    Inherited(source),
    _changed(source._changed),
    _last_changed(source._last_changed),
    _gl_version(source._gl_version),
    _polygon_mode(source._polygon_mode),
    _backface_culling(source._backface_culling),
    _two_sided_lighting(source._two_sided_lighting),
    _spec_tex_lighting(source._spec_tex_lighting)
{
}

/*!
 * \brief
 * \param
 * \return
 */
RenderOptions::~RenderOptions(void)
{
}

/*!
 * \brief
 * \param
 * \return
 */
void RenderOptions::initMethod (void)
{
}

/*!
 * \brief
 * \param
 * \return
 */
void RenderOptions::changed(BitVector whichField, UInt32 origin)
{
    _changed |= whichField;
    Inherited::changed(whichField, origin);
}

void RenderOptions::setWireframe( bool value )
{
    if(value)
        setPolygonMode(GL_LINE);
    else
        setPolygonMode(GL_FILL);
}

bool RenderOptions::getWireframe( void )
{
    return getPolygonMode() == GL_LINE;
}

BitVector RenderOptions::getChanged( void )
{
    return _changed;
}

BitVector RenderOptions::getLastChanged( void )
{
    return _last_changed;
}

void RenderOptions::activateOptions(RenderAction *action)
{
    if(_gl_version == 0.0f)
    {
        // detect OpenGL version.
        std::string vstr = 
            reinterpret_cast<const char *>(glGetString(GL_VERSION));

        // remove last .x
        vstr = vstr.substr(0, 3);
        _gl_version = atof(vstr.c_str());
    }

    if(_changed & PolygonModeFieldMask)
        _polygon_mode = getPolygonMode();

    if(_changed & BackfaceCullingFieldMask)
        _backface_culling = getBackfaceCulling();

    if(_changed & CorrectTwoSidedLightingFieldMask)
        action->setCorrectTwoSidedLighting(getCorrectTwoSidedLighting());

    if(_changed & TwoSidedLightingFieldMask)
        _two_sided_lighting = getTwoSidedLighting();
    
    if(_changed & SortTransFieldMask)
        action->setSortTrans(getSortTrans());

    if(_changed & ZWriteTransFieldMask)
        action->setZWriteTrans(getZWriteTrans());

    if(_changed & LocalLightsFieldMask)
        action->setLocalLights(getLocalLights());

    if(_changed & SpecTexLightingFieldMask)
        _spec_tex_lighting = getSpecTexLighting();

    if(_changed & OcclusionCullingFieldMask)
        action->setOcclusionCulling(getOcclusionCulling());

    if(_changed & OcclusionCullingModeFieldMask)
        action->setOcclusionCullingMode(getOcclusionCullingMode());

    if(_changed & OcclusionCullingPixelsFieldMask)
        action->setOcclusionCullingPixels(getOcclusionCullingPixels());

    if(_changed & OcclusionCullingThresholdFieldMask)
        action->setOcclusionCullingThreshold(getOcclusionCullingThreshold());

    if(_changed & SmallFeatureCullingFieldMask)
        action->setSmallFeatureCulling(getSmallFeatureCulling());

    if(_changed & SmallFeatureCullingModeFieldMask)
        action->setSmallFeatureCullingMode(getSmallFeatureCullingMode());

    if(_changed & SmallFeaturePixelsFieldMask)
        action->setSmallFeaturePixels(getSmallFeaturePixels());

    if(_changed & SmallFeatureThresholdFieldMask)
        action->setSmallFeatureThreshold(getSmallFeatureThreshold());

    if(_changed & FrustumCullingFieldMask)
        action->setFrustumCulling(getFrustumCulling());

    if(_changed & DepthOnlyPassFieldMask)
        action->setDepthOnlyPass(getDepthOnlyPass());

    // we update the gl stuff each frame.
    glPolygonMode(GL_FRONT_AND_BACK, _polygon_mode);

    if(_backface_culling)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
    {
        glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } 

    // activate multi-sample buffer
    if ((getMultiSample() > 1) && (getMultiSampleFilterMode())) 
    {
        GLint bufs = 0, samples = 0;
        glGetIntegerv (GL_SAMPLE_BUFFERS, &bufs);
        glGetIntegerv (GL_SAMPLES, &samples);
        
        if (bufs > 1 || (samples != getMultiSample())) 
        {
            static bool firstTime = true;
            if (firstTime) 
            {
              FWARNING (( "Invalid multi-sample window setting: %d/%d\n",
                          bufs, samples ));
			  firstTime = false;
            }
        }

        glEnable ( GL_MULTISAMPLE );
        glHint   ( GL_MULTISAMPLE_FILTER_HINT_NV, 
                   getMultiSampleFilterMode () );
    }
    else 
      glDisable ( GL_MULTISAMPLE );
    
    if(_two_sided_lighting)
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    else
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    if(_gl_version >= 1.2f)
    {
        if(_spec_tex_lighting)
            glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
        else
            glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
    }
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, getLightModelAmbient().getValuesRGBA());

    if ( getFogMode() ) {
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, getFogMode());
        glFogf(GL_FOG_DENSITY, getFogDensity());
        glFogf(GL_FOG_START, getFogRange().x());
        glFogf(GL_FOG_END, getFogRange().y());
        glFogfv(GL_FOG_COLOR, getFogColor().getValuesRGBA());
    }
	else {
		glDisable(GL_FOG);
	}

    _last_changed = _changed;
    _changed = 0;
}
