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

#ifdef OSG_HAS_SSTREAM
#include <sstream>
#else
#include <strstream>
#endif

#include <OSGNodePtr.h>
#include <OSGTXFFont.h>
#include <OSGViewport.h>

#include "OSGSimpleStatisticsForeground.h"

#include "OSGStatisticsDefaultFont.h"

OSG_USING_NAMESPACE

/*! \class osg::SimpleStatisticsForeground
    \ingroup GrpSystemWindowForegroundsStatistics
    
SimpleStatisticsForeground displays the Statistics info as simple text lines. 
See \ref PageSystemWindowForegroundStatisticsSimple for a description.

The format string for the given elements are stored in the _mfFormats Field,
the size and color used for all lines in _sfSize and _sfColor.
*/


/* static vars */

ImageP          SimpleStatisticsForeground::_textimage = NULL;
Text            SimpleStatisticsForeground::_text;

TextureChunkPtr SimpleStatisticsForeground::_texchunk;


/*----------------------- constructors & destructors ----------------------*/

SimpleStatisticsForeground::SimpleStatisticsForeground(void) :
    Inherited()
{
}

SimpleStatisticsForeground::SimpleStatisticsForeground(const SimpleStatisticsForeground &source) :
    Inherited(source)
{
}

SimpleStatisticsForeground::~SimpleStatisticsForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SimpleStatisticsForeground::initMethod(void)
{
}

void SimpleStatisticsForeground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SimpleStatisticsForeground::dump(     UInt32    , 
                         const BitVector) const
{
    SLOG << "Dump SimpleStatisticsForeground NI" << std::endl;
}

/*! Convenience function to add an element and format.
*/
void SimpleStatisticsForeground::addElement(StatElemDescBase &desc, 
                                             const char *format)
{
    getElementIDs().push_back(desc.getID());
    getFormats().push_back(format ? format : "");
}

/*! Convenience function to add an element and format.
*/
void SimpleStatisticsForeground::addElement(UInt32 id, 
                                             const char *format)
{
    getElementIDs().push_back(id);
    getFormats().push_back(format ? format : "");
}


/*! Initialize the text used. It is compiled into the library as 
    StatisticsDefaultFontData and used as a TXF font.
*/
void SimpleStatisticsForeground::initText(void)
{
    // create the text needed
#ifdef OSG_HAS_SSTREAM
    std::istringstream stream((char*)StatisticsDefaultFontData, 
                              std::istringstream::in | 
                              std::istringstream::out);
#else
    std::istrstream stream((char*)StatisticsDefaultFontData, 
                           StatisticsDefaultFontDataSize);
#endif
                       
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
}

/*! Draw the statistics lines.
*/
void SimpleStatisticsForeground::draw(DrawActionBase *action, Viewport *port)
{
    if(_textimage == NULL)
        initText();
        
    Real32 pw = port->getPixelWidth();
    Real32 ph = port->getPixelHeight();

    if(pw < 1 || ph < 1)
        return;

    bool light = glIsEnabled(GL_LIGHTING);

    GLint fill;
    glGetIntegerv(GL_POLYGON_MODE, &fill);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    bool depth = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    bool colmat = glIsEnabled(GL_COLOR_MATERIAL);
    glDisable(GL_COLOR_MATERIAL);

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
    
    std::vector<std::string> stat;
    StatCollector *col = &getCollector();
    StatElem *el;
    
    if(getElementIDs().size() != 0)
    {
        for(UInt32 i = 0; i < getElementIDs().size(); ++i)
        {
            el = col->getElem(getElementIDs()[i]);
            if(el)
            {
                stat.resize(stat.size() + 1);
                std::vector<std::string>::iterator str = stat.end() - 1;
                
                const char *format = NULL;
                if(i < getFormats().size() && getFormats()[i].length())
                {
                    format = getFormats()[i].c_str();
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
                std::vector<std::string>::iterator str = stat.end() - 1;
                el->putToString(*str);
            }
        }
    }
    
    std::vector<Pnt3f> pos;
    std::vector<Vec2f> tex;
    
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

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
        

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if (depth)    
        glEnable(GL_DEPTH_TEST);
    if (light)    
        glEnable(GL_LIGHTING);
    if (colmat)   
        glEnable(GL_COLOR_MATERIAL);
    glPolygonMode(GL_FRONT_AND_BACK, fill);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGSimpleStatisticsForeground.cpp,v 1.11 2002/08/07 04:04:13 vossg Exp $";
    static char cvsid_hpp[] = OSGSIMPLESTATISTICSFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGSIMPLESTATISTICSFOREGROUND_INLINE_CVSID;
}
