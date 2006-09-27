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


#ifndef _OSGCHUNKMATERIAL_H_
#define _OSGCHUNKMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGChunkMaterialBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief Material using chunk set.  See \ref 
    PageSystemMaterialChunkMaterial for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ChunkMaterial : public ChunkMaterialBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "ChunkMaterial"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Constants                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField,
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

    virtual void       draw              (DrawFunctor& func,
                                          DrawActionBase * action );

    virtual void       draw              (Geometry* geo,
                                          DrawActionBase * action);

    virtual StatePtr   makeState         (void);

    virtual void       rebuildState      (void);

    virtual bool       isTransparent     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    bool addChunk(StateChunkPtr chunk, Int32 slot = State::AutoSlotReplace);
    bool subChunk(StateChunkPtr chunk, Int32 slot = State::AutoSlotReplace);

    Int32         find(StateChunkPtr chunk);
    StateChunkPtr find(const FieldContainerType &type, 
                       Int32 slot = State::AutoSlotReplace);
    void          clearChunks(void);

    virtual bool operator == (const Material &other);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ChunkMaterial(void);
    ChunkMaterial(const ChunkMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ChunkMaterial(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    void addChunks(StatePtr state);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef ChunkMaterialBase Inherited;

    friend class FieldContainer;
    friend class ChunkMaterialBase;

    static char cvsid[];

    static void initMethod( void );

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ChunkMaterial &source);
};

typedef ChunkMaterial *ChunkMaterialP;

OSG_END_NAMESPACE

#include <OSGChunkMaterialBase.inl>
#include <OSGChunkMaterial.inl>

#define OSGCHUNKMATERIAL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGCHUNKMATERIAL_H_ */
