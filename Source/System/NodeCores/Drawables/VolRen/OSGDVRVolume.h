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

#ifndef _OSGDVRVOLUME_H_
#define _OSGDVRVOLUME_H_
#ifdef __sgi
#pragma once
#endif

#undef OSG_INCLUDE_SOVOLUME


#include <OSGConfig.h>

#include <OSGDVRVolumeBase.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGTextureManager.h>
#include <OSGDVRClipper.h>


//! Conveniance macros - makes code much more readable

#define DVRVOLUME_PARAMETER(volume, class) \
class##Ptr::dcast(volume->findParameter(class::getClassType()))



#ifdef OSG_INCLUDE_SOVOLUME
class SoVolume;
#endif

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DVRVolume : public DVRVolumeBase
{
  private:

    typedef DVRVolumeBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setAppearance    (const DVRAppearancePtr &value);
     void setGeometry      (const DVRGeometryPtr   &value);
     void setShader        (const DVRShaderPtr     &value);
     void setRenderMaterial(const MaterialPtr      &value);
     void setTextureStorage(const ChunkMaterialPtr &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Draw                                     */

    // execute the OpenGL commands to draw the geometry	
    Action::ResultE doDraw(Action         *action);
	
    // low-level OpenGL calls, ignoring materials	
    Action::ResultE draw  (DrawActionBase *action);

    // generate draw tree
    Action::ResultE render(Action         *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Volume Parameter                              */

    AttachmentPtr findParameter(const FieldContainerType &type,
                                      UInt16              binding = 0);

    AttachmentPtr findParameter(      UInt32              groupId, 
                                      UInt16              binding = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Volume                                   */

    void          buildDrawStyleList   (      Window         *win = NULL    );

    //! Prepare the clip objects for this volume    
    void          initializeClipObjects(      DrawActionBase *action, 
                                        const Matrix          &volumeToWorld);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   TextureManager                             */

    TextureManager              &getTextureManager(void          );

    TextureManager::TextureMode  getTextureMode   (Window *window);

//!! FIXME: This methods are to be removed as soon as the node gets informed
//!!	about modified attachments of the appearance

    // updates the texture color table
    void reload(void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRVolume(void);
    DVRVolume(const DVRVolume &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRVolume(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        GL                                    */
    /*! \{                                                                 */

    // extension indices for used extensions;
    static UInt32 _extTex3D;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DVRVolumeBase;
    
    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DVRVolume &source);

    /*! \brief used to initialize class to initialize member variables -
     *         method is called by every constructor
     */
    void commonConstructor( void );

    // intersect action: ray test
    Action::ResultE intersect(Action * action);

    /*---------------------------------------------------------------------*/
    /*! \name                      Volume-Rendering                        */
    /*! \{                                                                 */

#ifdef OSG_INCLUDE_SOVOLUME
    SoVolume       *volumeImpl;
    UInt32          nextDrawStyle;
#endif
    bool            drawStyleListValid;
    TextureManager  textureManager;
    bool            shadingInitialized;

    DVRClipper      clipper;
    
    /*! \}                                                                 */

    //!! FIXME:
    friend class TextureManager;
};

typedef DVRVolume *DVRVolumeP;

OSG_END_NAMESPACE

#include <OSGDVRVolume.inl>
#include <OSGDVRVolumeBase.inl>

#define OSGDVRVOLUME_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRVOLUME_H_ */
