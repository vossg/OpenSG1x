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


#ifndef _OSGGROUP_H_
#define _OSGGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGAction.h>
#include <OSGGroupBase.h>

OSG_BEGIN_NAMESPACE

/*! Group is the basic NodeCore for inner nodes in the tree.
 *  \ingroup NodesLib
 */

class OSG_SYSTEMLIB_DLLMAPPING Group : public GroupBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Group"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Static Action Callbacks                    */
    /*! \{                                                                 */

#ifdef OSG_NOFUNCTORS
    static Action::ResultE GroupDrawEnter(CNodePtr &cnode,
                                          Action   *pAction);
    static Action::ResultE GroupDrawLeave(CNodePtr &cnode,
                                          Action   *pAction);
	static Action::ResultE GroupIntEnter(CNodePtr  &cnode,
										 Action    *pAction);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         ChangeMode from);

    virtual void dump   (UInt32     uiIndent = 0,
                         const BitVector &bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    Action::ResultE drawEnter(Action * action );
    Action::ResultE drawLeave(Action * action );
	Action::ResultE intersect(Action * action );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Group(void);
    Group(const Group &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Group(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef GroupBase Inherited;

    friend class FieldContainer;
    friend class GroupBase;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static void initMethod( void );
    void operator =(const Group &source);

    /*! \}                                                                 */
};

typedef Group *GroupP;

OSG_END_NAMESPACE

#include <OSGGroup.inl>
#include <OSGGroupBase.inl>

#endif /* _OSGGROUP_H_ */
