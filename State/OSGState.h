/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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


#ifndef _OSGSTATE_H_
#define _OSGSTATE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGStateBase.h>
#include <OSGStateChunk.h>

OSG_BEGIN_NAMESPACE

/*! \brief State base class
 *  \ingroup StateLib
 */

class OSG_SYSTEMLIB_DLLMAPPING State : public StateBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "State"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      State                                   */
    /*! \{                                                                 */

    void activate   (DrawActionBase *action);

    void changeFrom (DrawActionBase *action, State *old);

    void deactivate (DrawActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    StateChunkPtr getChunk     ( UInt32 id );

    bool          chunkPresent ( UInt32 id );
    bool          chunkPresent ( StateChunkPtr chunk );

    void           addChunk     ( StateChunkPtr chunk, Int32 index = -1 );

    void           subChunk     ( StateChunkPtr chunk, Int32 index = -1 );

    void           subChunk     ( UInt32 classid, Int32 index = -1 );

    void           clearChunks  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( State * state );

    virtual bool   operator <  (const State &other) const;

    virtual bool   operator == (const State &other) const;
    virtual bool   operator != (const State &other) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    State(void);
    State(const State &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~State(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef StateBase Inherited;

    friend class FieldContainer;
    friend class StateBase;

    static char cvsid[];

    static void initMethod( void );

    void operator =(const State &source);
};

typedef State *StateP;

OSG_END_NAMESPACE

#include <OSGStateBase.inl>
#include <OSGState.inl>

#endif /* _OSGSTATE_H_ */
