/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGFIELDCONTAINERFUNCSIMPL_INL_
#define _OSGFIELDCONTAINERFUNCSIMPL_INL_

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

inline
void addRefCP(const FieldContainerPtrBase &objectP)
{
    if(objectP != NullFC)
        objectP.addRef();
}

inline
void subRefCP(const FieldContainerPtrBase &objectP)
{
    if(objectP != NullFC)
        objectP.subRef();
}

inline
void clearRefCP(FieldContainerPtrBase &objectP)
{
    if(objectP != NullFC)
        objectP.subRef();

    objectP = NullFC;
}

inline
void setRefdCP(      FieldContainerPtrBase &objectP,
               const FieldContainerPtrBase &newObjectP)
{
    if(objectP != newObjectP)
    {
        if(objectP != NullFC)
            objectP.subRef();

        objectP = newObjectP;

        if(objectP != NullFC)
            objectP.addRef();
    }
}

inline
void beginEditCP(const FieldContainerPtr &objectP,
                       BitVector         whichField,
                       UInt32            origin    )
{
    if(objectP != NullFC)
        objectP.beginEdit(whichField, origin);
}

inline
void endEditCP(const FieldContainerPtr &objectP,
                     BitVector          whichField,
                     UInt32             origin    )
{
    if(objectP != NullFC)
        objectP.endEdit(whichField, origin);
}

inline
void changedCP(const FieldContainerPtr &objectP,
                     BitVector          whichField,
                     UInt32             origin    )
{
    if(objectP != NullFC)
        objectP.changed(whichField, origin);
}

inline
void endEditNotChangedCP(const FieldContainerPtr &objectP,
                               BitVector          whichField,
                               UInt32             origin    )
{
    if(objectP != NullFC)
        objectP.endEditNotChanged(whichField, origin);
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFUNCS_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINREFUNCSIMPL_INL_ */
