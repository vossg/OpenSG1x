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
#include <OSGConfig.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <OSGImage.h>

#include <OSGTextTXFFace.h>
#include <OSGTextTXFGlyph.h>
#include <OSGTextLayoutResult.h>

#include <OSGNodePtr.h>
#include <OSGViewport.h>
#include "OSGStatisticsDefaultFont.h"

#include "OSGStatElem.h"
#include "OSGGraphicStatisticsForeground.h"
#include "OSGGL.h"

OSG_USING_NAMESPACE

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
    Inherited(), _face(0), _texchunk()
{
}

/* */
GraphicStatisticsForeground::GraphicStatisticsForeground(const GraphicStatisticsForeground &source) :
        Inherited(source), _face(source._face), _texchunk(source._texchunk)
{
    if (_face != 0)
        addRefP(_face);
    if (_texchunk != NullFC)
        addRefCP(_texchunk);
}

/* */
GraphicStatisticsForeground::~GraphicStatisticsForeground(void)
{
    if (_face != 0)
        subRefP(_face);
    if (_texchunk != NullFC)
        subRefCP(_texchunk);
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
                                                   (getMaxValue()[i] - getMinValue()[i]) / 2.0f);
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
    if (getActive() == false)
        return;
	
    // Check the height and width of the window
    if(port->getPixelWidth() < 1 || port->getPixelHeight() < 1)
    {
        return;
    }

    // initialize the text texture
    if(_face == 0)
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

        glMatrixMode(GL_MODELVIEW);
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

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }                                       //for()

    //reset OpenGL matrices
    glMatrixMode(GL_PROJECTION);
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
void GraphicStatisticsForeground::drawAnalog(UInt32 elementID, StatElem *el,
                                             DrawActionBase *base, Viewport *)
{
    // helper Var
    Real32  xdist = 0.0;

    // get the current value to be digitised
    Real32  value = Real32(el->getValue());
    Real32  vsave = value;

    //std::cout << "Analog value: " << value << std::endl;
    // process this value according to the flags
    processValue(value, elementID);
    processOnlyValue(vsave, elementID);

    // calculate minimum value and maximun value
    Real32  minV = getMinValue()[elementID];
    Real32  maxV = getMaxValue()[elementID];

    // get the colors
    Color4f minColor = getColorMin()[elementID];
    Color4f currentColor = getColorCurrent()[elementID];
    Color4f maxColor = getColorMax()[elementID];

    // xdist helps to calculate the real size[0] of the quadstrip and the colors
    xdist = (value - minV) / (maxV - minV);

    // draw a filled circle  with alpha value if expected
    Color3f c = getBackgroundColor();
    Real32  angle = 0.0;
    if(getBackgroundEnabled())
    {
        // filled circle drawn with a triangle_strip
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);
        glColor4f(c[0], c[1], c[2], 0.4);
        glBegin(GL_POLYGON);

        // glVertex2f(0.0, 0.0);
        for(angle = 0.0; angle < 2 * Pi; angle += Pi / 24)
        {
            glVertex2f(0.5f * cos(angle), 0.5f * sin(angle));
        }

        glEnd();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    // draw a Frame around the display
    if(getBorderEnabled())
    {
        glColor4f(c[0], c[1], c[2], 0.8);

        // non filled circle around the filled one
        angle = 0.0;
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);
        glBegin(GL_LINE_LOOP);

        for(angle = 0.0; angle < 2 * Pi; angle += Pi / 24)
        {
            glVertex2f(0.5f * cos(angle), 0.5f * sin(angle));
        }

        glEnd();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    // draw the ticks
    glColor3f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2]);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glRotatef(135, 0.0, 0.0, 1.0);

    glColor3f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2]);
    for(UInt32 r = 0; r < 10; r++)
    {
        glBegin(GL_LINES);
        glVertex2f(-0.5, 0.0);
        glVertex2f(-0.35, 0.0);
        glEnd();
        glRotatef(30, 0.0, 0.0, 1.0);
    }                                       // end for

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // save current matrix, translate to the origin of the pointer and rotate
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0);
    glRotatef(45 - (xdist * 270.0f), 0.0, 0.0, 1.0);

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
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    //draw the center of the arrow...
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glColor3f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2]);
    glBegin(GL_QUADS);
    glVertex2f(0.475, 0.475);
    glVertex2f(0.525, 0.475);
    glVertex2f(0.525, 0.525);
    glVertex2f(0.475, 0.525);

    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    /* draw a line representing the real current value if the value is
       smoothed */
    UInt32  flags = getFlags()[elementID];
    if(flags & OSG_SMOOTH)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);

        Real32  ang = 1 - ((vsave - minV) / (maxV - minV));
        glRotatef(45.0, 0.0, 0.0, 1.0);
        glRotatef((ang * 270.0f), 0.0, 0.0, 1.0);
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, -0.5);
        glEnd();

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    // draw some text ------------
    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string maxstr = real2String(maxV);
        std::string minstr = real2String(minV);

        //set color for drawing the text
        glColor4f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2], 1.0f);

        // Draw the current value under the center.
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0.0);
        glScalef(0.2, 0.2, 1.0);
        drawString(base, real2String(value), TextLayoutParam::ALIGN_MIDDLE,
                   TextLayoutParam::ALIGN_FIRST);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        // scale and translate the text
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.2, 0.3, 0.0);
        glScalef(0.12, 0.12, 1.0);

        //draw the text
        glTranslatef(0.0, -1.5, 0.0);
        drawString(base, minstr);
        glTranslatef(3.4, 0.0, 0.0);
        drawString(base, maxstr);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    // end of text drawing ------
}

// end of drawAnalog

/*******************************************************/
void GraphicStatisticsForeground::drawChart(UInt32 elementID, StatElem *el,
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
    Real32  value = Real32(el->getValue());
    processValue(value, elementID);

    //std::cout << "Chart value: " << value << std::endl;
    /* calculate minimum value and maximun value */
    Real32  minV = getMinValue()[elementID];
    Real32  maxV = getMaxValue()[elementID];

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
    UInt32  number = _history[elementID].size();

    /* width of each Bar */
    Real32  step = (1.0f - textWidth) / number;

    /* The collor of the chart is set by the currentColor of this
       statistics Element */
    glColor4f(getColorCurrent()[elementID][0],
              getColorCurrent()[elementID][1],
              getColorCurrent()[elementID][2],
              getColorCurrent()[elementID][3]);

    /* Base coordiantes for the chart (lower left corner)
       Will be set to the current base coordinates of each bar in the
       loop */
    Real32  deltax = textWidth;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0, textHeight, 0.0);
    glScalef(1.0f, 1.0f - textHeight, 1.0f);

    /* loop over all entries in the cycle buffer */
    for(UInt32 i = 0; i < number; i++)
    {
        /* get the current value out of the cycle Buffer */
        value = _history[elementID][((_historyID[elementID]) + i) % number];

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

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string minstr = real2String(minV, "%.0f");
        std::string maxstr = real2String(maxV, "%.0f");
        std::string valstr = getDescription()[elementID] + " " + real2String(value);

        // set color to draw the text with
        glColor4f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2], 1.0f);

        // scale and translate the text
        Real32  ratio = ((Real32) port->getPixelHeight()) /
            ((Real32) port->getPixelWidth());

        // bottom: Current Value
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.5, 0.01, 0.0);
        glScalef(0.2f * ratio, 0.2f, 1.0f);
        drawString(base, valstr, TextLayoutParam::ALIGN_MIDDLE);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        //draw: min value
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.0, 0.22, 0.0);
        glScalef(0.12f * ratio, 0.12f, 1.0f);
        drawString(base, minstr);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        //draw: maximum value
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(0.12f * ratio, 0.12f, 1.0f);
        drawString(base, maxstr, TextLayoutParam::ALIGN_FIRST, TextLayoutParam::ALIGN_FIRST);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    // end of text drawing ------
}

/*******************************************************/
void GraphicStatisticsForeground::drawBar(UInt32 elementID, StatElem *el,
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
    Real32  minV = getMinValue()[elementID];
    Real32  maxV = getMaxValue()[elementID];

    Real32  value = Real32(el->getValue());
    Real32  vsave = value;

    //std::cout << "Bar value: " << value << std::endl;
    processValue(value, elementID);
    processOnlyValue(vsave, elementID);

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
    Color4f MinColor = getColorMin()[elementID];
    Color4f CurrentColor = getColorCurrent()[elementID];
    Color4f MaxColor = getColorMax()[elementID];

    // xdist helps to calculate the real size[0] of the quadstrip and the colors
    xdist = (value - minV) / (maxV - minV) * (1.0f - 2 * textWidth) + textWidth;

    /* draw the quads */
    if(xdist < 0.5)
    {
        glColor4f(MinColor[0], MinColor[1], MinColor[2], getColorMin()[elementID][3]);
        glBegin(GL_QUADS);
        glVertex2f(textWidth, textHeight);
        glVertex2f(textWidth, 1.0);
        glColor4f(CurrentColor[0] * 2 * xdist + MinColor[0] * (1 - (2 * xdist)),
                  CurrentColor[1] * 2 * xdist + MinColor[1] * (1 - (2 * xdist)),
                  CurrentColor[2] * 2 * xdist + MinColor[2] * (1 - (2 * xdist)),
                  getColorCurrent()[elementID][3]);
        glVertex2f(xdist, 1.0);
        glVertex2f(xdist, textHeight);
        glEnd();
    }                                       // end if
    else                                    //if xdist > 0.5
    {
        glBegin(GL_QUADS);

        // draw first quad
        glColor4f(MinColor[0], MinColor[1], MinColor[2], getColorMin()[elementID][3]);
        glVertex2f(textWidth, textHeight);
        glVertex2f(textWidth, 1.0);
        glColor4f(CurrentColor[0], CurrentColor[1], CurrentColor[2],
                  getColorCurrent()[elementID][3]);
        glVertex2f(0.5, 1.0);
        glVertex2f(0.5, textHeight);

        // draw second quad
        glVertex2f(0.5, textHeight);
        glVertex2f(0.5, 1.0);
        glColor4f(MaxColor[0] * ((xdist - 0.5f) * 2) + CurrentColor[0] *
                    (1 - ((xdist - 0.5f) * 2)),
                  MaxColor[1] * ((xdist - 0.5f) * 2) + CurrentColor[1] *
                    (1 - ((xdist - 0.5f) * 2)),
                  MaxColor[2] * ((xdist - 0.5f) * 2) + CurrentColor[2] *
                    (1 - ((xdist - 0.5f) * 2)), getColorMax()[elementID][3]);
        glVertex2f(0.5f + ((xdist - 0.5f)), 1.0);
        glVertex2f(0.5f + ((xdist - 0.5f)), textHeight);
        glEnd();
    }                                       // end else

    /* draw a line representing the real current value
       if the value to be digitized is smoothed */
    if(_history[elementID].size() > 0)
    {
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINES);

        glVertex2f((vsave - minV) / (maxV - minV) * (1.0f - 2 * textWidth) +
                           textWidth, 1.0f);
        glVertex2f((vsave - minV) / (maxV - minV) * (1.0f - 2 * textWidth) +
                           textWidth, textHeight);
        glEnd();
    }

    // Draw the text
    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string valstr = getDescription()[elementID] + " " + real2String(value);
        std::string minstr = real2String(minV, "%.0f");
        std::string maxstr = real2String(maxV, "%.0f");

        // set color to draw the text with
        glColor4f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2], 1.0f);

        // scale and translate the text
        Real32  ratio = ((Real32) port->getPixelHeight()) /
            ((Real32) port->getPixelWidth());

        // Left side: Min
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.0, 0.7, 0.0);
        glScalef(0.15f * ratio, 0.15f, 1.0f);
        drawString(base, minstr);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        // right side: Max
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(1.0, 0.7, 0.0);
        glScalef(0.15f * ratio, 0.15f, 1.0f);
        drawString(base, maxstr, TextLayoutParam::ALIGN_END);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        // bottom: Current Value
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.5f, 0.01f, 0.0f);
        glScalef(0.2f * ratio, 0.2f, 1.0f);
        drawString(base, valstr, TextLayoutParam::ALIGN_MIDDLE);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    // end of text drawing ------
}

/*******************************************************/

//begin drawlinechart
void GraphicStatisticsForeground::drawLineChart(UInt32 elementID, StatElem *el,
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
    UInt32  flags = getFlags()[elementID];

    /* Get the current value and process it */
    Real32  value = Real32(el->getValue());
    Real32  realValue = (flags & OSG_RECIPROC) ? 1.f / value : value;

    processValue(value, elementID);

    //std::cout << "LineChart value: " << value << std::endl;
    /* calculate minimum value and maximun value */
    Real32  minV = getMinValue()[elementID];
    Real32  maxV = getMaxValue()[elementID];

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
    UInt32  number = _history[elementID].size();

    /* width of each Bar */
    Real32  step = (1.0f - textWidth) / number;

    /* The collor of the chart is set by the currentColor of this
       statistics Element */
    glColor4f(getColorCurrent()[elementID][0], getColorCurrent()[elementID][1],
              getColorCurrent()[elementID][2], getColorCurrent()[elementID][3]);

    /* Base coordiantes for the chart (lower left corner)
       Will be set to the current base coordinates of each bar in the
       loop */
    Real32  deltax = textWidth;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0, textHeight, 0.0);
    glScalef(1.0f, 1.0f - textHeight, 1.0f);

    /* loop over all entries in the cycle buffer */
    value = _history[elementID][_historyID[elementID]];

    /* save the last x und y value to draw the line in the next
       iterarion */
    Real32  lastx = textWidth;
    Real32  lasty = ((value - minV) / (maxV - minV));

    for(UInt32 i = 0; i < number; i++)
    {
        /* get the current value out of the cycle Buffer */
        value = _history[elementID][((_historyID[elementID]) + i) % number];

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
            glPointSize(2.0f * getLineWidth());
            glBegin(GL_POINTS);
            glVertex2f(deltax, currHeight);
            glEnd();
        }                                   // end if

        deltax += step;
    }                                       // end for

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // draw some text ------------
    if(getTextEnabled())
    {
        // create some Strings to be drawn
        std::string valstr = getDescription()[elementID] + " " +
                    real2String(realValue);

        // set color to draw the text with
        glColor4f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2], 1.0f);

        // scale and translate the text
        Real32  ratio = ((Real32) port->getPixelHeight()) /
            ((Real32) port->getPixelWidth());

        // bottom: Current Value
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0.5, 0.01, 0.0);
        glScalef(0.2f * ratio, 0.2f, 1.0f);
        drawString(base, valstr, TextLayoutParam::ALIGN_MIDDLE);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        //draw: min value
        if(flags & OSG_MAX_TEXT)
        {
            std::string minstr = real2String(minV, "%.0f");
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(0.0, 0.22, 0.0);
            glScalef(0.12f * ratio, 0.12f, 1.0f);
            drawString(base, minstr);
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        //draw: maximum value
        if(flags & OSG_MIN_TEXT)
        {
            std::string maxstr = real2String(maxV, "%.0f");
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(0.0, 1.0, 0.0);
            glScalef(0.12f * ratio, 0.12f, 1.0f);
            drawString(base, maxstr, TextLayoutParam::ALIGN_FIRST,
                       TextLayoutParam::ALIGN_FIRST);
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }
    }

    // end of text drawing ------
}

/* */
void GraphicStatisticsForeground::drawText(UInt32 elementID, StatElem *el,
                                           DrawActionBase *base, Viewport *port)
{
    /* Get the current value and process it */
    Real32  value = Real32(el->getValue());
    processOnlyValue(value, elementID);

    //std::cout << "TextChart value: " << value << std::endl;
    /* get value, calculate minimum value and maximun value and
       convert into a string*/
    Real32      minV = getMinValue()[elementID];
    Real32      maxV = getMaxValue()[elementID];
    std::string minstr = real2String(minV, "%.0f");
    std::string maxstr = real2String(maxV, "%.0f");
    std::string valstr = getDescription()[elementID] + " " + real2String(value);

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
    glColor4f(1.0f - c[0], 1.0f - c[1], 1.0f - c[2], 1.0f);

    // scale and translate the text
    Real32  ratio = ((Real32) port->getPixelHeight()) /
        ((Real32) port->getPixelWidth());

    // Current Value
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.02, 0.7, 0.0);
    glScalef(0.18f * ratio, 0.18f, 1.0f);
    drawString(base, valstr);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // MinValue
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.02, 0.5, 0.0);
    glScalef(0.18f * ratio, 0.18f, 1.0f);
    drawString(base, "Min: " + minstr);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // MaxValue
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.02, 0.3, 0.0);
    glScalef(0.18f * ratio, 0.18f, 1.0f);
    drawString(base, "Max: " + maxstr);
    glMatrixMode(GL_MODELVIEW);
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
    Real32  pw = Real32(port->getPixelWidth ());     // PixelWidth
    Real32  ph = Real32(port->getPixelHeight());    // PixelHeight
    Real32  ratio = pw / ph;

    /*
      Calculate the size
    */
    Vec2f size = getSize(id); // Temp Size

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
    Vec2f pos = getPos(id); // Temp Position

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
        pos[0] = 1.0f + pos[0] - size[0];
    if(yneg)
        pos[1] = 1.0f + pos[1] - size[1];

    // Save the calculated position
    (*Position) = pos;
}

// calcPosAndSize()

//! initialize the text
void GraphicStatisticsForeground::initText(void)
{
    // Cleanup
    if (_face != 0)
        subRefP(_face);
    if (_texchunk != NullFC)
        subRefCP(_texchunk);

    _face = getStatisticsDefaultFont();
    _texchunk = getStatisticsDefaultFontTexture();

    // Increment reference counters
    addRefP(_face);
    addRefCP(_texchunk);
}

//! Draws a String
void GraphicStatisticsForeground::drawString(DrawActionBase *base,
                                             const std::string &text,
                                             TextLayoutParam::Alignment majorAlignment,
                                             TextLayoutParam::Alignment minorAlignment)
{
    std::vector < std::string > stat(1);
    stat[0] = text;

    TextLayoutParam layoutParam;
    layoutParam.majorAlignment = majorAlignment;
    layoutParam.minorAlignment = minorAlignment;
    TextLayoutResult layoutResult;
    _face->layout(stat, layoutParam, layoutResult);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Draw the text
    _texchunk->activate(base);

    glBegin(GL_QUADS);
    UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    for(i = 0; i < numGlyphs; ++i)
    {
        const TextTXFGlyph &glyph = _face->getTXFGlyph(layoutResult.indices[i]);
        Real32 width = glyph.getWidth();
        Real32 height = glyph.getHeight();
        // No need to draw invisible glyphs
        if ((width <= 0.f) || (height <= 0.f))
            continue;

        // Calculate coordinates
        const Vec2f &pos = layoutResult.positions[i];
        Real32 posLeft = pos.x();
        Real32 posTop = pos.y();
        Real32 posRight = pos.x() + width;
        Real32 posBottom = pos.y() - height;
        Real32 texCoordLeft = glyph.getTexCoord(TextTXFGlyph::COORD_LEFT);
        Real32 texCoordTop = glyph.getTexCoord(TextTXFGlyph::COORD_TOP);
        Real32 texCoordRight = glyph.getTexCoord(TextTXFGlyph::COORD_RIGHT);
        Real32 texCoordBottom = glyph.getTexCoord(TextTXFGlyph::COORD_BOTTOM);

        // lower left corner
        glTexCoord2f(texCoordLeft, texCoordBottom);
        glVertex2f(posLeft, posBottom);

        // lower right corner
        glTexCoord2f(texCoordRight, texCoordBottom);
        glVertex2f(posRight, posBottom);

        // upper right corner
        glTexCoord2f(texCoordRight, texCoordTop);
        glVertex2f(posRight, posTop);

        // upper left corner
        glTexCoord2f(texCoordLeft, texCoordTop);
        glVertex2f(posLeft, posTop);
    }
    glEnd();

    _texchunk->deactivate(base);

    glMatrixMode(GL_MODELVIEW);
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
