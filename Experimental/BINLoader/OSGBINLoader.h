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

#ifndef _OSGBINLoader_H_
#define _OSGBINLoader_H_
#ifdef __sgi
#pragma once
#endif
#include <OSGConfig.h>
#include <map>
#include <vector>
#include <OSGNode.h>
#include <OSGBinaryDataHandler.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING BINLoader
{
    /*==========================  PUBLIC  =================================*/

	public:
		void read();
        NodePtr         getRootNode();
        vector<NodePtr> getRootNodes();
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
		BINLoader(FILE *file);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
		virtual ~BINLoader();

       
    /*=========================  PROTECTED  ===============================*/
	protected:
    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */
		
	    struct FCInfoStruct
	    {
		   UInt32            newId;
		   FieldContainerPtr ptr;
           bool              read; 
           FCInfoStruct();
		};
		//          oldID	newId + FCPtr
		typedef map<UInt32, FCInfoStruct> IDLookupMap;

		struct FCIdMapper:public FieldContainerMapper
        {                                              
            const IDLookupMap *ptrMap;
			FCIdMapper(IDLookupMap *m);

			virtual UInt32 map(UInt32 uiId);
        };

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
    	};

         
    /*==========================  PRIVATE  ================================*/
	private:
    	BinaryFileHandler _inFileHandler;
    	IDLookupMap       _fcInfoMap;
		UInt32            _countContainers;
        vector<NodePtr>   _vec_pRootNodes;
		void createFieldContainers();
		void chargeFieldContainers();

};

OSG_END_NAMESPACE

#define OSGBINLOADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGBINLoader_H_ */
