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


#ifndef _OSGLIGHTCHUNK_H_
#define _OSGLIGHTCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGLightChunkBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief class for light source chunks.
 */

class OSG_SYSTEMLIB_DLLMAPPING LightChunk : public LightChunkBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "LightChunk"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Fieldcontainer decklaration                      */
    /*! \{                                                                 */

    virtual const StateChunkClass *  getClass( void ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                        ChangeMode from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector &bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      State                                   */
    /*! \{                                                                 */

    virtual void activate   ( DrawActionBase * action, UInt32 index );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index );

    virtual void deactivate ( DrawActionBase * action, UInt32 index );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual Bool   operator <  (const StateChunk &other) const;

    virtual Bool   operator == (const StateChunk &other) const;
    virtual Bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LightChunk(void);
    LightChunk(const LightChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LightChunk(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef LightChunkBase Inherited;

    friend class FieldContainer;
    friend class LightChunkBase;

    static char cvsid[];

    // class. Used for indexing in State
    static StateChunkClass _class;

    static void initMethod( void );

    // prohibit default functions (move to 'public' if you need one)

    // void operator =(const LightChunk &source);
};

typedef LightChunk *LightChunkP;

OSG_END_NAMESPACE

#include <OSGLightChunk.inl>
#include <OSGLightChunkBase.inl>

#endif /* _OSGLIGHTCHUNK_H_ */
