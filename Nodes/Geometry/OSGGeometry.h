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


#ifndef _OSGGEOMETRY_H_
#define _OSGGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGWindow.h>

#include <OSGGeometryBase.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;

class TriangleIterator;
class PrimitiveIterator;
class FaceIterator;

/*! \ingroup GeometryLib
 *  \brief Geometry base class
 */

class OSG_SYSTEMLIB_DLLMAPPING Geometry : public GeometryBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    static const UInt16 MapPosition;
    static const UInt16 MapNormal;
    static const UInt16 MapColor;
    static const UInt16 MapTexcoords;
    static const UInt16 MapTexcoords2;  // not used yet
    static const UInt16 MapTexcoords3;  // not used yet
    static const UInt16 MapTexcoords4;  // not used yet
    static const UInt16 MapEmpty;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Geometry"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Class Specific                         */
    /*! \{                                                                 */

    static const char *mapType          (UInt8 type);

    virtual void       changed          (BitVector whichField,
                                         ChangeMode from);

    GeometryPtr        getPtr           (void) const;

    void               adjustVolume     (Volume & volume);

    TriangleIterator   beginTriangles   (void) const;
    TriangleIterator   endTriangles     (void) const;
    
    PrimitiveIterator  beginPrimitives  (void) const;
    PrimitiveIterator  endPrimitives    (void) const;

    FaceIterator       beginFaces       (void) const;
    FaceIterator       endFaces         (void) const;

    Int16              calcMappingIndex (UInt16 attrib) const;

    Bool               isMergeable      (const GeometryPtr other);

    Bool               merge            (const GeometryPtr other);

    GeometryPtr        clone            (void);

    virtual void       dump             (      UInt32    uiIndent = 0,
                                         const BitVector bvFlags = 0) const;

    inline void        invalidateDlistCache    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    Action::ResultE doDraw  (Action * action );
    Action::ResultE draw    (DrawActionBase *action);
    Action::ResultE render  (Action *action);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

#ifdef OSG_NOFUNCTORS

    typedef void (Geometry::*FunctorFunc)(Window *, UInt32);

    struct GeoGLObjectFunctor : public Window::GLObjectFunctor
    {
       public:

        GeometryPtr _pObj;
        FunctorFunc     _func;

        virtual void call(Window *win, UInt32 uiOpt)
        {
            (_pObj.getCPtr()->*_func)(win, uiOpt);
        }
    };

    static GeoGLObjectFunctor osgMethodFunctor2CPtr(GeometryPtr pTexChunk,
                                                    FunctorFunc     func)
    {
        GeoGLObjectFunctor result;

        result._pObj = pTexChunk;
        result._func = func;

        return result;
    }
#endif

#ifdef OSG_NOFUNCTORS
    static Action::ResultE GeoDrawEnter(CNodePtr &cnode, Action   *pAction);
    static Action::ResultE GeoRenderEnter(CNodePtr &cnode, Action   *pAction);
    static Action::ResultE GeoIntEnter(CNodePtr &cnode, Action   *pAction);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Geometry(void);
    Geometry(const Geometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Geometry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void handleGL(Window* win, UInt32 id);

    void onCreate(const FieldContainer &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef GeometryBase Inherited;

    friend class FieldContainer;
    friend class GeometryBase;

    static char cvsid[];

    static void initMethod( void );

    void operator =(const Geometry &source);

    // intersect action: ray test
    Action::ResultE intersect(Action * action );

};

typedef Geometry *GeometryP;

OSG_END_NAMESPACE

#include <OSGGeometry.inl>
#include <OSGGeometryBase.inl>

#endif /* _OSGGEOMETRY_H_ */
