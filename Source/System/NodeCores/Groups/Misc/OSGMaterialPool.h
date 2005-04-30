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

#ifndef _OSGMATERIALPOOL_H_
#define _OSGMATERIALPOOL_H_

#ifdef __sgi
#pragma once
#endif

#include <set>
#include <vector>

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGMaterialPoolBase.h>
#include <OSGAction.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING MaterialPool : public MaterialPoolBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField,
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void    sync     (void                          );

    UInt32  getCount (void                          ) const;

    void    add      (const MaterialPtr &mat        );
    void    add      (const NodePtr &root           );
    void    add      (const MaterialPoolPtr &mp     );

    Int32   find     (const MaterialPtr &mat        ) const;

    void    sub      (const MaterialPtr &mat        );
    void    sub      (const NodePtr &root           );
    void    sub      (const MaterialPoolPtr &mp     );
    void    sub      (      UInt32   mat            );

    MaterialPtr get  (      UInt32   index          );
    void        get  (std::vector<MaterialPtr> &mats);
    const std::set<MaterialPtr> &get(void);

    void    clear    (void                          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef MaterialPoolBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    MaterialPool(void);
    MaterialPool(const MaterialPool &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialPool(void);

    void onDestroy(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MaterialPoolBase;

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MaterialPool &source);

    OSG::Action::ResultE addMaterialCB(OSG::NodePtr &node);
    OSG::Action::ResultE subMaterialCB(OSG::NodePtr &node);

    std::set<MaterialPtr> _mats;
};

typedef MaterialPool *MaterialPoolP;

OSG_END_NAMESPACE

#include <OSGMaterialPoolBase.inl>
#include <OSGMaterialPool.inl>

#define OSGMATERIALPOOL_HEADER_CVSID "@(#)$Id: OSGMaterialPool.h,v 1.1 2005/04/30 15:03:20 a-m-z Exp $"

#endif /* _OSGMATERIALPOOL_H_ */
