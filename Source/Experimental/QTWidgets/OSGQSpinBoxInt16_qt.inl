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

inline Int16
QSpinBoxInt16::getValue(void) const
{
    return _spinHelper.getValue();
}

inline void
QSpinBoxInt16::setValue(Int16 value)
{
    _spinHelper.setValue(value);

    updateDisplay();

    emit valueChanged();
}

inline Int16
QSpinBoxInt16::getLowerBound(void) const
{
    return _spinHelper.getLowerBound();
}


inline void
QSpinBoxInt16::setLowerBound(Int16 lowerBound)
{
    _spinHelper.setLowerBound(lowerBound);
}

inline Int16
QSpinBoxInt16::getUpperBound(void) const
{
    return _spinHelper.getUpperBound();
}

inline void
QSpinBoxInt16::setUpperBound(Int16 upperBound)
{
    _spinHelper.setUpperBound(upperBound);
}

inline Int16
QSpinBoxInt16::getStepSize(void) const
{
    return _spinHelper.getStepSize();
}

inline void
QSpinBoxInt16::setStepSize(Int16 stepSize)
{
    _spinHelper.setStepSize(stepSize);
}

inline Int16
QSpinBoxInt16::getPageStepSize(void) const
{
    return _spinHelper.getPageStepSize();
}

inline void
QSpinBoxInt16::setPageStepSize(Int16 pageStepSize)
{
    _spinHelper.setPageStepSize(pageStepSize);
}

OSG_END_NAMESPACE

#define OSGQSPINBOXINT16QT_INLINE_CVSID "@(#)$Id: OSGQSpinBoxInt16_qt.inl,v 1.1 2004/07/30 15:32:15 neumannc Exp $"
