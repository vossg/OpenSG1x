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
 *                                                                           *
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

#include "OSGConfig.h"

#include <OSGGL.h>

#include "OSGLog.h"

#include "OSGFieldContainerPtr.h"
#include "OSGGeometry.h"
#include "OSGDrawAction.h"

#include "OSGMaterial.h"

#include "OSGGeoPumpFactory.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*

The PumpFactory is responsible for selecting the most appropriate pump
function to send the geometry's data to OpenGL.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char GeoPumpFactory::cvsid[] = "@(#)$Id: $";

GeoPumpFactory *GeoPumpFactory::_the = NULL;

InitFuncWrapper
GeoPumpFactory::_glextInitFuncWrapper(GeoPumpFactory::glextInitFunction);

UInt32 GeoPumpFactory::_extSecondaryColor;
UInt32 GeoPumpFactory::_extMultitexture;
   
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

GeoPumpFactory::GeoPumpFactory(void)
{
}

/** \brief Destructor
 */

GeoPumpFactory::~GeoPumpFactory(void)
{
}

/*------------------------------ access -----------------------------------*/


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/


GeoPumpFactory::Index GeoPumpFactory::getIndex( Geometry * )
{
    return 0;
}
    

GeoPumpFactory::GeoPump GeoPumpFactory::getGeoPump( 
                Window * , 
                GeoPumpFactory::Index  )
{
    return &masterGeoPump;
}

GeoPumpFactory::PartialGeoPump GeoPumpFactory::getPartialGeoPump( 
                Window * , 
                GeoPumpFactory::Index  )
{
    FWARNING(("GeoPumpFactory::getPartialGeoPump: not implemented yet!\n"));
    return NULL;
}

GeoPumpFactory::InterfacePump GeoPumpFactory::getInterfacePump( 
                Window * , 
                GeoPumpFactory::Index  )
{
    FWARNING(("GeoPumpFactory::getInterfacePump: not implemented yet!\n"));
    return NULL;
}

GeoPumpFactory::PartialInterfacePump GeoPumpFactory::getPartialInterfacePump( 
                Window * , 
                GeoPumpFactory::Index  )
{
    FWARNING(("GeoPumpFactory::getPartialInterfacePump: not "
                "implemented yet!\n"));
    return NULL;
}


/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

    
GeoPumpFactory::Index GeoPumpFactory::numIndices( void )
{
    return 1;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

// a little hack to get around ifdefs

#ifndef GL_TEXTURE1_ARB

#define GL_TEXTURE1_ARB 0x84C1
#define GL_TEXTURE2_ARB 0x84C2
#define GL_TEXTURE3_ARB 0x84C3

#endif

// Pumping function definitions

typedef void (OSG_APIENTRY *pumpFunc)(GLubyte * data);
typedef void (OSG_APIENTRY *multiPumpFunc)(GLenum which, GLubyte * data);

// Some helper arrays for function selection
// indexed by data type and dimension

static const int formatBase = GL_BYTE;
static const int numFormats = GL_DOUBLE - GL_BYTE + 1;

static char *formatNames[] = 
{   "GL_BYTE", "GL_UNSIGNED_BYTE", "GL_SHORT", "GL_UNSIGNED_SHORT", 
    "GL_INT", "GL_UNSIGNED_INT", "GL_FLOAT", "GL_2_BYTES", 
    "GL_3_BYTES", "GL_4_BYTES", "GL_DOUBLE"
};

// little helper class for function init

class glextFuncInit
{
    public:

        glextFuncInit(char *name, UInt32 format, UInt32 dim) : 
            _name(name), _format(format), _dim(dim) {};

        void init(UInt32 (&extids)[numFormats][4])
        {
            extids[_format - formatBase][_dim] = 
                                        Window::registerFunction(_name);
        }

    private:

        char   *_name;
        UInt32  _format;
        UInt32  _dim;
};

glextFuncInit secondaryColorInitFuncs[8] = {
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3bvEXT",  
                  GL_BYTE, 
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3ubvEXT", 
                  GL_UNSIGNED_BYTE,  
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3svEXT",  
                  GL_SHORT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3usvEXT", 
                  GL_UNSIGNED_SHORT, 
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3ivEXT",  
                  GL_INT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3uivEXT", 
                  GL_UNSIGNED_INT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3fvEXT",  
                  GL_FLOAT,      
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glSecondaryColor3dvEXT",  
                  GL_DOUBLE,
                  3)
};

glextFuncInit multiTexCoordsInitFuncs[16] = {
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1svARB",
                  GL_SHORT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2svARB",
                  GL_SHORT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3svARB",
                  GL_SHORT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4svARB",
                  GL_SHORT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1ivARB",
                  GL_INT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2ivARB",
                  GL_INT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3ivARB",
                  GL_INT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4ivARB",
                  GL_INT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1fvARB",
                  GL_FLOAT,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2fvARB",
                  GL_FLOAT,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3fvARB",
                  GL_FLOAT,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4fvARB",
                  GL_FLOAT,
                  4),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord1dvARB",
                  GL_DOUBLE,
                  1),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2dvARB",
                  GL_DOUBLE,
                  2),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3dvARB",
                  GL_DOUBLE,
                  3),
    glextFuncInit(OSG_DLSYM_UNDERSCORE"glMultiTexCoord4dvARB",   
                  GL_DOUBLE,
                  4)
};

// The real pumping functions

static pumpFunc PositionFuncs[numFormats][4] = {
    { NULL, NULL, NULL, NULL },                           // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { NULL, (pumpFunc)glVertex2sv, 
      (pumpFunc)glVertex3sv, (pumpFunc)glVertex4sv },     // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { NULL, (pumpFunc)glVertex2iv, 
      (pumpFunc)glVertex3iv, (pumpFunc)glVertex4iv },     // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { NULL, (pumpFunc)glVertex2fv,
      (pumpFunc)glVertex3fv, (pumpFunc)glVertex4fv },     // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, (pumpFunc)glVertex2dv, 
      (pumpFunc)glVertex3dv, (pumpFunc)glVertex4dv },     // GL_DOUBLE
};

static pumpFunc NormalFuncs[numFormats][4] = {
    { NULL, NULL, (pumpFunc)glNormal3sv, NULL },          // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { NULL, NULL, (pumpFunc)glNormal3sv, NULL },          // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { NULL, NULL, (pumpFunc)glNormal3iv, NULL },          // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { NULL, NULL, (pumpFunc)glNormal3fv, NULL },          // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, NULL, (pumpFunc)glNormal3dv, NULL },          // GL_DOUBLE
};

static pumpFunc ColorFuncs[numFormats][4] = {
    { NULL, NULL, 
      (pumpFunc)glColor3bv, (pumpFunc)glColor4bv },       // GL_BYTE
    { NULL, NULL, 
      (pumpFunc)glColor3ubv, (pumpFunc)glColor4ubv },     // GL_UNSIGNED_BYTE
    { NULL, NULL, 
      (pumpFunc)glColor3sv, (pumpFunc)glColor4sv },       // GL_SHORT
    { NULL, NULL,  
      (pumpFunc)glColor3usv, (pumpFunc)glColor4usv },     // GL_UNSIGNED_SHORT
    { NULL, NULL,  
      (pumpFunc)glColor3iv, (pumpFunc)glColor4iv },       // GL_INT
    { NULL, NULL,  
      (pumpFunc)glColor3uiv, (pumpFunc)glColor4uiv },     // GL_UNSIGNED_INT
    { NULL, NULL,  
      (pumpFunc)glColor3fv, (pumpFunc)glColor4fv },       // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { NULL, NULL,   
      (pumpFunc)glColor3dv, (pumpFunc)glColor4dv },       // GL_DOUBLE
};

static UInt32 SecColorIDs[numFormats][4];

static pumpFunc TexCoordsFuncs[numFormats][4] = {
    { NULL, NULL, NULL, NULL },                           // GL_BYTE
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_BYTE
    { (pumpFunc)glTexCoord1sv, (pumpFunc)glTexCoord2sv, 
      (pumpFunc)glTexCoord3sv, (pumpFunc)glTexCoord4sv }, // GL_SHORT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_SHORT
    { (pumpFunc)glTexCoord1iv, (pumpFunc)glTexCoord2iv, 
      (pumpFunc)glTexCoord3iv, (pumpFunc)glTexCoord4iv }, // GL_INT
    { NULL, NULL, NULL, NULL },                           // GL_UNSIGNED_INT
    { (pumpFunc)glTexCoord1fv, (pumpFunc)glTexCoord2fv, 
      (pumpFunc)glTexCoord3fv, (pumpFunc)glTexCoord4fv }, // GL_FLOAT
    { NULL, NULL, NULL, NULL },                           // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                           // GL_4_BYTES
    { (pumpFunc)glTexCoord1dv, (pumpFunc)glTexCoord2dv, 
      (pumpFunc)glTexCoord3dv, (pumpFunc)glTexCoord4dv }, // GL_DOUBLE
};

static UInt32 TexCoords1IDs[numFormats][4];

#define TexCoords2IDs TexCoords1IDs
#define TexCoords3IDs TexCoords1IDs

// The master pump. Can render everything, but takes ages to do so.
// A real fallback, when everything else fails.
// Its second function is the example of how things are supposed to work.
// If an optimized pump creates a different result, it's wrong.
// The formal specification is defined in the design document though.

// some little helper macros to make the code more readable

// define and initialize the variables needed to access the data

#define pumpInternalSetup( name, typename, getmethod, mandatory )           \
    GLubyte * name##Data;                                                   \
    UInt32 name##Stride;                                                    \
    UInt32 name##Ind = 0;                                                   \
    typename name##Ptr;                                                     \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if(mandatory && name##Ptr == NullFC)                                    \
    {                                                                       \
        SWARNING << "masterPump: Geometry " << geo << " has no "            \
                 << #name << "s!" << endl;                                  \
        return;                                                             \
    }                                                                       \
    else if(name##Ptr != NullFC)                                            \
    {                                                                       \
        name##Data = name##Ptr->getData();                                  \
        if(!(name##Stride = name##Ptr->getStride()))                        \
            name##Stride =  name##Ptr->getFormatSize() *                    \
                            name##Ptr->getDimension();                      \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Stride = 0;                                                   \
    }

#define pumpGLSetup( name, typename, getmethod )                            \
    GLubyte * name##Data;                                                   \
    UInt32 name##Stride;                                                    \
    UInt32 name##Ind = 0;                                                   \
    typename name##Ptr;                                                     \
    pumpFunc name##Func;                                                    \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if(name##Ptr != NullFC)                                                 \
    {                                                                       \
        name##Data = name##Ptr->getData();                                  \
        if(!(name##Stride = name##Ptr->getStride()))                        \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
        if(!(name##Func = name##Funcs[name##Ptr->getFormat() -              \
                                            formatBase]                     \
                                     [name##Ptr->getDimension() - 1]        \
          ) )                                                               \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " has illegal "   \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << "!" << endl;                                        \
            return;                                                         \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Func = NULL;                                                  \
        name##Stride = 0;                                                   \
    }

#define pumpGLExtSetup( name, typename, getmethod )                         \
    GLubyte * name##Data;                                                   \
    UInt32 name##Stride;                                                    \
    UInt32 name##Ind = 0;                                                   \
    typename name##Ptr;                                                     \
    pumpFunc name##Func;                                                    \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if(name##Ptr != NullFC)                                                 \
    {                                                                       \
        name##Data = name##Ptr->getData();                                  \
        if(!(name##Stride = name##Ptr->getStride()))                        \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
        if(name##IDs[name##Ptr->getFormat() - formatBase]                   \
                    [name##Ptr->getDimension() - 1] ==                      \
                    Window::invalidFunctionID)                              \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " has illegal "   \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << "!" << endl;                                        \
            return;                                                         \
        }                                                                   \
        if(!(name##Func = (pumpFunc)win->getFunction(name##IDs              \
                                     [name##Ptr->getFormat() - formatBase]  \
                                     [name##Ptr->getDimension() - 1])       \
          ) )                                                               \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << " uses "          \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << " which are not supported by Window " << win        \
                     <<  "!" << endl;                                       \
            return;                                                         \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Func = NULL;                                                  \
        name##Stride = 0;                                                   \
    }

#define pumpMultiGLExtSetup(name, typename, getmethod)                      \
    GLubyte * name##Data;                                                   \
    UInt32 name##Stride;                                                    \
    UInt32 name##Ind = 0;                                                   \
    typename name##Ptr;                                                     \
    multiPumpFunc name##Func;                                               \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if(name##Ptr != NullFC)                                                 \
    {                                                                       \
        name##Data = name##Ptr->getData();                                  \
        if(!(name##Stride = name##Ptr->getStride() ) )                      \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
        if(name##IDs[name##Ptr->getFormat() - formatBase]                   \
                    [name##Ptr->getDimension() - 1] ==                      \
                    Window::invalidFunctionID)                              \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << "has illegal "    \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << "!" << endl;                                        \
            return;                                                         \
        }                                                                   \
        if(!(name##Func = (multiPumpFunc)win->getFunction(name##IDs         \
                                     [name##Ptr->getFormat() - formatBase]  \
                                     [name##Ptr->getDimension() - 1])       \
          ) )                                                               \
        {                                                                   \
            SWARNING << "masterPump: Geometry " << geo << "uses "           \
                     << #name << "s: " << name##Ptr->getDimension()         \
                     << "D " << formatNames[ name##Ptr->getFormat() -       \
                                            formatBase ]                    \
                     << "which are not supported by Window " << win         \
                     <<  "!" << endl;                                       \
            return;                                                         \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Func = NULL;                                                  \
        name##Stride = 0;                                                   \
    }

// the master pump function

#ifdef __sgi
#pragma set woff 1174,1209
#endif

void GeoPumpFactory::masterGeoPump(Window   *win, 
                                   Geometry *geo)
{
    // Setup: get all the data
    
    pumpInternalSetup( Type, GeoPTypesPtr, getTypes, true );
    pumpInternalSetup( Length, GeoPLengthsPtr, getLengths, false );
    pumpInternalSetup( Index, GeoIndicesPtr, getIndices, false );

    pumpGLSetup        ( Position,   GeoPositionsPtr, getPositions      );
    pumpGLSetup        ( Color,      GeoColorsPtr,    getColors         );
    pumpGLExtSetup     ( SecColor,   GeoColorsPtr,    getSecondaryColors);
    pumpGLSetup        ( Normal,     GeoNormalsPtr,   getNormals        );
    pumpGLSetup        ( TexCoords,  GeoTexCoordsPtr, getTexCoords      );
    pumpMultiGLExtSetup( TexCoords1, GeoTexCoordsPtr, getTexCoords1     );
    pumpMultiGLExtSetup( TexCoords2, GeoTexCoordsPtr, getTexCoords2     );
    pumpMultiGLExtSetup( TexCoords3, GeoTexCoordsPtr, getTexCoords3     );
  
    // check if the node is empty
    if(! TypeData || TypePtr->getSize() == 0)
        return;
    
    // if it's not empty we need positions
    if(! PositionData)
    {
        SWARNING << "masterPump: Geometry " << geo << " has no positions!?!"
                 << endl;
        return;
    }
    
    // find the mapping indices
    UInt16 nmappings = geo->getIndexMapping().size();
    Int16 PositionIndex   = -1, 
          NormalIndex     = -1, 
          ColorIndex      = -1, 
          SecColorIndex   = -1, 
          TexCoordsIndex  = -1,
          TexCoords1Index = -1,
          TexCoords2Index = -1,
          TexCoords3Index = -1;

    if(nmappings)
    {
        PositionIndex   = geo->calcMappingIndex(Geometry::MapPosition      );
        NormalIndex     = geo->calcMappingIndex(Geometry::MapNormal        );
        ColorIndex      = geo->calcMappingIndex(Geometry::MapColor         );
        SecColorIndex   = geo->calcMappingIndex(Geometry::MapSecondaryColor);
        TexCoordsIndex  = geo->calcMappingIndex(Geometry::MapTexCoords     );
        TexCoords1Index = geo->calcMappingIndex(Geometry::MapTexCoords1    );
        TexCoords2Index = geo->calcMappingIndex(Geometry::MapTexCoords2    );
        TexCoords3Index = geo->calcMappingIndex(Geometry::MapTexCoords3    );
        
        if(! PositionData)
        {
            SWARNING << "masterPump: Geometry " << geo << "has no position index!?!"
                     << endl;
            return;
        }
        
    }
    else if(IndexData)
    {
        nmappings = 1;
        PositionIndex = 
        NormalIndex =
        ColorIndex =
        SecColorIndex =
        TexCoordsIndex = 
        TexCoords1Index = 
        TexCoords2Index = 
        TexCoords3Index = 0;
    }
    
    // overall color?
    if(ColorData && ColorPtr->getSize() == 1)
        ColorFunc(ColorData);

    // Length handling. Special case: no length given
    
    UInt32 lendummy;
    UInt32 LengthSize;

    // no lengths? use all available data for the first type
    if(! LengthData)
    {
        LengthSize = 1;
        LengthData = (UChar8*) &lendummy;
        if(IndexData)
        {
            lendummy = IndexPtr->getSize() / nmappings;
        }
        else
        {
            lendummy = PositionPtr->getSize();
        }
    }
    else
    {
        LengthSize = LengthPtr->getSize();
    }

    for(LengthInd = 0; LengthInd < LengthSize; LengthInd++)
    {
        glBegin(*(TypeData + TypeInd++ * TypeStride));
        
        for(UInt32 l = *(UInt32*)(LengthData + LengthInd * LengthStride); 
                       l > 0; l--)
        {
            if(IndexData)
            {
                UInt32 * vind;
            
                vind = (UInt32*)(IndexData + IndexStride * IndexInd);
                IndexInd += nmappings;
                
                if(ColorData && ColorIndex >= 0)
                {
                    ColorFunc(ColorData + ColorStride * vind[ColorIndex]);
                }       
                
                if(SecColorData && SecColorIndex >= 0)
                {
                    SecColorFunc(SecColorData + SecColorStride * 
                                    vind[SecColorIndex]);
                }       
                
                if(NormalData && NormalIndex >= 0)
                {
                    NormalFunc(NormalData + NormalStride * vind[NormalIndex]);
                }       
                
                if(TexCoordsData && TexCoordsIndex >= 0)
                {
                    TexCoordsFunc(TexCoordsData + TexCoordsStride * 
                                    vind[TexCoordsIndex]);
                }       

                if(TexCoords1Data && TexCoords1Index >= 0)
                {
                    TexCoords1Func(GL_TEXTURE1_ARB,
                                     TexCoords1Data + TexCoords1Stride *
                                     vind[TexCoords1Index]);
                }       
                
                if(TexCoords2Data && TexCoords2Index >= 0)
                {
                    TexCoords2Func(GL_TEXTURE2_ARB,
                                     TexCoords2Data + TexCoords2Stride *
                                     vind[TexCoords2Index]);
                }       
                
                if(TexCoords3Data && TexCoords3Index >= 0)
                {
                    TexCoords3Func(GL_TEXTURE3_ARB,
                                     TexCoords3Data + TexCoords3Stride *
                                     vind[TexCoords3Index]);
                }       
                    
                PositionFunc(PositionData + PositionStride * vind[PositionIndex]);
            }
            else
            {   
                if(ColorData)
                {
                    ColorFunc(ColorData + ColorStride * PositionInd);
                }       

                if(SecColorData)
                {
                    SecColorFunc(SecColorData + SecColorStride * PositionInd);
                }       
               
                if(NormalData)
                {
                    NormalFunc(NormalData + NormalStride * PositionInd);
                }       
                
                if(TexCoordsData)
                {
                    TexCoordsFunc(TexCoordsData + TexCoordsStride * 
                                                    PositionInd);
                }       
                
                if(TexCoords1Data)
                {
                    TexCoords1Func(GL_TEXTURE1_ARB,
                                   TexCoords1Data + TexCoords1Stride * 
                                                    PositionInd);
                }       
                
                if(TexCoords2Data)
                {
                    TexCoords2Func(GL_TEXTURE2_ARB,
                                   TexCoords2Data + TexCoords2Stride * 
                                                    PositionInd);
                }       
                
                if(TexCoords3Data)
                {
                    TexCoords3Func(GL_TEXTURE3_ARB,
                                   TexCoords3Data + TexCoords3Stride * 
                                                    PositionInd);
                }       
                    
                PositionFunc(PositionData + PositionStride * PositionInd);
                
                PositionInd++;
            }
        }
        
        glEnd();
    }
}

        
void GeoPumpFactory::masterPartialGeoPump(Window   *OSG_CHECK_ARG(win     ), 
                                          Geometry *OSG_CHECK_ARG(geo      ),
                                          UInt32    OSG_CHECK_ARG(primtype ), 
                                          UInt32    OSG_CHECK_ARG(firstvert), 
                                          UInt32    OSG_CHECK_ARG(nvert    ))
{
    FWARNING(("GeoPumpFactory::masterPartialGeoPump: not implemented yet!\n"));
}
    
void GeoPumpFactory::masterInterfacePump(
    Window                *OSG_CHECK_ARG(win       ), 
    GeoPositionsInterface *OSG_CHECK_ARG(pos       ), 
    GeoNormalsInterface   *OSG_CHECK_ARG(norm      ),
    GeoColorsInterface    *OSG_CHECK_ARG(col       ), 
    GeoColorsInterface    *OSG_CHECK_ARG(seccol    ), 
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords ),
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords1),
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords2),
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords3),
    GeoPTypesInterface    *OSG_CHECK_ARG(type      ), 
    GeoPLengthsInterface  *OSG_CHECK_ARG(len       ),
    GeoIndicesInterface   *OSG_CHECK_ARG(ind       ), 
    UInt16                *OSG_CHECK_ARG(pMap      ),
    UInt16                 OSG_CHECK_ARG(nmap      ))
{
    FWARNING(("GeoPumpFactory::masterInterfacePump: not implemented yet!\n"));
}
    
void GeoPumpFactory::masterPartialInterfacePump( 
    Window                *OSG_CHECK_ARG(win       ), 
    GeoPositionsInterface *OSG_CHECK_ARG(pos       ), 
    GeoNormalsInterface   *OSG_CHECK_ARG(norm      ),
    GeoColorsInterface    *OSG_CHECK_ARG(col       ), 
    GeoColorsInterface    *OSG_CHECK_ARG(seccol    ), 
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords ),
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords1),
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords2),
    GeoTexCoordsInterface *OSG_CHECK_ARG(texcoords3),
    GeoPTypesInterface    *OSG_CHECK_ARG(type      ), 
    GeoPLengthsInterface  *OSG_CHECK_ARG(len       ),
    GeoIndicesInterface   *OSG_CHECK_ARG(ind       ), 
    UInt16                *OSG_CHECK_ARG(pMap      ), 
    UInt16                 OSG_CHECK_ARG(nmap      ),
    UInt32                 OSG_CHECK_ARG(primtype  ), 
    UInt32                 OSG_CHECK_ARG(firstvert ), 
    UInt32                 OSG_CHECK_ARG(nvert     ))
{
    FWARNING(
        ("GeoPumpFactory::masterPartialInterfacePump not implemented yet!\n"));
}

#ifdef __sgi
#pragma reset woff 1174,1209
#endif

bool GeoPumpFactory::glextInitFunction(void)
{
    _extSecondaryColor = Window::registerExtension("GL_EXT_secondary_color");
    _extMultitexture   = Window::registerExtension("GL_ARB_multitexture");
    
    UInt16 i,j;
    for(i = 0; i < numFormats; i++)
    {
        for(j = 0; j < 4; j++)
        {
            SecColorIDs  [i][j] = Window::invalidFunctionID;
            TexCoords1IDs[i][j] = Window::invalidFunctionID;
        }
    }

    for(i = 0; i < 8; i++)
        secondaryColorInitFuncs[i].init(SecColorIDs);

    for(i = 0; i < 16; i++)
        multiTexCoordsInitFuncs[i].init(TexCoords1IDs);
    
    return true;
}

