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

#include <OSGSysFieldDataType.h>

#include <qlabel.h>
#include <qlineedit.h>
#include <qtooltip.h>

OSG_BEGIN_NAMESPACE

inline void
QFieldContainerPtrEditor::getValue(FieldContainerPtr &pFC) const
{
    UInt32 uiContId = TypeTraits<UInt32>::getFromString(
                          _pLineEditId->text().latin1());

    pFC = FieldContainerFactory::the()->getContainer(uiContId);
}

inline void
QFieldContainerPtrEditor::setValue(const FieldContainerPtr &pFC)
{
    std::string strBasePtr;
    std::string strInfo;

    if(pFC != NullFC)
    {
        _pLineEditId->blockSignals(true    );
        _pLineEditId->setText(
            TypeTraits<UInt32>::putToString(pFC.getFieldContainerId()).c_str());
        _pLineEditId->blockSignals(false   );

        FieldDataTraits<void *>::putToString(
            pFC.getBaseCPtr(), strBasePtr);

        strInfo.assign(pFC->getType().getCName());
        strInfo.append(" ("                     );
        strInfo.append(strBasePtr               );
        strInfo.append(")"                      );

        QToolTip::add(_pLineEditId, strInfo.c_str());
    }
    else
    {
        _pLineEditId->blockSignals(true    );
        _pLineEditId->setText     ("NullFC");
        _pLineEditId->blockSignals(false   );

        QToolTip::add(_pLineEditId, "NullFC (0x0)");
    }
}

OSG_END_NAMESPACE

#define OSGQFIELDCONTAINERPTREDITORQT_INLINE_CVSID "@(#)$Id: OSGQFieldContainerPtrEditor_qt.inl,v 1.4 2004/08/14 18:17:01 a-m-z Exp $"
