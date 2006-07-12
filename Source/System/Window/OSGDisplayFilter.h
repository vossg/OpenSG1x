/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGDISPLAYFILTER_H_
#define _OSGDISPLAYFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGViewport.h>

#include "OSGDisplayFilterBase.h"

OSG_BEGIN_NAMESPACE

class DisplayFilterForeground;

/*! \brief DisplayFilter class. See \ref 
           PageSystemDisplayFilter for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING DisplayFilter : public DisplayFilterBase
{
  private:

    typedef DisplayFilterBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   filter handling                            */
    /*! \{                                                                 */

    virtual void createFilter(DisplayFilterForeground *fg,
                              Viewport *port) = 0;
    virtual void updateFilter(Viewport *port);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   changed handling                           */
    /*! \{                                                                 */

    UInt32 getChanged( void );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DisplayFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DisplayFilter(void);
    DisplayFilter(const DisplayFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DisplayFilter(void); 

    /*! \}                                                                 */

    UInt32 _changed;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DisplayFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DisplayFilter &source);
};

typedef DisplayFilter *DisplayFilterP;

OSG_END_NAMESPACE

#include "OSGDisplayFilterBase.inl"
#include "OSGDisplayFilter.inl"

#define OSGDISPLAYFILTER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.22 2004/08/03 05:53:03 dirk Exp $"

#endif /* _OSGDISPLAYFILTER_H_ */
