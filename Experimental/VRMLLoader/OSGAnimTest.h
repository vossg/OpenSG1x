#ifndef __VRML2ANIM_H
#define __VRML2ANIM_H

#include "OSGAnimation.h"
#include "OSGGenericInterpolator.h"

OSG_BEGIN_NAMESPACE

/** Add/Create a new animation to the list. */
OSG::Animation *addAnim(InterpolatorBase::InterpolType type, 
                        char *name, char *objname,
                        int destNr, float duration );
    
OSG_END_NAMESPACE

#endif //__VRML2ANIM_H
