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

#include "OSGQColorButton_qt.h"

#include <OSGLog.h>

#include <qstyle.h>
#include <qpainter.h>

OSG_USING_NAMESPACE

QColorButton::QColorButton(QWidget *pParent, const char *name, WFlags flags)
    : Inherited     (pParent, name, flags),
      _packedColor  (0                   ),
      _bTransparency(false               )
{
}

QColorButton::~QColorButton(void)
{
}

void
QColorButton::drawButton(QPainter *pPainter)
{
    QRect          drawRect(0, 0, geometry().width(), geometry().height());
    QStyle::SFlags drawFlags = QStyle::Style_Default;

    if(isEnabled() == true)
    {
        drawFlags |= QStyle::Style_Enabled;
    }

    if(isDown() == true)
    {
        drawFlags |= QStyle::Style_Down;
    }
    else
    {
        drawFlags |= QStyle::Style_Up;
    }

    style().drawPrimitive(QStyle::PE_ButtonBevel, pPainter, drawRect,
                          colorGroup(),           drawFlags          );

    drawButtonLabel(pPainter);
}

void
QColorButton::drawButtonLabel(QPainter *pPainter)
{
    UInt8 red    = (_packedColor & 0x000000FF) >> 0;
    UInt8 green  = (_packedColor & 0x0000FF00) >> 8;
    UInt8 blue   = (_packedColor & 0x00FF0000) >> 16;
    UInt8 alpha  = (_packedColor & 0xFF000000) >> 24;

    Int32 margin = style().pixelMetric(QStyle::PM_ButtonMargin, NULL);

    if(_bTransparency == true)
    {
        Real32 floatAlpha = TypeTraits<UInt8>::getFraction(alpha);

        QColor fillColorLight(
            static_cast<UInt8>(floatAlpha * red   + (1.0 - floatAlpha) * 255.0),
            static_cast<UInt8>(floatAlpha * green + (1.0 - floatAlpha) * 255.0),
            static_cast<UInt8>(floatAlpha * blue  + (1.0 - floatAlpha) * 255.0) );
        QColor fillColorDark (
            static_cast<UInt8>(floatAlpha * red                             ),
            static_cast<UInt8>(floatAlpha * green                           ),
            static_cast<UInt8>(floatAlpha * blue                            ) );

        QRect buttonRect = geometry();
        QRect drawRect(margin, margin,
                       (buttonRect.width () - (2 * margin)) / 4,
                       (buttonRect.height() - (2 * margin)) / 2);

        for(UInt32 row = 0; row < 2; ++row)
        {
            for(UInt32 col = 0; col < 2; ++col)
            {
                pPainter->fillRect(drawRect, (row + col) % 2 ? white : black);

                drawRect.moveBy(drawRect.width(), 0);
            }

            for(UInt32 col = 2; col < 4; ++col)
            {
                pPainter->fillRect(drawRect, (row + col) % 2 ? fillColorLight :
                                                               fillColorDark  );

                drawRect.moveBy(drawRect.width(), 0);
            }

            drawRect.moveLeft(margin                                           );
            drawRect.moveTop ((buttonRect.height() - (2 * margin)) / 2 + margin);
        }
    }
    else
    {
        QColor fillColor((_packedColor & 0x000000FF) >> 0,
                         (_packedColor & 0x0000FF00) >> 8,
                         (_packedColor & 0x00FF0000) >> 16);

        QRect buttonRect = geometry();
        QRect drawRect(margin, margin,
                       buttonRect.width () - (2 * margin),
                       buttonRect.height() - (2 * margin) );

        pPainter->fillRect(drawRect, fillColor);
    }
}

// include generated file
#include "OSGQColorButton_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQColorButton_qt.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQCOLORBUTTONQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQCOLORBUTTONQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
