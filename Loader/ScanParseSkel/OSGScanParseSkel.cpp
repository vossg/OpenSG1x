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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGScanParseSkel.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

extern int  OSGScanParseSkel_char;
extern void resetScanner(void);

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ScanParseSkel::ScanParseSkel(void) :
    _uiCurrOptions    (0),
    _uiDefOptions     (0),
    _bMapTypeIds      (false),
    _szReferenceHeader(NULL )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ScanParseSkel::~ScanParseSkel(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Scan                                     */

extern int   OSGScanParseSkel_parse(void);
extern FILE *OSGScanParseSkel_in;

extern void setSkel    (ScanParseSkel *pSkel);
extern void clearSkel  (void);
extern void abortParser(void);

void ScanParseSkel::scanFile(const Char8 *szFilename, 
                                   UInt32 uiOptions)
{
    if(szFilename == NULL)
        return;

    FILE *pInFile = fopen(szFilename, "r");

    if(pInFile != NULL)
    {
        setSkel(this);

        PNOTICE << "Loading : " << szFilename << endl;

        OSGScanParseSkel_in = pInFile;

        _uiCurrOptions = uiOptions;

        OSGScanParseSkel_parse();

        reset();

        fclose(pInFile);

        clearSkel();
    }
}

void ScanParseSkel::scanFile(const Char8  *szFilename, 
                                   UInt32  uiAddOptions, 
                                   UInt32  uiSubOptions)
{
    UInt32 uiOptions = _uiDefOptions;

    uiOptions |=  uiAddOptions;
    uiOptions &= ~uiSubOptions;

    ScanParseSkel::scanFile(szFilename, uiOptions);
}

void ScanParseSkel::setDefaultOptions(UInt32 uiOptions)
{
    _uiDefOptions = uiOptions;
}

/*-------------------------------------------------------------------------*/
/*                             Prototypes                                  */

bool ScanParseSkel::verifyHeader(const Char8 *szHeader)
{
    bool returnValue = true;

    if(szHeader == NULL)
    {
        SLOG << "Error Null Header String Read" << endl;
        return false;
    }
    
    if(_szReferenceHeader != NULL)
    {
        if(strncmp(szHeader, 
                   _szReferenceHeader, 
                   stringlen(_szReferenceHeader)) != 0)
        {
            SLOG << "Error : Header [" << szHeader << "] does not "
                    << "match reference [" << _szReferenceHeader << "]" 
                    << endl;
            
            returnValue = false;
        }
    }
    else
    {
        SLOG << "Error Null Reference Header, Check disabled " << endl;
        return true;
    }

    return returnValue;
}

void ScanParseSkel::beginProto(const Char8 *)
{
}

void ScanParseSkel::endProto(void)
{
}

void ScanParseSkel::beginScript(const Char8 *)
{
}

void ScanParseSkel::endScript(void)
{
}

void ScanParseSkel::addEventInDecl (const Char8 *,
                                    const Char8 *)
{
}

void ScanParseSkel::addEventOutDecl(const Char8 *,
                                    const Char8 *)
{
}

void ScanParseSkel::beginFieldDecl(const Char8  *,
                                   const UInt32  ,
                                   const Char8  *)
{
}

void ScanParseSkel::endFieldDecl(void)
{
}

void ScanParseSkel::beginExposedFieldDecl(const Char8  *,
                                          const UInt32  ,
                                          const Char8  *)
{
}

void ScanParseSkel::endExposedFieldDecl(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Fields                                    */

void ScanParseSkel::beginField(const Char8 *,
                               const UInt32)
{
}

void ScanParseSkel::endField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Nodes                                     */

void ScanParseSkel::beginNode(const Char8 *,
                              const Char8 *)
{
}
    
void ScanParseSkel::endNode(void)
{
}

void ScanParseSkel::use(const Char8 *szName)
{
    PINFO << "Use : " << szName << endl;
}

void ScanParseSkel::is(const Char8 *)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void ScanParseSkel::addFieldValue(const Char8 *)
{
}

void ScanParseSkel::addRoute(const Char8 *,
                             const Char8 *,
                             const Char8 *,
                             const Char8 *)
{
}

/*-------------------------------------------------------------------------*/
/*                           Type Information                              */

bool ScanParseSkel::getMapFieldTypes(void)
{
    return _bMapTypeIds;
}

Int32 ScanParseSkel::mapExtIntFieldType(const Char8*, const Int32)
{
    return 0;
}

UInt32 ScanParseSkel::getFieldType(const Char8 *)
{
    return 0;
}

/*-------------------------------------------------------------------------*/
/*                               Set                                       */

void ScanParseSkel::reset(void)
{
    OSGScanParseSkel_char = -2;
    resetScanner();
}

void ScanParseSkel::setMapTypeIds(bool bVal)
{
    _bMapTypeIds = bVal;
}

void ScanParseSkel::setReferenceHeader(const Char8 *szReferenceHeader)
{
    stringDup(szReferenceHeader, _szReferenceHeader);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSCANPARSESKEL_HEADER_CVSID;
}
