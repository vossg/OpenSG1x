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

OSG_BEGIN_NAMESPACE

inline UInt32
QSpinBoxUInt32::getValue(void) const
{
    return _spinHelper.getValue();
}

inline void
QSpinBoxUInt32::setValue(UInt32 value)
{
    _spinHelper.setValue(value);

    updateDisplay();

    emit valueChanged();
}

inline UInt32
QSpinBoxUInt32::getLowerBound(void) const
{
    return _spinHelper.getLowerBound();
}

inline void
QSpinBoxUInt32::setLowerBound(UInt32 lowerBound)
{
    _spinHelper.setLowerBound(lowerBound);
}

inline UInt32
QSpinBoxUInt32::getUpperBound(void) const
{
    return _spinHelper.getUpperBound();
}

inline void
QSpinBoxUInt32::setUpperBound(UInt32 upperBound)
{
    _spinHelper.setUpperBound(upperBound);
}

inline UInt32
QSpinBoxUInt32::getStepSize(void) const
{
    return _spinHelper.getStepSize();
}

inline void
QSpinBoxUInt32::setStepSize(UInt32 stepSize)
{
    _spinHelper.setStepSize(stepSize);
}

inline UInt32
QSpinBoxUInt32::getPageStepSize(void) const
{
    return _spinHelper.getPageStepSize();
}

inline void
QSpinBoxUInt32::setPageStepSize(UInt32 pageStepSize)
{
    _spinHelper.setPageStepSize(pageStepSize);
}

OSG_END_NAMESPACE

#define OSGQSPINBOXUINT32QT_INLINE_CVSID "@(#)$Id: OSGQSpinBoxUInt32_qt.inl,v 1.1 2004/07/30 15:32:15 neumannc Exp $"
