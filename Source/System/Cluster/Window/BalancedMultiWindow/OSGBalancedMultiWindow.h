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

#ifndef _OSGBALANCEDMULTIWINDOW_H_
#define _OSGBALANCEDMULTIWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include "OSGConfig.h"
#include "OSGNode.h"
#include "OSGBalancedMultiWindowBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief BalancedMultiWindow class. See \ref 
           PageSystemBalancedMultiWindow for a description.
*/
//#define MW_TILE_SIZE 21
//#define MW_TILE_SIZE 44
#define MW_TILE_SIZE 256

// TODO use dynamic performance values
#define MW_INDICES_PER_SEC         100000000.0
#define MW_VISIBLE_INDICES_PER_SEC  30000000.0
#define MW_PIXEL_PER_SEC          1000000000.0
#define MW_SHADED_PIXEL_PER_SEC      5000000.0

class OSG_SYSTEMLIB_DLLMAPPING BalancedMultiWindow : public BalancedMultiWindowBase
{
  private:

    typedef BalancedMultiWindowBase Inherited;
    enum {LEFT=0,BOTTOM=1,RIGHT=2,TOP=3};

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*--------------------------------------------------------------------*/
    /*! \name     server window funcitons                                 */
    /*! \{                                                                */

    void serverInit   ( WindowPtr window,UInt32 id  );
    void serverRender ( WindowPtr window,UInt32 id,
                        RenderActionBase *action    );

    /*! \}                                                                */
    /*--------------------------------------------------------------------*/
    /*! \name     client window functions                                 */
    /*! \{                                                                */

    void clientInit   ( void                        );
    void clientPreSync( void                        );
    void clientRender ( RenderActionBase *action    );

    /*! \}                                                                */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BalancedMultiWindow(void);
    BalancedMultiWindow(const BalancedMultiWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BalancedMultiWindow(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    struct LoadGroup;
    struct BBox;
    struct VPort;
    struct Server;
    struct WorkPackage;
    struct Tile;
    struct Area;
    struct Cluster;
    struct Worker;
    struct OpenBBox;
    struct ServerComp;
    struct BBoxList;

    friend struct LoadGroup;
    friend struct BBox;
    friend struct VPort;
    friend struct Server;
    friend struct WorkPackage;
    friend struct Tile;
    friend struct Area;
    friend struct Cluster;
    friend struct Worker;
    friend struct OpenBBox;
    friend struct ServerComp;
    friend struct BBoxList;

    struct LoadGroup {
        NodePtr                root;
        NodePtr                node;
        Real32                 pixel;
        Real32                 constant;
        Real32                 ratio;
    };
    struct BBox {
        UInt32                 groupId;
        Int32                  rect[4];
    };
    struct VPort {
        UInt32                 serverId;
        ViewportPtr            serverPort;
        NodePtr                root;
        UInt16                 id;
        Real32                 load;
        Int32                  rect[4];
        Real32                 loadCenter[2];
        std::vector<BBox>      bboxes;
    };
    struct Server {
        UInt16                 id;
        Real32                 load;
        std::vector<VPort>     viewports;
        WindowPtr              window;
    };
    struct WorkPackage {
        UInt16 viewportId;
        UInt16 drawServer;
        UInt16 sendToServer;
        Int32  rect[4];
    };
    struct Tile {
        struct Header {
            unsigned int x      :16;
            unsigned int y      :16;
            unsigned int width  :16;
            unsigned int height :15;
            unsigned int last   :1 ;
        } header;
        UInt8  pixel[MW_TILE_SIZE*MW_TILE_SIZE*3];
    };
    struct Area {
        UInt16                     workpackageId;
        std::vector<Tile>          tiles;
    };
    struct Cluster {
        UInt32                     load;
        std::vector<NodePtr>       rootNodes;
        std::vector<LoadGroup>     loadGroups;
        std::vector<Server>        servers;
        std::vector<WorkPackage>   workpackages;
        std::vector<Area>          areas;
    };
    struct Worker {
        UInt32                     serverId;
        Real32                     takeLoad;
        Real32                     assignedLoad;
    };
    struct OpenBBox {
        Real32                     lineLoad;
        Real32                     cnostLoast;
    };
    struct ServerComp
    {
        bool operator () (Server *s1,Server *s2) {
            return (s1->load < s2->load);
        }
    };
    struct BBoxList {
        BBoxList *next;
        Real32    pixel;
        Real32    constant;
    };
    Cluster                _cluster;
    std::vector<BBoxList*> _groupOpen;
    std::vector<BBoxList*> _groupClose;
    std::vector<BBoxList>  _bboxlist;
    VPort                  _foreignPort;
    bool                   _preloadCache;

    UInt32                 _triCount;
    Real64                 _drawTime;
    Real64                 _pixelTime;
    Real64                 _loadTime;
    Real64                 _balanceTime;
    Real64                 _netTime;

    bool                   _rebuildLoadGroups;

    // calculate rendering load 
    inline Real32 getVisibleLoad(Int32 const (&rect)[4],
                                 BBox      &bbox);
    // get number of tiles for the given area
    UInt32 calcTileCount(Int32 const (&rect)[4]);
    // project group and calculate bounding box
    bool calculateProjectedBBox(VPort &port,
                                LoadGroup &group,
                                BBox &bbox,
                                Matrix &proj);
    // create load groups for all root nodes
    void createLoadGroups(void);
    // collect load for a subtree
    void collectLoadGroups(NodePtr node,NodePtr root);
    // collect load for a subtree and to a maximal depth
    void collectLoadGroups(NodePtr node, NodePtr root, Int32 maxDepth, LoadGroup *parentLoad = 0);
    // collect visible viewports
    void collectVisibleViewports(Server &server);
    // calculate server viewport
    bool calculateServerPort(VPort &port, Int32 const (&rect)[4]);
    // create view dependent bboxes
    void createBBoxes(Server &server);
    // do load balancing for all servers
    void balanceServer(void);
    // split viewport
    void splitViewport(std::vector<Worker> &worker,
                       VPort &port,
                       Int32 const (&rect)[4],
                       Real32 load);
    // sort bboxes
    void sortBBoxes(VPort &port,UInt32 axis, Int32 const (&rect)[4]);
    // split load at a given axis
    void splitAxis(Real32 const (&load)[2],
                   VPort &port,
                   Int32 const (&rect)[4],
                   int axis,
                   Real32 (&resultLoad)[2],
                   Int32 (&resultRect)[2][4]);
    // render part of a viewport viewport 
    void renderViewport(WindowPtr         serverWindow,
                        UInt32            id,
                        RenderActionBase *action,
                        UInt32            portId,
                        Int32 const (&rect)[4]);
    // clear local ports
    void clearViewports(WindowPtr         serverWindow,
                        UInt32            id,
                        RenderActionBase *action);
    // store viewport
    void storeViewport(Area &area,ViewportPtr vp, Int32 const (&rect)[4]);

    // do rendering and network transfer
    void drawSendAndRecv(WindowPtr serverWindow,
                         RenderActionBase *action,
                         UInt32 id);

    // preload display lists and textures
    void preloadCache(WindowPtr window,
                      RenderActionBase *action);

    friend class FieldContainer;
    friend class BalancedMultiWindowBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const BalancedMultiWindow &source);
};

typedef BalancedMultiWindow *BalancedMultiWindowP;

OSG_END_NAMESPACE

#include "OSGBalancedMultiWindowBase.inl"
#include "OSGBalancedMultiWindow.inl"

#define OSGBALANCEDMULTIWINDOW_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.21 2003/07/11 18:39:08 dirk Exp $"

#endif /* _OSGBALANCEDMULTIWINDOW_H_ */
