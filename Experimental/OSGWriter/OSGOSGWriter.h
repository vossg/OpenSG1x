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

#ifndef _OSGOSGWRITER_H_
#define _OSGOSGWRITER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <iostream>

#include <string>
#include <map>
#include <vector>

#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGFieldContainer.h>
#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GeometryWriterLib
 *  \brief Brief OSGWriter
 */

class OSG_SYSTEMLIB_DLLMAPPING OSGWriter
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSGWriter(ostream &stream, UInt32 indentStep = 4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~OSGWriter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    void write(FieldContainerPtr         container );
    void write(vector<FieldContainerPtr> containers);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected: 

    struct SharedFCInfoHelper
    {
        Bool   printed;
        Bool   named;
        string name;
        static string buildName(FieldContainerPtr fcptr,
                                UInt32            num);

        SharedFCInfoHelper(void);
    };
    
    typedef map<FieldContainerPtr, SharedFCInfoHelper> SharedFCInfoMap;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SharedFCInfoMap  _fcmap;
    UInt32           _sharedFCCount;
    UInt32           _indention;
    UInt32           _indentStep;

    ostream         &_outstream;


    void indentLine     (void                         );
    void setIndentStep  (UInt32            newStep    );
    void doListFC       (FieldContainerPtr fieldConPtr);
    void doPrintListedFC(FieldContainerPtr fieldConPtr);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGWriter(const OSGWriter &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OSGWriter &source);
};

OSG_END_NAMESPACE

#define OSGOSGWRITER_HEADER_CVSID "@(#)$Id: OSGOSGWriter.h,v 1.5 2001/12/20 16:35:10 vossg Exp $"
    
#endif /* _OSGOSGWRITER_H_ */
