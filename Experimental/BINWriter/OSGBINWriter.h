/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSGBINWriter_H_
#define _OSGBINWriter_H_
#ifdef __sgi
#pragma once
#endif
#include <OSGConfig.h>

#include <map>
#include <vector>

#include <OSGNode.h>
#include <OSGBinaryDataHandler.h>
#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//! Brief
//! \ingroup baselib

class OSG_SYSTEMLIB_DLLMAPPING BINWriter
{
    /*==========================  PUBLIC  =================================*/
  public:
	
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BINWriter(FILE *file);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~BINWriter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Access                                       */
    /*! \{                                                                 */

    void write(NodePtr         node );
    void write(vector<NodePtr> nodes);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */
	struct FCInfo 
	{
         osg::IDString     type;
		 FieldContainerPtr ptr;  
 		 BitVector         mask; //should match UInt32
		 FCInfo();
	};
    //FieldContainerId is of type UInt32
  	typedef map<UInt32, FCInfo> FCInfoMap;	
    typedef map<std::string, vector<UInt32> > FCTypeIdMap;

	class BinaryFileHandler : public OSG::BinaryDataHandler
    {
	  public:
		BinaryFileHandler(FILE *file);
		virtual ~BinaryFileHandler();
	    
		void read (OSG::MemoryHandle mem, OSG::UInt32 size);
		void write(OSG::MemoryHandle mem, OSG::UInt32 size);
	
	  private:
		vector<OSG::UInt8> _readMemory;
		vector<OSG::UInt8> _writeMemory;
		FILE *_file;

        BinaryFileHandler(const BinaryFileHandler &source);
        void operator =(const BinaryFileHandler &source);
	};
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

	void addToIdMap(FieldContainerPtr fcPtr);
	void writeFileHeader();
	void doIndexFC       (FieldContainerPtr fieldConPtr);
    void doWriteIndexedFC();


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

	FCInfoMap         _fcMap;
	FCTypeIdMap       _fcIdMap;
	BinaryFileHandler _outFileHandler;
    vector<NodePtr>   _vec_pRootNodes;
    
    BINWriter(const BINWriter &source);
    void operator =(const BINWriter &source);

};

OSG_END_NAMESPACE

#define OSG_HEADER_CVSID "@(#)$Id: $"


#endif /* _OSGBINWriter_H_ */
