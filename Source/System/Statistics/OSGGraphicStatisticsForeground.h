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

#include <OSGTextureChunk.h>
#include <OSGTextFace.h>
#include <OSGTextLayoutParam.h>

#include <OSGGraphicStatisticsForegroundBase.h>

OSG_BEGIN_NAMESPACE

class TextTXFFace;

/*! \brief Graphics Statistics Foreground class. See \ref
    PageSystemWindowForegroundStatisticsGraphic for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING GraphicStatisticsForeground : public GraphicStatisticsForegroundBase
{
  private:

    typedef GraphicStatisticsForegroundBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    enum Type {
      OSG_ANALOG     = 0,
      OSG_BAR        = 1,
      OSG_CHART      = 2,
      OSG_LINE_CHART = 3,
      OSG_TEXT       = 4
    };

    enum Mode {
      OSG_OVERFLOW_RESIZE  = 1,
      OSG_UNDERFLOW_RESIZE = 2,
      OSG_RECIPROC         = 4,
      OSG_SMOOTH           = 8,
      OSG_ENABLE_POINTS    = 16,
      OSG_MAX_TEXT         = 32,
      OSG_MIN_TEXT         = 64
    };

    enum TextHA {
      OSG_LEFT   = 0,
      OSG_RIGHT  = 1,
      OSG_CENTER = 2
    };

    enum TextVA {
      OSG_BOTTOM = 0,
      OSG_MIDDLE = 1,
      OSG_TOP    = 2
    };

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
                    UInt32            Flags = OSG_UNDERFLOW_RESIZE |
                                              OSG_OVERFLOW_RESIZE,
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
    void drawString(DrawActionBase    *base,
                    const std::string &text,
                    TextLayoutParam::Alignment majorAlignment
                    = TextLayoutParam::ALIGN_FIRST,
                    TextLayoutParam::Alignment minorAlignment
                    = TextLayoutParam::ALIGN_END);

    // converts a Real32 to a std::string
    std::string real2String(Real32 value, char* format = 0);


    void calcPosAndSize(const UInt32& elementID,
                        Viewport* port,
                        Vec2f* Position,
                        Vec2f* Size);

    //! Calculate the "real" value based on the value and the Flags
    inline void processValue( Real32& value, const UInt32& elementID );
    inline void processOnlyValue( Real32& value, const UInt32& elementID );
    inline void addValueToHistory( Real32& value, const UInt32& elementID );



    /*==========================  PRIVATE  ================================*/
  private:

    TextTXFFace*    _face;

    TextureChunkPtr _texchunk;


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
