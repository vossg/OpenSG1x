/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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


#ifndef _OSGDFFUNCTORS_H_
#define _OSGDFFUNCTORS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGFieldType.h>

#include <OSGSField.h>
#include <OSGMField.h>

#include <OSGAction.h>
#include <OSGVolume.h>
#include <OSGTypedFunctors.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;

// The functor types used by the Core
typedef TypedFunctor1Base< Action::ResultE, PtrCallArg<DrawActionBase> >
                                                DrawFunctor;
                                               
typedef TypedVoidFunctor1Base< PtrCallArg<Volume> > VolumeFunctor;


template <>
struct FieldDataTraits<DrawFunctor> : 
    public FieldTraitsRecurseBase<DrawFunctor>
{
    static DataType       _type;

    enum                  { StringConvertable = 0 };

    static DataType       &getType      (void) { return _type;          }

    static Char8          *getSName     (void) { return "SFDrawFunctor"; }
    static Char8          *getMName     (void) { return "MFDrawFunctor"; }

    static DrawFunctor     getDefault   (void) { return DrawFunctor();   }

    static UInt32 getBinSize(const DrawFunctor &)
    {
        return 0;
    }

    static UInt32 getBinSize (const DrawFunctor *, UInt32 )
    {
        return 0;
    }

    static void copyToBin(      BinaryDataHandler &, 
                          const DrawFunctor       &)
    {
    	FFATAL(("Tried to convert DrawFunctor to binary!"));
    }

    static void copyToBin(      BinaryDataHandler &,
                          const DrawFunctor       *,
                                UInt32             )
    {
    	FFATAL(("Tried to convert multiple DrawFunctors to binary!"));
    }
    
    static void copyFromBin(BinaryDataHandler &, 
                            DrawFunctor       &)
    {
    	FFATAL(("Tried to convert DrawFunctor from binary!"));
    }
    
    static void copyFromBin(BinaryDataHandler &,
                            DrawFunctor       *,
                            UInt32             )
    {
    	FFATAL(("Tried to convert multiple DrawFunctors from binary!"));
    }
};

typedef SField<DrawFunctor> SFDrawFunctor;
typedef MField<DrawFunctor> MFDrawFunctor;

#ifndef OSG_COMPILEDFFUNCTORSINST

// Declare the functions/classes/methods Windows needs
OSG_DLLEXPORT_DECL1(SField, DrawFunctor, )
OSG_DLLEXPORT_DECL1(MField, DrawFunctor, )

#endif

template <>
struct FieldDataTraits<VolumeFunctor> : 
    public FieldTraitsRecurseBase<VolumeFunctor>
{
    static DataType       _type;

    enum                  { StringConvertable = 0 };

    static DataType       &getType      (void) { return _type;          }

    static Char8          *getSName     (void) { return "SFVolumeFunctor"; }
    static Char8          *getMName     (void) { return "MFVolumeFunctor"; }

    static VolumeFunctor     getDefault   (void) { return VolumeFunctor();   }

    static UInt32 getBinSize(const VolumeFunctor &)
    {
        return 0;
    }

    static UInt32 getBinSize (const VolumeFunctor *, UInt32 )
    {
        return 0;
    }

    static void copyToBin(      BinaryDataHandler &, 
                          const VolumeFunctor       &)
    {
    	FFATAL(("Tried to convert VolumeFunctor to binary!"));
    }

    static void copyToBin(      BinaryDataHandler &,
                          const VolumeFunctor       *,
                                UInt32             )
    {
    	FFATAL(("Tried to convert multiple VolumeFunctors to binary!"));
    }
    
    static void copyFromBin(BinaryDataHandler &, 
                            VolumeFunctor       &)
    {
    	FFATAL(("Tried to convert VolumeFunctor from binary!"));
    }
    
    static void copyFromBin(BinaryDataHandler &,
                            VolumeFunctor       *,
                            UInt32             )
    {
    	FFATAL(("Tried to convert multiple VolumeFunctors from binary!"));
    }
};

typedef SField<VolumeFunctor> SFVolumeFunctor;
typedef MField<VolumeFunctor> MFVolumeFunctor;

#ifndef OSG_COMPILEDFFUNCTORSINST

// Declare the functions/classes/methods Windows needs
OSG_DLLEXPORT_DECL1(SField, VolumeFunctor, )
OSG_DLLEXPORT_DECL1(MField, VolumeFunctor, )

#endif

OSG_END_NAMESPACE

#define OSGDFFUNCTORS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDFFUNCTORS_H_ */
