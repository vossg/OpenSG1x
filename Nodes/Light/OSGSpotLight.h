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


#ifndef _OSGSPOTLIGHT_H_
#define _OSGSPOTLIGHT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSpotLightBase.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup LightNodes
 *  \brief Spotlight
 */

class OSG_SYSTEMLIB_DLLMAPPING SpotLight : public SpotLightBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "SpotLight"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    inline void    setSpotDirection(Real32 rX, Real32 rY, Real32 rZ);
    inline void    setSpotCutOffDeg(Real32 angle);
    inline Real32  getSpotCutOffDeg(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                        ChangeMode from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Volume                                 */
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
    static Action::ResultE SLightDrawEnter(CNodePtr &cnode,
                                           Action   *pAction);
    static Action::ResultE SLightDrawLeave(CNodePtr &cnode,
                                           Action   *pAction);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SpotLight(void);
    SpotLight(const SpotLight &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SpotLight(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    // execute the OpenGL commands to draw the light
    Action::ResultE drawEnter(Action * action );
    Action::ResultE drawLeave(Action * action );

    // generate drawtree
    Action::ResultE renderEnter(Action * action );
    Action::ResultE renderLeave(Action * action );

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef SpotLightBase Inherited;

    friend class FieldContainer;
    friend class SpotLightBase;

    static char cvsid[];

    static void initMethod( void );

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SpotLight &source);
};

typedef SpotLight *SpotLightP;

OSG_END_NAMESPACE

#include <OSGSpotLight.inl>
#include <OSGSpotLightBase.inl>

#endif /* _OSGSPOTLIGHT_H_ */
