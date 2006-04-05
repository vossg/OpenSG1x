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

#ifndef _OSGCGFXANNOTATION_H_
#define _OSGCGFXANNOTATION_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGShaderParameterAccess.h>

#include <OSGCGFXAnnotationBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief CGFXAnnotation class. See \ref 
           PageContribCGFXAnnotation for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING CGFXAnnotation : public CGFXAnnotationBase
{
  private:

    typedef CGFXAnnotationBase Inherited;

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
    /*---------------------------------------------------------------------*/
    /*! \name                 Parameter Access                             */
    /*! \{                                                                 */

    bool    getParameter(const char *name, bool   &value);
    bool    getParameter(const char *name, Int32  &value);
    bool    getParameter(const char *name, Real32 &value);
    bool    getParameter(const char *name, Vec2f  &value);
    bool    getParameter(const char *name, Vec3f  &value);
    bool    getParameter(const char *name, Vec4f  &value);
    bool    getParameter(const char *name, Matrix &value);
    bool    getParameter(const char *name, std::string &value);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CGFXAnnotationBase.

    void onCreate(const CGFXAnnotation *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CGFXAnnotation(void);
    CGFXAnnotation(const CGFXAnnotation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CGFXAnnotation(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CGFXAnnotationBase;

    static void initMethod(void);

    ShaderParameterAccess *_parameter_access;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGFXAnnotation &source);
};

typedef CGFXAnnotation *CGFXAnnotationP;

OSG_END_NAMESPACE

#include <OSGCGFXAnnotationBase.inl>
#include <OSGCGFXAnnotation.inl>

#define OSGCGFXANNOTATION_HEADER_CVSID "@(#)$Id: OSGCGFXAnnotation.h,v 1.1 2006/04/05 16:10:24 a-m-z Exp $"

#endif /* _OSGCGFXANNOTATION_H_ */
