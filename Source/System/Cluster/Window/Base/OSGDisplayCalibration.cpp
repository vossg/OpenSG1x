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

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGMaterialChunk.h>

#include "OSGDisplayCalibration.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DisplayCalibration
The DisplayCalibration is responsible to calibrate a cluster window
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DisplayCalibration::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DisplayCalibration::DisplayCalibration(void) :
    Inherited(),
    _changed(true),
    _cmPort(NullFC),
    _dsPort(NullFC),
    _dsPort2(NullFC)
{
}

DisplayCalibration::DisplayCalibration(const DisplayCalibration &source) :
    Inherited(source),
    _changed(true),
    _cmPort(NullFC),
    _dsPort(NullFC),
    _dsPort2(NullFC)
{
}

DisplayCalibration::~DisplayCalibration(void)
{
    if(_cmPort != osg::NullFC) 
    {
        subRefCP(_cmPort);
        subRefCP(_dsPort);
        subRefCP(_dsPort2);
        subRefCP(_cmRoot);
        subRefCP(_dsRoot);
        subRefCP(_ds2Root);
        subRefCP(_cam);
        subRefCP(_dsBack);
        subRefCP(_ds2Back);
    }
}

/*----------------------------- class specific ----------------------------*/

/*! Calibrate display 
 */
void DisplayCalibration::calibrate(ViewportPtr port,RenderActionBase *ract)
{
    WindowPtr window=port->getParent();
    if(!getEnabled())
        return;

    createCMViewports(port);

    window->addPort(_cmPort);
    _cmPort->render(ract);
    window->subPort(_cmPort);

    if(getScaleDown() < 1.0f)
    {
        window->addPort(_dsPort);
        _dsPort->render(ract);
        window->subPort(_dsPort);
        window->addPort(_dsPort2);
        _dsPort2->render(ract);
        window->subPort(_dsPort2);
    }

}

void DisplayCalibration::changed(BitVector whichField, UInt32 origin)
{
    _changed = true;
    Inherited::changed(whichField, origin);
}

void DisplayCalibration::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DisplayCalibration NI" << std::endl;
}

void DisplayCalibration::createCMViewports(ViewportPtr port)
{
    WindowPtr window=port->getParent();

    // create color management structures
    if(_cmPort != osg::NullFC &&
       !_changed &&
       _vpLeft == port->getPixelLeft() &&
       _vpRight == port->getPixelRight() &&
       _vpBottom == port->getPixelBottom() &&
       _vpTop == port->getPixelTop())
        return;

    if(getScaleDown()>1.0)
        setScaleDown(1.0);

    _changed = false;
    _vpLeft = port->getPixelLeft();
    _vpBottom = port->getPixelBottom();
    _vpRight = port->getPixelRight();
    _vpTop = port->getPixelTop();

    // reset
    if(_cmPort != osg::NullFC) {
        subRefCP(_cmPort);
        subRefCP(_dsPort);
        subRefCP(_dsPort2);
        subRefCP(_cmRoot);
        subRefCP(_dsRoot);
        subRefCP(_ds2Root);
        subRefCP(_cam);
        subRefCP(_dsBack);
        subRefCP(_ds2Back);
    }

    Matrix m;
    ImagePtr img = Image::create();
    beginEditCP(img);
    img->set(GL_RGB,1,1);

    endEditCP(img);

    int extension;
    extension = osg::Window::registerExtension("GL_ARB_fragment_program");
    if(window->hasExtension(extension))
    {
        SINFO << "Use fragment program for color crrection" << std::endl;
        _useFragmentProgram = true;
    }
    else
    {
        SINFO << "Use reg combiner for color crrection" << std::endl;
        _useFragmentProgram = false;
    }
    extension = Window::registerExtension("GL_ARB_texture_non_power_of_two" );
    if(window->hasExtension(extension))
        _nonPowerOfTwo = true;
    else
        _nonPowerOfTwo = false;

    TextureChunkPtr tex = TextureChunk::create();    

    if(_useFragmentProgram)
    {
        // Step 1: The texture from the GrabBackground

        beginEditCP(tex);
        tex->setImage(img);
        tex->setMinFilter(GL_NEAREST);
        tex->setScale(false);
        tex->setEnvMode(GL_REPLACE);
        endEditCP  (tex);

        // Step 2: The textures for the initial gamma mapping
        
        // Texture Chunks for gamma mapping
        
        UChar8 rgammadata[] =
            {  0, 80, 160, 255 };
        
        _rgammaimg = Image::create();
        beginEditCP(_rgammaimg);
        _rgammaimg->set(Image::OSG_L_PF,4,1,1,1,1,0,rgammadata);
        endEditCP(_rgammaimg);
        
        _rgammachunk = TextureChunk::create();    
        beginEditCP(_rgammachunk);
        _rgammachunk->setImage(_rgammaimg);
        _rgammachunk->setMinFilter(GL_LINEAR);
        _rgammachunk->setMagFilter(GL_LINEAR);
        _rgammachunk->setWrapS(GL_CLAMP_TO_EDGE);
        _rgammachunk->setWrapT(GL_CLAMP_TO_EDGE);
        endEditCP  (_rgammachunk);
        
        UChar8 ggammadata[] =
            {  0, 80, 160, 255 };
        
        _ggammaimg = Image::create();
        beginEditCP(_ggammaimg);
        _ggammaimg->set(Image::OSG_L_PF,4,1,1,1,1,0,ggammadata);
        endEditCP(_ggammaimg);
        
        _ggammachunk = TextureChunk::create();    
        beginEditCP(_ggammachunk);
        _ggammachunk->setImage(_ggammaimg);
        _ggammachunk->setMinFilter(GL_LINEAR);
        _ggammachunk->setMagFilter(GL_LINEAR);
        _ggammachunk->setWrapS(GL_CLAMP_TO_EDGE);
        _ggammachunk->setWrapT(GL_CLAMP_TO_EDGE);
        endEditCP  (_ggammachunk);

        UChar8 bgammadata[] =
            {  0, 80, 160, 255 };
        
        _bgammaimg = Image::create();
        beginEditCP(_bgammaimg);
        _bgammaimg->set(Image::OSG_L_PF,4,1,1,1,1,0,bgammadata);
        endEditCP(_bgammaimg);
    
        _bgammachunk = TextureChunk::create();    
        beginEditCP(_bgammachunk);
        _bgammachunk->setImage(_bgammaimg);
        _bgammachunk->setMinFilter(GL_LINEAR);
        _bgammachunk->setMagFilter(GL_LINEAR);
        _bgammachunk->setWrapS(GL_CLAMP_TO_EDGE);
        _bgammachunk->setWrapT(GL_CLAMP_TO_EDGE);
        endEditCP  (_bgammachunk);

        // set gamma table
        for(int j=0; j < 3; ++j)
        {
            ImagePtr img;
            switch(j)
            {
                case 0: img = _rgammaimg; break;
                case 1: img = _ggammaimg; break;
                case 2: img = _bgammaimg; break;
            }
            beginEditCP(img);
            if(getGammaRamp().size() == 0)
            {
                img->set(Image::OSG_L_PF, 256, 1);
                UInt8 *data = img->getData();
                for(int i=0; i < 256; i++)
                {
                    data[i] = (UInt8)(pow(i/255.0,1.0)*255);
                }
            }
            else
            {
                img->set(Image::OSG_L_PF, getGammaRamp().size(), 1);
                UInt8 *data = img->getData();
                for(int i=0; i < getGammaRamp().size(); i++)
                {
                    data[i] = (UInt8)(getGammaRamp()[i][j] * 255);
                }
            }
            endEditCP(img);
        }

        // Step 3: FragmentProgram Chunk for color matrix multiply
        m.setValue(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);     
        
        _fragProgram = FragmentProgramChunk::create();
        std::string prog(
            "!!ARBfp1.0\n"
            "PARAM mat0 = program.local[1];\n"
            "PARAM mat1 = program.local[2];\n"
            "PARAM mat2 = program.local[3];\n"
            "PARAM mat3 = program.local[4];\n"
            "PARAM gamma = program.local[5];\n"
            "TEMP source;\n"
            "TEMP target;\n"
            "\n"
            "# get the grabbed texture's color\n"
            "TEX source, fragment.texcoord[0], texture[0], 2D;\n"
            "\n"
            "# gamma map it\n"
            "POW source.r, source.r, gamma.r;\n"
            "POW source.g, source.g, gamma.r;\n"
            "POW source.b, source.b, gamma.r;\n"
            "\n"
            "# do the matrix transform\n"
            "DP4 target.x, mat0, source;\n"
            "DP4 target.y, mat1, source;\n"
            "DP4 target.z, mat2, source;\n"
            "\n"
            "# map it through the target gamma\n"
            "TEX target.r, target.r, texture[1], 1D;\n"
            "TEX target.g, target.g, texture[2], 1D;\n"
            "TEX target.b, target.b, texture[3], 1D;\n"
            "\n"
            "# mov it to the output\n"
            "MOV result.color, target;\n"
            "END\n");
        
        beginEditCP(_fragProgram);
        _fragProgram->setProgram(prog);
        endEditCP(_fragProgram);
    }   
    else
    {
        // Step 1: The texture from the GrabBackground

        beginEditCP(tex);
        tex->setImage(img);
        tex->setWrapS(GL_CLAMP_TO_EDGE);
        tex->setWrapT(GL_CLAMP_TO_EDGE);

        tex->setMinFilter(GL_LINEAR);
        tex->setMagFilter(GL_LINEAR);

//        tex->setMinFilter(GL_NEAREST);
        tex->setScale(false);
        tex->setEnvMode(GL_REPLACE);
        tex->setShaderOperation(GL_TEXTURE_2D);
        tex->setInternalFormat(GL_RGB8);
        endEditCP  (tex);

        // Step 2: The textures for the initial gamma mapping
  
        // Texture Chunks for gamma mapping

        UChar8 _argammadata[] =
            {  0,  0,  0,    0,  0,  0,    0,  0,  0,    0,  0,  0,    
               80,  0,  0,   80,  0,  0,   80,  0,  0,   80,  0,  0,    
               160,  0,  0,  160,  0,  0,  160,  0,  0,  160,  0,  0,    
               255,  0,  0,  255,  0,  0,  255,  0,  0,  255,  0,  0  
            };
    
        _argammaimg = Image::create();
        beginEditCP(_argammaimg);
        _argammaimg->set(GL_RGB,4,4,1,1,1,0,_argammadata);
        endEditCP(_argammaimg);
    
        _argammachunk = TextureChunk::create();    
        beginEditCP(_argammachunk);
        _argammachunk->setImage(_argammaimg);
        _argammachunk->setMinFilter(GL_NEAREST);
        _argammachunk->setMagFilter(GL_NEAREST);
        _argammachunk->setWrapS(GL_CLAMP_TO_EDGE);
        _argammachunk->setWrapT(GL_CLAMP_TO_EDGE);
        _argammachunk->setShaderOperation(GL_DEPENDENT_AR_TEXTURE_2D_NV);
        _argammachunk->setShaderInput    (GL_TEXTURE0_ARB);
        _argammachunk->setInternalFormat(GL_RGB8);
        endEditCP  (_argammachunk);

        UChar8 _gbgammadata[] =
            {  0,  0,  0,     0, 80,  0,     0,160,  0,    0,255,  0,
               0,  0, 80,     0, 80, 80,     0,160, 80,    0,255, 80,
               0,  0,160,     0, 80,160,     0,160,160,    0,255,160,
               0,  0,255,     0, 80,255,     0,160,255,    0,255,255
            };
    
        _gbgammaimg = Image::create();
        beginEditCP(_gbgammaimg);
        _gbgammaimg->set(GL_RGB,4,4,1,1,1,0,_gbgammadata);
        endEditCP(_gbgammaimg);
    
        _gbgammachunk = TextureChunk::create();    
        beginEditCP(_gbgammachunk);
        _gbgammachunk->setImage(_gbgammaimg);
        _gbgammachunk->setMinFilter(GL_NEAREST);
        _gbgammachunk->setMagFilter(GL_NEAREST);
        _gbgammachunk->setWrapS(GL_CLAMP_TO_EDGE);
        _gbgammachunk->setWrapT(GL_CLAMP_TO_EDGE);
        _gbgammachunk->setShaderOperation(GL_DEPENDENT_GB_TEXTURE_2D_NV);
        _gbgammachunk->setShaderInput    (GL_TEXTURE0_ARB);
        _gbgammachunk->setInternalFormat(GL_RGB8);
        endEditCP  (_gbgammachunk);

        // Step 3: RegisterCombiners Chunk for color matrix multiply

        m.setValue(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);     
        m.setValue(1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1);
        
        _regCombiner = RegisterCombinersChunk::create();
    }

    // putting it all together
        
    ChunkMaterialPtr mat = ChunkMaterial::create();
    beginEditCP(mat);
    mat->addChunk(tex);
    if(_useFragmentProgram)
    {
        mat->addChunk(_rgammachunk);
        mat->addChunk(_ggammachunk);
        mat->addChunk(_bgammachunk);
        mat->addChunk(_fragProgram);
    }
    else
    {
        mat->addChunk(_argammachunk);
        mat->addChunk(_gbgammachunk);
        mat->addChunk(_regCombiner);
    }
    endEditCP(mat);

    // add the second viewport
     
    GeoPTypesUI8Ptr  types = GeoPTypesUI8::create();
    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(types);
    types->addValue(GL_QUADS);
    endEditCP(types);

    beginEditCP(lens);
    lens->addValue(4);
    endEditCP(lens);
    
    GeoPositions3fPtr pos = GeoPositions3f::create();
    beginEditCP(pos);
    pos->addValue(Pnt3f(-1, -1, -0.5));
    pos->addValue(Pnt3f( 1, -1, -0.5));
    pos->addValue(Pnt3f( 1,  1, -0.5));
    pos->addValue(Pnt3f(-1,  1, -0.5));
    endEditCP(pos);
    _positions=pos;
    
    _texcoords = GeoTexCoords2f::create();
    beginEditCP(_texcoords);
    _texcoords->addValue(Vec2f(0,0));
    _texcoords->addValue(Vec2f(1,0));
    _texcoords->addValue(Vec2f(1,1));
    _texcoords->addValue(Vec2f(0,1));
    endEditCP(_texcoords);
   
    GeometryPtr geo = Geometry::create();
    beginEditCP(geo);
    geo->setMaterial(mat);
    geo->setPositions(pos);
    geo->setTypes(types);
    geo->setTexCoords(_texcoords);
    geo->setLengths(lens);
    endEditCP  (geo);
    
    NodePtr cube = Node::create();
    beginEditCP(cube);
    cube->setCore(geo);
    endEditCP(cube);
   
    ComponentTransformPtr trans = ComponentTransform::create();
    beginEditCP(trans);
    trans->setTranslation(Vec3f(getScaleDown()-1, getScaleDown()-1, 0));
    trans->setScale(Vec3f(getScaleDown(), getScaleDown(), 1.0));
    endEditCP(trans);
    
    _cmRoot = Node::create();
    addRefCP(_cmRoot);
    beginEditCP(_cmRoot);
    _cmRoot->setCore(trans);
    _cmRoot->addChild(cube);
    endEditCP(_cmRoot);
 
    GroupPtr group = Group::create();
    NodePtr gr = Node::create();
    beginEditCP(gr);
    gr->setCore(group);
    gr->addChild(_cmRoot);
    endEditCP(gr);
   
    _cam = MatrixCamera::create();
    addRefCP(_cam);
    beginEditCP(_cam);
    _cam->setNear(0.1);
    _cam->setFar(10);
    _cam->setModelviewMatrix(Matrix::identity());
    _cam->setProjectionMatrix(Matrix::identity());   
    endEditCP(_cam);
    
    // create a dummy geometry
    _dsRoot = makePlane(1, 1, 1, 1);
    addRefCP(_dsRoot);
    beginEditCP(_dsRoot);
      _dsRoot->setActive(false);
    endEditCP(_dsRoot);
    
    // Add the grab background
    
    _cmBack = TextureGrabBackground::create();
    addRefCP(_cmBack);
    
    beginEditCP(_cmBack);
        _cmBack->setTexture(tex);
        _cmBack->setColor(Color3f(0,0,0));
    endEditCP(_cmBack);
    
    _cmPort = Viewport::create();
    addRefCP(_cmPort);

    beginEditCP(_cmPort);
        _cmPort->setCamera(_cam);
        _cmPort->setRoot(_cmRoot);
        _cmPort->setBackground(_cmBack);
        _cmPort->setLeft(port->getLeft());
        _cmPort->setRight(port->getRight());
        _cmPort->setBottom(port->getBottom());
        _cmPort->setTop(port->getTop());
    endEditCP(_cmPort);

    // create down scale viewport

    ImagePtr img2 = Image::create();
    beginEditCP(img2);
        img2->set(GL_RGB,1,1);
    endEditCP(img2);
    
    TextureChunkPtr tex2 = TextureChunk::create();
    beginEditCP(tex2);
        tex2->setImage(img2);
        tex2->setMinFilter(GL_NEAREST);
        tex2->setMagFilter(GL_NEAREST);
        tex2->setScale(false);
        tex2->setEnvMode(GL_REPLACE);
    endEditCP(tex2);
    
    _dsBack = TextureGrabBackground::create();
    addRefCP(_dsBack);
    beginEditCP(_dsBack);
        _dsBack->setTexture(tex2);
        _dsBack->setColor(Color3f(1,0,0));
    endEditCP(_dsBack);
    
    // create the down scale viewport
    _dsPort = Viewport::create();
    addRefCP(_dsPort);
    beginEditCP(_dsPort);
        _dsPort->setCamera(_cam);
        _dsPort->setRoot(_dsRoot);
        _dsPort->setBackground(_dsBack);
        _dsPort->setLeft(port->getLeft());
        _dsPort->setRight(port->getRight());
        _dsPort->setBottom(port->getBottom());
        _dsPort->setTop(port->getTop());
    endEditCP(_dsPort);

    // vp2
    
    _ds2Back = SolidBackground::create();
    addRefCP(_ds2Back);
    beginEditCP(_ds2Back);
        _ds2Back->setColor(Color3f(1,0,0));
    endEditCP(_ds2Back);

    ChunkMaterialPtr mat2 = ChunkMaterial::create();
    MaterialChunkPtr matc = MaterialChunk::create();
    
    beginEditCP(mat2);
        mat2->addChunk(tex2);
    endEditCP(mat2);

    GeometryPtr geo2 = Geometry::create();

    GeoPLengthsPtr lens2 = GeoPLengthsUI32::create();    
    beginEditCP(lens2);
    lens->addValue(4);
    endEditCP(lens2);

    _positionsScale = GeoPositions3f::create();
    beginEditCP(_positionsScale);
    _positionsScale->addValue(Pnt3f(-1, -1, -0.5));
    _positionsScale->addValue(Pnt3f( 1, -1, -0.5));
    _positionsScale->addValue(Pnt3f( 1,  1, -0.5));
    _positionsScale->addValue(Pnt3f(-1,  1, -0.5));
    endEditCP(_positionsScale);
    
    _texcoordsScale = GeoTexCoords2f::create();
    beginEditCP(_texcoordsScale);
    _texcoordsScale->addValue(Vec2f(0,0));
    _texcoordsScale->addValue(Vec2f(1,0));
    _texcoordsScale->addValue(Vec2f(1,1));
    _texcoordsScale->addValue(Vec2f(0,1));
    endEditCP(_texcoordsScale);

    beginEditCP(geo2);
    geo2->setMaterial(mat2);
    geo2->setPositions(_positionsScale);
    geo2->setTypes(types);
    geo2->setTexCoords(_texcoordsScale);
    geo2->setLengths(lens2);
    endEditCP(geo2);
 
    _ds2Root = Node::create();
    beginEditCP(_ds2Root);
    _ds2Root->setCore(geo2);
    endEditCP(_ds2Root);

    _dsPort2 = Viewport::create();
    addRefCP(_dsPort2);
    beginEditCP(_dsPort2);
        _dsPort2->setCamera(_cam);
        _dsPort2->setRoot(_ds2Root);
        _dsPort2->setBackground(_ds2Back);
        _dsPort2->setLeft(0);
        _dsPort2->setRight(1);
        _dsPort2->setBottom(0);
        _dsPort2->setTop(1);
    endEditCP(_dsPort2);

    updateMatrix();
    updateGamma();


    // ---------------------------------------------------------------
    // set projection grid
    // ---------------------------------------------------------------

    UInt32 x,y;
    Int32 left=0,top=1,bottom=0,right=1;
    left   = port->getPixelLeft();
    right  = port->getPixelRight();
    bottom = port->getPixelBottom();
    top    = port->getPixelTop();

    Real32 h=top-bottom+1;
    Real32 w=right-left+1;
    Real32 
        tw = osgnextpower2((UInt32)w), 
        th = osgnextpower2((UInt32)h);

    beginEditCP(_texcoords);
    beginEditCP(_positions);
    _positions->clear();
    _texcoords->clear();

    if(getGrid().size() == 0 ||
       getGrid().size() != getGridWidth() * getGridHeight() ||
       getGridWidth() < 2 ||
       getGridHeight() < 2)
    {
        if(!_nonPowerOfTwo)
        {
            _texcoords->addValue(Vec2f(0,0));
            _texcoords->addValue(Vec2f(w/tw,0));
            _texcoords->addValue(Vec2f(w/tw,h/th));
            _texcoords->addValue(Vec2f(0,h/th));
        }
        else
        {
            _texcoords->addValue(Vec2f(0,0));
            _texcoords->addValue(Vec2f(1,0));
            _texcoords->addValue(Vec2f(1,1));
            _texcoords->addValue(Vec2f(0,1));
        }
        _positions->addValue(Pnt3f(-1, -1, -0.5));
        _positions->addValue(Pnt3f( 1, -1, -0.5));
        _positions->addValue(Pnt3f( 1,  1, -0.5));
        _positions->addValue(Pnt3f(-1,  1, -0.5));
    }
    else
    {
        UInt32 i;
        bool   absolute=false;
        for(i=0;i<getGrid().size();++i)
            if(getGrid()[i][0]>1 ||
               getGrid()[i][1]>1)
            {
                absolute=true;
                break;
            }
        for(int y=0 ; y<getGridHeight()-1 ; ++y)
        {
            for(int x=0 ; x<getGridWidth()-1 ; ++x)
            {
                // calculate texture coordinates
                Vec2f tex[4];
                tex[0] = Vec2f(  x,  y);
                tex[1] = Vec2f(x+1,  y);
                tex[2] = Vec2f(x+1,y+1);
                tex[3] = Vec2f(  x,y+1);

                // get position
                Vec2f pos[4];
                pos[0] = getGrid()[y*getGridWidth()+x];
                pos[1] = getGrid()[y*getGridWidth()+x+1];
                pos[2] = getGrid()[(y+1)*getGridWidth()+x+1];
                pos[3] = getGrid()[(y+1)*getGridWidth()+x];
                for(i=0 ; i<4 ; ++i)
                {
                    // scale to 0 - 1
                    tex[i][0] /= getGridWidth() - 1;
                    tex[i][1] /= getGridHeight() - 1;
                    // scale to ^2 texture size
                    if(!_nonPowerOfTwo)
                    {
                        tex[i][0] *= w/(float)tw;
                        tex[i][1] *= h/(float)th;
                    }
                    if(absolute) 
                    {
                        pos[i][0] /= (w-1);
                        pos[i][1] /= (h-1);
                    }
                    _texcoords->addValue(tex[i]);
                    Pnt3f p(pos[i][0],pos[i][1],0);
                    _positions->addValue(p*2-Vec3f(1,1,1));
                }
            }
        }
    }
    endEditCP(_texcoords);

    beginEditCP(lens);
    lens->clear();
    lens->addValue(_positions->getSize());
    endEditCP(lens);

    endEditCP(_positions);

    // ---------------------------------------------------------------
    // set downscale params
    // ---------------------------------------------------------------

    UInt32 w2 = UInt32(((right - left) + 1) * getScaleDown());
    UInt32 h2 = UInt32(((top - bottom) + 1) * getScaleDown());
    UInt32 lefts = Int32(left * getScaleDown());
    UInt32 rights = w2 - 1;
    UInt32 bottoms = Int32(bottom * getScaleDown());
    UInt32 tops = h2 - 1;
    
    _dsPort->setSize(lefts,bottoms,rights,tops);
    _dsPort2->setSize(left,bottom,right,top);
                    
    Real32 h3= tops - bottoms + 1;
    Real32 w3= rights - lefts + 1;
    Real32 tw2 = osgnextpower2((UInt32) w2);
    Real32 th2 = osgnextpower2((UInt32) h2);
    
    beginEditCP(_texcoordsScale);
    _texcoordsScale->clear();
    _texcoordsScale->addValue(Vec2f(0,0));
    _texcoordsScale->addValue(Vec2f(w3/tw2,0));
    _texcoordsScale->addValue(Vec2f(w3/tw2,h3/th2));
    _texcoordsScale->addValue(Vec2f(0,h3/th2));
    endEditCP(_texcoordsScale);
    
    beginEditCP(_positionsScale);
    _positionsScale->clear();
    _positionsScale->addValue(Pnt3f(-1, -1, -0.5));
    _positionsScale->addValue(Pnt3f( 1, -1, -0.5));
    _positionsScale->addValue(Pnt3f( 1,  1, -0.5));
    _positionsScale->addValue(Pnt3f(-1,  1, -0.5));
    endEditCP(_positionsScale);

}

void DisplayCalibration::updateGamma()
{
    UInt16 x,y;
    UInt8 *data;
    UInt32 res = getGammaRamp().size();

    if(res == 0)
        res = 256;

    if(_useFragmentProgram)
    {
        beginEditCP(_fragProgram, FragmentProgramChunk::ParamValuesFieldMask);

        _fragProgram->setParameter(5, Vec4f(getGamma(),getGamma(),getGamma(),0));   

        endEditCP(_fragProgram, FragmentProgramChunk::ParamValuesFieldMask);
    }
    else
    {
        _argammaimg->set(GL_RGB,res,res);

        beginEditCP(_argammaimg);
        data = _argammaimg->getData();
    
        memset(data, 0, res * res * 3);
    
        for(y = 0; y < res; ++y)
        {
            UInt8 v = (int)(pow(y/(Real32)(res-1),getGamma())*255+0.5);
            for(x = 0; x < res; ++x)
            {
                *data++ = v;
                *data++ = 0;
                *data++ = 0;           
            }
        }
        endEditCP(_argammaimg);

        beginEditCP(_argammachunk);
        _argammachunk->setImage(_argammaimg);
        endEditCP(_argammachunk);

        _gbgammaimg->set(GL_RGB,res,res);

        beginEditCP(_gbgammaimg);
        data = _gbgammaimg->getData();
    
        memset(data, 0, res * res * 3);
    
        for(y = 0; y < res; ++y)
        {
            UInt8 vy = (int)(pow(y/(Real32)(res-1),getGamma())*255+0.5);
            for(x = 0; x < res; ++x)
            {
                UInt8 vx = (int)(pow(x/(Real32)(res-1),getGamma())*255+0.5);
                *data++ = 0;
                *data++ = vx;
                *data++ = vy;           
            }
        }
        endEditCP(_gbgammaimg);

        beginEditCP(_gbgammachunk);
        _gbgammachunk->setImage(_gbgammaimg);
        endEditCP(_gbgammachunk);
    }
}

void DisplayCalibration::updateMatrix()
{
    if(_useFragmentProgram)
    {
        beginEditCP(_fragProgram, FragmentProgramChunk::ParamValuesFieldMask);
    
        _fragProgram->setParameter(1, getColorMatrix()[0]);
        _fragProgram->setParameter(2, getColorMatrix()[1]);
        _fragProgram->setParameter(3, getColorMatrix()[2]);
        _fragProgram->setParameter(4, getColorMatrix()[3]);
    
        endEditCP(_fragProgram, FragmentProgramChunk::ParamValuesFieldMask);

    }
    else
    {
#if 0
        Color4f 
            m1(m[0][0]/2+.5,m[0][1]/2+.5,m[0][2]/2+.5,0),
            m2(m[1][0]/2+.5,m[1][1]/2+.5,m[1][2]/2+.5,0),
            m3(m[2][0]/2+.5,m[2][1]/2+.5,m[2][2]/2+.5,0),
            m4(m[3][0]/2+.5,m[3][1]/2+.5,m[3][2]/2+.5,0);
#endif
        Color4f 
            m1(getColorMatrix()[0][0]/2+.5,
            getColorMatrix()[0][1]/2+.5,
            getColorMatrix()[0][2]/2+.5,0),
            m2(getColorMatrix()[1][0]/2+.5,
            getColorMatrix()[1][1]/2+.5,
            getColorMatrix()[1][2]/2+.5,0),
            m3(getColorMatrix()[2][0]/2+.5,
            getColorMatrix()[2][1]/2+.5,
            getColorMatrix()[2][2]/2+.5,0),
            m4(getColorMatrix()[3][0]/2+.5,
            getColorMatrix()[3][1]/2+.5,
            getColorMatrix()[3][2]/2+.5,0);
    
        Color4f selectR(1,0,0,0), selectG(0,1,0,0), selectB(0,0,1,0);

        UInt16 ncomb = 0;
    
        beginEditCP(_regCombiner);

        _regCombiner->setCombinerRGB(ncomb,
                            GL_TEXTURE1_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
                            GL_ZERO,               GL_UNSIGNED_INVERT_NV,   GL_RGB, // variable B
                            GL_TEXTURE2_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
                            GL_ZERO,               GL_UNSIGNED_INVERT_NV,   GL_RGB, // variable D
                            GL_DISCARD_NV, GL_DISCARD_NV, GL_TEXTURE0_ARB,   // ABout, CDout, Sumout
                            GL_NONE, GL_NONE,                            // scale, bias
                            GL_FALSE, GL_FALSE, GL_FALSE );                // ABdot, CDdot, muxSum

        ncomb++;

        // first combiner: spare0 = dot(col, m1), spare1 = dot(col,m2)      
        
        _regCombiner->setCombinerColors(ncomb, m1, m2);

        _regCombiner->setCombinerRGB(
            ncomb,
            GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
            GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
            GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
            GL_CONSTANT_COLOR1_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable D
            GL_SPARE0_NV, GL_SPARE1_NV, GL_DISCARD_NV,   // ABout, CDout, Sumout
            GL_NONE, GL_NONE,                            // scale, bias
            GL_TRUE, GL_TRUE, GL_FALSE );                // ABdot, CDdot, muxSum
        
        ncomb++;
    
        // second combiner: tex0 = dot(col, m3), spare0 = spare0.r   
    
        _regCombiner->setCombinerColors(ncomb, m3, selectR);

        _regCombiner->setCombinerRGB(ncomb,
                            GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
                            GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
                            GL_SPARE0_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
                            GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
                            GL_TEXTURE3_ARB, GL_SPARE0_NV, GL_DISCARD_NV, // ABout, CDout, Sumout
                            GL_NONE, GL_NONE,                             // scale, bias
                            GL_TRUE, GL_FALSE, GL_FALSE );                 // ABdot, CDdot, muxSum

        ncomb++;
    
        // final combiner 
    
        _regCombiner->setColor0(selectG);
        _regCombiner->setColor1(selectB);
    
        // RGB = D + AB + (1-A)C
        _regCombiner->setFinalCombiner( 
            GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
            GL_SPARE1_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable B
            GL_E_TIMES_F_NV,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
            GL_SPARE0_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
            GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable E
            GL_TEXTURE3_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable F
            GL_PRIMARY_COLOR_NV,   GL_UNSIGNED_IDENTITY_NV, GL_ALPHA );// variable G

        endEditCP(_regCombiner);
    }
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGDISPLAYCALIBRATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISPLAYCALIBRATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISPLAYCALIBRATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

