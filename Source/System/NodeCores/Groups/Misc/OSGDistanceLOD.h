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

#ifndef _OSGDISTANCELOD_H_
#define _OSGDISTANCELOD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGDistanceLODBase.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

class DrawActionBase;

/*! \brief Distance-based Level Of Detail
    \ingroup GrpSystemNodeCoresMisc
*/

class OSG_SYSTEMLIB_DLLMAPPING DistanceLOD : public DistanceLODBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField,
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef DistanceLODBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DistanceLOD(void);
    DistanceLOD(const DistanceLOD &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DistanceLOD(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Action Callbacks                           */
    /*! \{                                                                 */

    Action::ResultE draw( Action* action );
    Action::ResultE intersect(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               calc the distance                              */
    /*! \{                                                                 */

    Real32 calcDistance(DrawActionBase *pAction, const Matrix &mToWorld);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DistanceLODBase;

    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
	
	Real32 _lastDist;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const DistanceLOD &source);
};

OSG_END_NAMESPACE

#include "OSGDistanceLODBase.inl"
#include "OSGDistanceLOD.inl"

#define OSGDISTANCELOD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDISTANCELOD_H_ */
