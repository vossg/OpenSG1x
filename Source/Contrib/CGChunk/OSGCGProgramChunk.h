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

#ifndef _OSGCGPROGRAMCHUNK_H_
#define _OSGCGPROGRAMCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include <map>

#include <OSGCGProgramChunkBase.h>

#include <Cg/cgGL.h>

OSG_BEGIN_NAMESPACE

/*! \brief CGProgramChunk class. See \ref
           PageKernelCGProgramChunk for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING CGProgramChunk : public CGProgramChunkBase
{
  private:

    typedef CGProgramChunkBase Inherited;

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
    /*! \name                 CGProgramChunk Commands                             */
    /*! \{                                                                 */

                 bool    readProgram        (const char   *file);
                 bool    readProgram        (std::istream &stream);
    
                 bool    addParameter(const char   *name, 
                                            Int16   index);                                     
    inline       bool    addParameter(const char   *name, 
                                            Int16   index, 
                                      const Vec4f  &value);
    
           const Vec4f  &getParameter(      Int16        index);
    inline const Vec4f  &getParameter(const char        *name );
    inline const Vec4f  &getParameter(const std::string &name );

                 bool    setParameter(      Int16  index, const Vec4f& value);
    inline       bool    setParameter(const char  *name,  const Vec4f& value);
    inline       bool    setParameter(const std::string &name, 
                                      const Vec4f       & value);

    inline       Int16   findParameter(const char        *name);
                 Int16   findParameter(const std::string &name);

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

    // Variables should all be in CGProgramChunkBase.

    void onCreate(const CGProgramChunk *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CGProgramChunk(void);
    CGProgramChunk(const CGProgramChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CGProgramChunk(void);

    /*! \}                                                                 */

    CGcontext   _context;

    static CGcontext _current_context;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CGProgramChunkBase;

    // class. Used for indexing in State
    static StateChunkClass _class;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGProgramChunk &source);
    
    static void cgErrorCallback(void);

    void parseProgramParams(CGprogram prog);
    void parseParams(CGparameter param);
};

typedef CGProgramChunk *CGProgramChunkP;

OSG_END_NAMESPACE

#include <OSGCGProgramChunkBase.inl>
#include <OSGCGProgramChunk.inl>

#define OSGCGPROGRAMCHUNK_HEADER_CVSID "@(#)$Id: OSGCGProgramChunk.h,v 1.1 2004/02/29 18:40:35 a-m-z Exp $"

#endif /* _OSGCGPROGRAMCHUNK_H_ */
