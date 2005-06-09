/*!
 * \class TwoSidedLightingChunk
 * \brief
 * \author Andreas Zieringer AMZ GmbH
 */

#ifndef _OSGTWOSIDEDLIGHTINGCHUNK_H_
#define _OSGTWOSIDEDLIGHTINGCHUNK_H_
#ifdef __sgi
#   pragma once
#endif

//----------------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------------

#include <OSGConfig.h>

#include <OSGTwoSidedLightingChunkBase.h>

//----------------------------------------------------------------------------
//  namespaces
//----------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

/*! \brief State chunk for automatic cubetexture coordinate transformations. 
*/

class OSG_SYSTEMLIB_DLLMAPPING TwoSidedLightingChunk : public TwoSidedLightingChunkBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

           virtual const StateChunkClass * getClass         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    inline static        UInt32            getStaticClassId (void);
    inline static  const StateChunkClass * getStaticClass   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      State                                   */
    /*! \{                                                                 */

    virtual void activate   ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0 );

    virtual void deactivate ( DrawActionBase * action, UInt32 index = 0 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32  switchCost    ( StateChunk * chunk );

    virtual bool operator <  (const StateChunk &other) const;

    virtual bool operator == (const StateChunk &other) const;
    virtual bool operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CubeTextureTransformChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TwoSidedLightingChunk(void);
    TwoSidedLightingChunk(const TwoSidedLightingChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TwoSidedLightingChunk(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TwoSidedLightingChunkBase;

    typedef TwoSidedLightingChunkBase Inherited;

    static void initMethod(void);
    
    // class. Used for indexing in State
    static StateChunkClass _class;
   
    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TwoSidedLightingChunk &source);

    GLboolean _state;
};

typedef TwoSidedLightingChunk *TwoSidedLightingChunkP;

OSG_END_NAMESPACE

#include <OSGTwoSidedLightingChunkBase.inl>
#include <OSGTwoSidedLightingChunk.inl>

#define OSGTWOSIDEDLIGHTINGCHUNK_HEADER_CVSID "@(#)$Id: OSGTwoSidedLightingChunk.h,v 1.1 2005/06/09 08:39:27 a-m-z Exp $"

#endif /* _OSGTWOSIDEDLIGHTINGCHUNK_H_ */
