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

#ifndef _OSGRAWSCENEFILETYPE_H_
#define _OSGRAWSCENEFILETYPE_H_
#ifdef  __sig
#pragma  once
#endif

#include <OSGBaseTypes.h>

#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING RAWSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RAWSceneFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual RAWSceneFileType & the (void) { return _the; }

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
    static  RAWSceneFileType & staticThe (void) { return _the; }
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr read(const Char8 *fileName, UInt32 uiOptions) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual Bool write (const NodePtr node, const char *fileName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    virtual const char *getName (void) const { return "RAW GEOMETRY"; }

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

   RAWSceneFileType ( const char *suffixArray[],
                                                UInt16 suffixByteCount );

    RAWSceneFileType (const RAWSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef SceneFileType Inherited;

    static RAWSceneFileType _the;
};

typedef RAWSceneFileType* RAWSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGRAWSCENEFILETYPE_H_
