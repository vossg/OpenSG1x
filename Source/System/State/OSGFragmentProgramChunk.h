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

#ifndef _OSGFRAGMENTPROGRAMCHUNK_H_
#define _OSGFRAGMENTPROGRAMCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGFragmentProgramChunkBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief FragmentProgramChunk class. See \ref 
           PageSystemFragmentProgramChunk for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING FragmentProgramChunk : public FragmentProgramChunkBase
{
  private:

    typedef FragmentProgramChunkBase Inherited;

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
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FragmentProgramChunkBase.

     /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate(const FragmentProgramChunk *source = NULL);

    /*! \}                                                                 */
   /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FragmentProgramChunk(void);
    FragmentProgramChunk(const FragmentProgramChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FragmentProgramChunk(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Program-Specific Methods                         */
    /*! \{                                                                 */

    virtual       UInt32  getExtension(void)  const; 
    virtual       GLenum  getTarget(void)     const; 
    virtual const char   *getTargetName(void) const; 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FragmentProgramChunkBase;

    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _arbFragmentProgram;

    /*! \}                                                                 */

    static void initMethod(void);

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    void handleGL(Window *win, UInt32 id);
    
    /*! \}                                                                 */

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FragmentProgramChunk &source);
};

typedef FragmentProgramChunk *FragmentProgramChunkP;

OSG_END_NAMESPACE

#include <OSGFragmentProgramChunkBase.inl>
#include <OSGFragmentProgramChunk.inl>

#define OSGFRAGMENTPROGRAMCHUNK_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFRAGMENTPROGRAMCHUNK_H_ */
