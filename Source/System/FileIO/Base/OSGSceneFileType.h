/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGSCENEFILETYPE_H_
#define _OSGSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <OSGSystemDef.h>
#include <list>
#include <OSGBaseTypes.h>
#include <OSGIDString.h>
#include <OSGNodePtr.h>

OSG_BEGIN_NAMESPACE

/*!\ingroup GeometryLoaderLib 
 * \brief OSGSceneFileType
 */ 

class OSG_SYSTEMLIB_DLLMAPPING SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef std::vector<FieldContainerPtr> FCPtrStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual std::list<IDString> &suffixList         (void);

            bool                 doOverride         (void);
            UInt32               getOverridePriority(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr    read        (const Char8  *fileName,
                                          UInt32  uiReplaceOptions) const = 0;

    virtual NodePtr    read        (const Char8  *fileName,
                                          UInt32  uiAddOptions,
                                          UInt32  uiSubOptions    ) const = 0;

    virtual FCPtrStore readTopNodes(const Char8  *fileName,
                                          UInt32  uiReplaceOptions) const;

    virtual FCPtrStore readTopNodes(const Char8  *fileName,
                                          UInt32  uiAddOptions,
                                          UInt32  uiSubOptions     ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(const NodePtr  node,
                       const Char8   *fileName) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debug                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    std::list<IDString> _suffixList;
    
    bool                _override;
    UInt32              _overridePriority;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SceneFileType(const Char8  *suffixArray[],
                        UInt16  suffixByteCount,
                        bool    override,
                        UInt32  overridePriority);

    SceneFileType (const SceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SceneFileType &source);
};

typedef SceneFileType* SceneFileTypeP;

OSG_END_NAMESPACE

#define OSGSCENEFILETYPE_HEADER_CVSID "@(#)$Id: $"

#endif // _OSGSCENEFILETYPE_H_
