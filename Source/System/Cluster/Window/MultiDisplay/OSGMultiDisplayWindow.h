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

#ifndef _OSGMULTIDISPLAYWINDOW_H_
#define _OSGMULTIDISPLAYWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGMultiDisplayWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Class to manage multiple displays for clusters, see \ref 
    PageSystemClusterMultiDisplayWindow for details.
 */

class OSG_SYSTEMLIB_DLLMAPPING MultiDisplayWindow : public MultiDisplayWindowBase
{
  private:

    typedef MultiDisplayWindowBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name      server window funcitons                                 */
    /*! \{                                                                 */

    virtual void serverInit   ( WindowPtr window,UInt32 id  );
    virtual void serverRender ( WindowPtr window,UInt32 id,
                                RenderActionBase *action    );
    virtual void serverSwap   ( WindowPtr window,UInt32 id  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      client window funcitons                                 */
    /*! \{                                                                 */

    virtual void clientInit              ( void                        );
    virtual void clientSwap              ( void                        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiDisplayWindow(void);
    MultiDisplayWindow(const MultiDisplayWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiDisplayWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Helper                                     */
    /*! \{                                                                 */

    void updateViewport(ViewportPtr &serverPort,ViewportPtr &clientPort); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:
    friend class FieldContainer;
    friend class MultiDisplayWindowBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MultiDisplayWindow &source);
};

typedef MultiDisplayWindow *MultiDisplayWindowP;

OSG_END_NAMESPACE

#include "OSGMultiDisplayWindow.inl"
#include "OSGMultiDisplayWindowBase.inl"

#define OSGMULTIDISPLAYCONFIG_HEADER_CVSID "@(#)$Id:$"

#endif /* _OSGMULTIDISPLAYCONFIG_H_ */

