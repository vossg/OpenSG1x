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

#ifndef _OSGCOLORMASKCHUNK_H_
#define _OSGCOLORMASKCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGColorMaskChunkBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief ColorMaskChunk class. See \ref
           PageSystemColorMaskChunk for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ColorMaskChunk : public ColorMaskChunkBase
{
  private:

    typedef ColorMaskChunkBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
  
    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

           virtual const StateChunkClass * getClass         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    inline static        UInt32            getStaticClassId (void);
    inline static  const StateChunkClass * getStaticClass   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void activate   ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0 );

    virtual void deactivate ( DrawActionBase * action, UInt32 index = 0 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
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
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setMask(  const bool &r, 
                    const bool &g, 
                    const bool &b, 
                    const bool &a );
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ColorMaskChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ColorMaskChunk(void);
    ColorMaskChunk(const ColorMaskChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorMaskChunk(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ColorMaskChunkBase;

    // class. Used for indexing in State
    static StateChunkClass _class;
    
    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ColorMaskChunk &source);
};

typedef ColorMaskChunk *ColorMaskChunkP;

OSG_END_NAMESPACE

#include <OSGColorMaskChunkBase.inl>
#include <OSGColorMaskChunk.inl>

#define OSGCOLORMASKCHUNK_HEADER_CVSID "@(#)$Id: OSGColorMaskChunk.h,v 1.1 2005/06/06 17:14:20 yjung Exp $"

#endif /* _OSGCOLORMASKCHUNK_H_ */
