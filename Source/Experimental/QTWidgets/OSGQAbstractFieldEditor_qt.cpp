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

#include "OSGQAbstractFieldEditor_qt.h"
#include <OSGQOSGWidgetFactory.h>

#include <qpixmap.h>

#include <OSGNo.xpm>
#include <OSGYes.xpm>

OSG_USING_NAMESPACE

QPixmap *QAbstractFieldEditor::_pPixmapNo  = NULL;
QPixmap *QAbstractFieldEditor::_pPixmapYes = NULL;

QAbstractFieldEditor::~QAbstractFieldEditor(void)
{
}

void
QAbstractFieldEditor::setField(FieldContainerPtr fcPtr, UInt32 uiFieldId)
{
    _fcPtr     = fcPtr;
    _uiFieldId = uiFieldId;
}

void
QAbstractFieldEditor::setReadOnly(bool bReadOnly)
{
    _bReadOnly = bReadOnly;
}

void
QAbstractFieldEditor::setLabelsVisible(bool bVisible)
{
    _bLabelsVisible = bVisible;
}

void
QAbstractFieldEditor::setActionButtonsVisible(bool bVisible)
{
    _bActionButtonsVisible = bVisible;
}

QAbstractFieldEditor::QAbstractFieldEditor(QWidget *pParent, const char *name)
    : Inherited             (pParent, name           ),
      _fcPtr                (NullFC                  ),
      _uiFieldId            (0                       ),
      _bReadOnly            (false                   ),
      _bActionButtonsVisible(false                   ),
      _pFactory             (QOSGWidgetFactory::the())
{
    if(_pPixmapNo == NULL)
    {
        _pPixmapNo = new QPixmap(XPMNo);
    }

    if(_pPixmapYes == NULL)
    {
        _pPixmapYes = new QPixmap(XPMYes);
    }
}

// include generated file
#include "OSGQAbstractFieldEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQAbstractFieldEditor_qt.cpp,v 1.3 2004/08/13 12:33:06 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQABSTRACTFIELDEDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQABSTRACTFIELDEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
