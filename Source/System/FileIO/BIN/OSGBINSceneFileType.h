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

#ifndef _OSGBINSCENEFILETYPE_H_
#define _OSGBINSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <OSGBaseTypes.h>

#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief BINSceneFileType
*/

class OSG_SYSTEMLIB_DLLMAPPING BINSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Static Get                                 */
    /*! \{                                                                 */

    static BINSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BINSceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr read(std::istream &is,
                         const Char8 *fileNameOrExtension) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(const NodePtr &node, std::ostream &os,
                       const Char8 *fileNameOrExtension) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8            *_suffixA[];
    static       BINSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BINSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           bool    override,
                           UInt32  overridePriority,
                           UInt32  flags);

    BINSceneFileType(const BINSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef SceneFileType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BINSceneFileType &source);
};

typedef BINSceneFileType* BINSceneFileTypeP;

OSG_END_NAMESPACE

#define OSGBINSCENEFILETYPE_HEADER_CVSID "@(#)$Id: OSGBINSceneFileType.h,v 1.4 2001/10/08 05:21:54 vossg Exp $"

#endif // _OSGBINSCENEFILETYPE_H_
