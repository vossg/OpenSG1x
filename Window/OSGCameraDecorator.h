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


#ifndef _OSGCAMERADECORATOR_H_
#define _OSGCAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGCameraDecoratorBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING CameraDecorator : public CameraDecoratorBase
{
    /*==========================  PRIVATE =================================*/
  private:

    typedef CameraDecoratorBase Inherited;

    /*==========================  PUBLIC  =================================*/
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Class Get                                   */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "CameraDecorator"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   transformation                             */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);
 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /** get the separate elements needed for rendering */

    virtual void getProjection           (Matrix        &result, 
                                          UInt32 width, UInt32 height );

    virtual void getProjectionTranslation(Matrix        &result, 
                                          UInt32 width, UInt32 height);

    virtual void getViewing              (Matrix        &result, 
                                          UInt32 width, UInt32 height);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  dump                                        */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*==========================  PROTECTED ===============================*/
  protected:
   
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CameraDecorator(void);
    CameraDecorator(const CameraDecorator &source);
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CameraDecorator(void); 
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
 private:

    friend class FieldContainer;
    friend class CameraDecoratorBase;
 
    static char cvsid[];

    static void initMethod( void );

    void operator =(const CameraDecorator &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef CameraDecorator *CameraDecoratorP;

OSG_END_NAMESPACE

#include <OSGCameraDecorator.inl>
#include <OSGCameraDecoratorBase.inl>

#endif /* _OSGCAMERADECORATOR_H_ */
