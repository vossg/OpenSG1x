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

#ifndef _OSGQCOLORBUTTON_QT_H_
#define _OSGQCOLORBUTTON_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGBaseTypes.h>

#include <qbutton.h>

OSG_BEGIN_NAMESPACE

class QColorButton : public QButton
{
    Q_OBJECT

  public:
    QColorButton(QWidget *pParent = NULL, const char *name = NULL,
                 WFlags   flags   = 0                             );

    virtual ~QColorButton(void);

    inline UInt32 getPackedColor (void                ) const;
    inline void   setPackedColor (UInt32 packedColor  );

    inline bool   getTransparency(void                ) const;
    inline void   setTransparency(bool   bTransparency);

  protected:
    virtual void drawButton     (QPainter *pPainter);
    virtual void drawButtonLabel(QPainter *pPainter);

  private:
    typedef QButton Inherited;

    UInt32 _packedColor;
    bool   _bTransparency;
};

OSG_END_NAMESPACE

#include "OSGQColorButton_qt.inl"

#define OSGQCOLORBUTTONQT_HEADER_CVSID "@(#)$Id: OSGQColorButton_qt.h,v 1.1 2004/07/30 15:31:57 neumannc Exp $"

#endif /* _OSGQCOLORBUTTON_QT_H_ */
