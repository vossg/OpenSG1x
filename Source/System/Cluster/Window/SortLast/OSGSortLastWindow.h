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

#ifndef _OSGSORTLASTWINDOW_H_
#define _OSGSORTLASTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <utility>
#include <vector>
#include <queue>

#include "OSGConfig.h"
#include "OSGRenderAction.h"

#include "OSGSortLastWindowBase.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING SortLastWindow : public SortLastWindowBase
{
  private:

    typedef SortLastWindowBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    enum { BALANCE_GEOMETRY_STATIC          =0,
           BALANCE_GEOMETRY_VIEW_DEOENDENT  =1,
           BALANCE_PROXYGROUPS              =2 };

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
    /*! \name                   static partition functions                 */
    /*! \{                                                                 */

    virtual void buildGroups              (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    struct DrawableInfo
    {
        NodePtr  node;
        Vec3f    bMin;
        Vec3f    bMax;
        Real32   load;
        
        DrawableInfo();
        DrawableInfo(const DrawableInfo &source);
        const DrawableInfo &operator =(const DrawableInfo &source);

        struct MaxXOrder : public 
        std::binary_function<const DrawableInfo&,const DrawableInfo&, bool>
        {
            bool operator() (const DrawableInfo &a, const DrawableInfo &b);
        };
        struct MaxYOrder : public 
        std::binary_function<const DrawableInfo&,const DrawableInfo&, bool>
        {
            bool operator() (const DrawableInfo &a, const DrawableInfo &b);
        };
        struct MaxZOrder : public 
        std::binary_function<const DrawableInfo&,const DrawableInfo&, bool>
        {
            bool operator() (const DrawableInfo &a, const DrawableInfo &b);
        };
    };
    typedef std::vector<DrawableInfo> DrawableListT;

    friend struct DrawableInfo;

    /*---------------------------------------------------------------------*/
    /*! \name      protected types                                         */
    /*! \{                                                                 */
/*
    typedef std::pair<UInt32,Real32> ServerLoad;
    typedef std::vector<ServerLoad>  ServerLoadSequence;
    struct ServerLoadCompate
    {
        bool operator()(const ServerLoad &a,const ServerLoad &b);
    };
    typedef std::priority_queue< ServerLoad, 
                                 ServerLoadSequence,
                                 ServerLoadCompate > ServerPQueue;
*/
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      client window funcitons                                 */
    /*! \{                                                                 */

    virtual void clientInit              ( void                        );
    virtual void clientPreSync           ( void                        );
    virtual void clientRender            ( RenderActionBase *action    );
    virtual void clientSwap              ( void                        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      server window funcitons                                 */
    /*! \{                                                                 */

    virtual void serverInit              ( WindowPtr window,UInt32 id  );
    virtual void serverRender            ( WindowPtr window,UInt32 id,
                                           RenderActionBase *action    );
    virtual void serverSwap              ( WindowPtr window,UInt32 id  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SortLastWindow(void);
    SortLastWindow(const SortLastWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SortLastWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   load balancing                             */
    /*! \{                                                                 */

    void collectDrawables  (const NodePtr       &node,
                            DrawableListT &drawables);
    void splitDrawables    (DrawableListT &src,
                            UInt32         groups,
                            bool           cut=false);
    void setupNodes        (UInt32         groupId  );
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SortLastWindowBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SortLastWindow &source);
};

typedef SortLastWindow *SortLastWindowP;

OSG_END_NAMESPACE

#include "OSGSortLastWindowBase.inl"
#include "OSGSortLastWindow.inl"

#define OSGSORTLASTWINDOW_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSORTLASTWINDOW_H_ */
