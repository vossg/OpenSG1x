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

#ifndef _OSGGRAPHICSTATISTICSFOREGROUND_H_
#define _OSGGRAPHICSTATISTICSFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGText.h>
#include <OSGTextureChunk.h>

#include <OSGGraphicStatisticsForegroundBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief Graphics Statistics Foreground class. See \ref 
    PageSystemWindowForegroundStatisticsGraphics for a description.
*/

// The different types of the displayed Statistic
#define STATISTICS_ANALOG 0
#define STATISTICS_BAR   1
#define STATISTICS_CHART 2
#define STATISTICS_LINE_CHART 3
#define STATISTICS_TEXT 4

// Flags for Statistics
#define STATISTICS_OVERFLOW_RESIZE 0x1
#define STATISTICS_UNDERFLOW_RESIZE 0x2
#define STATISTICS_RECIPROC 0x4
#define STATISTICS_SMOOTH 0x8 
#define STATISTICS_ENABLE_POINTS 0x10
#define STATISTICS_MAX_TEXT 0x20
#define STATISTICS_MIN_TEXT 0x40

// Alignments for the text:
#define STATISTICS_LEFT   0
#define STATISTICS_RIGHT  1
#define STATISTICS_CENTER 2

#define STATISTICS_BOTTOM 0
#define STATISTICS_MIDDLE 1
#define STATISTICS_TOP    2

class OSG_SYSTEMLIB_DLLMAPPING GraphicStatisticsForeground : public GraphicStatisticsForegroundBase
{
  private:

    typedef GraphicStatisticsForegroundBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, UInt32 from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                            const BitVector  bvFlags  = 0) const;

    
    void draw(DrawActionBase *, Viewport *);
    
    
    //! Add an Element to be shown
    void addElement(StatElemDescBase &desc,
                    UInt32            displayType, 
                    Vec2f             pos, 
                    Vec2f             size, 
                    Color4f           highColor, 
                    Color4f           lowColor,
                    Color4f           currentColor,
                    Real32            minValue     = 0.0,
                    Real32            maxValue     = 0.0,
                    UInt32            Flags = STATISTICS_UNDERFLOW_RESIZE | 
                                              STATISTICS_OVERFLOW_RESIZE,
                    UInt32            historySize = 0,
                    std::string       description=""                      );
    
    void removeElement(StatElemDescBase &desc);



    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GraphicStatisticsForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GraphicStatisticsForeground(void);
    GraphicStatisticsForeground(const GraphicStatisticsForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GraphicStatisticsForeground(void); 

    /*! \}                                                                 */
    
    //! Draw an analog Display
    void drawAnalog(UInt32,   StatElem*, DrawActionBase *, Viewport *);
    //! Draw a chart of the StatElem
    void drawChart(UInt32,   StatElem*, DrawActionBase *, Viewport *);
    //! Draw a line-chart of the StatElem
    void drawLineChart(UInt32,   StatElem*, DrawActionBase *, Viewport*);
    //! Draw a Bar of the StatElem
    void drawBar(UInt32,   StatElem*, DrawActionBase *, Viewport *);
    //! Draw just Text to represent the Statistics Data
    void drawText(UInt32,   StatElem*, DrawActionBase *, Viewport *);



    //! initializes the text
    void initText( void );
    
    //! Draws a string
    void drawString(           DrawActionBase *base, 
                    const std::string         &text,
                               UInt32          align  = STATISTICS_LEFT,
                               UInt32          valign = STATISTICS_BOTTOM);
    
    // converts a Real32 to a std::string
    std::string real2String(Real32 value, char* format = 0);

    
    void calcPosAndSize(const UInt32& ID, 
                        Viewport* port, 
                        Vec2f* Position, 
                        Vec2f* Size);

    //! Calculate the "real" value based on the value and the Flags
    inline void processValue( Real32& value, const UInt32& ID );
    inline void processOnlyValue( Real32& value, const UInt32& ID );
    inline void addValueToHistory( Real32& value, const UInt32& ID );



    /*==========================  PRIVATE  ================================*/
  private:

    static ImageP          _textimage;


    static Text            _text;

    static TextureChunkPtr _texchunk;


    friend class FieldContainer;
    friend class GraphicStatisticsForegroundBase;

    static void initMethod(void);

    std::vector< std::vector< Real32> > _history;
    
    std::vector< UInt32 >               _historyID;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GraphicStatisticsForeground &source);
};

typedef GraphicStatisticsForeground *GraphicStatisticsForegroundP;

OSG_END_NAMESPACE

#include <OSGGraphicStatisticsForegroundBase.inl>
#include <OSGGraphicStatisticsForeground.inl>

#define OSGGRAPHICSTATISTICSFOREGROUND_HEADER_CVSID "@(#)$Id: OSGGraphicStatisticsForeground.h,v 1.1 2002/07/18 16:09:33 jbehr Exp $"

#endif /* _OSGGRAPHICSTATISTICSFOREGROUND_H_ */
