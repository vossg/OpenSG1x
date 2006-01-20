/*!
 * \class OSGRenderOptions
 * \brief
 * \author Andreas Zieringer AMZ GmbH
 */

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGGLEXT.h>

#include "OSGRenderOptions.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE


/*!
 * \brief
 * \param
 * \return
 */
RenderOptions::RenderOptions(void) :
    Inherited()
{
}

/*!
 * \brief
 * \param
 * \return
 */
RenderOptions::RenderOptions(const RenderOptions &source) :
    Inherited(source)
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

void RenderOptions::activateOptions(RenderAction *action)
{
    if(_changed & PolygonModeFieldMask)
    {
        glPolygonMode(GL_FRONT_AND_BACK, getPolygonMode());
    }
    if(_changed & BackfaceCullingFieldMask)
    {
        if(getBackfaceCulling())
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
        else
        {
            glDisable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        } 
    }
    if(_changed & CorrectTwoSidedLightingFieldMask)
    {
        action->setCorrectTwoSidedLighting(getCorrectTwoSidedLighting());
    }
    if(_changed & TwoSidedLightingFieldMask)
    {
        if(getTwoSidedLighting())
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        else
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    }
    if(_changed & SortTransFieldMask)
    {
        action->setSortTrans(getSortTrans());
    }
    if(_changed & ZWriteTransFieldMask)
    {
        action->setZWriteTrans(getZWriteTrans());
    }
    if(_changed & LocalLightsFieldMask)
    {
        action->setLocalLights(getLocalLights()); 
    }
    if(_changed & SpecTexLightingFieldMask)
    {
        // detect OpenGL version.
        std::string vstr = (const char *) glGetString(GL_VERSION);
        // remove last .x
        vstr = vstr.substr(0, 3);
        double opengl_version = atof(vstr.c_str()); 
        if(opengl_version >= 1.2f)
        {
            if(getSpecTexLighting())
                glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
            else
                glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
        } 
    }
    _changed = 0;
}
