/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
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
 *  \brief OSGGeoProperty is a specialized form of OSGAttachment, used to 
 *  define the properties of the geometry node. This is the abstract base 
 *  class for all 
 *  properties.
 */

template <class GeoPropertyDesc>
class OSGAbstractGeoProperty : public GeoPropertyDesc::Inherit
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

    typedef OSGAbstractGeoProperty<GeoPropertyDesc>        OSGPropertyType;

    typedef OSGFCPtr<typename GeoPropertyDesc::InheritPtr, 
                              OSGPropertyType            > OSGPtrType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const OSGPtrType OSGNullPtr;

    static const char *getClassname(void) 
        { return GeoPropertyDesc::getClassName(); }

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_ABSTR_FIELD_CONTAINER_TMPL_DECL(OSGPtrType)

    virtual ~OSGAbstractGeoProperty(void); 

    /*----------------------------- access ----------------------------------*/
	
	virtual OSGUInt32	getFormat    (void) = 0;
    // number of bytes per format element
	virtual OSGUInt32	getFormatSize(void) = 0;	
	virtual OSGUInt32	getStride    (void) = 0;
	virtual OSGUInt32	getDimension (void) = 0;
	virtual OSGUInt32	getSize      (void) = 0;
	virtual OSGUInt8	*getData     (void) = 0;
	
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

    friend class OSGFieldContainer;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGAbstractGeoProperty(void);
    OSGAbstractGeoProperty(const OSGAbstractGeoProperty &source);

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

	static OSGFieldContainerType _type;

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
class OSGGeoProperty : public GeoPropertyDesc::Inherit
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGGeoPropDataField)
    
    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGGeoProperty<GeoPropertyDesc>                OSGPropertyType;

    typedef OSGFCPtr<typename GeoPropertyDesc::InheritPtr, 
                              OSGPropertyType            > OSGPtrType;

	typedef typename GeoPropertyDesc::FieldType OSGFieldType;
	
    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static const OSGPtrType OSGNullPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return GeoPropertyDesc::getClassName(); }

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_FIELD_CONTAINER_TMPL_DECL(OSGPtrType)

    virtual ~OSGGeoProperty(void); 

    /*----------------------------- access ----------------------------------*/

          typename GeoPropertyDesc::FieldType *getFieldPtr(void);

          typename GeoPropertyDesc::FieldType &getField(void);
    const typename GeoPropertyDesc::FieldType &getField(void) const;
	
	
	virtual OSGUInt32	getFormat    (void);
    // number of bytes per format element
	virtual OSGUInt32	getFormatSize(void);	
	virtual OSGUInt32	getStride    (void);
	virtual OSGUInt32	getDimension (void);
    // number of elements
	virtual OSGUInt32	getSize      (void);		
	virtual OSGUInt8	*getData     (void);

	typename GeoPropertyDesc::FieldType& operator->() { return _field; }

    /*------------------------- assignment ----------------------------------*/

    OSGGeoProperty &operator =(const OSGGeoProperty &source);

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename GeoPropertyDesc::FieldType   FieldType;
    typedef typename GeoPropertyDesc::InheritDesc InheritDesc;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    friend class OSGFieldContainer;

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

    OSGGeoProperty(void);
    OSGGeoProperty(const OSGGeoProperty &source);

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

	static OSGFieldDescription   _desc[];

	static OSGFieldContainerType _type;

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

struct OSGAttachmentPropertyDesc
{
	static const char *getTypeName (void)  { return "Attachment"; }
};


// Position

struct OSGGeoPositionPropertyDesc
{
	static const char *getTypeName (void) { return "GeoPosition";         }
	static const char *getGroupName(void) { return "GeoPosition";         }
	static const char *getClassName(void) { return "GeoPositionProperty"; }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	typedef OSGAttachment             Inherit;
	typedef OSGAttachmentPropertyDesc InheritDesc;
	typedef OSGAttachmentPtr          InheritPtr;
};

typedef OSGAbstractGeoProperty<OSGGeoPositionPropertyDesc> OSGGeoPosition;

typedef OSGGeoPosition::OSGPtrType OSGGeoPositionPtr;


template <>
struct OSGFieldDataTraits<OSGGeoPositionPtr> : public OSGTraits
{
    static char            *getSName (void)  { return "SFGeoPositionPtr"; }
    static char            *getMName (void)  { return "MFGeoPositionPtr"; }

    static OSGString        getDefault(void) { return OSGString();        }

    static bool             getFromString(OSGGeoPositionPtr  &,
                                          const char        *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGGeoPositionPtr &,
                                              OSGString         &)
    {
        // TO_BE_DONE
    }
};

typedef OSGSField<OSGGeoPositionPtr> OSGSFGeoPositionPtr;


// Position 3f

struct OSGGeoPosition3fPropertyDesc
{
	static const char *getTypeName (void) { return "GeoPosition3f";         }
	static const char *getClassName(void) { return "GeoPosition3fProperty"; }
	static const char *getFieldName(void) { return "positions";             }
	static const char *getGroupName(void) { return "GeoPosition";           }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	static OSGUInt32 getFormat    (void)  { return GL_FLOAT;        }
	static OSGUInt32 getFormatSize(void)  { return sizeof(GLfloat); }
	static OSGUInt32 getDimension (void)  { return 3;               }
	static OSGUInt32 getStride    (void)  { return 0;               }

	typedef OSGGeoPosition             Inherit;
	typedef OSGGeoPositionPtr          InheritPtr;
    typedef OSGGeoPositionPropertyDesc InheritDesc;
	typedef OSGMFPnt3f                 FieldType;
};

typedef OSGGeoProperty<OSGGeoPosition3fPropertyDesc> OSGGeoPosition3f;

typedef OSGGeoPosition3f::OSGPtrType OSGGeoPosition3fPtr;


// Normal

struct OSGGeoNormalPropertyDesc
{
	static const char *getTypeName (void) { return "GeoNormal";         }
	static const char *getGroupName(void) { return "GeoNormal";         }
	static const char *getClassName(void) { return "GeoNormalProperty"; }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	typedef OSGAttachment             Inherit;
	typedef OSGAttachmentPropertyDesc InheritDesc;
	typedef OSGAttachmentPtr          InheritPtr;
};

typedef OSGAbstractGeoProperty<OSGGeoNormalPropertyDesc> OSGGeoNormal;

typedef OSGGeoNormal::OSGPtrType OSGGeoNormalPtr;


template <>
struct OSGFieldDataTraits<OSGGeoNormalPtr> : public OSGTraits
{
    static char            *getSName  (void) { return "SFGeoNormalPtr"; }
    static char            *getMName  (void) { return "MFGeoNormalPtr"; }
    static OSGString        getDefault(void) { return OSGString();      }

    static bool             getFromString(      OSGGeoNormalPtr  &,
                                          const char            *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGGeoNormalPtr &,
                                              OSGString       &)
    {
        // TO_BE_DONE
    }
};

typedef OSGSField<OSGGeoNormalPtr> OSGSFGeoNormalPtr;


// Normal 3f

struct OSGGeoNormal3fPropertyDesc
{
	static const char *getTypeName  (void) { return "GeoNormal3f";         }
	static const char *getClassName (void) { return "GeoNormal3fProperty"; }
	static const char *getFieldName (void) { return "Normals";             }
	static const char *getGroupName (void) { return "GeoNormal";           }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	static OSGUInt32 getFormat    (void) { return GL_FLOAT;        }
	static OSGUInt32 getFormatSize(void) { return sizeof(GLfloat); }
	static OSGUInt32 getDimension (void) { return 3;               }
	static OSGUInt32 getStride    (void) { return 0;               }

	typedef OSGGeoNormal             Inherit;
	typedef OSGGeoNormalPtr          InheritPtr;
    typedef OSGGeoNormalPropertyDesc InheritDesc;
	typedef OSGMFVec3f               FieldType;
};

typedef OSGGeoProperty<OSGGeoNormal3fPropertyDesc> OSGGeoNormal3f;

typedef OSGGeoNormal3f::OSGPtrType OSGGeoNormal3fPtr;


// Color

struct OSGGeoColorPropertyDesc
{
	static const char *getTypeName (void) { return "GeoColor";         }
	static const char *getGroupName(void) { return "GeoColor";         }
	static const char *getClassName(void) { return "GeoColorProperty"; }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	typedef OSGAttachment             Inherit;
	typedef OSGAttachmentPropertyDesc InheritDesc;
	typedef OSGAttachmentPtr          InheritPtr;
};

typedef OSGAbstractGeoProperty<OSGGeoColorPropertyDesc> OSGGeoColor;

typedef OSGGeoColor::OSGPtrType OSGGeoColorPtr;


template <>
struct OSGFieldDataTraits<OSGGeoColorPtr> : public OSGTraits
{
    static char            *getSName  (void) { return "SFGeoColorPtr";    }
    static char            *getMName  (void) { return "MFGeoColorPtr";    }
    static OSGString        getDefault(void) { return OSGString();        }

    static bool             getFromString(      OSGGeoColorPtr  &,
                                          const char           *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGGeoColorPtr &,
                                              OSGString      &)
    {
        // TO_BE_DONE
    }
};

typedef OSGSField<OSGGeoColorPtr> OSGSFGeoColorPtr;


// Color 3f

struct OSGGeoColor3fPropertyDesc
{
	static const char *getTypeName (void) { return "GeoColor3f";         }
	static const char *getClassName(void) { return "GeoColor3fProperty"; }
	static const char *getFieldName(void) { return "Colors";             }
	static const char *getGroupName(void) { return "GeoColor";           }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	static OSGUInt32 getFormat    (void)  { return GL_FLOAT;        }
	static OSGUInt32 getFormatSize(void)  { return sizeof(GLfloat); }
	static OSGUInt32 getDimension (void)  { return 3;               }
	static OSGUInt32 getStride    (void)  { return 0;               }

	typedef OSGGeoColor             Inherit;
	typedef OSGGeoColorPtr          InheritPtr;
    typedef OSGGeoColorPropertyDesc InheritDesc;
	typedef OSGMFVec3f              FieldType;
};

typedef OSGGeoProperty<OSGGeoColor3fPropertyDesc> OSGGeoColor3f;

typedef OSGGeoColor3f::OSGPtrType OSGGeoColor3fPtr;


// Color 4ub


struct OSGGeoColor4ubPropertyDesc
{
	static const char *getTypeName  (void) { return "GeoColor4ub";         }
	static const char *getClassName (void) { return "GeoColor4ubProperty"; }
	static const char *getFieldName (void) { return "Colors";              }
	static const char *getGroupName (void) { return "GeoColor";            }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	static OSGUInt32 getFormat    (void)   { return GL_UNSIGNED_BYTE; }
	static OSGUInt32 getFormatSize(void)   { return sizeof(GLubyte);  }
	static OSGUInt32 getDimension (void)   { return 4;                }
	static OSGUInt32 getStride    (void)   { return 0;                }

	typedef OSGGeoColor             Inherit;
	typedef OSGGeoColorPtr          InheritPtr;
    typedef OSGGeoColorPropertyDesc InheritDesc;
	typedef OSGMFVec4ub             FieldType;
};

typedef OSGGeoProperty<OSGGeoColor4ubPropertyDesc> OSGGeoColor4ub;

typedef OSGGeoColor4ub::OSGPtrType OSGGeoColor4ubPtr;


// Index

struct OSGGeoIndexPropertyDesc
{
	static const char *getTypeName (void) { return "GeoIndex";         }
	static const char *getGroupName(void) { return "GeoIndex";         }
	static const char *getClassName(void) { return "GeoIndexProperty"; }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	typedef OSGAttachment             Inherit;
	typedef OSGAttachmentPropertyDesc InheritDesc;
	typedef OSGAttachmentPtr          InheritPtr;
};

typedef OSGAbstractGeoProperty<OSGGeoIndexPropertyDesc> OSGGeoIndex;

typedef OSGGeoIndex::OSGPtrType OSGGeoIndexPtr;


template <>
struct OSGFieldDataTraits<OSGGeoIndexPtr> : public OSGTraits
{
    static char            *getSName  (void) { return "SFGeoIndexPtr"; }
    static char            *getMName  (void) { return "MFGeoIndexPtr"; }
    static OSGString        getDefault(void) { return OSGString();     }

    static bool             getFromString(      OSGGeoIndexPtr   &,
                                          const char            *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGGeoIndexPtr &,
                                              OSGString      &)
    {
        // TO_BE_DONE
    }
};

typedef OSGSField<OSGGeoIndexPtr> OSGSFGeoIndexPtr;


// Index uint32

struct OSGGeoIndexUI32PropertyDesc
{
	static const char *getTypeName (void) { return "GeoIndexUI32";         }
	static const char *getClassName(void) { return "GeoIndexUI32Property"; }
	static const char *getFieldName(void) { return "Indices";              }
	static const char *getGroupName(void) { return "GeoIndex";             }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	static OSGUInt32 getFormat    (void) { return GL_UNSIGNED_INT; }
	static OSGUInt32 getFormatSize(void) { return sizeof(GLuint);  }
	static OSGUInt32 getDimension (void) { return 1;               }
	static OSGUInt32 getStride    (void) { return 0;               }

	typedef OSGGeoIndex             Inherit;
	typedef OSGGeoIndexPtr          InheritPtr;
    typedef OSGGeoIndexPropertyDesc InheritDesc;
	typedef OSGMFUInt32             FieldType;
};

typedef OSGGeoProperty<OSGGeoIndexUI32PropertyDesc> OSGGeoIndexUI32;

typedef OSGGeoIndexUI32::OSGPtrType OSGGeoIndexUI32Ptr;


// Primitive Type

// just one kind, to cut down the number of pumps needed
// screwed up architectures might have a problem with uint8, maybe we'll
// have to expand it later 


// PType

struct OSGGeoPTypePropertyDesc
{
	static const char *getTypeName (void) { return "GeoPType"; }
	static const char *getClassName(void) { return "GeoPTypeProperty"; }
	static const char *getFieldName(void) { return "Types"; }
	static const char *getGroupName(void) { return "GeoPType"; }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }
	static OSGUInt32 getFormat    (void) { return GL_UNSIGNED_BYTE;  }
	static OSGUInt32 getFormatSize(void) { return sizeof(GLubyte);   }
	static OSGUInt32 getDimension (void) { return 1;                 }
	static OSGUInt32 getStride    (void) { return 0;                 }

	typedef OSGAttachment             Inherit;
	typedef OSGAttachmentPtr          InheritPtr;
	typedef OSGAttachmentPropertyDesc InheritDesc;
	typedef OSGMFUInt8                FieldType;
};

typedef OSGGeoProperty<OSGGeoPTypePropertyDesc> OSGGeoPType;

typedef OSGGeoPType::OSGPtrType OSGGeoPTypePtr;


template <>
struct OSGFieldDataTraits<OSGGeoPTypePtr> : public OSGTraits
{
    static char            *getSName  (void) { return "SFGeoPTypePtr"; }
    static char            *getMName  (void) { return "MFGeoPTypePtr"; }
    static OSGString        getDefault(void) { return OSGString();     }

    static bool             getFromString(OSGGeoPTypePtr  &,
                                          const char     *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGGeoPTypePtr &,
                                              OSGString      &)
    {
        // TO_BE_DONE
    }
};

typedef OSGSField<OSGGeoPTypePtr> OSGSFGeoPTypePtr;


// Primitive Lengths

// just one kind, to cut down the number of pumps needed
// screwed up architectures might have a problem with uint8, maybe we'll
// have to expand it later 


struct OSGGeoPLengthPropertyDesc
{
	static const char *getTypeName (void) { return "GeoPLength";         }
	static const char *getClassName(void) { return "GeoPLengthProperty"; }
	static const char *getFieldName(void) { return "Lengths";            }
	static const char *getGroupName(void) { return "GeoPLength";         }

	static OSGInitContainerMethod getInitMethod(void) { return NULL; }

	static OSGUInt32 getFormat    (void) { return GL_UNSIGNED_INT; }
	static OSGUInt32 getFormatSize(void) { return sizeof(GLuint);  }
	static OSGUInt32 getDimension (void) { return 1;               }
	static OSGUInt32 getStride    (void) { return 0;               }

	typedef OSGAttachment             Inherit;
	typedef OSGAttachmentPtr          InheritPtr;
	typedef OSGAttachmentPropertyDesc InheritDesc;
	typedef OSGMFUInt32               FieldType;
};

typedef OSGGeoProperty<OSGGeoPLengthPropertyDesc> OSGGeoPLength;

typedef OSGGeoPLength::OSGPtrType OSGGeoPLengthPtr;


template <>
struct OSGFieldDataTraits<OSGGeoPLengthPtr> : public OSGTraits
{
    static char            *getSName  (void) { return "SFGeoPLengthPtr"; }
    static char            *getMName  (void) { return "MFGeoPLengthPtr"; }
    static OSGString        getDefault(void) { return OSGString();       }

    static bool             getFromString(      OSGGeoPLengthPtr  &,
                                          const char             *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGGeoPLengthPtr &,
                                              OSGString        &)
    {
        // TO_BE_DONE
    }
};

typedef OSGSField<OSGGeoPLengthPtr> OSGSFGeoPLengthPtr;

OSG_END_NAMESPACE

#include <OSGGeoProperty.inl>

#endif /* _OSGGEOPROPERTY_H_ */
