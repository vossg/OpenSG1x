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

#ifndef _OSGSHADERPARAMETERMVEC2F_H_
#define _OSGSHADERPARAMETERMVEC2F_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGShaderParameterMVec2fBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief ShaderParameterMVec2f class. See \ref 
           PageSystemShaderParameterMVec2f for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShaderParameterMVec2f : public ShaderParameterMVec2fBase
{
  private:

    typedef ShaderParameterMVec2fBase Inherited;

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

    // Variables should all be in ShaderParameterMVec2fBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderParameterMVec2f(void);
    ShaderParameterMVec2f(const ShaderParameterMVec2f &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderParameterMVec2f(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShaderParameterMVec2fBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShaderParameterMVec2f &source);
};

typedef ShaderParameterMVec2f *ShaderParameterMVec2fP;

OSG_END_NAMESPACE

#include <OSGShaderParameterMVec2fBase.inl>
#include <OSGShaderParameterMVec2f.inl>

#define OSGSHADERPARAMETERMVEC2F_HEADER_CVSID "@(#)$Id: OSGShaderParameterMVec2f.h,v 1.1 2007/03/09 18:11:49 a-m-z Exp $"

#endif /* _OSGSHADERPARAMETERMVEC2F_H_ */
