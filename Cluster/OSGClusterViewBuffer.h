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

#ifndef _VIEWBUFFERHANDLER_H_
#define _VIEWBUFFERHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

class ImageFileType;
class Connection;

class OSG_SYSTEMLIB_DLLMAPPING ClusterViewBuffer
{
    /*==========================  PUBLIC  =================================*/
  public:

    /** \brief Buffer component */
    enum {
        RED      =1,
        GREEN    =2,
        BLUE     =4,
        ALPHA    =8,
        STENCIL  =16,
        DEPTH    =32,
        RGB      =RED|GREEN|BLUE,
        RGBA     =RED|GREEN|BLUE|ALPHA
    } Component;
    /** \brief stl vector used as char buffer */
    typedef std::vector<Int8> BufferT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ClusterViewBuffer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ClusterViewBuffer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   functions                                  */
    /*! \{                                                                 */

    void recv       (Connection &connection);

    void send       (Connection &connection,
                     UInt32     component,
                     UInt32     x1,
                     UInt32     y1,
                     UInt32     x2,
                     UInt32     y2,
                     UInt32     toX,
                     UInt32     toY);
    void send       (Connection &connection,
                     UInt32     component,
                     UInt32     toX,
                     UInt32     toY);

    void   setImgTransType(const char *mime=NULL);
    void   setSubtileSize(UInt32 size);

    UInt32 getBufferWidth();
    UInt32 getBufferHeight();

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    ImageFileType              *_imgTransType;
    UInt32                      _subTileSize;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /* prohibit default function (move to 'public' if needed) */
    ClusterViewBuffer(const ClusterViewBuffer &source);
    /* prohibit default function (move to 'public' if needed) */
    void operator =(const ClusterViewBuffer &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef ClusterViewBuffer *ClusterViewBufferP;

OSG_END_NAMESPACE

#define OSG_VIEWBUFFERHANDLER_HEADER_CVSID "@(#)$Id:$"

#endif /* _VIEWBUFFERHANDLER_H_ */
