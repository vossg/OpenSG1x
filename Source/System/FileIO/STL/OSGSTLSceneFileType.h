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

#ifndef _OSGSTLSCENEFILETYPE_H_
#define _OSGSTLSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGBaseTypes.h"

#include "OSGSceneFileType.h"

#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief OSGSTLSceneFileType
*/

class OSG_SYSTEMLIB_DLLMAPPING STLSceneFileType : public SceneFileType
{
	/*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static STLSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~STLSceneFileType(void);

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
    /*=========================  PROTECTED  ===============================*/
  protected:


	struct STLFace	{
		Real32 v1x, v1y, v1z; 
		Real32 v2x, v2y, v2z; 
		Real32 v3x, v3y, v3z; 
		Real32 nx, ny, nz; 
	}; 
	typedef std::vector<STLFace> STLFaceList;
	typedef std::vector<STLFace>::iterator STLFaceListIterator;

	Real32 ReadFloat(std::istream& is, bool bigEndian=false) const;
	bool IsASCII(std::istream &is, const Char8* fileNameOrExtension) const;
	virtual bool readASCII(std::istream &is, STLFaceList& theFaces, 
                            std::string& theName) const;
    virtual bool readBinary(std::istream &is, STLFaceList& theFaces, 
                            std::string& theName) const;


    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8            *_suffixA[];
    static       STLSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    STLSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           bool    override,
                           UInt32  overridePriority,
                           UInt32  flags);

    STLSceneFileType(const STLSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef SceneFileType Inherited;
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const STLSceneFileType &source);
};

typedef STLSceneFileType* STLSceneFileTypeP;

OSG_END_NAMESPACE

#define OSGSTLSCENEFILETYPE_HEADER_CVSID "@(#)$Id: OSGSTLSceneFileType.h,v 1.1 2006/04/26 23:35:18 dirk Exp $"

#endif // _OSGSTLSCENEFILETYPE_H_
