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

#ifdef _MSC_VER
# pragma warning (disable: 4786)
#endif

#include "OSGTextFaceFactory.h"
#include "OSGTextBackend.h"
#include "OSGTextVectorFace.h"
#include "OSGTextPixmapFace.h"
#include "OSGTextTXFFace.h"
#include "OSGTextWIN32Backend.h"
#include "OSGTextMacBackend.h"
#include "OSGTextFT2Backend.h"

#ifdef __sgi
# include <assert.h>
#else
# include <cassert>
#endif


using namespace std;


OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Helper function that gets called from osgExit
// Author: pdaehne
//----------------------------------------------------------------------
static bool terminateFaceFactory()
{
    // we need this extra valid flag because the compiler creates
    // some atexit() code for destruction of the TextFaceFactory instance
    // and this would conflict with osgExit() which is also called via atexit()!
    // The osgExit() would be called after the TextFaceFactory instance has already
    // been destroyed ...

    if(TextFaceFactory::isValid())
        TextFaceFactory::the().clearCache();
    //else already destroyed do nothing.
    return true;
}


//----------------------------------------------------------------------
// Static Class Variable implementations
// Author: pdaehne
//----------------------------------------------------------------------
bool TextFaceFactory::_valid = false;
TextFaceFactory TextFaceFactory::_the;

//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFaceFactory::TextFaceFactory()
: _backend(), _vectorFaceMap(), _pixmapFaceMap(), _txfFaceMap()
{
    _valid = true;
#if defined(_WIN32)
    _backend = new TextWIN32Backend();
#elif 0 // defined(__APPLE__X) not more apply text
# ifdef __LP64__ 
#  if defined(FT2_LIB)
    _backend = new TextFT2Backend();
#  else
    _backend = NULL;
#  endif
# else
    _backend = new TextMacBackend();
# endif
#elif defined(FT2_LIB)
    _backend = new TextFT2Backend();
#else
    _backend = 0;
#endif

    addSystemExitFunction(&terminateFaceFactory);
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFaceFactory::~TextFaceFactory()
{
    _valid = false;
    clearCache();
    delete _backend;
}


//----------------------------------------------------------------------
// Returns a vector face
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFace *TextFaceFactory::createVectorFace(const string &family,
                                                 TextFace::Style style)
{
    // Try to find the face in the cache
    pair<VectorFaceMap::iterator, VectorFaceMap::iterator> range = _vectorFaceMap.equal_range(family);
    VectorFaceMap::iterator it;
    for (it = range.first; it != range.second; ++it)
    {
        assert(it->second != 0);
        if (it->second->getStyle() == style)
            return it->second;
    }

    // We did not find the face in the cache, so let the backend create it
    if (_backend == 0)
        return 0;
    TextVectorFace *face = _backend->createVectorFace(family, style);
    if (face == 0)
        return 0;
    _vectorFaceMap.insert(VectorFaceMap::value_type(family, face));
    addRefP(face);
    return face;
}


//----------------------------------------------------------------------
// Returns a pixmap face
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFace *TextFaceFactory::createPixmapFace(const string &family,
                                                  TextFace::Style style,
                                                  UInt32 size)
{
    // Try to find the face in the cache
    pair<PixmapFaceMap::iterator, PixmapFaceMap::iterator> range = _pixmapFaceMap.equal_range(family);
    PixmapFaceMap::iterator it;
    for (it = range.first; it != range.second; ++it)
    {
        assert(it->second != 0);
        if ((it->second->getStyle() == style) && (it->second->getSize() == size))
            return it->second;
    }

    // We did not find the face in the cache, so let the backend create it
    if (_backend == 0)
        return 0;
    TextPixmapFace *face = _backend->createPixmapFace(family, style, size);
    if (face == 0)
        return 0;
    _pixmapFaceMap.insert(PixmapFaceMap::value_type(family, face));
    addRefP(face);
    return face;
}


//----------------------------------------------------------------------
// Returns a TXF face
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFace *TextFaceFactory::createTXFFace(const string &family,
                                            TextFace::Style style,
                                            const TextTXFParam &param)
{
    // Try to find the face in the cache
    pair<TXFFaceMap::iterator, TXFFaceMap::iterator> range = _txfFaceMap.equal_range(family);
    TXFFaceMap::iterator it;
    for (it = range.first; it != range.second; ++it)
    {
        assert(it->second != 0);
        if ((it->second->getStyle() == style) && (it->second->getParam() == param))
            return it->second;
    }

    // We did not find the face in the cache, so let the backend create it
    if (_backend == 0)
        return 0;
    TextTXFFace *face = _backend->createTXFFace(family, style, param);
    if (face == 0)
        return 0;
    _txfFaceMap.insert(TXFFaceMap::value_type(family, face));
    addRefP(face);
    return face;
}


//----------------------------------------------------------------------
// Removes all faces from the face cache
// Author: pdaehne
//----------------------------------------------------------------------
void TextFaceFactory::clearCache()
{
    // Vector faces
    VectorFaceMap::iterator vIt;
    for (vIt = _vectorFaceMap.begin(); vIt != _vectorFaceMap.end(); ++vIt)
    {
        assert(vIt->second != 0);
        subRefP(vIt->second);
    }
    _vectorFaceMap.clear();

    // Pixmap faces
    PixmapFaceMap::iterator pIt;
    for (pIt = _pixmapFaceMap.begin(); pIt != _pixmapFaceMap.end(); ++pIt)
    {
        assert(pIt->second != 0);
        subRefP(pIt->second);
    }
    _pixmapFaceMap.clear();

    // TXF faces
    TXFFaceMap::iterator tIt;
    for (tIt = _txfFaceMap.begin(); tIt != _txfFaceMap.end(); ++tIt)
    {
        assert(tIt->second != 0);
        subRefP(tIt->second);
    }
    _txfFaceMap.clear();
}


//----------------------------------------------------------------------
// Returns the names of all font families available
// Author: pdaehne
//----------------------------------------------------------------------
void TextFaceFactory::getFontFamilies(vector<string> &families) const
{
    families.clear();
    if (_backend != 0)
        _backend->getFontFamilies(families);
}

bool TextFaceFactory::isValid(void)
{
    return _valid;
}

OSG_END_NAMESPACE


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
    static OSG::Char8 cvsid_cpp[] = "@(#)$Id: OSGTextFaceFactory.cpp,v 1.5 2012/03/04 17:29:59 yjung Exp $";
    static OSG::Char8 cvsid_hpp[] = OSGTEXTFACEFACTORY_HEADER_CVSID;
    static OSG::Char8 cvsid_inl[] = OSGTEXTFACEFACTORY_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
