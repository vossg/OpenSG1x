#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGTypedFunctors.h>
#include <OSGQuaternion.h>
#include <OSGDrawAction.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

#include <OSGBackground.h>
#include <OSGForeground.h>
#include <OSGImage.h>

#include <OSGLight.h>

#include "OSGTreeRenderer.h"
#include "OSGShadowViewport.h"

#define PI 3.14159265f

OSG_USING_NAMESPACE

TreeRenderer::TreeRenderer(void)
{
}

TreeRenderer::TreeRenderer(ShadowViewport *source)
{
	shadowVP = source;
}


TreeRenderer::~TreeRenderer(void)
{
}
 

