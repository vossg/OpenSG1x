/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGPIPELINECOMPOSER_H_
#define _OSGPIPELINECOMPOSER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGPipelineComposerBase.h"
#include "OSGBaseThread.h"
#include "OSGLock.h"

OSG_BEGIN_NAMESPACE

//#define USE_NV_OCCLUSION 1

/*! \brief PipelineComposer class. See \ref 
           PageSystemPipelineComposer for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING PipelineComposer : public PipelineComposerBase
{
  private:

    typedef PipelineComposerBase       Inherited;

    struct TileBuffer;
    struct GroupInfo;
    struct GroupInfoOrder;
    friend struct TileBuffer;
    friend struct GroupInfo;
    friend struct GroupInfoOrder;

    /** \brief RGB Color value */
    struct RGBValue
    {
        UInt8 red;
        UInt8 green;
        UInt8 blue;
    };
    struct DepthInfo
    {
        UInt32 min;
        UInt32 max;
        UInt8  occlude;
    };
    struct TransInfo
    {
        unsigned int sendTo   :13;
        unsigned int empty    :1;
        unsigned int sendDepth:1;
        unsigned int first    :1;
    };
    struct TileBuffer
    {
        bool empty;
        UInt32 size;
        UInt32 colorSize;
        UInt32 depthSize;
        UInt32 dataSize;
        Connection *dstConnection;
        struct DepthInfo depth;
        struct TransInfo trans;
        struct {
            UInt32 count;
            UInt16 x;
            UInt16 y;
            UInt16 w;
            UInt16 h;
            UInt16 depth;
        } header;
        UInt8 data[1];
    };
    struct GroupInfo
    {
        UInt32 id;
        struct DepthInfo depth;
        struct TransInfo trans;
    };
    struct GroupInfoOrder : public std::binary_function<
        const GroupInfo*,const GroupInfo*, bool>
    {
        bool operator() (const GroupInfo *a, const GroupInfo *b);
    };
    struct Statistics {
        UInt32 bytesIn;
        UInt32 bytesOut;
        UInt32 occluded;
        UInt32 noDepth;
        UInt32 noGeo;
        UInt32 clipped;
        double sortTime;
        double pixelReadTime;
        double composeTime;
    };
    typedef std::list<TileBuffer*> QueueT;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      composition                                             */
    /*! \{                                                                 */

    virtual void open           ( void             );
    virtual void startViewport  ( ViewportPtr port );
    virtual void composeViewport( ViewportPtr port );
    virtual void close          ( void             );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      features                                                */
    /*! \{                                                                 */

    virtual bool getClientRendering(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    UInt32                      _tileBufferSize;
    std::vector<UInt8>          _tileA;
    std::vector<UInt8>          _tileB;
    std::vector<UInt8>          _workingTile;
    std::vector<UInt8>         *_readTilePtr;
    std::vector<UInt8>         *_composeTilePtr;
    UInt32                      _readTilesX;
    UInt32                      _readTilesY;
    UInt32                      _composeTilesX;
    UInt32                      _composeTilesY;

    std::vector< TransInfo              > _transInfo;
    std::list  < GroupInfo              > _groupInfoPool;
    std::vector< GroupInfo*             > _groupInfo;

    GLenum                      _colorFormat;
    GLenum                      _colorType;
    GLenum                      _depthType;

    Statistics                  _statistics;

    BaseThread                 *_writer;
    Thread                     *_composer;
    Barrier                    *_barrier;
    Barrier                    *_composeBarrier;
    Barrier                    *_frameEndBarrier;
    Lock                       *_lock;
    QueueT                      _queue;
    bool                        _waiting;
    GLuint                      _occlusionQuery;
    bool                        _firstFrame;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PipelineComposer(void);
    PipelineComposer(const PipelineComposer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PipelineComposer(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      helper function                         */
    /*! \{                                                                 */

    template<class DepthT,class ColorT>
    UInt32 getMinMaxOcclude(DepthT &depth,ColorT &color,
                            DepthInfo *buffer);

    template<class DepthT,class ColorT>
    void setTransInfo(DepthT &depth,ColorT &color);

    template<class DepthT,class ColorT>
    void calculateTransInfo(DepthT &depth,ColorT &color);

    template<class DepthT,class ColorT>
    void clientCompose(DepthT &depth,ColorT &color);

    template<class DepthT,class ColorT>
    void serverCompose(DepthT &depth,ColorT &color);

    template<class DepthT,class ColorT>
    void writeResult(DepthT &depth,ColorT &color);

    template<class DepthT,class ColorT>
    void readBuffer(DepthT &depth,ColorT &color,
                      ViewportPtr port);
    template<class DepthT,class ColorT>
    void composeBuffer(DepthT &depth,ColorT &color);

    UInt32 compressTransInfo(std::vector<TransInfo> &transInfo);
    void   uncompressTransInfo(std::vector<TransInfo> &transInfo,UInt32 infoCount);

    template <class T,T empty>
    static bool checkDepth(T *buffer,T &front,T &back,int size);

    TileBuffer *getComposeTileBuffer(UInt32 x,UInt32 y);
    TileBuffer *getReadTileBuffer(UInt32 x,UInt32 y);
    TileBuffer *getWorkingTileBuffer(void);

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PipelineComposerBase;

    static void writeProc(void *arg);
    static void composeProc(void *arg);
    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PipelineComposer &source);
};

typedef PipelineComposer *PipelineComposerP;

OSG_END_NAMESPACE

#include "OSGPipelineComposerBase.inl"
#include "OSGPipelineComposer.inl"

#define OSGPIPELINECOMPOSER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGPIPELINECOMPOSER_H_ */
