
#ifndef _OSGSTATEUNAWAREITERATOR_H_
#define _OSGSTATEUNAWAREITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGIteratorBase.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING StateUnawareIterator : public IteratorBase
{
  public:
    virtual ~StateUnawareIterator(void) = 0;
    
    virtual void receiveActorAdd   (ActorBase *pActor,   UInt32 uiActorId) = 0;
    virtual void receiveActorSub   (ActorBase *pActor,   UInt32 uiActorId) = 0;
    virtual void receiveActorsClear(void                                 ) = 0;

    virtual void receiveStateRead  (UInt32     uiActorId                 ) = 0;
    virtual void receiveStateWrite (UInt32     uiActorId                 ) = 0;

  protected:
    StateUnawareIterator(void);

  private:
    typedef IteratorBase Inherited;
};

OSG_END_NAMESPACE

#include "OSGStateUnawareIterator.inl"

#define OSGSTATEUNAWAREITERATOR_HEADER_CVSID "@(#)$Id: OSGStateUnawareIterator.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGSTATEUNAWAREITERATOR_H_ */
