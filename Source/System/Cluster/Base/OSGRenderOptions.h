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

#ifndef _OSGRENDEROPTIONS_H_
#define _OSGRENDEROPTIONS_H_

#include <OSGConfig.h>

#include <OSGRenderOptionsBase.h>

OSG_BEGIN_NAMESPACE

class RenderAction;

class OSG_SYSTEMLIB_DLLMAPPING RenderOptions : public RenderOptionsBase
{
  private:

    typedef RenderOptionsBase Inherited;

  public:

    virtual void changed(BitVector whichField, UInt32 origin);

    void      setWireframe   (bool value          );
    bool      getWireframe   (void                );
    BitVector getChanged     (void                );
    BitVector getLastChanged (void                );
    void      activateOptions(RenderAction *action);

  protected:

    RenderOptions(void);
    RenderOptions(const RenderOptions &source);

    virtual ~RenderOptions(void);

    BitVector   _changed;
    BitVector   _last_changed;
    Real32      _gl_version;
    GLenum      _polygon_mode;
    bool        _backface_culling;
    bool        _two_sided_lighting;
    bool        _spec_tex_lighting;

  private:

    friend class FieldContainer;
    friend class RenderOptionsBase;

    static void initMethod(void);

    void operator =(const RenderOptions &source);
};

typedef RenderOptions *RenderOptionsP;

OSG_END_NAMESPACE

#include <OSGRenderOptionsBase.inl>

#endif /* _OSGRENDEROPTIONS_H_ */

