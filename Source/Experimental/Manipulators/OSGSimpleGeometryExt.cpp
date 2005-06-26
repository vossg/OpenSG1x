#include "OSGSimpleGeometryExt.h"

#include <OSGSimpleMaterial.h>
#include <OSGLineChunk.h>
#include <OSGGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGFaceIterator.h>
#include <OSGComponentTransform.h>

using namespace std;

OSG_BEGIN_NAMESPACE

GeometryPtr makeGridGeo(     Real32 width, 
                            Real32 depth,
                             Real32 hCellWidth, 
                             Color3f color )
{
    Real32        height, widthHalf, depthHalf;
    Real32        vCellWidth = hCellWidth;
    Real32        w, d;
    Int32       pntCnt, nCols, nRows;
    Real32        x, z;    
    Color3f     darkerColor = 
                    Color3f( color[0]-0.4, color[1]-0.4, color[2]-0.4 ); 

    GeometryPtr         geo     = Geometry::create();
    GeoPositions3fPtr    pnts      = GeoPositions3f::create();
    GeoPLengthsUI32Ptr  lens      = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr        types     = GeoPTypesUI8::create();
    GeoColors3fPtr        colors  = GeoColors3f::create();
//    GeoIndicesUI32Ptr   indices = GeoIndicesUI32::create();
    SimpleMaterialPtr    mat     = SimpleMaterial::create();

    height        = 0.0;
    widthHalf    = width/2.0;
    depthHalf     = depth/2.0;
//    hCellWidth     = 1;
    vCellWidth     = hCellWidth;
    nCols        = Int32( width / hCellWidth );
    nRows        = Int32( depth / vCellWidth );

    /*
    SLOG << "creating Grid: width=" << width 
         << ", depth=" << depth 
         << ", hCellWidth=" << hCellWidth    
         << ", vCellWidth=" << vCellWidth 
         << ", nCols=" << nCols
         << ", nRows=" << nRows << endl;
    */
    pntCnt=0;
    beginEditCP( pnts );
    beginEditCP( colors );
        // horizontal lines
        for( d = -nRows/2; d <= nRows/2; ++d  )
        {
            z = d*vCellWidth;
            pnts->addValue( Pnt3f(-widthHalf , height, z) );
            pnts->addValue( Pnt3f( widthHalf , height, z) );
            pntCnt++; pntCnt++;
            colors->addValue( color );
            colors->addValue( color );
        }
        // vertical lines
        for( w = -nCols/2; w <= nCols/2; ++w  )
        {
            x = w*hCellWidth;
            pnts->addValue( Pnt3f( x, height, -depthHalf) );
            pnts->addValue( Pnt3f( x, height,  depthHalf) );
            pntCnt++; pntCnt++;
            colors->addValue( color );
            colors->addValue( color );            
        }
        
        /*
        // horizontal & vertical mid lines in different color
        pnts->addValue( Pnt3f( -widthHalf, height, 0) );
        pnts->addValue( Pnt3f( widthHalf, height, 0) );
        pntCnt++; pntCnt++;
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );
        
        
        pnts->addValue( Pnt3f( 0, height, -depthHalf) );
        pnts->addValue( Pnt3f( 0, height, depthHalf) );
        pntCnt++; pntCnt++;        
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );        
        */
    endEditCP( colors );        
    endEditCP( pnts );
    
    //SLOG << "Grid has " << pntCnt << " points.\n" << endl;
    
    beginEditCP( types );
    beginEditCP( lens );
        types->addValue( GL_LINES );
        lens->addValue( pntCnt );
    endEditCP( lens );
    endEditCP( types );
        
    // set the color for the grid
    beginEditCP( mat );
        mat->setAmbient( color ); 
        mat->setDiffuse( color ); 
        mat->setLit( false );
    endEditCP( mat );    
    
    beginEditCP( geo );
        geo->setPositions    ( pnts );    
//        geo->setIndices        ( indices );
        geo->setColors        ( colors );
        geo->setTypes        ( types );
        geo->setLengths        ( lens );                    
        geo->setMaterial    ( mat );
    endEditCP( geo );    
    
    return geo;    
}                                                  


GeometryPtr makeGridBorderGeo( Real32 width, Real32 depth, Color3f color )
{
    Real32        height, widthHalf, depthHalf;
//    Real32        vCellWidth;
//    Real32        w, d;
//    Int32        index, pntCnt, nCols, nRows;
    Int32       pntCnt;
//    Real32        x, z;    
    Color3f     darkerColor = 
                    Color3f( color[0]-0.4, color[1]-0.4, color[2]-0.4 ); 

    GeometryPtr         geo     = Geometry::create();
    GeoPositions3fPtr    pnts      = GeoPositions3f::create();
    GeoPLengthsUI32Ptr  lens      = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr        types     = GeoPTypesUI8::create();
    GeoColors3fPtr        colors  = GeoColors3f::create();
//    GeoIndicesUI32Ptr   indices = GeoIndicesUI32::create();
    SimpleMaterialPtr    mat     = SimpleMaterial::create();
    LineChunkPtr        lineChunk= LineChunk::create();

    height        = 0.0;
    widthHalf    = width/2.0;
    depthHalf     = depth/2.0;
                 
    pntCnt=0;
    beginEditCP( pnts );
    beginEditCP( colors );
        // horizontal & vertical mid lines in different color
        pnts->addValue( Pnt3f( -widthHalf, height, 0) );
        pnts->addValue( Pnt3f( widthHalf, height, 0) );
        pntCnt++; pntCnt++;
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );
                
        pnts->addValue( Pnt3f( 0, height, -depthHalf) );
        pnts->addValue( Pnt3f( 0, height, depthHalf) );
        pntCnt++; pntCnt++;        
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );        
        
        // the border
        pnts->addValue( Pnt3f( -widthHalf,  0,     depthHalf) );
        pnts->addValue( Pnt3f(  widthHalf,  0,     depthHalf) );
        pntCnt++; pntCnt++;        
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );                
        
        pnts->addValue( Pnt3f(  widthHalf,  0,     depthHalf) );
        pnts->addValue( Pnt3f(  widthHalf,  0, -depthHalf) );
        pntCnt++; pntCnt++;        
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );                
        
        pnts->addValue( Pnt3f(  widthHalf,  0, -depthHalf) );
        pnts->addValue( Pnt3f( -widthHalf,  0, -depthHalf) );
        pntCnt++; pntCnt++;        
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );                

        pnts->addValue( Pnt3f( -widthHalf,  0, -depthHalf) );
        pnts->addValue( Pnt3f( -widthHalf,  0,     depthHalf) );
        pntCnt++; pntCnt++;        
        colors->addValue( darkerColor );
        colors->addValue( darkerColor );                        
    endEditCP( colors );        
    endEditCP( pnts );
    
    beginEditCP( lineChunk );
        lineChunk->setWidth( 1 );
        lineChunk->setSmooth( true );
    endEditCP( lineChunk );
    
    beginEditCP( types );
    beginEditCP( lens );
        types->addValue( GL_LINES );
        lens->addValue( pntCnt );
    endEditCP( lens );
    endEditCP( types );
        
    // set the color for the grid
    beginEditCP             (mat);
        mat->setLit         (false);
        mat->addChunk        (lineChunk);
    endEditCP                (mat);    
    
    beginEditCP( geo );
        geo->setPositions    (pnts);
//        geo->setIndices        (indices );
        geo->setColors        (colors);
        geo->setTypes        (types);
        geo->setLengths        (lens);
        geo->setMaterial    (mat);
    endEditCP( geo );    
    
    return geo;    
}

/*! \brief create a grid
 *  \ingroup SimpleGeometryExt
 
     Creates a grid with the specified <i>width</i> and <i>height</i>.
    The grid has the base color <i>color</i>.
 */
NodePtr makeGrid(     Real32  width, 
                    Real32  depth,
                      Real32  hCellWidth,
                      Color3f color )
{
    NodePtr     grpNode = Node::create();
    GroupPtr     grpCore = Group::create();
    
    NodePtr     gridNode = Node::create();
    NodePtr     borderNode = Node::create();
    
    beginEditCP             (gridNode);
    beginEditCP             (borderNode);
        gridNode->setCore    (makeGridGeo(width, depth, hCellWidth, color));
        borderNode->setCore (makeGridBorderGeo(width, depth, color));
    endEditCP                (gridNode);
    endEditCP                (borderNode);

    
    beginEditCP             (grpNode, Node::CoreFieldMask);
        grpNode->setCore    (grpCore);    
        grpNode->addChild    (gridNode);
        grpNode->addChild    (borderNode);
    endEditCP                (grpNode);
    
    return grpNode;
}                                        


NodePtr makeSelection(NodePtr geoN)
{
    NodePtr               transN = Node::create();
    NodePtr               node   = Node::create();
    ComponentTransformPtr transC = ComponentTransform::create();

    beginEditCP     (node);
    node->setCore   (makeSelectionGeo(geoN));
    endEditCP        (node);
    
    beginEditCP     (transN, Node::CoreFieldMask | Node::ChildrenFieldMask);
    transN->setCore (transC);
    transN->addChild(node  );
    endEditCP       (transN, Node::CoreFieldMask | Node::ChildrenFieldMask);
    
    addRefCP(transN);
        
    return          transN;
}

GeometryPtr makeSelectionGeo(NodePtr geoN)
{
    Pnt3f       min, 
                max;
//    Int32        pntCnt=0;

    geoN->getVolume().getBounds(min,max);
        
    GeometryPtr         geo     = Geometry::create();
    GeoPositions3fPtr    newPnts = GeoPositions3f::create();
    GeoPLengthsUI32Ptr  lens      = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr        types     = GeoPTypesUI8::create();
    GeoColors3fPtr        colors  = GeoColors3f::create();
    
//    GeoIndicesUI32Ptr   indices = GeoIndicesUI32::create();
    SimpleMaterialPtr    mat     = SimpleMaterial::create();
    
    LineChunkPtr        lineChunk= LineChunk::create();    
            
    GeometryPtr selGeoC = GeometryPtr::dcast(geoN->getCore());
    if( selGeoC != NullFC )
    {
        GeoPositions3fPtr pnts = GeoPositions3fPtr::dcast(selGeoC->getPositions());
//        GeoPositions3f::StoredFieldType     *p = pnts->getFieldPtr();
        
//        GeoPositions3f::StoredFieldType::iterator it;
        FaceIterator fi;
        
        beginEditCP(newPnts);
        beginEditCP(colors);
        beginEditCP(lens);
        beginEditCP(types);
        for(fi=selGeoC->beginFaces(); fi!=selGeoC->endFaces(); ++fi)
        {            
            newPnts->addValue( fi.getPosition( 0 ) );            
            newPnts->addValue( fi.getPosition( 1 ) );            
            newPnts->addValue( fi.getPosition( 2 ) );
            
            colors->addValue( Color3f(1,1,1) );
            colors->addValue( Color3f(1,1,1) );
            colors->addValue( Color3f(1,1,1) );
            
            types->addValue( GL_LINE_STRIP );
            lens->addValue( 3 );
            
        }
        endEditCP(newPnts);
        endEditCP(colors);
        endEditCP(lens);
        endEditCP(types);
        
    }
    
    beginEditCP( lineChunk );
        lineChunk->setWidth( 1 );
        lineChunk->setSmooth( false );
    endEditCP( lineChunk );
            
    // set the color for the grid
    beginEditCP             (mat);
        mat->setLit         (false);
        mat->addChunk        (lineChunk);
    endEditCP                (mat);    
    
    beginEditCP( geo );
        geo->setPositions    (newPnts);
//        geo->setIndices        (indices );
//        geo->setColors        (colors);
        geo->setTypes        (types);
        geo->setLengths        (lens);
        geo->setMaterial    (mat);
    endEditCP( geo );    
    
    return geo;        
}




GeometryPtr makeCoordAxisGeo(Real32 length, Real32 lineWidth, bool showAxisName)
{
    Int32                pntCnt;
    
    GeometryPtr         geo     = Geometry::create();
    GeoPositions3fPtr    pnts      = GeoPositions3f::create();
    GeoPLengthsUI32Ptr  lens      = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr        types     = GeoPTypesUI8::create();
    GeoColors3fPtr        colors  = GeoColors3f::create();
    
//    GeoIndicesUI32Ptr   indices = GeoIndicesUI32::create();
    SimpleMaterialPtr    mat     = SimpleMaterial::create();
    
    LineChunkPtr        lineChunk= LineChunk::create();
        
    pntCnt=0;
    beginEditCP( pnts );
    beginEditCP( colors );
        // the x-axis coords and colors
        pnts->addValue( Pnt3f(0,0,0) );
        pnts->addValue( Pnt3f(length,0,0) );
        pntCnt++; pntCnt++;        
        colors->addValue( Color3f(1,0,0) );
        colors->addValue( Color3f(1,0,0) );        

        // the y-axis coords and colors
        pnts->addValue( Pnt3f(0,0,0) );
        pnts->addValue( Pnt3f(0,length,0) );
        pntCnt++; pntCnt++;
        colors->addValue( Color3f(0,1,0) );
        colors->addValue( Color3f(0,1,0) );        

        // the z-axis coords and colors
        pnts->addValue( Pnt3f(0,0,0) );
        pnts->addValue( Pnt3f(0,0,length) );
        pntCnt++; pntCnt++;            
        colors->addValue( Color3f(0,0,1) );
        colors->addValue( Color3f(0,0,1) );                
        
        if( showAxisName )
        {
            // the x text (drawn with lines)
            pnts->addValue( Pnt3f(length,         0.125,    0) );
            pnts->addValue( Pnt3f(length+0.25,    -0.125,    0) );
            pntCnt++; pntCnt++;            
            colors->addValue( Color3f(1,0,0) );
            colors->addValue( Color3f(1,0,0) );                
            pnts->addValue( Pnt3f(length,-0.125,0) );
            pnts->addValue( Pnt3f(length+0.25,0.125,0) );
            pntCnt++; pntCnt++;            
            colors->addValue( Color3f(1,0,0) );
            colors->addValue( Color3f(1,0,0) );                

            // the y text (drawn with lines)
            pnts->addValue( Pnt3f(-0.125, length,        0) );
            pnts->addValue( Pnt3f( 0.125, length+0.25,    0) );
            pntCnt++; pntCnt++;            
            colors->addValue( Color3f(0,1,0) );
            colors->addValue( Color3f(0,1,0) );                
            pnts->addValue( Pnt3f(-0.125, length+0.25,        0) );
            pnts->addValue( Pnt3f( 0.000, length+0.125,0) );
            pntCnt++; pntCnt++;            
            colors->addValue( Color3f(0,1,0) );
            colors->addValue( Color3f(0,1,0) );        

            // the z text (drawn with lines)

            pnts->addValue( Pnt3f(-0.125, 0,    length) );
            pnts->addValue( Pnt3f( 0.125, 0,    length) );
            pntCnt++; pntCnt++;            
            colors->addValue( Color3f(0,0,1) );
            colors->addValue( Color3f(0,0,1) );                
            pnts->addValue( Pnt3f( 0.125, 0,    length) );
            pnts->addValue( Pnt3f(-0.125, 0,    length+0.25) );
            pntCnt++; pntCnt++;            
            colors->addValue( Color3f(0,0,1) );
            colors->addValue( Color3f(0,0,1) );        
            pnts->addValue( Pnt3f(-0.125, 0,    length+0.25) );
            pnts->addValue( Pnt3f( 0.125, 0,    length+0.25) );
            pntCnt++; pntCnt++;            
            colors->addValue( Color3f(0,0,1) );
            colors->addValue( Color3f(0,0,1) );        
        }
    endEditCP( colors );
    endEditCP( pnts );
    
    //SLOG << "CoordAxis has " << pntCnt << " points.\n" << endl;
    
    beginEditCP( types );
    beginEditCP( lens );
        types->addValue( GL_LINES );
        lens->addValue( pntCnt );
    endEditCP( lens );
    endEditCP( types );
        
    
    beginEditCP( lineChunk );
        lineChunk->setWidth( lineWidth );
    endEditCP( lineChunk );
    
    beginEditCP( mat );
    /*
        mat->setAmbient( Color3f(1,1,1) ); 
        mat->setDiffuse( Color3f(1,1,1) ); 
    */
        mat->addChunk    ( lineChunk );
        mat->setLit     ( false );
    endEditCP( mat );    

    beginEditCP( geo );
        geo->setPositions    ( pnts );    
        geo->setColors        ( colors );
//        geo->setIndices        ( indices );
        geo->setTypes        ( types );
        geo->setLengths        ( lens );                    
        geo->setMaterial    ( mat );
    endEditCP( geo );    
    
    return geo;    
}                                                  

NodePtr makeCoordAxis    ( Real32 length, Real32 lineWidth, bool showAxisName )
{
    NodePtr node = Node::create();
    
    beginEditCP( node );
        node->setCore(makeCoordAxisGeo(length, lineWidth, showAxisName));
    endEditCP( node );
    
    return node;
}

PolygonChunkPtr _gayaPolygonChunk;

PolygonChunkPtr getPolygonChunk(UInt16 faces, UInt16 mode)
{
    if( _gayaPolygonChunk == NullFC )
    {
        _gayaPolygonChunk = PolygonChunk::create();
    
        addRefCP(_gayaPolygonChunk);
    
        _gayaPolygonChunk->setCullFace(faces);
        _gayaPolygonChunk->setFrontMode(mode);
        _gayaPolygonChunk->setSmooth(true);
        _gayaPolygonChunk->setOffsetLine(true);
        _gayaPolygonChunk->setOffsetFill(false);
        _gayaPolygonChunk->setOffsetFactor(-1);
//        _gayaPolygonChunk->setOffsetBias(1);
    }
    return _gayaPolygonChunk;
}

MaterialChunkPtr _gayaMaterialChunk;

MaterialChunkPtr getMaterialChunk(Color4f ambientColor, Color4f diffuseColor,
                                 Color4f specularColor,
                                 bool lit)
{
    if( _gayaMaterialChunk == NullFC )
    {
        _gayaMaterialChunk = MaterialChunk::create();
    
        addRefCP(_gayaMaterialChunk);
    
        _gayaMaterialChunk->setDiffuse(diffuseColor);
        _gayaMaterialChunk->setAmbient(ambientColor);
        _gayaMaterialChunk->setSpecular(specularColor);
        _gayaMaterialChunk->setLit(lit);
    }
    return _gayaMaterialChunk;
}



ChunkMaterialPtr _gayaSelectionMaterial;


ChunkMaterialPtr getSelectionMaterial()
{
    if( _gayaSelectionMaterial == NullFC )
    {
        _gayaSelectionMaterial = ChunkMaterial::create();
    
        addRefCP(_gayaSelectionMaterial);
    
        _gayaSelectionMaterial->addChunk(getPolygonChunk());
        _gayaSelectionMaterial->addChunk(getMaterialChunk(Color4f(1,1,1,0),
                                                          Color4f(1,1,1,0)));
    }
    return _gayaSelectionMaterial;
}


OSG_END_NAMESPACE
