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

#include "OSGQOSGWidgetFactory.h"

OSG_USING_NAMESPACE

QOSGWidgetFactory *QOSGWidgetFactory::_the = NULL;

QOSGWidgetFactory *
QOSGWidgetFactory::the(void)
{
    if(_the == NULL)
    {
        _the = new QOSGWidgetFactory();
    }

    return _the;
}

QOSGWidgetFactory *
QOSGWidgetFactory::clone(void)
{
    if(_the == NULL)
    {
        _the = new QOSGWidgetFactory();
    }

    return new QOSGWidgetFactory(*_the);
}

void
QOSGWidgetFactory::registerValueEditor(const DataType      &dataType,
                                             ValueEditorCF  cFunc    )
{
    SINFO << "QOSGWidgetFactory::registerValueEditor: "
          << dataType.getId()
          << " -> "
          << cFunc
          << endLog;

    _typeEditorMap[dataType.getId()] = cFunc;
}

void
QOSGWidgetFactory::registerFCPtrEditor(ValueEditorCF cFunc)
{
    _cfFCPtrEditor = cFunc;
}

void
QOSGWidgetFactory::registerDefaultEditor(ValueEditorCF cFunc)
{
    _cfDefaultEditor = cFunc;
}

QOSGWidgetFactory::ValueEditorCF
QOSGWidgetFactory::getValueEditor(const DataType &dataType)
{
    SINFO << "QOSGWidgetFactory::getValueEditor: " << dataType.getId() << endLog;

    ValueEditorCF    cFunc = NULL;
    ValueEditorMapIt it    = _typeEditorMap.find(dataType.getId());

    if(it != _typeEditorMap.end())
    {
        cFunc = it->second;
    }
    else if(strstr(dataType.getCName(), "Ptr") != NULL)
    {
        cFunc = _cfFCPtrEditor;
    }
    else
    {
        cFunc = _cfDefaultEditor;
    }

    return cFunc;
}

void
QOSGWidgetFactory::registerFieldEditor(const FieldContainerType &fcType,
                                       const FieldType          &fType,
                                       const Char8              *fName,
                                             FieldEditorCF       cFunc    )
{
    UInt32           fcTypeId = fcType.getId(                 );
    UInt32           fTypeId  = fType .getId(                 );
    UInt64           index    = getIndex    (fcTypeId, fTypeId);

    registerFieldEditor(index, fName, cFunc);
}

void
QOSGWidgetFactory::registerFieldEditor(const FieldType     &fType,
                                       const Char8         *fName,
                                             FieldEditorCF  cFunc )
{
    UInt32 fTypeId  = fType.getId(          );
    UInt64 index    = getIndex   (0, fTypeId);

    registerFieldEditor(index, fName, cFunc);
}

void
QOSGWidgetFactory::registerDefaultSFEditor(FieldEditorCF cFunc)
{
    _cfDefaultSFEditor = cFunc;
}

void
QOSGWidgetFactory::registerDefaultMFEditor(FieldEditorCF cFunc)
{
    _cfDefaultMFEditor = cFunc;
}

QOSGWidgetFactory::FieldEditorCF
QOSGWidgetFactory::getFieldEditor(const FieldContainerType &fcType,
                                  const FieldType          &fType,
                                  const Char8              *fName    )
{
    UInt32           fcTypeId = fcType.getId(                 );
    UInt32           fTypeId  = fType .getId(                 );
    UInt64           index    = getIndex    (fcTypeId, fTypeId);

    return getFieldEditor(index, fName, fType.getCardinality());
}

QOSGWidgetFactory::FieldEditorCF
QOSGWidgetFactory::getFieldEditor(const FieldType &fType,
                                  const Char8     *fName )
{
    UInt32 fTypeId = fType.getId(          );
    UInt64 index   = getIndex   (0, fTypeId);

    return getFieldEditor(index, fName, fType.getCardinality());
}

QOSGWidgetFactory::QOSGWidgetFactory(void)
    : _cfFCPtrEditor    (NULL),
      _cfDefaultEditor  (NULL),
      _typeEditorMap    (    ),
      _cfDefaultSFEditor(NULL),
      _cfDefaultMFEditor(NULL),
      _fieldEditorMap   (    )
{
}

QOSGWidgetFactory::QOSGWidgetFactory(const QOSGWidgetFactory &source)
    : _cfFCPtrEditor    (source._cfFCPtrEditor    ),
      _cfDefaultEditor  (source._cfDefaultEditor  ),
      _typeEditorMap    (source._typeEditorMap    ),
      _cfDefaultSFEditor(source._cfDefaultSFEditor),
      _cfDefaultMFEditor(source._cfDefaultMFEditor),
      _fieldEditorMap   (source._fieldEditorMap   )
{
}

void
QOSGWidgetFactory::registerFieldEditor(      UInt64         index,
                                       const Char8         *fName,
                                             FieldEditorCF  cFunc )
{
    FieldEditorMapIt beginFC  = _fieldEditorMap.lower_bound(index);
    FieldEditorMapIt endFC    = _fieldEditorMap.upper_bound(index);

    if(beginFC == endFC)
    {
        _fieldEditorMap.insert(
            std::make_pair(index, FieldEditorMapEntry(fName, cFunc)));
    }
    else
    {
        for(; beginFC != endFC; ++beginFC)
        {
            if((beginFC->second.getFieldName()                == fName) ||
               (strcmp(beginFC->second.getFieldName(), fName) == 0    )   )
            {
                beginFC->second.setCreateFunc(cFunc);

                break;
            }
        }

        if(beginFC == endFC)
        {
            _fieldEditorMap.insert(
                std::make_pair(index, FieldEditorMapEntry(fName, cFunc)));
        }
    }
}

QOSGWidgetFactory::FieldEditorCF
QOSGWidgetFactory::getFieldEditor(      UInt64                  index,
                                  const Char8                  *fName,
                                        FieldType::Cardinality  fCard )
{
    FieldEditorCF    cFunc    = NULL;

    FieldEditorMapIt beginFC  = _fieldEditorMap.lower_bound(index);
    FieldEditorMapIt endFC    = _fieldEditorMap.upper_bound(index);

    if(beginFC == endFC)
    {
        if(fCard == FieldType::SINGLE_FIELD)
        {
            cFunc = _cfDefaultSFEditor;
        }
        else
        {
            cFunc = _cfDefaultMFEditor;
        }
    }
    else
    {
        if(fName == NULL)
        {
            for(; beginFC != endFC; ++beginFC)
            {
                if(beginFC->second.getFieldName() == NULL)
                {
                    cFunc = beginFC->second.getCreateFunc();

                    break;
                }
            }
        }
        else
        {
            for(; beginFC != endFC; ++beginFC)
            {
                if(strcmp(beginFC->second.getFieldName(), fName) == 0)
                {
                    cFunc = beginFC->second.getCreateFunc();

                    break;
                }
            }
        }
    }

    return cFunc;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQOSGWidgetFactory.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQOSGWIDGETFACTORY_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQOSGWIDGETFACTORY_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
