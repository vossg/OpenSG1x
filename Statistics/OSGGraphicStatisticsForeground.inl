/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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
    UInt32 size = _history[ID].size();
  
    if(size > 0)
        {
            UInt32 queueEnd = _historyID[ID];
            _history[ID][queueEnd]  =  value;
            /* increment the queue end */
            _historyID[ID]  =  (_historyID[ID] + 1) % size;
      
            /* check whether the value should be smoothed */
            if(flags & STATISTICS_SMOOTH)
                {
                    Real32 sum = 0.0;
                    for(UInt32 i = 0; i<size; i++)
                        {
                            sum += _history[ID][i];
                        }
                    value = sum / size;
                }
        }
  
}
OSG_END_NAMESPACE

#define OSGGRAPHICSTATISTICSFOREGROUND_INLINE_CVSID "@(#)$Id: OSGGraphicStatisticsForeground.inl,v 1.1 2002/07/18 16:09:33 jbehr Exp $"

