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


#ifndef _OSGLIGHTBASE_H_
#define _OSGLIGHTBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGLightBaseBase.h>
#include <OSGAction.h>
#include <OSGLightChunk.h>

OSG_BEGIN_NAMESPACE

//! LightBase
//! \ingroup LightNodes

class OSG_SYSTEMLIB_DLLMAPPING LightBase : public LightBaseBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void setAmbient (      Real32   rRed, 
                           Real32   rGreen, 
                           Real32   rBlue, 
                           Real32   rAlpha);
    void setDiffuse (      Real32   rRed, 
                           Real32   rGreen, 
                           Real32   rBlue, 
                           Real32   rAlpha);
    void setSpecular(      Real32   rRed, 
                           Real32   rGreen, 
                           Real32   rBlue, 
                           Real32   rAlpha);
    
    void setAmbient (const Color4f &col);
    void setDiffuse (const Color4f &col);
    void setSpecular(const Color4f &col);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Chunk                                   */
    /*! \{                                                                 */

            LightChunkPtr getChunk (void);
    virtual void          makeChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         ChangeMode from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Dump                                    */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef LightBaseBase  Inherited;

            LightChunkPtr _pChunk;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LightBase(void);
    LightBase(const LightBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LightBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */
   
    // Draw action: execute the OpenGL commands to set the light's parameters.
    Action::ResultE drawEnter  (Action *action);
    Action::ResultE drawLeave  (Action *action);

    // generate draw tree
    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LightBaseBase;

    static void initMethod( void );

    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const LightBase &source);
};

OSG_END_NAMESPACE

#include <OSGLightBase.inl>
#include <OSGLightBaseBase.inl>

#define OSGLIGHTBASE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGLIGHTBASE_H_ */
