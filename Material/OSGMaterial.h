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
 *                                                                           *
 *                                                                           *
 *                                                                           *
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


#ifndef _OSGMATERIAL_H_
#define _OSGMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEMATERIAL
#       define OSG_MATERIAL_DLLMAPPING __declspec(dllexport)
#   else
#       define OSG_MATERIAL_DLLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_MATERIAL_DLLMAPPING
#endif

#include "OSGFieldDescription.h"
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Geometry;
typedef FCPtr <NodeCorePtr, Geometry> GeometryPtr;

class Action;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class Material;
typedef FCPtr<FieldContainerPtr, Material> MaterialPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class Material : public FieldContainer
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

	typedef FieldContainer Inherited;
    typedef MaterialPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGMaterial"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_ABSTR_FIELD_CONTAINER_DECL(MaterialPtr)

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;
 
    /*------------------------- your_category -------------------------------*/

	/** sets up the OpenGL and calls the Geometry's draw method.
	    Not sure that's the best idea. Alternative: Functor */
	
	virtual void draw( Geometry* geo, Action * action ) = 0;

    /*----------------------------- access ----------------------------------*/

	
    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

	// defines an ordering for materials.
    virtual Bool operator < (const Material &other) const;
    
	virtual Bool operator == (const Material &other) const;
	virtual Bool operator != (const Material &other) const;

    /*------------------------- debug ----------------------------------*/

	void print( void );
	
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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Material(void);
    virtual ~Material(void); 

    Material(const Material &source);    

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

	friend class FieldContainer;
	
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
	Material & operator =(const Material &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef Material *MaterialP;

// field support

template <>
struct OSG_MATERIAL_DLLMAPPING FieldDataTraits<MaterialPtr> : public Traits
{
    enum		{ StringConvertable = ToStringConvertable | 
										FromStringConvertable };

    static char *getSName(void) { return "SFMaterialPtr"; }
    static char *getMName(void) { return "MFMaterialPtr"; }

    static Bool          getDefault(void)    { return false; }

    static bool             getFromString(MaterialPtr &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const MaterialPtr &,
                                              String &)
    {
        // TO_BE_DONE
    }
};

typedef SField<MaterialPtr> SFMaterialPtr;
typedef MField<MaterialPtr> MFMaterialPtr;

// null pointer

extern MaterialPtr NullMaterial;

OSG_END_NAMESPACE

#include "OSGMaterial.inl"

#endif /* _OSGMaterial_H_ */
