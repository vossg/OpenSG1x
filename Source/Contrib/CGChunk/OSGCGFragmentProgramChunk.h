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

#ifndef _OSGCGFRAGMENTPROGRAMCHUNK_H_
#define _OSGCGFRAGMENTPROGRAMCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include <OSGCGFragmentProgramChunkBase.h>

#include <Cg/cgGL.h>

OSG_BEGIN_NAMESPACE

/*! \brief CGFragmentProgramChunk class. See \ref
           PageKernelCGFragmentProgramChunk for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING CGFragmentProgramChunk : public CGFragmentProgramChunkBase
{
  private:

    typedef CGFragmentProgramChunkBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    virtual const StateChunkClass * getClass         (void) const;

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
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void activate   ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0 );

    virtual void deactivate ( DrawActionBase * action, UInt32 index = 0 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CGFragmentProgramChunkBase.

    void onCreate(const CGFragmentProgramChunk *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CGFragmentProgramChunk(void);
    CGFragmentProgramChunk(const CGFragmentProgramChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CGFragmentProgramChunk(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CGFragmentProgramChunkBase;

    // class. Used for indexing in State
    static StateChunkClass _class;

    static void initMethod(void);

    void handleGL(Window *win, UInt32 id);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGFragmentProgramChunk &source);

    bool hasFP(void);

    CGprogram   _fProgram;
    bool        _fp_isvalid;
    
    void updateCGContext(void);
};

typedef CGFragmentProgramChunk *CGFragmentProgramChunkP;

OSG_END_NAMESPACE

#include <OSGCGFragmentProgramChunkBase.inl>
//#include <OSGCGFragmentProgramChunk.inl>

#define OSGCGFRAGMENTPROGRAMCHUNK_HEADER_CVSID "@(#)$Id: OSGCGFragmentProgramChunk.h,v 1.1 2004/02/29 18:40:35 a-m-z Exp $"

#endif /* _OSGCGFRAGMENTPROGRAMCHUNK_H_ */
