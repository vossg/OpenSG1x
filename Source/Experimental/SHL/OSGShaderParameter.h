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

#ifndef _OSGSHADERPARAMETER_H_
#define _OSGSHADERPARAMETER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGShaderParameterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderParameter class. See \ref 
           PageSystemShaderParameter for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShaderParameter : public ShaderParameterBase
{
  private:

    typedef ShaderParameterBase Inherited;

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

    inline bool hasChanged(void);
    inline void resetChanged(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     TypeId's                                 */
    /*! \{                                                                 */

    enum SHPType
    {
        SHPTypeUnknown = 0,
        SHPTypeBool,
        SHPTypeInt,
        SHPTypeReal,
        SHPTypeVec2s,
        SHPTypeVec3s,
        SHPTypeVec4s,
        SHPTypeVec2f,
        SHPTypeVec3f,
        SHPTypeVec4f,
        SHPTypeMatrix,
        SHPTypeString,
        SHPTypeMBool,
        SHPTypeMInt,
        SHPTypeMReal,
        SHPTypeMVec2s,
        SHPTypeMVec3s,
        SHPTypeMVec4s,
        SHPTypeMVec2f,
        SHPTypeMVec3f,
        SHPTypeMVec4f,
        SHPTypeMMatrix,
        SHPTypeMString
    };

    enum SHPFlags
    {
        SHPFlagNone = 0,
        SHPFlagUpdate = 1
    };

    inline SHPType getTypeId(void);

    inline GLint getLocation(void);
    inline void  setLocation(GLint location);

    inline UInt32 getFlags(void);
    inline void  setFlags(UInt32 flags);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ShaderParameterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderParameter(void);
    ShaderParameter(const ShaderParameter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderParameter(void); 

    inline void setTypeId(SHPType type);
    inline void setChanged(void);

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    bool    _changed;
    SHPType _typeid;
    GLint   _location;
    UInt32  _flags;

    friend class FieldContainer;
    friend class ShaderParameterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShaderParameter &source);
};

typedef ShaderParameter *ShaderParameterP;

OSG_END_NAMESPACE

#include "OSGShaderParameterBase.inl"
#include "OSGShaderParameter.inl"

#define OSGSHADERPARAMETER_HEADER_CVSID "@(#)$Id: OSGShaderParameter.h,v 1.7 2007/03/09 18:11:48 a-m-z Exp $"

#endif /* _OSGSHADERPARAMETER_H_ */
