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

#ifndef _OSGSHLPARAMETERCHUNK_H_
#define _OSGSHLPARAMETERCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGDrawActionBase.h>
#include <OSGWindow.h>

#include "OSGSHLChunk.h"

#include "OSGSHLParameterChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SHLParameterChunk class. See \ref
           PageKernelSHLParameterChunk for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING SHLParameterChunk : public SHLParameterChunkBase
{
  private:

    typedef SHLParameterChunkBase Inherited;

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

    // Variables should all be in SHLParameterChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SHLParameterChunk(void);
    SHLParameterChunk(const SHLParameterChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SHLParameterChunk(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SHLParameterChunkBase;

    // class. Used for indexing in State
    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _shl_extension;

    /*! \}                                                                 */

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SHLParameterChunk &source);

    void updateProgram(Window *win);
    void updateParameters(Window *win);
};

typedef SHLParameterChunk *SHLParameterChunkP;

OSG_END_NAMESPACE

#include <OSGSHLParameterChunkBase.inl>
#include <OSGSHLParameterChunk.inl>

#define OSGSHLPARAMETERCHUNK_HEADER_CVSID "@(#)$Id: OSGSHLParameterChunk.h,v 1.2 2004/08/27 12:50:51 a-m-z Exp $"

#endif /* _OSGSHLPARAMETERCHUNK_H_ */
