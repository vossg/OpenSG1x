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

#ifndef _OSGBINWRITER_H_
#define _OSGBINWRITER_H_
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

class OSG_SYSTEMLIB_DLLMAPPING BINWriter
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors/Destructor                    */
    /*! \{                                                                 */

             BINWriter(std::ostream &os);
    virtual ~BINWriter(void      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 write                                        */
    /*! \{                                                                 */

    bool write(            NodePtr  node );
    bool write(std::vector<NodePtr> nodes);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    /*! \hideinhierarchy */
	struct FCInfo
	{
         OSG::IDString     type;
		 FieldContainerPtr ptr;
 		 BitVector         mask; //should match UInt32
		 FCInfo(void);
	};
    //FieldContainerId is of type UInt32
  	typedef std::map<     UInt32,             FCInfo  > FCInfoMap;
    typedef std::map<std::string, std::vector<UInt32> > FCTypeIdMap;

    /*! \hideinhierarchy */

	class BinaryFileHandler : public BinaryDataHandler
    {
	  public:
		BinaryFileHandler(std::ostream &os);
		virtual ~BinaryFileHandler();

		void write(MemoryHandle mem, UInt32 size);

	  private:

		std::vector<UInt8> _writeMemory;
        std::ostream &_os;

        BinaryFileHandler(const BinaryFileHandler &source);
        void operator =(const BinaryFileHandler &source);
	};
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

	void addToIdMap      (FieldContainerPtr fcPtr      );
	void writeFileHeader (void                         );
	void doIndexFC       (FieldContainerPtr fieldConPtr);
    void doWriteIndexedFC(void                         );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name                provate members                               */
    /*! \{                                                                 */

	FCInfoMap            _fcMap;
	FCTypeIdMap          _fcIdMap;
	BinaryFileHandler    _outFileHandler;
    std::vector<NodePtr> _vec_pRootNodes;
    bool                 _valid_stream;

    /*! \}                                                                 */

    BINWriter(const BINWriter &source);
    void operator =(const BINWriter &source);
};

OSG_END_NAMESPACE

#define OSGBINWRITER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGBINWRITER_H_ */
