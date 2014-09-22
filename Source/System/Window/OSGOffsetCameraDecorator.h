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


#ifndef _OSGOFFSETCAMERADECORATOR_H_
#define _OSGOFFSETCAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGOffsetCameraDecoratorBase.h"

OSG_BEGIN_NAMESPACE


/*! \brief Camera Decorator class to select a part of the image, see \ref
    PageSystemWindowCameraDecoratorsTile for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING OffsetCameraDecorator : public OffsetCameraDecoratorBase
{
    /*==========================  PRIVATE  ================================*/     
  private:

    typedef OffsetCameraDecoratorBase Inherited;

    /*==========================  PUPLIC   ================================*/       
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "OffsetCameraDecorator"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     transformation                           */
    /*! \{                                                                 */
    
    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

    void setOffset(Real32 x, Real32 y);
    void setFullSize(UInt32 width, UInt32 height);
 
    virtual void getProjection           (Matrix        &result, 
                                          UInt32 width, UInt32 height);
										  
	virtual void getDecoration           (Matrix        &result, 
                                          UInt32 width, UInt32 height);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   dump                                       */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OffsetCameraDecorator(void);
    OffsetCameraDecorator(const OffsetCameraDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~OffsetCameraDecorator(void); 
    
    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
 private:

    friend class FieldContainer;
    friend class OffsetCameraDecoratorBase;

    static void initMethod( void );

    void operator =(const OffsetCameraDecorator &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef OffsetCameraDecorator *OffsetCameraDecoratorP;

OSG_END_NAMESPACE

#include "OSGOffsetCameraDecoratorBase.inl"
#include "OSGOffsetCameraDecorator.inl"

#endif /* _OSGOFFSETCAMERADECORATOR_H_ */
