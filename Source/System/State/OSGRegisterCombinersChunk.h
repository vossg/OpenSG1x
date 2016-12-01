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

#ifndef _OSGREGISTERCOMBINERSCHUNK_H_
#define _OSGREGISTERCOMBINERSCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindow.h"
#include "OSGGL.h"
#include "OSGGLEXT.h"

#include "OSGRegisterCombinersChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief State chunk for register combiners. See \ref
    PageSystemRegisterCombinersChunk for a description.
*/

#define OSG_NUM_COMBINERS 8

class OSG_SYSTEMLIB_DLLMAPPING RegisterCombinersChunk : public RegisterCombinersChunkBase
{
  private:

    typedef RegisterCombinersChunkBase Inherited;

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
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32 from);

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

    virtual void activate   (DrawActionBase * action, UInt32 index = 0);

    virtual void changeFrom (DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0);

    virtual void deactivate (DrawActionBase * action, UInt32 index = 0);

    virtual bool isTransparent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost  (StateChunk * chunk);

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Register Combiner Specific                        */
    /*! \{                                                                 */

    void clearCombiners(void);

    void clearCombiner(UInt16 which);

    void setConstantColors(Color4f &color0, Color4f &color1);

    void setCombinerColors(UInt16 which, 
          Color4f &color0, Color4f &color1);

    void setCombinerRGB(UInt16 which, 
          GLenum ainput, GLenum amapping, GLenum acompusage, 
          GLenum binput, GLenum bmapping, GLenum bcompusage, 
          GLenum cinput, GLenum cmapping, GLenum ccompusage, 
          GLenum dinput, GLenum dmapping, GLenum dcompusage, 
          GLenum outputAB, GLenum outputCD, GLenum outputSum,
          GLenum scale, GLenum bias, 
          GLboolean dotAB, GLboolean dotCD, GLboolean muxSum);

    void setCombinerAlpha(UInt16 which, 
          GLenum ainput, GLenum amapping, GLenum acompusage, 
          GLenum binput, GLenum bmapping, GLenum bcompusage, 
          GLenum cinput, GLenum cmapping, GLenum ccompusage, 
          GLenum dinput, GLenum dmapping, GLenum dcompusage, 
          GLenum outputAB, GLenum outputCD, GLenum outputSum,
          GLenum scale, GLenum bias, 
          GLboolean muxSum);
    
    void setFinalCombiner(
          GLenum ainput, GLenum amapping, GLenum acompusage, 
          GLenum binput, GLenum bmapping, GLenum bcompusage, 
          GLenum cinput, GLenum cmapping, GLenum ccompusage, 
          GLenum dinput, GLenum dmapping, GLenum dcompusage, 
          GLenum einput, GLenum emapping, GLenum ecompusage, 
          GLenum finput, GLenum fmapping, GLenum fcompusage, 
          GLenum ginput, GLenum gmapping, GLenum gcompusage);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in RegisterCombinersChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RegisterCombinersChunk(void);
    RegisterCombinersChunk(const RegisterCombinersChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RegisterCombinersChunk(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helpers                                  */
    /*! \{                                                                 */

    void ensureSizes(void); 

    /*! \}                                                                 */

    // extension indices for used extensions;
    static UInt32 _nvRegisterCombiners;
    static UInt32 _nvRegisterCombiners2;
    
    // extension indices for used functions;
    static UInt32 _funcCombinerParameterfv;
    static UInt32 _funcCombinerStageParameterfv;
    static UInt32 _funcCombinerInput;
    static UInt32 _funcCombinerOutput;
    static UInt32 _funcFinalCombinerInput;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class RegisterCombinersChunkBase;

    static void initMethod(void);

    // class. Used for indexing in State
    static StateChunkClass _class;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const RegisterCombinersChunk &source);
};

typedef RegisterCombinersChunk *RegisterCombinersChunkP;

OSG_END_NAMESPACE

#include "OSGRegisterCombinersChunkBase.inl"
#include "OSGRegisterCombinersChunk.inl"

#define OSGREGISTERCOMBINERSCHUNK_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGREGISTERCOMBINERSCHUNK_H_ */
