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

#include <OSGGL.h>
#include <OSGGLU.h>

#include "OSGDrawActionBase.h"

#include "OSGRegisterCombinersChunk.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGRegisterCombinersChunk.cpp,v 1.1 2002/06/10 22:10:46 dirk Exp $";
    static char cvsid_hpp[] = OSGREGISTERCOMBINERSCHUNK_HEADER_CVSID;
    static char cvsid_inl[] = OSGREGISTERCOMBINERSCHUNK_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::RegisterCombinersChunk

*/

StateChunkClass RegisterCombinersChunk::_class("RegisterCombiners");

UInt32 RegisterCombinersChunk::_nvRegisterCombiners;
UInt32 RegisterCombinersChunk::_funcCombinerParameterfv 
                                            = Window::invalidFunctionID; 
UInt32 RegisterCombinersChunk::_funcCombinerInput
                                            = Window::invalidFunctionID; 
UInt32 RegisterCombinersChunk::_funcCombinerOutput
                                            = Window::invalidFunctionID; 
UInt32 RegisterCombinersChunk::_funcFinalCombinerInput
                                            = Window::invalidFunctionID; 

// this should go somewhere central...

#ifdef OSG_DEBUG
#define glErr(text)                           \
{                                   \
        GLenum glerr;                           \
        glerr=glGetError();                     \
        if(glerr!=GL_NO_ERROR)                     \
        {                               \
                fprintf(stderr, "%s failed: %s (%#x)\n", (text),    \
                                        (char*)gluErrorString(glerr), glerr);  \
        }                               \
}
#else
#define glErr(text)
#endif

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

RegisterCombinersChunk::RegisterCombinersChunk(void) :
    Inherited()
{
    _nvRegisterCombiners      = Window::registerExtension( 
                                                "GL_NV_register_combiners" );
    _funcCombinerParameterfv  = Window::registerFunction (
                                                "glCombinerParameterfvNV" );
    _funcCombinerInput        = Window::registerFunction (
                                                "glCombinerInputNV" );
    _funcCombinerOutput       = Window::registerFunction (
                                                "glCombinerOutputNV" );
    _funcFinalCombinerInput   = Window::registerFunction (
                                                "glFinalCombinerInputNV" );

    clearCombiners();
}

//! Copy Constructor

RegisterCombinersChunk::RegisterCombinersChunk(const RegisterCombinersChunk &source) :
    Inherited(source)
{
    clearCombiners();
}

//! Destructor

RegisterCombinersChunk::~RegisterCombinersChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void RegisterCombinersChunk::initMethod (void)
{
}

//! react to field changes

void RegisterCombinersChunk::changed(BitVector, UInt32)
{
    // does it make sense to put the combiner settings into a dlist?
    // if yes we would need to invalidate it here
}

bool RegisterCombinersChunk::isTransparent(void) const
{
    return false;
}

//! output the instance for debug purposes

void RegisterCombinersChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RegisterCombinersChunk NI" << endl;
}


void RegisterCombinersChunk::ensureSizes()
{
    getVariableArgb  ().resize(OSG_NUM_COMBINERS * 3 + 3);
    getVariableBrgb  ().resize(OSG_NUM_COMBINERS * 3 + 3);
    getVariableCrgb  ().resize(OSG_NUM_COMBINERS * 3 + 3);
    getVariableDrgb  ().resize(OSG_NUM_COMBINERS * 3 + 3);
    getVariableAalpha().resize(OSG_NUM_COMBINERS * 3 + 3);
    getVariableBalpha().resize(OSG_NUM_COMBINERS * 3 + 3);
    getVariableCalpha().resize(OSG_NUM_COMBINERS * 3 + 3);
    getVariableDalpha().resize(OSG_NUM_COMBINERS * 3 + 3);
    getOutputABrgb   ().resize(OSG_NUM_COMBINERS);
    getOutputCDrgb   ().resize(OSG_NUM_COMBINERS);
    getOutputSumrgb  ().resize(OSG_NUM_COMBINERS);
    getScalergb      ().resize(OSG_NUM_COMBINERS);
    getBiasrgb       ().resize(OSG_NUM_COMBINERS);
    getDotABrgb      ().resize(OSG_NUM_COMBINERS);
    getDotCDrgb      ().resize(OSG_NUM_COMBINERS);
    getMuxSumrgb     ().resize(OSG_NUM_COMBINERS);
    getScalealpha    ().resize(OSG_NUM_COMBINERS);
    getBiasalpha     ().resize(OSG_NUM_COMBINERS);
    getMuxSumalpha   ().resize(OSG_NUM_COMBINERS);
    getVariableE     ().resize(3);
    getVariableF     ().resize(3);
    getVariableG     ().resize(3);
}


void RegisterCombinersChunk::clearCombiners(void)
{
    ensureSizes();
    
    for(UInt16 i = 0; i < OSG_NUM_COMBINERS * 3; i += 3)
    {
        getVariableArgb  ().setValue(GL_NONE, i);
        getVariableAalpha().setValue(GL_NONE, i);
    }
}

void RegisterCombinersChunk::clearCombiner(UInt16 which)
{
    ensureSizes();
    
    getVariableArgb  ().setValue(GL_NONE, which * 3);
    getVariableAalpha().setValue(GL_NONE, which * 3);
}

void RegisterCombinersChunk::setCombinerRGB(UInt16 which, 
      GLenum ainput, GLenum amapping, GLenum acompusage, 
      GLenum binput, GLenum bmapping, GLenum bcompusage, 
      GLenum cinput, GLenum cmapping, GLenum ccompusage, 
      GLenum dinput, GLenum dmapping, GLenum dcompusage, 
      GLenum outputAB, GLenum outputCD, GLenum outputSum,
      GLenum scale, GLenum bias, 
      GLboolean dotAB, GLboolean dotCD, GLboolean muxSum)
{
    ensureSizes();
    
    const UInt16 ibase = which * 3;
    
    getVariableArgb().setValue(ainput,     ibase);
    getVariableArgb().setValue(amapping,   ibase + 1);
    getVariableArgb().setValue(acompusage, ibase + 2);
    
    getVariableBrgb().setValue(binput,     ibase);
    getVariableBrgb().setValue(bmapping,   ibase + 1);
    getVariableBrgb().setValue(bcompusage, ibase + 2);
    
    getVariableCrgb().setValue(cinput,     ibase);
    getVariableCrgb().setValue(cmapping,   ibase + 1);
    getVariableCrgb().setValue(ccompusage, ibase + 2);
    
    getVariableDrgb().setValue(dinput,     ibase);
    getVariableDrgb().setValue(dmapping,   ibase + 1);
    getVariableDrgb().setValue(dcompusage, ibase + 2);
    
    getOutputABrgb ().setValue(outputAB,   which);
    getOutputCDrgb ().setValue(outputCD,   which);
    getOutputSumrgb().setValue(outputSum,  which);
    getScalergb    ().setValue(scale,      which);
    getBiasrgb     ().setValue(bias,       which);
    getDotABrgb    ().setValue(dotAB,      which);
    getDotCDrgb    ().setValue(dotCD,      which);
    getMuxSumrgb   ().setValue(muxSum,     which);
}

void RegisterCombinersChunk::setCombinerAlpha(UInt16 which, 
      GLenum ainput, GLenum amapping, GLenum acompusage, 
      GLenum binput, GLenum bmapping, GLenum bcompusage, 
      GLenum cinput, GLenum cmapping, GLenum ccompusage, 
      GLenum dinput, GLenum dmapping, GLenum dcompusage, 
      GLenum outputAB, GLenum outputCD, GLenum outputSum,
      GLenum scale, GLenum bias, 
      GLboolean muxSum)
{
    ensureSizes();
    
    const UInt16 ibase = which * 3;
    
    getVariableAalpha().setValue(ainput,     ibase);
    getVariableAalpha().setValue(amapping,   ibase + 1);
    getVariableAalpha().setValue(acompusage, ibase + 2);
    
    getVariableBalpha().setValue(binput,     ibase);
    getVariableBalpha().setValue(bmapping,   ibase + 1);
    getVariableBalpha().setValue(bcompusage, ibase + 2);
    
    getVariableCalpha().setValue(cinput,     ibase);
    getVariableCalpha().setValue(cmapping,   ibase + 1);
    getVariableCalpha().setValue(ccompusage, ibase + 2);
    
    getVariableDalpha().setValue(dinput,     ibase);
    getVariableDalpha().setValue(dmapping,   ibase + 1);
    getVariableDalpha().setValue(dcompusage, ibase + 2);
    
    getOutputABalpha ().setValue(outputAB,   which);
    getOutputCDalpha ().setValue(outputCD,   which);
    getOutputSumalpha().setValue(outputSum,  which);
    getScalealpha    ().setValue(scale,      which);
    getBiasalpha     ().setValue(bias,       which);
    getMuxSumalpha   ().setValue(muxSum,     which);
}

void RegisterCombinersChunk::setFinalCombiner(
      GLenum ainput, GLenum amapping, GLenum acompusage, 
      GLenum binput, GLenum bmapping, GLenum bcompusage, 
      GLenum cinput, GLenum cmapping, GLenum ccompusage, 
      GLenum dinput, GLenum dmapping, GLenum dcompusage, 
      GLenum einput, GLenum emapping, GLenum ecompusage, 
      GLenum finput, GLenum fmapping, GLenum fcompusage, 
      GLenum ginput, GLenum gmapping, GLenum gcompusage)
{    
    UInt16 ibase = OSG_NUM_COMBINERS * 3;
    
    getVariableArgb().setValue(ainput,     ibase);
    getVariableArgb().setValue(amapping,   ibase + 1);
    getVariableArgb().setValue(acompusage, ibase + 2);
    
    getVariableBrgb().setValue(binput,     ibase);
    getVariableBrgb().setValue(bmapping,   ibase + 1);
    getVariableBrgb().setValue(bcompusage, ibase + 2);
    
    getVariableCrgb().setValue(cinput,     ibase);
    getVariableCrgb().setValue(cmapping,   ibase + 1);
    getVariableCrgb().setValue(ccompusage, ibase + 2);
    
    getVariableDrgb().setValue(dinput,     ibase);
    getVariableDrgb().setValue(dmapping,   ibase + 1);
    getVariableDrgb().setValue(dcompusage, ibase + 2);
    
    getVariableE().setValue(einput,     0);
    getVariableE().setValue(emapping,   1);
    getVariableE().setValue(ecompusage, 2);
    
    getVariableF().setValue(finput,     0);
    getVariableF().setValue(fmapping,   1);
    getVariableF().setValue(fcompusage, 2);
    
    getVariableG().setValue(ginput,     0);
    getVariableG().setValue(gmapping,   1);
    getVariableG().setValue(gcompusage, 2);    
}


void RegisterCombinersChunk::activate( DrawActionBase *action, UInt32  )
{
    Window *win = action->getWindow();
    
    if ( ! win->hasExtension( _nvRegisterCombiners ) )
        return;

    // setup register combiners
 
    // functions
 
    void (*CombinerParameterfv)(GLenum pname, GLfloat *params) = 
            (void (*)(GLenum pname, GLfloat *params))
            win->getFunction(_funcCombinerParameterfv);
 
    void (*CombinerInput)(GLenum stage, GLenum portion, GLenum variable, 
                          GLenum input, GLenum mapping, GLenum component) = 
            (void (*)(GLenum stage, GLenum portion, GLenum variable, 
                      GLenum input, GLenum mapping, GLenum component))
            win->getFunction(_funcCombinerInput);
 
    void (*CombinerOutput)(GLenum stage, GLenum portion, 
                           GLenum abOut, GLenum cdOut, GLenum sumOut, 
                           GLenum scale, GLenum bias, 
                           GLboolean abdot, GLboolean cddot, 
                           GLboolean muxSum) = 
            (void (*)(GLenum stage, GLenum portion, 
                      GLenum abOut, GLenum cdOut, GLenum sumOut, 
                      GLenum scale, GLenum bias, 
                      GLboolean abdot, GLboolean cddot, 
                      GLboolean muxSum))
            win->getFunction(_funcCombinerOutput);
 
    void (*FinalCombinerInput)(GLenum variable, GLenum input, GLenum mapping, 
                               GLenum component) = 
            (void (*)(GLenum variable, GLenum input, GLenum mapping, 
                               GLenum component))
            win->getFunction(_funcFinalCombinerInput);
    
    // constants first    
    CombinerParameterfv( GL_CONSTANT_COLOR0_NV, 
                            (GLfloat*)getColor0().getValuesRGBA() );
    CombinerParameterfv( GL_CONSTANT_COLOR1_NV, 
                            (GLfloat*)getColor1().getValuesRGBA() );
    // color sum clamp here
    
    // how many combiners do we need?
    
    Int32 ncomb;
 
    for(ncomb = OSG_NUM_COMBINERS - 1; ncomb >= 0; ncomb--)
    {
        if(getVariableArgb().getValue(ncomb * 3) != GL_NONE)
            break;
    }

    if(ncomb < 0)
    {
        // no combiner active, return
        
        glDisable(GL_REGISTER_COMBINERS_NV);
        return;
    }
    
    ncomb++;
    
    GLfloat dummy = ncomb;
    CombinerParameterfv( GL_CONSTANT_COLOR0_NV, &dummy );
    
    // setup the general combiners
 
    for(UInt16 i = 0; i < ncomb; i++)
    {
        if(getVariableArgb().getValue(i * 3) != GL_NONE)
        {
            // RGB inputs
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_A_NV,
                          getVariableArgb().getValue(i * 3),
                          getVariableArgb().getValue(i * 3 + 1),
                          getVariableArgb().getValue(i * 3 + 2) );
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_B_NV,
                          getVariableBrgb().getValue(i * 3),
                          getVariableBrgb().getValue(i * 3 + 1),
                          getVariableBrgb().getValue(i * 3 + 2) );
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_C_NV,
                          getVariableCrgb().getValue(i * 3),
                          getVariableCrgb().getValue(i * 3 + 1),
                          getVariableCrgb().getValue(i * 3 + 2) );
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_D_NV,
                          getVariableDrgb().getValue(i * 3),
                          getVariableDrgb().getValue(i * 3 + 1),
                          getVariableDrgb().getValue(i * 3 + 2) );

            // RGB output
            CombinerOutput(GL_COMBINER0_NV + i, GL_RGB, 
                                getOutputABrgb    ().getValue(i),
                                getOutputCDrgb    ().getValue(i),
                                getOutputSumrgb   ().getValue(i),
                                getScalergb       ().getValue(i),
                                getBiasrgb        ().getValue(i),
                                getDotABrgb       ().getValue(i),
                                getDotCDrgb       ().getValue(i),
                                getMuxSumrgb      ().getValue(i) );

        }
        else
        {
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_A_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_B_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_C_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 
            CombinerInput(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_D_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 

            CombinerOutput(GL_COMBINER0_NV + i, GL_RGB, 
                            GL_DISCARD_NV, GL_DISCARD_NV, GL_DISCARD_NV,
                            GL_NONE, GL_NONE,
                            GL_FALSE, GL_FALSE, GL_FALSE );   
                            
        }
        
        if(getVariableAalpha().getValue(i * 3) != GL_NONE)
        {
            // Alpha inputs
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_A_NV,
                          getVariableAalpha().getValue(i * 3),
                          getVariableAalpha().getValue(i * 3 + 1),
                          getVariableAalpha().getValue(i * 3 + 2) );
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_B_NV,
                          getVariableBalpha().getValue(i * 3),
                          getVariableBalpha().getValue(i * 3 + 1),
                          getVariableBalpha().getValue(i * 3 + 2) );
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_C_NV,
                          getVariableCalpha().getValue(i * 3),
                          getVariableCalpha().getValue(i * 3 + 1),
                          getVariableCalpha().getValue(i * 3 + 2) );
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_D_NV,
                          getVariableDalpha().getValue(i * 3),
                          getVariableDalpha().getValue(i * 3 + 1),
                          getVariableDalpha().getValue(i * 3 + 2) );

            // ALPHA output
            CombinerOutput(GL_COMBINER0_NV + i, GL_ALPHA, 
                                getOutputABalpha    ().getValue(i),
                                getOutputCDalpha    ().getValue(i),
                                getOutputSumalpha   ().getValue(i),
                                getScalealpha       ().getValue(i),
                                getBiasalpha        ().getValue(i),
                                GL_FALSE,
                                GL_FALSE,
                                getMuxSumalpha      ().getValue(i) );
            }
        else
        {
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_A_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_B_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_C_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 
            CombinerInput(GL_COMBINER0_NV + i, GL_ALPHA, GL_VARIABLE_D_NV,
                            GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 

            CombinerOutput(GL_COMBINER0_NV + i, GL_ALPHA, 
                            GL_DISCARD_NV, GL_DISCARD_NV, GL_DISCARD_NV,
                            GL_NONE, GL_NONE,
                            GL_FALSE, GL_FALSE, GL_FALSE );   
        }
    }
    glErr("RegisterCombinersChunk::general combiners setup");
 
    // setup the final combiner
     
    FinalCombinerInput(GL_VARIABLE_A_NV,
                        getVariableArgb().getValue(OSG_NUM_COMBINERS * 3),
                        getVariableArgb().getValue(OSG_NUM_COMBINERS * 3 + 1),
                        getVariableArgb().getValue(OSG_NUM_COMBINERS * 3 + 2));
    
    glErr("RegisterCombinersChunk::final combiner var a setup");
 
    FinalCombinerInput(GL_VARIABLE_B_NV,
                        getVariableBrgb().getValue(OSG_NUM_COMBINERS * 3),
                        getVariableBrgb().getValue(OSG_NUM_COMBINERS * 3 + 1),
                        getVariableBrgb().getValue(OSG_NUM_COMBINERS * 3 + 2));
 
    glErr("RegisterCombinersChunk::final combiner var b setup");
 
    FinalCombinerInput(GL_VARIABLE_C_NV,
                        getVariableCrgb().getValue(OSG_NUM_COMBINERS * 3),
                        getVariableCrgb().getValue(OSG_NUM_COMBINERS * 3 + 1),
                        getVariableCrgb().getValue(OSG_NUM_COMBINERS * 3 + 2));
 
    glErr("RegisterCombinersChunk::final combiner var c setup");
 
    FinalCombinerInput(GL_VARIABLE_D_NV,
                        getVariableDrgb().getValue(OSG_NUM_COMBINERS * 3),
                        getVariableDrgb().getValue(OSG_NUM_COMBINERS * 3 + 1),
                        getVariableDrgb().getValue(OSG_NUM_COMBINERS * 3 + 2));
 
    glErr("RegisterCombinersChunk::final combiner var d setup");
 
    FinalCombinerInput(GL_VARIABLE_E_NV,
                        getVariableE().getValue(0),
                        getVariableE().getValue(1),
                        getVariableE().getValue(2));
 
    glErr("RegisterCombinersChunk::final combiner var e setup");
 
    FinalCombinerInput(GL_VARIABLE_F_NV,
                        getVariableF().getValue(0),
                        getVariableF().getValue(1),
                        getVariableF().getValue(2));
 
    glErr("RegisterCombinersChunk::final combiner var f setup");
 
    FinalCombinerInput(GL_VARIABLE_G_NV,
                        getVariableG().getValue(0),
                        getVariableG().getValue(1),
                        getVariableG().getValue(2));
    
    glErr("RegisterCombinersChunk::final combiner setup");
    // and activate everything
    
    glEnable(GL_REGISTER_COMBINERS_NV);

    glErr("RegisterCombinersChunk::activate");
}


void RegisterCombinersChunk::changeFrom(DrawActionBase *action, 
                              StateChunk     *old   , 
                              UInt32          idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;

    old->deactivate(action, idx);
    activate(action, idx);
}

void RegisterCombinersChunk::deactivate ( DrawActionBase *, UInt32 )
{
    glDisable(GL_REGISTER_COMBINERS_NV);

    glErr("RegisterCombinersChunk::deactivate");
}

/*-------------------------- comparison -----------------------------------*/

Real32 RegisterCombinersChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

/** \brief assignment
 */

bool RegisterCombinersChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool RegisterCombinersChunk::operator == (const StateChunk &other) const
{
    RegisterCombinersChunk const *tother = dynamic_cast<RegisterCombinersChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    // TODO compare reg comb
    return false;
}

/** \brief unequal
 */

bool RegisterCombinersChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

