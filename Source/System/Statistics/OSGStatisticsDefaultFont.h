/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGSTATISTICSDEFAULTFONT_H_
#define _OSGSTATISTICSDEFAULTFONT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGTextureChunk.h>

#include <string>

OSG_BEGIN_NAMESPACE

/*--------------------------------------------------------------------------*/
/*! \name                     Geometry Functions                            */
/*! \{                                                                      */

/*! \brief font data for default font 
 *  \ingroup Statistics
 */

extern OSG_SYSTEMLIB_DLLMAPPING UChar8 StatisticsDefaultFontData[];

extern OSG_SYSTEMLIB_DLLMAPPING UInt32 StatisticsDefaultFontDataSize;

extern OSG_SYSTEMLIB_DLLMAPPING std::string StatisticsDefaultFontString;

class TextTXFFace;

OSG_SYSTEMLIB_DLLMAPPING TextTXFFace *getStatisticsDefaultFont();

OSG_SYSTEMLIB_DLLMAPPING TextureChunkPtr getStatisticsDefaultFontTexture();

/*! \}                                                                      */

OSG_END_NAMESPACE

#endif /* _OSGSTATISTICSDEFAULTFONT_H_ */
