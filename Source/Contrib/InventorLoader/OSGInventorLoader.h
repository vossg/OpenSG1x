/*
 *
 *  Copyright (C) 2002 vrcom GmbH  
 *  All Rights Reserved. 
 *
 *  THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 *  INFORMATION OF VRCOM GMBH. ANY DUPLICATION, MODIFICATION, DISTRIBUTION,
 *  OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, MUST INCLUDE THIS 
 *	COPYRIGHT NOTICE AS WELL AS THE DISCLAIMER OF WARRANTY.
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
 
 
/*! \file  InventorLoader.h
	\brief Declaration of the InventorLoader-Class
	\author Erik Ferner
	\version 0.1
	\bug none available
*/


#ifndef InventorLoader_h
#define InventorLoader_h

//------------------------------------------------------------------------------
//
//  System Headerfiles
//                                                                          
//------------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGSimpleMaterial.h>
#include <OSGGeometry.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

//------------------------------------------------------------------------------
//
//  Project Headerfiles
//                                                                          
//------------------------------------------------------------------------------

#include <set>
#include <stack>
using namespace std;

#include <Inventor/SoPath.h>

#include <OSGMaterial.h>

//------------------------------------------------------------------------------
//
//  Local Headerfiles
//                                                                          
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Forward declarations
//                                                                          
//------------------------------------------------------------------------------

class SoCoordinate3;
class SoGroup;
class SoIndexedFaceSet;
class SoMaterial;
class SoNode;
class SoNormal;
class SoSeparator;
class SoTransform;

//------------------------------------------------------------------------------
//
//  Typedefs
//                                                                          
//------------------------------------------------------------------------------

//! Current state during traversal
typedef struct
{
	// The effecting positions
	osg::GeoPositions3fPtr Positions;

	// The effecting material 
    osg::SimpleMaterialPtr Material;
    
    // The effecting normals
    osg::GeoNormals3fPtr Normals;
    
    // The normal binding
    int NormalBinding;
    
} TState;

//! Holds all materials to prevent duplication
typedef std::set< osg::SimpleMaterialPtr > TMaterialSet;

//------------------------------------------------------------------------------
//
//  Defines
//                                                                          
//------------------------------------------------------------------------------


/*! 
	\brief Declaration of the InventorLoader-Class
	\author Erik Ferner
	\version 0.1
	\bug none available
	
	This class handles inventor files
*/
class InventorLoader
{ 
public:

		
	//////////////////////////////
	// Construction / Destruction
	//////////////////////////////
	
//! Constructor
    InventorLoader();

//------------------------------------------------------------------------------
 			
//! Destructor 
    ~InventorLoader();
    
//------------------------------------------------------------------------------

/*! Sets the name of the inventor file and loads it
	\param File Inventor file name
*/
    void setFile( std::string File );
    
//------------------------------------------------------------------------------

/*! Sets whether to merge simular materials
	\param Merge True or false
*/
    void setMergeMaterials( bool Merge );
    
//------------------------------------------------------------------------------

/*! Sets tolerance for comparing floating points when merging materials
	\param Tolerance Tolerance value
*/
    void setMergeTolerance( osg::Real32 Tolerance );
    
//------------------------------------------------------------------------------

/*! Sets whether to optimize primitives (striping and fanning)
	\param Optimize True or false
*/
    void setOptimizePrimitives( bool Optimize );
    
//------------------------------------------------------------------------------

/*! Sets number of iterations for striping and fanning
	\param Iterations Number of iterations
*/
    void setNumIterations( osg::UInt32 Iterations );
    
//------------------------------------------------------------------------------

/*! Prints the scenegraph to the standard output
*/
    void printSceneGraph( );
    
//------------------------------------------------------------------------------

/*! Converts the inventor scene to OpenSG
	\return Root pointer of the OSG scenegraph
*/
    osg::NodePtr convertToOSG();
    
//------------------------------------------------------------------------------

					
protected:

		
	/////////////////////
	// Traversal methods
	/////////////////////
	
/*! Recursively traverses inventor graph and converts it to OpenSG
	\param OIVNode Current inventor node
    \param OSGNode Current OSG node
    \return OSG node after traversal
*/
    osg::NodePtr traverseGraph( SoNode* OIVNode, osg::NodePtr OSGNode );
		
//------------------------------------------------------------------------------

/*! Checks whether a group node has less than two children and discards it
	if necessary
    \param OSGGroup Group node
*/
    void checkForRedundancy( osg::NodePtr OSGGroup );
		
//------------------------------------------------------------------------------

		
	//////////////////////
	// Conversion methods
	//////////////////////
	
/*! Returns an OpenSG group node
	\param OIVNode Pointer to inventor node (for the name)
	\return Pointer to an OSG group node
*/
	osg::NodePtr getGroupNode( SoNode* OIVNode = 0);	

//------------------------------------------------------------------------------

/*! Converts an inventor material to an OpenSG material
	\param OIVNode Pointer to inventor material node
    \return Pointer to an OSG material
*/
	osg::SimpleMaterialPtr convertMaterial( SoNode* OIVNode );	

//------------------------------------------------------------------------------

/*! Converts inventor coordinates to OpenSG geo positions
	\param OIVNode Pointer to inventor coordinate node
    \return Pointer to OSG geo positions
*/
	osg::GeoPositions3fPtr convertCoordinates( SoNode* OIVNode );	

//------------------------------------------------------------------------------

/*! Converts inventor normals to OpenSG geo normals
	\param OIVNode Pointer to inventor normals node
    \return Pointer to OSG geo normals
*/
	osg::GeoNormals3fPtr convertNormals( SoNode* OIVNode );	

//------------------------------------------------------------------------------

/*! Converts an inventor transformation to an OpenSG transformation
	\param OIVNode Pointer to inventor transformation node
    \return Pointer to an OSG transformation node
*/
	osg::NodePtr convertTransformation( SoNode* OIVNode );	

//------------------------------------------------------------------------------

/*! Converts an inventor geometry to an OpenSG geometry
	\param OIVNode Pointer to inventor geometry
    \return Pointer to an OSG geometry
*/
	osg::NodePtr convertGeometry( SoNode* OIVNode );	

//------------------------------------------------------------------------------

/*! Copys the name of an inventor node to an OpenSG node
	\param OIVPath The inventor node
	\param OSGNode The OpenSG node
*/
	void copyName( SoNode* OIVNode, osg::NodePtr OSGNode );	

//------------------------------------------------------------------------------

/*! Compares two OpenSG materials
	\param Material1 1. material
	\param Material2 2. material
	\param Tolerance Maximum tolerance of all float values
    \return True: Identical / False: Different
*/
	bool compareMaterial( 	osg::SimpleMaterialPtr Material1,
    						osg::SimpleMaterialPtr Material2, 
                            osg::Real32 Tolerance );

//------------------------------------------------------------------------------


	/////////////////////
	// Debugging methods
	/////////////////////
	
/*! Recursively prints the open inventor scenegraph
	\param OIVGroup Current inventor group node
    \param Layer Layer in the scenegraph
*/    	    
	void printGraph( SoGroup* OIVGroup, int Layer );

//------------------------------------------------------------------------------
	
/*! Prints a separator node
	\param Separator Inventor separator node
    \param Layer Layer in the scenegraph
*/    	    
	void printSeparator( SoSeparator* Separator, int Layer );

//------------------------------------------------------------------------------
	
/*! Prints a group node
	\param Group Inventor group node
    \param Layer Layer in the scenegraph
*/    	    
	void printGroup( SoGroup* Group, int Layer );

//------------------------------------------------------------------------------
	
/*! Prints a transform node
	\param Transform Inventor transform node
    \param Layer Layer in the scenegraph
*/    	    
	void printTransform( SoTransform* Transform, int Layer );

//------------------------------------------------------------------------------
	
/*! Prints a coordinate node
	\param Coordinate Inventor coordinate node
    \param Layer Layer in the scenegraph
*/    	    
	void printCoordinate( SoCoordinate3* Coordinate, int Layer );

//------------------------------------------------------------------------------
	
/*! Prints a normal node
	\param Normal Inventor normal node
    \param Layer Layer in the scenegraph
*/    	    
	void printNormal( SoNormal* Normal, int Layer );

//------------------------------------------------------------------------------
	
/*! Prints a normal node
	\param IndexedFaceSet Inventor IndexedFaceSet node
    \param Layer Layer in the scenegraph
*/    	    
	void printIndexedFaceSet( SoIndexedFaceSet* IndexedFaceSet, int Layer );

//------------------------------------------------------------------------------
	
/*! Prints other nodes
	\param Node Other node
    \param Layer Layer in the scenegraph
*/    	    
	void printOther( SoNode* Node, int Layer );

//------------------------------------------------------------------------------

		
	///////////////////////////
	// Basic protected members
	///////////////////////////
    
//! The root node of the inventor scene graph
	SoSeparator* mOIVRoot;		
	
//------------------------------------------------------------------------------

//! The root node of the OpenSG scene graph
	osg::NodePtr mOSGRoot;		
	
//------------------------------------------------------------------------------

/*! Holds the current state (coords, normals, material, ...)
*/   
	TState mCurrentState;

//------------------------------------------------------------------------------

/*! Holds all materials converted during traversal to assure unified material
	cores for faster rendering
*/   
	TMaterialSet mMaterialSet;

//------------------------------------------------------------------------------

		
	////////////
	// Settings
	////////////
    
/*! Indicates whether geometries should be converted using multi-indexedmapping
	(As long as the normals look fine, it should stay false)
*/    
	bool mMultiIndexMapping;

//------------------------------------------------------------------------------

/*! Indicates whether simular materials should be merged together to one 
	OpenSG material core (recommended)
*/    
	bool mMergeMaterial;

//------------------------------------------------------------------------------

/*! Tolerance for comparing floating points of material properties
*/    
	osg::Real32 mMergeTolerance;

//------------------------------------------------------------------------------

/*! Indicates whether the primitives of each geometry should be optimized
	using striping and fanning
*/    
	bool mOptimizePrimitives;

//------------------------------------------------------------------------------

/*! Number of iterations for striping and fanning
*/    
	osg::UInt32 mNumIterations;

//------------------------------------------------------------------------------

		
};

#endif // InventorLoader_h
