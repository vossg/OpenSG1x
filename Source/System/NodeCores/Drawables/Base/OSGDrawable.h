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

#ifndef _OSGDRAWABLE_H_
#define _OSGDRAWABLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGDrawableBase.h"
#include "OSGStatElemTypes.h"

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING Drawable : public DrawableBase
{
  private:

    typedef DrawableBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  static stat elem                            */
    /*! \{                                                                 */

    static StatElemDesc<StatIntElem>     statNTriangles;
    static StatElemDesc<StatIntElem>     statNLines;
    static StatElemDesc<StatIntElem>     statNPoints;
    static StatElemDesc<StatIntElem>     statNVertices;
    static StatElemDesc<StatIntElem>     statNPrimitives;
    static StatElemDesc<StatIntOnceElem> statNGeoBytes;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DrawableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Drawable(void);
    Drawable(const Drawable &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Drawable(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DrawableBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Drawable &source);
};

typedef Drawable *DrawableP;

OSG_END_NAMESPACE

#include "OSGDrawableBase.inl"
#include "OSGDrawable.inl"

#define OSGDRAWABLE_HEADER_CVSID "@(#)$Id: OSGDrawable.h,v 1.6 2007/05/31 10:48:57 a-m-z Exp $"

#endif /* _OSGDRAWABLE_H_ */
