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

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
#include <OSGRemoteAspect.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGStereoCameraDecorator.h>
#include <OSGRenderAction.h>

#include <OSGShaderParameter.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>

#include "OSGCGChunk.h"

#include <Cg/cgGL.h>

OSG_USING_NAMESPACE

CGChunk::OSGCGcontext CGChunk::_current_context = NULL;
CGChunk::parametercbfp CGChunk::_userParametersCallback = NULL;

/*! \class osg::CGChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass CGChunk::_class("CG");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void CGChunk::cgErrorCallback(void)
{
    CGerror LastError = cgGetError();

    if(LastError)
    {
        FWARNING(("Cg error occured!\n\n"));
        if(cgIsContext((CGcontext) _current_context))
        {
            const char *Listing = cgGetLastListing((CGcontext) _current_context);
            FWARNING(("\n---------------------------------------------------\n"));
            FWARNING(("%s\n\n", cgGetErrorString(LastError)));
            FWARNING(("%s\n", Listing));
            FWARNING(("---------------------------------------------------\n"));
        }
    }
}

/*----------------------- constructors & destructors ----------------------*/

CGChunk::CGChunk(void) :
    Inherited(),
    _context(NULL),
    _vProgram(NULL),
    _fProgram(NULL),
    _vp_isvalid(false),
    _fp_isvalid(false),
    _osgParametersCallbacks(),
    _oldParameterSize(0)
{
}

CGChunk::CGChunk(const CGChunk &source) :
    Inherited(source),
    _context(source._context),
    _vProgram(source._vProgram),
    _fProgram(source._fProgram),
    _vp_isvalid(source._vp_isvalid),
    _fp_isvalid(source._fp_isvalid),
    _osgParametersCallbacks(source._osgParametersCallbacks),
    _oldParameterSize(source._oldParameterSize)
{
}

CGChunk::~CGChunk(void)
{
}

void CGChunk::onCreate(const CGChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(CGChunk::getClassType().getId(),
                                 CGChunk::GLIdFieldMask);
    
    cgSetErrorCallback(CGChunk::cgErrorCallback);

    CGChunkPtr tmpPtr(*this);
    beginEditCP(tmpPtr, CGChunk::GLIdFieldMask);
        setGLId(Window::registerGLObject(osgTypedMethodVoidFunctor2ObjCPtrPtr<CGChunkPtr,
                                         Window , UInt32>(tmpPtr, &CGChunk::handleGL), 1));
    endEditCP(tmpPtr, CGChunk::GLIdFieldMask);
}

void CGChunk::onDestroy(void)
{
    Inherited::onDestroy();

    if(cgIsProgram((CGprogram) _vProgram))
        cgDestroyProgram((CGprogram) _vProgram);
    if(cgIsProgram((CGprogram) _fProgram))
        cgDestroyProgram((CGprogram) _fProgram);
    if(cgIsContext((CGcontext) _context))
        cgDestroyContext((CGcontext) _context);
        
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

const StateChunkClass *CGChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void CGChunk::changed(BitVector whichField, UInt32 origin)
{
    if((whichField & VertexProgramFieldMask) ||
       (whichField & FragmentProgramFieldMask))
    {
        Window::reinitializeGLObject(getGLId());
    }  
     
    if(whichField & ParametersFieldMask)
    {
        Window::refreshGLObject(getGLId());
    }

    Inherited::changed(whichField, origin);
}

void CGChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/
void CGChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::destroy)
    {
        ;
    }
    else if(mode == Window::finaldestroy)
    {
        ;//SWARNING << "Last program user destroyed" << std::endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh)
    {
        if(mode != Window::needrefresh)
        {
            updateCGContext();
        }

        updateParameters(win, getParameters());
    }
    else
    {
        SWARNING << "CGChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

void CGChunk::updateCGContext(void)
{
    if(_context == NULL)
        _context = (OSGCGcontext) cgCreateContext();
    
    _current_context = _context;

    // can't do this in onCreate()
    if(getVertexProfile() == CG_PROFILE_UNKNOWN)
        setVertexProfile(cgGLGetLatestProfile(CG_GL_VERTEX));
    cgGLSetOptimalOptions((CGprofile) getVertexProfile());
    
    if(getFragmentProfile() == CG_PROFILE_UNKNOWN)
        setFragmentProfile(cgGLGetLatestProfile(CG_GL_FRAGMENT));
    cgGLSetOptimalOptions((CGprofile) getFragmentProfile());

    // reload programs
    if(hasVP() && !getVertexProgram().empty())
    {
        if(cgIsProgram((CGprogram) _vProgram))
            cgDestroyProgram((CGprogram) _vProgram);

        const char *entry = NULL;
        if(!getVertexEntryPoint().empty())
            entry = getVertexEntryPoint().c_str();
    
        const char **args = NULL;
        if(!getVertexArguments().empty())
        {
            UInt32 asize = getVertexArguments().size();
            args = new const char *[asize + 1];
            for(UInt32 i=0;i<asize;++i)
                args[i] = getVertexArguments()[i].c_str();
            args[asize] = NULL;
        }
        
        _vProgram = (OSGCGprogram) cgCreateProgram((CGcontext) _context,
                                    CG_SOURCE, getVertexProgram().c_str(),
                                    (CGprofile) getVertexProfile(), entry, args);
        if(_vProgram)
        {
            _vp_isvalid = true;
            cgGLLoadProgram((CGprogram) _vProgram);
        }
        else
        {
            _vp_isvalid = false;
            FWARNING(("Couldn't load vertex program!\n"));
        }
        
        if(!getVertexArguments().empty())
            delete [] args;
    }

    if(hasFP() && !getFragmentProgram().empty())
    {
        if(cgIsProgram((CGprogram) _fProgram))
            cgDestroyProgram((CGprogram) _fProgram);

        const char *entry = NULL;
        if(!getFragmentEntryPoint().empty())
            entry = getFragmentEntryPoint().c_str();
    
        const char **args = NULL;
        if(!getFragmentArguments().empty())
        {
            UInt32 asize = getFragmentArguments().size();
            args = new const char *[asize + 1];
            for(UInt32 i=0;i<asize;++i)
                args[i] = getFragmentArguments()[i].c_str();
            args[asize] = NULL;
        }
        
        _fProgram = (OSGCGprogram) cgCreateProgram((CGcontext) _context,
                                    CG_SOURCE, getFragmentProgram().c_str(),
                                    (CGprofile) getFragmentProfile(), entry, args);
        if(cgIsProgram((CGprogram) _fProgram))
        {
            _fp_isvalid = true;
            cgGLLoadProgram((CGprogram) _fProgram);
        }
        else
        {
            _fp_isvalid = false;
            FWARNING(("Couldn't load fragment program!\n"));
        }

        if(!getFragmentArguments().empty())
            delete [] args;
    }
}

void CGChunk::updateParameters(Window *OSG_CHECK_ARG(win),
                               const MFShaderParameterPtr &parameters,
                               bool force)
{
    checkOSGParameters();

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        // works also but is not possible with a switch and a switch is much faster.
        //UInt16 groupid = parameter->getType().getGroupId();
        //if(groupid == ShaderParameterInt::getClassType().getGroupId())

        if(!force)
        {
            if(!parameter->hasChanged())
                    continue;
            parameter->resetChanged();
        }

        switch(parameter->getTypeId())
        {
            //case ShaderParameter::SHPTypeBool:
            //break;
            //case ShaderParameter::SHPTypeInt:
            //break;
            case ShaderParameter::SHPTypeReal:
            {
                ShaderParameterRealPtr p = ShaderParameterRealPtr::dcast(parameter);

                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram, p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter1f(vpparam, p->getValue());
                    //FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram, p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter1f(fpparam, p->getValue());
                }
            }
            break;
            case ShaderParameter::SHPTypeVec2f:
            {
                ShaderParameterVec2fPtr p = ShaderParameterVec2fPtr::dcast(parameter);

                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter2fv(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter2fv(fpparam, p->getValue().getValues());
                }
            }
            break;
            case ShaderParameter::SHPTypeVec3f:
            {
                ShaderParameterVec3fPtr p = ShaderParameterVec3fPtr::dcast(parameter);

                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter3fv(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter3fv(fpparam, p->getValue().getValues());
                }
            }
            break;
            case ShaderParameter::SHPTypeVec4f:
            {
                ShaderParameterVec4fPtr p = ShaderParameterVec4fPtr::dcast(parameter);
                
                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter4fv(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter4fv(fpparam, p->getValue().getValues());
                }
            }
            break;
            case ShaderParameter::SHPTypeMatrix:
            {
                ShaderParameterMatrixPtr p = ShaderParameterMatrixPtr::dcast(parameter);
                
                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetMatrixParameterfr(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetMatrixParameterfr(fpparam, p->getValue().getValues());
                }
            }
            break;
            default:
                FWARNING(("Parameter '%s' has unknown tpye %d!\n", parameter->getName().c_str(),
                                                                   parameter->getTypeId()));
            break;
        }
    }
}

CGChunk::OSGCGcontext CGChunk::getContext(void)
{
    return _context;
}

CGChunk::OSGCGprogram CGChunk::getVP(void)
{
    return _vProgram;
}

bool CGChunk::isVPValid(void)
{
    return _vp_isvalid;
}

CGChunk::OSGCGprogram CGChunk::getFP(void)
{
    return _fProgram;
}

bool CGChunk::isFPValid(void)
{
    return _fp_isvalid;
}


/*------------------------------ State ------------------------------------*/

void CGChunk::update(DrawActionBase *action)
{
    action->getWindow()->validateGLObject(getGLId());

    updateOSGParameters(action);
}

void CGChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_vp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getVertexProfile());
        cgGLBindProgram((CGprogram) _vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getFragmentProfile());
        cgGLBindProgram((CGprogram) _fProgram);
    }

    updateOSGParameters(action);
}




void CGChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    CGChunk *old = dynamic_cast<CGChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "CGChunk::changeFrom: caught non-CGChunk!\n"));
        return;
    }

    if(_osgParametersCallbacks.empty())
    {
        // For the state parameter OSGModelView... parameters we have
        // to update even if the state didn't change!
        // CGChunk didn't change so do nothing.
        if(old == this)
            return;
    }

    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    // now deactivate the old.
    if(old->_fp_isvalid)
    {
        // unbinds program too
        cgGLDisableProfile((CGprofile) old->getFragmentProfile());
    }

    if(old->_vp_isvalid)
    {
        // unbinds program too
        cgGLDisableProfile((CGprofile) old->getVertexProfile());
    }

    if(_vp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getVertexProfile());
        cgGLBindProgram((CGprogram) _vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getFragmentProfile());
        cgGLBindProgram((CGprogram) _fProgram);
    }

    updateOSGParameters(action);
}


void CGChunk::deactivate(DrawActionBase *OSG_CHECK_ARG(action), UInt32 OSG_CHECK_ARG(idx))
{
    if(_fp_isvalid)
        cgGLDisableProfile((CGprofile) getFragmentProfile());

    if(_vp_isvalid)
        cgGLDisableProfile((CGprofile) getVertexProfile());
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CGChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CGChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CGChunk::operator == (const StateChunk &other) const
{
    CGChunk const *tother = dynamic_cast<CGChunk const*>(&other);

    if(!tother)
        return false;

    if(getVertexProgram() != tother->getVertexProgram() ||
       getVertexProfile() != tother->getVertexProfile() ||
       getFragmentProgram() != tother->getFragmentProgram() ||
       getFragmentProfile() != tother->getFragmentProfile() ||
       getParameters().size() != tother->getParameters().size())
        return false;

    return true;
}

bool CGChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


bool CGChunk::hasVP(void)
{
    if(cgGLIsProfileSupported((CGprofile) getVertexProfile()))
    {
        return true;
    }
    
    SWARNING << "Vertex programming extensions "
             << cgGetProfileString((CGprofile) getVertexProfile())
             << " not supported!" << std::endl;
    return false;
}

bool CGChunk::hasFP(void)
{
    if (cgGLIsProfileSupported((CGprofile) getFragmentProfile()))
        return true;

    SWARNING << "Fragment programming extensions "
             << cgGetProfileString((CGprofile) getFragmentProfile())
             << " not supported!" << std::endl;
    return false;
}


void CGChunk::checkOSGParameters(void)
{
    // ok this can go wrong if you sub and add a parameter
    // between one begin/endEditCP ...
    if(getParameters().getSize() == _oldParameterSize)
        return;
    _oldParameterSize = getParameters().getSize();

    _osgParametersCallbacks.clear();
    const MFShaderParameterPtr &parameters = getParameters();
    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];
        if(parameter->getName().size() > 3 &&
           parameter->getName()[0] == 'O' &&
           parameter->getName()[1] == 'S' &&
           parameter->getName()[2] == 'G')
        {
            if(parameter->getName() == "OSGWorldMatrix")
            {
                // .net compiler needs this workaround in opt mode ...
                parametercbfp fp = updateWorldMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGInvWorldMatrix")
            {
                // .net compiler needs this workaround in opt mode ...
                parametercbfp fp = updateInvWorldMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGCameraOrientation")
            {
                // .net compiler needs this workaround in opt mode ...
                paramtercbfp fp = updateCameraOrientation;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGCameraPosition")
            {
                paramtercbfp fp = updateCameraPosition;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGProjection")
            {
                paramtercbfp fp = updateProjectionMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGModelViewProjection")
            {
                paramtercbfp fp = updateModelViewProjectionMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGTexture")
            {
                paramtercbfp fp = updateTextureMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGModelView")
            {
                paramtercbfp fp = updateModelViewMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGModelViewI")
            {
                paramtercbfp fp = updateModelViewMatrixI;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGModelViewIT")
            {
                paramtercbfp fp = updateModelViewMatrixIT;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGStereoLeftEye")
            {
                paramtercbfp fp = updateStereoLeftEye;
                _osgParametersCallbacks.push_back(fp);
            }
            else
            {
                FWARNING(("CGChunk::checkOSGParameters : unknown osg paramter '%s'\n",
                         parameter->getName().c_str()));;
            }
        }
    }
}

void CGChunk::setParameterCallback(parametercbfp fp)
{
    _userParametersCallback = fp;
}

void CGChunk::updateOSGParameters(DrawActionBase *action)
{
    if(_userParametersCallback != NULL)
        _userParametersCallback(action, this);

    if(_osgParametersCallbacks.empty())
        return;

    for(UInt32 i=0;i<_osgParametersCallbacks.size();++i)
        _osgParametersCallbacks[i](action, this);
}

void CGChunk::updateWorldMatrix(DrawActionBase *action, CGChunk *cgchunk)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateWorldMatrix : Can't update OSGWorldMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        m = ra->top_matrix();

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGWorldMatrix");
        if(vpparam != 0)
            cgGLSetMatrixParameterfr(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGWorldMatrix");
        if(fpparam != 0)
            cgGLSetMatrixParameterfr(fpparam, m.getValues());
    }
}

void CGChunk::updateInvWorldMatrix(DrawActionBase *action, CGChunk *cgchunk)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateInvWorldMatrix : Can't update OSGInvWorldMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        m = ra->top_matrix();
    m.invert();

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGInvWorldMatrix");
        if(vpparam != 0)
            cgGLSetMatrixParameterfr(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGInvWorldMatrix");
        if(fpparam != 0)
            cgGLSetMatrixParameterfr(fpparam, m.getValues());
    }
}

void CGChunk::updateCameraOrientation(DrawActionBase *action, CGChunk *cgchunk)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateCameraOrientation : Can't update OSGCameraOrientation"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();
    m[3].setValues(0, 0, 0, 1);

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGCameraOrientation");
        if(vpparam != 0)
            cgGLSetMatrixParameterfr(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGCameraOrientation");
        if(fpparam != 0)
            cgGLSetMatrixParameterfr(fpparam, m.getValues());
    }
}

void CGChunk::updateCameraPosition(DrawActionBase *action, CGChunk *cgchunk)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateCameraPosition : Can't update OSGCameraPosition"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();
    Vec3f cameraPos(m[3][0], m[3][1], m[3][2]);

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGCameraPosition");
        if(vpparam != 0)
            cgGLSetParameter3fv(vpparam, cameraPos.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGCameraPosition");
        if(fpparam != 0)
            cgGLSetParameter3fv(fpparam, cameraPos.getValues());
    }
}

void CGChunk::updateProjectionMatrix(DrawActionBase *action, CGChunk *cgchunk)
{
#if 0
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateProjectionMatrix : Can't update OSGProjection"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getProjection(m, action->getViewport()->getPixelWidth(),
                                          action->getViewport()->getPixelHeight());

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGProjection");
        if(vpparam != 0)
            cgGLSetMatrixParameterfr(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGProjection");
        if(fpparam != 0)
            cgGLSetMatrixParameterfr(fpparam, m.getValues());
    }
#else
    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGProjection");
        if(vpparam != 0)
            cgGLSetStateMatrixParameter(vpparam,
                                  CG_GL_PROJECTION_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGProjection");
        if(fpparam != 0)
            cgGLSetStateMatrixParameter(fpparam,
                                  CG_GL_PROJECTION_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
#endif
}

void CGChunk::updateModelViewProjectionMatrix(DrawActionBase *action, CGChunk *cgchunk)
{
#if 0
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateModelViewProjectionMatrix : Can't update OSGModelViewProjection"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m, world, projection, translation, viewing;

    // ok with the new Material::NoStateSorting flags this works fine.
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        world = ra->top_matrix();
    //world = action->getActNode()->getToWorld();

    action->getCamera()->getProjection(projection, action->getViewport()->getPixelWidth(),
                                                   action->getViewport()->getPixelHeight());
    action->getCamera()->getProjectionTranslation(translation, action->getViewport()->getPixelWidth(),
                                                               action->getViewport()->getPixelWidth());
    action->getCamera()->getViewing(viewing, action->getViewport()->getPixelWidth(),
                                             action->getViewport()->getPixelHeight());

    m = projection;
    m.mult(translation);
    m.mult(viewing);
    m.mult(world);

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelViewProjection");
        if(vpparam != 0)
            cgGLSetMatrixParameterfc(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelViewProjection");
        if(fpparam != 0)
            cgGLSetMatrixParameterfc(fpparam, m.getValues());
    }

#else

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelViewProjection");
        if(vpparam != 0)
            cgGLSetStateMatrixParameter(vpparam,
                                  CG_GL_MODELVIEW_PROJECTION_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelViewProjection");
        if(fpparam != 0)
            cgGLSetStateMatrixParameter(fpparam,
                                  CG_GL_MODELVIEW_PROJECTION_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
#endif
}

void CGChunk::updateTextureMatrix(DrawActionBase *action, CGChunk *cgchunk)
{
    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGTexture");
        if(vpparam != 0)
            cgGLSetStateMatrixParameter(vpparam,
                                  CG_GL_TEXTURE_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGTexture");
        if(fpparam != 0)
            cgGLSetStateMatrixParameter(fpparam,
                                  CG_GL_TEXTURE_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
}

void CGChunk::updateModelViewMatrix(DrawActionBase *action, CGChunk *cgchunk)
{
#if 0
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateModelViewMatrix : Can't update OSGModelView"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelView");
        if(vpparam != 0)
            cgGLSetMatrixParameterfr(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelView");
        if(fpparam != 0)
            cgGLSetMatrixParameterfr(fpparam, m.getValues());
    }
#else
    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelView");
        if(vpparam != 0)
            cgGLSetStateMatrixParameter(vpparam,
                                  CG_GL_MODELVIEW_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelView");
        if(fpparam != 0)
            cgGLSetStateMatrixParameter(fpparam,
                                  CG_GL_MODELVIEW_MATRIX,
                                  CG_GL_MATRIX_IDENTITY);
    }
#endif
}

void CGChunk::updateModelViewMatrixI(DrawActionBase *action, CGChunk *cgchunk)
{
#if 0
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateModelViewMatrixI : Can't update OSGModelViewI"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelViewI");
        if(vpparam != 0)
            cgGLSetMatrixParameterfr(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelViewI");
        if(fpparam != 0)
            cgGLSetMatrixParameterfr(fpparam, m.getValues());
    }
#else
    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelViewI");
        if(vpparam != 0)
            cgGLSetStateMatrixParameter(vpparam,
                                  CG_GL_MODELVIEW_MATRIX,
                                  CG_GL_MATRIX_INVERSE);
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelViewI");
        if(fpparam != 0)
            cgGLSetStateMatrixParameter(fpparam,
                                  CG_GL_MODELVIEW_MATRIX,
                                  CG_GL_MATRIX_INVERSE);
    }
#endif
}

void CGChunk::updateModelViewMatrixIT(DrawActionBase *action, CGChunk *cgchunk)
{
#if 0
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateModelViewMatrixIT : Can't update OSGModelViewIT"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();
    m.transpose();

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelViewIT");
        if(vpparam != 0)
            cgGLSetMatrixParameterfr(vpparam, m.getValues());
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelViewIT");
        if(fpparam != 0)
            cgGLSetMatrixParameterfr(fpparam, m.getValues());
    }
#else
    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGModelViewIT");
        if(vpparam != 0)
            cgGLSetStateMatrixParameter(vpparam,
                                  CG_GL_MODELVIEW_MATRIX,
                                  CG_GL_MATRIX_INVERSE_TRANSPOSE);
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGModelViewIT");
        if(fpparam != 0)
            cgGLSetStateMatrixParameter(fpparam,
                                  CG_GL_MODELVIEW_MATRIX,
                                  CG_GL_MATRIX_INVERSE_TRANSPOSE);
    }
#endif
}

void CGChunk::updateStereoLeftEye(DrawActionBase *action, CGChunk *cgchunk)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("CGChunk::updateStereoLeftEye : Can't update OSGStereoLeftEye"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    // ok -1 is mono
    Real32 leftEye = -1.0f;
    // now search for a stereo camera decorator and get the eye.
    CameraPtr camera(*action->getCamera());
    CameraDecoratorPtr decorator = CameraDecoratorPtr::dcast(camera);
    while(decorator != NullFC)
    {
        StereoCameraDecoratorPtr stereoDecorator = StereoCameraDecoratorPtr::dcast(decorator);
        if(stereoDecorator != NullFC)
        {
            if(stereoDecorator->getLeftEye())
                leftEye = 1.0f;
            else
                leftEye = 0.0f;
            break;
        }
        decorator = CameraDecoratorPtr::dcast(decorator->getDecoratee());
    }

    if(cgchunk->_vp_isvalid)
    {
        CGparameter vpparam = cgGetNamedParameter((CGprogram) cgchunk->_vProgram,
                                            "OSGStereoLeftEye");
        if(vpparam != 0)
            cgGLSetParameter1f(vpparam, leftEye);
    }
    
    if(cgchunk->_fp_isvalid)
    {
        CGparameter fpparam = cgGetNamedParameter((CGprogram) cgchunk->_fProgram,
                                            "OSGStereoLeftEye");
        if(fpparam != 0)
            cgGLSetParameter1f(fpparam, leftEye);
    }
}


#if 0
void CGChunk::parseProgramParams(OSGCGprogram prog)
{
    parseParams(cgGetFirstParameter(prog, CG_PROGRAM));
}

void CGChunk::parseParams(OSGCGparameter param)
{
    if(!param)
        return;

    do
    {
        switch(cgGetParameterType((CGparameter) param))
        {
            case CG_STRUCT :
                parseParams(cgGetFirstStructParameter((CGparameter) param));
            break;
            case CG_ARRAY :
            {
                int ArraySize = cgGetArraySize((CGparameter) param, 0);
                int i;
                for(i=0; i < ArraySize; ++i)
                    parseParams(cgGetArrayParameter((CGparameter) param, i));
            }
            break;
            default: // Display parameter information
                const char *name = cgGetParameterName((CGparameter) param);
                CGtype paramType = cgGetParameterType((CGparameter) param);
                const char *type = cgGetTypeString(paramType);
                CGresource paramRes = cgGetParameterResource((CGparameter) param);
                const char *resource = cgGetResourceString(paramRes);
                printf("-- Name = '%s'\n", name);
                printf("-- Type = '%s'\n", type);
                printf("-- Resource = '%s'\n\n", resource);
        }
    }
    while((param = cgGetNextParameter((CGparameter) param)) != 0);
}
#endif

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGChunk.cpp,v 1.2 2003/07/28 08:44:22 amz Exp $";
    static Char8 cvsid_hpp       [] = OSGCGCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
