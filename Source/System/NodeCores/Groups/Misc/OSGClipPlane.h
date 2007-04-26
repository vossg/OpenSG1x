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


#ifndef _OSGCLIPPLANE_H_
#define _OSGCLIPPLANE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGClipPlaneBase.h>
#include <OSGNodePtr.h>
#include <OSGAction.h>
#include <OSGSClipPlaneChunk.h>

OSG_BEGIN_NAMESPACE

/*! \brief ClipPlanes Base class
    \ingroup GrpSystemNodeCoresClipPlanes
*/

class OSG_SYSTEMLIB_DLLMAPPING ClipPlane : public ClipPlaneBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Chunk                                   */
    /*! \{                                                                 */

            SClipPlaneChunkPtr getChunk (void);
    virtual void          makeChunk(void);

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

    typedef ClipPlaneBase      Inherited;

            SClipPlaneChunkPtr _pChunk;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ClipPlane(void);
    ClipPlane(const ClipPlane &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ClipPlane(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */
   
    // Draw action: execute the OpenGL commands to set the light's parameters.
    //Action::ResultE drawEnter  (Action *action);
    //Action::ResultE drawLeave  (Action *action);

    // generate draw tree
    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ClipPlaneBase;

    static void initMethod( void );

    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const ClipPlane &source);
};

OSG_END_NAMESPACE

#include <OSGClipPlaneBase.inl>
#include <OSGClipPlane.inl>

#define OSGCLIPPLANE_HEADER_CVSID "@(#)$Id: OSGClipPlane.h,v 1.1 2007/04/26 15:22:01 a-m-z Exp $"

#endif /* _OSGCLIPPLANE_H_ */
