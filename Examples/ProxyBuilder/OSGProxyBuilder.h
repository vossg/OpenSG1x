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

#ifndef _OSGPROXYBUILDER_H_
#define _OSGPROXYBUILDER_H_
#ifdef __sgi
#pragma once
#endif

#include <map>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGMaterialGroup.h>

#include <OSGProxyBuilderBase.h>

OSG_BEGIN_NAMESPACE

class ProxyBuilder : public ProxyBuilderBase
{
  private:

    typedef ProxyBuilderBase Inherited;

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
    /*! \name                     enable / disable                         */
    /*! \{                                                                 */

    static void start(const std::string &filePrefix,
                      UInt32 positionsThreshold,
                      bool concurrent=false,
                      bool zip=true); 
    static void stop(void); 
    void onCreate(const ProxyBuilder *source = NULL);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ProxyBuilderBase.
    struct GroupInfo{
        osg::MaterialGroupPtr mat;
        osg::NodeCorePtr      proxy;
        osg::GeometryPtr      builder;
    };

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ProxyBuilder(void);
    ProxyBuilder(const ProxyBuilder &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ProxyBuilder(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   misc                                       */
    /*! \{                                                                 */

    static void createProxyGroup(GeometryPtr proxyBuilder);
    static void createPendingProxyGroups(bool force=false);

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    static FieldContainerPtr         _geometryProto;
    static FieldContainerPtr         _proxyBuilderProto;
    static UInt32                    _proxyNum;
    static std::vector<GeometryPtr>  _geos;
    static UInt32                    _positionsThreshold;
    static bool                      _concurrentLoad;
    static bool                      _zip;
    static std::string               _filePrefix;

    friend class FieldContainer;
    friend class ProxyBuilderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ProxyBuilder &source);
};

typedef ProxyBuilder *ProxyBuilderP;

OSG_END_NAMESPACE

#include <OSGProxyBuilderBase.inl>
#include <OSGProxyBuilder.inl>

#define OSGPROXYBUILDER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.21 2003/07/11 18:39:08 dirk Exp $"

#endif /* _OSGPROXYBUILDER_H_ */
