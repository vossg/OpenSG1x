
OSG_BEGIN_NAMESPACE

template <class ValueTypeT>
SpinBoxHelper<ValueTypeT>::SpinBoxHelper(void)
    : _bWrapAround (false                                   ),
      _value       (TypeTraits<ValueTypeT>::getZeroElement()),
      _lowerBound  (Traits::_initLowerBound                 ),
      _upperBound  (Traits::_initUpperBound                 ),
      _stepSize    (Traits::_defaultStepSize                ),
      _pageStepSize(Traits::_defaultPageStepSize            )
{
    if(_value > _upperBound)
    {
        _value = _upperBound;
    }
    else if(_value < _lowerBound)
    {
        _value = _lowerBound;
    }
}

template <class ValueTypeT>
SpinBoxHelper<ValueTypeT>::SpinBoxHelper(
    ValueType initialValue, ValueType lowerBound,
    ValueType upperBound,   ValueType stepSize,
    ValueType pageStepSize                       )

    : _bWrapAround (false       ),
      _value       (initalValue ),
      _lowerBound  (lowerBound  ),
      _upperBound  (upperBound  ),
      _stepSize    (stepSize    ),
      _pageStepSize(pageStepSize)
{
    if(_value > _upperBound)
    {
        _value = _upperBound;
    }
    else if(_value < _lowerBound)
    {
        _value = _lowerBound;
    }
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::stepUp(void)
{
    stepUp(_stepSize);
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::stepDown(void)
{
    stepDown(_stepSize);
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::stepPageUp(void)
{
    stepUp(_pageStepSize);
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::stepPageDown(void)
{
    stepDown(_pageStepSize);
}

template <class ValueTypeT>
typename SpinBoxHelper<ValueTypeT>::ValueType
SpinBoxHelper<ValueTypeT>::getValue(void) const
{
    return _value;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setValue(ValueType value)
{
    if(value > _upperBound)
    {
        _value = _upperBound;
    }
    else if(value < _lowerBound)
    {
        _value = _lowerBound;
    }
    else
    {
        _value = value;
    }
}

template <class ValueTypeT>
std::string
SpinBoxHelper<ValueTypeT>::getValueByStr(void) const
{
    return TypeTraits<ValueType>::putToString(_value);
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setValueByStr(const std::string &strValue)
{
    _value = TypeTraits<ValueType>::getFromString(strValue.c_str());
}

template <class ValueTypeT>
bool
SpinBoxHelper<ValueTypeT>::getWrapAround(void) const
{
    return _bWrapAround;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setWrapAround(bool bWrapAround)
{
    _bWrapAround = bWrapAround;
}

template <class ValueTypeT>
typename SpinBoxHelper<ValueTypeT>::ValueType
SpinBoxHelper<ValueTypeT>::getLowerBound(void) const
{
    return _lowerBound;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setLowerBound(ValueType lowerBound)
{
    _lowerBound = lowerBound;

    if(_value < _lowerBound)
    {
        _value = _lowerBound;
    }
}

template <class ValueTypeT>
typename SpinBoxHelper<ValueTypeT>::ValueType
SpinBoxHelper<ValueTypeT>::getUpperBound(void) const
{
    return _upperBound;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setUpperBound(ValueType upperBound)
{
    _upperBound = upperBound;

    if(_value > _upperBound)
    {
        _value = _upperBound;
    }
}

template <class ValueTypeT>
typename SpinBoxHelper<ValueTypeT>::ValueType
SpinBoxHelper<ValueTypeT>::getStepSize(void) const
{
    return _stepSize;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setStepSize(ValueType stepSize)
{
    _stepSize = stepSize;
}

template <class ValueTypeT>
typename SpinBoxHelper<ValueTypeT>::ValueType
SpinBoxHelper<ValueTypeT>::getPageStepSize(void) const
{
    return _pageStepSize;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setPageStepSize(ValueType pageStepSize)
{
    _pageStepSize = pageStepSize;
}

template <class ValueTypeT>
typename SpinBoxHelper<ValueTypeT>::ValueType
SpinBoxHelper<ValueTypeT>::getDefaultStepSize(void)
{
    return Traits::_defaultStepSize;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setDefaultStepSize(ValueType stepSize)
{
    Traits::_defaultStepSize = stepSize;
}

template <class ValueTypeT>
typename SpinBoxHelper<ValueTypeT>::ValueType
SpinBoxHelper<ValueTypeT>::getDefaultPageStepSize(void)
{
    return Traits::_defaultPageStepSize;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::setDefaultPageStepSize(ValueType pageStepSize)
{
    Traits::_defaultPageStepSize = pageStepSize;
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::stepUp(ValueType stepSize)
{
    typename Traits::DeltaType delta = _upperBound - _value;

    if(delta >= stepSize)
    {
        _value += stepSize;
    }
    else
    {
        if(_bWrapAround)
        {
            _value = _lowerBound + (stepSize - delta);
        }
        else
        {
            _value = _upperBound;
        }
    }
}

template <class ValueTypeT>
void
SpinBoxHelper<ValueTypeT>::stepDown(ValueType stepSize)
{
    typename Traits::DeltaType delta = _value - _lowerBound;

    if(delta >= stepSize)
    {
        _value -= stepSize;
    }
    else
    {
        if(_bWrapAround)
        {
            _value = _upperBound - (stepSize - delta);
        }
        else
        {
            _value = _lowerBound;
        }
    }
}

OSG_END_NAMESPACE

#define OSGSPINBOXHELPER_INLINE_CVSID "@(#)$Id: OSGSpinBoxHelper.inl,v 1.1 2004/07/30 15:32:15 neumannc Exp $"
