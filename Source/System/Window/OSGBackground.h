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


#ifndef _OSGBACKGROUND_H_
#define _OSGBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif


#include <OSGConfig.h>

#include <OSGBackgroundBase.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;
class Viewport;

/*! \brief Background clearing base class. See \ref 
    PageSystemWindowBackground for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING Background : public BackgroundBase
{

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const Char8 *getClassname(void) { return "Background"; };

  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access fields                             */
    /*! \{                                                                 */

    virtual void clear( DrawActionBase * action, Viewport * port ) = 0;

     
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

    Background(void);
    Background(const Background &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Background(void); 
  
    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
private:

  
    typedef BackgroundBase Inherited;
  
    friend class FieldContainer;
    friend class BackgroundBase;

    static void initMethod( void );

    void operator =(const Background &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Background *BackgroundP;

OSG_END_NAMESPACE

#include <OSGBackgroundBase.inl>
#include <OSGBackground.inl>

#define OSGBACKGROUND_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGBACKGROUND_H_ */
