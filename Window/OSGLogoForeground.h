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


#ifndef _OSGLOGOFOREGROUND_H_
#define _OSGLOGOFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGLogoForegroundBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING LogoForeground : public LogoForegroundBase
{
    /*==========================  PRIVATE  ================================*/  
 private:

    typedef LogoForegroundBase Inherited;

    /*==========================  PUBLIC  =================================*/ 
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
   
    static const char *getClassname(void) { return "LogoForeground"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     transformation                           */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     dump                                     */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access fields                             */
    /*! \{                                                                 */

    inline void addLogo(ImageP logo, Pnt2f position);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    draw                                      */
    /*! \{                                                                 */

    virtual void draw( DrawActionBase * action, Viewport * port );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LogoForeground(void);
    LogoForeground(const LogoForeground &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
 
    virtual ~LogoForeground(void); 
 
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  
 private:

    friend class FieldContainer;
    friend class LogoForegroundBase;

    static char cvsid[];

    static void initMethod( void );

    void operator =(const LogoForeground &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef LogoForeground *LogoForegroundP;

OSG_END_NAMESPACE

#include <OSGLogoForeground.inl>
#include <OSGLogoForegroundBase.inl>

#endif /* _OSGLOGOFOREGROUND_H_ */


