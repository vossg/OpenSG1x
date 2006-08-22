/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OSGSimpleGeometry.h>
#include "OSGSwitchMaterial.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SwitchMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SwitchMaterial::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SwitchMaterial::SwitchMaterial(void) :
    Inherited()
{
}

SwitchMaterial::SwitchMaterial(const SwitchMaterial &source) :
    Inherited(source)
{
}

SwitchMaterial::~SwitchMaterial(void)
{
    // ACHTUNG _pState wird der State vom jeweiligen aktiven Material zugewiesen.
    // wenn nun die Materialien zerstoert werden dann wird im Material::~Material
    // ein subRefCP(_pState) aufgerufen. Dieser subRefCP wuerde dann nochmal mit dem
    // gleichen ungueltigen pointer fuer das SwitchMaterial aufgerufen werden und
    // das kracht natürlich, deswegen wird er jetzt einfach auf NullFC gesetzt!
    _pState = NullFC;
    MFMaterialPtr::iterator       matIt        = _mfMaterials.begin();
    MFMaterialPtr::const_iterator matEnd       = _mfMaterials.end  ();

    FINFO(("SwitchMaterial::onDestroy : subrefing %u materials\n", _mfMaterials.size()));
    while(matIt != matEnd)
    {
        subRefCP(*matIt);
        ++matIt;
    }
    _mfMaterials.clear();
}

/*----------------------------- class specific ----------------------------*/

void SwitchMaterial::changed(BitVector whichField, UInt32 origin)
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

    // Don't need to call rebuildState it is allready called in the
    // base class method Material::changed()
#if 0
    if(whichField & SwitchMaterial::ChoiceFieldMask)
    {
        makeState();
        rebuildState();
    }
#endif

    Inherited::changed(whichField, origin);
}

void SwitchMaterial::addMaterial(MaterialPtr mat)
{
    if(mat == NullFC)
        return;

    _mfMaterials.push_back(mat);
    addRefCP(mat);
}

void SwitchMaterial::subMaterial(MaterialPtr mat)
{
    if(mat == NullFC)
        return;

    UInt32 i;
    
    for(i = 0; i < _mfMaterials.size(); ++i)
    {
        if(_mfMaterials[i] == mat)
        {
            subRefCP(mat);
            _mfMaterials.erase(_mfMaterials.begin() + i);
            return;
        }
    }

    SWARNING << "SwitchMaterial::subMaterial(" << this << ") has no material "
             << mat << std::endl;
}

bool SwitchMaterial::hasMaterial(MaterialPtr mat)
{
    UInt32 i;

    for(i = 0; i < _mfMaterials.size(); ++i)
    {
        if(_mfMaterials[i] == mat)
            return true;
    }

    return false;
}

MaterialPtr SwitchMaterial::getMaterial(UInt32 index)
{
    if(index >= _mfMaterials.size())
    {
        FWARNING(("SwitchMaterial::getMaterial : index %u out of range\n", index));
        return NullFC;
    }
    return _mfMaterials[index];
}

MaterialPtr SwitchMaterial::getCurrentMaterial(void)
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        FWARNING(("SwitchMaterial::getCurrentMaterial : current choice %u out of range\n", choice));
        return NullFC;
    }
    return _mfMaterials[choice];
}

/*! Draw the geometry with this material.
*/

void SwitchMaterial::draw(Geometry *OSG_CHECK_ARG(geo), DrawActionBase *OSG_CHECK_ARG(action))
{
}

/*! Draw the function behind the functor with this material. The functored
    function should be very careful changing OpenGL state, better just use
    glBegin(), glEnd() and the standard stuff in between.
*/

void SwitchMaterial::draw(DrawFunctor &OSG_CHECK_ARG(func), DrawActionBase *OSG_CHECK_ARG(action))
{
}

/*! Create a osg::State that represents this Material and return it.
*/

StatePtr SwitchMaterial::makeState(void)
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::makeState: choice index (" << choice << ") out of range!" << std::endl;
        return OSG::getDefaultMaterial()->makeState();
    }

    if(_mfMaterials[choice] != NullFC)
    {
        return _mfMaterials[choice]->makeState();
    }

    return OSG::getDefaultMaterial()->makeState();
}

/*! Rebuild the internal State. Just collects the chunks in the State.
*/

void SwitchMaterial::rebuildState(void)
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::rebuildState: choice index (" << choice << ") out of range!" << std::endl;
        OSG::getDefaultMaterial()->rebuildState();
        //_pState = OSG::getDefaultMaterial()->getState();
        return;
    }

    if(_mfMaterials[choice] != NullFC)
    {
        _mfMaterials[choice]->rebuildState();
        //_pState = _mfMaterials[choice]->getState();
    }
    else
    {
        OSG::getDefaultMaterial()->rebuildState();
        //_pState = OSG::getDefaultMaterial()->getState();
    }
}

StatePtr SwitchMaterial::getState(UInt32 index)
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::getState: choice index out of range!" << std::endl;
        return NullFC;
    }

    if(_mfMaterials[choice] != NullFC)
    {
        if(_mfMaterials[choice]->getState(index) == NullFC)
            rebuildState();

        return _mfMaterials[choice]->getState(index);
    }

    return NullFC;
}

bool SwitchMaterial::isMultiPass(void) const
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::isMultiPass: choice index out of range!" << std::endl;
        return false;
    }

    if(_mfMaterials[choice] != NullFC)
        return _mfMaterials[choice]->isMultiPass();

    return false;
}

UInt32 SwitchMaterial::getNPasses(void) const
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::getNPasses: choice index out of range!" << std::endl;
        return 1;
    }

    if(_mfMaterials[choice] != NullFC)
        return _mfMaterials[choice]->getNPasses();

    return 1;
}

/*! Check if the Material (i.e. any of its materials) is transparent..
*/
bool SwitchMaterial::isTransparent(void) const
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::isTransparent: choice index out of range!" << std::endl;
        return false;
    }

    if(_mfMaterials[choice] != NullFC)
        return _mfMaterials[choice]->isTransparent();

    return false;
}

Int32 SwitchMaterial::getRealSortKey(void) const
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::isTransparent: choice index out of range!" << std::endl;
        return Inherited::getRealSortKey();
    }

    if(_mfMaterials[choice] != NullFC)
        return _mfMaterials[choice]->getRealSortKey();

    return Inherited::getRealSortKey();
}

void SwitchMaterial::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SwitchMaterial NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSwitchMaterial.cpp,v 1.4 2006/08/22 10:11:44 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSWITCHMATERIALBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSWITCHMATERIALBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSWITCHMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

