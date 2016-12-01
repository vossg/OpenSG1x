/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGINVERSETRANSFORM_H_
#define _OSGINVERSETRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGInverseTransformBase.h"

#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

class DrawActionBase;

/*! \brief InverseTransform class. See \ref
           PageSystemInverseTransform for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING InverseTransform : public InverseTransformBase
{
  private:

    typedef InverseTransformBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               calc the inverse matrix                        */
    /*! \{                                                                 */

    void initMatrix(const Matrix         &mToWorld);

    void calcMatrix(      DrawActionBase *pAction,
                    const Matrix         &mToWorld,
                          Matrix         &mResult);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Transformation                              */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrix &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in InverseTransformBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    InverseTransform(void);
    InverseTransform(const InverseTransform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~InverseTransform(void);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                      NodeCore Specific                       */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume & volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Draw & Intersect & Render                       */
    /*! \{                                                                 */

    Action::ResultE drawEnter     (Action *action);
    Action::ResultE drawLeave     (Action *action);

    Action::ResultE intersectEnter(Action *action);
    Action::ResultE intersectLeave(Action *action);

    Action::ResultE renderEnter   (Action *action);
    Action::ResultE renderLeave   (Action *action);

    /*! \}    */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class InverseTransformBase;

    static void initMethod(void);

    Matrix _invWorld;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const InverseTransform &source);
};

typedef InverseTransform *InverseTransformP;

OSG_END_NAMESPACE

#include "OSGInverseTransformBase.inl"
#include "OSGInverseTransform.inl"

#define OSGINVERSETRANSFORM_HEADER_CVSID "@(#)$Id: OSGInverseTransform.h,v 1.2 2004/10/13 14:51:34 a-m-z Exp $"

#endif /* _OSGINVERSETRANSFORM_H_ */
