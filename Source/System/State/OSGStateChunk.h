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


#ifndef _OSGSTATECHUNK_H_
#define _OSGSTATECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGDrawActionBase.h>
#include <OSGStateChunkBase.h>

#include <string>

OSG_BEGIN_NAMESPACE

class TextureTransformChunk;

/*! \brief The classification class for StateChunks, see \ref StateChunkClass
    for a description. 
*/

class OSG_SYSTEMLIB_DLLMAPPING StateChunkClass
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    StateChunkClass( Char8 *name, UInt32 numslots = 1 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Instance Access                              */
    /*! \{                                                                 */

          UInt32   getId       (void) const;
    const Char8   *getName     (void) const;
          Int32    getNumSlots (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Class Access                                */
    /*! \{                                                                 */

           static const Char8 * getName     (UInt32 index);
           static       Int32   getNumSlots (UInt32 index);
    inline static       UInt32  getUsedSlots(void) ;

    typedef std::vector<std::string>::const_iterator iterator;

    static iterator begin();
    static iterator end();
    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  protected:

    friend class TextureTransformChunk;

    void swap(StateChunkClass &other);

  private:

           UInt32               _classId;
    static std::vector<std::string>* _classNames;
    static std::vector<UInt32>* _numslots;
};

/*! \brief The abstract base class for StateChunks, see \ref StateChunk
    for a description. 
 */

class OSG_SYSTEMLIB_DLLMAPPING StateChunk : public StateChunkBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

                         UInt32           getClassId      (void) const;
           virtual const StateChunkClass *getClass        (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    inline static        UInt32           getStaticClassId(void);
    inline static  const StateChunkClass *getStaticClass  (void);

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

    virtual void update        ( DrawActionBase * action );

    virtual void activate      ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom    ( DrawActionBase * action, StateChunk * old,
                                 UInt32 index = 0 );

    virtual void deactivate    ( DrawActionBase * action, UInt32 index = 0 );

    virtual bool isTransparent (void) const;

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

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StateChunk(void);
    StateChunk(const StateChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StateChunk(void);

    /*! \}                                                                 */

    static void initMethod(void);

    /*==========================  PRIVATE  ================================*/
  private:

    typedef StateChunkBase Inherited;

    friend class FieldContainer;
    friend class StateChunkBase;

    static char cvsid[];

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StateChunk &source);
};

typedef StateChunk *StateChunkP;

OSG_END_NAMESPACE

#include <OSGStateChunk.inl>
#include <OSGStateChunkBase.inl>

#endif /* _OSGSTATECHUNK_H_ */
