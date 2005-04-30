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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGNodePtr.h"
#include "OSGMaterialPool.h"
#include "OSGMaterialGroup.h"
#include "OSGMaterialDrawable.h"

OSG_USING_NAMESPACE

/*! \class osg::MaterialPool
*/

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void MaterialPool::changed(BitVector whichField, UInt32 origin)
{
    if(origin & ChangedOrigin::Abstract)
    {
        MFMaterialPtr::iterator matIt  = _mfMaterials.begin();
        MFMaterialPtr::iterator matEnd = _mfMaterials.end ();
        
        while(matIt != matEnd)
        {
            addRefCP(*matIt);
            ++matIt;
        }
    }

    if(whichField & MaterialsFieldMask)
    {
        sync();
    }
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void MaterialPool::dump(      UInt32    uiIndent, 
                         const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MaterialPool::MaterialPool(void) :
    Inherited(),
    _mats()
{
}

MaterialPool::MaterialPool(const MaterialPool &source) :
    Inherited(source),
    _mats(source._mats)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MaterialPool::~MaterialPool(void)
{
}

void MaterialPool::onDestroy(void)
{
    // if we're in shutdown this is the prototype ...
    if(OSG::GlobalSystemState == OSG::Shutdown)
        return;

    MFMaterialPtr::iterator       matIt        = _mfMaterials.begin();
    MFMaterialPtr::const_iterator endMaterials = _mfMaterials.end  ();

    FINFO(("MaterialPool::onDestroy : subrefing %u materials\n", _mfMaterials.size()));
    while(matIt != endMaterials)
    {
        subRefCP(*matIt);
        ++matIt;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */
 
void MaterialPool::initMethod(void)
{
}


void MaterialPool::sync(void)
{
    // should be safe as the materials interface is protected.
    if(_mfMaterials.size() == _mats.size())
    {
        FINFO(("MaterialPool::sync : %u materials already synced, nothing to do.\n", _mfMaterials.size()));
        return;
    }

    MFMaterialPtr::iterator       matIt        = _mfMaterials.begin();
    MFMaterialPtr::const_iterator endMaterials = _mfMaterials.end  ();

    while(matIt != endMaterials)
    {
        // this is already done in the osb loader!
        //addRefCP(*matIt);
        _mats.insert(*matIt);
        ++matIt;
    }
    FINFO(("MaterialPool::sync : synced %u materials\n", _mfMaterials.size()));
}

/*-------------------------------------------------------------------------*/
/*                             Access                                      */

void MaterialPool::add(const MaterialPtr &mat)
{
    if(mat == NullFC)
        return;

    if(_mats.count(mat) > 0)
        return;

    addRefCP(mat);
    _mats.insert(mat);
    _mfMaterials.push_back(mat);
}

void MaterialPool::add(const NodePtr &root)
{
    traverse(root, osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE,
                   MaterialPool, NodePtr>(this, &MaterialPool::addMaterialCB));
}

void MaterialPool::add(const MaterialPoolPtr &mp)
{
    if(mp == getPtr())
        return;

    MFMaterialPtr::iterator       matIt        = mp->_mfMaterials.begin();
    MFMaterialPtr::const_iterator endMaterials = mp->_mfMaterials.end  ();

    while(matIt != endMaterials)
    {
        add(*matIt);
        ++matIt;
    }
}

Int32 MaterialPool::find(const MaterialPtr &mat) const
{
    if(_mats.count(mat) == 0)
        return -1;

    UInt32 index;

    for(index = 0; index < _mfMaterials.size(); ++index)
    {
        if(_mfMaterials[index] == mat)
            return index;
    }
    return -1;
}

void MaterialPool::sub(const MaterialPtr &mat)
{
    if(_mats.count(mat) == 0)
    {
        SWARNING << "MaterialPool(" << this << ")::sub: " << mat 
                 << " is not one of my materials!" << std::endl;
        return;
    }

    MFMaterialPtr::iterator matIt = _mfMaterials.find(mat);

    if(matIt != _mfMaterials.end())
    {
        _mats.erase(mat);
        subRefCP(mat);

        _mfMaterials.erase(matIt);
    }
    else
    {
        SWARNING << "MaterialPool(" << this << ")::sub: " << mat 
                 << " is not one of my materials!" << std::endl;
    }
}

void MaterialPool::sub(const NodePtr &root)
{
    traverse(root, osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE,
                   MaterialPool, NodePtr>(this, &MaterialPool::subMaterialCB));
}

void MaterialPool::sub(const MaterialPoolPtr &mp)
{
    if(mp == getPtr())
        return;

    MFMaterialPtr::iterator       matIt        = mp->_mfMaterials.begin();
    MFMaterialPtr::const_iterator endMaterials = mp->_mfMaterials.end  ();

    while(matIt != endMaterials)
    {
        sub(*matIt);
        ++matIt;
    }
}

void MaterialPool::sub(UInt32 index)
{
    MFMaterialPtr::iterator matIt = _mfMaterials.begin();

    matIt += index;

    if(matIt != _mfMaterials.end())
    {
        subRefCP(*matIt);
        _mats.erase(*matIt);
        _mfMaterials.erase(matIt);
    }
}

void MaterialPool::get(std::vector<MaterialPtr> &mats)
{
    mats.clear();
    mats.reserve(_mfMaterials.getSize());
    MFMaterialPtr::iterator       matIt        = _mfMaterials.begin();
    MFMaterialPtr::const_iterator endMaterials = _mfMaterials.end  ();

    while(matIt != endMaterials)
    {
        mats.push_back(*matIt);
        ++matIt;
    }
}

const std::set<MaterialPtr> &MaterialPool::get(void)
{
    return _mats;
}

void MaterialPool::clear(void)
{
    MFMaterialPtr::iterator       matIt        = _mfMaterials.begin();
    MFMaterialPtr::const_iterator endMaterials = _mfMaterials.end  ();

    while(matIt != endMaterials)
    {
        subRefCP(*matIt);
        ++matIt;
    }
    _mfMaterials.clear();
    _mats.clear();
}

Action::ResultE MaterialPool::addMaterialCB(NodePtr &node)
{
    FieldContainerPtr core = node->getCore();

    if(core == NullFC)
        return Action::Continue;

    MaterialGroupPtr mg = MaterialGroupPtr::dcast(core);
    if(mg != NullFC)
    {
        add(mg->getMaterial());
        return Action::Continue;
    }

    MaterialPoolPtr mp = MaterialPoolPtr::dcast(core);
    if(mp != NullFC)
    {
        add(mp);
        return Action::Continue;
    }

    MaterialDrawablePtr md = MaterialDrawablePtr::dcast(core);
    if(md != NullFC)
    {
        add(md->getMaterial());
        return Action::Continue;
    }

    const char *typename2 = core->getType().getName().str();
    if(!strcmp(typename2, "DVRVolume"))
    {
        Field *field = core->getField("renderMaterial");
        if(field != NULL)
        {
            add(MaterialPtr::dcast(((SFFieldContainerPtr *) field)->getValue()));
        }
    }

    return Action::Continue;
}

Action::ResultE MaterialPool::subMaterialCB(NodePtr &node)
{
    FieldContainerPtr core = node->getCore();

    if(core == NullFC)
        return Action::Continue;

    MaterialGroupPtr mg = MaterialGroupPtr::dcast(core);
    if(mg != NullFC)
    {
        sub(mg->getMaterial());
        return Action::Continue;
    }

    // ignore MaterialPool node!
#if 0
    MaterialPoolPtr mp = MaterialPoolPtr::dcast(core);
    if(mp != NullFC)
    {
        sub(mp);
        return Action::Continue;
    }
#endif

    MaterialDrawablePtr md = MaterialDrawablePtr::dcast(core);
    if(md != NullFC)
    {
        sub(md->getMaterial());
        return Action::Continue;
    }

    const char *typename2 = core->getType().getName().str();
    if(!strcmp(typename2, "DVRVolume"))
    {
        Field *field = core->getField("renderMaterial");
        if(field != NULL)
        {
            sub(MaterialPtr::dcast(((SFFieldContainerPtr *) field)->getValue()));
        }
    }

    return Action::Continue;
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGMaterialPool.cpp,v 1.1 2005/04/30 15:03:19 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGMATERIALPOOL_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGMATERIALPOOL_INLINE_CVSID;
}
