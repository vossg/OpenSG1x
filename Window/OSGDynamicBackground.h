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


#ifndef _OSGDYNAMICBACKGROUND_H_
#define _OSGDYNAMICBACKGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGDynamicBackgroundBase.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;
class Viewport;

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DynamicBackground : public DynamicBackgroundBase
{
 
    /*==========================  PUBLIC  =================================*/
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "DynamicBackground"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */

    void clear( DrawActionBase * action, Viewport * port );

    void addColor(Color3f color, Real32 position);

 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    transformation                            */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);
 
     /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     dump                                     */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:
                                                                  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DynamicBackground(void);
    DynamicBackground(const DynamicBackground &source);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
 
    virtual ~DynamicBackground(void); 
   
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  
 private:

    typedef DynamicBackgroundBase Inherited;

    friend class FieldContainer;
    friend class DynamicBackgroundBase;

    static char cvsid[];

    static void initMethod( void );

    void operator =(const DynamicBackground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef DynamicBackground *DynamicBackgroundP;

OSG_END_NAMESPACE

#include <OSGDynamicBackground.inl>
#include <OSGDynamicBackgroundBase.inl>

#endif /* _OSGDYNAMICBACKGROUND_H_ */
