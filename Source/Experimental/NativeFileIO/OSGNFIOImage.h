/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#ifndef _OSGNFIOIMAGE_H_
#define _OSGNFIOIMAGE_H_
#ifdef __sgi
#pragma once
#endif

#include <set>
#include <string>

#include "OSGNFIOBase.h"
#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

/* \brief NFIOImage class.
          reads and writes a image.
*/

class NFIOImage : public NFIOBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    NFIOImage                     (void);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~NFIOImage            (void);
  
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Read/Write                                */
    /*! \{                                                                 */

    virtual FieldContainerPtr   readFC  (const std::string &typeName);
    virtual void                writeFC (const FieldContainerPtr &fc);

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/
private:

    void readCompressedPixel(ImagePtr &img);
    void writeCompressedPixel(const ImagePtr &img);
    bool isImageTypeSupported(const std::string &imageType);

    bool                    _imageTypeInitialized;
    std::set<std::string>   _imageTypes;

    static NFIOImage        _the;

};

OSG_END_NAMESPACE

#define OSGNFIOIMAGE_HEADER_CVSID "@(#)$Id: OSGNFIOImage.h,v 1.2 2005/02/17 14:30:42 a-m-z Exp $"

#endif /* _OSGNFIOIMAGE_H_ */
