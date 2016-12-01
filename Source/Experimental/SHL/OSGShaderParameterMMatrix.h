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

#ifndef _OSGSHADERPARAMETERMMATRIX_H_
#define _OSGSHADERPARAMETERMMATRIX_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGShaderParameterMMatrixBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderParameterMMatrix class. See \ref 
           PageSystemShaderParameterMMatrix for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShaderParameterMMatrix : public ShaderParameterMMatrixBase
{
  private:

    typedef ShaderParameterMMatrixBase Inherited;

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

    // Variables should all be in ShaderParameterMMatrixBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderParameterMMatrix(void);
    ShaderParameterMMatrix(const ShaderParameterMMatrix &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderParameterMMatrix(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShaderParameterMMatrixBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShaderParameterMMatrix &source);
};

typedef ShaderParameterMMatrix *ShaderParameterMMatrixP;

OSG_END_NAMESPACE

#include "OSGShaderParameterMMatrixBase.inl"
#include "OSGShaderParameterMMatrix.inl"

#define OSGSHADERPARAMETERMMATRIX_HEADER_CVSID "@(#)$Id: OSGShaderParameterMMatrix.h,v 1.1 2007/03/09 18:11:48 a-m-z Exp $"

#endif /* _OSGSHADERPARAMETERMMATRIX_H_ */
