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

#ifndef _OSGOBJSCENEFILETYPE_H_
#define _OSGOBJSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <OSGBaseTypes.h>

#include "OSGSceneFileType.h"

#include <map>


OSG_BEGIN_NAMESPACE

/*! \ingroup GeometryLoaderLib
 *  \brief Brief OSGOBJSceneFileType
 */

class OSG_SYSTEMLIB_DLLMAPPING OBJSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static OBJSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~OBJSceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr read(const Char8  *fileName, 
                               UInt32  uiReplaceOptions) const;

    virtual NodePtr read(const Char8  *fileName, 
                               UInt32  uiAddOptions,
                               UInt32  uiSubOptions) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual Bool write(const NodePtr node, const Char8 *fileName) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8            *_suffixA[];
    static       OBJSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OBJSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           Bool    override,
                           UInt32  overridePriority);

    OBJSceneFileType(const OBJSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef SceneFileType Inherited;

    enum DataElem 
    { 
      UNKNOWN_DE = 0,
      VERTEX_DE, VERTEX_TEXTURECOORD_DE, VERTEX_NORMAL_DE,
      MTL_LIB_DE, NEW_MTL_DE, 
      MTL_DIFFUSE_DE, MTL_AMBIENT_DE, MTL_SPECULAR_DE, 
      MTL_SHININESS_DE, MTL_ILLUM_DE,
      MTL_MAP_KD_DE, MTL_MAP_KA_DE, MTL_MAP_KS_DE,
      FACE_DE, 
      USE_MTL_DE, 
      GROUP_DE, SMOOTHING_GROUP_DE, OBJECT_DE
    };

    static map<string, DataElem> _dataElemMap;
    static void initDataElemMap(void);

    struct TiePoint {
      Int32 index[3];
      TiePoint( Int32 v = -1, Int32 vt = -1, Int32 vn = -1 )
        { index[0] = v; index[1] = vt; index[2] = vn; }
      inline void set ( Int32 v = -1, Int32 vt = -1, Int32 vn = -1 )
        { index[0] = v; index[1] = vt; index[2] = vn; }
    };
    
    struct Face {
      vector<TiePoint> tieVec;
    };

    struct Mesh {
      string name;
      std::list<Face> faceList;
      SimpleMaterialPtr mtlPtr;
    };

    Int32 readMTL ( const Char8 *fileName, 
                    map<string, SimpleTexturedMaterialPtr> & mtlMap ) const;

    /* prohibit default function (move to 'public' if needed) */
    void operator =(const OBJSceneFileType &source);
};

typedef OBJSceneFileType* OBJSceneFileTypeP;

OSG_END_NAMESPACE

#define OSGOBJSCENEFILETYPE_HEADER_CVSID "@(#)$Id: OSGOBJSceneFileType.h,v 1.10 2001/10/16 10:58:37 jbehr Exp $"

#endif // _OSGOBJSCENEFILETYPE_H_

