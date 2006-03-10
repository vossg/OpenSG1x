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


#include "OSGQ4FieldLabelFactory.h"
#include "OSGQ4FieldView_qt.h"

#include "OSGQ4FieldValueLabel.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQ4FieldLabelFactory.cpp,v 1.1 2006/03/10 18:30:35 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDLABELFACTORY_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQFIELDLABELFACTORY_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QFieldLabelFactory *QFieldLabelFactory::_the = 0;

QFieldLabelFactory::~QFieldLabelFactory(void)
{
}

QFieldLabelFactory &
QFieldLabelFactory::the(void)
{
    if(!_the)
        _the = new QFieldLabelFactory;

    return *_the;
}

bool
QFieldLabelFactory::registerLabel(const std::string  &strFieldContentName,
                                        LabelCreateF  labelCreateFunc     )
{
    _labelMap[strFieldContentName] = labelCreateFunc;

    return true;
}

QFieldValueLabelBase *
QFieldLabelFactory::createLabel(QFieldViewBase *pView, UInt32 uiIndex)
{
    const Char8 *szContentTypeName = 
        pView->getFieldPtr()->getContentType().getCName();

    LabelMapIt iter = _labelMap.find(szContentTypeName);

    if(iter != _labelMap.end())
    {
        return (*iter).second(pView, uiIndex);
    }
    else
    {
        return _defaultLabelCreateFunc(pView, uiIndex);
    }
}

QFieldLabelFactory::QFieldLabelFactory(void)
    : _labelMap              (                                ),
      _defaultLabelCreateFunc(&QGenericFieldValueLabel::create)
{
}

