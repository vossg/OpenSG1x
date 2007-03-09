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

#ifndef _OSGSHADERPARAMETERMREAL_H_
#define _OSGSHADERPARAMETERMREAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGShaderParameterMRealBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief ShaderParameterMReal class. See \ref 
           PageSystemShaderParameterMReal for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShaderParameterMReal : public ShaderParameterMRealBase
{
  private:

    typedef ShaderParameterMRealBase Inherited;

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

    // Variables should all be in ShaderParameterMRealBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderParameterMReal(void);
    ShaderParameterMReal(const ShaderParameterMReal &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderParameterMReal(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShaderParameterMRealBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShaderParameterMReal &source);
};

typedef ShaderParameterMReal *ShaderParameterMRealP;

OSG_END_NAMESPACE

#include <OSGShaderParameterMRealBase.inl>
#include <OSGShaderParameterMReal.inl>

#define OSGSHADERPARAMETERMREAL_HEADER_CVSID "@(#)$Id: OSGShaderParameterMReal.h,v 1.1 2007/03/09 18:11:48 a-m-z Exp $"

#endif /* _OSGSHADERPARAMETERMREAL_H_ */
