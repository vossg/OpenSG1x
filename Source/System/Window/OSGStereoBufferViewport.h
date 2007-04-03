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

#ifndef _OSGSTEREOBUFFERVIEWPORT_H_
#define _OSGSTEREOBUFFERVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGStereoBufferViewportBase.h>

OSG_BEGIN_NAMESPACE

class RenderActionBase;

/*! \brief Viewport class for quad-buffered stereo rendering. See \ref 
    PageSystemWindowViewports for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING StereoBufferViewport : public StereoBufferViewportBase
{
  private:

    typedef StereoBufferViewportBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    virtual void activateSize(void);
    virtual void activate    (void);
    virtual void deactivate  (void);
    virtual void draw        (DrawAction       *action);
    virtual void render      (RenderActionBase *action);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in StereoBufferViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StereoBufferViewport(void);
    StereoBufferViewport(const StereoBufferViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StereoBufferViewport(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class StereoBufferViewportBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const StereoBufferViewport &source);
};

typedef StereoBufferViewport *StereoBufferViewportP;

OSG_END_NAMESPACE

#include <OSGStereoBufferViewportBase.inl>
#include <OSGStereoBufferViewport.inl>

#define OSGSTEREOBUFFERVIEWPORT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSTEREOBUFFERVIEWPORT_H_ */
