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

#include <OSGComponentTransformBase.h>

OSG_BEGIN_NAMESPACE

/*! ComponentTransform provides a vrml style transformation.
 *  \ingroup NodesLib
 */

class OSG_SYSTEMLIB_DLLMAPPING ComponentTransform : public ComponentTransformBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "ComponentTransform"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         ChangeMode from);

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      ComponentTransform Draw                      */
    /*! \{                                                                 */

#ifdef OSG_NOFUNCTORS
    static Action::ResultE ComponentTransformDrawEnter(CNodePtr &cnode,
                                                  Action   *pAction);
    static Action::ResultE ComponentTransformDrawLeave(CNodePtr &cnode,
                                                  Action   *pAction);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ComponentTransform(void);
    ComponentTransform(const ComponentTransform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComponentTransform(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef ComponentTransformBase Inherited;

    friend class FieldContainer;
    friend class ComponentTransformBase;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static void initMethod( void );
    void operator =(const ComponentTransform &source);

    /*! \}                                                                 */
};

typedef ComponentTransform *ComponentTransformP;

OSG_END_NAMESPACE

#include <OSGComponentTransform.inl>
#include <OSGComponentTransformBase.inl>

#endif /* _OSGVRMLTRANSFORM_H_ */
