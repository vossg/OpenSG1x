
#include "OSGStateAwareIterator.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

StateAwareIterator::~StateAwareIterator(void)
{
}

void
StateAwareIterator::receiveActorAdd(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorAdd(pActor, uiActorId);
}
void
StateAwareIterator::receiveActorSub(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorSub(pActor, uiActorId);
}

void
StateAwareIterator::receiveActorsClear(void)
{
    Inherited::receiveActorsClear();
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

StateAwareIterator::StateAwareIterator(void)
    : Inherited()
{
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGStateAwareIterator.cpp,v 1.1 2003/10/10 13:51:06 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGSTATEAWAREITERATOR_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTATEAWAREITERATOR_INLINE_CVSID;
}
