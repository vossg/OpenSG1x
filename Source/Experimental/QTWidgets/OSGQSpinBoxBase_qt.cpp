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

#include "OSGQSpinBoxBase_qt.h"
#include <OSGBaseTypes.h>

#include <qlineedit.h>

OSG_USING_NAMESPACE

QSpinBoxBase::QSpinBoxBase(QWidget *pParent, const char *name)
    : Inherited (pParent, name),
      _bReadOnly(false        ),
      _pLineEdit(NULL         )
{
    _pLineEdit = new QLineEdit(this, "QSpinBoxBase::_pLineEdit");

    _pLineEdit->setFrame(false);

    setFocusProxy(_pLineEdit);
}


QSpinBoxBase::~QSpinBoxBase(void)
{
}

void
QSpinBoxBase::setReadOnly(bool bReadOnly)
{
    _bReadOnly = bReadOnly;
}

// include generated file
#include "OSGQSpinBoxBase_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQSpinBoxBase_qt.cpp,v 1.1 2004/07/30 15:32:15 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQSPINBOXBASEQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQSPINBOXBASEQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
