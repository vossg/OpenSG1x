/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

template<class ParameterType, class ValueType> inline
bool ShaderParameterAccess::setParameter(const char *name, const ValueType &value)
{
    if(name == NULL)
        return false;

    updateMap();

    parameterIt it = _parametermap.find(name);
    
    if(it != _parametermap.end())
    {
        //ParameterType::Ptr p = ParameterType::Ptr::dcast(_parameters[(*it).second]);
        FCPtr<ShaderParameterPtr, ParameterType> p = FCPtr<ShaderParameterPtr, ParameterType>::dcast(_parameters[(*it).second]);
        if(p == NullFC)
        {
            FWARNING(("ShaderParameterAccess::setParameter : Parameter '%s' has wrong type!\n", name));
            return false;
        }
        beginEditCP(p, ParameterType::ValueFieldMask);
            p->setValue(value);
        endEditCP(p, ParameterType::ValueFieldMask);
    }
    else
    {
        //ParameterType::Ptr p = ParameterType::create();
        FCPtr<ShaderParameterPtr, ParameterType> p = ParameterType::create();
        if(p != NullFC)
        {
            beginEditCP(p);
                p->setName(name);
                p->setValue(value);
            endEditCP(p);
            _parameters.push_back(p);
            _parametermap.insert(std::pair<std::string, UInt32>(name, _parameters.size()-1));
            _mapsize = _parameters.size();
        }
    }
    return true;
}

template<class ParameterType, class ValueType> inline
bool ShaderParameterAccess::setMParameter(const char *name, const ValueType &value)
{
    if(name == NULL)
        return false;

    updateMap();

    parameterIt it = _parametermap.find(name);
    
    if(it != _parametermap.end())
    {
        //ParameterType::Ptr p = ParameterType::Ptr::dcast(_parameters[(*it).second]);
        FCPtr<ShaderParameterPtr, ParameterType> p = FCPtr<ShaderParameterPtr, ParameterType>::dcast(_parameters[(*it).second]);
        if(p == NullFC)
        {
            FWARNING(("ShaderParameterAccess::setMParameter : Parameter '%s' has wrong type!\n", name));
            return false;
        }
        beginEditCP(p, ParameterType::ValueFieldMask);
            p->getValue() = value;
        endEditCP(p, ParameterType::ValueFieldMask);
    }
    else
    {
        //ParameterType::Ptr p = ParameterType::create();
        FCPtr<ShaderParameterPtr, ParameterType> p = ParameterType::create();
        if(p != NullFC)
        {
            beginEditCP(p);
                p->setName(name);
                p->getValue() = value;
            endEditCP(p);
            _parameters.push_back(p);
            _parametermap.insert(std::pair<std::string, UInt32>(name, _parameters.size()-1));
            _mapsize = _parameters.size();
        }
    }
    return true;
}

template<class ParameterType, class ValueType> inline
bool ShaderParameterAccess::getParameter(const char *name, ValueType &value)
{
    if(name == NULL)
        return false;

    updateMap();

    parameterIt it = _parametermap.find(name);
    
    if(it != _parametermap.end())
    {
        //ParameterType::Ptr p = ParameterType::Ptr::dcast(_parameters[(*it).second]);
        FCPtr<ShaderParameterPtr, ParameterType> p = FCPtr<ShaderParameterPtr, ParameterType>::dcast(_parameters[(*it).second]);
        if(p == NullFC)
        {
            FWARNING(("ShaderParameterAccess::getParameter : Parameter '%s' has wrong type!\n", name));
            return false;
        }
        value = p->getValue();
    }
    else
    {
        FINFO(("ShaderParameterAccess::getParameter : Parameter '%s' doesn't exist!\n", name));
        return false;
    }
    return true;
}

OSG_END_NAMESPACE

#define OSGSHADERPARAMETERACCESS_INLINE_CVSID "@(#)$Id: OSGShaderParameterAccess.inl,v 1.11 2007/03/09 18:11:48 a-m-z Exp $"
