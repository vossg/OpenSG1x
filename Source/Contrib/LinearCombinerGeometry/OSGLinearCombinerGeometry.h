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

#ifndef _OSGLINEARCOMBINERGEOMETRY_H_
#define _OSGLINEARCOMBINERGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGLinearCombinerGeometryBase.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING LinearCombinerGeometry : public LinearCombinerGeometryBase
{
  private:

    typedef LinearCombinerGeometryBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

    /*---------------------------------------------------------------------*/
    /*! \name                      Initialization                          */
    /*! \{                                                                 */

	void initWithGeometry( GeometryPtr source);
	void addGeometry( GeometryPtr source, Real32 weight=0.0);

	/*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in LinearCombinerGeometryBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LinearCombinerGeometry(void);
    LinearCombinerGeometry(const LinearCombinerGeometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LinearCombinerGeometry(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Draw                                    */
    /*! \{                                                                 */

    Action::ResultE render(Action *action);

    /*---------------------------------------------------------------------*/
    /*! \name                      NodeCore Specific                       */
    /*! \{                                                                 */
    void               adjustVolume     (Volume & volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Class specific                                */
    /*! \{                                                                 */

        void recalculateGeometry();
        void recalculateBoundingVolumes();
		void recalculateAllgeometry3f();

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LinearCombinerGeometryBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LinearCombinerGeometry &source);
};

// FIXME: Documentation
OSG_SYSTEMLIB_DLLMAPPING
NodePtr     createLinearCombinerStructure(NodePtr source);
OSG_SYSTEMLIB_DLLMAPPING
void        addToLinearCombinerStructure(NodePtr source, NodePtr dest);
OSG_SYSTEMLIB_DLLMAPPING
void 	   getLinearCombinerCores(std::vector<LinearCombinerGeometryPtr> &cores, NodePtr node);



typedef LinearCombinerGeometry *LinearCombinerGeometryP;

OSG_END_NAMESPACE

#include <OSGLinearCombinerGeometryBase.inl>
#include <OSGLinearCombinerGeometry.inl>

#define OSGLINEARCOMBINERGEOMETRY_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.16 2002/10/25 13:09:36 dirk Exp $"

#endif /* _OSGLINEARCOMBINERGEOMETRY_H_ */
