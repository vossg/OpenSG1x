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


#ifndef _OSGSTATESORTINGGROUP_H_
#define _OSGSTATESORTINGGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGStateSortingGroupBase.h>
#include <OSGNodePtr.h>
#include <OSGAction.h>

OSG_BEGIN_NAMESPACE

/*! \brief StateSortingGroups Base class
    \ingroup GrpSystemNodeCoresStateSortingGroups
*/

class OSG_SYSTEMLIB_DLLMAPPING StateSortingGroup : public StateSortingGroupBase
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

    typedef StateSortingGroupBase      Inherited;


    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StateSortingGroup(void);
    StateSortingGroup(const StateSortingGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StateSortingGroup(void);

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

    bool _sorting_state;

    friend class FieldContainer;
    friend class StateSortingGroupBase;

    static void initMethod( void );

    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const StateSortingGroup &source);
};

OSG_END_NAMESPACE

#include <OSGStateSortingGroupBase.inl>
#include <OSGStateSortingGroup.inl>

#define OSGSTATESORTINGGROUP_HEADER_CVSID "@(#)$Id: OSGStateSortingGroup.h,v 1.1 2005/04/06 09:35:00 a-m-z Exp $"

#endif /* _OSGSTATESORTINGGROUP_H_ */
