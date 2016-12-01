/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGPARTICLEBSP_H_
#define _OSGPARTICLEBSP_H_
#ifdef __sgi
#pragma once
#endif

// exclude the whole class from user docs
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

#include "OSGConfig.h"

#include "OSGMaterialDrawable.h"

#include "OSGGeoPropertyBase.h"

OSG_BEGIN_NAMESPACE

typedef GeoPositions::PtrType GeoPositionsPtr;

class Particles;
typedef FCPtr<MaterialDrawablePtr, Particles> ParticlesPtr;
 
class ParticleBSPTree;

/*! \brief Particle BSP Tree Node
 */

class OSG_SYSTEMLIB_DLLMAPPING ParticleBSPNode
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum { X=0, Y, Z, Leaf } Axis;
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleBSPNode(void);
    ParticleBSPNode(const ParticleBSPNode &source);

    ParticleBSPNode(UInt32 value);
    ParticleBSPNode(UInt8 axis, Real32 splitvalue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    ~ParticleBSPNode(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access                                   */
    /*! \{                                                                 */

    inline bool   isLeaf       (void) const;
    inline Int32  getValue     (void) const;
    inline Real32 getSplitValue(void) const;
    inline UInt8  getAxis      (void) const;

    inline void   setValue     (Int32 value);
    inline void   setSplit     (UInt8 axis, Real32 splitvalue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void dump(      UInt32     uiIndent = 0, 
              const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    
    /*==========================  PRIVATE  ================================*/
  private:

    UInt8   _axis;

    union
    {
        Int32   _value;   
        Real32  _splitvalue;
    };
};

/*! \brief Particle BSP Tree 
 */

class OSG_SYSTEMLIB_DLLMAPPING ParticleBSPTree
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleBSPTree(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleBSPTree(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Creation / Deletion                            */
    /*! \{                                                                 */

    inline bool created(void) const;

           void build  (Particles *core);

           void destroy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Traversal                                 */
    /*! \{                                                                 */

    Int32 *traverse(const Pnt3f &refPoint, UInt32 &length, 
                    Int32 *order = NULL) const; 

    Int32 *traverse(const Vec3f &refVec, UInt32 &length, 
                    Int32 *order = NULL) const; 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Input / Output                               */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;
    
    void putToString(std::string &outVal) const;
     
    bool getFromString(const Char8 *&inVal);
   
    UInt32 getBinSize(void) const;

    void copyToBin(BinaryDataHandler &pMem) const;
    
    void copyFromBin(BinaryDataHandler &pMem);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                 Node Traversal                               */
    /*! \{                                                                 */

    UInt32 doTraverse(const Pnt3f &refPoint, UInt32 index, UInt32 length, 
                      Int32 *order) const; 

    UInt32 doTraverse(const Vec3f &refVec, UInt32 index, UInt32 length, 
                      Int32 *order) const; 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Creation Tools                               */
    /*! \{                                                                 */

    UInt32 doBuild(std::vector<Int32>::iterator begin, 
                   std::vector<Int32>::iterator end,
                        UInt32                  nodeindex,
                        GeoPositionsPtr         pos      ); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:
    
    std::vector<ParticleBSPNode> _tree;
};


#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<ParticleBSPTree> : 
    public FieldTraitsRecurseBase<ParticleBSPTree>
{
    static DataType       _type;

    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    static       DataType       &getType      (void) { return _type;          }

    static const Char8          *getSName     (void) { return "SFParticleBSPTree"; }
    static const Char8          *getMName     (void) { return "MFParticleBSPTree"; }

    static       ParticleBSPTree getDefault   (void) { return ParticleBSPTree();   }

    static bool            getFromString(      ParticleBSPTree  &outVal,
                                         const Char8           *&inVal)
    {
        return outVal.getFromString(inVal);
    }

    static void           putToString   (const      ParticleBSPTree &inVal,
                                               std::string          &outVal)
    {
        inVal.putToString(outVal);
    }
    
    static UInt32 getBinSize(const ParticleBSPTree &oObject)
    {
        return oObject.getBinSize();
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const ParticleBSPTree     &oObject)
    {
       oObject.copyToBin(pMem);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ParticleBSPTree     &oObject)
    {
        oObject.copyFromBin(pMem);
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class FieldTraitsRecurseBase<ParticleBSPTree> */
/*! \hideinhierarchy                               */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \brief ParticleBSPTree fields
*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<ParticleBSPTree> SFParticleBSPTree;
#endif

#ifndef OSG_COMPILEPARTICLEBSPINST
OSG_DLLEXPORT_DECL1(SField, ParticleBSPTree, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


OSG_END_NAMESPACE

#include "OSGParticleBSP.inl"

#define OSGPARTICLEBSP_HEADER_CVSID "@(#)$Id: $"

#endif            // exclude from user doc

#endif /* _OSGPARTICLES_H_ */
