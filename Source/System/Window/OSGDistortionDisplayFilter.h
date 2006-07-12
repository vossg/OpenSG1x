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

#ifndef _OSGDISTORTIONDISPLAYFILTER_H_
#define _OSGDISTORTIONDISPLAYFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include "OSGDistortionDisplayFilterBase.h"
#include "OSGDisplayFilterForeground.h"

OSG_BEGIN_NAMESPACE

/*! \brief DistortionDisplayFilter class. See \ref 
           PageSystemDistortionDisplayFilter for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING DistortionDisplayFilter : public DistortionDisplayFilterBase
{
  private:

    typedef DistortionDisplayFilterBase Inherited;

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

    // Variables should all be in DistortionDisplayFilterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DistortionDisplayFilter(void);
    DistortionDisplayFilter(const DistortionDisplayFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DistortionDisplayFilter(void); 

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
    friend class DistortionDisplayFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DistortionDisplayFilter &source);
};

typedef DistortionDisplayFilter *DistortionDisplayFilterP;

OSG_END_NAMESPACE

#include "OSGDistortionDisplayFilterBase.inl"
#include "OSGDistortionDisplayFilter.inl"

#define OSGDISTORTIONDISPLAYFILTER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.22 2004/08/03 05:53:03 dirk Exp $"

#endif /* _OSGDISTORTIONDISPLAYFILTER_H_ */
