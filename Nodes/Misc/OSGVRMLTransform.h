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

#ifndef _OSGVRMLTRANSFORM_H_
#define _OSGVRMLTRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGVRMLTransformBase.h>

OSG_BEGIN_NAMESPACE

/*! VRMLTransform provides a vrml style transformation.
 *  \ingroup NodesLib
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLTransform : public VRMLTransformBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "VRMLTransform"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         ChangeMode from);

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector &bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      VRMLTransform Draw                      */
    /*! \{                                                                 */

#ifdef OSG_NOFUNCTORS
    static Action::ResultE VRMLTransformDrawEnter(CNodePtr &cnode,
                                                  Action   *pAction);
    static Action::ResultE VRMLTransformDrawLeave(CNodePtr &cnode,
                                                  Action   *pAction);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLTransform(void);
    VRMLTransform(const VRMLTransform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VRMLTransform(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLTransformBase Inherited;

    friend class FieldContainer;
    friend class VRMLTransformBase;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static void initMethod( void );
    void operator =(const VRMLTransform &source);

    /*! \}                                                                 */
};

typedef VRMLTransform *VRMLTransformP;

OSG_END_NAMESPACE

#include <OSGVRMLTransform.inl>
#include <OSGVRMLTransformBase.inl>

#endif /* _OSGVRMLTRANSFORM_H_ */
