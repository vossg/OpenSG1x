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

#include "OSGQOSGWidgetFactoryHelper.h"

OSG_USING_NAMESPACE

ValueEditorRegistrator::ValueEditorRegistrator(
    const DataType &dataType, ValueEditorCF cFunc)
{
    QOSGWidgetFactory::the()->registerValueEditor(dataType, cFunc);
}

ValueEditorRegistrator::ValueEditorRegistrator(
    RegisterSelectionE regSelection, ValueEditorCF cFunc)
{
    switch(regSelection)
    {
    case ValueEditorRegistrator::FCPtrEditor:
        QOSGWidgetFactory::the()->registerFCPtrEditor(cFunc);
        break;

    case ValueEditorRegistrator::DefaultValueEditor:
        QOSGWidgetFactory::the()->registerDefaultEditor(cFunc);
        break;
    };
}


FieldEditorRegistrator::FieldEditorRegistrator(
    const FieldContainerType &fcType, const FieldType     &fType,
    const Char8              *fName,        FieldEditorCF  cFunc  )
{
    QOSGWidgetFactory::the()->registerFieldEditor(fcType, fType, fName, cFunc);
}

FieldEditorRegistrator::FieldEditorRegistrator(
    const FieldType     &fType, const Char8 *fName,
          FieldEditorCF  cFunc                     )
{
    QOSGWidgetFactory::the()->registerFieldEditor(fType, fName, cFunc);
}

FieldEditorRegistrator::FieldEditorRegistrator(
    FieldEditorCF cFunc, FieldType::Cardinality card)
{
    switch(card)
    {
    case FieldType::SINGLE_FIELD:
        QOSGWidgetFactory::the()->registerDefaultSFEditor(cFunc);
        break;

    case FieldType::MULTI_FIELD:
        QOSGWidgetFactory::the()->registerDefaultMFEditor(cFunc);
        break;
    };
}

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
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGQOSGWidgetFactoryHelper.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGQOSGWIDGETFACTORYHELPER_HEADER_CVSID;
//    static Char8 cvsid_inl     [] = OSGQOSGWIDGETFACTORYHELPER_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
