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

#ifndef _OSGSHADERCHUNK_H_
#define _OSGSHADERCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGShaderChunkBase.h>
#include <OSGShaderParameterAccess.h>

OSG_BEGIN_NAMESPACE

/*! \brief ShaderChunk class. See \ref 
           PageSystemShaderChunk for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShaderChunk : public ShaderChunkBase
{
  private:

    typedef ShaderChunkBase Inherited;

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
    /*! \name                 ShaderChunk Access                           */
    /*! \{                                                                 */

            bool    readVertexProgram        (const char   *file  );
            bool    readVertexProgram        (std::istream &stream);
            bool    readFragmentProgram      (const char   *file  );
            bool    readFragmentProgram      (std::istream &stream);

            bool    setUniformParameter(const char *name, bool   value       );
            bool    setUniformParameter(const char *name, Int32  value       );
            bool    setUniformParameter(const char *name, Real32 value       );
            bool    setUniformParameter(const char *name, const Vec2f  &value);
            bool    setUniformParameter(const char *name, const Vec3f  &value);
            bool    setUniformParameter(const char *name, const Vec4f  &value);
            bool    setUniformParameter(const char *name, const Matrix &value);

            bool    getUniformParameter(const char *name, bool   &value);
            bool    getUniformParameter(const char *name, Int32  &value);
            bool    getUniformParameter(const char *name, Real32 &value);
            bool    getUniformParameter(const char *name, Vec2f  &value);
            bool    getUniformParameter(const char *name, Vec3f  &value);
            bool    getUniformParameter(const char *name, Vec4f  &value);
            bool    getUniformParameter(const char *name, Matrix &value);

            bool    subUniformParameter(const char *name);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ShaderChunkBase.

    void onCreate(const ShaderChunk *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderChunk(void);
    ShaderChunk(const ShaderChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderChunk(void); 

    /*---------------------------------------------------------------------*/
    /*! \name                  Parameter Access                            */
    /*! \{                                                                 */

    ShaderParameterAccess *_parameter_access;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShaderChunkBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShaderChunk &source);
};

typedef ShaderChunk *ShaderChunkP;

OSG_END_NAMESPACE

#include <OSGShaderChunkBase.inl>
#include <OSGShaderChunk.inl>

#define OSGSHADERCHUNK_HEADER_CVSID "@(#)$Id: OSGShaderChunk.h,v 1.2 2004/07/02 17:59:45 a-m-z Exp $"

#endif /* _OSGSHADERCHUNK_H_ */
