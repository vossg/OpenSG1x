/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
inline Bool StatElemDesc::isValidID (Int32 ID)
{ 
  return (_descVec && (ID >= 0) && (ID < Int32(_descVec->size()))); 
}

/*-------------------------------------------------------------------------*/
inline  StatElemDesc *StatElemDesc::getDesc (Int32 ID)
{ 
  return (*_descVec)[ID]; 
}

/*-------------------------------------------------------------------------*/
inline  Int32 StatElemDesc::getNumOfDescs(void)
{ 
  return _descVec ? _descVec->size() : 0; 
}

/*-------------------------------------------------------------------------*/
inline const Char8 *StatElemDesc::getClassname(void)
{ 
  return "StatElemDesc"; 
}

/*-------------------------------------------------------------------------*/
inline        Int32   StatElemDesc::getID            (void) 
{ 
  return _ID; 
}

/*-------------------------------------------------------------------------*/
inline  const IDString &StatElemDesc::getName        (void) 
{ 
  return _name; 
}

/*-------------------------------------------------------------------------*/
inline  const IDString &StatElemDesc::getDescription (void) 
{ 
  return _description; 
}

/*-------------------------------------------------------------------------*/
inline StatElem* StatElemDesc::createElem ( void )
{ 
  return _createMethod ? _createMethod(this) : 0; 
}

OSG_END_NAMESPACE
