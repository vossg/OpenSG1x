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


#ifndef _OSGFOREGROUND_H_
#define _OSGFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGForegroundBase.h"

OSG_BEGIN_NAMESPACE

class DrawActionBase;
class Viewport;

/*! \brief Foreground base class. See \ref 
    PageSystemWindowForegrounds for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING Foreground : public ForegroundBase
{

   /*==========================  PRIVATE =================================*/
 private:

    typedef ForegroundBase Inherited;

   /*==========================  PUBLIC  =================================*/
  public:

   
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    static const char *getClassname(void) { return "Foreground"; };

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
    /*---------------------------------------------------------------------*/
    /*! \name                   draw                                       */
    /*! \{                                                                 */

    virtual void draw( DrawActionBase * action, Viewport * port ) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:


    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
     
    Foreground(void);
    Foreground(const Foreground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                               */
    /*! \{                                                                 */

    virtual ~Foreground(void); 
  
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  
 private:

    friend class FieldContainer;
    friend class ForegroundBase;

    static void initMethod( void );

    void operator =(const Foreground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Foreground *ForegroundP;

OSG_END_NAMESPACE

#include "OSGForegroundBase.inl"
#include "OSGForeground.inl"

#define OSGFOREGROUND_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGFOREGROUND_H_ */

