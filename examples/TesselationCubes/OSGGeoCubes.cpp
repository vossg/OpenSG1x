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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEMYLIB

#include <OpenSG/OSGConfig.h>


#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGDrawAction.h>     
#include <OpenSG/OSGRenderAction.h>   
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGMaterial.h>

#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGGeoProperty.h>

#include "OSGGeoCubes.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGGeoCubes.cpp,v 1.1 2002/05/13 10:53:40 dirk Exp $";
    static char cvsid_hpp[] = OSGGEOCUBES_HEADER_CVSID;
    static char cvsid_inl[] = OSGGEOCUBES_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::GeoCubes

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

GeoCubes::GeoCubes(void) :
    Inherited()
{
}

//! Copy Constructor

GeoCubes::GeoCubes(const GeoCubes &source) :
    Inherited(source)
{
}

//! Destructor

GeoCubes::~GeoCubes(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void GeoCubes::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GeoCubesPtr,
                                          CNodePtr,  
                                          Action *>(&Geometry::doDraw));

    IntersectAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,   
                                          GeoCubesPtr,
                                          CNodePtr,  
                                          Action *>(&Geometry::intersect));

    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GeoCubesPtr,
                                          CNodePtr,  
                                          Action *>(&Geometry::render));


}

//! react to field changes

void GeoCubes::changed(BitVector whichField, ChangeMode from)
{
//  SLOG << "Geocubes::changed in..." << endl;
  if (whichField & PositionFieldMask ||
      whichField & LengthFieldMask ||
      whichField & ColorFieldMask) {
//      SLOG << "Geocubes::changed: need to retessellate " << endl;
      tessellate(); // we have to retessellate
  }

  // you should call the parent's changed() function in case
  // it needs to update inherited fields.
  Geometry::changed( whichField, from );
}

//! tessellate: generate the geometry
void GeoCubes::tessellate(void)
{
//  SLOG << "tessellate called..." << endl;

    if ( getMFPosition()->getSize() != getMFLength()->getSize() ||
         getMFPosition()->getSize() != getMFColor()->getSize() ) 
    {
         SWARNING << "GeoCubes::tessellate: inconsistent attributes!" << endl;
         return;
    }


    GeoPTypesPtr gtypes = getTypes();
    if ( gtypes == NullFC ) 
    {
        //if it's NULL it wasn't used before -> you have to create it
        gtypes = GeoPTypesUI8::create();
    }
    beginEditCP(gtypes, GeoPTypesUI8::GeoPropDataFieldMask);
        gtypes->clear();
        gtypes->addValue(GL_QUADS);
    endEditCP  (gtypes, GeoPTypesUI8::GeoPropDataFieldMask);

    GeoPLengthsPtr glens = getLengths();
    if ( glens == NullFC ) 
    {
        //if it's NULL it wasn't used before -> you have to create it
        glens = GeoPLengthsUI32::create();
    }
    UInt32 numcubes = getMFPosition()->getSize();
    beginEditCP(glens, GeoPLengthsUI32::GeoPropDataFieldMask);
        glens->clear();
        glens->addValue( numcubes * 4 * 6 );
    endEditCP  (glens, GeoPLengthsUI32::GeoPropDataFieldMask);

    GeoPositionsPtr gpos = getPositions();
    if ( gpos == NullFC )
    {
        //if it's NULL it wasn't used before -> you have to create it
        gpos = GeoPositions3f::create();
    }
    MFPnt3f   *pos = getMFPosition();
    MFColor3f *col = getMFColor();
    MFReal32  *len = getMFLength();
 
    beginEditCP( gpos );
        gpos->clear();
        for ( UInt32 i = 0; i < numcubes; i++ )
        {
            Pnt3f p = pos->getValue( i );       
            Real32 l = len->getValue( i ) / 2.f;
            gpos->addValue( Pnt3f( p[0] - l, p[1] - l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] - l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] + l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] - l, p[1] + l, p[2] - l ));

            gpos->addValue( Pnt3f( p[0] - l, p[1] - l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] - l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] + l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] - l, p[1] + l, p[2] + l ));
        
            gpos->addValue( Pnt3f( p[0] - l, p[1] - l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] - l, p[1] - l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] - l, p[1] + l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] - l, p[1] + l, p[2] - l ));
        
            gpos->addValue( Pnt3f( p[0] + l, p[1] - l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] - l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] + l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] + l, p[2] + l ));
        
            gpos->addValue( Pnt3f( p[0] - l, p[1] + l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] + l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] + l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] - l, p[1] + l, p[2] - l ));
        
            gpos->addValue( Pnt3f( p[0] - l, p[1] - l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] - l, p[2] - l ));
            gpos->addValue( Pnt3f( p[0] + l, p[1] - l, p[2] + l ));
            gpos->addValue( Pnt3f( p[0] - l, p[1] - l, p[2] + l ));

        }
    endEditCP  ( gpos );

    GeoNormalsPtr gnorms = getNormals();
    if ( gnorms == NullFC )
    {
        //if it's NULL it wasn't used before -> you have to create it
        gnorms = GeoNormals3f::create();
    }
    beginEditCP( gnorms );
        gnorms->clear();
        for ( UInt32 i = 0; i < numcubes; i++ )
        {
            gnorms->addValue( Vec3f( 0, 0, -1 ));
            gnorms->addValue( Vec3f( 0, 0, -1 ));
            gnorms->addValue( Vec3f( 0, 0, -1 ));
            gnorms->addValue( Vec3f( 0, 0, -1 ));

            gnorms->addValue( Vec3f( 0, 0, 1 ));
            gnorms->addValue( Vec3f( 0, 0, 1 ));
            gnorms->addValue( Vec3f( 0, 0, 1 ));
            gnorms->addValue( Vec3f( 0, 0, 1 ));

            gnorms->addValue( Vec3f( -1, 0, 0 ));
            gnorms->addValue( Vec3f( -1, 0, 0 ));
            gnorms->addValue( Vec3f( -1, 0, 0 ));
            gnorms->addValue( Vec3f( -1, 0, 0 ));

            gnorms->addValue( Vec3f( 1, 0, 0 ));
            gnorms->addValue( Vec3f( 1, 0, 0 ));
            gnorms->addValue( Vec3f( 1, 0, 0 ));
            gnorms->addValue( Vec3f( 1, 0, 0 ));

            gnorms->addValue( Vec3f( 0, 1, 0 ));
            gnorms->addValue( Vec3f( 0, 1, 0 ));
            gnorms->addValue( Vec3f( 0, 1, 0 ));
            gnorms->addValue( Vec3f( 0, 1, 0 ));

            gnorms->addValue( Vec3f( 0, -1, 0 ));
            gnorms->addValue( Vec3f( 0, -1, 0 ));
            gnorms->addValue( Vec3f( 0, -1, 0 ));
            gnorms->addValue( Vec3f( 0, -1, 0 ));
        }
    endEditCP( gnorms );

    GeoColorsPtr gcol = getColors();
    if ( gcol == NullFC )
    {
        //if it's NULL it wasn't used before -> you have to create it
        gcol = GeoColors3f::create();
    }
    beginEditCP( gcol );
        gcol->clear();
        for ( UInt32 i = 0; i < numcubes; i++ )
        { 
            for ( UInt32 j = 0; j < 24; j++ )
                gcol->addValue( col->getValue(i) );
        }
    endEditCP  ( gcol );

    // get the pointer for our own FC.
    GeoCubesPtr thisPtr = GeoCubesPtr( this );

    beginEditCP(thisPtr, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::NormalsFieldMask   |
                         Geometry::ColorsFieldMask);
        setTypes( gtypes );
        setLengths( glens ); 
        setPositions( gpos );
        setNormals( gnorms );
        setColors( gcol );
    endEditCP  (thisPtr, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::NormalsFieldMask   |
                         Geometry::ColorsFieldMask);

}

//! output the instance for debug purposes

void GeoCubes::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeoCubes NI" << endl;
}

