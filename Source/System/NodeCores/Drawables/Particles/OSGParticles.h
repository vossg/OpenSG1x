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

#ifndef _OSGPARTICLES_H_
#define _OSGPARTICLES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGAction.h>

#include <OSGParticlesBase.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;

struct ParticlesDrawer;

class OSG_SYSTEMLIB_DLLMAPPING Particles : public ParticlesBase
{
  private:

    typedef ParticlesBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Modes                                    */
    /*! \{                                                                 */
    
    enum { Points=0, Lines, ViewDirQuads, ViewerQuads, Arrows, 
           ViewerArrows, Rectangles, ShaderQuads, ShaderStrips,
           LastMode }
           ModeE;
    
    enum { Any=0, BackToFront, FrontToBack } DrawOrderE;
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    Action::ResultE drawPrimitives (DrawActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */
    
    void setPositions      (const GeoPositionsPtr &value);
    void setSecPositions      (const GeoPositionsPtr &value);
    void setColors         (const GeoColorsPtr    &value);
    void setNormals        (const GeoNormalsPtr   &value);
    void setMaterial       (const MaterialPtr     &value);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ParticlesBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Particles(void);
    Particles(const Particles &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Particles(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                NodeCore Specific                             */
    /*! \{                                                                 */

    void    adjustVolume(Volume & volume);

    /*! \}                                                                 */
     /*---------------------------------------------------------------------*/
    /*! \name                Particles Specific                            */
    /*! \{                                                                 */

    Int32 *calcIndex(DrawActionBase *action, UInt32 &len, 
                     Int32 *index = NULL);

    ParticlesDrawer *findDrawer(void);
    
    /*! \}                                                                 */
   
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ParticlesBase;

    static void initMethod(void);
    
    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Particles &source);
};

typedef Particles *ParticlesP;

OSG_END_NAMESPACE

#include <OSGParticlesBase.inl>
#include <OSGParticles.inl>

#define OSGPARTICLES_HEADER_CVSID "@(#)$Id: OSGParticles.h,v 1.7 2002/06/01 10:37:24 vossg Exp $"

#endif /* _OSGPARTICLES_H_ */
