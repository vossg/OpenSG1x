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

#ifndef _OSGSHADERPARAMETERACCESS_H_
#define _OSGSHADERPARAMETERACCESS_H_
#ifdef __sgi
#pragma once
#endif

#include <map>
#include <string>

#include <OSGConfig.h>

#include <OSGShaderParameter.h>

OSG_BEGIN_NAMESPACE

/*! \brief ShaderParameterAccess class. See \ref 
           PageSystemShaderParameterAccess for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShaderParameterAccess 
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */
    
    ShaderParameterAccess(MFShaderParameterPtr &parameters);
    ~ShaderParameterAccess(void);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */
  
    template<class ParameterType, class ValueType> 
    bool    setParameter(const char *name, ValueType value);
    bool    subParameter(const char *name);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderParameterAccess &source);
    void updateMap(void);

    MFShaderParameterPtr &_parameters;

    typedef std::map<std::string, UInt32> parameterMap;
    typedef parameterMap::iterator parameterIt;
    parameterMap _parametermap;
    UInt32       _mapsize;
};

OSG_END_NAMESPACE

#include <OSGShaderParameterAccess.inl>

#define OSGSHADERPARAMETERACCESS_HEADER_CVSID "@(#)$Id: OSGShaderParameterAccess.h,v 1.2 2004/06/06 16:44:21 a-m-z Exp $"

#endif /* _OSGSHADERPARAMETERACCESS_H_ */
