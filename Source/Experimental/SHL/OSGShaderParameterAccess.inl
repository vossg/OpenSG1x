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
void ShaderParameterAccess::setParameter(const char *name, ValueType value)
{
    if(name == NULL)
        return;

    parameterIt it = _parametermap.find(name);
    
    if(it != _parametermap.end())
    {
        ParameterType::Ptr p = ParameterType::Ptr::dcast(_parameters[(*it).second]);
        if(p == NullFC)
        {
            FWARNING(("Parameter '%s' has wrong type!\n", name));
            return;
        }
        p->setValue(value);
        p->setChanged(true);
    }
    else
    {
        ParameterType::Ptr p = ParameterType::create();
        if(p != NullFC)
        {
            p->setName(name);
            p->setValue(value);
            p->setChanged(true);
            _parameters.push_back(p);
            _parametermap.insert(std::pair<std::string, UInt32>(name, _parameters.size()-1));
        }
    }
}

OSG_END_NAMESPACE

#define OSGSHADERPARAMETER_INLINE_CVSID "@(#)$Id: OSGShaderParameterAccess.inl,v 1.1 2004/06/05 18:16:43 a-m-z Exp $"

