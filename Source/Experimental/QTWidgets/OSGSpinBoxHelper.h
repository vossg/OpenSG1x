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

#ifndef _OSGSPINBOXHELPER_H_
#define _OSGSPINBOXHELPER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

#include "OSGSpinBoxHelperTraits.h"

OSG_BEGIN_NAMESPACE

template <class ValueTypeT>
class SpinBoxHelper :
    public SpinBoxHelperTraits<ValueTypeT>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef ValueTypeT                      ValueType;
    typedef SpinBoxHelperTraits<ValueType>  Traits;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    SpinBoxHelper(void                                                 );
    // The .net 7.0 compiler doesn't compile this with the default parameters :-(
    SpinBoxHelper(ValueType initialValue,
                  ValueType lowerBound   /*= Traits::_initLowerBound*/,
                  ValueType upperBound   /*= Traits::_initUpperBound*/,
                  ValueType stepSize     /*= Traits::_defaultStepSize*/,
                  ValueType pageStepSize /*= Traits::_defaultPageStepSize*/);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Value Modification                                        */
    /*! \{                                                                 */

    void             stepUp                (void                       );
    void             stepDown              (void                       );

    void             stepPageUp            (void                       );
    void             stepPageDown          (void                       );

    ValueType        getValue              (void                       ) const;
    void             setValue              (ValueType          value   );

    std::string      getValueByStr         (void                       ) const;
    void             setValueByStr         (const std::string &strValue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Customization                                             */
    /*! \{                                                                 */

    bool             getWrapAround         (void                  ) const;
    void             setWrapAround         (bool      bWrapAround );

    ValueType        getLowerBound         (void                  ) const;
    void             setLowerBound         (ValueType lowerBound  );

    ValueType        getUpperBound         (void                  ) const;
    void             setUpperBound         (ValueType upperBound  );

    ValueType        getStepSize           (void                  ) const;
    void             setStepSize           (ValueType stepSize    );

    ValueType        getPageStepSize       (void                  ) const;
    void             setPageStepSize       (ValueType pageStepSize);

    static ValueType getDefaultStepSize    (void                  );
    static void      setDefaultStepSize    (ValueType stepSize    );

    static ValueType getDefaultPageStepSize(void                  );
    static void      setDefaultPageStepSize(ValueType pageStepSize);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name    Helper Methods                                            */
    /*! \{                                                                 */

    void stepUp  (ValueType stepSize);
    void stepDown(ValueType stepSize);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    bool      _bWrapAround;

    ValueType _value;

    ValueType _lowerBound;
    ValueType _upperBound;

    ValueType _stepSize;
    ValueType _pageStepSize;
};

OSG_END_NAMESPACE

#include "OSGSpinBoxHelper.inl"

#define OSGSPINBOXHELPER_HEADER_CVSID "@(#)$Id: OSGSpinBoxHelper.h,v 1.2 2004/11/26 13:55:30 a-m-z Exp $"

#endif /* _OSGSPINBOXHELPER_H_ */
