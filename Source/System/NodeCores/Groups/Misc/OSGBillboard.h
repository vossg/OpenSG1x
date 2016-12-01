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

#ifndef _OSGBILLBOARD_H_
#define _OSGBILLBOARD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGMatrix.h"
#include "OSGBillboardBase.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

class DrawActionBase;

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING Billboard : public BillboardBase
{
  private:

    typedef BillboardBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               calc the model matrix                          */
    /*! \{                                                                 */

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

    // Variables should all be in BillboardBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Billboard(void);
    Billboard(const Billboard &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Billboard(void); 

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

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class BillboardBase;

    static void initMethod(void);

    Matrix _camTransform;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Billboard &source);
};

typedef Billboard *BillboardP;

OSG_END_NAMESPACE

#include "OSGBillboardBase.inl"
#include "OSGBillboard.inl"

#define OSGBILLBOARD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGBILLBOARD_H_ */

