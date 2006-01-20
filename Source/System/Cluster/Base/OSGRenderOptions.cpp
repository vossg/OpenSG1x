/*!
 * \class OSGRenderOptions
 * \brief
 * \author Andreas Zieringer AMZ GmbH
 */

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGRenderOptions.h"

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
    Inherited::changed(whichField, origin);
}

