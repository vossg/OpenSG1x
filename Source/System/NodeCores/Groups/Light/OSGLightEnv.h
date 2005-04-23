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


#ifndef _OSGLIGHTENV_H_
#define _OSGLIGHTENV_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGLightEnvBase.h>
#include <OSGNodePtr.h>
#include <OSGAction.h>

OSG_BEGIN_NAMESPACE

/*! \brief LightEnvs Base class
    \ingroup GrpSystemNodeCoresLightEnvs
*/

class OSG_SYSTEMLIB_DLLMAPPING LightEnv : public LightEnvBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField,
                         UInt32    origin   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Dump                                    */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef LightEnvBase      Inherited;


    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LightEnv(void);
    LightEnv(const LightEnv &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LightEnv(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    // generate draw tree
    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LightEnvBase;

    static void initMethod( void );

    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const LightEnv &source);
};

OSG_END_NAMESPACE

#include <OSGLightEnvBase.inl>
#include <OSGLightEnv.inl>

#define OSGLIGHTENV_HEADER_CVSID "@(#)$Id: OSGLightEnv.h,v 1.1 2005/04/23 11:00:58 a-m-z Exp $"

#endif /* _OSGLIGHTENV_H_ */
