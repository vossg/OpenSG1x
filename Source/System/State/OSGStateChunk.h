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


// little helper class to wrap and create chunk ids
// the id is a low int to index into the state's chunk vector
// A static instance of this is part of every new chunk class

class OSG_SYSTEMLIB_DLLMAPPING StateChunkClass
{
  public:

    StateChunkClass( Char8 *name, UInt32 numslots = 1 );

    // get name and id of this class
          UInt32   getID       ( void ) const;
    const Char8   *getName     ( void ) const;
          Int32    getNumSlots ( void ) const;

    // get name and id of indicated class
    static const Char8 * getName     ( UInt32 index ) ;
    static       Int32   getNumSlots ( UInt32 index ) ;

    // access to the class name list
    typedef std::vector<std::string>::const_iterator iterator;

    static iterator begin();
    static iterator end();

  private:

           UInt32                    _classId;
    static std::vector<std::string> *_classNames;
    static std::vector<     UInt32> *_numslots;
};

//! StateChunk base class
//! \ingroup StateChunks

class OSG_SYSTEMLIB_DLLMAPPING StateChunk : public StateChunkBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "StateChunk"; };

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

    virtual void activate   ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0 );

    virtual void deactivate ( DrawActionBase * action, UInt32 index = 0 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

                   UInt32            getClassID  (void) const;
    virtual const  StateChunkClass * getClass    (void) const;

    virtual bool   isTransparent                 (void) const;

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

    /*==========================  PRIVATE  ================================*/
  private:

    typedef StateChunkBase Inherited;

    friend class FieldContainer;
    friend class StateChunkBase;

    static char cvsid[];

    static void initMethod( void );

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StateChunk &source);
};

typedef StateChunk *StateChunkP;

OSG_END_NAMESPACE

#include <OSGStateChunk.inl>
#include <OSGStateChunkBase.inl>

#endif /* _OSGSTATECHUNK_H_ */
