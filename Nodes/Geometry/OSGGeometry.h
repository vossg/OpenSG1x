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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGWindow.h>

#include <OSGGeometryBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class DrawActionBase;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

// Iterators
class TriangleIterator;
class PrimitiveIterator;
class FaceIterator;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLib
 *  \brief Geometry base class
 */

class OSG_SYSTEMLIB_DLLMAPPING Geometry : public GeometryBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    // Mapping constants
    
    static const UInt16 MapPosition;
    static const UInt16 MapNormal;
    static const UInt16 MapColor;
    static const UInt16 MapTexcoords;
    static const UInt16 MapTexcoords2;	// not used yet
    static const UInt16 MapTexcoords3;	// not used yet
    static const UInt16 MapTexcoords4;	// not used yet
    static const UInt16 MapEmpty;
   
    
    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Geometry"; };

    // map the primitive type to a name
    static const char *mapType( UInt8 type );
     
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------


    virtual void changed(BitVector  whichField, 
                         ChangeMode from);

    /** pointer */

    GeometryPtr getPtr(void) const;
    
    /** updates */
    
    void adjustVolume( Volume & volume );
    
    /** Triangle iterator functions */
    
	TriangleIterator beginTriangles( void ) const;
	TriangleIterator endTriangles  ( void ) const;

    
    /** Primitive iterator functions */

	PrimitiveIterator beginPrimitives( void ) const;
	PrimitiveIterator endPrimitives  ( void ) const;
	
    
    /** Face iterator functions */

	FaceIterator beginFaces( void ) const;
	FaceIterator endFaces  ( void ) const;

    /** calc the inverse property mappings */
    
    Int16 calcMappingIndex( UInt16 attrib ) const;
   

    /** check if the geometry can be merged into this one, return true if yes */
    
    Bool isMergeable( const GeometryPtr other );

    /** merge the geometry into this one, return true if successful */
    
    Bool merge( const GeometryPtr other );

    /** create a deep copy of the geometry */
    
    GeometryPtr clone( void );

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

    /*--------------------------- gl objects --------------------------------*/
    
    inline void invalidateDlistCache(void);

    /*------------------------------ Actions --------------------------------*/
	
	// execute the OpenGL commands to draw the geometry	
	Action::ResultE doDraw(Action * action );
	
	// low-level OpenGL calls, ignoring materials	
	Action::ResultE draw(DrawActionBase *action);

    // generate draw tree
    Action::ResultE render(Action *action);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

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


    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

#ifdef OSG_NOFUNCTORS
    static Action::ResultE GeoDrawEnter(CNodePtr &cnode, 
                                        Action   *pAction);

    static Action::ResultE GeoRenderEnter(CNodePtr &cnode, 
                                        Action   *pAction);

    static Action::ResultE GeoIntEnter(CNodePtr &cnode, 
                                       Action   *pAction);
#endif

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    // They should all be in GeometryBase.

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Geometry(void);
    Geometry(const Geometry &source);
    virtual ~Geometry(void); 

    void handleGL( Window* win, UInt32 id );
    
    void onCreate(const FieldContainer &source);
    
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef GeometryBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;
    friend class GeometryBase;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void initMethod( void );

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Geometry &source);
	
	// intersect action: ray test	
	Action::ResultE intersect(Action * action );

};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef Geometry *GeometryP;

/** empty geometry instance
 */
extern OSG_SYSTEMLIB_DLLMAPPING GeometryPtr NullGeo;

OSG_END_NAMESPACE

#include <OSGGeometry.inl>
#include <OSGGeometryBase.inl>

#endif /* _OSGGEOMETRY_H_ */
