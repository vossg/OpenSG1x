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


#ifndef _OSGVRMLSCENEFILETYPE_H_
#define _OSGVRMLSCENEFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGSceneFileType.h>
#include <OSGVRMLFile.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup Loader
 *  \brief Brief
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef vector<FieldContainerPtr> FCPtrStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLSceneFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual       VRMLSceneFileType &the    (void);

    virtual const Char8             *getName(void) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr    read        (const Char8  *fileName, 
                                          UInt32  uiOptions) const;
    
    virtual FCPtrStore readTopNodes(const Char8  *fileName,
                                          UInt32  uiOptions) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual Bool write(const NodePtr  node, 
                       const Char8   *fileName) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const char        *_suffixA[];
    static VRMLSceneFileType  _the;
    
    static VRMLFile          *_pVRMLLoader;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLSceneFileType(const Char8  *suffixArray[], 
                            UInt16  suffixByteCount,
                            Bool    override,
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

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#define OSGVRMLSCENEFILETYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _GFHSSCENEFILETYPE_H_ */
