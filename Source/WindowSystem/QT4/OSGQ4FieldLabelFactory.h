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

#ifndef _OSGQFIELDLABELFACTORY_H_
#define _OSGQFIELDLABELFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGWindowQT4Def.h"

#include <OSGBaseTypes.h>

#include <string>
#include <map>

#include <qnamespace.h>

OSG_BEGIN_NAMESPACE

class QFieldViewBase;
class QFieldValueLabelBase;

class OSG_WINDOWQTLIB_DLLMAPPING QFieldLabelFactory
{
public:
    typedef QFieldValueLabelBase *(*LabelCreateF)(QFieldViewBase *, UInt32);

    ~QFieldLabelFactory(void);

    static QFieldLabelFactory &the();
    
    bool registerLabel       (const std::string  &strFieldContentsName,
                                    LabelCreateF  labelCreateFunc      );
    bool registerDefaultLabel(const std::string  &strFieldContentsName,
                                    LabelCreateF  labelCreateFunc      );

    QFieldValueLabelBase *createLabel(QFieldViewBase *pView, UInt32 uiIndex);

private:
    typedef std::map<std::string, LabelCreateF>           LabelMap;
    typedef std::map<std::string, LabelCreateF>::iterator LabelMapIt;

    QFieldLabelFactory(void);

    static QFieldLabelFactory *_the;

    LabelMap                   _labelMap;
    LabelCreateF               _defaultLabelCreateFunc;
};

template <class FieldLabelType>
struct QLabelRegisterWrapper
{
    explicit QLabelRegisterWrapper(const std::string &strFieldContentsName);
};

OSG_END_NAMESPACE

#define OSGQFIELDLABELFACTORY_HEADER_CVSID "@(#)$Id: OSGQ4FieldLabelFactory.h,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"

#include "OSGQ4FieldLabelFactory.inl"

#endif /* _OSGQFIELDLABELFACTORY_H_ */
