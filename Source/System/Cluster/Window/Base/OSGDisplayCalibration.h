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

#ifndef _OSGDISPLAYCALIBRATION_H_
#define _OSGDISPLAYCALIBRATION_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGViewport.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGComponentTransform.h>
#include <OSGMatrixCamera.h>
#include <OSGTextureGrabBackground.h>
#include <OSGTextureGrabForeground.h>
#include <OSGSolidBackground.h>
#include <OSGGeometry.h>
#include <OSGDisplayCalibrationBase.h>
#include <OSGWindow.h>
#include <OSGChunkMaterial.h>
#include <OSGFragmentProgramChunk.h>
#include <OSGRegisterCombinersChunk.h>
#include <OSGRenderAction.h>

OSG_BEGIN_NAMESPACE

/*! \brief DisplayCalibration class. See \ref 
           PageSystemDisplayCalibration for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING DisplayCalibration : public DisplayCalibrationBase
{
  private:

    typedef DisplayCalibrationBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      calibration                             */
    /*! \{                                                                 */

    virtual void calibrate(ViewportPtr port,RenderActionBase *ract);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DisplayCalibrationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DisplayCalibration(void);
    DisplayCalibration(const DisplayCalibration &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DisplayCalibration(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   helper                                     */
    /*! \{                                                                 */

    void createCMViewports(ViewportPtr port);
    void updateMatrix();
    void updateGamma();
    void updateGrid(ViewportPtr port);
    void createPincushionGrid();

    /*! \}                                                                 */

    bool                      _useFragmentProgram;
    bool                      _changed;
    bool                      _nonPowerOfTwo;
    GeometryPtr               _scalegeo;
    GeoPositions3fPtr         _positions;
    GeoTexCoords2fPtr         _texcoords;
    GeoPositions3fPtr         _positionsScale;
    GeoTexCoords2fPtr         _texcoordsScale;
    ImagePtr                  _rgammaimg;
    TextureChunkPtr           _rgammachunk;    
    ImagePtr                  _ggammaimg;
    TextureChunkPtr           _ggammachunk;    
    ImagePtr                  _bgammaimg;
    TextureChunkPtr           _bgammachunk;    
    ImagePtr                  _argammaimg;
    TextureChunkPtr           _argammachunk;    
    ImagePtr                  _gbgammaimg;
    TextureChunkPtr           _gbgammachunk;    
    FragmentProgramChunkPtr   _fragProgram;
    RegisterCombinersChunkPtr _regCombiner;

    ViewportPtr               _cmPort;
    ViewportPtr               _dsPort;
    ViewportPtr               _dsPort2;
    NodePtr                   _cmRoot;
    NodePtr                   _dsRoot;
    NodePtr                   _ds2Root;
    MatrixCameraPtr           _cam;
    TextureGrabBackgroundPtr  _cmBack;
    TextureGrabBackgroundPtr  _dsBack;
    SolidBackgroundPtr        _ds2Back;

    UInt32                    _vpLeft;
    UInt32                    _vpRight;
    UInt32                    _vpBottom;
    UInt32                    _vpTop;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DisplayCalibrationBase;
    
    static void initMethod(void);
    
    // prohibit default functions (move to 'public' if you need one)
    
    void operator =(const DisplayCalibration &source);
};

typedef DisplayCalibration *DisplayCalibrationP;

OSG_END_NAMESPACE

#include <OSGDisplayCalibrationBase.inl>
#include <OSGDisplayCalibration.inl>

#define OSGDISPLAYCALIBRATION_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.21 2003/07/11 18:39:08 dirk Exp $"

#endif /* _OSGDISPLAYCALIBRATION_H_ */
