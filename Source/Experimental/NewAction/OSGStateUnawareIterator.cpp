
#include "OSGStateUnawareIterator.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

StateUnawareIterator::~StateUnawareIterator(void)
{
}

void
StateUnawareIterator::receiveActorAdd(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorAdd(pActor, uiActorId);
}
void
StateUnawareIterator::receiveActorSub(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorSub(pActor, uiActorId);
}

void
StateUnawareIterator::receiveActorsClear(void)
{
    Inherited::receiveActorsClear();
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

StateUnawareIterator::StateUnawareIterator(void)
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGStateUnawareIterator.cpp,v 1.1 2003/10/10 13:51:06 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGSTATEUNAWAREITERATOR_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTATEUNAWAREITERATOR_INLINE_CVSID;
}
