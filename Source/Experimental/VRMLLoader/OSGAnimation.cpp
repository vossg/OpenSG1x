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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGAnimation.h"
#include <OSGAttachment.h>
#include <OSGSimpleAttachments.h>

extern "C"
{
extern int v2a_parse(void);

extern int   v2aLineNumber;
extern float v2aDuration;

//extern OSG::Animation* _animations;
}

extern FILE *v2a_in;

//extern FILE *v2a_in;
//extern int   v2LineNumber;
//extern int   v2a_parse(void);

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

Animation* Animation::_theAnim = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

Animation* Animation::getAnim(void) 
{ 
    if(_theAnim == NULL)
    {
        std::cerr << "GlobalAnimation is NULL. Creating one.\n";

        _theAnim = new Animation();
    }
    
    return _theAnim; 
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------- constructor ----------------------------------*/

Animation::Animation(void) :
    _currentInterpol(-1)        
{
}

Animation::~Animation(void)
{
}
/*-------------------------- other ---------------------------------------*/

void Animation::addInterpolator(InterpolatorBase* interpol)
{
    std::cerr << "Animation::addInterpolator() ";

    _interpols.push_back(interpol);
    
    _currentInterpol = _interpols.size() - 1;

    std::cerr << _interpols.size() << " " << _currentInterpol << std::endl;
}

InterpolatorBase* Animation::currentInterpolator(void) 
{ 
    InterpolatorBase *returnValue = NULL;

    if(_currentInterpol != -1)
    {
        returnValue = _interpols[_currentInterpol]; 
    }

    return returnValue;
}

int Animation::getNrOfInterpols() const
{
    return _interpols.size();
}

InterpolatorBase* Animation::getInterpolator(UInt32 index)
{
    if(index < _interpols.size())
    {
        return _interpols[index];
    }
    else
    {
        return NULL;
    }
}

bool Animation::parse(const std::string& filename)
{
    FILE *f = fopen(filename.c_str(), "r");
    
    if(f == NULL)
    {
        return false;
    }
   
    ::v2a_in        = f;
    ::v2aLineNumber = 1;

    ::v2a_parse();
    
    return true;
}

/*! \brief Traverses the scenegraph and checks for ComponentTransforms.
    
    If there are any transformations with viewpoint attachment these
    are stored in a global vector. These transformations act as camera 
    beacons.
    
    \todo Perhaps add code for moving the collected transformations 
    under the root node of the scenegraph.
 */ 
    
Animation::InterpolatorVec Animation::findInterpolator(const Char8 *szName)
{
    std::vector<InterpolatorBase *>::iterator interpolIt;
    std::vector<InterpolatorBase *>::iterator interpolEnd = _interpols.end();

    InterpolatorVec returnValue;

    for(  interpolIt  = _interpols.begin(); 
          interpolIt !=  interpolEnd;
        ++interpolIt                      )
    {
        if(strcmp(szName, 
                  (*interpolIt)->getTargetName().c_str())==0)
        {
            std::cerr << "Got "
                      << (*interpolIt)
                      << " for "
                      << szName 
                      << std::endl;

            returnValue.push_back((*interpolIt));
        }
    }

    return returnValue;
}

void Animation::resolveTransform(      ComponentTransformPtr  pTransform, 
                                 const Char8            *szName)
{
    InterpolatorVec           vInterpol   = findInterpolator(szName);
    InterpolatorVec::iterator interpolIt  = vInterpol.begin ();
    InterpolatorVec::iterator interpolEnd = vInterpol.end   ();

    for(; interpolIt != interpolEnd; ++interpolIt)
    {
        (*interpolIt)->setTargetTransform(pTransform);
    }
}

OSG::Action::ResultE animResolver(OSG::CNodePtr &, OSG::Action *action)
{
    OSG::NodePtr            node        = action->getActNode();
    OSG::ComponentTransformPtr   vrmlTrans   = OSG::NullFC;
    OSG::NamePtr            namePtr;
    std::string             targetName;
                    
    vrmlTrans = OSG::ComponentTransformPtr::dcast(node->getCore());
        
    if(!vrmlTrans)
    {
        std::cerr << "ERROR! The Node " << node << " does not have a core.\n";
    }
    else
    {
        namePtr = OSG::NamePtr::dcast(
            node->findAttachment(OSG::Name::getClassType().getGroupId()) ); 

        if(namePtr != NullFC)
        {
            OSG::Animation::getAnim()->resolveTransform(
                vrmlTrans, 
                namePtr->getFieldPtr()->getValue().c_str());
        }
    }
    
    return OSG::Action::Continue;
}

void Animation::resolve(NodePtr pRoot)
{
    if(pRoot == NullFC)
        return;

    std::cerr << "Checking interpolator target nodes..." << std::endl;
    
#ifndef OSG_NOFUNCTORS

    OSG::Action *act2;  

    act2 = OSG::Action::create (                                      );   
    act2->registerEnterFunction(OSG::ComponentTransform::getClassType(),
                                OSG::osgTypedFunctionFunctor2CPtrRef<
                                     OSG::Action::ResultE, 
                                     OSG::CNodePtr,
                                     OSG::Action *         >(animResolver));      
    act2->apply(pRoot);

#endif
    
    std::cerr << "done !\n";    
}

void Animation::setRelTime(Time relTime)
{
    for(OSG::Int32 i = 0; i < _interpols.size(); ++i)
    {
        _interpols[i]->setTime(relTime);
    }
}

OSG_END_NAMESPACE


