/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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


#ifndef _OSG_GRADIENTBACKGROUND_H_
#define _OSG_GRADIENTBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGMFBaseTypes.h> //? kennt MFGradient3f nicht 
#include <OSGMFSysTypes.h> //? kennt MFReal32 nicht
#include <OSGFieldContainer.h>
#include "OSGWindowBase.h"
#include <OSGBackground.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class DrawAction;
class Viewport;

class GradientBackground;
typedef FCPtr<BackgroundPtr, GradientBackground> GradientBackgroundPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief gradient background class
 */

class OSG_WINDOW_DLLMAPPING GradientBackground : public Background
{
  private:

    typedef FieldContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(ColorField)
    OSG_FC_FIELD_IDM_DECL      (PositionField, ColorField)
    OSG_FC_LAST_FIELD_IDM_DECL (PositionField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "GradientBackground"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(GradientBackgroundPtr)

    /*------------------------- your_category -------------------------------*/

	void clear( DrawAction * action, Viewport * port );

	void addColor(Color3f color, Real32 position);

	MFColor3f *getMFColor();

	MFReal32 *getMFPosition();

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const GradientBackground &other) const;
    
	//Bool operator == (const Background &other) const;
	//Bool operator != (const Background &other) const;

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

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

	  //** The clear colors of the window */
	  MFColor3f _color;

	  //** The color coordinates */
	  MFReal32 _position;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    GradientBackground(void);
    virtual ~GradientBackground(void); 

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

    friend class FieldContainer;
    friend class FieldContainerType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static FieldContainerType _type;
	static FieldDescription   _desc[];


    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	void addColor(Color3f col);

	void addPosition(Real32 pos);

	void setMFColor(MFColor3f col);

	void setMFPosition(MFReal32 pos);

//	Color3f getColor();

//	Real32 getPosition();

	// prohibit default functions (move to 'public' if you need one)

    GradientBackground(const GradientBackground &source);
    GradientBackground & operator =(const GradientBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

/** \brief class pointer
 */
typedef GradientBackground *GradientBackgroundP;

/** \brief BackgroundPtr
 */
////typedef FCPtr<FieldContainerPtr, SolidBackground> SolidBackgroundPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief BackgroundPtr field traits 
 */


template <>
struct FieldDataTraits<GradientBackgroundPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFGradientBackgroundPtr"; }
    static Char8 *getMName(void) { return "MFGradientBackgroundPtr"; }
};


/** \brief SFSolidBackgroundPtr
 */
/*
typedef SField<GradientBackgroundPtr>       SFGradientBackgroundPtr;

#ifndef OSG_COMPILEBACKGROUNDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GradientBackgroundPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GradientBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif
*/

/** \brief MFGradientBackgroundPtr
 */

typedef MField<GradientBackgroundPtr>       MFGradientBackgroundPtr;

#ifndef OSG_COMPILEBACKGROUNDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<GradientBackgroundPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, GradientBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif


OSG_END_NAMESPACE

#include "OSGGradientBackground.inl"

#endif /* _OSGGRADIENTBACKGROUND_H_ */


