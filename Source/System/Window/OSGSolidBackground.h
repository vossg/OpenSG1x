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


#ifndef _OSGSOLIDBACKGROUND_H_
#define _OSGSOLIDBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGSolidBackgroundBase.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;
class Viewport;

/*! \brief Single color background clearing class. See \ref 
    PageSystemWindowBackgroundSolid for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING SolidBackground : public SolidBackgroundBase
{
    /*==========================  PUBLIC  =================================*/
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "SolidBackground"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     your_category                            */
    /*! \{                                                                 */

    void clear(DrawActionBase *, Viewport *);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     transformation                           */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   dump                                       */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SolidBackground(void);
    
    SolidBackground(const SolidBackground &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SolidBackground(void); 
    
    /*! \}                                                                 */
    /*=========================  PRIVATE  =================================*/
  private:

    typedef SolidBackgroundBase Inherited;

    friend class FieldContainer;
    friend class SolidBackgroundBase;

    static void initMethod( void );

    void operator =(const SolidBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef SolidBackground *SolidBackgroundP;

OSG_END_NAMESPACE

#include <OSGSolidBackgroundBase.inl>
#include <OSGSolidBackground.inl>

#define OSGSOLIDBACKGROUND_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGSOLIDBACKGROUND_H_ */
