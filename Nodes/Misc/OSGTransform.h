/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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


#ifndef _OSGTRANSFORM_H_
#define _OSGTRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGAction.h>
#include <OSGTransformBase.h>

OSG_BEGIN_NAMESPACE

/*! Transform provides one matrix to transform objects.
 *	\ingroup NodesLib
 */

class OSG_SYSTEMLIB_DLLMAPPING Transform : public TransformBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Transform"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void accumulateMatrix( Matrix & result );

    virtual void changed(BitVector  whichField,
                         ChangeMode from);

    void adjustVolume( Volume & volume );

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector &bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Transform Draw                          */
    /*! \{                                                                 */

#ifdef OSG_NOFUNCTORS
    static Action::ResultE TransformDrawEnter(CNodePtr &cnode,
                                              Action   *pAction);
    static Action::ResultE TransformDrawLeave(CNodePtr &cnode,
                                              Action   *pAction);

    static Action::ResultE TransformIntEnter(CNodePtr &cnode,
                                             Action   *pAction);
    static Action::ResultE TransformIntLeave(CNodePtr &cnode,
                                             Action   *pAction);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Transform(void);
    Transform(const Transform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Transform(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Draw & Intersect & Render                       */
    /*! \{                                                                 */

    Action::ResultE drawEnter(Action * action );
    Action::ResultE drawLeave(Action * action );

    Action::ResultE intersectEnter(Action * action );
    Action::ResultE intersectLeave(Action * action );

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef TransformBase Inherited;

    friend class FieldContainer;
    friend class TransformBase;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                       Class Specific                         */
    /*! \{                                                                 */

    static void initMethod( void );
    void operator =(const Transform &source);

    /*! \}                                                                 */
};

typedef Transform *TransformP;

OSG_END_NAMESPACE

#include <OSGTransform.inl>
#include <OSGTransformBase.inl>

#endif /* _OSGTRANSFORM_H_ */
