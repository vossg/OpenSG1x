/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGTEXTUREBACKGROUND_H_
#define _OSGTEXTUREBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGTextureBackgroundBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief TextureBackground class. See \ref
           PageSystemTextureBackground for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING TextureBackground : public TextureBackgroundBase
{
  private:

    typedef TextureBackgroundBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                     Clear                                    */
    /*! \{                                                                 */

    virtual void clear( DrawActionBase * action, Viewport * port );

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TextureBackgroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureBackground(void);
    TextureBackground(const TextureBackground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureBackground(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:
    std::vector<Vec2f> _textureCoordArray;
    std::vector<Vec2f> _vertexCoordArray;
    std::vector<UInt32> _indexArray;
    
    // Values for which the grid has been calculated, 
    // to check for update necessity
    UInt16              _hor, _vert;
    Real32              _radialDistortion;
    Vec2f               _centerOfDistortion;
    
    // Helper method
    
    void updateGrid(void);
    
    friend class FieldContainer;
    friend class TextureBackgroundBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TextureBackground &source);
};

typedef TextureBackground *TextureBackgroundP;

OSG_END_NAMESPACE

#include <OSGTextureBackgroundBase.inl>
#include <OSGTextureBackground.inl>

#define OSGTEXTUREBACKGROUND_HEADER_CVSID "@(#)$Id: OSGTextureBackground.h,v 1.2 2005/07/06 16:00:44 dirk Exp $"

#endif /* _OSGTEXTUREBACKGROUND_H_ */
