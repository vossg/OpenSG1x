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


#ifndef _OSG_SOLIDBACKGROUND_H_
#define _OSG_SOLIDBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGFieldContainer.h>
#include "OSGWindowBase.h"
#include "OSGBackground.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class DrawAction;
class Viewport;

class SolidBackground;
typedef FCPtr<BackgroundPtr, SolidBackground> SolidBackgroundPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_WINDOW_DLLMAPPING SolidBackground : public Background
{
  private:

    typedef FieldContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(ColorField)
    OSG_FC_LAST_FIELD_IDM_DECL (ColorField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "SolidBackground"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(SolidBackgroundPtr) //????

    /*------------------------- your_category -------------------------------*/

	void clear( DrawAction * action, Viewport * port );

	void setColor( Color3f col );

	Color3f getColor();

	SFColor3f *getSFColor();

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const SolidBackground &other) const;
    
	//Bool operator == (const Background &other) const;
	//Bool operator != (const Background &other) const;

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;

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

	  //** The clear color of the window */
	  SFColor3f _color;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    SolidBackground(void);
    virtual ~SolidBackground(void); 

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

	// prohibit default functions (move to 'public' if you need one)

    SolidBackground(const SolidBackground &source);
    SolidBackground & operator =(const SolidBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

/** \brief class pointer
 */
typedef SolidBackground *SolidBackgroundP;

/** \brief BackgroundPtr
 */
typedef FCPtr<BackgroundPtr, SolidBackground> SolidBackgroundPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief BackgroundPtr field traits 
 */


template <>
struct FieldDataTraits<SolidBackgroundPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFSolidBackgroundPtr"; }
    static Char8 *getMName(void) { return "MFSolidBackgroundPtr"; }
};


/** \brief SFSolidBackgroundPtr
 */

typedef SField<SolidBackgroundPtr>       SFSolidBackgroundPtr;

#ifndef OSG_COMPILEBACKGROUNDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<SolidBackgroundPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, SolidBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFBackgroundPtr
 */
/*
typedef MField<BackgroundPtr>       MFBackgroundPtr;

#ifndef OSG_COMPILEBACKGROUNDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<BackgroundPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, BackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif
*/

OSG_END_NAMESPACE

#include "OSGSolidBackground.inl"

#endif /* _OSGSolidBACKGROUND_H_ */


