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

#ifndef _OSGINTERSECTACTOR_H_
#define _OSGINTERSECTACTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGIntersectActorBase.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING IntersectActor : public IntersectActorBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef ActorBase::ResultE ResultE;
    typedef ActorBase::Functor Functor;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Create                                                    */
    /*! \{                                                                 */

    static IntersectActor *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    virtual ~IntersectActor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Apply                                                     */
    /*! \{                                                                 */

    virtual ResultE applyLeave(const NodePtr &pNode);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Class specific helper                                     */
    /*! \{                                                                 */

    inline void reset             (void                               );
    inline void setHit            (Real32 hitDist,   NodePtr pHitObj,
                                   Int32  iTriIndex, Vec3f   hitNormal);

    inline void prioritizeChildren(void                               );

    /*! \}                                                                 */
    /*============================== PROTECTED ============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name    Constructor                                               */
    /*! \{                                                                 */

    IntersectActor(void);

    /*! \}                                                                 */
    /*=============================== PRIVATE =============================*/
  private:
    typedef IntersectActorBase Inherited;
};

OSG_END_NAMESPACE

#include <OSGIntersectActor.inl>

#define OSGINTERSECTACTOR_HEADER_CVSID "@(#)$Id:"

#endif /* _OSGINTERSECTACTOR_H_ */

