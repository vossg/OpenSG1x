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

UInt32 GeoPumpFactory::_funcglSecondaryColorPointer;
UInt32 GeoPumpFactory::_funcglClientActiveTextureARB;

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


/* index is organised as follows:
   there are 2^7-1+3 different functions
   The first (0) is for invalid (empty) geometry
   The next 127 define all multi-indexed functions,
   the last 2 define non-indexed and single-indexed
   geometries
*/

GeoPumpFactory::Index GeoPumpFactory::getIndex( Geometry * geo)
{
    if (geo->getPositions() == NullFC ||
       !geo->getPositions()->getData() ) return 0; //INVALID

    if (geo->getTypes() == NullFC || !geo->getTypes()->getData() ||
        geo->getTypes()->getSize() == 0) return 0; //INVALID

    if (geo->getIndices() == NullFC) return 128; //NON_INDEXED
    if (geo->getIndexMapping().size() < 2) return 129; //SINGLE_INDEXED

    UInt32 uiIndexMask = 0;

    for(Int32 i = 0; i < geo->getIndexMapping().size(); ++i)
    {
        uiIndexMask |= geo->getIndexMapping()[i];
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
#ifndef GL_SECONDARY_COLOR_ARRAY_EXT
#define GL_SECONDARY_COLOR_ARRAY_EXT 0x845E
#endif

#ifndef GL_TEXTURE0_ARB

#define GL_TEXTURE0_ARB 0x84C0
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


/*! MasterPump for empty geometry, does nothing
 */

void GeoPump0(Window   *OSG_CHECK_ARG(win),
              Geometry *OSG_CHECK_ARG(geo))
{
    return;
}

#define pumpSetup( name, typename, getmethod )                              \
    typename name##Ptr;                                                     \
    GLubyte * name##Data = NULL;                                            \
    UInt32 name##Stride;                                                    \
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
    pumpSetup(Normals    , GeoNormalsPtr   , getNormals    );

    pumpSetup(Lengths    , GeoPLengthsPtr  , getLengths    );
    pumpSetup(Types      , GeoPTypesPtr    , getTypes      );

    if (PositionsData)
    {        
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(PositionsPtr->getDimension(), PositionsPtr->getFormat(),
                        PositionsStride, PositionsData);
        modified|=(1<<0);
    }

    if (ColorsData)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(ColorsPtr->getDimension(), ColorsPtr->getFormat(),
                       ColorsStride, ColorsData);
        modified|=(1<<1);        
    }

    if (SecColorsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extSecondaryColor))
        {
            glEnableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
             void (OSG_APIENTRY*_glSecondaryColorPointerEXT)
                  (GLint size,GLenum type,GLsizei stride,const GLvoid *pointer)=
            (void (OSG_APIENTRY*)(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer))
             win->getFunction(GeoPumpFactory::_funcglSecondaryColorPointer);

            _glSecondaryColorPointerEXT(SecColorsPtr->getDimension(),
                                       SecColorsPtr->getFormat(),
                                       SecColorsStride, SecColorsData);
            modified|=(1<<2);
        }
        else
            FWARNING(("GeoPump128: Window has no Secondary Color extension\n"));
    }


    if (NormalsData)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(NormalsPtr->getFormat(), NormalsStride, NormalsData);
        modified|=(1<<3);
    }

    if (TexCoordsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
        }
        else
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
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
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoords1Ptr->getDimension(), TexCoords1Ptr->getFormat(),
                               TexCoords1Stride, TexCoords1Data);
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
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoords2Ptr->getDimension(), TexCoords2Ptr->getFormat(),
                               TexCoords2Stride, TexCoords2Data);
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
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoords3Ptr->getDimension(), TexCoords3Ptr->getFormat(),
                               TexCoords3Stride, TexCoords3Data);
            modified|=(1<<7);
        }
        else
            FWARNING(("GeoPump128: Window has no MultitextureARB extension\n"));
    }

    UInt32 lendummy;
    UInt32 LengthsSize;

    if(LengthsPtr != NullFC && LengthsData != NULL)
    {
        LengthsSize = LengthsPtr->getSize();
    }
    else
    {
        LengthsSize = 1;
        LengthsData = (UChar8*) &lendummy;
        lendummy = PositionsPtr->getSize();
    }

    UInt32 LengthsInd,TypesInd = 0;
    UInt32 first=0;

    for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
    {
        UInt32 count = *(UInt32*)(LengthsData + LengthsInd * LengthsStride);
        glDrawArrays(*(TypesData + TypesInd++ * TypesStride),first,count);
        first+=count;
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
    }
    else
    {
        if(modified&(1<<4)) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}

/*! MasterPump for single-indexed geometry
 */

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
    pumpSetup(Normals    , GeoNormalsPtr   , getNormals   );

    pumpSetup(Lengths    , GeoPLengthsPtr  , getLengths  );
    pumpSetup(Types      , GeoPTypesPtr    , getTypes    );
    pumpSetup(Indices    , GeoIndicesPtr   , getIndices  );

    if (PositionsData)
    {        
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(PositionsPtr->getDimension(), PositionsPtr->getFormat(),
                        PositionsStride, PositionsData);
        modified|=(1<<0);
    }

    if (ColorsData)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(ColorsPtr->getDimension(), ColorsPtr->getFormat(),
                       ColorsStride, ColorsData);
        modified|=(1<<1);        
    }

    if (SecColorsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extSecondaryColor))
        {
            glEnableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
             void (OSG_APIENTRY*_glSecondaryColorPointerEXT)
                  (GLint size,GLenum type,GLsizei stride,const GLvoid *pointer)=
            (void (OSG_APIENTRY*)(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer))
             win->getFunction(GeoPumpFactory::_funcglSecondaryColorPointer);

            _glSecondaryColorPointerEXT(SecColorsPtr->getDimension(),
                                       SecColorsPtr->getFormat(),
                                       SecColorsStride, SecColorsData);
            modified|=(1<<2);
        }
        else
            FWARNING(("GeoPump129: Window has no Secondary Color extension\n"));
    }


    if (NormalsData)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(NormalsPtr->getFormat(), NormalsStride, NormalsData);
        modified|=(1<<3);
    }

    if (TexCoordsData)
    {
        if (win->hasExtension(GeoPumpFactory::_extMultitexture))
        {
            void (OSG_APIENTRY*_glClientActiveTextureARB) (GLenum type)=
            (void (OSG_APIENTRY*) (GLenum type))win->getFunction(GeoPumpFactory::_funcglClientActiveTextureARB);
            _glClientActiveTextureARB(GL_TEXTURE0_ARB);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
        }
        else
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoordsPtr->getDimension(), TexCoordsPtr->getFormat(),
                               TexCoordsStride, TexCoordsData);
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
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoords1Ptr->getDimension(), TexCoords1Ptr->getFormat(),
                               TexCoords1Stride, TexCoords1Data);
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
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoords2Ptr->getDimension(), TexCoords2Ptr->getFormat(),
                               TexCoords2Stride, TexCoords2Data);
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
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (TexCoords3Ptr->getDimension(), TexCoords3Ptr->getFormat(),
                               TexCoords3Stride, TexCoords3Data);
            modified|=(1<<7);
        }
        else
            FWARNING(("GeoPump129: Window has no MultitextureARB extension\n"));
    }

    UInt32 lendummy;
    UInt32 LengthsSize;

    if(LengthsPtr != NullFC && LengthsData != NULL)
    {
        LengthsSize = LengthsPtr->getSize();
    }
    else
    {
        LengthsSize = 1;
        LengthsData = (UChar8*) &lendummy;
        lendummy = PositionsPtr->getSize();
    }

    UInt32 LengthsInd = 0,TypesInd = 0, IndicesInd = 0;

    for(LengthsInd = 0; LengthsInd < LengthsSize; LengthsInd++)
    {
        UInt32 count  = *(UInt32*)(LengthsData + LengthsInd * LengthsStride);
        UInt32 * vind = (UInt32*)(IndicesData + IndicesStride * IndicesInd);
        IndicesInd += count;

        glDrawElements(*(TypesData + TypesInd++ * TypesStride),count,
                        IndicesPtr->getFormat(),vind);
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
            Int16 ColorIndex  =  geo->calcMappingIndex( Geometry::MapColor );

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

#define rC ColorFunc     ( ColorData     + ColorStride     * vind[ColorIndex]     );
#define rS SecColorFunc  ( SecColorData  + SecColorStride  * vind[SecColorIndex]  );
#define rN NormalFunc    ( NormalData    + NormalStride    * vind[NormalIndex]    );
#define rT TexCoordsFunc ( TexCoordsData + TexCoordsStride * vind[TexCoordsIndex] );
#define rT1 TexCoords1Func( GL_TEXTURE1_ARB , TexCoords1Data + TexCoords1Stride * vind[TexCoords1Index] );
#define rT2 TexCoords2Func( GL_TEXTURE2_ARB , TexCoords2Data + TexCoords2Stride * vind[TexCoords2Index] );
#define rT3 TexCoords3Func( GL_TEXTURE3_ARB , TexCoords3Data + TexCoords3Stride * vind[TexCoords3Index] );

/*
    nmappings for sure is greater or equal than two because this is multi
    index geometry and there is for sure IndexData!!!
*/

#define defMultiGeoPump( func, init , render )                              \
void GeoPump##func( Window   *win,                                          \
                           Geometry *geo)                                   \
{                                                                           \
    if (win) ;                                                              \
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

GeoPumpFactory::GeoPump GeoPumpFactory::GeoPumps[130]={&GeoPump0,
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
&GeoPump121,&GeoPump122,&GeoPump123,&GeoPump124,&GeoPump125,&GeoPump126,&GeoPump127,&GeoPump128,&GeoPump129};

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

    _funcglSecondaryColorPointer = Window::registerFunction(OSG_DLSYM_UNDERSCORE"glSecondaryColorPointerEXT");
    _funcglClientActiveTextureARB = Window::registerFunction(OSG_DLSYM_UNDERSCORE"glClientActiveTextureARB");

    return true;
}
