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

#ifndef _OSGSHADERPARAMETERCHUNK_H_
#define _OSGSHADERPARAMETERCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGMFSysTypes.h"
#include "OSGMFVecTypes.h"
#include "OSGMFMathTypes.h"

#include "OSGShaderParameterChunkBase.h"
#include "OSGShaderParameterAccess.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderParameterChunk class. See \ref 
           PageSystemShaderParameterChunk for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShaderParameterChunk : public ShaderParameterChunkBase
{
  private:

    typedef ShaderParameterChunkBase Inherited;

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
    /*! \name                 ShaderParameterChunk Access                           */
    /*! \{                                                                 */

    bool    setUniformParameter(const char *name, bool   value       );
    bool    setUniformParameter(const char *name, Int32  value       );
    bool    setUniformParameter(const char *name, Real32 value       );
    bool    setUniformParameter(const char *name, const Vec2f  &value);
    bool    setUniformParameter(const char *name, const Vec3f  &value);
    bool    setUniformParameter(const char *name, const Vec4f  &value);
    bool    setUniformParameter(const char *name, const Matrix &value);

    bool    setUniformParameter(const char *name, const MFInt32  &value);
    bool    setUniformParameter(const char *name, const MFReal32 &value);
    bool    setUniformParameter(const char *name, const MFVec2f  &value);
    bool    setUniformParameter(const char *name, const MFVec3f  &value);
    bool    setUniformParameter(const char *name, const MFVec4f  &value);
    bool    setUniformParameter(const char *name, const MFMatrix &value);

    bool    getUniformParameter(const char *name, bool   &value);
    bool    getUniformParameter(const char *name, Int32  &value);
    bool    getUniformParameter(const char *name, Real32 &value);
    bool    getUniformParameter(const char *name, Vec2f  &value);
    bool    getUniformParameter(const char *name, Vec3f  &value);
    bool    getUniformParameter(const char *name, Vec4f  &value);
    bool    getUniformParameter(const char *name, Matrix &value);

    bool    getUniformParameter(const char *name, MFInt32  &value);
    bool    getUniformParameter(const char *name, MFReal32 &value);
    bool    getUniformParameter(const char *name, MFVec2f  &value);
    bool    getUniformParameter(const char *name, MFVec3f  &value);
    bool    getUniformParameter(const char *name, MFVec4f  &value);
    bool    getUniformParameter(const char *name, MFMatrix &value);

    bool    subUniformParameter(const char *name);

    bool    hasUniformParameter(const char *name);

    void    clearUniformParameters(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ShaderParameterChunkBase.

    void onCreate(const ShaderParameterChunk *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderParameterChunk(void);
    ShaderParameterChunk(const ShaderParameterChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderParameterChunk(void); 

    /*---------------------------------------------------------------------*/
    /*! \name                  Parameter Access                            */
    /*! \{                                                                 */

    ShaderParameterAccess *_parameter_access;

    bool _cleared_parameters;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShaderParameterChunkBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShaderParameterChunk &source);
};

typedef ShaderParameterChunk *ShaderParameterChunkP;

OSG_END_NAMESPACE

#include "OSGShaderParameterChunkBase.inl"
#include "OSGShaderParameterChunk.inl"

#define OSGSHADERPARAMETERCHUNK_HEADER_CVSID "@(#)$Id: OSGShaderParameterChunk.h,v 1.5 2011/11/08 17:46:19 carstenneumann Exp $"

#endif /* _OSGSHADERPARAMETERCHUNK_H_ */
