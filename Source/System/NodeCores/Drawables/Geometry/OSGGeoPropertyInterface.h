/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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


#ifndef _OSGGEOPROPERTYINTERFACES_H_
#define _OSGGEOPROPERTYINTERFACES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGSystemDef.h>
#include <OSGMFVecTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGAttachment.h>
#include <OSGAttachmentFieldDataType.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GeometryLib
 *  \brief GeoPropertyInterface defines the interface used by the geometry to 
 *  access its attributes. It's an abstract class and not to be instantiated.
 *  Properties are one implementation of this interface,
 *  but not necessarily the only one. In fact, the main purpose of the 
 *  interface layer is the ability to be able to create simplified geometry
 *  nodes that don't need the properties' flexibility and can't stand the
 *  overhead.
 */

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE

class AbstractGeoPropertyInterface
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    virtual UInt32  getFormat    (void) const = 0;
    virtual UInt32  getFormatSize(void) const = 0;
    virtual UInt32  getStride    (void) const = 0;
    virtual UInt32  getDimension (void) const = 0;
    virtual UInt32  getSize      (void) const = 0;
    virtual UInt32  size         (void) const = 0;
    virtual UInt8  *getData      (void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Generic Access                         */
    /*! \{                                                                 */

    virtual void        clear    (      void               )       = 0;
    virtual void        resize   (      size_t      newsize)       = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AbstractGeoPropertyInterface(void);
    AbstractGeoPropertyInterface(const AbstractGeoPropertyInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractGeoPropertyInterface(void);

    /*! \}                                                                 */
};

template <class GeoPropertyDesc>
class GeoPropertyInterface : public AbstractGeoPropertyInterface
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef          GeoPropertyInterface<GeoPropertyDesc> InterfaceType;

    typedef typename GeoPropertyDesc::GenericType          GenericType;

    typedef          AbstractGeoPropertyInterface          Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                       Generic Access                         */
    /*! \{                                                                 */

    virtual GenericType getValue (const UInt32       index )       = 0;

    virtual GenericType getValue (const UInt32       index ) const = 0;

    virtual void        getValue (      GenericType &val,
                                  const UInt32       index )       = 0;

    virtual void        getValue (      GenericType &val,
                                  const UInt32       index ) const = 0;


    virtual void        setValue (const GenericType &val,
                                  const UInt32       index )       = 0;

    virtual void        addValue (const GenericType &val   )       = 0;


    virtual void        push_back(const GenericType &val   )       = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    GeoPropertyInterface(void);
    GeoPropertyInterface(const GeoPropertyInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoPropertyInterface(void);

    /*! \}                                                                 */
};
#endif

struct AttachmentPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const char *getTypeName (void)  { return "Attachment"; }

    /*! \}                                                                 */ 
};

struct GeoPositionsPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions";         }

    static const Char8 *getGroupName(void) { return "GeoPositions";         }
    static const Char8 *getClassName(void) { return "GeoPositionsProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
    
    typedef Attachment             Inherited;
    typedef AttachmentPtr          InheritedPtr;

    typedef AttachmentPropertyDesc InheritedDesc;

    typedef Pnt3f                  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */ 
};

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
typedef GeoPositionsPropertyDesc::Interface GeoPositionsInterface;
#endif

struct GeoNormalsPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoNormals";         }
    static const Char8 *getGroupName(void) { return "GeoNormals";         }
    static const Char8 *getClassName(void) { return "GeoNormalsProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
    
    typedef Attachment             Inherited;
    typedef AttachmentPtr          InheritedPtr;

    typedef AttachmentPropertyDesc InheritedDesc;

    typedef Vec3f                  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoNormalsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
typedef GeoNormalsPropertyDesc::Interface GeoNormalsInterface;
#endif

struct GeoColorsPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoColors";         }
    static const Char8 *getGroupName(void) { return "GeoColors";         }
    static const Char8 *getClassName(void) { return "GeoColorsProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
    
    typedef Attachment             Inherited;
    typedef AttachmentPtr          InheritedPtr;

    typedef AttachmentPropertyDesc InheritedDesc;

    typedef Color3f                GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoColorsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */ 
};

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
typedef GeoColorsPropertyDesc::Interface GeoColorsInterface;
#endif

struct GeoTexCoordsPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoTexCoords";         }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";         }
    static const Char8 *getClassName(void) { return "GeoTexCoordsProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
    
    typedef Attachment              Inherited;
    typedef AttachmentPtr           InheritedPtr;

    typedef AttachmentPropertyDesc  InheritedDesc;

    typedef Vec2f                   GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
typedef GeoTexCoordsPropertyDesc::Interface GeoTexCoordsInterface;
#endif

struct GeoIndicesPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoIndices";         }
    static const Char8 *getGroupName(void) { return "GeoIndices";         }
    static const Char8 *getClassName(void) { return "GeoIndicesProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */

    typedef Attachment             Inherited;
    typedef AttachmentPtr          InheritedPtr;

    typedef AttachmentPropertyDesc InheritedDesc;

    typedef UInt32                 GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoIndicesPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
typedef GeoIndicesPropertyDesc::Interface GeoIndicesInterface;
#endif

struct GeoPTypesPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPTypes"; }
    static const Char8 *getGroupName(void) { return "GeoPTypes"; }
    static const Char8 *getClassName(void) { return "GeoPTypesProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
    
    typedef Attachment             Inherited;
    typedef AttachmentPropertyDesc InheritedDesc;

    typedef AttachmentPtr          InheritedPtr;

    typedef UInt8                  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPTypesPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};


#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
typedef GeoPTypesPropertyDesc::Interface GeoPTypesInterface;
#endif

struct GeoPLengthsPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPLengths";         }
    static const Char8 *getClassName(void) { return "GeoPLengthsProperty"; }
    static const Char8 *getGroupName(void) { return "GeoPLengths";         }

    static InitContainerF getInitMethod(void) { return NULL; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */

    typedef Attachment             Inherited;
    typedef AttachmentPtr          InheritedPtr;

    typedef AttachmentPropertyDesc InheritedDesc;

    typedef UInt32                 GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPLengthsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
typedef GeoPLengthsPropertyDesc::Interface GeoPLengthsInterface;
#endif

OSG_END_NAMESPACE

#include <OSGGeoPropertyInterface.inl>

#endif /* _OSGGEOPROPERTYINTERFACES_H_ */














