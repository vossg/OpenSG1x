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

inline Real64
QSpinBoxReal64::getValue(void) const
{
    return _spinHelper.getValue();
}

inline void
QSpinBoxReal64::setValue(Real64 value)
{
    _spinHelper.setValue(value);

    updateDisplay();

    emit valueChanged();
}

inline Real64
QSpinBoxReal64::getLowerBound(void) const
{
    return _spinHelper.getLowerBound();
}


inline void
QSpinBoxReal64::setLowerBound(Real64 lowerBound)
{
    _spinHelper.setLowerBound(lowerBound);
}

inline Real64
QSpinBoxReal64::getUpperBound(void) const
{
    return _spinHelper.getUpperBound();
}

inline void
QSpinBoxReal64::setUpperBound(Real64 upperBound)
{
    _spinHelper.setUpperBound(upperBound);
}

inline Real64
QSpinBoxReal64::getStepSize(void) const
{
    return _spinHelper.getStepSize();
}

inline void
QSpinBoxReal64::setStepSize(Real64 stepSize)
{
    _spinHelper.setStepSize(stepSize);
}

inline Real64
QSpinBoxReal64::getPageStepSize(void) const
{
    return _spinHelper.getPageStepSize();
}

inline void
QSpinBoxReal64::setPageStepSize(Real64 pageStepSize)
{
    _spinHelper.setPageStepSize(pageStepSize);
}

OSG_END_NAMESPACE

#define OSGQSPINBOXREAL64QT_INLINE_CVSID "@(#)$Id: OSGQSpinBoxReal64_qt.inl,v 1.1 2004/07/30 15:32:15 neumannc Exp $"
