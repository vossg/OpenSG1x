/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline void GraphicStatisticsForeground::processValue(Real32& value, const UInt32& ID)
{
    processOnlyValue(value, ID);
    addValueToHistory(value, ID);
  
}

inline void GraphicStatisticsForeground::processOnlyValue(Real32&  value, 
                                                          const UInt32& ID)
{
    UInt32 flags =  getFlags()[ID];
    Real32 minV  =  getMinValue()[ID];
    Real32 maxV  =  getMaxValue() [ID];
  
    /* check for invert */
    if (flags & STATISTICS_INVERT)
        {
            value  =  1.0 / value; 
        }
  
    /* check for a to big Value */
    if(value > maxV)
        {
            if (flags & STATISTICS_OVERFLOW_RESIZE)
                {
                    getMaxValue()[ID]  =  value;
                }
            else
                {
                    value  =  maxV;
                }
        }
    /* check for to small values */
    if( value < minV )
        { 
            if (flags & STATISTICS_UNDERFLOW_RESIZE)
                {
                    getMinValue()[ID]  =  value;
                }
            else
                {
                    value  =  minV;
                }
        }
    /* end of these checks */
  
}

inline void GraphicStatisticsForeground::addValueToHistory(Real32&  value, 
                                                           const UInt32& ID)
{
    UInt32 flags =  getFlags()[ID];
  
    /* Smooth the value, if asked for */
    UInt32 hSize = _history.size();
    UInt32 size = (ID < hSize) ? _history[ID].size() : 0;
    
    if(size > 0)
        {
            UInt32 queueEnd = _historyID[ID];
            _history[ID][queueEnd]  =  value;
            /* increment the queue end */
            _historyID[ID]  =  (_historyID[ID] + 1) % size;
      
            /* check whether the value should be smoothed */
            if ( (flags & STATISTICS_SMOOTH) ||
                 (flags & STATISTICS_OVERFLOW_RESIZE) ||
                 (flags & STATISTICS_UNDERFLOW_RESIZE) ) 
              {
                Real32 v, max, min, sum = 0.0;

                for(UInt32 i = 0; i < size; i++)
                {
                  v = _history[ID][i];
                  
                  if (i) 
                  {
                    if (v > max)
                      max = v;
                    else
                      if (v < min)
                        min = v;
                  }
                  else
                    min = max = v;

                  sum += v;
                }
                if (flags & STATISTICS_SMOOTH)
                {
                  value = sum / size;
                  //_history[ID][queueEnd] = value;
                }

                if ( (flags & STATISTICS_OVERFLOW_RESIZE) &&
                     (max < getMaxValue()[ID]) ) 
                {
                  max += (getMaxValue()[ID] - max) / 2.0;
                  getMaxValue()[ID] = osgMax(v,max);
                }
                
                if ( (flags & STATISTICS_UNDERFLOW_RESIZE) &&
                     (min > getMinValue()[ID]) ) 
                {
                  min -= (min - getMinValue()[ID]) / 2.0;
                  getMinValue()[ID] = osgMin(v,min);
                }

              }
        }
  
}
OSG_END_NAMESPACE

#define OSGGRAPHICSTATISTICSFOREGROUND_INLINE_CVSID "@(#)$Id: OSGGraphicStatisticsForeground.inl,v 1.2 2002/07/30 16:30:32 jbehr Exp $"

