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


#ifndef OSGIMAGE_CLASS_DECLARATION
#define OSGIMAGE_CLASS_DECLARATION

#ifdef  __sgi
#pragma  once
#endif

#ifdef WIN32
#include <windows.h>
#endif

extern "C" {
#include <GL/gl.h>
}

#include <OSGSystemDef.h>
#include <OSGTime.h>
#include <OSGBaseTypes.h>

#include <string>
#include <map>

#if defined(GL_BGR) || defined(GL_BGR_EXT)
#define OSG_HAS_BGR_PF
#endif

#if defined(GL_BGRA) || defined(GL_BGRA_EXT)
#define OSG_HAS_BGRA_PF
#endif

OSG_BEGIN_NAMESPACE

//! Image

class OSG_SYSTEMLIB_DLLMAPPING Image {

    /*==========================  PUBLIC  =================================*/
  public:

    enum PixelFormat {   OSG_INVALID_PF = 0,
                         OSG_L_PF       = GL_LUMINANCE,
                         OSG_LA_PF      = GL_LUMINANCE_ALPHA,
#if defined(GL_BGR)
                         OSG_BGR_PF     = GL_BGR,
#elif defined(GL_BGR_EXT)
                         OSG_BGR_PF     = GL_BGR_EXT,
#endif
                         
#if defined(GL_BGRA)
                         OSG_BGRA_PF    = GL_BGRA,
#elif defined(GL_BGRA_EXT)
                         OSG_BGRA_PF    = GL_BGRA_EXT,
#endif
                         OSG_RGB_PF     = GL_RGB,
                         OSG_RGBA_PF    = GL_RGBA
    };

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    Image (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    Image (const Image &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Image (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    Image ( PixelFormat pixelFormat,
            Int32 width, Int32 height = 1, Int32 depth = 1,
            Int32 mipmapCount = 1,
            Int32 frameCount = 1, Time frameDelay = 0.0,
            const UChar8 *data = 0, Bool doCopy = true );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    Bool set     ( PixelFormat pixelFormat,
                   Int32 width, Int32 height = 1,
                   Int32 depth = 1,
                   Int32 mipmapCount = 1,
                   Int32 frameCount = 1, Time frameDelay = 0.0,
                   const UChar8 *data = 0, Bool doCopy = true );

    Bool set     ( const Image &image, Bool doCopy = true );

    Bool setData ( const UChar8 *data = 0, Bool doCopy = true );

		Bool flipDepthFrameData (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Add Value                                */
    /*! \{                                                                 */

    Bool addValue (const char *value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Reformate                                */
    /*! \{                                                                 */

    Bool reformat ( PixelFormat pixelFormat,
                    Image *destination = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Scale                                  */
    /*! \{                                                                 */

    Bool scale ( Int32 width, Int32 height = 1,
                 Int32 depth = 1,
                 Image *destination = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mipmap                                  */
    /*! \{                                                                 */

    Bool createMipmap ( Int32 level = -1,
                        Image *destination = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    Bool write (const Char8 *fileName);

    Bool read  (const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Storage                                   */
    /*! \{                                                                 */

    UInt64 store   (Char8 *mimeType, 
                    UChar8* mem,
                    Int32 memSize = -1);

    UInt64 restore ( const UChar8* mem, Int32 memSize = -1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Comparison/Assign                              */
    /*! \{                                                                 */

    Bool   operator == (const Image &image);

    Image &operator=   (const Image &image);

    Bool   operator <  (const Image &image);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get  Methods                              */
    /*! \{                                                                 */

		inline Bool   isValid (void) const;

    inline Int32  getDimension  (void) const;

    inline Int32  getWidth      (void) const;

    inline Int32  getHeight     (void) const;

    inline Int32  getDepth      (void) const;

    inline UChar8 getBpp        (void) const;

    inline Int32  getMipMapCount(void) const;

    inline Int32  getFrameCount (void) const;

    inline Time   getFrameDelay (void) const;

    inline PixelFormat getPixelFormat (void) const;

    Bool hasAlphaChannel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Size                                    */
    /*! \{                                                                 */


    inline unsigned long getSize ( Bool withMipmap = true,
                                   Bool withFrames = true) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Methods                                */
    /*! \{                                                                 */

    inline UChar8 *getData ( UInt32 mipmapNum = 0, 
                             UInt32 frameNum = 0) const;

    inline UChar8 *getDataByTime(Time time, UInt32 mipmapNum = 1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               string attachment handling                     */
    /*! \{                                                                 */

    inline Bool hasAttachment (void) const;

    inline UInt32 attachmentCount (void) const;

    inline  void setAttachment ( const std::string &key, 
                                 const std::string &data);

    inline std::string * findAttachment ( const std::string &key);

    inline void eraseAttachment ( const std::string &key);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Calculate                               */
    /*! \{                                                                 */

    inline void   calcMipmapGeometry   ( UInt32 mipmapNum,
                                         UInt32 &width, 
                                         UInt32 &height, 
                                         UInt32 &depth );

    inline UInt32 calcMipmapLevelCount ( void );

    UInt32 calcFrameNum(Time time, Bool loop = true);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Clear Image                                */
    /*! \{                                                                 */

    virtual void clear (UChar8 pixelValue = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump (void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    static Int32 _formatMap[][2];

    PixelFormat _pixelFormat;

    Int32 _width;

    Int32 _height;

    Int32 _depth;

    Int32 _mipmapCount;

    Int32 _frameCount;

    Time _frameDelay;

    UChar8 _bpp;

    Int32 _dimension;

    Int32 _frameSize;

    Bool  _isCopy;

    UChar8 * _data;

    std::map<std::string, std::string> _attachmentMap;

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name               Calculate Mipmap Size                          */
    /*! \{                                                                 */

    inline UInt32 calcMipmapSize ( UInt32 mipmapNum,
                                   UInt32 w, UInt32 h, UInt32 d) const;

    inline UInt32 calcMipmapSize    ( UInt32 mipmapNum) const;

    inline UInt32 calcMipmapSumSize ( UInt32 mipmapNum,
                                      UInt32 w, UInt32 h, UInt32 d) const;

    inline UInt32 calcMipmapSumSize (UInt32 mipmapNum) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Image Data                                 */
    /*! \{                                                                 */

    Bool createData (const UChar8 *data, Bool doCopy );

    Bool scaleData  ( UChar8* srcData, 
                      Int32 srcW, Int32 srcH, Int32 srcD,
                      UChar8* destData, 
                      Int32 destW, Int32 destH, Int32 destD );

    /*! \}                                                                 */
};

typedef Image* ImageP;

OSG_END_NAMESPACE

#include <OSGImage.inl>

#endif // OSGIMAGE_CLASS_DECLARATION
