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

#ifndef _OSGFILESYSTEM_H_
#define _OSGFILESYSTEM_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __sgi
#include <sys/fs/efs_ino.h>
#endif

#ifndef WIN32
#include <dirent.h>
#include <unistd.h>
#include <vector>
#else
#include <windows.h>
#include <direct.h>
#include <vector>
#endif

OSG_BEGIN_NAMESPACE

/*! \ingroup 
 *  \brief Brief
 */

namespace AccessFlags
{
    const UInt32 None        = 0x00;
    const UInt32 IsReadable  = 0x01;
    const UInt32 IsWriteable = 0x02;
}


namespace File
{
    inline
    static Bool tstAttr(const Char8  *szFilename,
                              UInt32  uiAccessFlags);
}

namespace Directory
{
    inline
    static Bool             tstAttr   (const Char8  *szFilename,
                                             UInt32  uiAccessFlags);
    inline
    static Char8           *getCurrent(void);

    inline
    static Bool             setCurrent(const Char8 *szDirname);

    inline
    static vector<Char8 *> *getEntries(const Char8 *szDirname);
}

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGFileSystem.inl>

#endif /* _OSGFILESYSTEM_H_ */




