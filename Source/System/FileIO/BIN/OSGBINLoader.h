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

#ifndef _OSGBINLOADER_H_
#define _OSGBINLOADER_H_
#ifdef __sgi
#pragma once
#endif
#include <OSGConfig.h>
#include <map>
#include <vector>
#include <iostream>
#include <OSGNode.h>
#include <OSGBinaryDataHandler.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING BINLoader
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors/Destructor                    */
    /*! \{                                                                 */

             BINLoader(std::istream &is);
    virtual ~BINLoader();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   read / root access                         */
    /*! \{                                                                 */

         void            read        (void);
         NodePtr         getRootNode (void);
    std::vector<NodePtr> getRootNodes(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    struct FCIdMapper;
    friend class FCIdMapper;

    /*! \hideinhierarchy */
    struct FCInfoStruct
    {
        UInt32            newId;
        FieldContainerPtr ptr;
        bool              read;
        FCInfoStruct();
    };
    //          oldID	newId + FCPtr
    typedef std::map<UInt32, FCInfoStruct> IDLookupMap;

    /*! \hideinhierarchy */
    struct FCIdMapper : public FieldContainerMapper
    {
      public:
        const IDLookupMap *ptrMap;
        FCIdMapper(IDLookupMap *m);

        virtual UInt32 map(UInt32 uiId);
    };

    /*! \hideinhierarchy */
    class BinaryFileHandler : public BinaryDataHandler
    {
      public:
        BinaryFileHandler(std::istream &is);
        virtual ~BinaryFileHandler();

        void read (MemoryHandle mem, UInt32 size);

      private:

        std::vector<UInt8>  _readMemory;
        std::istream &_is;
    };

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                   private helper functions                   */
    /*! \{                                                                 */

    bool createFieldContainers(void);
    void chargeFieldContainers(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   provate members                            */
    /*! \{                                                                 */

         BinaryFileHandler _inFileHandler;
         IDLookupMap       _fcInfoMap;
         UInt32            _countContainers;
    std::vector<NodePtr>   _vec_pRootNodes;
         bool              _valid_stream;

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#define OSGBINLOADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGBINLOADER_H_ */
