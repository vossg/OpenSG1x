/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/


inline
void DVRVolume::setAppearance(const DVRAppearancePtr &value)
{
    SINFO << "DVRVolume::setAppearance this: " << this << std::endl;

//  SINFO << "setRefdCP(" << _sfAppearance.getValue() 
//        << ", " << value << std::endl;

    setRefdCP(_sfAppearance.getValue(), value);
}

inline
void DVRVolume::setGeometry(const DVRGeometryPtr &value)
{
    SINFO << "DVRVolume::setGeometry this: " << this << std::endl;
//  SINFO << "setRefdCP(" << _sfGeometry.getValue() << ", " 
//        << value << std::endl;

    setRefdCP(_sfGeometry.getValue(), value);
}

inline
void DVRVolume::setShader(const DVRShaderPtr &value)
{
    SINFO << "DVRVolume::setShader this: " << this << std::endl;
//  SINFO << "setRefdCP(" << _sfShader.getValue() << ", " 
//        << value << std::endl;

    setRefdCP(_sfShader.getValue(), value);
}

inline
void DVRVolume::setRenderMaterial(const MaterialPtr &value)
{
    SINFO << "DVRVolume::setRenderMaterial this: " 
          << this 
          << std::endl;

    SINFO << "setRefdCP(" 
          << _sfRenderMaterial.getValue() << ", " 
          << value << std::endl;

    SINFO << "---" << std::endl;

    setRefdCP(_sfRenderMaterial.getValue(), value);
}

inline
void DVRVolume::setTextureStorage(const ChunkMaterialPtr &value)
{
    SINFO << "DVRVolume::setTextureStorage this: " 
          << this << std::endl;
    SINFO << "setRefdCP(" 
          << _sfTextureStorage.getValue() << ", " 
          << value << std::endl;

    SINFO << "---" << std::endl;

    setRefdCP(_sfTextureStorage.getValue(), value);
}

inline
TextureManager &DVRVolume::getTextureManager() 
{
    return textureManager;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


OSG_END_NAMESPACE

#define OSGDVRVOLUME_INLINE_CVSID "@(#)$Id: $"

