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

#ifndef _OSGPOINTLIGHT_H_
#define _OSGPOINTLIGHT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGPointLightBase.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup LightNodes
 *  \brief Pointlight
 */

class OSG_SYSTEMLIB_DLLMAPPING PointLight : public PointLightBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "PointLight"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access Fields                            */
    /*! \{                                                                 */

    void setPosition(Real32 rX, Real32 rY, Real32 rZ);
    inline void setPosition(const Pnt3f & pos);
    void setAttenuation(Real32 rConstant,
                        Real32 rLinear,
                        Real32 rQuadratic);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Access                                */
    /*! \{                                                                 */

    virtual void makeChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                        ChangeMode from);

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
    static Action::ResultE PLightDrawEnter(CNodePtr &cnode,
                                           Action   *pAction);
    static Action::ResultE PLightDrawLeave(CNodePtr &cnode,
                                           Action   *pAction);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PointLight(void);
    PointLight(const PointLight &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PointLight(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    // execute the OpenGL commands to draw the light
    Action::ResultE drawEnter(Action * action );
    Action::ResultE drawLeave(Action * action );

    // generate draw tree
    Action::ResultE renderEnter(Action * action);
    Action::ResultE renderLeave(Action * action);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef PointLightBase Inherited;

    friend class FieldContainer;
    friend class PointLightBase;

    static char cvsid[];

    static void initMethod( void );

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PointLight &source);
};

typedef PointLight *PointLightP;

OSG_END_NAMESPACE

#include <OSGPointLight.inl>
#include <OSGPointLightBase.inl>

#endif /* _OSGPOINTLIGHT_H_ */
