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

#include "OSGQ4FieldEditorFactory.h"
#include "OSGQ4FieldView_qt.h"
#include "OSGQ4FieldEditor_qt.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQ4FieldEditorFactory.cpp,v 1.1 2006/03/10 18:30:35 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDEDITORFACTORY_HEADER_CVSID;
//    static Char8 cvsid_inl[] = OSGQFIELDEDITORFACTORY_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QFieldEditorFactory *QFieldEditorFactory::_the = 0;

QFieldEditorFactory::~QFieldEditorFactory(void)
{
}

QFieldEditorFactory &
QFieldEditorFactory::the(void)
{
    if(!_the)
        _the = new QFieldEditorFactory;

    return *_the;
}

QFieldEditorBase *
QFieldEditorFactory::createEditor(      QFieldViewBase *pView,
                                  const char           *name  )
{
    return new QGenericFieldEditor(pView, name);
}

QFieldEditorBase *
QFieldEditorFactory::createEditor(      UInt32  uiIndex, QFieldViewBase *pView,
                                  const char   *name)
{
    return new QGenericFieldEditor(uiIndex, pView, name);
}

QFieldEditorFactory::QFieldEditorFactory(void)
{
}
