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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGOSGWriter.h"
#include <OSGAttachment.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif


namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGOSGWriter.cpp,v 1.9 2002/02/28 08:02:39 vossg Exp $";
    static Char8 cvsid_hpp[] = OSGOSGWRITER_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif



#if 0
#if defined(OSG_WIN32_ICL)
#pragma warning (disable : 383)
#endif

#if defined(OSG_WIN32_ICL)
#pragma warning (default : 383)
#endif
#endif

const UInt32 OSGWriter::DefaultSFWidth = TypeConstants<UInt32>::getMax();
const UInt32 OSGWriter::DefaultMFWidth = 60;

/*-------------------------------------------------------------------------*/
/*                             Constructor                                 */

/*! Constructor. Set members to initial values.
 */
OSGWriter::FCInfoHelper::FCInfoHelper(void) :
    written      (false),
    hasName      (false),
    containerName(     )
{
}

/*! Constructor. Set members to initial values.
 */
OSGWriter::OSGWriter(ostream &stream, UInt32 indentStep) :
    _visitedFCMap(                 ),
    _state       (0, DefaultSFWidth),
    _indent      (0, indentStep    ),
    _outStream   (stream           )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor. There are no dynamic members to destroy.
 */
OSGWriter::~OSGWriter(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Methods                                     */

/*! Write a single FieldContainer with all its "children", i.e. everything
 *  that can be reached via Ptr-Fields.
 */
void OSGWriter::write(FieldContainerPtr container)
{
    _visitedFCMap.clear();
    _indent.setIndent(0);

    _outStream << "#OSG V1.0 " << endl;

    visitContainer(container);
    writeContainer(container);
}


/*! Write all FieldContainers in containers with their "children",
 *  i.e. everything that can be reached via Ptr-Fields.
 */
void OSGWriter::write(vector<FieldContainerPtr> containers)
{
    _visitedFCMap.clear();
    _indent.setIndent(0);

    _outStream << "#OSG V1.0 " << endl;

    vector<FieldContainerPtr>::iterator iter = containers.begin();

    for(; iter != containers.end(); ++iter)
    {
        visitContainer( *iter );
    }

    for(iter = containers.begin(); iter != containers.end(); ++iter)
    {
        writeContainer( *iter );
    }
}


/*! Set the name by which this FieldContainer is referenced. If available
 *  a NameAttachment is used, otherwise the name is constructed from
 *  the type name and the container id.
 */
void OSGWriter::FCInfoHelper::setName(const FieldContainerPtr pFC)
{
    const FieldContainerType& fcType = pFC->getType();
    AttachmentContainerPtr pAttCon;
    NamePtr                pNameAtt;

    if(fcType.isDerivedFrom(AttachmentContainer::getClassType()))
    {
        pAttCon = AttachmentContainerPtr::dcast(pFC);
        if(pAttCon != NullFC)
        {
            pNameAtt = NamePtr::dcast(pAttCon->findAttachment(
                Name::getClassType().getGroupId()));

            if(pNameAtt != NullFC)
            {
                containerName = pNameAtt->getFieldPtr()->getValue().c_str();
                return;
            }
        }
    }

    //no NameAttachment. Build name from Type and Id
    containerName = pFC->getTypeName() +
        TypeConstants<UInt32>::putToString(pFC.getFieldContainerId());
}


void OSGWriter::visitContainer(const FieldContainerPtr pFC)
{

    if(pFC == NullFC)
    {
        return;
    }

    typedef pair<FCInfoHelperMap::iterator, bool> MapInsertInfo;

    string containerName;
    const FieldContainerType& fcType    = pFC->getType();
    UInt32              numFields = fcType.getNumFieldDescs();
    MapInsertInfo       insertInfo;

    insertInfo = _visitedFCMap.insert(make_pair(pFC, FCInfoHelper()));
    if(insertInfo.second == true)
    {
        //the FC was NOT visited before
        for(UInt32 field=1; field<=numFields; field++)
        {
            const FieldDescription* fieldDesc =
                fcType.getFieldDescription(field);
            if(fieldDesc->isInternal())
            {
                continue;
            }
            visitField(pFC->getField(field));
        }
    }
    else
    {
        //the FC was in the map => FC is shared
        FCInfoHelperMap::iterator iter = _visitedFCMap.find(pFC);
        if(iter == _visitedFCMap.end())
        {
            SWARNING << "OSGWriter::visitContainer(): FieldContainerPtr "
                     << "not found in map" << endl;
            return;
        }
        if(iter->second.hasName == false)
        {
            iter->second.setName(pFC);
            iter->second.hasName = true;
        }
    }
}

void OSGWriter::visitField(const Field* pF)
{
    if(pF == NULL)
    {
        return;
    }

    const FieldType& fType       = pF->getType();
    const DataType & contentType = pF->getContentType();

    SLOG << contentType.getCName() << endl;

    //handle SFAttachmentMap as special case here
    //if(fType.isDerivedFrom(SFAttachmentMap::getClassType()))
    if(strstr(fType.getCName(), "AttachmentMap") != NULL)
    {
        //visit the Attachment FCs
        SLOG << "Visiting AttachmentMap" << endl;

        const SFAttachmentMap *sfAttMap = (const SFAttachmentMap*) pF;
              AttachmentMap    attMap   = sfAttMap->getValue();

        AttachmentMap::const_iterator iter = attMap.begin();
        AttachmentMap::const_iterator end  = attMap.end();

        for(; iter!=end; ++iter)
        {
            visitContainer(iter->second);
        }
    }
    //else if(contentType.isDerivedFrom(FieldContainerPtr::getClassType()))
    else if(strstr(fType.getCName(), "Ptr") != NULL)
    {
        //this Field points to FC

        //to access the content of a field one must know the cardinality
        if(pF->getCardinality() == FieldType::SINGLE_FIELD)
        {
            const SFFieldContainerPtr* sfFCPtr =
                (const SFFieldContainerPtr*) pF;
            visitContainer(sfFCPtr->getValue());
        }
        else if(pF->getCardinality() == FieldType::MULTI_FIELD)
        {
            const MFFieldContainerPtr* mfFCPtr =
                (const MFFieldContainerPtr*) pF;
            UInt32 mfSize = mfFCPtr->getSize();
            for(UInt32 i=0; i < mfSize; i++)
            {
                visitContainer(mfFCPtr->getValue(i));
            }
        }
    }
}

void OSGWriter::writeContainer(const FieldContainerPtr pFC)
{
    if(pFC == NullFC)
    {
        return;
    }

    const FieldContainerType& fcType    = pFC->getType();
    UInt32              numFields = fcType.getNumFieldDescs();

    FCInfoHelperMap::iterator iter = _visitedFCMap.find(pFC);
    if(iter == _visitedFCMap.end())
    {
        SWARNING << "OSGWriter::writeContainer(): FieldContainerPtr "
                 << "not found in map" << endl;
        return;
    }

    if(!iter->second.written)
    {
        //FC is not written yet
        iter->second.written = true;
        if(iter->second.hasName)
        {
            _outStream << _indent                    << "DEF "
                       << iter->second.containerName << " "
                       << pFC->getTypeName()         << " {"
                       << endl;
        }
        else{
            _outStream << _indent <<  pFC->getTypeName() << " {"
                       << endl;
        }

        _indent++;

        for(UInt32 field=1; field<=numFields; field++)
        {
            const FieldDescription* fieldDesc =
                fcType.getFieldDescription(field);
            if(fieldDesc->isInternal())
            {
                continue;
            }
            writeField(pFC->getField(field), fieldDesc);
        }
        _indent--;
        _outStream << _indent << "}" << endl;
    }
    else
    {
        //FC is already written -> its shared -> write reference
        if(!iter->second.hasName)
        {
            SWARNING << "OSGWriter::writeContainer(): FieldContainer is "
                     << "shared, but not named"
                     << endl;
            return;
        }

        _outStream << _indent << "USE " << iter->second.containerName << endl;
    }

}


void OSGWriter::writeField(const Field* pF, const FieldDescription* fieldDesc)
{

    if(pF == NULL)
    {
        return;
    }

    const FieldType& fType = pF->getType();
    const DataType&  contentType = pF->getContentType();

    //handle SFAttachmentMap as special case here
    //if(fType.isDerivedFrom(SFAttachmentMap::getClassType()))
    if(strstr(fType.getCName(), "AttachmentMap") != NULL)
    {
        //write Attachments
        SLOG << "Writing Attachment Map" << endl;
        
        const SFAttachmentMap *sfAttMap = (const SFAttachmentMap*) pF;
              AttachmentMap    attMap   = sfAttMap->getValue();

        AttachmentMap::const_iterator iter = attMap.begin();
        AttachmentMap::const_iterator end  = attMap.end();

        _outStream << _indent << fieldDesc->getName() << " [ ";
        _indent++;
        _state.setIndent(_indent.getIndent());
        
        //if the Attachment Map is empty write [] as its content
        if(iter==end)
        {
            _outStream << " ] " << endl;
            _indent--; 
        }
        else
        {
            _outStream << endl;
        
            for(; iter!=end; ++iter)
            {
                writeContainer(iter->second);
            }
            _indent--; 
            
            _outStream << _indent << " ] " << endl;
        }
    }
    //else if(contentType.isDerivedFrom(FieldContainerPtr::getClassType()))
    else if(strstr(fType.getCName(), "Ptr") != NULL)
    {
        //this Field points to FC

        _state.setIndent(_indent.getIndent());
        _outStream << _indent << fieldDesc->getName();

        //to access the content of a field via a Field*
        //one must know the cardinality
        if(pF->getCardinality() == FieldType::SINGLE_FIELD)
        {
            const SFFieldContainerPtr* sfFCPtr =
                (const SFFieldContainerPtr*) pF;
            if(sfFCPtr->getValue() == NullFC)
            {
                _outStream << " NULL" << endl;
            }
            else
            {
                _outStream << endl;
                _indent++;
                writeContainer(sfFCPtr->getValue());
                _indent--;
            }
        }
        else if(pF->getCardinality() == FieldType::MULTI_FIELD)
        {
            _outStream << " [" << endl;
            _indent++;
            const MFFieldContainerPtr* mfFCPtr =
                (const MFFieldContainerPtr*) pF;
            UInt32 mfSize = mfFCPtr->getSize();
            for(UInt32 i=0; i < mfSize; i++)
            {
                if(mfFCPtr->getValue(i) == NullFC)
                {
                    _outStream << _indent << "NULL" << endl;
                }
                else
                {
                    writeContainer(mfFCPtr->getValue(i));
                }
            }
            _indent--;
            _outStream << _indent << "]" << endl;
        }
    }
    else
    {
        //this Field contains data -> write it out

        _state.setIndent(_indent.getIndent());
        _outStream << _indent << fieldDesc->getName();

        string fieldValue;

        //to access the content of a field via a Field*
        //one must know the cardinality
        if(pF->getCardinality() == FieldType::SINGLE_FIELD)
        {
            _state.setIndent(0);
            _state.setWidth(DefaultSFWidth);
            pF->getValueByStr(fieldValue, _state);
            _outStream << " " << fieldValue << endl;
        }
        else if(pF->getCardinality() == FieldType::MULTI_FIELD)
        {
            _outStream << " [" << endl;

            _indent++;
            _state.setIndent(_indent.getIndent());
            _state.setWidth(DefaultMFWidth);
            pF->getValueByStr(fieldValue, _state);
            _outStream << fieldValue << endl;
            _indent--;

            _outStream << _indent << "]" << endl;
        }
    }
}






