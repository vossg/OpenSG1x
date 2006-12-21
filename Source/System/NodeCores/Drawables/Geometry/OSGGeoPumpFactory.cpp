/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include <stddef.h>

#include "OSGConfig.h"

#include <OSGGL.h>
#include <OSGGLEXT.h>

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

/* \class osg::GeoPumpFactory
   \ingroup GrpSystemNodeCoresDrawablesGeometry
    
The PumpFactory is responsible for selecting the most appropriate pump
function to send the geometry's data to OpenGL in the most efficient manner.

The pump is selected inside the rendering function and should not be accessed
from the outside.

\dev The pump factory chooses the pump based on the used properties. For
non- and single-indexed geometry OpenGL VertexArrays are used, for
multi-indexed geometry an immediate mode pump has to be used. Specialized Pumps
for all combinations of properties are created to optimizie this case as much
as possible.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! The Singleton instance of the GeoPumpFactory.
*/
GeoPumpFactory *GeoPumpFactory::_the = NULL;

/*! An InitFuncWrapper to initialize the GeoPumpFactory.
*/
InitFuncWrapper
GeoPumpFactory::_glextInitFuncWrapper(GeoPumpFactory::glextInitFunction);

/*! OpenGL extension indices.
*/
UInt32 GeoPumpFactory::_extSecondaryColor;
UInt32 GeoPumpFactory::_extMultitexture;
UInt32 GeoPumpFactory::_extCompiledVertexArray;
UInt32 GeoPumpFactory::_extDrawRangeElements;
UInt32 GeoPumpFactory::_arbVBO;

/*! OpenGL extension function indices.
*/
UInt32 GeoPumpFactory::_funcglSecondaryColorPointer;
UInt32 GeoPumpFactory::_funcglClientActiveTextureARB;
UInt32 GeoPumpFactory::_funcglLockArraysEXT;
UInt32 GeoPumpFactory::_funcglUnlockArraysEXT;
UInt32 GeoPumpFactory::_funcglDrawRangeElementsEXT;

UInt32 GeoPumpFactory::_funcglGenBuffers;
UInt32 GeoPumpFactory::_funcglDeleteBuffers;
UInt32 GeoPumpFactory::_funcglBindBuffer;
UInt32 GeoPumpFactory::_funcglBufferData;
UInt32 GeoPumpFactory::_funcglBufferSubData;

UInt32 GeoPumpFactory::_funcglGenBuffersARB;
UInt32 GeoPumpFactory::_funcglDeleteBuffersARB;
UInt32 GeoPumpFactory::_funcglBindBufferARB;
UInt32 GeoPumpFactory::_funcglBufferDataARB;
UInt32 GeoPumpFactory::_funcglBufferSubDataARB;


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

GeoPumpFactory::GeoPumpFactory(void)
{
}

GeoPumpFactory::~GeoPumpFactory(void)
{
}

/*-------------------------- your_category---------------------------------*/

/*! Access the index of the given Geometry. Needed to access the Pump.

\dev The index is organised as follows:
-  there are 2^7-1+3 different functions
-  the first (0) is for invalid (empty) geometry
-  the next 127 define all multi-indexed functions
-  the last 2 define non-indexed and single-indexed geometries
\enddev
*/
GeoPumpFactory::Index GeoPumpFactory::getIndex(Geometry * geo)
{
    if (geo->getPositions() == NullFC ||
       !geo->getPositions()->getData() ) return 0; //INVALID

    if (geo->getTypes() == NullFC || !geo->getTypes()->getData() ||
        geo->getTypes()->getSize() == 0) return 0; //INVALID

    if (geo->getIndices() == NullFC) return 128; //NON_INDEXED
    if (geo->getIndexMapping().size() < 2) return 129; //SINGLE_INDEXED

    if ((geo->getIndices() != NullFC && 
         geo->getIndices()->getFormatSize() != 4) ||
        (geo->getLengths() != NullFC && 
         geo->getLengths()->getFormatSize() != 4)
        )
        return 130; // Needd to use the master pump
    
    UInt32 uiIndexMask = 0;

    for(UInt32 i = 0; i < geo->getIndexMapping().size(); ++i)
    {
        uiIndexMask |= geo->getIndexMapping()[i];
    }

    // ok the multi index table supports only 4 texcoord units!
    if((uiIndexMask & Geometry::MapTexCoords4 &&
       geo->getTexCoords4() != NullFC         &&
       geo->getTexCoords4()->getData()          ) ||
       (uiIndexMask & Geometry::MapTexCoords5 &&
       geo->getTexCoords5() != NullFC         &&
       geo->getTexCoords5()->getData()          ) ||
       (uiIndexMask & Geometry::MapTexCoords6 &&
       geo->getTexCoords6() != NullFC         &&
       geo->getTexCoords6()->getData()          ) ||
       (uiIndexMask & Geometry::MapTexCoords7 &&
       geo->getTexCoords7() != NullFC         &&
       geo->getTexCoords7()->getData()          ))
    {
        return 130; // Needd to use the master pump
    }

    int a[7];

    if(uiIndexMask & Geometry::MapColor &&
       geo->getColors() != NullFC       &&
       geo->getColors()->getData()        ) 
    {
        a[0]=1;
    } 
    else 
    {
        a[0] = 0;
    }
    
    if(uiIndexMask & Geometry::MapSecondaryColor &&
       geo->getSecondaryColors() != NullFC       &&
       geo->getSecondaryColors()->getData()       ) 
    {
        a[1]=1;
    }
    else 
    {
        a[1]=0;
    }

    if(uiIndexMask & Geometry::MapNormal &&
       geo->getNormals() != NullFC       &&
       geo->getNormals()->getData()        ) 
    {
        a[2]=1;
    }
    else
    {
        a[2]=0;
    }

    if(uiIndexMask & Geometry::MapTexCoords &&
       geo->getTexCoords() != NullFC        &&
       geo->getTexCoords()->getData()        ) 
    {
        a[3]=1; 
    }
    else
    {
        a[3]=0;
    }

    if(uiIndexMask & Geometry::MapTexCoords1 &&
       geo->getTexCoords1() != NullFC        &&
       geo->getTexCoords1()->getData()        ) 
    {
        a[4]=1; 
    }
    else
    {
        a[4]=0;
    }

    if(uiIndexMask & Geometry::MapTexCoords2 &&
       geo->getTexCoords2() != NullFC        &&
       geo->getTexCoords2()->getData()        ) 
    {
        a[5]=1;
    }
    else 
    {
        a[5]=0;
    }

    if(uiIndexMask & Geometry::MapTexCoords3 &&
       geo->getTexCoords3() != NullFC        &&
       geo->getTexCoords3()->getData()        ) 
    {
        a[6]=1;
    }
    else
    {
        a[6]=0;
    }

    int index=0;

    for (int i=0; i<7; i++)
        if (a[i]) index=index|(1<<i);

    /* if the geometry was detected as multi-indexed,but
       there was no index data, then index will be 0, which
       corresponds to invalid geometry.
     */

    return index;
}


/*! Get the full Geometry pump for the given \a index.
*/
GeoPumpFactory::GeoPump GeoPumpFactory::getGeoPump(
                Window * ,
                GeoPumpFactory::Index index )
{
    //FWARNING(("GeoPump%d used\n",index));
    return GeoPumps[index]; //crashed windows while testing, watch it.
    //return &masterGeoPump;
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

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


GeoPumpFactory::Index GeoPumpFactory::numIndices( void )
{
    return 131;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

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

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

class glextFuncInit
{
    public:

        glextFuncInit(char *name, UInt32 format, UInt32 dim) :
            _name(name), _format(format), _dim(dim) {};

        void init(UInt32 (&extids)[numFormats][4], UInt32 extension)
        {
            extids[_format - formatBase][_dim - 1] =
                              Window::registerFunction(_name, extension);
        }

    private:

        char   *_name;
        UInt32  _format;
        UInt32  _dim;
};

static glextFuncInit secondaryColorInitFuncs[8] = {
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

static glextFuncInit multiTexCoordsInitFuncs[16] = {
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
#define TexCoords4IDs TexCoords1IDs
#define TexCoords5IDs TexCoords1IDs
#define TexCoords6IDs TexCoords1IDs
#define TexCoords7IDs TexCoords1IDs

#endif      // remove from all but dev docs

/*! MasterPump for empty geometry, does nothing
*/

static
void GeoPump0(Window   *OSG_CHECK_ARG(win),
              Geometry *OSG_CHECK_ARG(geo))
{
    return;
}

#define pumpSetup( name, typename, getmethod )                              \
    typename name##Ptr;                                                     \
    GLubyte * name##Data = NULL;                                            \
    UInt32 name##Stride = 0;                                                \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if ( name##Ptr != NullFC )                                              \
    {                                                                       \
        name##Data = name##Ptr->getData();                                  \
        if ( ! ( name##Stride = name##Ptr->getStride() ) )                  \
            name##Stride = name##Ptr->getFormatSize() *                     \
            name##Ptr->getDimension();                                      \
    }

/*! MasterPump for non-indexed geometry
*/
static
void GeoPump128(Window   *win,
                Geometry *geo               )
{
    Int16 modified=0;
    pumpSetup(Positions  , GeoPositionsPtr , getPositions  );
    pumpSetup(Colors     , GeoColorsPtr    , getColors     );
    pumpSetup(SecColors  , GeoColorsPtr    , getSecondaryColors );
    pumpSetup(TexCoords  , GeoTexCoordsPtr , getTexCoords  );
    pumpSetup(TexCoords1 , GeoTexCoordsPtr , getTexCoords1 );
    pumpSetup(TexCoords2 , GeoTexCoordsPtr , getTexCoords2 );
    pumpSetup(TexCoords3 , GeoTexCoordsPtr , getTexCoords3 );
    pumpSetup(TexCoords4 , GeoTexCoordsPtr , getTexCoords4 );
    pumpSetup(TexCoords5 , GeoTexCoordsPtr , getTexCoords5 );
    pumpSetup(TexCoords6 , GeoTexCoordsPtr , getTexCoords6 );
    pumpSetup(TexCoords7 , GeoTexCoordsPtr , getTexCoords7 );
    pumpSetup(Normals    , GeoNormalsPtr   , getNormals    );

    pumpSetup(Lengths    , GeoPLengthsPtr  , getLengths    );
    pumpSetup(Types      , GeoPTypesPtr    , getTypes      );

    if (PositionsData)
    {        
        glVertexPointer(PositionsPtr->getDimension(), PositionsPtr->getFormat(),
                        PositionsStride, PositionsData);
        glEnableClientState(GL_VERTEX_ARRAY);
        modified|=(1<<0);
    }

    if (ColorsData)
    {
        glColorPointer(ColorsPtr->getDimension(), ColorsPtr->getFormat(),
                       ColorsStride, ColorsData);
        glEnableClientState(GL_COLOR_ARRAY);
        modified|=(1<<1);        
    }

    if (SecColorsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extSecondaryColor))
        {
             void (OSG_APIENTRY*_glSecondaryColorPointerEXT)
                  (GLint size,GLenum type,GLsizei stride,const GLvoid *pointer)=
            (void (OSG_APIENTRY*)(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer))
             win->getFunction(GeoPumpFactory::_funcglSecondaryColorPointer);

            _glSecondaryColorPointerEXT(SecColorsPtr->getDimension(),
                                       SecColorsPtr->getFormat(),
                                       SecColorsStride, SecColorsData);
            glEnableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
            modified|=(1<<2);
        }
        else
            FWARNING(("GeoPump128: Window has no Secondary Color extension\n"));
    }


    if (NormalsData)
    {
        glNormalPointer(NormalsPtr->getFormat(), NormalsStride, NormalsData);
        glEnableClientState(GL_NORMAL_ARRAY);
        modified|=(1<<3);
    }

    if (TexCoordsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        else
        {
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        modified|=(1<<4);
    }

    if (TexCoords1Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE1_ARB);
            glTexCoordPointer (TexCoords1Ptr->getDimension(), TexCoords1Ptr->getFormat(),
                               TexCoords1Stride, TexCoords1Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<5);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords2Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE2_ARB);
            glTexCoordPointer (TexCoords2Ptr->getDimension(), TexCoords2Ptr->getFormat(),
                               TexCoords2Stride, TexCoords2Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<6);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords3Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE3_ARB);
            glTexCoordPointer (TexCoords3Ptr->getDimension(), TexCoords3Ptr->getFormat(),
                               TexCoords3Stride, TexCoords3Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<7);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords4Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE4_ARB);
            glTexCoordPointer (TexCoords4Ptr->getDimension(), TexCoords4Ptr->getFormat(),
                               TexCoords4Stride, TexCoords4Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<8);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords5Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE5_ARB);
            glTexCoordPointer (TexCoords5Ptr->getDimension(), TexCoords5Ptr->getFormat(),
                               TexCoords5Stride, TexCoords5Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<9);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords6Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE6_ARB);
            glTexCoordPointer (TexCoords6Ptr->getDimension(), TexCoords6Ptr->getFormat(),
                               TexCoords6Stride, TexCoords6Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<10);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords7Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE7_ARB);
            glTexCoordPointer (TexCoords7Ptr->getDimension(), TexCoords7Ptr->getFormat(),
                               TexCoords7Stride, TexCoords7Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<11);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    UInt32 lendummy;
    UInt32 LengthsSize;
    UInt32 LengthsFormatSize;

    if(LengthsPtr != NullFC && LengthsData != NULL)
    {
        LengthsSize = LengthsPtr->getSize();
        LengthsFormatSize = LengthsPtr->getFormatSize();
    }
    else
    {
        LengthsSize = 1;
        LengthsFormatSize = 4;
        LengthsData = (UChar8*) &lendummy;
        lendummy = PositionsPtr->getSize();
    }

    UInt32 LengthsInd,TypesInd = 0;
    UInt32 first=0;

    if(LengthsFormatSize == 4)
    {
        for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
        {
            UInt32 count = *(UInt32*)(LengthsData + LengthsInd * LengthsStride);
            glDrawArrays(*(TypesData + TypesInd++ * TypesStride),first,count);
            first+=count;
        }
    }
    else if(LengthsFormatSize == 2)
    {
        for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
        {
            UInt16 count = *(UInt16*)(LengthsData + LengthsInd * LengthsStride);
            glDrawArrays(*(TypesData + TypesInd++ * TypesStride),first,count);
            first+=count;
        }       
    }
    else
    {
        FWARNING(("GeoPump128: unknown Lengths format size\n"));
    }
    
    if(modified&(1<<0)) glDisableClientState(GL_VERTEX_ARRAY);
    if(modified&(1<<1)) glDisableClientState(GL_COLOR_ARRAY);
    if(modified&(1<<2)) glDisableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
    if(modified&(1<<3)) glDisableClientState(GL_NORMAL_ARRAY);

    if (win->hasExtension(GeoPumpFactory::_extMultitexture))
    {
        void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
        (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);

        if(modified&(1<<4))
        {
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<5))
        {
            _glClientActiveTextureARB(GL_TEXTURE1_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<6))
        {
            _glClientActiveTextureARB(GL_TEXTURE2_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<7))
        {
            _glClientActiveTextureARB(GL_TEXTURE3_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<8))
        {
            _glClientActiveTextureARB(GL_TEXTURE4_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<9))
        {
            _glClientActiveTextureARB(GL_TEXTURE5_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<10))
        {
            _glClientActiveTextureARB(GL_TEXTURE6_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<11))
        {
            _glClientActiveTextureARB(GL_TEXTURE7_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
    else
    {
        if(modified&(1<<4)) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}

/*! MasterPump for single-indexed geometry
 */

static
void GeoPump129(Window   *win,
                Geometry *geo)
{
    Int16 modified=0;
    pumpSetup(Positions  , GeoPositionsPtr , getPositions );
    pumpSetup(Colors     , GeoColorsPtr    , getColors    );
    pumpSetup(SecColors  , GeoColorsPtr    , getSecondaryColors );
    pumpSetup(TexCoords  , GeoTexCoordsPtr , getTexCoords  );
    pumpSetup(TexCoords1 , GeoTexCoordsPtr , getTexCoords1 );
    pumpSetup(TexCoords2 , GeoTexCoordsPtr , getTexCoords2 );
    pumpSetup(TexCoords3 , GeoTexCoordsPtr , getTexCoords3 );
    pumpSetup(TexCoords4 , GeoTexCoordsPtr , getTexCoords4 );
    pumpSetup(TexCoords5 , GeoTexCoordsPtr , getTexCoords5 );
    pumpSetup(TexCoords6 , GeoTexCoordsPtr , getTexCoords6 );
    pumpSetup(TexCoords7 , GeoTexCoordsPtr , getTexCoords7 );
    pumpSetup(Normals    , GeoNormalsPtr   , getNormals    );

    pumpSetup(Lengths    , GeoPLengthsPtr  , getLengths    );
    pumpSetup(Types      , GeoPTypesPtr    , getTypes      );
    pumpSetup(Indices    , GeoIndicesPtr   , getIndices    );

    if (PositionsData)
    {        
        glVertexPointer(PositionsPtr->getDimension(), PositionsPtr->getFormat(),
                        PositionsStride, PositionsData);
        glEnableClientState(GL_VERTEX_ARRAY);
        modified|=(1<<0);
    }

    if (ColorsData)
    {
        glColorPointer(ColorsPtr->getDimension(), ColorsPtr->getFormat(),
                       ColorsStride, ColorsData);
        glEnableClientState(GL_COLOR_ARRAY);
        modified|=(1<<1);        
    }

    if (SecColorsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extSecondaryColor))
        {
             void (OSG_APIENTRY*_glSecondaryColorPointerEXT)
                  (GLint size,GLenum type,GLsizei stride,const GLvoid *pointer)=
            (void (OSG_APIENTRY*)(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer))
             win->getFunction(GeoPumpFactory::_funcglSecondaryColorPointer);

            _glSecondaryColorPointerEXT(SecColorsPtr->getDimension(),
                                       SecColorsPtr->getFormat(),
                                       SecColorsStride, SecColorsData);
            glEnableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
            modified|=(1<<2);
        }
        else
            FWARNING(("GeoPump129: Window has no Secondary Color extension\n"));
    }


    if (NormalsData)
    {
        glNormalPointer(NormalsPtr->getFormat(), NormalsStride, NormalsData);
        glEnableClientState(GL_NORMAL_ARRAY);
        modified|=(1<<3);
    }

    if (TexCoordsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        else
        {
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        modified|=(1<<4);
    }

    if (TexCoords1Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE1_ARB);
            glTexCoordPointer (TexCoords1Ptr->getDimension(), TexCoords1Ptr->getFormat(),
                               TexCoords1Stride, TexCoords1Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<5);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords2Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE2_ARB);
            glTexCoordPointer (TexCoords2Ptr->getDimension(), TexCoords2Ptr->getFormat(),
                               TexCoords2Stride, TexCoords2Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<6);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords3Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE3_ARB);
            glTexCoordPointer (TexCoords3Ptr->getDimension(), TexCoords3Ptr->getFormat(),
                               TexCoords3Stride, TexCoords3Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<7);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords4Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE4_ARB);
            glTexCoordPointer (TexCoords4Ptr->getDimension(), TexCoords4Ptr->getFormat(),
                               TexCoords4Stride, TexCoords4Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<8);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords5Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE5_ARB);
            glTexCoordPointer (TexCoords5Ptr->getDimension(), TexCoords5Ptr->getFormat(),
                               TexCoords5Stride, TexCoords5Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<9);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords6Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE6_ARB);
            glTexCoordPointer (TexCoords6Ptr->getDimension(), TexCoords6Ptr->getFormat(),
                               TexCoords6Stride, TexCoords6Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<10);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    if (TexCoords7Data)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE7_ARB);
            glTexCoordPointer (TexCoords7Ptr->getDimension(), TexCoords7Ptr->getFormat(),
                               TexCoords7Stride, TexCoords7Data);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<11);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    UInt32 lendummy;
    UInt32 LengthsSize;
    bool   len16 = false;

    if(LengthsPtr != NullFC && LengthsData != NULL)
    {
        LengthsSize = LengthsPtr->getSize();
        len16 = (LengthsPtr->getFormatSize() == 2);
    }
    else
    {
        LengthsSize = 1;
        LengthsData = (UChar8*) &lendummy;
        lendummy = PositionsPtr->getSize();
    }
        
    UInt32 LengthsInd = 0, TypesInd = 0, IndicesInd = 0, 
           IndicesSize = IndicesPtr->getSize();

    if (win->hasExtension(GeoPumpFactory::_extCompiledVertexArray))
    {
            void (OSG_APIENTRY*_glLockArraysEXT) (GLint first, GLsizei count)=
            (void (OSG_APIENTRY*) (GLint first, GLsizei count))
                win->getFunction(GeoPumpFactory::_funcglLockArraysEXT);
                
            _glLockArraysEXT(geo->getMinindex(), geo->getMaxindex() + 1);
    }

    void (OSG_APIENTRY *osgGLDrawRangeElementsEXT)(GLenum mode, GLuint start,
           GLuint end, GLsizei count, GLenum type, const GLvoid*indices) =
    (void (OSG_APIENTRY *)(GLenum mode, GLuint start,
           GLuint end, GLsizei count, GLenum type, const GLvoid*indices))
            win->getFunction(GeoPumpFactory::_funcglDrawRangeElementsEXT);


    if(len16 == false)
    {
        for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
        {
            UInt32 count  = *(UInt32*)(LengthsData + LengthsInd * LengthsStride);
            UInt8 * vind = IndicesData + IndicesStride * IndicesInd;
            IndicesInd += count;

#if 0
            glDrawElements(*(TypesData + TypesInd++ * TypesStride),count,
                            IndicesPtr->getFormat(),vind);
#else
            if(win->hasExtension(GeoPumpFactory::_extDrawRangeElements))
            {
                osgGLDrawRangeElementsEXT(*(TypesData + TypesInd++ * TypesStride),
                                          geo->getLowindices() [LengthsInd], 
                                          geo->getHighindices()[LengthsInd], 
                                          count,
                                          IndicesPtr->getFormat(), 
                                          vind);
            }
            else
            {
                // hope this still works
                glDrawElements(*(TypesData + TypesInd++ * TypesStride),
                               count,
                               IndicesPtr->getFormat(),
                               vind);
            }
#endif                        
        }
    }
    else if(len16 == true)
    {
        for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
        {
            UInt16 count  = *(UInt16*)(LengthsData + LengthsInd * LengthsStride);
            UInt8 * vind = IndicesData + IndicesStride * IndicesInd;
            IndicesInd += count;

#if 0
            glDrawElements(*(TypesData + TypesInd++ * TypesStride),count,
                            IndicesPtr->getFormat(),vind);
#else
            if(win->hasExtension(GeoPumpFactory::_extDrawRangeElements))
            {
                osgGLDrawRangeElementsEXT(*(TypesData + TypesInd++ * TypesStride),
                                          0, 
                                          IndicesSize, 
                                          count,
                                          IndicesPtr->getFormat(), 
                                          vind);
            }
            else
            {
                // hope this still works
                glDrawElements(*(TypesData + TypesInd++ * TypesStride),
                               count,
                               IndicesPtr->getFormat(),
                               vind);
            }
#endif                        
        }
    }
    else
    {
        FWARNING(("GeoPump129: unknown Lengths format size\n"));
    }

    if (win->hasExtension(GeoPumpFactory::_extCompiledVertexArray))
    {
            void (OSG_APIENTRY*_glUnlockArraysEXT) (void)=
            (void (OSG_APIENTRY*) (void))
                win->getFunction(GeoPumpFactory::_funcglUnlockArraysEXT);
                
            _glUnlockArraysEXT();
    }

    if(modified&(1<<0)) glDisableClientState(GL_VERTEX_ARRAY);
    if(modified&(1<<1)) glDisableClientState(GL_COLOR_ARRAY);
    if(modified&(1<<2)) glDisableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
    if(modified&(1<<3)) glDisableClientState(GL_NORMAL_ARRAY);

    if (win->hasExtension(GeoPumpFactory::_extMultitexture))
    {
        void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
        (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);

        if(modified&(1<<4))
        {
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<5))
        {
            _glClientActiveTextureARB(GL_TEXTURE1_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<6))
        {
            _glClientActiveTextureARB(GL_TEXTURE2_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<7))
        {
            _glClientActiveTextureARB(GL_TEXTURE3_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<8))
        {
            _glClientActiveTextureARB(GL_TEXTURE4_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<9))
        {
            _glClientActiveTextureARB(GL_TEXTURE5_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<10))
        {
            _glClientActiveTextureARB(GL_TEXTURE6_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<11))
        {
            _glClientActiveTextureARB(GL_TEXTURE7_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
    else
    {
        if(modified&(1<<4)) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}


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
                 << #name << "s!" << std::endl;                             \
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
                     << "!" << std::endl;                                   \
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
                     << "!" << std::endl;                                   \
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
                     <<  "!" << std::endl;                                  \
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
                     << "!" << std::endl;                                   \
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
                     <<  "!" << std::endl;                                  \
            return;                                                         \
        }                                                                   \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        name##Data = NULL;                                                  \
        name##Func = NULL;                                                  \
        name##Stride = 0;                                                   \
    }

#define iC  pumpGLSetup         ( Color     , GeoColorsPtr   , getColors         )\
            Int16 ColorIndex  =  geo->calcMappingIndex( Geometry::MapColor );     \
            if(ColorData && ColorPtr->getSize() == 1)                             \
                ColorFunc(ColorData);

#define iS  pumpGLExtSetup      ( SecColor  , GeoColorsPtr   , getSecondaryColors)\
            Int16 SecColorIndex = geo->calcMappingIndex(Geometry::MapSecondaryColor);

#define iN  pumpGLSetup         ( Normal    , GeoNormalsPtr  , getNormals        )\
            Int16 NormalIndex = geo->calcMappingIndex(Geometry::MapNormal);

#define iT  pumpGLSetup         ( TexCoords , GeoTexCoordsPtr, getTexCoords      )\
            Int16 TexCoordsIndex  = geo->calcMappingIndex(Geometry::MapTexCoords);

#define iT1 pumpMultiGLExtSetup ( TexCoords1, GeoTexCoordsPtr, getTexCoords1     )\
            Int16 TexCoords1Index = geo->calcMappingIndex(Geometry::MapTexCoords1);

#define iT2 pumpMultiGLExtSetup ( TexCoords2, GeoTexCoordsPtr, getTexCoords2     )\
            Int16 TexCoords2Index = geo->calcMappingIndex(Geometry::MapTexCoords2);

#define iT3 pumpMultiGLExtSetup ( TexCoords3, GeoTexCoordsPtr, getTexCoords3     )\
            Int16 TexCoords3Index = geo->calcMappingIndex(Geometry::MapTexCoords3);

#define iT4 pumpMultiGLExtSetup ( TexCoords4, GeoTexCoordsPtr, getTexCoords4     )\
            Int16 TexCoords4Index = geo->calcMappingIndex(Geometry::MapTexCoords4);

#define iT5 pumpMultiGLExtSetup ( TexCoords5, GeoTexCoordsPtr, getTexCoords5     )\
            Int16 TexCoords5Index = geo->calcMappingIndex(Geometry::MapTexCoords5);

#define iT6 pumpMultiGLExtSetup ( TexCoords6, GeoTexCoordsPtr, getTexCoords6     )\
            Int16 TexCoords6Index = geo->calcMappingIndex(Geometry::MapTexCoords6);

#define iT7 pumpMultiGLExtSetup ( TexCoords7, GeoTexCoordsPtr, getTexCoords7     )\
            Int16 TexCoords7Index = geo->calcMappingIndex(Geometry::MapTexCoords7);

#define rC ColorFunc     ( ColorData     + ColorStride     * vind[ColorIndex]     );
#define rS SecColorFunc  ( SecColorData  + SecColorStride  * vind[SecColorIndex]  );
#define rN NormalFunc    ( NormalData    + NormalStride    * vind[NormalIndex]    );
#define rT TexCoordsFunc ( TexCoordsData + TexCoordsStride * vind[TexCoordsIndex] );
#define rT1 TexCoords1Func( GL_TEXTURE1_ARB , TexCoords1Data + TexCoords1Stride * vind[TexCoords1Index] );
#define rT2 TexCoords2Func( GL_TEXTURE2_ARB , TexCoords2Data + TexCoords2Stride * vind[TexCoords2Index] );
#define rT3 TexCoords3Func( GL_TEXTURE3_ARB , TexCoords3Data + TexCoords3Stride * vind[TexCoords3Index] );
#define rT4 TexCoords4Func( GL_TEXTURE4_ARB , TexCoords4Data + TexCoords4Stride * vind[TexCoords4Index] );
#define rT5 TexCoords5Func( GL_TEXTURE5_ARB , TexCoords5Data + TexCoords5Stride * vind[TexCoords5Index] );
#define rT6 TexCoords6Func( GL_TEXTURE6_ARB , TexCoords6Data + TexCoords6Stride * vind[TexCoords6Index] );
#define rT7 TexCoords7Func( GL_TEXTURE7_ARB , TexCoords7Data + TexCoords7Stride * vind[TexCoords7Index] );

/*
    nmappings for sure is greater or equal than two because this is multi
    index geometry and there is for sure IndexData!!!
*/

#define defMultiGeoPump( func, init , render )                              \
static                                                                      \
void GeoPump##func( Window   *win,                                          \
                           Geometry *geo)                                   \
{                                                                           \
    /*if (win) ; */                                                         \
                                                                            \
    pumpInternalSetup( Type  , GeoPTypesPtr   , getTypes  , true );         \
    pumpInternalSetup( Length, GeoPLengthsPtr , getLengths, false );        \
    pumpInternalSetup( Index , GeoIndicesPtr  , getIndices, false );        \
                                                                            \
    pumpGLSetup( Position    , GeoPositionsPtr, getPositions );             \
    Int16 PositionIndex = geo->calcMappingIndex(Geometry::MapPosition);     \
                                                                            \
    init;                                                                   \
    UInt16 nmappings = geo->getIndexMapping().size();                       \
                                                                            \
    UInt32 lendummy;                                                        \
    UInt32 LengthSize;                                                      \
                                                                            \
    if ( ! LengthData )                                                     \
    {                                                                       \
        LengthSize = 1;                                                     \
        LengthData = (UChar8*) &lendummy;                                   \
        lendummy = IndexPtr->getSize() / nmappings;                         \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        LengthSize = LengthPtr->getSize();                                  \
    }                                                                       \
                                                                            \
    for ( LengthInd = 0; LengthInd < LengthSize; LengthInd++ )              \
    {                                                                       \
        glBegin( *(TypeData + TypeInd++ * TypeStride) );                    \
                                                                            \
        for ( UInt32 l = *(UInt32*)(LengthData + LengthInd * LengthStride); \
                       l > 0; l-- )                                         \
        {                                                                   \
            UInt32 * vind;                                                  \
                                                                            \
            vind = (UInt32*)(IndexData + IndexStride * IndexInd);           \
            IndexInd += nmappings;                                          \
                                                                            \
            render;                                                         \
            PositionFunc(PositionData+PositionStride*vind[PositionIndex]);  \
        }                                                                   \
        glEnd();                                                            \
    }                                                                       \
                                                                            \
}


#ifdef __sgi
#pragma set woff 1174,1209
#endif

/*
   Defining all multi-indexed Geometry pumps (127:))
*/

defMultiGeoPump(   1 , iC;                            , rC;                             ) 
defMultiGeoPump(   2 ,     iS;                        ,     rS;                         ) 
defMultiGeoPump(   3 , iC; iS;                        , rC; rS;                         ) 
defMultiGeoPump(   4 ,         iN;                    ,         rN;                     ) 
defMultiGeoPump(   5 , iC;     iN;                    , rC;     rN;                     ) 
defMultiGeoPump(   6 ,     iS; iN;                    ,     rS; rN;                     ) 
defMultiGeoPump(   7 , iC; iS; iN;                    , rC; rS; rN;                     ) 
defMultiGeoPump(   8 ,             iT;                ,             rT;                 ) 
defMultiGeoPump(   9 , iC;         iT;                , rC;         rT;                 ) 
defMultiGeoPump(  10 ,     iS;     iT;                ,     rS;     rT;                 ) 
defMultiGeoPump(  11 , iC; iS;     iT;                , rC; rS;     rT;                 ) 
defMultiGeoPump(  12 ,         iN; iT;                ,         rN; rT;                 ) 
defMultiGeoPump(  13 , iC;     iN; iT;                , rC;     rN; rT;                 ) 
defMultiGeoPump(  14 ,     iS; iN; iT;                ,     rS; rN; rT;                 ) 
defMultiGeoPump(  15 , iC; iS; iN; iT;                , rC; rS; rN; rT;                 ) 
defMultiGeoPump(  16 ,                 iT1;           ,                 rT1;            ) 
defMultiGeoPump(  17 , iC;             iT1;           , rC;             rT1;            ) 
defMultiGeoPump(  18 ,     iS;         iT1;           ,     rS;         rT1;            ) 
defMultiGeoPump(  19 , iC; iS;         iT1;           , rC; rS;         rT1;            ) 
defMultiGeoPump(  20 ,         iN;     iT1;           ,         rN;     rT1;            ) 
defMultiGeoPump(  21 , iC;     iN;     iT1;           , rC;     rN;     rT1;            ) 
defMultiGeoPump(  22 ,     iS; iN;     iT1;           ,     rS; rN;     rT1;            ) 
defMultiGeoPump(  23 , iC; iS; iN;     iT1;           , rC; rS; rN;     rT1;            ) 
defMultiGeoPump(  24 ,             iT; iT1;           ,             rT; rT1;            ) 
defMultiGeoPump(  25 , iC;         iT; iT1;           , rC;         rT; rT1;            ) 
defMultiGeoPump(  26 ,     iS;     iT; iT1;           ,     rS;     rT; rT1;            ) 
defMultiGeoPump(  27 , iC; iS;     iT; iT1;           , rC; rS;     rT; rT1;            ) 
defMultiGeoPump(  28 ,         iN; iT; iT1;           ,         rN; rT; rT1;            ) 
defMultiGeoPump(  29 , iC;     iN; iT; iT1;           , rC;     rN; rT; rT1;            ) 
defMultiGeoPump(  30 ,     iS; iN; iT; iT1;           ,     rS; rN; rT; rT1;            ) 
defMultiGeoPump(  31 , iC; iS; iN; iT; iT1;           , rC; rS; rN; rT; rT1;            ) 
defMultiGeoPump(  32 ,                      iT2;      ,                      rT2;       ) 
defMultiGeoPump(  33 , iC;                  iT2;      , rC;                  rT2;       ) 
defMultiGeoPump(  34 ,     iS;              iT2;      ,     rS;              rT2;       ) 
defMultiGeoPump(  35 , iC; iS;              iT2;      , rC; rS;              rT2;       ) 
defMultiGeoPump(  36 ,         iN;          iT2;      ,         rN;          rT2;       ) 
defMultiGeoPump(  37 , iC;     iN;          iT2;      , rC;     rN;          rT2;       ) 
defMultiGeoPump(  38 ,     iS; iN;          iT2;      ,     rS; rN;          rT2;       ) 
defMultiGeoPump(  39 , iC; iS; iN;          iT2;      , rC; rS; rN;          rT2;       ) 
defMultiGeoPump(  40 ,             iT;      iT2;      ,             rT;      rT2;       ) 
defMultiGeoPump(  41 , iC;         iT;      iT2;      , rC;         rT;      rT2;       ) 
defMultiGeoPump(  42 ,     iS;     iT;      iT2;      ,     rS;     rT;      rT2;       ) 
defMultiGeoPump(  43 , iC; iS;     iT;      iT2;      , rC; rS;     rT;      rT2;       ) 
defMultiGeoPump(  44 ,         iN; iT;      iT2;      ,         rN; rT;      rT2;       ) 
defMultiGeoPump(  45 , iC;     iN; iT;      iT2;      , rC;     rN; rT;      rT2;       ) 
defMultiGeoPump(  46 ,     iS; iN; iT;      iT2;      ,     rS; rN; rT;      rT2;       ) 
defMultiGeoPump(  47 , iC; iS; iN; iT;      iT2;      , rC; rS; rN; rT;      rT2;       ) 
defMultiGeoPump(  48 ,                 iT1; iT2;      ,                 rT1; rT2;       ) 
defMultiGeoPump(  49 , iC;             iT1; iT2;      , rC;             rT1; rT2;       ) 
defMultiGeoPump(  50 ,     iS;         iT1; iT2;      ,     rS;         rT1; rT2;       ) 
defMultiGeoPump(  51 , iC; iS;         iT1; iT2;      , rC; rS;         rT1; rT2;       ) 
defMultiGeoPump(  52 ,         iN;     iT1; iT2;      ,         rN;     rT1; rT2;       ) 
defMultiGeoPump(  53 , iC;     iN;     iT1; iT2;      , rC;     rN;     rT1; rT2;       ) 
defMultiGeoPump(  54 ,     iS; iN;     iT1; iT2;      ,     rS; rN;     rT1; rT2;       ) 
defMultiGeoPump(  55 , iC; iS; iN;     iT1; iT2;      , rC; rS; rN;     rT1; rT2;       ) 
defMultiGeoPump(  56 ,             iT; iT1; iT2;      ,             rT; rT1; rT2;       ) 
defMultiGeoPump(  57 , iC;         iT; iT1; iT2;      , rC;         rT; rT1; rT2;       ) 
defMultiGeoPump(  58 ,     iS;     iT; iT1; iT2;      ,     rS;     rT; rT1; rT2;       ) 
defMultiGeoPump(  59 , iC; iS;     iT; iT1; iT2;      , rC; rS;     rT; rT1; rT2;       ) 
defMultiGeoPump(  60 ,         iN; iT; iT1; iT2;      ,         rN; rT; rT1; rT2;       ) 
defMultiGeoPump(  61 , iC;     iN; iT; iT1; iT2;      , rC;     rN; rT; rT1; rT2;       ) 
defMultiGeoPump(  62 ,     iS; iN; iT; iT1; iT2;      ,     rS; rN; rT; rT1; rT2;       ) 
defMultiGeoPump(  63 , iC; iS; iN; iT; iT1; iT2;      , rC; rS; rN; rT; rT1; rT2;       ) 
defMultiGeoPump(  64 ,                           iT3; ,                           rT3;  ) 
defMultiGeoPump(  65 , iC;                       iT3; , rC;                       rT3;  ) 
defMultiGeoPump(  66 ,     iS;                   iT3; ,     rS;                   rT3;  ) 
defMultiGeoPump(  67 , iC; iS;                   iT3; , rC; rS;                   rT3;  ) 
defMultiGeoPump(  68 ,         iN;               iT3; ,         rN;               rT3;  ) 
defMultiGeoPump(  69 , iC;     iN;               iT3; , rC;     rN;               rT3;  ) 
defMultiGeoPump(  70 ,     iS; iN;               iT3; ,     rS; rN;               rT3;  ) 
defMultiGeoPump(  71 , iC; iS; iN;               iT3; , rC; rS; rN;               rT3;  ) 
defMultiGeoPump(  72 ,             iT;           iT3; ,             rT;           rT3;  ) 
defMultiGeoPump(  73 , iC;         iT;           iT3; , rC;         rT;           rT3;  ) 
defMultiGeoPump(  74 ,     iS;     iT;           iT3; ,     rS;     rT;           rT3;  ) 
defMultiGeoPump(  75 , iC; iS;     iT;           iT3; , rC; rS;     rT;           rT3;  ) 
defMultiGeoPump(  76 ,         iN; iT;           iT3; ,         rN; rT;           rT3;  ) 
defMultiGeoPump(  77 , iC;     iN; iT;           iT3; , rC;     rN; rT;           rT3;  ) 
defMultiGeoPump(  78 ,     iS; iN; iT;           iT3; ,     rS; rN; rT;           rT3;  ) 
defMultiGeoPump(  79 , iC; iS; iN; iT;           iT3; , rC; rS; rN; rT;           rT3;  ) 
defMultiGeoPump(  80 ,                 iT1;      iT3; ,                 rT1;      rT3;  ) 
defMultiGeoPump(  81 , iC;             iT1;      iT3; , rC;             rT1;      rT3;  ) 
defMultiGeoPump(  82 ,     iS;         iT1;      iT3; ,     rS;         rT1;      rT3;  ) 
defMultiGeoPump(  83 , iC; iS;         iT1;      iT3; , rC; rS;         rT1;      rT3;  ) 
defMultiGeoPump(  84 ,         iN;     iT1;      iT3; ,         rN;     rT1;      rT3;  ) 
defMultiGeoPump(  85 , iC;     iN;     iT1;      iT3; , rC;     rN;     rT1;      rT3;  ) 
defMultiGeoPump(  86 ,     iS; iN;     iT1;      iT3; ,     rS; rN;     rT1;      rT3;  ) 
defMultiGeoPump(  87 , iC; iS; iN;     iT1;      iT3; , rC; rS; rN;     rT1;      rT3;  ) 
defMultiGeoPump(  88 ,             iT; iT1;      iT3; ,             rT; rT1;      rT3;  ) 
defMultiGeoPump(  89 , iC;         iT; iT1;      iT3; , rC;         rT; rT1;      rT3;  ) 
defMultiGeoPump(  90 ,     iS;     iT; iT1;      iT3; ,     rS;     rT; rT1;      rT3;  ) 
defMultiGeoPump(  91 , iC; iS;     iT; iT1;      iT3; , rC; rS;     rT; rT1;      rT3;  ) 
defMultiGeoPump(  92 ,         iN; iT; iT1;      iT3; ,         rN; rT; rT1;      rT3;  ) 
defMultiGeoPump(  93 , iC;     iN; iT; iT1;      iT3; , rC;     rN; rT; rT1;      rT3;  ) 
defMultiGeoPump(  94 ,     iS; iN; iT; iT1;      iT3; ,     rS; rN; rT; rT1;      rT3;  ) 
defMultiGeoPump(  95 , iC; iS; iN; iT; iT1;      iT3; , rC; rS; rN; rT; rT1;      rT3;  ) 
defMultiGeoPump(  96 ,                      iT2; iT3; ,                      rT2; rT3;  ) 
defMultiGeoPump(  97 , iC;                  iT2; iT3; , rC;                  rT2; rT3;  ) 
defMultiGeoPump(  98 ,     iS;              iT2; iT3; ,     rS;              rT2; rT3;  ) 
defMultiGeoPump(  99 , iC; iS;              iT2; iT3; , rC; rS;              rT2; rT3;  ) 
defMultiGeoPump( 100 ,         iN;          iT2; iT3; ,         rN;          rT2; rT3;  ) 
defMultiGeoPump( 101 , iC;     iN;          iT2; iT3; , rC;     rN;          rT2; rT3;  ) 
defMultiGeoPump( 102 ,     iS; iN;          iT2; iT3; ,     rS; rN;          rT2; rT3;  ) 
defMultiGeoPump( 103 , iC; iS; iN;          iT2; iT3; , rC; rS; rN;          rT2; rT3;  ) 
defMultiGeoPump( 104 ,             iT;      iT2; iT3; ,             rT;      rT2; rT3;  ) 
defMultiGeoPump( 105 , iC;         iT;      iT2; iT3; , rC;         rT;      rT2; rT3;  ) 
defMultiGeoPump( 106 ,     iS;     iT;      iT2; iT3; ,     rS;     rT;      rT2; rT3;  ) 
defMultiGeoPump( 107 , iC; iS;     iT;      iT2; iT3; , rC; rS;     rT;      rT2; rT3;  ) 
defMultiGeoPump( 108 ,         iN; iT;      iT2; iT3; ,         rN; rT;      rT2; rT3;  ) 
defMultiGeoPump( 109 , iC;     iN; iT;      iT2; iT3; , rC;     rN; rT;      rT2; rT3;  ) 
defMultiGeoPump( 110 ,     iS; iN; iT;      iT2; iT3; ,     rS; rN; rT;      rT2; rT3;  ) 
defMultiGeoPump( 111 , iC; iS; iN; iT;      iT2; iT3; , rC; rS; rN; rT;      rT2; rT3;  ) 
defMultiGeoPump( 112 ,                 iT1; iT2; iT3; ,                 rT1; rT2; rT3;  ) 
defMultiGeoPump( 113 , iC;             iT1; iT2; iT3; , rC;             rT1; rT2; rT3;  ) 
defMultiGeoPump( 114 ,     iS;         iT1; iT2; iT3; ,     rS;         rT1; rT2; rT3;  ) 
defMultiGeoPump( 115 , iC; iS;         iT1; iT2; iT3; , rC; rS;         rT1; rT2; rT3;  ) 
defMultiGeoPump( 116 ,         iN;     iT1; iT2; iT3; ,         rN;     rT1; rT2; rT3;  ) 
defMultiGeoPump( 117 , iC;     iN;     iT1; iT2; iT3; , rC;     rN;     rT1; rT2; rT3;  ) 
defMultiGeoPump( 118 ,     iS; iN;     iT1; iT2; iT3; ,     rS; rN;     rT1; rT2; rT3;  ) 
defMultiGeoPump( 119 , iC; iS; iN;     iT1; iT2; iT3; , rC; rS; rN;     rT1; rT2; rT3;  ) 
defMultiGeoPump( 120 ,             iT; iT1; iT2; iT3; ,             rT; rT1; rT2; rT3;  ) 
defMultiGeoPump( 121 , iC;         iT; iT1; iT2; iT3; , rC;         rT; rT1; rT2; rT3;  ) 
defMultiGeoPump( 122 ,     iS;     iT; iT1; iT2; iT3; ,     rS;     rT; rT1; rT2; rT3;  ) 
defMultiGeoPump( 123 , iC; iS;     iT; iT1; iT2; iT3; , rC; rS;     rT; rT1; rT2; rT3;  ) 
defMultiGeoPump( 124 ,         iN; iT; iT1; iT2; iT3; ,         rN; rT; rT1; rT2; rT3;  ) 
defMultiGeoPump( 125 , iC;     iN; iT; iT1; iT2; iT3; , rC;     rN; rT; rT1; rT2; rT3;  ) 
defMultiGeoPump( 126 ,     iS; iN; iT; iT1; iT2; iT3; ,     rS; rN; rT; rT1; rT2; rT3;  ) 
defMultiGeoPump( 127 , iC; iS; iN; iT; iT1; iT2; iT3; , rC; rS; rN; rT; rT1; rT2; rT3;  )

// the master pump function

GeoPumpFactory::GeoPump GeoPumpFactory::GeoPumps[131]={&GeoPump0,
&GeoPump1,&GeoPump2,&GeoPump3,&GeoPump4,&GeoPump5,&GeoPump6,&GeoPump7,&GeoPump8,
&GeoPump9,&GeoPump10,&GeoPump11,&GeoPump12,&GeoPump13,&GeoPump14,&GeoPump15,&GeoPump16,
&GeoPump17,&GeoPump18,&GeoPump19,&GeoPump20,&GeoPump21,&GeoPump22,&GeoPump23,&GeoPump24,
&GeoPump25,&GeoPump26,&GeoPump27,&GeoPump28,&GeoPump29,&GeoPump30,&GeoPump31,&GeoPump32,
&GeoPump33,&GeoPump34,&GeoPump35,&GeoPump36,&GeoPump37,&GeoPump38,&GeoPump39,&GeoPump40,
&GeoPump41,&GeoPump42,&GeoPump43,&GeoPump44,&GeoPump45,&GeoPump46,&GeoPump47,&GeoPump48,
&GeoPump49,&GeoPump50,&GeoPump51,&GeoPump52,&GeoPump53,&GeoPump54,&GeoPump55,&GeoPump56,
&GeoPump57,&GeoPump58,&GeoPump59,&GeoPump60,&GeoPump61,&GeoPump62,&GeoPump63,&GeoPump64,
&GeoPump65,&GeoPump66,&GeoPump67,&GeoPump68,&GeoPump69,&GeoPump70,&GeoPump71,&GeoPump72,
&GeoPump73,&GeoPump74,&GeoPump75,&GeoPump76,&GeoPump77,&GeoPump78,&GeoPump79,&GeoPump80,
&GeoPump81,&GeoPump82,&GeoPump83,&GeoPump84,&GeoPump85,&GeoPump86,&GeoPump87,&GeoPump88,
&GeoPump89,&GeoPump90,&GeoPump91,&GeoPump92,&GeoPump93,&GeoPump94,&GeoPump95,&GeoPump96,
&GeoPump97,&GeoPump98,&GeoPump99,&GeoPump100,&GeoPump101,&GeoPump102,&GeoPump103,&GeoPump104,
&GeoPump105,&GeoPump106,&GeoPump107,&GeoPump108,&GeoPump109,&GeoPump110,&GeoPump111,&GeoPump112,
&GeoPump113,&GeoPump114,&GeoPump115,&GeoPump116,&GeoPump117,&GeoPump118,&GeoPump119,&GeoPump120,
&GeoPump121,&GeoPump122,&GeoPump123,&GeoPump124,&GeoPump125,&GeoPump126,&GeoPump127,&GeoPump128,
&GeoPump129,&GeoPumpFactory::masterGeoPump};

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
    pumpMultiGLExtSetup( TexCoords4, GeoTexCoordsPtr, getTexCoords4     );
    pumpMultiGLExtSetup( TexCoords5, GeoTexCoordsPtr, getTexCoords5     );
    pumpMultiGLExtSetup( TexCoords6, GeoTexCoordsPtr, getTexCoords6     );
    pumpMultiGLExtSetup( TexCoords7, GeoTexCoordsPtr, getTexCoords7     );

    // check if the node is empty
    if(! TypeData || TypePtr->getSize() == 0)
        return;

    // if it's not empty we need positions
    if(! PositionData)
    {
        SWARNING << "masterPump: Geometry " << geo << " has no positions!?!"
                 << std::endl;
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
          TexCoords3Index = -1,
          TexCoords4Index = -1,
          TexCoords5Index = -1,
          TexCoords6Index = -1,
          TexCoords7Index = -1;

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
        TexCoords4Index = geo->calcMappingIndex(Geometry::MapTexCoords4    );
        TexCoords5Index = geo->calcMappingIndex(Geometry::MapTexCoords5    );
        TexCoords6Index = geo->calcMappingIndex(Geometry::MapTexCoords6    );
        TexCoords7Index = geo->calcMappingIndex(Geometry::MapTexCoords7    );

        if(! PositionData)
        {
            SWARNING << "masterPump: Geometry " 
                     << geo 
                     << "has no position index!?!"
                     << std::endl;
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
        TexCoords3Index = 
        TexCoords4Index =
        TexCoords5Index =
        TexCoords6Index =
        TexCoords7Index = 0;
    }

    // overall color?
    if(ColorData && ColorPtr->getSize() == 1)
        ColorFunc(ColorData);

    // Length handling. Special case: no length given

    UInt32 lendummy;
    UInt32 LengthSize;
    bool len16 = false;
    
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
        len16 = (LengthPtr->getFormatSize() == 2);
    }

    bool ind16 = false;
    ind16 = (IndexPtr != NullFC && IndexPtr->getFormatSize() == 2);
    
    UInt32 l;
    
    for(LengthInd = 0; LengthInd < LengthSize; LengthInd++)
    {
        glBegin(*(TypeData + TypeInd++ * TypeStride));

        if(len16)
        {
            l = *(UInt16*)(LengthData + LengthInd * LengthStride);
        }
        else
        {
            l = *(UInt32*)(LengthData + LengthInd * LengthStride);
        }
        
        for( ; l > 0; l--)
        {
            if(IndexData && !ind16)
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

                if(TexCoords4Data && TexCoords4Index >= 0)
                {
                    TexCoords4Func(GL_TEXTURE4_ARB,
                                     TexCoords4Data + TexCoords4Stride *
                                     vind[TexCoords4Index]);
                }

                if(TexCoords5Data && TexCoords5Index >= 0)
                {
                    TexCoords5Func(GL_TEXTURE5_ARB,
                                     TexCoords5Data + TexCoords5Stride *
                                     vind[TexCoords5Index]);
                }

                if(TexCoords6Data && TexCoords6Index >= 0)
                {
                    TexCoords6Func(GL_TEXTURE6_ARB,
                                     TexCoords6Data + TexCoords6Stride *
                                     vind[TexCoords6Index]);
                }

                if(TexCoords7Data && TexCoords7Index >= 0)
                {
                    TexCoords7Func(GL_TEXTURE7_ARB,
                                     TexCoords7Data + TexCoords7Stride *
                                     vind[TexCoords7Index]);
                }

                PositionFunc(PositionData + PositionStride * vind[PositionIndex]);
            }
            else if(IndexData && ind16)
            {
                UInt16 * vind;

                vind = (UInt16*)(IndexData + IndexStride * IndexInd);
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

                if(TexCoords4Data && TexCoords4Index >= 0)
                {
                    TexCoords4Func(GL_TEXTURE4_ARB,
                                     TexCoords4Data + TexCoords4Stride *
                                     vind[TexCoords4Index]);
                }

                if(TexCoords5Data && TexCoords5Index >= 0)
                {
                    TexCoords5Func(GL_TEXTURE5_ARB,
                                     TexCoords5Data + TexCoords5Stride *
                                     vind[TexCoords5Index]);
                }

                if(TexCoords6Data && TexCoords6Index >= 0)
                {
                    TexCoords6Func(GL_TEXTURE6_ARB,
                                     TexCoords6Data + TexCoords6Stride *
                                     vind[TexCoords6Index]);
                }

                if(TexCoords7Data && TexCoords7Index >= 0)
                {
                    TexCoords7Func(GL_TEXTURE7_ARB,
                                     TexCoords7Data + TexCoords7Stride *
                                     vind[TexCoords7Index]);
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

                if(TexCoords4Data)
                {
                    TexCoords4Func(GL_TEXTURE4_ARB,
                                   TexCoords4Data + TexCoords4Stride *
                                                    PositionInd);
                }

                if(TexCoords5Data)
                {
                    TexCoords5Func(GL_TEXTURE5_ARB,
                                   TexCoords5Data + TexCoords5Stride *
                                                    PositionInd);
                }

                if(TexCoords6Data)
                {
                    TexCoords6Func(GL_TEXTURE6_ARB,
                                   TexCoords6Data + TexCoords6Stride *
                                                    PositionInd);
                }

                if(TexCoords7Data)
                {
                    TexCoords7Func(GL_TEXTURE7_ARB,
                                   TexCoords7Data + TexCoords7Stride *
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
    _extSecondaryColor      = 
        Window::registerExtension("GL_EXT_secondary_color");
    _extMultitexture        = 
        Window::registerExtension("GL_ARB_multitexture");
    _extCompiledVertexArray = 
        Window::registerExtension("GL_EXT_compiled_vertex_array");
    _extDrawRangeElements   = 
        Window::registerExtension("GL_EXT_draw_range_elements");
    _arbVBO =
        Window::registerExtension("GL_ARB_vertex_buffer_object");

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
        secondaryColorInitFuncs[i].init(SecColorIDs, _extSecondaryColor);

    for(i = 0; i < 16; i++)
        multiTexCoordsInitFuncs[i].init(TexCoords1IDs, _extMultitexture);

    _funcglSecondaryColorPointer  = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glSecondaryColorPointerEXT",
                            _extSecondaryColor);
    _funcglClientActiveTextureARB = Window::registerFunction(
                            OSG_DLSYM_UNDERSCORE"glClientActiveTextureARB",
                            _extMultitexture);
    _funcglLockArraysEXT          = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glLockArraysEXT",
                                _extCompiledVertexArray);
    _funcglUnlockArraysEXT        = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glUnlockArraysEXT",
                                _extCompiledVertexArray);
    _funcglDrawRangeElementsEXT   = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glDrawRangeElementsEXT",
                                _extDrawRangeElements);

    _funcglGenBuffers           = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glGenBuffers",
                                _arbVBO);
    _funcglDeleteBuffers         = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glDeleteBuffers",
                                _arbVBO);
    _funcglBindBuffer           = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glBindBuffer",
                                _arbVBO);
    _funcglBufferData           = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glBufferData",
                                _arbVBO);
    _funcglBufferSubData         = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glBufferSubData",
                                _arbVBO);

    _funcglGenBuffersARB        = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glGenBuffersARB",
                                _arbVBO);
    _funcglDeleteBuffersARB     = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glDeleteBuffersARB",
                                _arbVBO);
    _funcglBindBufferARB        = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glBindBufferARB",
                                _arbVBO);
    _funcglBufferDataARB        = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glBufferDataARB",
                                _arbVBO);
    _funcglBufferSubDataARB     = Window::registerFunction(
                                OSG_DLSYM_UNDERSCORE"glBufferSubDataARB",
                                _arbVBO);

    return true;
}

// ------------------------------------------------------
// vbo stuff.
// ------------------------------------------------------

#ifndef GL_ARB_vertex_buffer_object
#define GL_BUFFER_SIZE_ARB                          0x8764
#define GL_BUFFER_USAGE_ARB                         0x8765
#define GL_ARRAY_BUFFER_ARB                         0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB                 0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB                 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB         0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB          0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB          0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB           0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB           0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB   0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB       0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB  0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB          0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB   0x889F
#define GL_READ_ONLY_ARB                            0x88B8
#define GL_WRITE_ONLY_ARB                           0x88B9
#define GL_READ_WRITE_ARB                           0x88BA
#define GL_BUFFER_ACCESS_ARB                        0x88BB
#define GL_BUFFER_MAPPED_ARB                        0x88BC
#define GL_BUFFER_MAP_POINTER_ARB                   0x88BD
#define GL_STREAM_DRAW_ARB                          0x88E0
#define GL_STREAM_READ_ARB                          0x88E1
#define GL_STREAM_COPY_ARB                          0x88E2
#define GL_STATIC_DRAW_ARB                          0x88E4
#define GL_STATIC_READ_ARB                          0x88E5
#define GL_STATIC_COPY_ARB                          0x88E6
#define GL_DYNAMIC_DRAW_ARB                         0x88E8
#define GL_DYNAMIC_READ_ARB                         0x88E9
#define GL_DYNAMIC_COPY_ARB                         0x88EA
#endif

#define pumpSetup2( name, typename, getmethod )                             \
    typename name##Ptr;                                                     \
    GLubyte * name##Data = NULL;                                            \
    UInt32 name##Size = 0;                                                  \
                                                                            \
    name##Ptr = geo->getmethod();                                           \
    if ( name##Ptr != NullFC )                                              \
    {                                                                       \
        name##Data = name##Ptr->getData();                                  \
        name##Size = name##Ptr->getSize() * name##Ptr->getFormatSize() * name##Ptr->getDimension(); \
    }

GeoVBO::GeoVBO(Window *win, Geometry *geo) :
    _win(win),
    _geo(geo),
    _positions(0),
    _normals(0),
    _colors(0),
    _secColors(0),
    _texCoords(0),
    _texCoords1(0),
    _texCoords2(0),
    _texCoords3(0),
    _texCoords4(0),
    _texCoords5(0),
    _texCoords6(0),
    _texCoords7(0),
    _indices(0)
{
    update();
}

GeoVBO::~GeoVBO()
{
    // well ATI supports the GL_ARB_vertex_buffer_object extension but
    // not the ARB functions ...

    void (OSG_APIENTRY*_glDeleteBuffersARB)
                  (GLsizei, const GLuint *)=
            (void (OSG_APIENTRY*)(GLsizei, const GLuint *))
             _win->getFunction(GeoPumpFactory::_funcglDeleteBuffers);

    if(_glDeleteBuffersARB == NULL)
    {
        _glDeleteBuffersARB = (void (OSG_APIENTRY*)(GLsizei, const GLuint *))
             _win->getFunction(GeoPumpFactory::_funcglDeleteBuffersARB);
    }

    if(_positions != 0)
        _glDeleteBuffersARB(1, &_positions);

    if(_normals != 0)
        _glDeleteBuffersARB(1, &_normals);

    if(_colors != 0)
        _glDeleteBuffersARB(1, &_colors);

    if(_secColors != 0)
        _glDeleteBuffersARB(1, &_secColors);

    if(_texCoords != 0)
        _glDeleteBuffersARB(1, &_texCoords);

    if(_texCoords1 != 0)
        _glDeleteBuffersARB(1, &_texCoords1);

    if(_texCoords2 != 0)
        _glDeleteBuffersARB(1, &_texCoords2);

    if(_texCoords3 != 0)
        _glDeleteBuffersARB(1, &_texCoords3);

    if(_texCoords4 != 0)
        _glDeleteBuffersARB(1, &_texCoords4);

    if(_texCoords5 != 0)
        _glDeleteBuffersARB(1, &_texCoords5);

    if(_texCoords6 != 0)
        _glDeleteBuffersARB(1, &_texCoords6);

    if(_texCoords7 != 0)
        _glDeleteBuffersARB(1, &_texCoords7);

    if(_indices != 0)
        _glDeleteBuffersARB(1, &_indices);
}

void GeoVBO::update(void)
{
    GLenum usage = GL_STATIC_DRAW_ARB;

    Geometry *geo = _geo;

    pumpSetup2(Positions  , GeoPositionsPtr , getPositions );
    pumpSetup2(Colors     , GeoColorsPtr    , getColors    );
    pumpSetup2(SecColors  , GeoColorsPtr    , getSecondaryColors );
    pumpSetup2(TexCoords  , GeoTexCoordsPtr , getTexCoords  );
    pumpSetup2(TexCoords1 , GeoTexCoordsPtr , getTexCoords1 );
    pumpSetup2(TexCoords2 , GeoTexCoordsPtr , getTexCoords2 );
    pumpSetup2(TexCoords3 , GeoTexCoordsPtr , getTexCoords3 );
    pumpSetup2(TexCoords4 , GeoTexCoordsPtr , getTexCoords4 );
    pumpSetup2(TexCoords5 , GeoTexCoordsPtr , getTexCoords5 );
    pumpSetup2(TexCoords6 , GeoTexCoordsPtr , getTexCoords6 );
    pumpSetup2(TexCoords7 , GeoTexCoordsPtr , getTexCoords7 );
    pumpSetup2(Normals    , GeoNormalsPtr   , getNormals    );

    pumpSetup2(Indices    , GeoIndicesPtr   , getIndices    );

    void (OSG_APIENTRY*_glGenBuffersARB)
                  (GLsizei, GLuint *)=
            (void (OSG_APIENTRY*)(GLsizei, GLuint *))
             _win->getFunction(GeoPumpFactory::_funcglGenBuffers);

    if(_glGenBuffersARB == NULL)
    {
        _glGenBuffersARB = (void (OSG_APIENTRY*)(GLsizei, GLuint *))
             _win->getFunction(GeoPumpFactory::_funcglGenBuffersARB);
    }

    void (OSG_APIENTRY*_glDeleteBuffersARB)
                  (GLsizei, const GLuint *)=
            (void (OSG_APIENTRY*)(GLsizei, const GLuint *))
             _win->getFunction(GeoPumpFactory::_funcglDeleteBuffers);

    if(_glDeleteBuffersARB == NULL)
    {
        _glDeleteBuffersARB = (void (OSG_APIENTRY*)(GLsizei, const GLuint *))
             _win->getFunction(GeoPumpFactory::_funcglDeleteBuffersARB);
    }

    void (OSG_APIENTRY*_glBindBufferARB)
                  (GLenum, GLuint)=
            (void (OSG_APIENTRY*)(GLenum, GLuint))
             _win->getFunction(GeoPumpFactory::_funcglBindBuffer);

    if(_glBindBufferARB == NULL)
    {
        _glBindBufferARB = (void (OSG_APIENTRY*)(GLenum, GLuint))
             _win->getFunction(GeoPumpFactory::_funcglBindBufferARB);
    }

    // typedef ptrdiff_t GLsizeiptrARB;
    void (OSG_APIENTRY*_glBufferDataARB)
                  (GLenum, ptrdiff_t, const GLvoid *, GLenum)=
            (void (OSG_APIENTRY*)(GLenum, ptrdiff_t, const GLvoid *, GLenum))
             _win->getFunction(GeoPumpFactory::_funcglBufferData);

    if(_glBufferDataARB == NULL)
    {
        _glBufferDataARB = (void (OSG_APIENTRY*)(GLenum, ptrdiff_t, const GLvoid *, GLenum))
             _win->getFunction(GeoPumpFactory::_funcglBufferDataARB);
    }

#if 0
    // typedef ptrdiff_t GLsizeiptrARB;
    // typedef ptrdiff_t GLintptrARB;
    void (OSG_APIENTRY*_glBufferSubDataARB)
                  (GLenum, ptrdiff_t, ptrdiff_t, const GLvoid *)=
            (void (OSG_APIENTRY*)(GLenum, ptrdiff_t, ptrdiff_t, const GLvoid *))
             _win->getFunction(GeoPumpFactory::_funcglBufferSubDataARB);
#endif

    if(PositionsData)
    {
        if(_positions != 0)
            _glDeleteBuffersARB(1, &_positions);

        // calling _glBufferSubDataARB for changed data increases the
        // memory usage! why?
        _glGenBuffersARB(1, &_positions);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _positions);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, PositionsSize, PositionsData, usage);
    }
    else
    {
        if(_positions != 0)
        {
            _glDeleteBuffersARB(1, &_positions);
            _positions = 0;
        }
    }

    if(NormalsData)
    {
        if(_normals != 0)
            _glDeleteBuffersARB(1, &_normals);
    
        _glGenBuffersARB(1, &_normals);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _normals);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, NormalsSize, NormalsData, usage);
    }
    else
    {
        if(_normals != 0)
        {
            _glDeleteBuffersARB(1, &_normals);
            _normals = 0;
        }
    }

    if(ColorsData)
    {
        if(_colors != 0)
            _glDeleteBuffersARB(1, &_colors);

        _glGenBuffersARB(1, &_colors);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _colors);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, ColorsSize, ColorsData, usage);
    }
    else
    {
        if(_colors != 0)
        {
            _glDeleteBuffersARB(1, &_colors);
            _colors = 0;
        }
    }

    if(SecColorsData)
    {
        if(_secColors != 0)
            _glDeleteBuffersARB(1, &_secColors);

        _glGenBuffersARB(1, &_secColors);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _secColors);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, SecColorsSize, SecColorsData, usage);
    }
    else
    {
        if(_secColors != 0)
        {
            _glDeleteBuffersARB(1, &_secColors);
            _secColors = 0;
        }
    }

    if(TexCoordsData)
    {
        if(_texCoords != 0)
            _glDeleteBuffersARB(1, &_texCoords);

        _glGenBuffersARB(1, &_texCoords);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoordsSize, TexCoordsData, usage);
    }
    else
    {
        if(_texCoords != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords);
            _texCoords = 0;
        }
    }

    if(TexCoords1Data)
    {
        if(_texCoords1 != 0)
            _glDeleteBuffersARB(1, &_texCoords1);

        _glGenBuffersARB(1, &_texCoords1);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords1);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoords1Size, TexCoords1Data, usage);
    }
    else
    {
        if(_texCoords1 != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords1);
            _texCoords1 = 0;
        }
    }

    if(TexCoords2Data)
    {
        if(_texCoords2 != 0)
            _glDeleteBuffersARB(1, &_texCoords2);

        _glGenBuffersARB(1, &_texCoords2);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords2);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoords2Size, TexCoords2Data, usage);
    }
    else
    {
        if(_texCoords2 != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords2);
            _texCoords2 = 0;
        }
    }

    if(TexCoords3Data)
    {
        if(_texCoords3 != 0)
            _glDeleteBuffersARB(1, &_texCoords3);

        _glGenBuffersARB(1, &_texCoords3);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords3);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoords3Size, TexCoords3Data, usage);
    }
    else
    {
        if(_texCoords3 != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords3);
            _texCoords3 = 0;
        }
    }

    if(TexCoords4Data)
    {
        if(_texCoords4 != 0)
            _glDeleteBuffersARB(1, &_texCoords4);

        _glGenBuffersARB(1, &_texCoords4);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords4);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoords4Size, TexCoords4Data, usage);
    }
    else
    {
        if(_texCoords4 != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords4);
            _texCoords4 = 0;
        }
    }

    if(TexCoords5Data)
    {
        if(_texCoords5 != 0)
            _glDeleteBuffersARB(1, &_texCoords5);

        _glGenBuffersARB(1, &_texCoords5);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords5);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoords5Size, TexCoords5Data, usage);
    }
    else
    {
        if(_texCoords5 != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords5);
            _texCoords5 = 0;
        }
    }

    if(TexCoords6Data)
    {
        if(_texCoords6 != 0)
            _glDeleteBuffersARB(1, &_texCoords6);

        _glGenBuffersARB(1, &_texCoords6);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords6);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoords6Size, TexCoords6Data, usage);
    }
    else
    {
        if(_texCoords6 != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords6);
            _texCoords6 = 0;
        }
    }

    if(TexCoords7Data)
    {
        if(_texCoords7 != 0)
            _glDeleteBuffersARB(1, &_texCoords7);

        _glGenBuffersARB(1, &_texCoords7);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords7);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, TexCoords7Size, TexCoords7Data, usage);
    }
    else
    {
        if(_texCoords7 != 0)
        {
            _glDeleteBuffersARB(1, &_texCoords7);
            _texCoords7 = 0;
        }
    }

    if(IndicesData)
    {
        if(_indices != 0)
            _glDeleteBuffersARB(1, &_indices);

        _glGenBuffersARB(1, &_indices);
        _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indices);
        _glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndicesSize, IndicesData, usage);
    }
    else
    {
        if(_indices != 0)
        {
            _glDeleteBuffersARB(1, &_indices);
            _indices = 0;
        }
    }

    _glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}

void GeoVBO::draw(void)
{
    void (OSG_APIENTRY*_glBindBufferARB)
                  (GLenum, GLuint)=
            (void (OSG_APIENTRY*)(GLenum, GLuint))
             _win->getFunction(GeoPumpFactory::_funcglBindBuffer);

    if(_glBindBufferARB == NULL)
    {
        _glBindBufferARB = (void (OSG_APIENTRY*)(GLenum, GLuint))
             _win->getFunction(GeoPumpFactory::_funcglBindBufferARB);
    }

    Geometry *geo = _geo;
    Int16 modified=0;

    GeoPositionsPtr PositionsPtr = geo->getPositions();
    if (PositionsPtr != NullFC)
    {
        UInt32 PositionsStride = 0;
        if(!(PositionsStride = PositionsPtr->getStride()))
            PositionsStride = PositionsPtr->getFormatSize() * PositionsPtr->getDimension();

        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _positions);
        glVertexPointer(PositionsPtr->getDimension(), PositionsPtr->getFormat(),
                        PositionsStride, NULL);
        glEnableClientState(GL_VERTEX_ARRAY);
        modified|=(1<<0);
    }

    GeoNormalsPtr NormalsPtr = geo->getNormals();
    if (NormalsPtr != NullFC)
    {
        UInt32 NormalsStride = 0;
        if(!(NormalsStride = NormalsPtr->getStride()))
            NormalsStride = NormalsPtr->getFormatSize() * NormalsPtr->getDimension();

        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _normals);
        glNormalPointer(NormalsPtr->getFormat(), NormalsStride, NULL);
        glEnableClientState(GL_NORMAL_ARRAY);
        modified|=(1<<3);
    }

    GeoColorsPtr ColorsPtr = geo->getColors();
    if (ColorsPtr != NullFC)
    {
        UInt32 ColorsStride = 0;
        if(!(ColorsStride = ColorsPtr->getStride()))
            ColorsStride = ColorsPtr->getFormatSize() * ColorsPtr->getDimension();

        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _colors);
        glColorPointer(ColorsPtr->getDimension(), ColorsPtr->getFormat(),
                       ColorsStride, NULL);
        glEnableClientState(GL_COLOR_ARRAY);
        modified|=(1<<1);
    }

    GeoColorsPtr SecColorsPtr = geo->getSecondaryColors();
    if (SecColorsPtr != NullFC)
    {
        if (_win->hasExtension(GeoPumpFactory::_extSecondaryColor))
        {
            UInt32 SecColorsStride = 0;
            if(!(SecColorsStride = SecColorsPtr->getStride()))
                SecColorsStride = SecColorsPtr->getFormatSize() * SecColorsPtr->getDimension();

            void (OSG_APIENTRY*_glSecondaryColorPointerEXT)
                  (GLint size,GLenum type,GLsizei stride,const GLvoid *pointer)=
            (void (OSG_APIENTRY*)(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer))
             _win->getFunction(GeoPumpFactory::_funcglSecondaryColorPointer);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _secColors);
            _glSecondaryColorPointerEXT(SecColorsPtr->getDimension(),
                                       SecColorsPtr->getFormat(),
                                       SecColorsStride, NULL);
            glEnableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
            modified|=(1<<2);
        }
        else
            FWARNING(("VBO::draw: Window has no Secondary Color extension\n"));
    }

    GeoTexCoordsPtr TexCoordsPtr = geo->getTexCoords();
    if (TexCoordsPtr != NullFC)
    {
        UInt32 TexCoordsStride = 0;
        if(!(TexCoordsStride = TexCoordsPtr->getStride()))
            TexCoordsStride = TexCoordsPtr->getFormatSize() * TexCoordsPtr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        else
        {
            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        modified|=(1<<4);
    }

    GeoTexCoordsPtr TexCoords1Ptr = geo->getTexCoords1();
    if (TexCoords1Ptr != NullFC)
    {
        UInt32 TexCoords1Stride = 0;
        if(!(TexCoords1Stride = TexCoords1Ptr->getStride()))
            TexCoords1Stride = TexCoords1Ptr->getFormatSize() * TexCoords1Ptr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE1_ARB);
            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords1);
            glTexCoordPointer (TexCoords1Ptr->getDimension(), TexCoords1Ptr->getFormat(),
                               TexCoords1Stride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<5);
        }
        else
            FWARNING(("VBO::draw: Window has no MultitextureARB extension\n"));
    }

    GeoTexCoordsPtr TexCoords2Ptr = geo->getTexCoords2();
    if (TexCoords2Ptr != NullFC)
    {
        UInt32 TexCoords2Stride = 0;
        if(!(TexCoords2Stride = TexCoords2Ptr->getStride()))
            TexCoords2Stride = TexCoords2Ptr->getFormatSize() * TexCoords2Ptr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE2_ARB);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords2);
            glTexCoordPointer (TexCoords2Ptr->getDimension(), TexCoords2Ptr->getFormat(),
                               TexCoords2Stride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<6);
        }
        else
            FWARNING(("VBO::draw: Window has no MultitextureARB extension\n"));
    }

    GeoTexCoordsPtr TexCoords3Ptr = geo->getTexCoords3();
    if (TexCoords3Ptr != NullFC)
    {
        UInt32 TexCoords3Stride = 0;
        if(!(TexCoords3Stride = TexCoords3Ptr->getStride()))
            TexCoords3Stride = TexCoords3Ptr->getFormatSize() * TexCoords3Ptr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE3_ARB);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords3);
            glTexCoordPointer (TexCoords3Ptr->getDimension(), TexCoords3Ptr->getFormat(),
                               TexCoords3Stride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<7);
        }
        else
            FWARNING(("VBO::draw: Window has no MultitextureARB extension\n"));
    }

    GeoTexCoordsPtr TexCoords4Ptr = geo->getTexCoords4();
    if (TexCoords4Ptr != NullFC)
    {
        UInt32 TexCoords4Stride = 0;
        if(!(TexCoords4Stride = TexCoords4Ptr->getStride()))
            TexCoords4Stride = TexCoords4Ptr->getFormatSize() * TexCoords4Ptr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE4_ARB);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords4);
            glTexCoordPointer (TexCoords4Ptr->getDimension(), TexCoords4Ptr->getFormat(),
                               TexCoords4Stride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<8);
        }
        else
            FWARNING(("VBO::draw: Window has no MultitextureARB extension\n"));
    }

    GeoTexCoordsPtr TexCoords5Ptr = geo->getTexCoords5();
    if (TexCoords5Ptr != NullFC)
    {
        UInt32 TexCoords5Stride = 0;
        if(!(TexCoords5Stride = TexCoords5Ptr->getStride()))
            TexCoords5Stride = TexCoords5Ptr->getFormatSize() * TexCoords5Ptr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE5_ARB);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords5);
            glTexCoordPointer (TexCoords5Ptr->getDimension(), TexCoords5Ptr->getFormat(),
                               TexCoords5Stride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<9);
        }
        else
            FWARNING(("VBO::draw: Window has no MultitextureARB extension\n"));
    }

    GeoTexCoordsPtr TexCoords6Ptr = geo->getTexCoords6();
    if (TexCoords6Ptr != NullFC)
    {
        UInt32 TexCoords6Stride = 0;
        if(!(TexCoords6Stride = TexCoords6Ptr->getStride()))
                TexCoords6Stride = TexCoords6Ptr->getFormatSize() * TexCoords6Ptr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE6_ARB);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords6);
            glTexCoordPointer (TexCoords6Ptr->getDimension(), TexCoords6Ptr->getFormat(),
                               TexCoords6Stride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<10);
        }
        else
            FWARNING(("VBO::draw: Window has no MultitextureARB extension\n"));
    }

    GeoTexCoordsPtr TexCoords7Ptr = geo->getTexCoords7();
    if (TexCoords7Ptr != NullFC)
    {
        UInt32 TexCoords7Stride = 0;
        if(!(TexCoords7Stride = TexCoords7Ptr->getStride()))
                TexCoords7Stride = TexCoords7Ptr->getFormatSize() * TexCoords7Ptr->getDimension();

        if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE7_ARB);

            _glBindBufferARB(GL_ARRAY_BUFFER_ARB, _texCoords7);
            glTexCoordPointer (TexCoords7Ptr->getDimension(), TexCoords7Ptr->getFormat(),
                               TexCoords7Stride, NULL);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            modified|=(1<<11);
        }
        else
            FWARNING(("VBO::draw: Window has no MultitextureARB extension\n"));
    }

    pumpSetup(Lengths    , GeoPLengthsPtr  , getLengths    );
    pumpSetup(Types      , GeoPTypesPtr    , getTypes      );
    pumpSetup(Indices    , GeoIndicesPtr   , getIndices    );
    IndicesData = IndicesData; // workaround for irix compiler.
    
    UInt32 lendummy;
    UInt32 LengthsSize;
    bool   len16 = false;

    if(LengthsPtr != NullFC && LengthsData != NULL)
    {
        LengthsSize = LengthsPtr->getSize();
        len16 = (LengthsPtr->getFormatSize() == 2);
    }
    else
    {
        LengthsSize = 1;
        LengthsData = (UChar8*) &lendummy;
        lendummy = PositionsPtr->getSize();
    }

    UInt32 LengthsInd = 0, TypesInd = 0, IndicesInd = 0, 
           IndicesSize = IndicesPtr->getSize();

    void (OSG_APIENTRY *osgGLDrawRangeElementsEXT)(GLenum mode, GLuint start,
           GLuint end, GLsizei count, GLenum type, const GLvoid*indices) =
    (void (OSG_APIENTRY *)(GLenum mode, GLuint start,
           GLuint end, GLsizei count, GLenum type, const GLvoid*indices))
            _win->getFunction(GeoPumpFactory::_funcglDrawRangeElementsEXT);

    _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indices);

    if(len16 == false)
    {
        for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
        {
            UInt32 count  = *(UInt32*)(LengthsData + LengthsInd * LengthsStride);
            // for vbo's we need only a offset!
            UInt8 *vind = ((UInt8 *) NULL) + IndicesStride * IndicesInd;
            IndicesInd += count;

            if(_win->hasExtension(GeoPumpFactory::_extDrawRangeElements))
            {
                osgGLDrawRangeElementsEXT(*(TypesData + TypesInd++ * TypesStride),
                                          geo->getLowindices() [LengthsInd], 
                                          geo->getHighindices()[LengthsInd], 
                                          count,
                                          IndicesPtr->getFormat(), 
                                          vind);
            }
            else
            {
                // hope this still works
                glDrawElements(*(TypesData + TypesInd++ * TypesStride),
                               count,
                               IndicesPtr->getFormat(),
                               vind);
            }
        }
    }
    else if(len16 == true)
    {
        for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
        {
            UInt16 count  = *(UInt16*)(LengthsData + LengthsInd * LengthsStride);
            // for vbo's we need only a offset!
            UInt8 *vind = ((UInt8 *) NULL) + IndicesStride * IndicesInd;
            IndicesInd += count;

            if(_win->hasExtension(GeoPumpFactory::_extDrawRangeElements))
            {
                osgGLDrawRangeElementsEXT(*(TypesData + TypesInd++ * TypesStride),
                                          0, 
                                          IndicesSize, 
                                          count,
                                          IndicesPtr->getFormat(), 
                                          vind);
            }
            else
            {
                // hope this still works
                glDrawElements(*(TypesData + TypesInd++ * TypesStride),
                               count,
                               IndicesPtr->getFormat(),
                               vind);
            }
        }
    }
    else
    {
        FWARNING(("VBO::draw: unknown Lengths format size\n"));
    }

    if(modified&(1<<0)) glDisableClientState(GL_VERTEX_ARRAY);
    if(modified&(1<<1)) glDisableClientState(GL_COLOR_ARRAY);
    if(modified&(1<<2)) glDisableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
    if(modified&(1<<3)) glDisableClientState(GL_NORMAL_ARRAY);

    if (_win->hasExtension(GeoPumpFactory::_extMultitexture))
    {
        void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
        (void (OSG_APIENTRY*) (GLenum type))_win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);

        if(modified&(1<<4))
        {
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<5))
        {
            _glClientActiveTextureARB(GL_TEXTURE1_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<6))
        {
            _glClientActiveTextureARB(GL_TEXTURE2_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(modified&(1<<7))
        {
            _glClientActiveTextureARB(GL_TEXTURE3_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<8))
        {
            _glClientActiveTextureARB(GL_TEXTURE4_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<9))
        {
            _glClientActiveTextureARB(GL_TEXTURE5_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<10))
        {
            _glClientActiveTextureARB(GL_TEXTURE6_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if(modified&(1<<11))
        {
            _glClientActiveTextureARB(GL_TEXTURE7_ARB);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
    else
    {
        if(modified&(1<<4)) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    _glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
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
    static Char8 cvsid_hpp       [] = OSGGEOPUMPFACTORY_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOPUMPFACTORY_INLINE_CVSID;
}

