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

#include "OSGQSpinBoxUInt8_qt.h"

#include <qobject.h>
#include <qapplication.h>
#include <qevent.h>
#include <qrangecontrol.h>
#include <qlineedit.h>

OSG_USING_NAMESPACE

QSpinBoxUInt8::QSpinBoxUInt8(QWidget *pParent, const char *name)
    : Inherited    (pParent, name),
      _bTextChanged(false        ),
      _spinHelper  (             ),
      _pSpinWidget (NULL         )
{
    _pSpinWidget = new QSpinWidget(this, "QSpinBoxUInt8::_pSpinWidget");

    connect(_pSpinWidget, SIGNAL(stepUpPressed  (void)),
            this,         SLOT  (stepUp         (void)) );
    connect(_pSpinWidget, SIGNAL(stepDownPressed(void)),
            this,         SLOT  (stepDown       (void)) );

    _pSpinWidget ->setEditWidget     (getLineEdit());
    getLineEdit()->installEventFilter(this         );

    connect(getLineEdit(), SIGNAL(textChanged      (const QString &)),
            this,          SLOT  (slotTextChanged  (void           )) );
    connect(getLineEdit(), SIGNAL(returnPressed    (void           )),
            this,          SLOT  (slotReturnPressed(void           )) );

    updateDisplay();
}

QSpinBoxUInt8::~QSpinBoxUInt8(void)
{
}

std::string
QSpinBoxUInt8::getValueByStr(void) const
{
    return _spinHelper.getValueByStr();
}

bool
QSpinBoxUInt8::getWrapAround(void) const
{
    return _spinHelper.getWrapAround();
}

void
QSpinBoxUInt8::setWrapAround(bool bWrapAround)
{
    _spinHelper.setWrapAround(bWrapAround);
}

void
QSpinBoxUInt8::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    _pSpinWidget->setEnabled(!bReadOnly);

    updateDisplay();
}


void
QSpinBoxUInt8::setValueByStr(const std::string &strValue)
{
    _spinHelper.setValueByStr(strValue);

    updateDisplay();

    emit valueChanged();
}

void
QSpinBoxUInt8::stepUp(void)
{
    _spinHelper.stepUp();

    updateDisplay();

    emit valueChanged();
}

void
QSpinBoxUInt8::stepDown(void)
{
    _spinHelper.stepDown();

    updateDisplay();

    emit valueChanged();
}

void
QSpinBoxUInt8::stepPageUp(void)
{
    _spinHelper.stepPageUp();

    updateDisplay();

    emit valueChanged();
}

void
QSpinBoxUInt8::stepPageDown(void)
{
    _spinHelper.stepPageDown();

    updateDisplay();

    emit valueChanged();
}

void
QSpinBoxUInt8::slotTextChanged(void)
{
    _bTextChanged = true;
    
    _spinHelper.setValueByStr(getLineEdit()->text().latin1());
    
    emit valueChanged();
}

void
QSpinBoxUInt8::slotReturnPressed(void)
{
    if(_bTextChanged == true)
    {
        _bTextChanged = false;

        _spinHelper.setValueByStr(getLineEdit()->text().latin1());
    }

    updateDisplay();
}

void
QSpinBoxUInt8::updateDisplay(void)
{
    getLineEdit()->setUpdatesEnabled(false                              );
    getLineEdit()->setText          (_spinHelper.getValueByStr().c_str());
    getLineEdit()->setEnabled       (isEnabled() && !getReadOnly()      );
    getLineEdit()->setUpdatesEnabled(true                               );

    getLineEdit()->repaint(false);

    bool bUpEnabled   =
        (isEnabled  ()                == true                       ) &&
        (getReadOnly()                == false                      ) &&
        ((_spinHelper.getValue()      <  _spinHelper.getUpperBound()) ||
         (_spinHelper.getWrapAround() == true                       )   );

    bool bDownEnabled =
        (isEnabled  ()                == true                       ) &&
        (getReadOnly()                == false                      ) &&
        ((_spinHelper.getValue()      >  _spinHelper.getLowerBound()) ||
         (_spinHelper.getWrapAround() == true                       )   );

    _pSpinWidget->setUpEnabled  (bUpEnabled  );
    _pSpinWidget->setDownEnabled(bDownEnabled);

    repaint(false);
}

void
QSpinBoxUInt8::resizeEvent(QResizeEvent *pResizeEvent)
{
    _pSpinWidget->resize(pResizeEvent->size());
}

void
QSpinBoxUInt8::wheelEvent(QWheelEvent *pWheelEvent)
{
    Real32 offset         = pWheelEvent->delta()/120.0;
    Int32  integralOffset = static_cast<Int32>(offset);

    pWheelEvent->accept();

    if(getReadOnly() == true)
        return;

    while(integralOffset < 0)
    {
        ++integralOffset;

        this->stepDown();
    }

    while(integralOffset > 0)
    {
        --integralOffset;

        this->stepUp();
    }
}

bool
QSpinBoxUInt8::eventFilter(QObject *pObj, QEvent *pEvent)
{
    bool retValue = false;

    if(pObj != getLineEdit())
        return Inherited::eventFilter(pObj, pEvent);

    if(pEvent->type() == QEvent::KeyPress)
    {
        QKeyEvent *pKeyEvent = static_cast<QKeyEvent *>(pEvent);
     
        switch(pKeyEvent->key())
        {
            
        case Qt::Key_Tab:
        case Qt::Key_BackTab:
        {
            if(_bTextChanged == true)
            {
                this->slotReturnPressed();
            }
            
            qApp->sendEvent(this, pEvent);
            retValue = true;
            
            break;
        }

        case Qt::Key_Up:
        {
            if(_bTextChanged == true)
            {
                this->slotReturnPressed();
            }
            
            this->stepUp();
            retValue = true;
            
            break;
        }

        case Qt::Key_Down:
        {
            if(_bTextChanged == true)
            {
                this->slotReturnPressed();
            }
            
            this->stepDown();
            retValue = true;
            
            break;
        }

        case Qt::Key_PageUp:
        {
            if(_bTextChanged == true)
            {
                this->slotReturnPressed();
            }
            
            this->stepPageUp();
            retValue = true;
            
            break;
        }

        case Qt::Key_PageDown:
        {
            if(_bTextChanged == true)
            {
                this->slotReturnPressed();
            }
            
            this->stepPageDown();
            retValue = true;
            
            break;
        }

        case Qt::Key_Return:
        case Qt::Key_Enter:
        {
            this->slotReturnPressed();

            break;
        }

        };
    }
    else if((pEvent->type() == QEvent::FocusOut) ||
            (pEvent->type() == QEvent::Hide    )   )
    {
        if(_bTextChanged == true)
        {
            this->slotReturnPressed();
        }
    }

    return retValue;
}

// include generated files
#include "OSGQSpinBoxUInt8_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQSpinBoxUInt8_qt.cpp,v 1.4 2004/11/01 12:24:30 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQSPINBOXUINT8QT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQSPINBOXUINT8QT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
