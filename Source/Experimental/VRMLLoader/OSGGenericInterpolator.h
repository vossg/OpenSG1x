/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSGINTERPOLATOR_H_
#define _OSGINTERPOLATOR_H_

#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <string>

#include <OSGNode.h>
#include <OSGQuaternion.h>
#include <OSGComponentTransform.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING InterpolatorBase
{
  public:
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    enum InterpolType { Unused, Orientation, Position, Other };

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------
    
    static const std::string type2String(InterpolType t);
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    InterpolatorBase(InterpolType t);
    virtual ~InterpolatorBase(void);
    
    /*------------------------- your_category -------------------------------*/

    InterpolType         getType         (void                       ) const;
    
    void                 setTargetName   (const std::string &name    );
    const std::string   &getTargetName   (void                       );

    void                 setName         (const std::string& name    );
    std::string         &getName         (void                       );
    
    void                 addKey          (Real32 key                 ); 
    
    Int32                nrOfKeys        (void                       ) const;
    virtual Int32        nrOfKeyValues   (void                       ) const=0;

    Real32               time2key        (Real32 time                ); 
    std::vector<Real32> &getKeys         (void                       );  
    
    void                 setDuration     (const Real32 duration      );
    Real32               getDuration     (void                       ) const;
        
    void                 setLoop         (bool loopon                );
    bool                 isLooping       (void                       ) const;
    
    void                 setScaleInterpol(bool scale                 );
    bool                 isScaleInterpol (                           ) const;

    virtual void         setTime         (Real32 globalTime          ) = 0;
        
    virtual void         dump            (void                       ) = 0;
    
    /*------------------------- your_operators ------------------------------*/

    void setTargetTransform(ComponentTransformPtr pTransform);
    
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    InterpolType     _type;
    ComponentTransformPtr _pTransform;

    std::string         _targetName;
    std::string         _name;
    std::vector<Real32> _keys;
    Real32              _duration;
    Real32              _keyDelta;
    bool                _loop;
    bool                _isScale;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

};

template <class KeyValueType>
class Interpolator : public InterpolatorBase
{
  public:
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef InterpolatorBase Inherited;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------
    
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Interpolator(InterpolType t);
    virtual ~Interpolator(void);
    
    /*------------------------- your_category -------------------------------*/

    void         addKeyValue    (const KeyValueType& value            );
    void         addKeyValuePair(Real32 key, const KeyValueType& value);
    Int32        nrOfKeyValues  (void                                 ) const;

    KeyValueType getValue       (Real32 key                           );
    KeyValueType tick           (Real32 globalTime                    );

    virtual void setTime        (Real32 globalTime                    );

    virtual void dump           (void                                 );     
        
    /*------------------------- your_operators ------------------------------*/
    
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    std::vector<KeyValueType> _keyValues;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

};

typedef Interpolator<Vec3f> PositionInterpolator;
typedef PositionInterpolator* PositionInterpolatorPtr;

typedef Interpolator<Quaternion> OrientationInterpolator;
typedef OrientationInterpolator* OrientationInterpolatorPtr;
//extern OSG_BASE_DLLMAPPING PositionInterpolator;
//typedef Interpolator<

#include "OSGGenericInterpolator.inl"

OSG_END_NAMESPACE

#endif //_OSGINTERPOLATOR_H_
