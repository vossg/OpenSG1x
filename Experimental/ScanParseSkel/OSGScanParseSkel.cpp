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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGScanParseSkel.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char ScanParseSkel::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

extern int  OSGScanParseSkel_char;
extern void resetScanner(void);

void ScanParseSkel::reset(void)
{
    OSGScanParseSkel_char = -2;
    resetScanner();
}

void ScanParseSkel::setMapTypeIds(Bool bVal)
{
    _bMapTypeIds = bVal;
}

void ScanParseSkel::setReferenceHeader(const Char8 *szReferenceHeader)
{
    stringDup(szReferenceHeader, _szReferenceHeader);
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

ScanParseSkel::ScanParseSkel(void) :
    _bMapTypeIds(false),
    _szReferenceHeader(NULL)
{
}

/** \brief Destructor
 */

ScanParseSkel::~ScanParseSkel(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

extern int   OSGScanParseSkel_parse(void);
extern FILE *OSGScanParseSkel_in;

extern void setSkel(ScanParseSkel *pSkel);
extern void clearSkel(void);
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

        fprintf(stderr, "Loading : %s\n", szFilename);

        OSGScanParseSkel_in = pInFile;

        _uiOptions = uiOptions;

        OSGScanParseSkel_parse();

        reset();

        fclose(pInFile);

        clearSkel();
    }
}

/*-------------------------- your_category---------------------------------*/

Bool ScanParseSkel::verifyHeader(const Char8 *szHeader)
{
    Bool returnValue = true;

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

void ScanParseSkel::beginProtoInterface(const Char8 *)
{
}

void ScanParseSkel::endProtoInterface(void)
{
}

void ScanParseSkel::addProtoEventIn (const Char8 *,
                                        const Char8 *)
{
}

void ScanParseSkel::addProtoEventOut(const Char8 *,
                                        const Char8 *)
{
}

void ScanParseSkel::beginProtoField(const Char8  *,
                                       const UInt32  ,
                                       const Char8  *)
{
}

void ScanParseSkel::endProtoField(void)
{
}

void ScanParseSkel::beginProtoExposedField(const Char8  *,
                                              const UInt32  ,
                                              const Char8  *)
{
}

void ScanParseSkel::endProtoExposedField(void)
{
}


void ScanParseSkel::beginField(const Char8 *,
                               const UInt32)
{
}

void ScanParseSkel::endField(void)
{
}

void ScanParseSkel::beginNode(const Char8 *,
                              const Char8 *)
{
}
    
void ScanParseSkel::endNode(void)
{
}

void ScanParseSkel::use(const Char8 *szName)
{
    fprintf(stderr, "Use : %s\n", szName);
}

void ScanParseSkel::addFieldValue(const Char8 *)
{
}

void ScanParseSkel::addRoute(const Char8 *,
                                const Char8 *,
                                const Char8 *,
                                const Char8 *)
{
}

/*-------------------------- assignment -----------------------------------*/

Bool ScanParseSkel::getMapFieldTypes(void)
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

/*-------------------------- comparison -----------------------------------*/




//---------------------------------------------------------------------------
//  FUNCTION: 
//---------------------------------------------------------------------------
//:  Example for the head comment of a function
//---------------------------------------------------------------------------
//
//p: Paramaters: 
//p: 
//
//g: GlobalVars:
//g: 
//
//r: Return:
//r: 
//
//c: Caution:
//c: 
//
//a: Assumptions:
//a: 
//
//d: Description:
//d: 
//
//s: SeeAlso:
//s: 
//---------------------------------------------------------------------------

