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

#ifndef _OSGQOSGWIDGETFACTORYHELPER_H_
#define _OSGQOSGWIDGETFACTORYHELPER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

#include "OSGQOSGWidgetFactory.h"

OSG_BEGIN_NAMESPACE

class ValueEditorRegistrator
{
  public:
    typedef QOSGWidgetFactory::ValueEditorCF ValueEditorCF;

    enum RegisterSelectionE
    {
        FCPtrEditor,
        DefaultValueEditor
    };

    ValueEditorRegistrator(const DataType           &dataType,
                                 ValueEditorCF       cFunc        );
    ValueEditorRegistrator(      RegisterSelectionE  regSelection,
                                 ValueEditorCF       cFunc        );
};

class FieldEditorRegistrator
{
  public:
    typedef QOSGWidgetFactory::FieldEditorCF FieldEditorCF;

    FieldEditorRegistrator(const FieldContainerType     &fcType,
                           const FieldType              &fType,
                           const Char8                  *fName,
                                 FieldEditorCF           cFunc  );

    FieldEditorRegistrator(const FieldType              &fType,
                           const Char8                  *fName,
                                 FieldEditorCF           cFunc  );

    FieldEditorRegistrator(      FieldEditorCF           cFunc,
                                 FieldType::Cardinality  card   );
};

OSG_END_NAMESPACE

//#include "OSGQOSGWidgetFactoryHelper.inl"

#define OSGQOSGWIDGETFACTORYHELPER_HEADER_CVSID "@(#)$Id: OSGQOSGWidgetFactoryHelper.h,v 1.1 2004/07/30 15:31:57 neumannc Exp $"

#endif /* _OSGQOSGWIDGETFACTORYHELPER_H_ */
