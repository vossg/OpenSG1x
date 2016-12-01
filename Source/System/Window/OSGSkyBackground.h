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

#ifndef _OSGSKYBACKGROUND_H_
#define _OSGSKYBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindow.h"

#include "OSGSkyBackgroundBase.h"

OSG_BEGIN_NAMESPACE

class DrawActionBase;
class Viewport;

/*! \brief Background clearing class using a sky sphere and box. See \ref 
    PageSystemWindowBackgroundSky for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING SkyBackground : public SkyBackgroundBase
{
  private:

    typedef SkyBackgroundBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Background                               */
    /*! \{                                                                 */

    virtual void clear(DrawActionBase *action, Viewport *port);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SkyBackgroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkyBackground(void);
    SkyBackground(const SkyBackground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkyBackground(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void onCreate(const SkyBackground *source = NULL);

    void onDestroy(void);

    void handleGL(Window* win, UInt32 id);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw Helper                                */
    /*! \{                                                                 */

    void drawFace(      DrawActionBase  * action, 
                  const TextureChunkPtr  &tex, 
                        StateChunk      *&oldtex, 
                  const Pnt3f            &p1, 
                  const Pnt3f            &p2, 
                  const Pnt3f            &p3, 
                  const Pnt3f            &p4,  
                  const Vec3f          * texCoord);

    void drawBox(DrawActionBase *action);

    void drawSpheres();

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SkyBackgroundBase;

    static void initMethod(void);

    std::vector<Real32>  _hcos;
    std::vector<Real32>  _hsin;
    std::vector<Real32>  _sky_vcos;
    std::vector<Real32>  _sky_vsin;
    std::vector<Color4f> _skyColor;
    std::vector<Real32>  _ground_vcos;
    std::vector<Real32>  _ground_vsin;
    std::vector<Color4f> _groundColor;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SkyBackground &source);
};

typedef SkyBackground *SkyBackgroundP;

OSG_END_NAMESPACE

#include "OSGSkyBackgroundBase.inl"
#include "OSGSkyBackground.inl"

#define OSGSKYBACKGROUND_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSKYBACKGROUND_H_ */
