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

#ifndef _OSGFOG_H_
#define _OSGFOG_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGNodePtr.h"
#include "OSGAction.h"
#include "OSGFogChunk.h"

#include "OSGFogBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Fog class. See \ref 
           PageSystemFog for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING Fog : public FogBase
{
  private:

    typedef FogBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Chunk                                   */
    /*! \{                                                                 */

			FogChunkPtr getChunk (void);
	virtual void 		makeChunk(void);
    
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

    // Variables should all be in FogBase.

	FogChunkPtr _pChunk;
	
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Fog(void);
    Fog(const Fog &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Fog(void); 

    /*! \}                                                                 */
    
	/*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */
    
	Action::ResultE drawEnter  (Action *action);
    Action::ResultE drawLeave  (Action *action);
	
    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
	
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FogBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Fog &source);
};

typedef Fog *FogP;

OSG_END_NAMESPACE

#include "OSGFogBase.inl"
#include "OSGFog.inl"

#define OSGFOG_HEADER_CVSID "@(#)$Id: OSGFog.h,v 1.1 2009/11/13 15:44:26 yjung Exp $"

#endif /* _OSGFOG_H_ */
