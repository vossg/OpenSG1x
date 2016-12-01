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

#ifndef _OSGVRMLSCENEFILETYPE_H_
#define _OSGVRMLSCENEFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVRMLBase.h"
#include "OSGBaseTypes.h"
#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

class VRMLLoader;
class VRMLToOSGAction;

//! VRML97 SceneFileType
//! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib

class OSG_VRML_DLLMAPPING VRMLSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef std::vector<FieldContainerPtr> FCPtrStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static VRMLSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLSceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr    read        (std::istream &is,
                                    const Char8 *fileNameOrExtension) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8             *_suffixA[];
    static       VRMLSceneFileType  _the;

    static       VRMLLoader        *_pVRMLLoader;
    static       VRMLToOSGAction   *_pVRMLToOSGAction;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLSceneFileType(const Char8  *suffixArray[],
                            UInt16  suffixByteCount,
                            bool    override,
                            UInt32  overridePriority);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef SceneFileType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLSceneFileType(const VRMLSceneFileType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLSceneFileType &source);
};

OSG_END_NAMESPACE

#define OSGVRMLSCENEFILETYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLSCENEFILETYPE_H_ */
