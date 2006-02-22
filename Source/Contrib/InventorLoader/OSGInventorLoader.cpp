/*
 *
 *  Copyright (C) 2002 vrcom GmbH
 *  All Rights Reserved.
 *
 *  THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 *  INFORMATION OF VRCOM GMBH. ANY DUPLICATION, MODIFICATION, DISTRIBUTION,
 *  OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, MUST INCLUDE THIS
 *  COPYRIGHT NOTICE AS WELL AS THE DISCLAIMER OF WARRANTY.
 *
 *  THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 *  WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT SHALL VRCOM GMBH BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
 *  INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER OR
 *  NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 *  LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 *  OF THIS SOFTWARE.
 *
 *
 *  Contact information:
 *
 *       vrcom Gesellschaft fuer immersive Visualisierungsloesungen mbH
 *       Mornewegstr. 28
 *       D-64293 Darmstadt
 *       Germany
 *
 *       Email: info@vrcom.de
 *       Fon:   +49 (0) 6151 / 3 00 83 - 0
 *       Fax:   +49 (0) 6151 / 3 00 83 - 19
 *
 *       http://www.vrcom.de
 *
 */


/*! \file  InventorLoader.cpp
    \brief Implementation of the InventorLoader-Class
    \author Erik Ferner
    \version 0.1
    \bug none available
*/

//------------------------------------------------------------------------------
//
//  System Headerfiles
//
//------------------------------------------------------------------------------

#include <string>

#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>

#include <Inventor/actions/SoSearchAction.h>

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransform.h>

#include <OSGGeometry.h>
#include <OSGGeoFunctions.h>
#include <OSGGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleMaterial.h>
#include <OSGTransform.h>
#include <OSGSimpleAttachments.h>

//------------------------------------------------------------------------------
//
//  Local Headerfiles
//
//------------------------------------------------------------------------------

#include "OSGInventorLoader.h"

using namespace std;

//------------------------------------------------------------------------------
//
//  Construction / Destruction
//
//------------------------------------------------------------------------------

InventorLoader::InventorLoader() :
mOIVRoot(0),
mOSGRoot(NullFC),
mMultiIndexMapping( false ),
mMergeMaterial( false ),
mMergeTolerance( 0.0001f ),
mOptimizePrimitives( false ),
mNumIterations( 1 )
{
    // Init inventor
    SoDB::init();

    // Print inventor version
    FDEBUG(("Inventor version = %s\n", SoDB::getVersion()));

    // Init state structure
    mCurrentState.Positions     =  NullFC;
    mCurrentState.Material      =  NullFC;
    mCurrentState.Normals       =  NullFC;
    mCurrentState.NormalBinding = -1;
}


//------------------------------------------------------------------------------

InventorLoader::~InventorLoader()
{}

//------------------------------------------------------------------------------

void InventorLoader::setFile( std::string File )
{
    ////////////////////////////////////////////////////////////////////////////
    FINFO(("InventorLoader::setFile( %s )\n", File.c_str() ));
    ////////////////////////////////////////////////////////////////////////////

    // Load the inventor file
    SoInput *_SceneInput = new SoInput;

    // Open the input file
    if ( !_SceneInput->openFile( File.c_str() ) )
    {
        FWARNING(("Couldn't open inventor file %s\n", File.data()));
        return;
    }

    // Read the inventor file into the database
    mOIVRoot = SoDB::readAll( _SceneInput );
    if ( mOIVRoot == 0 )
    {
        FWARNING(("Problems reading inventor file %s\n",
                    File.data()));
        return;
    }

    mOIVRoot->ref();

    // Clean up
    _SceneInput->closeFile();
    delete _SceneInput;
}


//------------------------------------------------------------------------------

void InventorLoader::setMergeMaterials( bool Merge )
{
    ////////////////////////////////////////////////////////////////////////////
    FINFO(("InventorLoader::setMergeMaterials( %d )\n", Merge ));
    ////////////////////////////////////////////////////////////////////////////

    mMergeMaterial = Merge;
}


//------------------------------------------------------------------------------

void InventorLoader::setMergeTolerance( osg::Real32 Tolerance )
{
    ////////////////////////////////////////////////////////////////////////////
    FINFO(("InventorLoader::setMergeTolerance( %f )\n",
                            Tolerance ));
    ////////////////////////////////////////////////////////////////////////////

    mMergeTolerance = Tolerance;
}


//------------------------------------------------------------------------------

void InventorLoader::setOptimizePrimitives( bool Optimize )
{
    ////////////////////////////////////////////////////////////////////////////
    FINFO(("InventorLoader::setOptimizePrimitives( %d )\n",
                            Optimize ));
    ////////////////////////////////////////////////////////////////////////////

    mOptimizePrimitives = Optimize;
}


//------------------------------------------------------------------------------

void InventorLoader::setNumIterations( osg::UInt32 Iterations )
{
    ////////////////////////////////////////////////////////////////////////////
    FINFO(("InventorLoader::setNumIterations( %d )\n",
                            Iterations ));
    ////////////////////////////////////////////////////////////////////////////

    mNumIterations = Iterations;
}


//------------------------------------------------------------------------------

void InventorLoader::printSceneGraph( )
{
    ////////////////////////////////////////////////////////////////////////////
    FINFO(("InventorLoader::printSceneGraph()\n" ));
    ////////////////////////////////////////////////////////////////////////////

    // Traverse the scenegraph
    FDEBUG(("\n" ));
    FDEBUG(("  Root (%d children)\n",mOIVRoot->getNumChildren() ));
    printGraph( mOIVRoot, 0 );
}


//------------------------------------------------------------------------------

osg::NodePtr InventorLoader::convertToOSG( )
{
    ////////////////////////////////////////////////////////////////////////////
    FINFO(("InventorLoader::convertToOSG()\n" ));
    ////////////////////////////////////////////////////////////////////////////

    // Create OpenSG root
    mOSGRoot = getGroupNode();

    // Traverse inventor scenegraph
    traverseGraph( mOIVRoot, mOSGRoot );

    return mOSGRoot->getChild(0);
}



//------------------------------------------------------------------------------
//
//  Traversal methods
//
//------------------------------------------------------------------------------

osg::NodePtr InventorLoader::traverseGraph( SoNode* OIVNode,
                                            osg::NodePtr OSGNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::traverseGraph( %x )\n",
                          OIVNode));
    ////////////////////////////////////////////////////////////////////////////


    /////////////////
    // Material node
    /////////////////

    if( OIVNode->isOfType( SoMaterial::getClassTypeId() ) )
    {
        // Convert current material
        osg::SimpleMaterialPtr _Material;
        _Material = convertMaterial( ( SoMaterial* ) OIVNode );

        if( mMergeMaterial )
        {
            // Check if that material was already encountered
            TMaterialSet::iterator _Iter;
            for(_Iter = mMaterialSet.begin();
                _Iter != mMaterialSet.end();
                ++_Iter )
            {
                if( compareMaterial( *_Iter, _Material, mMergeTolerance ) )
                    break;
            }

            if( _Iter != mMaterialSet.end() )
            {
                mCurrentState.Material = *_Iter;

                // Delete the converted material from above as it isn't used.
                subRefCP( _Material );
            }
            else
            {
                mMaterialSet.insert( _Material );
                mCurrentState.Material = _Material;
            }
        }
        else
        {
            mCurrentState.Material = _Material;
        }

        // Return the old OSG node as the current OSG node
        return OSGNode;
    }


    ///////////////////
    // Coordinate node
    ///////////////////

    if( OIVNode->isOfType( SoCoordinate3::getClassTypeId() ) )
    {
        // Save current coordinates
        mCurrentState.Positions = convertCoordinates((SoCoordinate3*)OIVNode);

        // Return the old OSG node as the current OSG node
        return OSGNode;
    }


    //////////////////////
    // Normalbinding node
    //////////////////////

    if( OIVNode->isOfType( SoNormalBinding::getClassTypeId() ) )
    {
        // Save current normalbinding
        SoNormalBinding* _Binding = ( SoNormalBinding* ) OIVNode;
        mCurrentState.NormalBinding = _Binding->value.getValue();

        // Return the old OSG node as the current OSG node
        return OSGNode;
    }


    ///////////////
    // Normal node
    ///////////////

    if( OIVNode->isOfType( SoNormal::getClassTypeId() ) )
    {
        // Save current normals
        mCurrentState.Normals = convertNormals( ( SoNormal* ) OIVNode );

        // Return the old OSG node as the current OSG node
        return OSGNode;
    }


    ///////////////////////
    // Transformation node
    ///////////////////////

    if( OIVNode->isOfType( SoTransform::getClassTypeId() ) )
    {
        osg::NodePtr _OSGTransform = convertTransformation( OIVNode );

        // Add the transformation to the current OSG node
        beginEditCP ( OSGNode, Node::ChildrenFieldMask );
        {
            OSGNode->addChild( _OSGTransform );
        }
        endEditCP   ( OSGNode, Node::ChildrenFieldMask );

        // Return the new transform node as the current OSG node
        return _OSGTransform;
    }


    ////////////////////
    // Indexed face set
    ////////////////////

    if( OIVNode->isOfType( SoIndexedFaceSet::getClassTypeId() ) )
    {
        osg::NodePtr _OSGGeometry = convertGeometry( OIVNode );

        // Add the geometry to the current OSG node
        beginEditCP ( OSGNode, Node::ChildrenFieldMask );
        {
            OSGNode->addChild( _OSGGeometry );
        }
        endEditCP   ( OSGNode, Node::ChildrenFieldMask );

        // Return the old OSG node as the current OSG node
        return OSGNode;
    }


    //////////////////
    // Separator node
    //////////////////

    if( OIVNode->isOfType( SoSeparator::getClassTypeId() ) )
    {
        SoGroup* _OIVGroup = ( SoGroup* ) OIVNode;
        osg::NodePtr _OSGGroup = getGroupNode( OIVNode );
        osg::NodePtr _CurrentNode = _OSGGroup;

        // Add the group to the current OSG node
        beginEditCP ( OSGNode, Node::ChildrenFieldMask );
        {
            OSGNode->addChild( _OSGGroup );
        }
        endEditCP   ( OSGNode, Node::ChildrenFieldMask );

        // Save the current state
        TState _TmpState = mCurrentState;

        // Traverse children
        for( int i=0; i < _OIVGroup->getNumChildren(); ++i )
        {
            SoNode* _OIVChild = _OIVGroup->getChild( i );
            _CurrentNode = traverseGraph( _OIVChild, _CurrentNode );
        }

        // Restore the state
        mCurrentState = _TmpState;

        // Check if the new group node has only one child
        // --> then it's redundant and can be discarded
        checkForRedundancy( _OSGGroup );

        // Return the old OSG node as the current OSG node
        return OSGNode;
    }


    //////////////
    // Group node
    //////////////

    else if( OIVNode->isOfType( SoGroup::getClassTypeId() ) )
    {
        osg::NodePtr _CurrentNode = OSGNode;
        SoGroup* _OIVGroup = ( SoGroup* ) OIVNode;

        // Traverse children
        for( int i=0; i < _OIVGroup->getNumChildren(); ++i )
        {
            SoNode* _OIVChild = _OIVGroup->getChild( i );
            _CurrentNode = traverseGraph( _OIVChild, _CurrentNode );
        }

        // Return the end of the group as current OSG node
        return _CurrentNode;
    }

    return OSGNode;
}


//------------------------------------------------------------------------------

void InventorLoader::checkForRedundancy( osg::NodePtr OSGGroup )
{
  return;
  
    // TODO: Check the type of the node and return, if it's not a node
    // that should be discarded (discardable: group, not discardable: geometry)

    // If the group node has no children, then let's kick it !
    if( OSGGroup->getNChildren() == 0 )
    {
        if(OSGGroup->getParent() != NullFC)
        {
            OSGGroup->getParent()->subChild(OSGGroup);
        }
        else
        {
            subRefCP(OSGGroup);
        }
    }
    // If there's only one child, then add it to the parent of the group,
    // copy the name and remove the group
    else if ( OSGGroup->getNChildren() == 1 )
    {
        // Get parent and child
        osg::NodePtr _Child = OSGGroup->getChild(0);
        osg::NodePtr _Parent = OSGGroup->getParent();

        // Copy the name
        const char* _Name = getName(OSGGroup);
        if( _Name )
            setName( _Child, _Name );

        // Add the child to the parent
        _Parent->addChild( _Child );

        // Remove the group node
        _Parent->subChild( OSGGroup );
    }
}


//------------------------------------------------------------------------------
//
//  Conversion methods
//
//------------------------------------------------------------------------------

osg::NodePtr InventorLoader::getGroupNode( SoNode* OIVNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::getGroupNode()\n" ));
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////
    // Create the OpenSG group node
    ////////////////////////////////////

    osg::NodePtr _OSGNode = Node::create();
    osg::GroupPtr _Group = Group::create();

    beginEditCP( _OSGNode, Node::CoreFieldMask );
    {
        _OSGNode->setCore( _Group );
    }
    endEditCP( _OSGNode, Node::CoreFieldMask );

    /////////////////////////////
    // Copy the name of the node
    /////////////////////////////

    if( OIVNode )
        copyName( OIVNode, _OSGNode );

    return _OSGNode;
}


//------------------------------------------------------------------------------

osg::SimpleMaterialPtr InventorLoader::convertMaterial( SoNode* OIVNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::convertMaterial( %x )\n",
                          OIVNode ));
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////
    // Copy the material parameters
    ////////////////////////////////

    SoMaterial* _OIVMaterial = ( SoMaterial* ) OIVNode;
    osg::SimpleMaterialPtr _Material = SimpleMaterial::create();

    beginEditCP( _Material );
    {
        // Ambient color
        _Material->setAmbient( Color3f( _OIVMaterial->ambientColor[0][0],
                                        _OIVMaterial->ambientColor[0][1],
                                        _OIVMaterial->ambientColor[0][2] ));

        // Diffuse color
        _Material->setDiffuse( Color3f( _OIVMaterial->diffuseColor[0][0],
                                        _OIVMaterial->diffuseColor[0][1],
                                        _OIVMaterial->diffuseColor[0][2] ));

        // Specular color
        _Material->setSpecular( Color3f(_OIVMaterial->specularColor[0][0],
                                        _OIVMaterial->specularColor[0][1],
                                        _OIVMaterial->specularColor[0][2] ));

        // Emissive color
        _Material->setEmission( Color3f(_OIVMaterial->emissiveColor[0][0],
                                        _OIVMaterial->emissiveColor[0][1],
                                        _OIVMaterial->emissiveColor[0][2] ));

        // Shininess
        _Material->setShininess( _OIVMaterial->shininess[0] );

        // Transparency
        _Material->setTransparency( _OIVMaterial->transparency[0] );
    }
    endEditCP  ( _Material );

    return _Material;
}


//------------------------------------------------------------------------------

osg::GeoPositions3fPtr InventorLoader::convertCoordinates( SoNode* OIVNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::convertCoordinates( %x )\n",
                          OIVNode ));
    ////////////////////////////////////////////////////////////////////////////

    SoCoordinate3* _Coords = ( SoCoordinate3* ) OIVNode;
    GeoPositions3fPtr _Points = GeoPositions3f::create();

    beginEditCP ( _Points, GeoPositions3f::GeoPropDataFieldMask );
    {
        for( int i=0; i < _Coords->point.getNum(); ++i )
        {
            _Points->addValue( Pnt3f(   _Coords->point[i][0],
                                        _Coords->point[i][1],
                                        _Coords->point[i][2] ) );
        }
    }
    endEditCP  ( _Points, GeoPositions3f::GeoPropDataFieldMask );

    return _Points;
}


//------------------------------------------------------------------------------

osg::GeoNormals3fPtr InventorLoader::convertNormals( SoNode* OIVNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::convertNormals( %x )\n",
                          OIVNode ));
    ////////////////////////////////////////////////////////////////////////////

    SoNormal* _OIVNormalNode = ( SoNormal* ) OIVNode;
    GeoNormals3fPtr _Normals = GeoNormals3f::create();

    beginEditCP ( _Normals, GeoNormals3f::GeoPropDataFieldMask );
    {
        for( int i=0; i < _OIVNormalNode->vector.getNum(); ++i )
        {
            _Normals->addValue( Vec3f(  _OIVNormalNode->vector[i][0],
                                        _OIVNormalNode->vector[i][1],
                                        _OIVNormalNode->vector[i][2] ) );
        }
    }
    endEditCP  ( _Normals, GeoNormals3f::GeoPropDataFieldMask );

    return _Normals;
}


//------------------------------------------------------------------------------

osg::NodePtr InventorLoader::convertTransformation( SoNode* OIVNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::convertTransformation( %x )\n",
                          OIVNode ));
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////
    // Create the OpenSG transform node
    ////////////////////////////////////

    osg::NodePtr _OSGNode = Node::create();
    osg::TransformPtr _Transform = Transform::create();

    beginEditCP ( _OSGNode, Node::CoreFieldMask );
    {
        _OSGNode->setCore( _Transform );
    }
    endEditCP   ( _OSGNode, Node::CoreFieldMask );


    //////////////////////////////////////
    // Copy the transformation parameters
    //////////////////////////////////////

    SoTransform* _OIVTransform = ( SoTransform* ) OIVNode;
    osg::Matrix _Matrix;

    // Copy translation
    _Matrix.setTranslate(   _OIVTransform->translation.getValue()[0],
                            _OIVTransform->translation.getValue()[1],
                            _OIVTransform->translation.getValue()[2] );

    // Copy rotation
    SbVec3f _Axis;
    float _Radians;
    _OIVTransform->rotation.getValue().getValue( _Axis, _Radians );
    _Matrix.setRotate(  Quaternion( Vec3f( _Axis[0], _Axis[1], _Axis[2] ),
                        _Radians ) );

    // Copy scale
    _Matrix.setScale(   _OIVTransform->scaleFactor.getValue()[0],
                        _OIVTransform->scaleFactor.getValue()[1],
                        _OIVTransform->scaleFactor.getValue()[2] );

    // Set the transform's matrix
    beginEditCP ( _Transform, Transform::MatrixFieldMask );
    {
        _Transform->setMatrix( _Matrix );
    }
    endEditCP   ( _Transform, Transform::MatrixFieldMask );


    /////////////////////////////
    // Copy the name of the node
    /////////////////////////////

    copyName( OIVNode, _OSGNode );


    return _OSGNode;
}


//------------------------------------------------------------------------------

osg::NodePtr InventorLoader::convertGeometry( SoNode* OIVNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::convertGeometry( %x )\n",
                          OIVNode ));
    ////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////
    // Convert indices (incl. polygon types and lengths)
    /////////////////////////////////////////////////////

    SoIndexedFaceSet* _FaceSet = ( SoIndexedFaceSet* ) OIVNode;
    GeoPTypesPtr _Types = GeoPTypesUI8::create();
    GeoPLengthsPtr _Lengths = GeoPLengthsUI32::create();
    GeoIndicesUI32Ptr _Indices = GeoIndicesUI32::create();

    beginEditCP ( _Types,   GeoPTypesUI8::GeoPropDataFieldMask);
    beginEditCP ( _Lengths, GeoPLengthsUI32::GeoPropDataFieldMask);
    beginEditCP ( _Indices, GeoIndicesUI32::GeoPropDataFieldMask );
    {
        int _PolygonSize = 0;
        int _Length = 0;
        int _PolygonMode = -1;
        for( int i=0; i < _FaceSet->coordIndex.getNum(); ++i )
        {
            if( _FaceSet->coordIndex[i] == -1 )
            {
                // Initial polygon
                if( _PolygonMode == -1 )
                {
                    if( _PolygonSize == 3 )
                    {
                        _PolygonMode = GL_TRIANGLES;
                    }
                    else if( _PolygonSize == 4 )
                    {
                        _PolygonMode = GL_QUADS;
                    }
                    else
                    {
                        _PolygonMode = GL_POLYGON;
                    }

                    _Types->addValue( _PolygonMode );

                }

                // Did the polygon mode change ?
                else if(    _PolygonSize == 3 &&
                            _PolygonMode != GL_TRIANGLES )
                {
                    // Add new polygon type
                    _PolygonMode = GL_TRIANGLES;
                    _Types->addValue( GL_TRIANGLES );

                    // Save length of previous type
                    _Lengths->addValue( _Length - 3 );
                    _Length = 3;
                }
                else if(    _PolygonSize == 4 &&
                            _PolygonMode != GL_QUADS )
                {
                   // Add new polygon type
                    _PolygonMode = GL_QUADS;
                    _Types->addValue( GL_QUADS );

                    // Save length of previous type
                    _Lengths->addValue( _Length - 4 );
                    _Length = 4;
                }
                else if(    _PolygonSize != 3 &&
                            _PolygonSize != 4 &&
                            _PolygonMode != GL_POLYGON )
                {
                    // Add new polygon type
                    _PolygonMode = GL_POLYGON;
                    _Types->addValue( GL_POLYGON );

                    // Save length of previous type
                    _Lengths->addValue( _Length - _PolygonSize );
                    _Length = _PolygonSize;

                }

                _PolygonSize = 0;
            }
            else
            {
                // Copy coordinate indices
                _Indices->addValue( _FaceSet->coordIndex[i] );

                // Copy normal indices if there is a current normal node
                if( mMultiIndexMapping && mCurrentState.Normals != NullFC &&
                    mCurrentState.NormalBinding ==
                        SoNormalBinding::PER_VERTEX_INDEXED )
                {
                    if( _FaceSet->normalIndex[0] != -1 )
                    {
                        _Indices->addValue( _FaceSet->normalIndex[i] );
                    }
                    else
                    {
                        _Indices->addValue( _FaceSet->coordIndex[i] );
                    }
                }

                _PolygonSize++;
                _Length++;
            }
        }

        // Save length of last polygon type
        _Lengths->addValue( _Length );
    }
    endEditCP   ( _Indices, GeoIndicesUI32::GeoPropDataFieldMask );
    endEditCP   ( _Lengths, GeoPLengthsUI32::GeoPropDataFieldMask);
    endEditCP   ( _Types,   GeoPTypesUI8::GeoPropDataFieldMask);


    ///////////////////
    // Get coordinates
    ///////////////////

    osg::GeoPositions3fPtr _Positions;
    if( _FaceSet->vertexProperty.getValue() != 0 )
    {
        FWARNING(("InventorLoader::convertGeometry() --> "
                  "Use of vertexProperty in indexedFaceSet "
                  "not yet implemented.\n" ));

    }
    else if( mCurrentState.Positions != NullFC )
    {
        _Positions = mCurrentState.Positions;
    }
    else
    {
        FWARNING(("InventorLoader::convertGeometry() --> "
                  "No GeoPositions in current state.\n" ));
    }

    ////////////////
    // Get material
    ////////////////

    osg::MaterialPtr _Material;
    if( mCurrentState.Material != NullFC)
    {
        _Material = mCurrentState.Material;
    }
    else
    {
        _Material = getDefaultMaterial();
    }

    ///////////////////
    // Create geometry
    ///////////////////

    osg::GeometryPtr _Geometry = Geometry::create();
    beginEditCP ( _Geometry,    Geometry::TypesFieldMask        |
                                Geometry::LengthsFieldMask      |
                                Geometry::IndicesFieldMask      |
                                Geometry::IndexMappingFieldMask |
                                Geometry::NormalsFieldMask      |
                                Geometry::PositionsFieldMask    |
                                Geometry::MaterialFieldMask );
    {
        _Geometry->setTypes    ( _Types );
        _Geometry->setLengths  ( _Lengths );
        _Geometry->setIndices  ( _Indices );
        _Geometry->setPositions( _Positions );
        _Geometry->setMaterial ( _Material );

        // Handle normals
        // (convert from inventor if possible, otherwise calculate)
        if( mCurrentState.Normals != NullFC &&
            mCurrentState.NormalBinding == SoNormalBinding::PER_VERTEX_INDEXED )
        {
            // Set the index mapping
            if( mMultiIndexMapping )
                // Multi-indexmapping
            {
              _Geometry->getIndexMapping().push_back( Geometry::MapPosition );
              _Geometry->getIndexMapping().push_back( Geometry::MapNormal );
            }
            else
            {
                // Single-indexmapping
                _Geometry->getIndexMapping().push_back(  Geometry::MapPosition |
                                                        Geometry::MapNormal );
            }

            _Geometry->setNormals( mCurrentState.Normals );
        }
        else
        {
            _Geometry->getIndexMapping().push_back( Geometry::MapPosition );
            calcFaceNormals( _Geometry );
        }

        // Do striping and fanning (currently only works with
        // single-indexmapping )
        if( mOptimizePrimitives )
        {
            osg::createOptimizedPrimitives( _Geometry, mNumIterations );
        }
    }
    endEditCP   ( _Geometry,    Geometry::TypesFieldMask        |
                                Geometry::LengthsFieldMask      |
                                Geometry::IndicesFieldMask      |
                                Geometry::IndexMappingFieldMask |
                                Geometry::NormalsFieldMask      |
                                Geometry::PositionsFieldMask    |
                                Geometry::MaterialFieldMask );


    /////////////////////////////
    // Add geometry core to node
    /////////////////////////////

    osg::NodePtr _OSGNode = Node::create();
    beginEditCP( _OSGNode, Node::CoreFieldMask );
    {
        _OSGNode->setCore( _Geometry );
    }
    endEditCP( _OSGNode, Node::CoreFieldMask );


    /////////////////////////////
    // Copy the name of the node
    /////////////////////////////

    // Copy the name from the inventor node
    copyName( OIVNode, _OSGNode );

    return _OSGNode;
}


//------------------------------------------------------------------------------

void InventorLoader::copyName( SoNode* OIVNode, osg::NodePtr OSGNode )
{
    ////////////////////////////////////////////////////////////////////////////
  FDEBUG(("   InventorLoader::copyName( %x )\n",
          OIVNode ));
    ////////////////////////////////////////////////////////////////////////////

    // Return if there is no name
    if( !( OIVNode->getName() ) )
        return;

    // Get name of the inventor node
    const char* _NodeName= OIVNode->getName().getString();

    // Set the name of the OpenSG node
    setName( OSGNode, _NodeName );
}


//------------------------------------------------------------------------------

bool InventorLoader::compareMaterial(   osg::SimpleMaterialPtr Material1,
                                        osg::SimpleMaterialPtr Material2,
                                        osg::Real32 Tolerance )
{
    // Compare ambient color
    if( !( Material1->getAmbient().equals(  Material2->getAmbient(),
                                            Tolerance ) ) )
        return false;

    // Compare diffuse color
    if( !( Material1->getDiffuse().equals(  Material2->getDiffuse(),
                                            Tolerance ) ) )
        return false;

    // Compare specular color
    if( !( Material1->getSpecular().equals( Material2->getSpecular(),
                                            Tolerance ) ) )
        return false;

    // Compare emissive color
    if( !( Material1->getEmission().equals( Material2->getEmission(),
                                            Tolerance ) ) )
        return false;

    // Compare shininess
    if( fabs(   Material1->getShininess() -
                Material2->getShininess()) > Tolerance )
        return false;

    // Compare transparency
    if( fabs(   Material1->getTransparency() -
                Material2->getTransparency() ) > Tolerance )
        return false;

    // The materials are identical, if all the cases above where false
    return true;
}



//------------------------------------------------------------------------------
//
//  Debugging methods
//
//------------------------------------------------------------------------------

void InventorLoader::printGraph( SoGroup* OIVGroup, int Layer )
{
    // Traverse the children
    for( int i=0; i < OIVGroup->getNumChildren(); i++ )
    {
        // Get the OIV child node
        SoNode* _OIVChild = OIVGroup->getChild( i );


        //////////////////
        // Separator node
        //////////////////

        if( _OIVChild->isOfType( SoSeparator::getClassTypeId() ) )
        {
            printSeparator( ( SoSeparator* ) _OIVChild, Layer+1 );
        }


        //////////////
        // Group node
        //////////////

        else if( _OIVChild->isOfType( SoGroup::getClassTypeId() ) )
        {
            printGroup( ( SoGroup* ) _OIVChild, Layer+1 );
        }


        //////////////////
        // Transform node
        //////////////////

        else if( _OIVChild->isOfType( SoTransform::getClassTypeId() ) )
        {
            printTransform( ( SoTransform* ) _OIVChild, Layer+1 );
        }


        ///////////////////
        // Coordinate node
        ///////////////////

        else if( _OIVChild->isOfType( SoCoordinate3::getClassTypeId() ) )
        {
            printCoordinate(( SoCoordinate3* ) _OIVChild,Layer+1 );
        }


        ///////////////
        // Normal node
        ///////////////

        else if( _OIVChild->isOfType( SoNormal::getClassTypeId() ) )
        {
            printNormal( ( SoNormal* ) _OIVChild, Layer+1 );
        }


        ////////////////////
        // Indexed face set
        ////////////////////

        else if( _OIVChild->isOfType( SoIndexedFaceSet::getClassTypeId() ) )
        {
            printIndexedFaceSet(  ( SoIndexedFaceSet* ) _OIVChild,  Layer+1 );
        }


        ////////////////////
        // Other nodes
        ////////////////////

        else
        {
            printOther( _OIVChild,  Layer+1 );
        }



        //////////////////////
        // Continue traversal
        //////////////////////

        // Continue traversing, if this is a separator or group node
        if( _OIVChild->isOfType( SoSeparator::getClassTypeId() ) )
        {
            // Continue traversing the graph
            printGraph( ( SoSeparator* ) _OIVChild, Layer+1 );
        }
        else if( _OIVChild->isOfType( SoGroup::getClassTypeId() ) )
        {
            // Continue traversing the graph
            printGraph( ( SoGroup* ) _OIVChild, Layer+1 );
        }

    }
}


//------------------------------------------------------------------------------

void InventorLoader::printSeparator( SoSeparator* Separator, int Layer )
{
    // Print debug info
    std::string _NodeName = "Separator";
    int _Indent = ( Layer + 1 ) * 2 + _NodeName.size();
    FDEBUG(("% *s ( %x, %d children )\n",
            _Indent, _NodeName.c_str(),
            Separator, Separator->getNumChildren() ));
}


//------------------------------------------------------------------------------

void InventorLoader::printGroup( SoGroup* Group, int Layer )
{
    // Print debug info
    std::string _NodeName = "Group";
    int _Indent = ( Layer + 1 ) * 2 + _NodeName.size();
    FDEBUG(("% *s ( %x, %d children )\n",
                _Indent, _NodeName.c_str(),
                Group, Group->getNumChildren() ));
}


//------------------------------------------------------------------------------

void InventorLoader::printTransform( SoTransform* Transform, int Layer )
{
    // Print debug info
    std::string _NodeName = "Transform";
    int _Indent = ( Layer + 1 ) * 2 + _NodeName.size();
    FDEBUG(("% *s ( %x, "
                            "T: %.2f %.2f %.2f)\n",
                _Indent, _NodeName.c_str(), Transform,
                Transform->translation.getValue()[0],
                Transform->translation.getValue()[1],
                Transform->translation.getValue()[2]
                 ));
}


//------------------------------------------------------------------------------

void InventorLoader::printCoordinate( SoCoordinate3* Coordinate, int Layer )
{
    // Print debug info
    std::string _NodeName = "Coordinate";
    int _Indent = ( Layer + 1 ) * 2 + _NodeName.size();
    FDEBUG(("% *s (%x)\n",
                _Indent, _NodeName.c_str(), Coordinate ));
}


//------------------------------------------------------------------------------

void InventorLoader::printNormal( SoNormal* Normal, int Layer )
{
    // Print debug info
    std::string _NodeName = "Normal";
    int _Indent = ( Layer + 1 ) * 2 + _NodeName.size();
    FDEBUG(("% *s (%x)\n",
                _Indent, _NodeName.c_str(), Normal ));
}


//------------------------------------------------------------------------------

void InventorLoader::printIndexedFaceSet( SoIndexedFaceSet* IndexedFaceSet,
                                                int Layer )
{
    // Print debug info
    std::string _NodeName = "IndexedFaceSet";
    int _Indent = ( Layer + 1 ) * 2 + _NodeName.size();
    FDEBUG(("% *s (%x)\n",
                _Indent, _NodeName.c_str(), IndexedFaceSet ));
}


//------------------------------------------------------------------------------

void InventorLoader::printOther( SoNode* Node, int Layer )
{
    // Print debug info
    std::string _NodeName = "Other";
    int _Indent = ( Layer + 1 ) * 2 + _NodeName.size();
    FDEBUG(("% *s (%x)\n",
                _Indent, _NodeName.c_str(), Node ));
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGINVENTORLOADER_HEADER_CVSID;
}

