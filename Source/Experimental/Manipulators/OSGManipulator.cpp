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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEMANIPULATORSLIB

#include <OSGConfig.h>
#include <OSGSimpleMaterial.h>
#include <OSGTransform.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGWindow.h>
#include <OSGSimpleAttachments.h>
#include <OSGCamera.h>

#include "OSGManipulator.h"
#include "OSGSimpleGeometryExt.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Manipulator
Baseclass for all Manipulators
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

//! initialize the static features of the class, e.g. action callbacks

void Manipulator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Manipulator::Manipulator(void) :
    Inherited(),
    _activeParent( NullFC ),
    _externalUpdateHandler( NULL )
{
}

Manipulator::Manipulator(const Manipulator &source) :
    Inherited(source)
{
    //TODO: empty copy constructor?!?!?!?
}

Manipulator::~Manipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Manipulator::setExternalUpdateHandler(ExternalUpdateHandler* h)
{
    _externalUpdateHandler = h;
}

void Manipulator::callExternalUpdateHandler()
{
    if ( NULL != _externalUpdateHandler )
    {
        _externalUpdateHandler->update( this->getTarget() );
    }
}

//! react to field changes

void Manipulator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if ( (whichField & TargetFieldMask) == TargetFieldMask )
    {
        reverseTransform();
    }
    else if ( (whichField & ParentsFieldMask) == ParentsFieldMask )
    {
        MFNodePtr parents;
        NodePtr   parent;
        
        parents = getParents();        
        if ( !parents.isEmpty() )
        {
            //std::cout << "parent size= " << parents.getSize() << std::endl;
            parent = parents[0]; // Dangerous! multiple parents?
        }
        else
        {
            parent = NullFC;
        }
        
        //std::cout << "  Parent=       " << parent << std::endl;
        //std::cout << "  activeParent= " << _activeParent << std::endl;        
        
        if ( parent != _activeParent )
        {
            if ( NullFC != parent )
            {
                // remove old childs from a loaded osb file.
                beginEditCP(parent);
                    while(parent->getNChildren() > 0)
                        parent->subChild(parent->getChild(0));
                endEditCP(parent);
                addHandleGeo(parent);
            }
            
            if ( NullFC != _activeParent )
            {
                subHandleGeo(_activeParent);
            }
            
            _activeParent = parent;
        }
    }    
}

void Manipulator::addHandleGeo(NodePtr n)
{        
     beginEditCP(n);
     {
        n->addChild(getTransXNode());
        n->addChild(getTransYNode());
        n->addChild(getTransZNode());
        n->addChild(getAxisLinesN());
    }
    endEditCP(n);
}


void Manipulator::subHandleGeo(NodePtr n)
{
     beginEditCP(n);
     {
        n->subChild(getTransXNode());
        n->subChild(getTransYNode());
        n->subChild(getTransZNode());
        n->subChild(getAxisLinesN());
    }
    endEditCP(n);
}

void Manipulator::reverseTransform()
{
    TransformPtr t = TransformPtr::dcast(getTarget()->getCore());
    Matrix          m,n,o;

    Vec3f        translation;
    Quaternion    rotation;
    Vec3f        scaleFactor;
    Quaternion    scaleOrientation;

    m = t->getMatrix();
    m.getTransform(translation, rotation, scaleFactor, scaleOrientation);

    if( false == o.invertFrom(m) )
    {
        SWARNING << "Matrix is SINGULAR!!!\n";
    }
    else
    {
        n.setIdentity();
        n.setTransform(translation);
        n.setRotate(rotation);
        n.multLeft( o );
        setMatrix( n );
    }
}

//! output the instance for debug purposes

void Manipulator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Manipulator NI" << std::endl;
}

void Manipulator::onCreate()
{
}

void Manipulator::onCreate(const Manipulator* source)
{
    Inherited::onCreate(source);
    
    setMaterialX( SimpleMaterial::create() );
    setMaterialY( SimpleMaterial::create() );
    setMaterialZ( SimpleMaterial::create() );
    
    SimpleMaterialPtr  simpleMat;
    GeometryPtr        geo;
    
    setExternalUpdateHandler( NULL );

    // add a name attachment
    NamePtr nameN = Name::create();
    nameN->getFieldPtr()->setValue("XManipulator");
    addAttachment(nameN);

    // make the axis lines
    setAxisLinesN   (makeCoordAxis(getLength()[0], 2.0, false));
    addRefCP        (getAxisLinesN());
    
    // make the red x-axis transform and handle

    setTransXNode(Node::create());
    _transHandleXC= ComponentTransform::create();
    setHandleXNode(makeHandleGeo());
    setMaterialX(SimpleMaterial::create());
    
    addRefCP(getTransXNode());
    addRefCP(_transHandleXC);
    addRefCP(getHandleXNode());
    addRefCP(getMaterialX());    
    
    beginEditCP(getTransXNode(), Node::CoreFieldMask | Node::ChildrenFieldMask);
    getTransXNode()->setCore (_transHandleXC);
    getTransXNode()->addChild(getHandleXNode());
    endEditCP  (getTransXNode(), Node::CoreFieldMask | Node::ChildrenFieldMask);

    beginEditCP(_transHandleXC,
                ComponentTransform::TranslationFieldMask |
                ComponentTransform::RotationFieldMask);
    _transHandleXC->setTranslation(Vec3f(getLength()[0],0,0));
    _transHandleXC->setRotation( Quaternion(Vec3f(0,0,1),deg2rad(-90)) );
    endEditCP(  _transHandleXC,
                ComponentTransform::TranslationFieldMask |
                ComponentTransform::RotationFieldMask );

    simpleMat = SimpleMaterialPtr::dcast(getMaterialX());

    beginEditCP(simpleMat);
    simpleMat->setDiffuse(Color3f(1,0,0));
    simpleMat->setLit(true);
    endEditCP  (simpleMat);
    
    geo = GeometryPtr::dcast(getHandleXNode()->getCore());
    beginEditCP(geo, Geometry::MaterialFieldMask);
    geo->setMaterial(simpleMat);
    endEditCP(geo,Geometry::MaterialFieldMask);


    //
    // make the green y-axis transform and handle
    
    setTransYNode(Node::create());
    _transHandleYC    = ComponentTransform::create();
    setHandleYNode(makeHandleGeo());
    setMaterialY(SimpleMaterial::create());
    
    addRefCP(getTransYNode());
    addRefCP(_transHandleYC);
    addRefCP(getHandleYNode());
    addRefCP(getMaterialY());
    
    beginEditCP(getTransYNode(), Node::CoreFieldMask | Node::ChildrenFieldMask);
    getTransYNode()->setCore (_transHandleYC);
    getTransYNode()->addChild(getHandleYNode());
    endEditCP  (getTransYNode(), Node::CoreFieldMask | Node::ChildrenFieldMask);

    beginEditCP(_transHandleYC, ComponentTransform::TranslationFieldMask );
    _transHandleYC->setTranslation(Vec3f(0,getLength()[1],0));
//    _transHandleYC->setRotation( Quaternion(Vec3f(0,0,1),deg2rad(-90)) );
    endEditCP(_transHandleYC, ComponentTransform::TranslationFieldMask );

    simpleMat = SimpleMaterialPtr::dcast(getMaterialY());
    beginEditCP(simpleMat);
    simpleMat->setDiffuse(Color3f(0,1,0));
    simpleMat->setLit(true);
    endEditCP  (simpleMat);
    
    geo = GeometryPtr::dcast(getHandleYNode()->getCore());
    beginEditCP(geo, Geometry::MaterialFieldMask);
    geo->setMaterial(simpleMat);
    endEditCP(  geo, Geometry::MaterialFieldMask);


    //
    // make the blue z-axis transform and handle
    
    setTransZNode(Node::create());
    _transHandleZC= ComponentTransform::create();
    setHandleZNode(makeHandleGeo());
    setMaterialZ(SimpleMaterial::create());
    
    addRefCP(getTransZNode());
    addRefCP(_transHandleZC);
    addRefCP(getHandleZNode());
    addRefCP(getMaterialZ());
    
    beginEditCP(getTransZNode(), Node::CoreFieldMask | Node::ChildrenFieldMask);
    getTransZNode()->setCore (_transHandleZC);
    getTransZNode()->addChild(getHandleZNode());
    endEditCP(  getTransZNode(), Node::CoreFieldMask | Node::ChildrenFieldMask);

    beginEditCP(_transHandleZC,
                ComponentTransform::TranslationFieldMask |
                ComponentTransform::RotationFieldMask );
    _transHandleZC->setTranslation(Vec3f(0,0,getLength()[2]));
    _transHandleZC->setRotation( Quaternion(Vec3f(1,0,0),deg2rad(90)) );
    endEditCP(  _transHandleZC,
                ComponentTransform::TranslationFieldMask |
                ComponentTransform::RotationFieldMask );

    simpleMat = SimpleMaterialPtr::dcast(getMaterialZ());
    beginEditCP(simpleMat);
    simpleMat->setDiffuse(Color3f(0,0,1));
    simpleMat->setLit(true);
    endEditCP  (simpleMat);
    
    geo = GeometryPtr::dcast(getHandleZNode()->getCore());
    beginEditCP(geo, Geometry::MaterialFieldMask);
    geo->setMaterial(simpleMat);
    endEditCP(  geo, Geometry::MaterialFieldMask);
}

void Manipulator::onDestroy()
{
     subRefCP(getTransXNode());
     subRefCP(_transHandleXC);
     subRefCP(getHandleXNode());
     subRefCP(getMaterialX());
 
     subRefCP(getTransYNode());
     subRefCP(_transHandleYC);
     subRefCP(getHandleYNode());
     subRefCP(getMaterialY());
 
     subRefCP(getTransZNode());
     subRefCP(_transHandleZC);
     subRefCP(getHandleZNode());
     subRefCP(getMaterialZ());
    
    subRefCP(getAxisLinesN());
    // Name??
}


Pnt2f Manipulator::calcScreenProjection( const Pnt3f&       p, 
                                         const ViewportPtr& port )
{
    CameraPtr  cam; 
    Matrix     proj, projtrans, view;
    Pnt3f      pnt;

    if( port != NullFC )
    {
        cam = port->getCamera();

        cam->getProjection( proj, port->getPixelWidth(), port->getPixelHeight() );
        cam->getProjectionTranslation( projtrans, port->getPixelWidth(), 
                                       port->getPixelHeight() );
        cam->getViewing( view, port->getPixelWidth(), port->getPixelHeight() );

        Matrix wctocc = proj;
        wctocc.mult(projtrans);     
        wctocc.mult(view);

        wctocc.multFullMatrixPnt( p, pnt );

        Real32 rx = (pnt[0]+1.0)/2 * port->getPixelWidth();
        Real32 ry = (pnt[1]+1.0)/2 * port->getPixelHeight();

        return Pnt2f(rx, ry);
    }
    else
    {
        SWARNING << "calcScreenProjection(const Pnt3f&, "
                    "const ViewportPtr& port=" 
                 << port << ")\n";
        return Pnt2f(0.0f, 0.0f);
    }
}


/*! The mouseMove is called by the viewer when the mouse is moved in the 
    viewer and this handle is the active one. 
    
    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void Manipulator::mouseMove(Int16 x, Int16 y)
{
    //SLOG << "Manipulator::mouseMove() enter\n" << std::flush; 

    // get the beacon's core (must be ComponentTransform) and it's center
    if( getTarget() != NullFC )
    {
        // get transformation of beacon
        TransformPtr t = TransformPtr::dcast(getTarget()->getCore());

        if( t != NullFC )
        {                    
            UInt16          coord = 0;                  // active coordinate: X=0,
                                                  // Y=1, Z=2

            Int16            xDiff;                  // the mousepos x delta
            Int16            yDiff;                  // the mousepos y delta
    
            Vec3f            centerV;                // center of beacon
            Vec3f            handleCenterV;          // center of subhandle
            Vec2f            mouseScreenV;         // mouse move vector 
            Vec2f            handleScreenV;        // handle vec in (cc)
            Real32            handleScreenVLen;      // len of handle vec in (cc)
        
            Vec3f            translation;          // for matrix decomposition
            Quaternion        rotation;
            Vec3f            scaleFactor;
            Quaternion        scaleOrientation;

            // TODO: das ist ja schon ein wenig haesslich
             static const Vec3f coordVector[3] = {
                 Vec3f(1.0f, 0.0f, 0.0f),
                 Vec3f(0.0f, 1.0f, 0.0f),
                 Vec3f(0.0f, 0.0f, 1.0f)
             };

            //  check for the active handle
            if(     getActiveSubHandle() == getHandleXNode())
                coord = 0;
            else if(getActiveSubHandle() == getHandleYNode())
                coord = 1;
            else if(getActiveSubHandle() == getHandleZNode())
                coord = 2;
            // TODO: only for debugging, -> FDEBUG
            //SLOG << "moving " << ( coord == 0 ? "x\n" :
            //                       coord == 1 ? "y\n" :
            //                       "z\n" )
            //     << std::flush;

            // calculate diffs between current and last mouse position
            xDiff = x - Int16(getLastMousePos()[0]);
            yDiff = y - Int16(getLastMousePos()[1]);    
         
            // set the vector resulting from user mouse movement and calc its length
            mouseScreenV.setValues( xDiff, -yDiff );

            t->getMatrix().getTransform( translation,
                                         rotation,
                                         scaleFactor,
                                         scaleOrientation );


            // calculate the camera coordinate of the center
            centerV            = translation;
            Pnt2f centerPixPos = calcScreenProjection( centerV.addToZero(),
                                                       getViewport() );     


            // calculate the camera coordinate of the handle center
            handleCenterV             = centerV + coordVector[coord]*getLength()[coord];
            Pnt2f handleCenterPixPos  = calcScreenProjection( handleCenterV.addToZero(),
                                                              getViewport() );

            handleScreenV    = handleCenterPixPos - centerPixPos;
            handleScreenVLen = handleScreenV.length();
            
            Real32   s = handleScreenV.dot(mouseScreenV) / handleScreenVLen;

            doMovement(t,
                       coord,
                       s * getLength()[coord]*0.01,
                       translation,
                       rotation,
                       scaleFactor,
                       scaleOrientation );
        }
        else
            SWARNING << "handled object has no parent transform!\n";
        callExternalUpdateHandler();
    }        
    else
        SWARNING << "Handle has no target.\n";
    
    setLastMousePos(Pnt2f(Real32(x),Real32(y)));
    reverseTransform();

    //SLOG << "Manipulator::mouseMove() leave\n" << std::flush;     
}


/*! The mouseButtonPress is called by the viewer when the mouse is 
    pressed in the viewer above a subhandle of this handle.
    
    \param button the button pressed    
    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */

void Manipulator::mouseButtonPress   (UInt16 button, Int16 x, Int16 y)
{
    setLastMousePos(Pnt2f(Real32(x),Real32(y)));
    setActive(true);    
}


void Manipulator::mouseButtonRelease (UInt16 button, Int16 x, Int16 y)
{
    setActive(false);
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGManipulator.cpp,v 1.3 2005/08/12 15:27:36 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGMANIPULATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMANIPULATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMANIPULATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

