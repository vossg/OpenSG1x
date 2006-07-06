/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \brief GeoPropertyArrayInterface defines the generic interface used by 
    the geometry to access its attributes. 
 
    GeoPropertyArrayInterface defines the generic interface used by the
    geometry to  access its attributes. This interface is not templated and
    can be used for all kinds of properties. To allow that this interface is
    typeless and closely related to OpenGL's Vertex Arrays. 

    It's an abstract class and not to be instantiated. osg::GeoProperty is one
    implementation of this interface, but not necessarily the only one. In
    fact, the main purpose of the interface layer is the ability to be able
    to create simplified geometry nodes that don't need the properties'
    flexibility and can't stand the overhead.
 */

class GeoPropertyArrayInterface
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

    virtual void  clear  (void          ) = 0;
    virtual void  resize (size_t newsize) = 0;
    virtual void  shrink (void          ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    GeoPropertyArrayInterface(void);
    GeoPropertyArrayInterface(const GeoPropertyArrayInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoPropertyArrayInterface(void);

    /*! \}                                                                 */
};


/*! \ingroup GrpSystemDrawablesGeometryProperties
    \brief GeoPropertyInterface defines the typed generic interface used by 
    the geometry to access its attributes. 
 
    GeoPropertyInterface defines the typed generic interface used by the
    geometry to  access its attributes. This interface is templated and
    specific for every different kind of osg::GeoProperty. It includes the
    generic value access and thus is somewhat more heavy-weight than the 
    osg::GeoPropertyArrayInterface.
*/
template <class GeoPropertyDesc>
class GeoPropertyInterface : public GeoPropertyArrayInterface
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef          GeoPropertyInterface<GeoPropertyDesc> InterfaceType;

    typedef typename GeoPropertyDesc::GenericType          GenericType;

    typedef          GeoPropertyArrayInterface          Inherited;

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


/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Dummy base class for the abstract instances of osg::GeoProperty. 
*/
struct AttachmentPropertyDesc
{
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */
    
    static const char *getTypeName (void)  { return "Attachment"; }

    /*! \}                                                                 */ 
};

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoProperty traits. These are used to
    parameterize the actual osg::GeoProperty types. 
*/
struct GeoPropertyDesc
{
};

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoPositionsProperty traits. See \ref 
    GrpSystemDrawablesGeometryProperties for a description.
*/
struct GeoPositionsPropertyDesc : public GeoPropertyDesc
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

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoNormalsProperty traits. See \ref 
    GrpSystemDrawablesGeometryProperties for a description.
*/
struct GeoNormalsPropertyDesc : public GeoPropertyDesc
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

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoColorsProperty traits. See \ref 
    GrpSystemDrawablesGeometryProperties for a description.
*/
struct GeoColorsPropertyDesc : public GeoPropertyDesc
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

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoTexCoordsProperty traits. See \ref 
    GrpSystemDrawablesGeometryProperties for a description.
*/
struct GeoTexCoordsPropertyDesc : public GeoPropertyDesc
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

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoIndicesProperty traits. See \ref 
    GrpSystemDrawablesGeometryProperties for a description.
*/
struct GeoIndicesPropertyDesc : public GeoPropertyDesc
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

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoPTypesProperty traits. See \ref 
    GrpSystemDrawablesGeometryProperties for a description.
*/
struct GeoPTypesPropertyDesc : public GeoPropertyDesc
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

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    Abstract base class for all GeoPLengthsProperty traits. See \ref 
    GrpSystemDrawablesGeometryProperties for a description.
*/
struct GeoPLengthsPropertyDesc : public GeoPropertyDesc
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














