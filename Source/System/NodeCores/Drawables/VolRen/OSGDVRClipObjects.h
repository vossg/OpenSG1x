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

#ifndef _OSGDVRCLIPOBJECTS_H_
#define _OSGDVRCLIPOBJECTS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGPlane.h>

#include <OSGDVRClipObjectsBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DVRClipObjects : public DVRClipObjectsBase
{
  private:

    typedef DVRClipObjectsBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Constants                               */
    /*! \{                                                                 */

    enum ClipMode 
    {
        Off          = 0, 
        Intersection = 1, 
        Difference   = 2
    }; 

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
    /*---------------------------------------------------------------------*/
    /*! \name                     Info                                     */
    /*! \{                                                                 */

    //! Returns the number of clip objects set
    UInt32 count(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Objects                                    */
    /*! \{                                                                 */
  
    //! Get the ith object
    DVRClipGeometryPtr get   (UInt32             i  );

    //! Add a clip object
    void               add   (DVRClipGeometryPtr obj);

    //! Remove a clip object
    void               remove(DVRClipGeometryPtr obj);

    //! Remove the i-th clip object
    void               remove(UInt32             i  );
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Clipping                                 */
    /*! \{                                                                 */

    //! Prepare the clip objects for clipping a volume's slices
    void initialize(const Matrix &volumeToWorld, 
                    const Plane  &referencePlane);

    //! Prepare the clip objects for clipping a volume's slices
    // deprecated -> remove
    void initialize(const Matrix &volumeToWorld);

    //! Set the reference plane used in clipping
    // deprecated -> remove
    void setReferencePlane(const Plane &referencePlane);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DVRClipObjectsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRClipObjects(void);
    DVRClipObjects(const DVRClipObjects &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRClipObjects(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DVRClipObjectsBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DVRClipObjects &source);
};

typedef DVRClipObjects *DVRClipObjectsP;

OSG_END_NAMESPACE

#include <OSGDVRClipObjectsBase.inl>
#include <OSGDVRClipObjects.inl>

#define OSGDVRCLIPOBJECTS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRCLIPOBJECTS_H_ */
