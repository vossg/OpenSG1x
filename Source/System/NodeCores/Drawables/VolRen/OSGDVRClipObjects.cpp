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

#include <OSGConfig.h>

#include <OSGDVRClipGeometry.h>
#include <OSGDVRClipObjects.h>

OSG_USING_NAMESPACE

/*! \class osg::DVRClipObjects

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
DVRClipObjects::DVRClipObjects(void) :
    Inherited()
{
}

//! Copy Constructor
DVRClipObjects::DVRClipObjects(const DVRClipObjects &source) :
    Inherited(source)
{
}

//! Destructor
DVRClipObjects::~DVRClipObjects(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void DVRClipObjects::initMethod (void)
{
}

//! react to field changes
void DVRClipObjects::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void DVRClipObjects::dump(      UInt32    , 
                          const BitVector ) const
{
    SLOG << "Dump DVRClipObjects NI" << std::endl;
}

//! Count objects in the list
UInt32 DVRClipObjects::count(void) const
{
    return _mfClipObjects.size();
}

//! Prepare the clip objects for clipping a volume's slices
void DVRClipObjects::initialize(const Matrix &volumeToWorld, 
                                const Plane  &referencePlane)
{
    for(UInt32 i = 0; i < _mfClipObjects.size(); i++)
    {
        _mfClipObjects[i]->initialize       (volumeToWorld );
        _mfClipObjects[i]->setReferencePlane(referencePlane);
    }
}

// deprecated -> remove
void DVRClipObjects::initialize(const Matrix &volumeToWorld)
{
    for(UInt32 i = 0; i < _mfClipObjects.size(); i++)
        _mfClipObjects[i]->initialize(volumeToWorld);
}

//! Set the reference plane used in clipping
// deprecated -> remove
void DVRClipObjects::setReferencePlane(const Plane &referencePlane)
{
    for(UInt32 i = 0; i < _mfClipObjects.size(); i++)
        _mfClipObjects[i]->setReferencePlane(referencePlane);
}

//! Get the ith object
DVRClipGeometryPtr DVRClipObjects::get(UInt32 i)
{
    return _mfClipObjects[i];
}

//! Add a clip object
void DVRClipObjects::add(DVRClipGeometryPtr obj)
{
    if(obj == NullFC)
        return;

    addRefCP(obj);

    _mfClipObjects.push_back(obj);
}

//! Remove a clip object
void DVRClipObjects::remove(DVRClipGeometryPtr obj)
{
    if(obj == NullFC)
        return;

    for(MFDVRClipGeometryPtr::iterator i  = _mfClipObjects.begin(); 
                                       i != _mfClipObjects.end(); 
                                       i++)
    {
        if(*i == obj)
        {
            _mfClipObjects.erase(i);
            subRefCP(obj);
            break;
        }
    }
}

//! Remove the i-th clip object
void DVRClipObjects::remove(UInt32 n)
{
    MFDVRClipGeometryPtr::iterator it = _mfClipObjects.begin();

    for(UInt32 i = 0; i < n && it != _mfClipObjects.end(); i++) 
        it++;  

    if(it != _mfClipObjects.end())
    {
        subRefCP(*it);
        _mfClipObjects.erase(it);    
    }
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGDVRCLIPOBJECTSBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDVRCLIPOBJECTSBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDVRCLIPOBJECTSFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
