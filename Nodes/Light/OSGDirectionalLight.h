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


#ifndef _OSGDIRECTIONALLIGHT_H_
#define _OSGDIRECTIONALLIGHT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGDirectionalLightBase.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup LightNodes
 *  \brief Directional light
 */

class OSG_SYSTEMLIB_DLLMAPPING DirectionalLight : public DirectionalLightBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "DirectionalLight"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

           void setDirection(Real32 rX, Real32 rY, Real32 rZ);
    inline void setDirection( const Vec3f &direction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                        ChangeMode from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void makeChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

#ifdef OSG_NOFUNCTORS
    static Action::ResultE DLightDrawEnter(CNodePtr &cnode,
                                           Action   *pAction);
    static Action::ResultE DLightDrawLeave(CNodePtr &cnode,
                                           Action   *pAction);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DirectionalLight(void);
    DirectionalLight(const DirectionalLight &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DirectionalLight(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Actions                                */
    /*! \{                                                                 */

    // execute the OpenGL commands to draw the light
    Action::ResultE drawEnter(Action * action );
    Action::ResultE drawLeave(Action * action );

    // generate drawtree
    Action::ResultE renderEnter(Action * action);
    Action::ResultE renderLeave(Action * action);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef DirectionalLightBase Inherited;

    friend class FieldContainer;
    friend class DirectionalLightBase;

    static char cvsid[];

    static void initMethod( void );

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DirectionalLight &source);
};

typedef DirectionalLight *DirectionalLightP;

OSG_END_NAMESPACE

#include <OSGDirectionalLight.inl>
#include <OSGDirectionalLightBase.inl>

#endif /* _OSGDIRECTIONALLIGHT_H_ */
