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

#ifndef _OSGFIELDEDITORFACTORY_H_
#define _OSGFIELDEDITORFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"

#include <OSGBaseTypes.h>

#include <qnamespace.h>

class QWidget;

OSG_BEGIN_NAMESPACE

class QFieldViewBase;
class QFieldEditorBase;

class OSG_QTWIDGETLIB_DLLMAPPING QFieldEditorFactory : public Qt
{
public:
    ~QFieldEditorFactory(void);

    static QFieldEditorFactory &the();

    QFieldEditorBase *createEditor(      QFieldViewBase *pView,
                                   const char           *name = 0);

    QFieldEditorBase *createEditor(      UInt32          uiIndex,
                                         QFieldViewBase *pView,  
                                   const char           *name = 0);
private:
    QFieldEditorFactory(void);

    static QFieldEditorFactory *_the;
};

OSG_END_NAMESPACE

#define OSGQFIELDEDITORFACTORY_HEADER_CVSID "@(#)$Id: OSGQFieldEditorFactory.h,v 1.3 2003/05/19 07:36:41 neumannc Exp $"

// #include "OSGQFieldEditorFactory.inl"

#endif /* _OSGQFIELDEDITORFACTORY_H_ */
