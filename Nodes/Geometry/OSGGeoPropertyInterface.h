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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGMFVecTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGAttachment.h>


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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
  public:

    typedef GeoPropertyInterface<GeoPropertyDesc>       InterfaceType;

    typedef FCPtr<typename GeoPropertyDesc::InheritPtr, 
                           InterfaceType              > PtrType;

    typedef typename GeoPropertyDesc::Inherit Inherited;
   
    virtual UInt32  getFormat    (void) = 0;
    // number of bytes per format element
    virtual UInt32  getFormatSize(void) = 0;    
    virtual UInt32  getStride    (void) = 0;
    virtual UInt32  getDimension (void) = 0;
    virtual UInt32  getSize      (void) = 0;
    virtual UInt8   *getData     (void) = 0;
    
    // generic access to make using different types easier
    // mimics the MField interface as far as possible

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

    // insert() and erase() should go here
    // it's just not clear how to handle iterators in a generic way
    // what about find()? Probably not very useful in this context
    
    virtual void    clear( void ) = 0;
    

    virtual void    resize(size_t newsize) = 0;
    
    virtual void    push_back( 
                    const typename GeoPropertyDesc::GenericType & val ) = 0;
    
    // size clashes with another size()...
    // virtual UInt32   size( void ) const;


    // even though this is just an interface class, they need to be accessible?!?
    
    GeoPropertyInterface() : Inherited() {}
    GeoPropertyInterface(const GeoPropertyInterface &source) :
        Inherited(source) {}
    virtual ~GeoPropertyInterface() {}

   protected:
   
   private:
};

// For the properties not grouped together like type or length

struct AttachmentPropertyDesc
{
    static const char *getTypeName (void)  { return "Attachment"; }
};

// interfaces for the different properties.

// Position

struct GeoPositionPropertyDesc
{
    static const Char8 *getTypeName (void) { return "GeoPosition";         }

    static const Char8 *getGroupName(void) { return "GeoPosition";         }
    static const Char8 *getClassName(void) { return "GeoPositionProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef Pnt3f                  GenericType;
 
    typedef GeoPropertyInterface<GeoPositionPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoPositionPropertyDesc>::PtrType InterfacePtr;
};

typedef GeoPropertyInterface<GeoPositionPropertyDesc> GeoPositionInterface;


// Normal

struct GeoNormalPropertyDesc
{
    static const Char8 *getTypeName (void) { return "GeoNormal";         }
    static const Char8 *getGroupName(void) { return "GeoNormal";         }
    static const Char8 *getClassName(void) { return "GeoNormalProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef Vec3f                  GenericType;
 
    typedef GeoPropertyInterface<GeoNormalPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoNormalPropertyDesc>::PtrType InterfacePtr;
};

typedef GeoPropertyInterface<GeoNormalPropertyDesc> GeoNormalInterface;


// Color

struct GeoColorPropertyDesc
{
    static const Char8 *getTypeName (void) { return "GeoColor";         }
    static const Char8 *getGroupName(void) { return "GeoColor";         }
    static const Char8 *getClassName(void) { return "GeoColorProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef Color3f                GenericType;
 
    typedef GeoPropertyInterface<GeoColorPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoColorPropertyDesc>::PtrType InterfacePtr;
};

typedef GeoPropertyInterface<GeoColorPropertyDesc> GeoColorInterface;


// TexCoords

struct GeoTexCoordsPropertyDesc
{
    static const Char8 *getTypeName (void) { return "GeoTexCoords";         }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";         }
    static const Char8 *getClassName(void) { return "GeoTexCoordsProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    typedef Attachment              Inherit;
    typedef AttachmentPropertyDesc  InheritDesc;
    typedef AttachmentPtr           InheritPtr;

    typedef Vec2f                   GenericType;
 
    typedef 
        GeoPropertyInterface<GeoTexCoordsPropertyDesc>          Interface;
    typedef 
        GeoPropertyInterface<GeoTexCoordsPropertyDesc>::PtrType InterfacePtr;
};

typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> GeoTexCoordsInterface;


// Index

struct GeoIndexPropertyDesc
{
    static const Char8 *getTypeName (void) { return "GeoIndex";         }
    static const Char8 *getGroupName(void) { return "GeoIndex";         }
    static const Char8 *getClassName(void) { return "GeoIndexProperty"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    typedef Attachment             Inherit;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef AttachmentPtr          InheritPtr;

    typedef UInt32                 GenericType;
 
    typedef GeoPropertyInterface<GeoIndexPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoIndexPropertyDesc>::PtrType InterfacePtr;
};

typedef GeoPropertyInterface<GeoIndexPropertyDesc> GeoIndexInterface;


// Primitive Type

struct GeoPTypePropertyDesc
{
    static const Char8 *getTypeName (void) { return "GeoPType"; }
    static const Char8 *getClassName(void) { return "GeoPTypeProperty"; }
    static const Char8 *getFieldName(void) { return "Types"; }
    static const Char8 *getGroupName(void) { return "GeoPType"; }

    static InitContainerF getInitMethod(void) { return NULL; }

    static UInt32 getFormat    (void) { return GL_UNSIGNED_BYTE;  }
    static UInt32 getFormatSize(void) { return sizeof(GLubyte);   }
    static UInt32 getDimension (void) { return 1;                 }
    static UInt32 getStride    (void) { return 0;                 }

    typedef Attachment             Inherit;
    typedef AttachmentPtr          InheritPtr;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef MFUInt8                FieldType;

    typedef UInt8                  GenericType;
 
    typedef GeoPropertyInterface<GeoPTypePropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoPTypePropertyDesc>::PtrType InterfacePtr;
};


typedef GeoPropertyInterface<GeoPTypePropertyDesc> GeoPTypeInterface;

// Primitive Lengths

struct GeoPLengthPropertyDesc
{
    static const Char8 *getTypeName (void) { return "GeoPLength";         }
    static const Char8 *getClassName(void) { return "GeoPLengthProperty"; }
    static const Char8 *getFieldName(void) { return "Lengths";            }
    static const Char8 *getGroupName(void) { return "GeoPLength";         }

    static InitContainerF getInitMethod(void) { return NULL; }

    static UInt32 getFormat    (void) { return GL_UNSIGNED_INT; }
    static UInt32 getFormatSize(void) { return sizeof(GLuint);  }
    static UInt32 getDimension (void) { return 1;               }
    static UInt32 getStride    (void) { return 0;               }

    typedef Attachment             Inherit;
    typedef AttachmentPtr          InheritPtr;
    typedef AttachmentPropertyDesc InheritDesc;
    typedef MFUInt32               FieldType;

    typedef UInt32                 GenericType;
 
    typedef GeoPropertyInterface<GeoPLengthPropertyDesc>          Interface;
    typedef GeoPropertyInterface<GeoPLengthPropertyDesc>::PtrType InterfacePtr;
};

typedef GeoPropertyInterface<GeoPLengthPropertyDesc> GeoPLengthInterface;

OSG_END_NAMESPACE


#endif /* _OSGGEOPROPERTYINTERFACES_H_ */
