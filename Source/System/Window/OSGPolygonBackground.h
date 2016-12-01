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

#ifndef _OSGPOLYGONBACKGROUND_H_
#define _OSGPOLYGONBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGViewport.h"

#include "OSGPolygonBackgroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PolygonBackground class. See \ref 
           PageSystemPolygonBackground for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING PolygonBackground : public PolygonBackgroundBase
{
  private:

    typedef PolygonBackgroundBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                     Clear                                    */
    /*! \{                                                                 */

    virtual void clear( DrawActionBase *act, Viewport *port );

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
    /*---------------------------------------------------------------------*/
    /*! \name                     Helpers                                  */
    /*! \{                                                                 */

    Real32 mapCoordinate(Real32 val, Real32 max, bool norm);
    
    enum { VERTICAL=0, HORIZONTAL, SMALLER } FitMode;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PolygonBackgroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PolygonBackground(void);
    PolygonBackground(const PolygonBackground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PolygonBackground(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PolygonBackgroundBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PolygonBackground &source);
};

typedef PolygonBackground *PolygonBackgroundP;

OSG_END_NAMESPACE

#include "OSGPolygonBackgroundBase.inl"
#include "OSGPolygonBackground.inl"

#define OSGPOLYGONBACKGROUND_HEADER_CVSID "@(#)$Id: OSGPolygonBackground.h,v 1.2 2009/05/07 14:16:35 sawebel Exp $"

#endif /* _OSGPOLYGONBACKGROUND_H_ */
