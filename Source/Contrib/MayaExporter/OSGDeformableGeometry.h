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

#ifndef _OSGDEFORMABLEGEOMETRY_H_
#define _OSGDEFORMABLEGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGDeformableGeometryBase.h>

OSG_BEGIN_NAMESPACE

/*! rief DeformableGeometry class. See ef 
           PageMYDeformableGeometry for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING DeformableGeometry : public DeformableGeometryBase
{
  private:

    typedef DeformableGeometryBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

    // Variables should all be in DeformableGeometryBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DeformableGeometry(void);
    DeformableGeometry(const DeformableGeometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DeformableGeometry(void); 

    /*! \}                                                                 */

    void adjustVolume( Volume & volume );
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DeformableGeometryBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DeformableGeometry &source);
};

typedef DeformableGeometry *DeformableGeometryP;

OSG_END_NAMESPACE

#include <OSGDeformableGeometryBase.inl>
#include <OSGDeformableGeometry.inl>

#define OSGDEFORMABLEGEOMETRY_HEADER_CVSID "@(#)$Id: OSGDeformableGeometry.h,v 1.2 2003/04/28 23:05:32 michael Exp $"

#endif /* _OSGDEFORMABLEGEOMETRY_H_ */
