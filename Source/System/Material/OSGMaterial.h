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


#ifndef _OSGMATERIAL_H_
#define _OSGMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGTypedFunctors.h>
#include <OSGAction.h>
#include <OSGMaterialBase.h>
#include <OSGState.h>

OSG_BEGIN_NAMESPACE


class Geometry;
class DrawActionBase;

/*! \brief Abstract Material base class. See \ref PageSystemMaterial for a
    description.
*/

class OSG_SYSTEMLIB_DLLMAPPING Material : public MaterialBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Material"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Constants                                 */
    /*! \{                                                                 */

    static const Int32 NoStateSorting;
    static const Int32 TransparencyAutoDetection;
    static const Int32 TransparencyForceTransparent;
    static const Int32 TransparencyForceOpaque;

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

    // TODO: switch geo to functor too, remove makeState, replace by rebuild
    
    typedef TypedFunctor1Base<Action::ResultE, 
                              PtrCallArg<DrawActionBase> > DrawFunctor;

    virtual void       draw          (DrawFunctor& func,
                                      DrawActionBase * action )= 0;

    virtual void       draw          (Geometry* geo,
                                      DrawActionBase * action )= 0;

    virtual StatePtr   makeState     (void)                    = 0;

    virtual void       rebuildState  (void)                    = 0;

    virtual StatePtr   getState      (UInt32 index = 0);
    virtual bool       isMultiPass   (void) const;
    virtual UInt32     getNPasses    (void) const;

    virtual bool       isTransparent (void) const              = 0;

    virtual Int32      getRealSortKey(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual bool operator <  (const Material &other) const;

    virtual bool operator == (const Material &other) const;
    virtual bool operator != (const Material &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:


    StatePtr _pState;  // !!! TODO is that MT safe?
    // Yes, but not efficient. Every material has as many States as there
    // are aspects, each of which itself is threadsafe (i.e. multibuffered).
    // A single State per Material would be better. I'm just not sure how to
    // initialize it. :( DR
    // Actually, no, it isn't!!! Multiple materials updating the same aspect 
    // in different threads make this crash!!! DR


    // Make sure the state is deleted
#if defined(OSG_FIXED_MFIELDSYNC)
    virtual void onDestroyAspect(UInt32 uiId, UInt32 uiAspect);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Material(void);
    Material(const Material &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Material(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef MaterialBase Inherited;

    friend class FieldContainer;
    friend class MaterialBase;

    static void initMethod( void );

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Material &source);
};

typedef Material *MaterialP;

extern OSG_SYSTEMLIB_DLLMAPPING MaterialPtr NullMaterial;

OSG_END_NAMESPACE

#include <OSGMaterialBase.inl>
#include <OSGMaterial.inl>

#define OSGMATERIAL_HEADER_CVSID "@(#)$Id:$"

#endif /* _OSGMATERIAL_H_ */
