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

#include "OSGQMatrixEditor_qt.h"
#include <OSGQSpinBoxReal32_qt.h>

#include <OSGMatrix.h>
#include <OSGMatrixFields.h>

#include <qlayout.h>
#include <qlabel.h>

OSG_USING_NAMESPACE

QAbstractValueEditor *
QMatrixEditor::create(QWidget *pParent, const char *name)
{
    return new QMatrixEditor(pParent, name);
}

QMatrixEditor::QMatrixEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

QMatrixEditor::~QMatrixEditor(void)
{
}

void
QMatrixEditor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);

    if(bLabels == true)
    {
        for(UInt32 i = 0; i < 16; ++i)
        {
            _pLabels[i]->show();
        }
    }
    else
    {
        for(UInt32 i = 0; i < 16; ++i)
        {
            _pLabels[i]->show();
        }
    }
}

void
QMatrixEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    for(UInt32 i = 0; i < 16; ++i)
    {
        _pSpinBoxes[i]->setReadOnly(bReadOnly);
    }
}

void
QMatrixEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex, UInt32 uiAspect  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        const SFMatrix *pSF = dynamic_cast<const SFMatrix *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < 16; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true                          );
            _pSpinBoxes[i]->setValue    (pSF->getValue().getValues()[i]);
            _pSpinBoxes[i]->blockSignals(false                         );
        }
    }
    else
    {
        const MFMatrix *pMF = dynamic_cast<const MFMatrix *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < 16; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true                               );
            _pSpinBoxes[i]->setValue    ((*pMF)[uiValueIndex].getValues()[i]);
            _pSpinBoxes[i]->blockSignals(false                              );
        }
    }
}

void
QMatrixEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    readField(pFC, uiFieldId, uiValueIndex, Thread::getCurrent()->getAspect());
}

void
QMatrixEditor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                          UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SFMatrix *pSF = dynamic_cast<SFMatrix *>(pFC->getField(uiFieldId));

        for(UInt32 i = 0; i < 16; ++i)
        {
            pSF->getValue().getValues()[i] = _pSpinBoxes[i]->getValue();
        }
    }
    else
    {
        MFMatrix *pMF = dynamic_cast<MFMatrix *>(pFC->getField(uiFieldId));

        for(UInt32 i = 0; i < 16; ++i)
        {
            (*pMF)[uiValueIndex].getValues()[i] = _pSpinBoxes[i]->getValue();
        }
    }
}

void QMatrixEditor::createChildWidgets(void)
{
    _pGrid = new QGridLayout(this, 4, 9, 0, 1, "QMatrixEditor::_pGrid");

    _pLabels   [0]  = new QLabel        ("0,0", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[0]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");
    _pLabels   [1]  = new QLabel        ("1,0", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[1]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");
    _pLabels   [2]  = new QLabel        ("2,0", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[2]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");
    _pLabels   [3]  = new QLabel        ("3,0", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[3]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");

    _pLabels   [4]  = new QLabel        ("0,1", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[4]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");
    _pLabels   [5]  = new QLabel        ("1,1", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[5]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");
    _pLabels   [6]  = new QLabel        ("2,1", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[6]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");
    _pLabels   [7]  = new QLabel        ("3,1", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[7]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");

    _pLabels   [8]  = new QLabel        ("0,2", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[8]  = new QSpinBoxReal32(this,
                                         "QMatrixEditor::_pSpinBoxes");
    _pLabels   [9]  = new QLabel        ("1,2", this,
                                         "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[9]  = new QSpinBoxReal32(this,
                                        "QMatrixEditor::_pSpinBoxes");
    _pLabels   [10] = new QLabel        ("2,2", this,
                                        "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[10] = new QSpinBoxReal32(this,
                                        "QMatrixEditor::_pSpinBoxes");
    _pLabels   [11] = new QLabel        ("3,2", this,
                                        "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[11] = new QSpinBoxReal32(this,
                                        "QMatrixEditor::_pSpinBoxes");

    _pLabels   [12] = new QLabel        ("0,3", this,
                                        "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[12] = new QSpinBoxReal32(this,
                                        "QMatrixEditor::_pSpinBoxes");
    _pLabels   [13] = new QLabel        ("1,3", this,
                                        "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[13] = new QSpinBoxReal32(this,
                                        "QMatrixEditor::_pSpinBoxes");
    _pLabels   [14] = new QLabel        ("2,3", this,
                                        "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[14] = new QSpinBoxReal32(this,
                                        "QMatrixEditor::_pSpinBoxes");
    _pLabels   [15] = new QLabel        ("3,3", this,
                                        "QMatrixEditor::_pLabels"   );
    _pSpinBoxes[15] = new QSpinBoxReal32(this,
                                        "QMatrixEditor::_pSpinBoxes");
}

void QMatrixEditor::layoutChildWidgets(void)
{
    for(UInt32 col = 0; col < 4; ++col)
    {
        for(UInt32 row = 0; row < 4; ++row)
        {
            _pGrid->addWidget(_pLabels   [4 * col + row], row, 2 * col    );
            _pGrid->addWidget(_pSpinBoxes[4 * col + row], row, 2 * col + 1);
        }

        _pGrid->setColStretch(2 * col,      0);
        _pGrid->setColStretch(2 * col + 1, 10);
    }

    _pGrid->addMultiCellWidget(this->getActionButton(), 0, 9, 4, 9);
}

void QMatrixEditor::initSelf(void)
{
}

// include generated file
#include "OSGQMatrixEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQMatrixEditor_qt.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQMATRIXEDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQMATRIXEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
