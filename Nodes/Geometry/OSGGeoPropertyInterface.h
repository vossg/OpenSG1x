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

template <class GeoPropertyDesc>
class OSG_SYSTEMLIB_DLLTMPLMAPPING GeoPropertyInterface :
    public GeoPropertyDesc::Inherit
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef GeoPropertyInterface<GeoPropertyDesc>       InterfaceType;

    typedef FCPtr<typename GeoPropertyDesc::InheritPtr,
                           InterfaceType              > PtrType;

    typedef typename GeoPropertyDesc::Inherit Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    virtual UInt32  getFormat    (void) = 0;
    virtual UInt32  getFormatSize(void) = 0;
    virtual UInt32  getStride    (void) = 0;
    virtual UInt32  getDimension (void) = 0;
    virtual UInt32  getSize      (void) = 0;
    virtual UInt8   *getData     (void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Generic Access                         */
    /*! \{                                                                 */

    virtual typename GeoPropertyDesc::GenericType
                    getValue( const UInt32 index ) = 0;

    virtual typename GeoPropertyDesc::GenericType
                    getValue( const UInt32 index ) const = 0;

    virtual void    getValue( typename GeoPropertyDesc::GenericType & val,
                        const UInt32 index ) = 0;

    virtual void    getValue( typename GeoPropertyDesc::GenericType & val,
                        const UInt32 index ) const = 0;

    virtual void    setValue(
                        const typename GeoPropertyDesc::GenericType & val,
                        const UInt32 index ) = 0;

    virtual void    addValue(
                        const typename GeoPropertyDesc::GenericType & val )= 0;

    virtual void    clear( void ) = 0;

    virtual void    resize(size_t newsize) = 0;

    virtual void    push_back(
                    const typename GeoPropertyDesc::GenericType & val ) = 0;

    // size clashes with another size()...
    // virtual UInt32   size( void ) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    GeoPropertyInterface() : Inherited() {}
    GeoPropertyInterface(const GeoPropertyInterface &source) :
        Inherited(source) {}

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoPropertyInterface() {}
    /*! \}                                                                 */
};

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
    
    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef Pnt3f                  GenericType;

    typedef GeoPropertyInterface<GeoPositionsPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc>::PtrType InterfacePtr;
    /*! \}                                                                 */    
};

typedef GeoPropertyInterface<GeoPositionsPropertyDesc> GeoPositionsInterface;

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
    
    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef Vec3f                  GenericType;

    typedef GeoPropertyInterface<GeoNormalsPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoNormalsPropertyDesc>::PtrType InterfacePtr;
    /*! \}                                                                 */        
};

typedef GeoPropertyInterface<GeoNormalsPropertyDesc> GeoNormalsInterface;

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
    
    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef Color3f                GenericType;

    typedef GeoPropertyInterface<GeoColorsPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoColorsPropertyDesc>::PtrType InterfacePtr;
    /*! \}                                                                 */        
};

typedef GeoPropertyInterface<GeoColorsPropertyDesc> GeoColorsInterface;

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
    
    typedef Attachment              Inherit;
    typedef AttachmentPropertyDesc  InheritDesc;
    typedef AttachmentPtr           InheritPtr;

    typedef Vec2f                   GenericType;

    typedef
        GeoPropertyInterface<GeoTexCoordsPropertyDesc>          Interface;
    typedef
        GeoPropertyInterface<GeoTexCoordsPropertyDesc>::PtrType InterfacePtr;
    /*! \}                                                                 */        
};

typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> GeoTexCoordsInterface;

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

    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef UInt32                 GenericType;

    typedef GeoPropertyInterface<GeoIndicesPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoIndicesPropertyDesc>::PtrType InterfacePtr;
    /*! \}                                                                 */        
};

typedef GeoPropertyInterface<GeoIndicesPropertyDesc> GeoIndicesInterface;

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
    
    typedef Attachment             Inherit;
    typedef AttachmentPtr          InheritPtr;
    typedef AttachmentPropertyDesc InheritDesc;

    typedef UInt8                  GenericType;

    typedef GeoPropertyInterface<GeoPTypesPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoPTypesPropertyDesc>::PtrType InterfacePtr;
    /*! \}                                                                 */        
};


typedef GeoPropertyInterface<GeoPTypesPropertyDesc> GeoPTypesInterface;

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

    typedef Attachment             Inherit;
    typedef AttachmentPtr          InheritPtr;
    typedef AttachmentPropertyDesc InheritDesc;

    typedef UInt32                 GenericType;

    typedef GeoPropertyInterface<GeoPLengthsPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoPLengthsPropertyDesc>::PtrType InterfacePtr;
    /*! \}                                                                 */        
};

typedef GeoPropertyInterface<GeoPLengthsPropertyDesc> GeoPLengthsInterface;

OSG_END_NAMESPACE


#endif /* _OSGGEOPROPERTYINTERFACES_H_ */
