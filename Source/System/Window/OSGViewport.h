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


#ifndef _OSGVIEWPORT_H_
#define _OSGVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGViewportBase.h>

OSG_BEGIN_NAMESPACE

class DrawAction;
class RenderActionBase;

/*! \brief Viewport base class. See \ref 
    PageSystemWindowViewports for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING Viewport : public ViewportBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    static const char *getClassname(void) { return "Viewport"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

    void setSize(Real32 left,  Real32 bottom, 
                 Real32 right, Real32 top);
    
    Int32 getPixelLeft  (void) const;
    Int32 getPixelRight (void) const;
    Int32 getPixelBottom(void) const;
    Int32 getPixelTop   (void) const;
    Int32 getPixelWidth (void) const;
    Int32 getPixelHeight(void) const;
    
    bool isFullWindow( void ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

    void clearForegrounds(void                     );
    void addForeground   (ForegroundPtr pForeground);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    virtual void activateSize(void);
    virtual void activate    (void);
    virtual void deactivate  (void);
    virtual void draw        (DrawAction       *action);
    virtual void render      (RenderActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   change                                     */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

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
    Viewport(void);
    Viewport(const Viewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Viewport(void); 
    
    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
 private:

    typedef ViewportBase Inherited;

    friend class FieldContainer;
    friend class ViewportBase;

    static void initMethod( void );

    void operator =(const Viewport &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Viewport *ViewportP;

OSG_END_NAMESPACE

#include <OSGViewportBase.inl>
#include <OSGViewport.inl>

#define OSGVIEWPORT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGVIEWPORT_H_ */
