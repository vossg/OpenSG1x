/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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


#ifndef _OSGGEOPROPERTY_H_
#define _OSGGEOPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <GL/gl.h>

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
 *  \brief GeoProperty is a specialized form of Attachment, used to 
 *  define the properties of the geometry node. This is the abstract base 
 *  class for all 
 *  properties.
 */

template <class GeoPropertyDesc>
class OSG_DLLEXPORT AbstractGeoProperty : public GeoPropertyDesc::Inherit
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef AbstractGeoProperty<GeoPropertyDesc>        PropertyType;

    typedef FCPtr<typename GeoPropertyDesc::InheritPtr, 
                           PropertyType               > PtrType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const PtrType NullPtr;

    static const char *getClassname(void) 
        { return GeoPropertyDesc::getClassName(); }

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_ABSTR_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*----------------------------- access ----------------------------------*/
	
	virtual UInt32	getFormat    (void) = 0;
    // number of bytes per format element
	virtual UInt32	getFormatSize(void) = 0;	
	virtual UInt32	getStride    (void) = 0;
	virtual UInt32	getDimension (void) = 0;
	virtual UInt32	getSize      (void) = 0;
	virtual UInt8	*getData     (void) = 0;
	
    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    AbstractGeoProperty(void);
    AbstractGeoProperty(const AbstractGeoProperty &source);
    virtual ~AbstractGeoProperty(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename GeoPropertyDesc::Inherit     Inherited;
    typedef typename GeoPropertyDesc::InheritDesc InheritDesc;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

template <class GeoPropertyDesc>
class OSG_DLLEXPORT GeoProperty : public GeoPropertyDesc::Inherit
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(GeoPropDataField)
    
    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef GeoProperty<GeoPropertyDesc>                PropertyType;

    typedef FCPtr<typename GeoPropertyDesc::InheritPtr, 
                           PropertyType               > PtrType;

	typedef typename GeoPropertyDesc::FieldType FieldType;
	
    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static const PtrType NullPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return GeoPropertyDesc::getClassName(); }

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*----------------------------- access ----------------------------------*/

          typename GeoPropertyDesc::FieldType *getFieldPtr(void);

          typename GeoPropertyDesc::FieldType &getField(void);
    const typename GeoPropertyDesc::FieldType &getField(void) const;
	
	
	virtual UInt32	getFormat    (void);
    // number of bytes per format element
	virtual UInt32	getFormatSize(void);	
	virtual UInt32	getStride    (void);
	virtual UInt32	getDimension (void);
    // number of elements
	virtual UInt32	getSize      (void);		
	virtual UInt8	*getData     (void);

	typename GeoPropertyDesc::FieldType& operator->() { return _field; }

    /*------------------------- assignment ----------------------------------*/

    GeoProperty &operator =(const GeoProperty &source);

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename GeoPropertyDesc::InheritDesc InheritDesc;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    typename GeoPropertyDesc::FieldType _field;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    GeoProperty(void);
    GeoProperty(const GeoProperty &source);
    virtual ~GeoProperty(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename GeoPropertyDesc::Inherit Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static FieldDescription   _desc[];

	static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

// For the properties not group together like type or length

struct OSG_DLLEXPORT AttachmentPropertyDesc
{
	static const char *getTypeName (void)  { return "Attachment"; }
};


// Position

struct OSG_DLLEXPORT GeoPositionPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoPosition";         }

	static const Char8 *getGroupName(void) { return "GeoPosition";         }
	static const Char8 *getClassName(void) { return "GeoPositionProperty"; }

	static InitContainerF getInitMethod(void) { return NULL; }

	typedef Attachment             Inherit;
	typedef AttachmentPropertyDesc InheritDesc;
	typedef AttachmentPtr          InheritPtr;
};

typedef AbstractGeoProperty<GeoPositionPropertyDesc> GeoPosition;

typedef GeoPosition::PtrType GeoPositionPtr;


template <>
struct OSG_DLLEXPORT FieldDataTraits<GeoPositionPtr> : public Traits
{
    enum                           { StringConvertable = 0x00   };

    static Char8 *getSName (void)  { return "SFGeoPositionPtr"; }
    static Char8 *getMName (void)  { return "MFGeoPositionPtr"; }

//  static String getDefault(void) { return OSGString();        }
};

typedef SField<GeoPositionPtr> SFGeoPositionPtr;


// Position 3f

struct OSG_DLLEXPORT GeoPosition3fPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoPosition3f";         }
	static const Char8 *getClassName(void) { return "GeoPosition3fProperty"; }
	static const Char8 *getFieldName(void) { return "positions";             }
	static const Char8 *getGroupName(void) { return "GeoPosition";           }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void)  { return GL_FLOAT;        }
	static UInt32 getFormatSize(void)  { return sizeof(GLfloat); }
	static UInt32 getDimension (void)  { return 3;               }
	static UInt32 getStride    (void)  { return 0;               }

	typedef GeoPosition             Inherit;
	typedef GeoPositionPtr          InheritPtr;
    typedef GeoPositionPropertyDesc InheritDesc;
	typedef MFPnt3f                 FieldType;
};

typedef GeoProperty<GeoPosition3fPropertyDesc> GeoPosition3f;

typedef GeoPosition3f::PtrType GeoPosition3fPtr;


// Normal

struct OSG_DLLEXPORT GeoNormalPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoNormal";         }
	static const Char8 *getGroupName(void) { return "GeoNormal";         }
	static const Char8 *getClassName(void) { return "GeoNormalProperty"; }

	static InitContainerF getInitMethod(void) { return NULL; }

	typedef Attachment             Inherit;
	typedef AttachmentPropertyDesc InheritDesc;
	typedef AttachmentPtr          InheritPtr;
};

typedef AbstractGeoProperty<GeoNormalPropertyDesc> GeoNormal;

typedef GeoNormal::PtrType GeoNormalPtr;


template <>
struct OSG_DLLEXPORT FieldDataTraits<GeoNormalPtr> : public Traits
{
    enum                            { StringConvertable = 0x00 };

    static Char8  *getSName  (void) { return "SFGeoNormalPtr"; }
    static Char8  *getMName  (void) { return "MFGeoNormalPtr"; }

//  static String  getDefault(void) { return OSGString();      }
};

typedef SField<GeoNormalPtr> SFGeoNormalPtr;


// Normal 3f

struct OSG_DLLEXPORT GeoNormal3fPropertyDesc
{
	static const Char8 *getTypeName  (void) { return "GeoNormal3f";         }
	static const Char8 *getClassName (void) { return "GeoNormal3fProperty"; }
	static const Char8 *getFieldName (void) { return "Normals";             }
	static const Char8 *getGroupName (void) { return "GeoNormal";           }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void) { return GL_FLOAT;        }
	static UInt32 getFormatSize(void) { return sizeof(GLfloat); }
	static UInt32 getDimension (void) { return 3;               }
	static UInt32 getStride    (void) { return 0;               }

	typedef GeoNormal             Inherit;
	typedef GeoNormalPtr          InheritPtr;
    typedef GeoNormalPropertyDesc InheritDesc;
	typedef MFVec3f               FieldType;
};

typedef GeoProperty<GeoNormal3fPropertyDesc> GeoNormal3f;

typedef GeoNormal3f::PtrType GeoNormal3fPtr;


// Color

struct OSG_DLLEXPORT GeoColorPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoColor";         }
	static const Char8 *getGroupName(void) { return "GeoColor";         }
	static const Char8 *getClassName(void) { return "GeoColorProperty"; }

	static InitContainerF getInitMethod(void) { return NULL; }

	typedef Attachment             Inherit;
	typedef AttachmentPropertyDesc InheritDesc;
	typedef AttachmentPtr          InheritPtr;
};

typedef AbstractGeoProperty<GeoColorPropertyDesc> GeoColor;

typedef GeoColor::PtrType GeoColorPtr;


template <>
struct OSG_DLLEXPORT FieldDataTraits<GeoColorPtr> : public Traits
{
    enum                            { StringConvertable = 0x00   };

    static Char8  *getSName  (void) { return "SFGeoColorPtr";    }
    static Char8  *getMName  (void) { return "MFGeoColorPtr";    }
//  static String  getDefault(void) { return String();           }
};

typedef SField<GeoColorPtr> SFGeoColorPtr;


// Color 3f

struct OSG_DLLEXPORT GeoColor3fPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoColor3f";         }
	static const Char8 *getClassName(void) { return "GeoColor3fProperty"; }
	static const Char8 *getFieldName(void) { return "Colors";             }
	static const Char8 *getGroupName(void) { return "GeoColor";           }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void)  { return GL_FLOAT;        }
	static UInt32 getFormatSize(void)  { return sizeof(GLfloat); }
	static UInt32 getDimension (void)  { return 3;               }
	static UInt32 getStride    (void)  { return 0;               }

	typedef GeoColor             Inherit;
	typedef GeoColorPtr          InheritPtr;
    typedef GeoColorPropertyDesc InheritDesc;
	typedef MFVec3f              FieldType;
};

typedef GeoProperty<GeoColor3fPropertyDesc> GeoColor3f;

typedef GeoColor3f::PtrType GeoColor3fPtr;


// Color 4ub


struct OSG_DLLEXPORT GeoColor4ubPropertyDesc
{
	static const Char8 *getTypeName  (void) { return "GeoColor4ub";         }
	static const Char8 *getClassName (void) { return "GeoColor4ubProperty"; }
	static const Char8 *getFieldName (void) { return "Colors";              }
	static const Char8 *getGroupName (void) { return "GeoColor";            }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void)   { return GL_UNSIGNED_BYTE; }
	static UInt32 getFormatSize(void)   { return sizeof(GLubyte);  }
	static UInt32 getDimension (void)   { return 4;                }
	static UInt32 getStride    (void)   { return 0;                }

	typedef GeoColor             Inherit;
	typedef GeoColorPtr          InheritPtr;
    typedef GeoColorPropertyDesc InheritDesc;
	typedef MFVec4ub             FieldType;
};

typedef GeoProperty<GeoColor4ubPropertyDesc> GeoColor4ub;

typedef GeoColor4ub::PtrType GeoColor4ubPtr;


// Index

struct OSG_DLLEXPORT GeoIndexPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoIndex";         }
	static const Char8 *getGroupName(void) { return "GeoIndex";         }
	static const Char8 *getClassName(void) { return "GeoIndexProperty"; }

	static InitContainerF getInitMethod(void) { return NULL; }

	typedef Attachment             Inherit;
	typedef AttachmentPropertyDesc InheritDesc;
	typedef AttachmentPtr          InheritPtr;
};

typedef AbstractGeoProperty<GeoIndexPropertyDesc> GeoIndex;

typedef GeoIndex::PtrType GeoIndexPtr;


template <>
struct OSG_DLLEXPORT FieldDataTraits<GeoIndexPtr> : public Traits
{
    enum                            { StringConvertable = 0x00 };

    static Char8  *getSName  (void) { return "SFGeoIndexPtr";  }
    static Char8  *getMName  (void) { return "MFGeoIndexPtr";  }
//  static String  getDefault(void) { return String();         }
};

typedef SField<GeoIndexPtr> SFGeoIndexPtr;


// Index uint32

struct OSG_DLLEXPORT GeoIndexUI32PropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoIndexUI32";         }
	static const Char8 *getClassName(void) { return "GeoIndexUI32Property"; }
	static const Char8 *getFieldName(void) { return "Indices";              }
	static const Char8 *getGroupName(void) { return "GeoIndex";             }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void) { return GL_UNSIGNED_INT; }
	static UInt32 getFormatSize(void) { return sizeof(GLuint);  }
	static UInt32 getDimension (void) { return 1;               }
	static UInt32 getStride    (void) { return 0;               }

	typedef GeoIndex             Inherit;
	typedef GeoIndexPtr          InheritPtr;
    typedef GeoIndexPropertyDesc InheritDesc;
	typedef MFUInt32             FieldType;
};

typedef GeoProperty<GeoIndexUI32PropertyDesc> GeoIndexUI32;

typedef GeoIndexUI32::PtrType GeoIndexUI32Ptr;


// Primitive Type

// just one kind, to cut down the number of pumps needed
// screwed up architectures might have a problem with uint8, maybe we'll
// have to expand it later 


// PType

struct OSG_DLLEXPORT GeoPTypePropertyDesc
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
};

typedef GeoProperty<GeoPTypePropertyDesc> GeoPType;

typedef GeoPType::PtrType GeoPTypePtr;


template <>
struct OSG_DLLEXPORT FieldDataTraits<GeoPTypePtr> : public Traits
{
    enum                            { StringConvertable = 0x00 };

    static Char8  *getSName  (void) { return "SFGeoPTypePtr";  }
    static Char8  *getMName  (void) { return "MFGeoPTypePtr";  }

//  static String  getDefault(void) { return String();         }
};

typedef SField<GeoPTypePtr> SFGeoPTypePtr;


// Primitive Lengths

// just one kind, to cut down the number of pumps needed
// screwed up architectures might have a problem with uint8, maybe we'll
// have to expand it later 


struct OSG_DLLEXPORT GeoPLengthPropertyDesc
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
};

typedef GeoProperty<GeoPLengthPropertyDesc> GeoPLength;

typedef GeoPLength::PtrType GeoPLengthPtr;


template <>
struct OSG_DLLEXPORT FieldDataTraits<GeoPLengthPtr> : public Traits
{
    enum                            { StringConvertable = 0x00  };

    static char   *getSName  (void) { return "SFGeoPLengthPtr"; }
    static char   *getMName  (void) { return "MFGeoPLengthPtr"; }
//  static String  getDefault(void) { return String();          }
};

typedef SField<GeoPLengthPtr> SFGeoPLengthPtr;

OSG_END_NAMESPACE

#include <OSGGeoProperty.inl>

#endif /* _OSGGEOPROPERTY_H_ */
