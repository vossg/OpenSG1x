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

#ifndef _OSGNFIOOPTIONS_H_
#define _OSGNFIOOPTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <string>

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/* \brief NFIOOptions class.
          parses the reader/writer options.
*/

class NFIOOptions
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    NFIOOptions                     (void);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~NFIOOptions            (void);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */
  
    void init(const std::string &options);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Options                                   */
    /*! \{                                                                 */
    
    bool inlineTextures(void) const;
    bool compressTextures(void) const;
    UInt32 texturesCompressionQuality(void) const;
    std::string texturesImageType(void) const;
    
    UInt8 quantizePositions(void) const;
    UInt8 quantizeNormals(void) const;
    UInt8 quantizeTexCoords(void) const;
    
    bool packIndices(void) const;
    bool unpack16BitIndices(void) const;

    bool exportVolumes(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*==========================  PRIVATE  ================================*/
private:
    
    Int32 getInteger(const std::string &str);
    std::string getString(const std::string &str);

    bool        _inlineTextures;
    bool        _compressTextures;
    UInt32      _texturesCompressionQuality;
    std::string _texturesImageType;

    UInt8       _quantizePositions;
    UInt8       _quantizeNormals;
    UInt8       _quantizeTexCoords;
    bool        _packIndices;
    bool        _unpack16BitIndices;
    bool        _exportVolumes;
};

OSG_END_NAMESPACE

#define OSGNFIOOPTIONS_HEADER_CVSID "@(#)$Id: OSGNFIOOptions.h,v 1.3 2005/09/30 12:52:24 a-m-z Exp $"

#endif /* _OSGNFIOOPTIONS_H_ */
