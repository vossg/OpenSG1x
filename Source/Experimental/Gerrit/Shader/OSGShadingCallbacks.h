/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGSHADINGCALLBACKS_H_
#define _OSGSHADINGCALLBACKS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGShaderBase.h>
#include <OSGAction.h>

OSG_BEGIN_NAMESPACE

class Light;

//! Brief
//! \ingroup baselib

class OSG_SHADER_DLLMAPPING ShadingCallbacks //: public PARENTCLASS
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      init                                    */
    /*! \{                                                                 */

    static void initialize(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

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
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ShadingCallbacks(void);
    virtual ~ShadingCallbacks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    static Action::ResultE billboardRenderEnter  (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE billboardRenderLeave  (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE compTransRenderEnter  (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE compTransRenderLeave  (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE dirlightRenderEnter   (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE dirlightRenderLeave   (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE distanceLODRender     (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE groupRenderEnter      (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE groupRenderLeave      (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE lightRenderEnter      (Light    *pLight, 
                                                  Action   *action);
    static Action::ResultE lightRenderLeave      (Light    *pLight, 
                                                  Action   *action);


    static Action::ResultE matGroupRenderEnter   (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE matGroupRenderLeave   (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE matDrawableRenderEnter(CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE matDrawableRenderLeave(CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE pointlightRenderEnter (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE pointlightRenderLeave (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE spotlightRenderEnter  (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE spotlightRenderLeave  (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE switchRender          (CNodePtr &pNode, 
                                                  Action   *action);


    static Action::ResultE transformRenderEnter  (CNodePtr &pNode, 
                                                  Action   *action);
    static Action::ResultE transformRenderLeave  (CNodePtr &pNode, 
                                                  Action   *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

//    typedef PARENTCLASS Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ShadingCallbacks(const ShadingCallbacks &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ShadingCallbacks &source);
};

OSG_END_NAMESPACE

#define OSGSHADINGCALLBACKS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSHADINGCALLBACKS_H_ */
