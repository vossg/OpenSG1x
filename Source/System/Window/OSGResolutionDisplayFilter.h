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

#ifndef _OSGRESOLUTIONDISPLAYFILTER_H_
#define _OSGRESOLUTIONDISPLAYFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include "OSGDisplayFilterForeground.h"
#include "OSGResolutionDisplayFilterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ResolutionDisplayFilter class. See \ref 
           PageSystemResolutionDisplayFilter for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ResolutionDisplayFilter : public ResolutionDisplayFilterBase
{
  private:

    typedef ResolutionDisplayFilterBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ResolutionDisplayFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ResolutionDisplayFilter(void);
    ResolutionDisplayFilter(const ResolutionDisplayFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ResolutionDisplayFilter(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   filter handling                            */
    /*! \{                                                                 */

    virtual void createFilter(DisplayFilterForeground *fg,
                              Viewport *port);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ResolutionDisplayFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ResolutionDisplayFilter &source);
};

typedef ResolutionDisplayFilter *ResolutionDisplayFilterP;

OSG_END_NAMESPACE

#include "OSGResolutionDisplayFilterBase.inl"
#include "OSGResolutionDisplayFilter.inl"

#define OSGRESOLUTIONDISPLAYFILTER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.22 2004/08/03 05:53:03 dirk Exp $"

#endif /* _OSGRESOLUTIONDISPLAYFILTER_H_ */
