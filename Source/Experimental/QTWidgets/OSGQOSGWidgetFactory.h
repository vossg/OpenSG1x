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

#ifndef _OSGQOSGWIDGETFACTORY_H_
#define _OSGQOSGWIDGETFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGField.h>
#include <OSGFieldContainer.h>

#include <OSGQAbstractValueEditor_qt.h>
#include <OSGQAbstractFieldEditor_qt.h>

#include <qwidget.h>

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QOSGWidgetFactory
{
  public:
    typedef QAbstractValueEditor *(*ValueEditorCF)(QWidget *, const char *);
    typedef QAbstractFieldEditor *(*FieldEditorCF)(QWidget *, const char *);

    static QOSGWidgetFactory *the  (void);
    static QOSGWidgetFactory *clone(void);

    void          registerValueEditor    (const DataType           &dataType,
                                                ValueEditorCF       cFunc    );
    void          registerFCPtrEditor    (      ValueEditorCF       cFunc    );
    void          registerDefaultEditor  (      ValueEditorCF       cFunc    );

    ValueEditorCF getValueEditor         (const DataType           &dataType );

    void          registerFieldEditor    (const FieldContainerType &fcType,
                                          const FieldType          &fType,
                                          const Char8              *fName,
                                                FieldEditorCF       cFunc    );
    void          registerFieldEditor    (const FieldType          &fType,
                                          const Char8              *fName,
                                                FieldEditorCF       cFunc    );

    void          registerDefaultSFEditor(      FieldEditorCF       cFunc    );
    void          registerDefaultMFEditor(      FieldEditorCF       cFunc    );

    FieldEditorCF getFieldEditor         (const FieldContainerType &fcType,
                                          const FieldType          &fType,
                                          const Char8              *fName    );
    FieldEditorCF getFieldEditor         (const FieldType          &fType,
                                          const Char8              *fName    );

  private:
    typedef std::map<UInt32, ValueEditorCF> ValueEditorMap;
    typedef ValueEditorMap::iterator        ValueEditorMapIt;
    typedef ValueEditorMap::const_iterator  ValueEditorMapConstIt;

    class FieldEditorMapEntry
    {
      public:
        inline  FieldEditorMapEntry(      void                 );
        inline  FieldEditorMapEntry(const Char8         *fName,
                                          FieldEditorCF  cFunc );
        inline ~FieldEditorMapEntry(      void                 );

        inline const Char8         *getFieldName  (void               ) const;
        inline       void           setFieldName  (const Char8  *fName);

        inline       FieldEditorCF  getCreateFunc (void               ) const;
        inline       void           setCreateFunc (FieldEditorCF cFunc);

      private:
        const Char8         *_fName;
              FieldEditorCF  _cfFieldEditor;
    };

    typedef std::multimap<UInt64, FieldEditorMapEntry> FieldEditorMap;
    typedef FieldEditorMap::iterator                   FieldEditorMapIt;
    typedef FieldEditorMap::const_iterator             FieldEditorMapConstIt;

    QOSGWidgetFactory(void                           );
    QOSGWidgetFactory(const QOSGWidgetFactory &source);

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator=     (const QOSGWidgetFactory &source);

    inline UInt64 getIndex   (UInt32 fcTypeId, UInt32 fTypeId);
    inline UInt32 getFCTypeId(UInt64 index                   );
    inline UInt32 getFTypeId (UInt64 index                   );

    void          registerFieldEditor(      UInt64                  index,
                                      const Char8                  *fname,
                                            FieldEditorCF           cFunc );
    FieldEditorCF getFieldEditor     (      UInt64                  index,
                                      const Char8                  *fName,
                                            FieldType::Cardinality  fCard );

    static QOSGWidgetFactory *_the;

    ValueEditorCF  _cfFCPtrEditor;
    ValueEditorCF  _cfDefaultEditor;
    ValueEditorMap _typeEditorMap;

    FieldEditorCF  _cfDefaultSFEditor;
    FieldEditorCF  _cfDefaultMFEditor;
    FieldEditorMap _fieldEditorMap;

};

OSG_END_NAMESPACE

#include "OSGQOSGWidgetFactory.inl"

#define OSGQOSGWIDGETFACTORY_HEADER_CVSID "@(#)$Id: OSGQOSGWidgetFactory.h,v 1.1 2004/07/30 15:31:57 neumannc Exp $"

#endif /* _OSGQOSGWIDGETFACTORY_H_ */
