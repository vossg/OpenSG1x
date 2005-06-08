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

#ifndef _OSGPLYSCENEFILETYPE_H_
#define _OSGPLYSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <OSGBaseTypes.h>
#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBLIB_DLLMAPPING PLYSceneFileType : public SceneFileType
{
public:
    static PLYSceneFileType& the()
    {
        return _the;
    }

    virtual const Char8* getName() const;

    virtual NodePtr read(std::istream& is,
                         const Char8* fileNameOrExtension) const;

private:
    PLYSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           bool    override,
                           UInt32  overridePriority,
                           UInt32  flags);

    PLYSceneFileType(const PLYSceneFileType &obj);

    static PLYSceneFileType _the;


    /* prohibit default function (move to 'public' if needed) */
    void operator=(const PLYSceneFileType& source);
};

typedef PLYSceneFileType* PLYSceneFileTypeP;

OSG_END_NAMESPACE

#define OSGPLYSCENEFILETYPE_HEADER_CVSID "@(#)$Id: OSGPLYSceneFileType.h,v 1.1 2005/06/08 19:12:03 dirk Exp $"

#endif // _OSGPLYSCENEFILETYPE_H_

