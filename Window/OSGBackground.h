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


#ifndef _OSG_BACKGROUND_H_
#define _OSG_BACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGFieldContainer.h>
#include "OSGWindowBase.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class DrawAction;
class Viewport;

class Background;
typedef FCPtr<FieldContainerPtr, Background> BackgroundPtr;

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

class OSG_WINDOW_DLLMAPPING Background : public FieldContainer
{
  private:

    typedef FieldContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Background"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(BackgroundPtr)

    /*------------------------- your_category -------------------------------*/

	virtual void clear( DrawAction * action, Viewport * port );

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const Background &other) const;
    
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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Background(void);
    virtual ~Background(void); 

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

    Background(const Background &source);
    Background & operator =(const Background &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

/** \brief class pointer
 */
typedef Background *BackgroundP;

/** \brief BackgroundPtr
 */
typedef FCPtr<FieldContainerPtr, Background> BackgroundPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief BackgroundPtr field traits 
 */
template <>
struct FieldDataTraits<BackgroundPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFBackgroundPtr"; }
    static Char8 *getMName(void) { return "MFBackgroundPtr"; }
};

/** \brief SFBackgroundPtr
 */
typedef SField<BackgroundPtr>       SFBackgroundPtr;

#ifndef OSG_COMPILEBACKGROUNDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<BackgroundPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, BackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFBackgroundPtr
 */
typedef MField<BackgroundPtr>       MFBackgroundPtr;

#ifndef OSG_COMPILEBACKGROUNDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<BackgroundPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, BackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include "OSGBackground.inl"

#endif /* _OSGBACKGROUND_H_ */


