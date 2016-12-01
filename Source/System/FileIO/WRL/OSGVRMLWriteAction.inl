/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */



/** \brief Destructor
 */


/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

inline 
MaterialPtr VRMLWriteAction::getMaterial(void) const
{
  return _material;
}


inline
FILE *VRMLWriteAction::getFilePtr(void) const
{
    return _pFile;
}

inline
VRMLWriteAction::TraversalMode VRMLWriteAction::getMode(void) const
{
    return _eTraversalMode;
}

inline
const std::string &VRMLWriteAction::getTextureWritePrefix ( void ) const
{
  return _textureWritePrefix;
}

inline
void VRMLWriteAction::setTextureWritePrefix ( const std::string &path )
{
  _textureWritePrefix = path;
}

inline
const std::string &VRMLWriteAction::getTextureWriteSuffix ( void ) const
{
  return _textureWriteSuffix;
}

inline
void VRMLWriteAction::setTextureWriteSuffix ( const std::string &path )
{
  _textureWriteSuffix = path;
}

inline
bool VRMLWriteAction::isWritten(FieldContainerPtr &fc)
{
    return std::find(_writtenFCs.begin(), _writtenFCs.end(), fc) != 
            _writtenFCs.end();
}

inline
UInt32 VRMLWriteAction::getIndex(FieldContainerPtr &fc)
{
    std::vector<FieldContainerPtr>::iterator it;
    
    it =  std::find(_writtenFCs.begin(), _writtenFCs.end(), fc);
    
    return it - _writtenFCs.begin();
}

inline
UInt32 VRMLWriteAction::setWritten(FieldContainerPtr &fc)
{
    _writtenFCs.push_back(fc);
    
    return _writtenFCs.size() - 1;
}

OSG_END_NAMESPACE
