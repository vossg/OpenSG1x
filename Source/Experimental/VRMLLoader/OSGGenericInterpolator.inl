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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! \brief Linear interpolation between p1 and p2
    \lambda in the range [0,1]
    \return linear interpolated value 
 */

template<class T>
T linearInterpol(T& p1, T& p2, OSG::Real32 lambda)
{
    return ( p2*lambda + p1*(1.0-lambda) );
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

inline 
InterpolatorBase::InterpolType InterpolatorBase::getType(void) const 
{ 
    return _type; 
}

inline 
void InterpolatorBase::setTargetName(const std::string& name) 
{ 
    _targetName = name; 
}

inline 
const std::string& InterpolatorBase::getTargetName(void) 
{ 
    return _targetName; 
}

inline
void InterpolatorBase::setTargetTransform(ComponentTransformPtr pTransform)
{
    _pTransform = pTransform;
}

inline 
void InterpolatorBase::addKey(Real32 key) 
{   
    _keys.push_back(key); 
}

inline 
Int32 InterpolatorBase::nrOfKeys() const 
{ 
    return _keys.size(); 
}

inline 
std::vector<Real32> &InterpolatorBase::getKeys() 
{ 
    return _keys;
}   

inline 
void InterpolatorBase::setDuration(const Real32 duration) 
{ 
    _duration=duration; 
}

inline  
Real32  InterpolatorBase::getDuration(void) const 
{ 
    return _duration; 
}

inline 
void InterpolatorBase::setLoop(bool loopon) 
{ 
    _loop = loopon; 
}

inline 
bool InterpolatorBase::isLooping(void) const 
{ 
    return _loop; 
}   

inline 
void InterpolatorBase::setScaleInterpol(bool scale) 
{
    _isScale = scale;
}


inline 
bool InterpolatorBase::isScaleInterpol(void) const
{
    return _isScale;
}

inline Real32 InterpolatorBase::time2key(Real32 time)
{
    std::vector<Real32> &keys         = getKeys();
    int                  lastKeyIndex;
    Real64               lambda;
    
    lambda        = time / getDuration();  
    lambda       -= floor(lambda);    
    
    lastKeyIndex  = keys.size() - 1;
    
    if(lambda > keys[lastKeyIndex] && !isLooping())
    {
        return keys[lastKeyIndex];
    }
    else 
    {       
        return linearInterpol(keys[0], keys[lastKeyIndex], lambda);
    }
}

inline 
const std::string InterpolatorBase::type2String(InterpolType t)
{ 
    switch(t)
    {
        case Position:
            return std::string("Position");
        case Orientation:
            return std::string("Orientation");
        case Unused:
            return std::string("Unused");
        case Other:
            return std::string("Other");
        default:
            return std::string("Unknown");
    }
}

inline 
void InterpolatorBase::setName(const std::string& name) 
{ 
    _name = name; 
}

inline 
std::string& InterpolatorBase::getName(void) 
{ 
    return _name; 
}


template <class KeyValueType>
Interpolator<KeyValueType>::Interpolator(InterpolType t) :
    InterpolatorBase(t)     
{
}

template <class KeyValueType>
Interpolator<KeyValueType>::~Interpolator(void) 
{
}

template <class KeyValueType>
void Interpolator<KeyValueType>::addKeyValue(const KeyValueType& value)
{
    _keyValues.push_back( value );
}


template <class KeyValueType>
void Interpolator<KeyValueType>::addKeyValuePair(      Real32        key, 
                                                 const KeyValueType& value)
{
    _keys.push_back     (key);
    _keyValues.push_back(value);
}

template <class KeyValueType>
Int32 Interpolator<KeyValueType>::nrOfKeyValues(void) const 
{
    return _keyValues.size(); 
} 

template <class KeyValueType>
KeyValueType Interpolator<KeyValueType>::getValue(Real32 key)
{
    std::vector<Real32>::iterator keyIter;
    std::vector<Real32>          &keys    = getKeys();
    Int32                         ipos    = -1;
    Real32                        keyDiff; 
    
    keyIter = std::find(keys.begin(), keys.end(), key);
    
    if(keyIter != keys.end())
    {
        ipos = keyIter - keys.begin();          

        return _keyValues[ipos];
    }
    
    keyIter = std::find_if(keys.begin(), 
                           keys.end(), 
                           std::bind2nd(std::greater<Real32>(), key));

    ipos    = keyIter - keys.begin();

    keyDiff =  1.0 / (keys[ipos] - keys[ipos - 1]);

    return linearInterpol(_keyValues [ipos-1], 
                          _keyValues [ipos  ], 
                          (key - keys[ipos-1]) * keyDiff);
}

template <>
inline Quaternion Interpolator<Quaternion>::getValue(Real32 key)
{
    std::vector<Real32>::iterator keyIter;
    Quaternion                    q1,q2,q3;
    Real32                        keyDiff; 
    Int32                         ipos     = -1;
    std::vector<Real32>          &keys     = getKeys();
    
    keyIter = std::find(keys.begin(), keys.end(), key);
    
    // --- found desired key
    if(keyIter != keys.end())
    {
        ipos = keyIter - keys.begin();

        return _keyValues[ipos];
    }

    // --- didn't find key -> interpolate   
    
    // find key greater than the desired one
    keyIter = std::find_if(keys.begin(), keys.end(), 
                           std::bind2nd(std::greater<Real32>(), key));

    // calc key position                      
    ipos = keyIter - keys.begin();
    
    // calc delta between greater and lesser key, then normalize
    keyDiff = 1.0 / (keys[ipos] - keys[ipos-1]);
    
    // get the quaternions at greater and lesser key
    q1 = _keyValues[ipos-1];
    q2 = _keyValues[ipos  ];
    
    // interpolate quaternion between and return it
    q3 = q1.slerp(q1, q2, (key - keys[ipos-1]) * keyDiff);
    
    return q3;
}

template <> inline
void Interpolator<Quaternion>::setTime(Real32 globalTime)
{
    if(_pTransform == NullFC)
        return;

    OSG::beginEditCP(_pTransform);
    {
        Quaternion q = tick(globalTime);

        _pTransform->setRotation(q);
    }
    OSG::endEditCP  (_pTransform);

    
}

template <> inline
void Interpolator<Vec3f>::setTime(Real32 globalTime)
{
    if(_pTransform == NullFC)
        return;

    OSG::beginEditCP(_pTransform);
    {
        Vec3f v = tick(globalTime);

        if(isScaleInterpol())
        {
            _pTransform->setScale(v);
        }
        else 
        {
            _pTransform->setTranslation(v);
        }
    }
    OSG::endEditCP  (_pTransform);
}

template <class KeyValueType>
inline void Interpolator<KeyValueType>::dump(void)
{
    Int32 i;

    std::cerr << "------------------------------------------" << std::endl
              << "Name: "   << getName()                      << std::endl
              << "Type: "   << type2String(getType())         << std::endl
              << "Dura: "   << getDuration()                  << std::endl
              << "Target: " << getTargetName()                << std::endl
              << "#Keys:"   << nrOfKeys()                     << " [ ";
         
    for(i = 0; i < nrOfKeys(); ++i)
    {
        std::cerr << getKeys()[i] << ", ";
    }

    std::cerr << " ]"     << std::endl;
    std::cerr << "#Vals:" << nrOfKeyValues() << " [ ";
     
    for(i = 0; i < nrOfKeyValues(); ++i)
    {
        std::cerr << _keyValues[i] << ", ";
    } 
   
    std::cerr << std::endl;
}

template <class KeyValueType>
KeyValueType Interpolator<KeyValueType>::tick(Real32 globalTime)
{
    Real32 key = time2key(globalTime);

    return getValue(key);
}






