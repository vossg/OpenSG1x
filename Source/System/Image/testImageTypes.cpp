#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGComponentTransform.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGSceneFileHandler.h>
#include <OSGGroup.h>
#include <OSGImage.h>

#include <math.h>

// to write out raw data
#include <fstream>
#include <iostream>

int putbyte(FILE *outf, unsigned char val)
{
    unsigned char buf[1];
 
    buf[0] = val;
    return fwrite(buf,1,1,outf);
}
 
int putshort(FILE *outf, unsigned short val)
{
    unsigned char buf[2];
 
    buf[0] = (val>>8);
    buf[1] = (val>>0);
    return fwrite(buf,1,2,outf);
}
 
int putlong(FILE *outf, unsigned long val)
{
    unsigned char buf[4];
 
    buf[0] = (unsigned char)(val>>24);
    buf[1] = (unsigned char)(val>>16);
    buf[2] = (unsigned char)(val>>8);
    buf[3] = (unsigned char)(val>>0);
    return fwrite(buf,1,4,outf);
}
 
void save_rgb( const char* pcFileName, unsigned char* pucNormalImageData, unsigned int uiWidth, unsigned int uiHeight, int iNumColorChannels )
{
    FILE*	pt_output;
    char	ac_converted_int[80];
	int		i_num_bytes = 0;
 
	// open file
	pt_output = fopen( pcFileName, "wb" );
	if ( NULL == pt_output ) {

		return;
	}

	strcpy( ac_converted_int, pcFileName );
	ac_converted_int[79] = (char)0;

    // write header
	putshort( pt_output, 474 );								/* MAGIC                       */
	putbyte( pt_output, 0 );								/* STORAGE is VERBATIM         */
	putbyte( pt_output, 1 );								/* BPC is 1                    */
	putshort( pt_output, 3 );								/* DIMENSION is 2              */
	putshort( pt_output, uiWidth );							/* XSIZE                       */
	putshort( pt_output, uiHeight );						/* YSIZE                       */
	putshort( pt_output, iNumColorChannels );				/* ZSIZE                       */
	putlong( pt_output, 0 );								/* PIXMIN is 0                 */
	putlong( pt_output, 255 );								/* PIXMAX is 255               */
	for( i_num_bytes=0; i_num_bytes<4; i_num_bytes++)		/* DUMMY 4 bytes       */
		putbyte( pt_output, 0 );
	fwrite( ac_converted_int, 80, 1, pt_output );			/* IMAGENAME           */
	putlong( pt_output, 0 );								/* COLORMAP is 0       */
	for( i_num_bytes=0; i_num_bytes<404; i_num_bytes++ )	/* DUMMY 404 bytes     */
		putbyte( pt_output, 0 );

	// write data
	int i_bytes_written= fwrite( pucNormalImageData, 1, uiWidth*uiHeight*iNumColorChannels, pt_output );
	if ( uiWidth*uiHeight*iNumColorChannels != i_bytes_written )
	{
		return;
	}
	fclose( pt_output );
}

void save_raw( const char* pcFileName, unsigned char* pucNormalImageData, unsigned int uiWidth, unsigned int uiHeight, int iNumColorChannels )
{
    FILE*	pt_output;
	int		i_num_bytes = 0;
 
	// open file
	pt_output = fopen( pcFileName, "wb" );
	if ( NULL == pt_output ) {

		return;
	}

	// write data
	int i_bytes_written= fwrite( pucNormalImageData, 1, uiWidth*uiHeight*iNumColorChannels, pt_output );
	if ( uiWidth*uiHeight*iNumColorChannels != i_bytes_written )
	{
		return;
	}
	fclose( pt_output );
}

bool raw_to_rgb( unsigned char* &rpucNormalImageData, unsigned int uiWidth, unsigned int uiHeight, int iNumColorChannels )
{
	unsigned char* pucTempData;
	pucTempData= new unsigned char[uiWidth*uiHeight*iNumColorChannels];

	unsigned char* pucCurrentIndex= rpucNormalImageData;

	if ( NULL == pucTempData)
	{
		return false;
	}

	for ( unsigned int ui_y= 0; ui_y< uiHeight; ui_y++)
		for ( unsigned int ui_x= 0; ui_x< uiWidth; ui_x++)
			for ( int i_channel= 0; i_channel < iNumColorChannels; i_channel++)
//				pucTempData[i_channel*uiWidth*uiHeight+( uiHeight - ui_y)*uiWidth+ui_x]= *(pucCurrentIndex++);
				pucTempData[i_channel*uiWidth*uiHeight+ ui_y*uiWidth+ui_x]= *(pucCurrentIndex++);

	pucCurrentIndex= rpucNormalImageData;
	rpucNormalImageData= pucTempData;

	delete [] pucCurrentIndex;
	return true;
}


// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// The SimpleSceneManager to manage simple applications
SimpleSceneManager *gpcl_mgr;


// global variables for easy access to loaded geometries
ImagePtr pcl_textimage_orig = NullFC;
ImagePtr pcl_textimage = NullFC;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// redraw the window
void display( void )
{
    gpcl_mgr->redraw();
}

//create the chessboard (so far a textured quad only)
NodePtr makeChessboardNode( Real32 fSize)
{
	NodePtr pcl_node= Node::create();
    GeometryPtr pcl_geo = Geometry::create();
    beginEditCP( pcl_node, Node::CoreFieldMask );
    {
        pcl_node->setCore( pcl_geo );        
    }
    endEditCP( pcl_node, Node::CoreFieldMask );

    GeoPTypesPtr pcl_type = GeoPTypesUI8::create();
    beginEditCP(pcl_type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        pcl_type->addValue(GL_QUADS);
    }
    endEditCP(pcl_type, GeoPTypesUI8::GeoPropDataFieldMask);
    GeoPLengthsPtr pcl_lens = GeoPLengthsUI32::create();
    beginEditCP(pcl_lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        // 1 quad with 4 points 
        pcl_lens->addValue(4);
    }
    endEditCP  (pcl_lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    
	GeoPositions3fPtr pcl_pnts = GeoPositions3f::create();
	beginEditCP(pcl_pnts, GeoPositions3f::GeoPropDataFieldMask);
    {
        // the 4 points of the quad
		pcl_pnts->push_back(Pnt3f( fSize, fSize, 0.0 ));
        pcl_pnts->push_back(Pnt3f( -fSize, fSize, 0.0 ));
        pcl_pnts->push_back(Pnt3f( -fSize, -fSize, 0.0 ));
        pcl_pnts->push_back(Pnt3f( fSize, -fSize, 0.0 ));
    }
    endEditCP  (pcl_pnts, GeoPositions3f::GeoPropDataFieldMask);

    GeoTexCoordsPtr pcl_texcoords = GeoTexCoords2f::create();
    beginEditCP( pcl_texcoords, GeoTexCoords2f::GeoPropDataFieldMask);
    {
        pcl_texcoords->push_back( Vec2f( 1.0, 1.0 ) );
        pcl_texcoords->push_back( Vec2f( 0.0, 1.0 ) );
        pcl_texcoords->push_back( Vec2f( 0.0, 0.0 ) );
        pcl_texcoords->push_back( Vec2f( 1.0, 0.0 ) );
        
    }
    endEditCP( pcl_texcoords, GeoTexCoords2f::GeoPropDataFieldMask);
    
    
    // build the material
    // first load the texture
	FLOG(("create image & read chessboard \n"));
	pcl_textimage_orig = Image::create();
	pcl_textimage_orig->read("chessboard.ppm");
	//pcl_textimage_orig->clear(255);
	save_raw( "testcreate_orig.raw", pcl_textimage_orig->getData(), 720, 720, 3 );
	

	pcl_textimage = Image::create();
	pcl_textimage = pcl_textimage_orig;
	

	// for MipMap-Test
	ImagePtr pcl_textimage_2 = Image::create();
	ImagePtr pcl_textimage_3 = Image::create();


	/*  TEST convertDataType 
	pcl_textimage->convertDataTypeTo(Image::OSG_FLOAT32_IMAGEDATA);
	pcl_textimage->convertDataTypeTo(Image::OSG_UINT32_IMAGEDATA);
	//pcl_textimage->convertDataTypeTo(Image::OSG_UINT8_IMAGEDATA);
	*/
	
	/* TEST scale
	pcl_textimage_2->set(pcl_textimage);
	pcl_textimage_2->setWidth(90);
	pcl_textimage_2->setHeight(90);
	pcl_textimage_2->convertDataTypeTo(Image::OSG_FLOAT32_IMAGEDATA);
	pcl_textimage->convertDataTypeTo(Image::OSG_FLOAT32_IMAGEDATA);
	pcl_textimage->scale(90, 90, 1, pcl_textimage_2);
	pcl_textimage = pcl_textimage_2;
	*/

	/* TEST subImage
	pcl_textimage_orig->subImage(720,720,0,360,360,0,pcl_textimage);
	*/

	/* TEST create MipMap */
	pcl_textimage->convertDataTypeTo(Image::OSG_UINT32_IMAGEDATA);

	pcl_textimage->createMipmap(3);

	pcl_textimage_2->set(pcl_textimage);
	beginEditCP (pcl_textimage_2, Image::WidthFieldMask || ImageBase::HeightFieldMask );
		pcl_textimage_2->setWidth(360);
		pcl_textimage_2->setHeight(360);
	endEditCP (pcl_textimage_2, Image::WidthFieldMask || ImageBase::HeightFieldMask );
	pcl_textimage_2->setData(pcl_textimage->getData(1,0));
	
	pcl_textimage_3->set(pcl_textimage);
	beginEditCP (pcl_textimage_3, Image::WidthFieldMask || ImageBase::HeightFieldMask );
		pcl_textimage_3->setWidth(180);
		pcl_textimage_3->setHeight(180);
	endEditCP (pcl_textimage_3, Image::WidthFieldMask || ImageBase::HeightFieldMask );
	pcl_textimage_3->setData(pcl_textimage->getData(2,0));
	
	// convert back to UINT8 to view in IrfanView
	// pcl_textimage->convertDataTypeTo(Image::OSG_UINT8_IMAGEDATA);

	// convert back to UINT8 to make loadable in IrfanView
	// pcl_textimage_orig->set(pcl_textimage_3);
	pcl_textimage_2->convertDataTypeTo(Image::OSG_UINT8_IMAGEDATA);
	pcl_textimage_3->convertDataTypeTo(Image::OSG_UINT8_IMAGEDATA);

	save_raw( "testcreate.raw", pcl_textimage->getData(), 720, 720, 3 );
	save_raw( "testcreate2.raw", pcl_textimage_2->getData(), 360, 360, 3 );
	save_raw( "testcreate3.raw", pcl_textimage_3->getData(), 180, 180, 3 );


	/* TEST slice	
	//pcl_textimage_orig->slice(-1, -1, 1, pcl_textimage);
	*/
	
	
	/* TEST operator ==
	ImagePtr pcl_textimage_orig_2 = Image::create();
	pcl_textimage_orig_2->read("textures/chessboard.jpg");
	
	// pcl_textimage = pcl_textimage_orig;
	FLOG (("Bilder Vergleich: \n\n"));
	FLOG (("%d , %d\n", pcl_textimage_orig->getWidth(), pcl_textimage_orig_2->getWidth()));
	FLOG (("%d , %d\n", pcl_textimage_orig->getHeight(), pcl_textimage_orig_2->getHeight()));
	FLOG (("%d , %d\n", pcl_textimage_orig->getDepth(), pcl_textimage_orig_2->getDepth()));
	FLOG (("%d , %d\n", pcl_textimage_orig->getMipMapCount(), pcl_textimage_orig_2->getMipMapCount()));
	FLOG (("%d , %d\n", pcl_textimage_orig->getFrameCount(), pcl_textimage_orig_2->getFrameCount()));
	FLOG (("%d , %d\n", pcl_textimage_orig->getFrameDelay(), pcl_textimage_orig_2->getFrameDelay()));
	FLOG (("%d , %d\n", pcl_textimage_orig->getPixelFormat(), pcl_textimage_orig_2->getPixelFormat()));
	FLOG (("%d , %d\n", pcl_textimage_orig->getDataType(), pcl_textimage_orig_2->getDataType()));

	bool test = (pcl_textimage_orig_2->operator==(*pcl_textimage_orig));
	bool test2 = pcl_textimage_orig_2 == pcl_textimage_orig;
	FLOG (("Bilder gleich?: %d\n", test));
	FLOG (("Bilder gleich?: %d\n", test2));
	*/

	/* TEST float ability
		pcl_textimage->setDataType(Image::OSG_FLOAT32_IMAGEDATA);
		pcl_textimage->read("textures/leather.xml.index.ppm");
		pcl_textimage->read("textures/leather.xml.comp.pfm");
		pcl_textimage->setWidth( 512 );
		pcl_textimage->setHeight( 512 ); 
	*/	        		
	
	SimpleTexturedMaterialPtr pcl_mat = SimpleTexturedMaterial::create();

    beginEditCP( pcl_mat );
    {
        pcl_mat->setImage        (pcl_textimage);
		//pcl_mat->setInternalFormat(FLOAT_RGB32_NV);
		
		/*        
		pcl_mat->setMinFilter    (GL_LINEAR_MIPMAP_LINEAR);
        pcl_mat->setMagFilter    (GL_LINEAR);
        */
		/*
		pcl_mat->setMinFilter    (GL_NEAREST);
        pcl_mat->setMagFilter    (GL_NEAREST);
		*/
		
        pcl_mat->setEnvMode      (GL_REPLACE);
        pcl_mat->setEnvMap       (false);
    }
    endEditCP( pcl_mat );
    beginEditCP(pcl_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::TexCoordsFieldMask |
                         Geometry::MaterialFieldMask);
    {
        pcl_geo->setTypes( pcl_type );
        pcl_geo->setLengths( pcl_lens );
        pcl_geo->setPositions( pcl_pnts );
        pcl_geo->setTexCoords( pcl_texcoords );
        pcl_geo->setMaterial( pcl_mat );
        
    }

    endEditCP  (pcl_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::TexCoordsFieldMask |
                         Geometry::MaterialFieldMask);
    
	return (pcl_node);
}


// Initialize GLUT & OpenSG and set up the scene
int main(int iArgc, char** ppcArgv)
{
    // OSG init
    osgInit( iArgc, ppcArgv );
        

    // GLUT init
    int i_winid = setupGLUT( &iArgc, ppcArgv );

    // the connection between GLUT and OpenSG
    GLUTWindowPtr pcl_gwin= GLUTWindow::create();
    pcl_gwin->setId(i_winid);
    pcl_gwin->init();

    // create the scene
    // create the root node
    NodePtr pcl_root = Node::create();
    GroupPtr pcl_rootcore = Group::create();
    // create the chessboard node
    NodePtr pcl_board = makeChessboardNode( 4000.0 );

    // setupPieces();
    // setup root node
    beginEditCP( pcl_root, Node::CoreFieldMask | Node::ChildrenFieldMask );
    {
        pcl_root->setCore( pcl_rootcore );

		pcl_root->addChild( pcl_board );

    }
    endEditCP( pcl_root, Node::CoreFieldMask | Node::ChildrenFieldMask);
    // create the SimpleSceneManager helper
    gpcl_mgr = new SimpleSceneManager();

    // tell the manager what to manage
    gpcl_mgr->setWindow( pcl_gwin );
    gpcl_mgr->setRoot  ( pcl_root);

    gpcl_mgr->getAction()->setFrustumCulling( false );

    // show the whole scene
    gpcl_mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// react to size changes
void reshape( int iWidth, int iHeight )
{
    gpcl_mgr->resize( iWidth, iHeight );
    glutPostRedisplay();
}

// react to mouse button presses
void mouse( int iButton, int iState, int iX, int iY )
{
    if ( iState )
        gpcl_mgr->mouseButtonRelease( iButton, iX, iY );
    else
        gpcl_mgr->mouseButtonPress( iButton, iX, iY );
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int iX, int iY)
{
    gpcl_mgr->mouseMove( iX, iY );
    glutPostRedisplay();
}

// react to keys
void keyboard( unsigned char ucKey, int iX, int iY )
{
    switch( ucKey )
    {
		case 27:
			exit(1);
        case 'W':
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		    glEnable( GL_LIGHTING );
            glutPostRedisplay( );
		    break;
        case 'w':                    
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		    glDisable( GL_LIGHTING );                    
		    glutPostRedisplay( );
            break;
        default:
			break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int* piArgc, char* pacArgv[])
{
    glutInit( piArgc, pacArgv );
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int i_winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return i_winid;
}
