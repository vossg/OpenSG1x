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

inline Int8
QSpinBoxInt8::getValue(void) const
{
    return _spinHelper.getValue();
}

inline void
QSpinBoxInt8::setValue(Int8 value)
{
    _spinHelper.setValue(value);

    updateDisplay();

    emit valueChanged();
}

inline Int8
QSpinBoxInt8::getLowerBound(void) const
{
    return _spinHelper.getLowerBound();
}

inline void
QSpinBoxInt8::setLowerBound(Int8 lowerBound)
{
    _spinHelper.setLowerBound(lowerBound);
}

inline Int8
QSpinBoxInt8::getUpperBound(void) const
{
    return _spinHelper.getUpperBound();
}

inline void
QSpinBoxInt8::setUpperBound(Int8 upperBound)
{
    _spinHelper.setUpperBound(upperBound);
}

inline Int8
QSpinBoxInt8::getStepSize(void) const
{
    return _spinHelper.getStepSize();
}

inline void
QSpinBoxInt8::setStepSize(Int8 stepSize)
{
    _spinHelper.setStepSize(stepSize);
}

inline Int8
QSpinBoxInt8::getPageStepSize(void) const
{
    return _spinHelper.getPageStepSize();
}

inline void
QSpinBoxInt8::setPageStepSize(Int8 pageStepSize)
{
    _spinHelper.setPageStepSize(pageStepSize);
}

OSG_END_NAMESPACE

#define OSGQSPINBOXINT8QT_INLINE_CVSID "@(#)$Id: OSGQSpinBoxInt8_qt.inl,v 1.1 2004/07/30 15:32:15 neumannc Exp $"
