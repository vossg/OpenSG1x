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


#ifndef _OSGGEOPROPERTYBASE_H_
#define _OSGGEOPROPERTYBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <GL/gl.h>

#include <OSGSystemDef.h>
#include <OSGMFVecTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGMFBaseTypes.h>
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
class OSG_SYSTEMLIB_DLLTMPLMAPPING AbstractGeoProperty : 
    public GeoPropertyDesc::Inherit
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
	
	// generic access to make using different types easier
	// mimics the MField interface as far as possible

	virtual typename GeoPropertyDesc::GenericType 
					getValue( const UInt32 index ) = 0;
					
	virtual typename GeoPropertyDesc::GenericType 
					getValue( const UInt32 index ) const = 0;

	virtual void	getValue( typename GeoPropertyDesc::GenericType & val,
						const UInt32 index ) = 0;

	virtual void	getValue( typename GeoPropertyDesc::GenericType & val,
						const UInt32 index ) const = 0;
					
	virtual void 	setValue(
						const typename GeoPropertyDesc::GenericType & val,
						const UInt32 index ) = 0;
	
	virtual void 	addValue(
						const typename GeoPropertyDesc::GenericType & val )= 0;

	// insert() and erase() should go here
	// it's just not clear how to handle iterators in a generic way
	// what about find()? Probably not very useful in this context
	
	virtual void 	clear( void ) = 0;
	

	virtual void	resize(size_t newsize) = 0;
	
	virtual void 	push_back( 
					const typename GeoPropertyDesc::GenericType & val ) = 0;
	
	// size clashes with another size()...
	// virtual UInt32	size( void ) const;

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;


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

    friend class OSG_SYSTEMLIB_DLLMAPPING FieldContainer;

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


};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

template <class GeoPropertyDesc>
class OSG_SYSTEMLIB_DLLMAPPING GeoProperty : public GeoPropertyDesc::Inherit
{
  private:

    typedef typename GeoPropertyDesc::Inherit Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(GeoPropDataField)
    
    OSG_FC_LAST_FIELD_IDM_DECL (GeoPropDataField)

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

	// cast operator to allow using a geoProperty just like its only field

	typename GeoPropertyDesc::FieldType& operator->() { return _field; }

	
	// generic access to make using different types easier

	virtual typename GeoPropertyDesc::GenericType 
					getValue( const UInt32 index );
					
	virtual typename GeoPropertyDesc::GenericType 
					getValue( const UInt32 index ) const;

	virtual void	getValue( typename GeoPropertyDesc::GenericType & val,
						const UInt32 index );

	virtual void	getValue( typename GeoPropertyDesc::GenericType & val,
						const UInt32 index ) const;
					
	virtual void 	setValue(
						const typename GeoPropertyDesc::GenericType & val,
						const UInt32 index );
	
	virtual void 	addValue(
						const typename GeoPropertyDesc::GenericType & val );
	// insert() and erase() should go here
	// it's just not clear how to handle iterators in a generic way
	// what about find()? Probably not very useful in this context
	
	virtual void 	clear();
	
	virtual void	resize(size_t newsize);
	
	virtual void 	push_back( 
					const typename GeoPropertyDesc::GenericType & val );
	
	// size clashes with FieldContainer::size()
	// virtual UInt32	size( void ) const;

    /*------------------------- assignment ----------------------------------*/

    GeoProperty &operator =(const GeoProperty &source);

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

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

    friend class OSG_SYSTEMLIB_DLLMAPPING FieldContainer;

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

    virtual void executeSync    (FieldContainer &other,
                                 BitVector       whichField);

            void executeSyncImpl(GeoProperty *pOther,
                                 BitVector    whichField);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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

struct AttachmentPropertyDesc
{
	static const char *getTypeName (void)  { return "Attachment"; }
};

//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

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
};

typedef AbstractGeoProperty<GeoPositionPropertyDesc> GeoPosition;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoPositionPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty, 
                            GeoPositionPropertyDesc, 
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

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
};

typedef AbstractGeoProperty<GeoNormalPropertyDesc> GeoNormal;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoNormalPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty, 
                            GeoNormalPropertyDesc, 
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

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
};

typedef AbstractGeoProperty<GeoColorPropertyDesc> GeoColor;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoColorPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty, 
                            GeoColorPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


// TexCoords

struct GeoTexCoordsPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoTexCoords";         }
	static const Char8 *getGroupName(void) { return "GeoTexCoords";         }
	static const Char8 *getClassName(void) { return "GeoTexCoordsProperty"; }

	static InitContainerF getInitMethod(void) { return NULL; }

	typedef Attachment				Inherit;
	typedef AttachmentPropertyDesc	InheritDesc;
	typedef AttachmentPtr			InheritPtr;

    typedef Vec2f					GenericType;
};

typedef AbstractGeoProperty<GeoTexCoordsPropertyDesc> GeoTexCoords;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoTexCoordsPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty, 
                            GeoTexCoordsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

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
};

typedef AbstractGeoProperty<GeoIndexPropertyDesc> GeoIndex;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoIndexPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty, 
                            GeoIndexPropertyDesc, 
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif



//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

// Primitive Type

// just one kind, to cut down the number of pumps needed
// screwed up architectures might have a problem with uint8, maybe we'll
// have to expand it later 


// PType

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
};

typedef GeoProperty<GeoPTypePropertyDesc> GeoPType;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoPTypePropertyDesc>::_type
#pragma do_not_instantiate GeoProperty<GeoPTypePropertyDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty, 
                      GeoPTypePropertyDesc, 
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------


// Primitive Lengths

// just one kind, to cut down the number of pumps needed
// screwed up architectures might have a problem with uint8, maybe we'll
// have to expand it later 


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
};

typedef GeoProperty<GeoPLengthPropertyDesc> GeoPLength;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoPLengthPropertyDesc>::_type
#pragma do_not_instantiate GeoProperty<GeoPLengthPropertyDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty, 
                      GeoPLengthPropertyDesc, 
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include <OSGGeoPropertyBase.inl>


#endif /* _OSGGEOPROPERTYBASE_H_ */
