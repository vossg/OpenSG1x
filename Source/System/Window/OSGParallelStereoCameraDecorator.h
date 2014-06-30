/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGPARALLELSTEREOCAMERADECORATOR_H_
#define _OSGPARALLELSTEREOCAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParallelStereoCameraDecoratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParallelStereoCameraDecorator class. See \ref
           PageWindowParallelStereoCameraDecorator for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ParallelStereoCameraDecorator : public ParallelStereoCameraDecoratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParallelStereoCameraDecoratorBase Inherited;
    typedef ParallelStereoCameraDecorator     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField,
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */
 
    virtual void getViewing   (Matrix &result, 
                               UInt32  width, 
                               UInt32  height);

    virtual void getProjection(Matrix &result, 
                               UInt32  width, 
                               UInt32  height);
    
  	virtual void getDecoration(Matrix &result, 
                               UInt32  width, 
                               UInt32  height);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParallelStereoCameraDecoratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParallelStereoCameraDecorator(void);
    ParallelStereoCameraDecorator(const ParallelStereoCameraDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParallelStereoCameraDecorator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParallelStereoCameraDecoratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParallelStereoCameraDecorator &source);
};

typedef ParallelStereoCameraDecorator *ParallelStereoCameraDecoratorP;

OSG_END_NAMESPACE

#include "OSGParallelStereoCameraDecoratorBase.inl"
#include "OSGParallelStereoCameraDecorator.inl"

#endif /* _OSGPARALLELSTEREOCAMERADECORATOR_H_ */
