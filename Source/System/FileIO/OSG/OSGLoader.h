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

#ifndef _OSGLOADER_H_
#define _OSGLOADER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGScanParseSkel.h"
#include "OSGScanParseFieldTypeMapper.h"

#include "OSGNodePtr.h"
#include "OSGField.h"
#include "OSGFieldContainer.h"

#include <stack>
#include <map>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib
 *  \brief native osg loader (vrml syntax)
 */

class OSG_SYSTEMLIB_DLLMAPPING OSGLoader :
    public ScanParseFieldTypeMapper<ScanParseSkel>
{
    /*==========================  PRIVATE  ================================*/
  private:

    typedef ScanParseFieldTypeMapper<ScanParseSkel    > Inherited;
    typedef std::map                <std::string,
                                     FieldContainerPtr> NamedFCMap;
    typedef OSGLoader                                   Self;

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSGLoader(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OSGLoader(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Skel replacements                             */
    /*! \{                                                                 */

    virtual void scanStream       (std::istream &is);

    virtual void    beginNode         (const Char8  *szNodeTypename,
                                       const Char8  *szNodename       );

    virtual void    endNode           (void);

    virtual void    use               (const Char8  *szName           );

    virtual void    beginField        (const Char8  *szFieldname,
                                       const UInt32  uiFieldTypeId    );

    virtual void    endField          (void                           );

    virtual void    addFieldValue     (const Char8  *szFieldVal       );

    virtual Int32   mapExtIntFieldType(const Char8  *szFieldname,
                                       const Int32   iFieldTypeId     );

    virtual UInt32  getFieldType      (const Char8  *szFieldname      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual      NodePtr                   getRootNode (void);
    virtual std::vector<FieldContainerPtr> getRootNodes(void);

    virtual      FieldContainerPtr         getReference (const Char8 *szName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

          FieldContainerPtr                     _pCurrentFC;
          NodePtr                               _pRootNode;
          Field                                *_pCurrentField;
    const FieldDescription                     *_pCurrentFieldDesc;
          NamedFCMap                            _defMap;

          std::stack<      FieldContainerPtr >  _fcStack;
          std::stack<      Field            *>  _fStack;
          std::stack<const FieldDescription *>  _fdStack;

    void              initFieldTypeMapper   (      void                      );

    void              setFieldContainerValue(      FieldContainerPtr pNewNode);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGLoader(const OSGLoader &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OSGLoader &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGLoader *OSGLoaderP;

OSG_END_NAMESPACE

#define OSGLOADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGLOADER_H_ */
