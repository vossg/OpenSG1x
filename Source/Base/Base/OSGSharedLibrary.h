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

#ifndef _OSGSHAREDLIBRARY_H_
#define _OSGSHAREDLIBRARY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#ifndef OSG_DISABLE_DEPRECATED

#include <OSGBase.h>
#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

#ifdef WIN32
typedef HMODULE  SharedHandle;
#else
typedef void    *SharedHandle;
#endif

typedef void *AnonSymbolHandle;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBase
 */

class OSG_BASE_DLLMAPPING SharedLibrary 
{
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Type                                      */
    /*! \{                                                                 */

    enum SharedLibraryType
    {
        Invalid       = 0x0000,
        Application   = 0x0001,
        SharedLib     = 0x0002
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SharedLibrary(void);
    SharedLibrary(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SharedLibrary(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */

          bool              open     (const Char8 *szName      );
          bool              close    (      void               );

          AnonSymbolHandle  getSymbol(const Char8 *szSymbolName);

          bool              isOpen   (      void               );

    const Char8            *getName  (      void               );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static Char8 _szApplicationName[];

           Char8            *_szName;
           SharedHandle      _pHandle;

           SharedLibraryType _type;    

    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool open(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    SharedLibrary(const SharedLibrary &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SharedLibrary &source);
};

OSG_END_NAMESPACE

#define OSGSHAREDLIBRARY_HEADER_CVSID "@(#)$Id: $"

#endif

#endif /* _OSGSHAREDLIBRARY_H_ */
