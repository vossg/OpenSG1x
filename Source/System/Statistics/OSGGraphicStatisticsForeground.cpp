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
#include <iostream>

#ifdef OSG_HAS_SSTREAM
#include <sstream>
#else
#include <strstream>
#endif
#include <OSGConfig.h>
#include <OSGTXFFont.h>
#include <OSGNodePtr.h>
#include <OSGViewport.h>
#include "OSGGraphicStatisticsFont.h"

#include "OSGStatElem.h"
#include "OSGGraphicStatisticsForeground.h"
#include "OSGGL.h"

//#include "GL/glut.h"
OSG_USING_NAMESPACE

/* static vars */
ImagePtr GraphicStatisticsForeground::          _textimage = NullFC;
Text GraphicStatisticsForeground::              _text;
TextureChunkPtr GraphicStatisticsForeground::   _texchunk;

/*! \class osg::GraphicStatisticsForeground
    \ingroup GrpSystemWindowForegroundsStatistics
    
GraphicStatisticsForeground displays the Statistics info as graphical displays. 
See \ref PageSystemWindowForegroundStatisticsGraphic for a description.

The different parameters for all the displays are spread over a lot of fields.
Thus it is stringly advised to use the addElement and removeElement convenience
functions to add and remove elements, to ensure consistency.

The _sfLineWidth, _sfBackgroundColor, _sfBackgroundEnabled and _sfBorderEnabled
Fields control the parameters used for all displays.

*/

/*----------------------- constructors & destructors ----------------------*/
GraphicStatisticsForeground::GraphicStatisticsForeground(void) :
    Inherited()
{
}

/* */
GraphicStatisticsForeground::GraphicStatisticsForeground(const GraphicStatisticsForeground &source) :
        Inherited(source)
{
}

/* */
GraphicStatisticsForeground::~GraphicStatisticsForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/
void GraphicStatisticsForeground::initMethod(void)
{
}

/* */
void GraphicStatisticsForeground::changed(BitVector whichField, UInt32)
{
    UInt32  i, n = getHistorySize().size();

    /* Save the data  */
    if(whichField & HistorySizeFieldMask)
    {
        _historyID.resize(n, 0);
        _history.resize(n);
        for(i = 0; i < n; i++)
        {
            if(_history[i].size() == 0)
            {
                _history[i].resize(getHistorySize()[i],
                                                   (getMaxValue()[i] - getMinValue()[i]) / 2.0);
            }
        }
    }
}

/* */
void GraphicStatisticsForeground::dump(UInt32, const BitVector) const
{
    SLOG << "Dump GraphicStatisticsForeground NI" << std::endl;
}

//! draws the forground
void GraphicStatisticsForeground::draw(DrawActionBase *action, Viewport *port)
{
    // Check the height and width of the window
    if(port->getPixelWidth() < 1 || port->getPixelHeight() < 1)
    {
        return;
    }

    // initialize the text texture
    if(_textimage == NullFC)
    {
        initText();
    }

    // Save the current OpenGL state
    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // Finished saving and setting the matrices
    // Enable Alpha Blending
    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Enable the scissor test
    glEnable(GL_SCISSOR_TEST);

    // Initialize the viewport
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    // set the standard line Width
    glLineWidth(getLineWidth());

    // Get the Collector
    StatCollector   *col = &getCollector();

    // temp StatElem
    StatElem        *el;

    // ratio = height / width
    //    Real32 ratio  =  ( (Real32)port->getPixelHeight()) / 
		//                     ((Real32) port->getPixelWidth());
    // temp Variables for the loop
    Vec2f           pos;
    Vec2f           size;

    // Loop over all selected elements
    for(UInt32 i = 0; i < getElementIDs().size(); ++i)
    {
        // get the StatElem and check whether it exists
        el = col->getElem(getElementIDs()[i]);
        if(!el)
        {
            continue;
        }

        glPushMatrix();

        // calculate position and size
        calcPosAndSize(i, port, &pos, &size);
        glTranslatef(pos[0], pos[1], 0.0);
        glScalef(size[0], size[1], 1.0);

        // calculate the pixel size of the display
        UInt32  pw = (UInt32) (port->getPixelWidth() * size[0]);
        UInt32  ph = (UInt32) (port->getPixelHeight() * size[1]);
        UInt32  px = (UInt32) (port->getPixelWidth() * pos[0]);
        UInt32  py = (UInt32) (port->getPixelHeight() * pos[1]);
        glScissor(px - 1, py - 1, pw + 2, ph + 2);

        //std::cout << pos << std::endl;
        //std::cout << size << std::endl;
        //std::cout << px << "/" << py << "/" << pw << "/" << ph
        //          << std::endl;
        // enable GL_POINT_SMOOTH
        glEnable(GL_POINT_SMOOTH);

        //select the Method to use for drawing
        switch(getDisplayType()[i])
        {
        case OSG_ANALOG:
            //draw an analog display
            drawAnalog(i, el, action, port);
            break;
        case OSG_BAR:
            //draw a bar display
            drawBar(i, el, action, port);
            break;
        case OSG_CHART:
            //draw a chart
            drawChart(i, el, action, port);
            break;
        case OSG_LINE_CHART:
            //draw a linechart
            drawLineChart(i, el, action, port);
            break;
        case OSG_TEXT:
            //draw a linechart
            drawText(i, el, action, port);
            break;

        default:
            break;
        }                                   //switch()

        glPopMatrix();
    }                                       //for()

    //reset OpenGL matrices
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // Restore all OpenGL states
    glPopAttrib();
}

//draw();

/* */
void GraphicStatisticsForeground::addElement(StatElemDescBase &desc,
                                             UInt32 displayType, Vec2f pos,
                                             Vec2f size, Color4f highColor,
                                             Color4f lowColor,
                                             Color4f currentColor,
                                             Real32 minValue, Real32 maxValue,
                                             UInt32 flags, UInt32 historySize,
                                             std::string description)
{
    /* get the ID of the StatElem to be added */
    // Save the given Data
    getElementIDs().push_back(desc.getID());
    getDisplayType().push_back(displayType);
    getPos().push_back(pos);
    getSize().push_back(size);
    getColorMax().push_back(highColor);
    getColorMin().push_back(lowColor);
    getColorCurrent().push_back(currentColor);
    getMinValue().push_back(minValue);
    getMaxValue().push_back(maxValue);
    getFlags().push_back(flags);
    getHistorySize().push_back(historySize ? historySize : 25);
    getDescription().push_back(description);

    // changed() must be called (automatically)
    // to sync the _history/_historyID values
}

//addElement()

/*******************************************************/
void GraphicStatisticsForeground::removeElement(StatElemDescBase &desc)
{
    UInt32  id = desc.getID();
    UInt32  i = 0, n = getElementIDs().size();

    for(i = 0; n; i++)
    {
        if(getElementIDs()[i] == id)
            break;
    }

    /* Now i is the id of the Element in the MFields. */
    if(i != n)
    {
        /* Erase these entries in the MFields */
        getElementIDs().erase(getElementIDs().begin() + i);
        getDisplayType().erase(getDisplayType().begin() + i);
        getPos().erase(getPos().begin() + i);
        getSize().erase(getSize().begin() + i);
        getColorMax().erase(getColorMax().begin() + i);
        getColorMin().erase(getColorMin().begin() + i);
        getColorCurrent().erase(getColorCurrent().begin() + i);
        getMinValue().erase(getMinValue().begin() + i);
        getMaxValue().erase(getMaxValue().begin() + i);
        getFlags().erase(getFlags().begin() + i);
        getHistorySize().erase(getHistorySize().begin() + i);

        _history.erase(_history.begin() + i);
        _historyID.erase(_historyID.begin() + i);
    }
}

/*******************************************************/
void GraphicStatisticsForeground::drawAnalog(UInt32 ID, StatElem *el,
                                             DrawActionBase *base, Viewport *)
{
    // helper Var
    Real32  xdist = 0.0;

    // get the current value to be digitised
    Real32  value = el->getValue();
    Real32  vsave = value;

    //std::cout << "Analog value: " << value << std::endl;
    // process this value according to the flags
    processValue(value, ID);
    processOnlyValue(vsave, ID);

    // calculate minimum value and maximun value
    Real32  minV = getMinValue()[ID];
    Real32  maxV = getMaxValue()[ID];

    // get the colors
    Color4f minColor = getColorMin()[ID];
    Color4f currentColor = getColorCurrent()[ID];
    Color4f maxColor = getColorMax()[ID];

    // xdist helps to calculate the real size[0] of the quadstrip and the colors
    xdist = (value - minV) / (maxV - minV);

    // draw a filled circle  with alpha value if expected
    Color3f c = getBackgroundColor();
    Real32  angle = 0.0;
    if(getBackgroundEnabled())
    {
        // filled circle drawn with a triangle_strip
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);
        glColor4f(c[0], c[1], c[2], 0.4);
        glBegin(GL_POLYGON);

        // glVertex2f(0.0, 0.0);
        for(angle = 0.0; angle < 2 * Pi; angle += Pi / 24)
        {
            glVertex2f(0.5 * cos(angle), 0.5 * sin(angle));
        }

        glEnd();
        glPopMatrix();
    }

    // draw a Frame around the display
    if(getBorderEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.8);

        // non filled circle around the filled one
        angle = 0.0;
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);
        glBegin(GL_LINE_LOOP);

        for(angle = 0.0; angle < 2 * Pi; angle += Pi / 24)
        {
            glVertex2f(0.5 * cos(angle), 0.5 * sin(angle));
        }

        glEnd();
        glPopMatrix();
    }

    // draw the ticks
    glColor3f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2]);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glRotatef(135, 0.0, 0.0, 1.0);

    glColor3f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2]);
    for(UInt32 r = 0; r < 10; r++)
    {
        glBegin(GL_LINES);
        glVertex2f(-0.5, 0.0);
        glVertex2f(-0.35, 0.0);
        glEnd();
        glRotatef(30, 0.0, 0.0, 1.0);
    }                                       // end for

    glPopMatrix();

    // save current matrix, translate to the origin of the pointer and rotate
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0);
    glRotatef(45 - (xdist * 270.0), 0.0, 0.0, 1.0);

    // draw arrow
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.4, 0.05);

    // next triangle -----
    glVertex2f(0.0, 0.0);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.4, -0.05);
    glEnd();

    // and finally go back
    glPopMatrix();

    //draw the center of the arrow...
    glPushMatrix();
    glColor3f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2]);
    glBegin(GL_QUADS);
    glVertex2f(0.475, 0.475);
    glVertex2f(0.525, 0.475);
    glVertex2f(0.525, 0.525);
    glVertex2f(0.475, 0.525);

    glEnd();

    glPopMatrix();

    /* draw a line representing the real current value if the value is
	   smoothed */
    UInt32  flags = getFlags()[ID];
    if(flags & OSG_SMOOTH)
    {
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);

        Real32  ang = 1 - ((vsave - minV) / (maxV - minV));
        glRotatef(45.0, 0.0, 0.0, 1.0);
        glRotatef((ang * 270.0), 0.0, 0.0, 1.0);
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, -0.5);
        glEnd();

        glPopMatrix();
    }

    // draw some text ------------
    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string maxstr = real2String(maxV);
        std::string minstr = real2String(minV);

        //set color for drawing the text
        glColor4f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2], 1.0);

        // Draw the current value under the center.
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0.0);
        glScalef(0.2, 0.2, 1.0);
        drawString(base, real2String(value), OSG_CENTER, OSG_TOP);
        glPopMatrix();

        // scale and translate the text
        glPushMatrix();
        glTranslatef(0.2, 0.3, 0.0);
        glScalef(0.12, 0.12, 1.0);

        //draw the text
        glTranslatef(0.0, -1.5, 0.0);
        drawString(base, minstr);
        glTranslatef(3.4, 0.0, 0.0);
        drawString(base, maxstr);
        glPopMatrix();
    }

    // end of text drawing ------
}

// end of drawAnalog

/*******************************************************/
void GraphicStatisticsForeground::drawChart(UInt32 ID, StatElem *el,
                                            DrawActionBase *base, Viewport *port)
{
    // The amount of the display to be used for the text on the bottom
    Real32  textHeight = 0.0;
    Real32  textWidth = 0.0;

    if(getTextEnabled())
    {
        textHeight = 0.2;
        textWidth = 0.25;
    }

    /* Height of the current quad */
    Real32  currQuadheight = 0.0;

    /* Get the current value and process it */
    Real32  value = el->getValue();
    processValue(value, ID);

    //std::cout << "Chart value: " << value << std::endl;
    /* calculate minimum value and maximun value */
    Real32  minV = getMinValue()[ID];
    Real32  maxV = getMaxValue()[ID];

    // draw a rectangle with alpha value
    Color3f c = getBackgroundColor();
    if(getBackgroundEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.4);
        glRectf(0.0, 0.0, 1.0, 1.0);
    }

    // draw a Frame around the display
    if(getBorderEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.8);
        glBegin(GL_LINE_STRIP);
        glVertex2f(textWidth, 0.0);
        glVertex2f(1.0, 0.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(textWidth, 1.0);
        glEnd();
    }

    /* Number of elements in the cycle buffer */
    UInt32  number = _history[ID].size();

    /* width of each Bar */
    Real32  step = (1.0 - textWidth) / number;

    /* The collor of the chart is set by the currentColor of this
       statistics Element */
    glColor4f(getColorCurrent()[ID][0], getColorCurrent()[ID][1],
                  getColorCurrent()[ID][2], getColorCurrent()[ID][3]);

    /* Base coordiantes for the chart (lower left corner) 
       Will be set to the current base coordinates of each bar in the
       loop */
    Real32  deltax = textWidth;

    glPushMatrix();
    glTranslatef(0.0, textHeight, 0.0);
    glScalef(1.0, 1.0 - textHeight, 1.0);

    /* loop over all entries in the cycle buffer */
    for(UInt32 i = 0; i < number; i++)
    {
        /* get the current value out of the cycle Buffer */
        value = _history[ID][((_historyID[ID]) + i) % number];

        /* calculate the height of the quad to be drawn in this
               iteration */
        currQuadheight = ((value - minV) / (maxV - minV));

        /* draw the current bar */
        glBegin(GL_QUADS);
        glVertex2f(deltax, 0.0);
        glVertex2f(deltax + step, 0.0);
        glVertex2f(deltax + step, currQuadheight);
        glVertex2f(deltax, currQuadheight);
        glEnd();                            // finished drawing current Quad
        deltax += step;
    }                                       // end for

    glPopMatrix();

    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string minstr = real2String(minV, "%.0f");
        std::string maxstr = real2String(maxV, "%.0f");
        std::string valstr = getDescription()[ID] + " " + real2String(value);

        // set color to draw the text with
        glColor4f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2], 1.0);

        // scale and translate the text
        Real32  ratio = ((Real32) port->getPixelHeight()) /
            ((Real32) port->getPixelWidth());

        // bottom: Current Value
        glPushMatrix();
        glTranslatef(0.5, 0.01, 0.0);
        glScalef(0.2 * ratio, 0.2, 1.0);
        drawString(base, valstr, OSG_CENTER);
        glPopMatrix();

        //draw: min value
        glPushMatrix();
        glTranslatef(0.0, 0.22, 0.0);
        glScalef(0.12 * ratio, 0.12, 1.0);
        drawString(base, minstr);
        glPopMatrix();

        //draw: maximum value
        glPushMatrix();
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(0.12 * ratio, 0.12, 1.0);
        drawString(base, maxstr, OSG_LEFT, OSG_TOP);
        glPopMatrix();
    }

    // end of text drawing ------
}

/*******************************************************/
void GraphicStatisticsForeground::drawBar(UInt32 ID, StatElem *el,
                                          DrawActionBase *base, Viewport *port)
{
    // The amount of the display to be used for the text on the bottom
    Real32  textHeight = 0.0;
    Real32  textWidth = 0.0;

    if(getTextEnabled())
    {
        textHeight = 0.2;
        textWidth = 0.0;
    }

    Real32  xdist = 0;                      // helper Var
    Real32  minV = getMinValue()[ID];
    Real32  maxV = getMaxValue()[ID];

    Real32  value = el->getValue();
    Real32  vsave = value;

    //std::cout << "Bar value: " << value << std::endl;
    processValue(value, ID);
    processOnlyValue(vsave, ID);

    // draw a rectangle with alpha value
    Color3f c = getBackgroundColor();
    if(getBackgroundEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.4);
        glRectf(0.0, 0.0, 1.0, 1.0);
    }

    // draw a Frame around the display
    if(getBorderEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.8);
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.0, 0.0);
        glVertex2f(1.0, 0.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(0.0, 1.0);
        glEnd();
    }

    // get the Colors into private vars
    Color4f MinColor = getColorMin()[ID];
    Color4f CurrentColor = getColorCurrent()[ID];
    Color4f MaxColor = getColorMax()[ID];

    // xdist helps to calculate the real size[0] of the quadstrip and the colors
    xdist = (value - minV) / (maxV - minV) * (1.0 - 2 * textWidth) + textWidth;

    /* draw the quads */
    if(xdist < 0.5)
    {
        glColor4f(MinColor[0], MinColor[1], MinColor[2], getColorMin()[ID][3]);
        glBegin(GL_QUADS);
        glVertex2f(textWidth, textHeight);
        glVertex2f(textWidth, 1.0);
        glColor4f(CurrentColor[0] * 2 * xdist + MinColor[0] * (1 - (2 * xdist)),
                  CurrentColor[1] * 2 * xdist + MinColor[1] * (1 - (2 * xdist)),
                  CurrentColor[2] * 2 * xdist + MinColor[2] * (1 - (2 * xdist)),
                  getColorCurrent()[ID][3]);
        glVertex2f(xdist, 1.0);
        glVertex2f(xdist, textHeight);
        glEnd();
    }                                       // end if
    else                                    //if xdist > 0.5
    {
        glBegin(GL_QUADS);

        // draw first quad
        glColor4f(MinColor[0], MinColor[1], MinColor[2], getColorMin()[ID][3]);
        glVertex2f(textWidth, textHeight);
        glVertex2f(textWidth, 1.0);
        glColor4f(CurrentColor[0], CurrentColor[1], CurrentColor[2],
                  getColorCurrent()[ID][3]);
        glVertex2f(0.5, 1.0);
        glVertex2f(0.5, textHeight);

        // draw second quad
        glVertex2f(0.5, textHeight);
        glVertex2f(0.5, 1.0);
        glColor4f(MaxColor[0] * ((xdist - 0.5) * 2) + CurrentColor[0] *
                    (1 - ((xdist - 0.5) * 2)),
                  MaxColor[1] * ((xdist - 0.5) * 2) + CurrentColor[1] * 
                    (1 - ((xdist - 0.5) * 2)),
                  MaxColor[2] * ((xdist - 0.5) * 2) + CurrentColor[2] *
                    (1 - ((xdist - 0.5) * 2)), getColorMax()[ID][3]);
        glVertex2f(0.5 + ((xdist - 0.5)), 1.0);
        glVertex2f(0.5 + ((xdist - 0.5)), textHeight);
        glEnd();
    }                                       // end else

    /* draw a line representing the real current value 
	   if the value to be digitized is smoothed */
    if(_history[ID].size() > 0)
    {
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINES);

        glVertex2f((vsave - minV) / (maxV - minV) * (1.0 - 2 * textWidth) +
                           textWidth, 1.0);
        glVertex2f((vsave - minV) / (maxV - minV) * (1.0 - 2 * textWidth) +
                           textWidth, textHeight);
        glEnd();
    }

    // Draw the text
    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string valstr = getDescription()[ID] + " " + real2String(value);
        std::string minstr = real2String(minV, "%.0f");
        std::string maxstr = real2String(maxV, "%.0f");

        // set color to draw the text with
        glColor4f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2], 1.0);

        // scale and translate the text
        Real32  ratio = ((Real32) port->getPixelHeight()) /
            ((Real32) port->getPixelWidth());

        // Left side: Min
        glPushMatrix();
        glTranslatef(0.0, 0.7, 0.0);
        glScalef(0.15 * ratio, 0.15, 1.0);
        drawString(base, minstr);
        glPopMatrix();

        // right side: Max
        glPushMatrix();
        glTranslatef(1.0, 0.7, 0.0);
        glScalef(0.15 * ratio, 0.15, 1.0);
        drawString(base, maxstr, OSG_RIGHT);
        glPopMatrix();

        // bottom: Current Value
        glPushMatrix();
        glTranslatef(0.5, 0.01, 0.0);
        glScalef(0.2 * ratio, 0.2, 1.0);
        drawString(base, valstr, OSG_CENTER);
        glPopMatrix();
    }

    // end of text drawing ------
}

/*******************************************************/

//begin drawlinechart
void GraphicStatisticsForeground::drawLineChart(UInt32 ID, StatElem *el,
                                                DrawActionBase *base,
                                                Viewport *port)
{
    // The amount of the display to be used for the text on the bottom
    Real32  textHeight = 0.0;
    Real32  textWidth = 0.0;

    if(getTextEnabled())
    {
        textHeight = 0.2;
        textWidth = 0.25;
    }

    /* Height of the current quad */
    Real32  currHeight = 0.0;

    /* Flags for check whether points should be drawn or not */
    UInt32  flags = getFlags()[ID];

    /* Get the current value and process it */
    Real32  value = el->getValue();
    Real32  realValue = (flags & OSG_RECIPROC) ? 1.f / value : value;

    processValue(value, ID);

    //std::cout << "LineChart value: " << value << std::endl;
    /* calculate minimum value and maximun value */
    Real32  minV = getMinValue()[ID];
    Real32  maxV = getMaxValue()[ID];

    // draw a rectangle with alpha value
    Color3f c = getBackgroundColor();
    if(getBackgroundEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.4);
        glRectf(0.0, 0.0, 1.0, 1.0);
    }

    // draw a Frame around the display
    if(getBorderEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.8);
        glBegin(GL_LINE_STRIP);
        glVertex2f(textWidth, 0.0);
        glVertex2f(1.0, 0.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(textWidth, 1.0);
        glEnd();
    }

    /* Number of elements in the cycle buffer */
    UInt32  number = _history[ID].size();

    /* width of each Bar */
    Real32  step = (1.0 - textWidth) / number;

    /* The collor of the chart is set by the currentColor of this
       statistics Element */
    glColor4f(getColorCurrent()[ID][0], getColorCurrent()[ID][1],
              getColorCurrent()[ID][2], getColorCurrent()[ID][3]);

    /* Base coordiantes for the chart (lower left corner) 
       Will be set to the current base coordinates of each bar in the
       loop */
    Real32  deltax = textWidth;

    glPushMatrix();
    glTranslatef(0.0, textHeight, 0.0);
    glScalef(1.0, 1.0 - textHeight, 1.0);

    /* loop over all entries in the cycle buffer */
    value = _history[ID][_historyID[ID]];

    /* save the last x und y value to draw the line in the next
       iterarion */
    Real32  lastx = textWidth;
    Real32  lasty = ((value - minV) / (maxV - minV));

    for(UInt32 i = 0; i < number; i++)
    {
        /* get the current value out of the cycle Buffer */
        value = _history[ID][((_historyID[ID]) + i) % number];

        /* calculate the height of the quad to be drawn in this
               iteration */
        currHeight = ((value - minV) / (maxV - minV));

        /* draw the current line */
        glBegin(GL_LINES);
        glVertex2f(lastx, lasty);
        glVertex2f(deltax, currHeight);
        glEnd();

        // save x und y position to draw the line in the next iteration */
        lastx = deltax;
        lasty = currHeight;

        //            Real32 angle = 0.0;
        /* draw Point if wanted */
        if(flags & OSG_ENABLE_POINTS)
        {
            /* filled circle 
                       glPushMatrix();
                       glTranslatef(deltax, currHeight, 0.0);
                       glBegin(GL_POLYGON);
                       for (angle = 0.0; angle < 2 * Pi; angle += Pi / 24)
                       {
                       glVertex2f(0.0125 *cos(angle), 0.0125 * sin(angle));
                       }
                       glEnd();
                       glPopMatrix();*/
            // draw one single point with GL_POINT_SIZE =
            glPointSize(2.0 * getLineWidth());
            glBegin(GL_POINTS);
            glVertex2f(deltax, currHeight);
            glEnd();
        }                                   // end if

        deltax += step;
    }                                       // end for

    glPopMatrix();

    // draw some text ------------
    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string valstr = getDescription()[ID] + " " + 
					real2String(realValue);

        // set color to draw the text with
        glColor4f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2], 1.0);

        // scale and translate the text
        Real32  ratio = ((Real32) port->getPixelHeight()) /
            ((Real32) port->getPixelWidth());

        // bottom: Current Value
        glPushMatrix();
        glTranslatef(0.5, 0.01, 0.0);
        glScalef(0.2 * ratio, 0.2, 1.0);
        drawString(base, valstr, OSG_CENTER);
        glPopMatrix();

        //draw: min value
        if(flags & OSG_MAX_TEXT)
        {
            std::string minstr = real2String(minV, "%.0f");
            glPushMatrix();
            glTranslatef(0.0, 0.22, 0.0);
            glScalef(0.12 * ratio, 0.12, 1.0);
            drawString(base, minstr);
            glPopMatrix();
        }

        //draw: maximum value
        if(flags & OSG_MIN_TEXT)
        {
            std::string maxstr = real2String(maxV, "%.0f");
            glPushMatrix();
            glTranslatef(0.0, 1.0, 0.0);
            glScalef(0.12 * ratio, 0.12, 1.0);
            drawString(base, maxstr, OSG_LEFT, OSG_TOP);
            glPopMatrix();
        }
    }

    // end of text drawing ------
}

/* */
void GraphicStatisticsForeground::drawText(UInt32 ID, StatElem *el,
                                           DrawActionBase *base, Viewport *port)
{
    /* Get the current value and process it */
    Real32  value = el->getValue();
    processOnlyValue(value, ID);

    //std::cout << "TextChart value: " << value << std::endl;
    /* get value, calculate minimum value and maximun value and
   convert into a string*/
    Real32      minV = getMinValue()[ID];
    Real32      maxV = getMaxValue()[ID];
    std::string minstr = real2String(minV, "%.0f");
    std::string maxstr = real2String(maxV, "%.0f");
    std::string valstr = getDescription()[ID] + " " + real2String(value);

    // draw a rectangle with alpha value
    Color3f     c = getBackgroundColor();
    if(getBackgroundEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.4);
        glRectf(0.0, 0.0, 1.0, 1.0);
    }

    // draw a Frame around the display
    if(getBorderEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.8);
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.0, 0.0);
        glVertex2f(1.0, 0.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(0.0, 1.0);
        glEnd();
    }

    // set color to draw the text with
    glColor4f(1.0 - c[0], 1.0 - c[1], 1.0 - c[2], 1.0);

    // scale and translate the text
    Real32  ratio = ((Real32) port->getPixelHeight()) /
        ((Real32) port->getPixelWidth());

    // Current Value
    glPushMatrix();
    glTranslatef(0.02, 0.7, 0.0);
    glScalef(0.18 * ratio, 0.18, 1.0);
    drawString(base, valstr);
    glPopMatrix();

    // MinValue
    glPushMatrix();
    glTranslatef(0.02, 0.5, 0.0);
    glScalef(0.18 * ratio, 0.18, 1.0);
    drawString(base, "Min: " + minstr);
    glPopMatrix();

    // MaxValue
    glPushMatrix();
    glTranslatef(0.02, 0.3, 0.0);
    glScalef(0.18 * ratio, 0.18, 1.0);
    drawString(base, "Max: " + maxstr);
    glPopMatrix();
}

// end of drawText

/*******************************************************/

//! Calculate the position an size of an element
void GraphicStatisticsForeground::calcPosAndSize(const UInt32 &id,
                                                 Viewport *port, 
                                                 Vec2f *Position,
                                                 Vec2f *Size)
{
    // Width and Height of the current viewport
    // needed for pixel to relative conversion
    Real32  pw = port->getPixelWidth();     // PixelWidth
    Real32  ph = port->getPixelHeight();    // PixelHeight
    Real32  ratio = pw / ph;

    /*
      Calculate the size
    */
    Vec2f   size(getSize()[id][0], getSize()[id][1]);   // Temp Size

    // Check for values < 0
    // If both values a <0 fall back to
    if(size[0] < 0 && size[1] < 0)
    {
        size[0] = size[1] = 1.0;
    }
    else
    {
        if(size[0] < 0)
        {
            size[0] = osgabs(size[0]) * size[1] / ratio;
        }

        if(size[1] < 0)
        {
            size[1] = osgabs(size[1]) * size[0] * ratio;
        }
    }

    //convert pixel based sizes to relative ones
    if(size[0] > 1.0)
        size[0] = size[0] / pw;
    if(size[1] > 1.0)
        size[1] = size[1] / ph;

    // Save the Size
    (*Size) = size;

    /*
      calculate the position
    */
    Vec2f   pos(getPos()[id][0], getPos()[id][1]);      // Temp Position

    // Hack the floats
    bool    xneg = false;
    bool    yneg = false;

    if(pos[0] < 0)
    {
        pos[0] = pos[0] + 1;
        xneg = true;
    }

    if(pos[1] < 0)
    {
        pos[1] = pos[1] + 1;
        yneg = true;
    }

    // convert the pixel Data to relative positions
    if(osgabs(pos[0]) > 1.0)
        pos[0] = pos[0] / pw;
    if(osgabs(pos[1]) > 1.0)
        pos[1] = pos[1] / ph;

    // check whether the positions are relative to the right/bottom
    if(xneg)
        pos[0] = 1.0 + pos[0] - size[0];
    if(yneg)
        pos[1] = 1.0 + pos[1] - size[1];

    // Save the calculated position
    (*Position) = pos;
}

// calcPosAndSize()

//! initialize the text
void GraphicStatisticsForeground::initText(void)
{
    // create the text needed
#ifdef OSG_HAS_SSTREAM
    std::istringstream stream((char *) GraphicsStatisticsFontData,
                                  GraphicsStatisticsFontDataSize);
#else
    std::istrstream stream((char *) GraphicsStatisticsFontData,
                               GraphicsStatisticsFontDataSize);
#endif

    TXFFont *font = new TXFFont("StatisticsDefaultFont", stream);
    font->initFont();

    _text.setSize(1);
    font->createInstance(&_text);
    _text.setJustifyMajor(FIRST_JT);

    // create the TXF texture
    _textimage = Image::create();
    _text.fillTXFImage(_textimage);

    _texchunk = TextureChunk::create();

    beginEditCP(_texchunk);
    {
        _texchunk->setImage(_textimage);
        _texchunk->setWrapS(GL_CLAMP);
        _texchunk->setWrapT(GL_CLAMP);
        _texchunk->setEnvMode(GL_MODULATE);
    }

    endEditCP(_texchunk);
}

//! Draws a String
void GraphicStatisticsForeground::drawString(DrawActionBase *base,
                                             const std::string &text,
                                             UInt32 align, UInt32 valign)
{
    Real32  deltaX = 0.0;
    Real32  deltaY = 0.0;
    std::vector < std::string > stat(1);
    stat[0] = text;

    UInt32  n = _text.getTXFNVertices(stat);

    std::vector < Pnt3f > positions(n);
    std::vector < Vec2f > tex(n);

    _text.fillTXFArrays(stat, &positions[0], &tex[0]);

    // check whether we have to right-align the text
    if(align == OSG_RIGHT)
        deltaX = -(positions[n - 3][0]);
    if(align == OSG_CENTER)
    {
        deltaX = -(positions[n - 3][0]) / 2.0;
    }

    if(valign != OSG_BOTTOM)
    {
        Real32  textHeight = 0.0;
        Real32  foo = 0.0;

        // calculate the height of the text
        for(int i = 0; i < n; i += 4)
        {
            foo = positions[i + 3][1] - positions[i][1];
            if(foo > textHeight)
                textHeight = foo;
        }

        if(valign == OSG_TOP)
            deltaY = -textHeight;
        if(valign == OSG_MIDDLE)
            deltaY = -(textHeight / 2.0);
    }

    glPushMatrix();

    // sane the delta values
    Int32   deltaXI = (Int32) (deltaX * 10.0);
    deltaX = ((Real32) deltaXI) / 10.0;

    Int32   deltaYI = (Int32) (deltaY * 10.0);
    deltaY = ((Real32) deltaYI) / 10.0;

    glTranslatef(deltaX, deltaY, 0.0);

    // Draw the text
    _texchunk->activate(base);

    glBegin(GL_QUADS);
    for(UInt32 i = 0; i < n; i++)
    {
        glTexCoord2fv((GLfloat *) &tex[i]);
        glVertex3fv((GLfloat *) &positions[i]);
    }

    glEnd();

    _texchunk->deactivate(base);

    glPopMatrix();
}

//! Converts a Real32 to a string
std::string GraphicStatisticsForeground::real2String(Real32 value, char *format)
{
    char    buff[100];

    if(format == 0)
        sprintf(buff, "%.2f", value);
    else
        sprintf(buff, format, value);

    std::string Result(buff);

    return Result;
}

//////////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */
#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif
namespace
{
static Char8    cvsid_cpp[] = "@(#)$Id: OSGGraphicStatisticsForeground.cpp,v 1.13 2002/08/07 08:27:35 vossg Exp $";
static Char8    cvsid_hpp[] = OSGGRAPHICSTATISTICSFOREGROUNDBASE_HEADER_CVSID;
static Char8    cvsid_inl[] = OSGGRAPHICSTATISTICSFOREGROUNDBASE_INLINE_CVSID;

static Char8    cvsid_fields_hpp[] =
    OSGGRAPHICSTATISTICSFOREGROUNDFIELDS_HEADER_CVSID;
}
#ifdef __sgi
#pragma reset woff 1174
#endif
