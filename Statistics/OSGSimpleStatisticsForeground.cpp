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
#include <strstream>

#include <OSGConfig.h>
#include <OSGTXFFont.h>
#include <OSGViewport.h>

#include "OSGSimpleStatisticsForeground.h"

#include "OSGStatisticsDefaultFont.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGSimpleStatisticsForeground.cpp,v 1.2 2002/03/20 06:32:39 vossg Exp $";
    static char cvsid_hpp[] = OSGSIMPLESTATISTICSFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGSIMPLESTATISTICSFOREGROUND_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::SimpleStatisticsForeground
Background is the base class for all background clearing.  	 	
*/

/* static vars */

ImageP          SimpleStatisticsForeground::_textimage = NULL;
#ifndef WIN32
Text            SimpleStatisticsForeground::_text;
#endif

TextureChunkPtr SimpleStatisticsForeground::_texchunk;


/*----------------------- constructors & destructors ----------------------*/

//! Constructor

SimpleStatisticsForeground::SimpleStatisticsForeground(void) :
    Inherited()
{
}

//! Copy Constructor

SimpleStatisticsForeground::SimpleStatisticsForeground(const SimpleStatisticsForeground &source) :
    Inherited(source)
{
}

//! Destructor

SimpleStatisticsForeground::~SimpleStatisticsForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void SimpleStatisticsForeground::initMethod(void)
{
}

//! react to field changes

void SimpleStatisticsForeground::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void SimpleStatisticsForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SimpleStatisticsForeground NI" << endl;
}

/** Convenience function for access
 */

void SimpleStatisticsForeground::addElement( StatElemDescBase &desc, 
                                             char *format)
{
    getElementIDs().addValue(desc.getID());
    getFormats().addValue(format);
}

void SimpleStatisticsForeground::addElement( UInt32 id, char *format)
{
    getElementIDs().addValue(id);
    getFormats().addValue(format);
}


//! initialize the text 

void SimpleStatisticsForeground::initText(void)
{
#ifndef WIN32
    // create the text needed
    istrstream stream((char*)StatisticsDefaultFontData, 
                      StatisticsDefaultFontDataSize);
                       
    TXFFont *font = new TXFFont("StatisticsDefaultFont", stream);
    font->initFont();

    _text.setSize(1);
    font->createInstance(&_text);
    _text.setJustifyMajor(FIRST_JT);
    
    // create the TXF texture

    _textimage = new Image;
    _text.fillTXFImage(*_textimage);

    _texchunk = TextureChunk::create();
    
    beginEditCP(_texchunk);
    {
        _texchunk->setImage(_textimage);
        _texchunk->setWrapS(GL_CLAMP);
        _texchunk->setWrapT(GL_CLAMP);
        _texchunk->setEnvMode(GL_MODULATE);
    }
    endEditCP  (_texchunk);
#endif
}

/** \brief draw the statistics 
 */
    
void SimpleStatisticsForeground::draw(DrawActionBase *action, Viewport *port)
{
#ifndef WIN32
    if(_textimage == NULL)
        initText();
        
    Real32 pw = port->getPixelWidth();
    Real32 ph = port->getPixelHeight();

    if(pw < 1 || ph < 1)
        return;

    bool light = glIsEnabled(GL_LIGHTING);

    GLint fill;
    glGetIntegerv(GL_POLYGON_MODE, &fill);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

    bool depth = glIsEnabled( GL_DEPTH_TEST );
    glDisable( GL_DEPTH_TEST );

    bool colmat = glIsEnabled( GL_COLOR_MATERIAL );
    glDisable( GL_COLOR_MATERIAL );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    Real32 aspect = pw/ph;
    Real32 size = getSize();
    
    glOrtho(-0.5, -0.5 + ph / size * aspect, 
             1 - ph / size, 1, 
             0, 1);

    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // draw text 
    
    vector<string> stat;
    StatCollector *col = &getCollector();
    StatElem *el;
    
    if(getElementIDs().getSize() != 0)
    {
        for(UInt32 i = 0; i < getElementIDs().getSize(); ++i)
        {
            el = col->getElem(getElementIDs().getValue(i));
            if(el)
            {
                stat.resize(stat.size() + 1);
                string *str = stat.end() - 1;
                
                const char *format = NULL;
                if(i < getFormats().getSize())
                {
                    format = getFormats().getValue(i).c_str();
                }
    
                el->putToString(*str,format);
            }
        }        
    }
    else // fallback, show all elements
    {
        for(UInt32 i = 0; i < col->getNumOfElems(); ++i)
        {
            el = col->getElem(i,false);
            if(el)
            {
                stat.resize(stat.size() + 1);
                string *str = stat.end() - 1;
                el->putToString(*str);
            }
        }
    }
    
    vector<Pnt3f> pos;
    vector<Vec2f> tex;
    
    UInt32 n = _text.getTXFNVertices(stat);

    pos.resize(n);
    tex.resize(n);

    _text.fillTXFArrays(stat, &pos[0], &tex[0]);
    
    _texchunk->activate(action);
    
    glColor4fv((GLfloat*) getColor().getValuesRGBA());
    
    glBegin(GL_QUADS);
    
    for(UInt32 i = 0; i < n; i++)
    {
        glTexCoord2fv((GLfloat*)&tex[i]);
        glVertex3fv  ((GLfloat*)&pos[i]);
    }
    
    glEnd();
    
    _texchunk->deactivate(action);  

    glDisable( GL_ALPHA_TEST );
    glDisable( GL_BLEND );
        

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if ( depth )    glEnable( GL_DEPTH_TEST );
    if ( light )    glEnable( GL_LIGHTING );
    if ( colmat )   glEnable( GL_COLOR_MATERIAL );
    glPolygonMode( GL_FRONT_AND_BACK, fill );
#endif
}

