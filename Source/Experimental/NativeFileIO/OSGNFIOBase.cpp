/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

// Header format
// "OpenSG binary V1.0"(std::string)<Name>(string)<Options>(string)<Size>(UInt64)
// For each FieldContainer:
// <FieldContainerType>(std::string)<FieldContainerId>(UInt32)
// "" empty FieldContainerType string as file endmarker.

#include <OSGConfig.h>
#include "OSGNFIOBase.h"

#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGSimpleAttachments.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGSceneFileHandler.h>

#include <OSGLog.h>

#include "OSGNFIOFactory.h"

// never change the length of the header!
#define OSGNFIOHEADERID "OpenSG binary V1.0"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NFIOBase
           Base class for native file io.
 */

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NFIOOptions                     NFIOBase::_options;

NFIOBase::BinaryReadHandler     *NFIOBase::_in = NULL;
NFIOBase::BinaryWriteHandler    *NFIOBase::_out = NULL;

NFIOBase::fcMap                 NFIOBase::_fcMap;
std::list<NFIOBase::fcInfo>     NFIOBase::_fieldList;

std::list<FieldContainerPtr>    NFIOBase::_fcList;
std::set<UInt32>                NFIOBase::_fcSet;

std::set<FieldContainerPtr>     NFIOBase::_added_cores;

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOBase::NFIOBase(const char *name) :
    _version(100)
{
    NFIOFactory::the().add(name, this);
}

/*------------------------------ destructor -------------------------------*/

NFIOBase::~NFIOBase()
{
    NFIOFactory::the().sub(this);
}

NodePtr NFIOBase::read(std::istream &is, const std::string &options)
{
    if(!isOSB(is))
    {
        FWARNING(("NFIOBase::read : Couldn't load file "
                  "this is not a '%s' format\n", OSGNFIOHEADERID));
        return NullFC;
    }

    _options.init(options);

    _in = new BinaryReadHandler(is);
    
    NodePtr node = NullFC;
    
    FieldContainerPtr fc = readFieldContainer();
    node = NodePtr::dcast(fc);
    fillAttachmentParents(node);

    delete _in;

    return node;
}

bool NFIOBase::write(const NodePtr &node, std::ostream &os,
                     const std::string &options)
{
    _options.init(options);
    
    _out = new BinaryWriteHandler(os);

    writeFieldContainer(node);
    
    _out->flush();
    delete _out;
    
    return true;
}

FieldContainerPtr NFIOBase::readFC(std::istream &is,
                                   const std::string &options)
{
    _options.init(options);

    _in = new BinaryReadHandler(is);

    FieldContainerPtr fc = readFieldContainer();

    delete _in;

    return fc;
}

bool NFIOBase::writeFC(const FieldContainerPtr &fc,
                       std::ostream &os,
                       const std::string &options)
{
    _options.init(options);
    
    _out = new BinaryWriteHandler(os);

    writeFieldContainer(fc);
    
    _out->flush();
    delete _out;
    
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                            Options                                      *
\***************************************************************************/

const NFIOOptions &NFIOBase::getOptions(void)
{
    return _options;
}

/***************************************************************************\
 *                            Reader                                       *
\***************************************************************************/

bool NFIOBase::isOSB(std::istream &is)
{
    // ok the first 4 bytes of the osb file are
    // the length of the osb header!
    const int osb_magic[6] = {0, 0, 0, sizeof(OSGNFIOHEADERID), 'O', 'p'};

    int c1 = (int) is.get();
    if(c1 != osb_magic[0])
    {
        is.putback(c1);
        return false;
    }

    int c2 = (int) is.get();
    if(c2 != osb_magic[1])
    {
        is.putback(c2);
        is.putback(c1);
        return false;
    }

    int c3 = (int) is.get();
    if(c3 != osb_magic[2])
    {
        is.putback(c3);
        is.putback(c2);
        is.putback(c1);
        return false;
    }

    int c4 = (int) is.get();
    if(c4 != osb_magic[3])
    {
        is.putback(c4);
        is.putback(c3);
        is.putback(c2);
        is.putback(c1);
        return false;
    }

    int c5 = (int) is.get();
    if(c5 != osb_magic[4])
    {
        is.putback(c5);
        is.putback(c4);
        is.putback(c3);
        is.putback(c2);
        is.putback(c1);
        return false;
    }

    int c6 = (int) is.get();
    if(c6 != osb_magic[5])
    {
        is.putback(c6);
        is.putback(c5);
        is.putback(c4);
        is.putback(c3);
        is.putback(c2);
        is.putback(c1);
        return false;
    }

    is.putback(c6);
    is.putback(c5);
    is.putback(c4);
    is.putback(c3);
    is.putback(c2);
    is.putback(c1);
    return true;
}

FieldContainerPtr NFIOBase::readFieldContainer(void)
{
    FDEBUG(("NFIOBase::readFieldContainer\n"));

    _fieldList.clear();
    _fcMap.clear();

    // read header
    std::string hid;
    _in->getValue(hid);
    if(hid != OSGNFIOHEADERID)
    {
        FWARNING(("NFIOBase::readFieldContainer : Couldn't load file "
                  "this is not a '%s' format\n", OSGNFIOHEADERID));
        return NullFC;
    }
    
    std::string hname;
    _in->getValue(hname);
    std::string hoptions;
    _in->getValue(hoptions);
    UInt64 hsize;
    _in->getValue(hsize);

    std::string typeName;
    UInt32 id;
    FieldContainerPtr root = NullFC;
    FieldContainerPtr fc = NullFC;
    
    while(true)
    {
        // read fieldcontainer type.
        _in->getValue(typeName);

        if(typeName.empty()) // check for eof.
            break;
        
        // read fieldcontainer id
        _in->getValue(id);

        FDEBUG(("NFIOBase::readFieldContainer %s\n", typeName.c_str()));
    
        // get the reader.
        fc = NFIOFactory::the().get(typeName)->readFC(typeName);
        
        if(fc != NullFC)
            addReadFieldContainer(fc, id);
        
        if(root == NullFC) // first fc is the root node.
            root = fc;
        SceneFileHandler::the().updateReadProgress();
    }

    SceneFileHandler::the().updateReadProgress();

    // process all SF/MFFieldContainerPtr
    for(std::list<fcInfo>::iterator i = _fieldList.begin();
        i != _fieldList.end(); ++i)
    {
        chargeFieldPtr(*i);
    }

    _fieldList.clear();
    _fcMap.clear();

    SceneFileHandler::the().updateReadProgress(100);

    return root;
}

void NFIOBase::chargeFieldPtr(const fcInfo &info)
{
    FieldContainerType  &fcType = info._fc->getType();
    Field *field = info._field;

    if(!info.isMultiField())
    {
        FieldContainerPtr fc = NullFC;
        
        UInt32 id = info._id;
        if(id != 0)
        {
            fcMap::iterator it = _fcMap.find(id);
            if(it == _fcMap.end())
            {
                FWARNING(("NFIOBase::chargeFieldPtr: couldn't find "
                          "FieldContainer with id %u\n", id));
                return;
            }
            fc = (*it).second;
            if(fc == NullFC)
                return;
        }
    
        beginEditCP(info._fc, info._mask);
            if(fc != NullFC && fcType.isNode() &&
               info._mask == Node::CoreFieldMask)
            {
                NodePtr node = NodePtr::dcast(info._fc);
                node->setCore(NodeCorePtr::dcast(fc));
            }
            else
            {
                addRefCP(fc); // increment ref count
                ((SFFieldContainerPtr *) field)->setValue(fc);
            }
        endEditCP(info._fc, info._mask);
    }
    else
    {
        if(info._ids.empty())
            return;

        NodePtr node = NodePtr::dcast(info._fc);
        //fcType == Node::getClassType()
        AttachmentContainerPtr attContainer = AttachmentContainerPtr::dcast(info._fc);
        bool attachment = false;
        if(attContainer != NullFC &&
           info._mask == AttachmentContainer::AttachmentsFieldMask)
        {
            attachment = true;
        }
        
        beginEditCP(info._fc, info._mask);
        bool has_ids_binding = (info._ids.size() == info._ids_binding.size());
        for(UInt32 i=0;i<info._ids.size();++i)
        {
            UInt32 id = info._ids[i];
            FieldContainerPtr fc = NullFC;
            if(id != 0)
            {
                fcMap::iterator it = _fcMap.find(id);
                if(it == _fcMap.end())
                {
                    FWARNING(("NFIOBase::chargeFieldPtr: couldn't find "
                              "FieldContainer with id %u\n", id));
                    continue;
                }
                fc = (*it).second;
                if(fc == NullFC)
                    continue;
            }
            
            if(node != NullFC && info._mask == Node::ChildrenFieldMask)
            {
                node->addChild(NodePtr::dcast(fc));
            }
            else if(attachment)
            {
                AttachmentPtr pAtt  = AttachmentPtr::dcast(fc);
                if(has_ids_binding)
                    attContainer->addAttachment(pAtt, info._ids_binding[i]);
                else
                    attContainer->addAttachment(pAtt);
            }
            else
            {
                addRefCP(fc); // increment ref count
                ((MFFieldContainerPtr *) field)->push_back(fc);
            }
        }
        endEditCP(info._fc, info._mask);
    }
}

void NFIOBase::addReadFieldContainer(const FieldContainerPtr &fc, UInt32 id)
{
    _fcMap.insert(std::pair<UInt32, FieldContainerPtr>(id, fc));
}

std::string NFIOBase::readFCFields(const FieldContainerPtr &fc,
                                   const std::string &exclude,
                                   const std::string &endMarkers)
{
    FieldContainerType  &fcType = fc->getType();

    std::string fieldName;
    while(true)
    {
        _in->getValue(fieldName);
        // check for fieldcontainer end marker.
        if(fieldName.empty() || (!endMarkers.empty() &&
                                 endMarkers.find("'" + fieldName + "'") != std::string::npos))
        {
            FDEBUG(("NFIOBase::readFCPtr: found fieldcontainer end marker.\n"));
            break;
        }
        
        std::string fieldType;
        _in->getValue(fieldType);
        UInt32 size;
        _in->getValue(size);
        
        FDEBUG(("NFIOBase::readFCPtr: field: '%s' '%s' %u\n",
                fieldName.c_str(), fieldType.c_str(), size));
        
        Field *field = fc->getField(fieldName.c_str());
        FieldDescription *fDesc = fcType.findFieldDescription(fieldName.c_str());
        BitVector mask;
        if(fDesc != NULL)
        {
            mask = fDesc->getFieldMask();
            // now check for the same type, ok nobody should change a field type but ...
            if(fieldType != field->getType().getCName())
            {
                // for equal sizes try to read it, could be a type change from UInt32 to Int32
                // and that's tolerable.
                FWARNING(("NFIOBase::readFCPtr: found conflicting field types field '%s' with "
                            "types '%s' and '%s'!\n", fieldName.c_str(),
                            fieldType.c_str(), field->getType().getCName()));

                if(size != fc->getBinSize(mask))
                {
                    // ok in this case we skip the field!
                    FFATAL(("NFIOBase::readFCPtr: found conflicting field types with different sizes skipping field '%s' with "
                            "types '%s' and '%s'!\n", fieldName.c_str(),
                            fieldType.c_str(), field->getType().getCName()));
                    _in->skip(size);
                    continue;
                }
            }
        }
        else
        {
            FNOTICE(("NFIOBase::readFCPtr: skipping unknown field '%s' with "
                      "type '%s'!\n", fieldName.c_str(),
                      fieldType.c_str()));
            _in->skip(size);
            continue;
        }

        if(!exclude.empty() && exclude.find("'" + fieldName + "'") != std::string::npos)
        {
            FDEBUG(("NFIOBase::readFCPtr: skipping field '%s'!\n",
                    fieldName.c_str()));
            _in->skip(size);
            continue;
        }
        
        
        if(strstr(fieldType.c_str(), "Ptr") != NULL)
        {
            if(fieldType[0] == 'S' && fieldType[1] == 'F') // single field
            {
                readSFFieldContainerPtr(fc, mask, field);
            }
            else if(fieldType[0] == 'M' && fieldType[1] == 'F') // multi field
            {
                UInt32 noe;
                _in->getValue(noe);
                readMFFieldContainerPtr(fc, mask, field, noe);
            }
        }
        else if(!strcmp(fieldName.c_str(), "attachments"))
        {
            UInt32 noe;
            _in->getValue(noe);
            // old buggy format without binding info but we want to keep the
            // osb format backward and forward compatible!
            if(size == sizeof(UInt32) + sizeof(UInt32) * noe)
                readMFFieldContainerPtr(fc, mask, field, noe);
            else
                readSFAttachmentMap(fc, mask, field, noe);
        }
        else
        {
            beginEditCP(fc, mask);
                fc->copyFromBin(*_in, mask);
            endEditCP(fc, mask);
        }
    }
    return fieldName;
}


void NFIOBase::readSFFieldContainerPtr(const FieldContainerPtr &fc,
                                       const BitVector &mask, Field *field)
{
    UInt32 id;
    _in->getValue(id);
    _fieldList.push_back(fcInfo(fc, mask, id, field));
}


void NFIOBase::readMFFieldContainerPtr(const FieldContainerPtr &fc,
                                       const BitVector &mask, Field *field,
                                       UInt32 noe)
{
    _fieldList.push_back(fcInfo(fc, mask, field));
    fcInfo &info = _fieldList.back();
    UInt32 id;
    for(UInt32 j=0;j<noe;++j)
    {
        _in->getValue(id);
        info._ids.push_back(id);
    }
}

void NFIOBase::readSFAttachmentMap(const FieldContainerPtr &fc,
                                   const BitVector &mask, Field *field,
                                   UInt32 noe)
{
    _fieldList.push_back(fcInfo(fc, mask, field));
    fcInfo &info = _fieldList.back();
    UInt32 id;
    for(UInt32 j=0;j<noe;++j)
    {
        _in->getValue(id);
        info._ids.push_back(id);
    }

    UInt16 id_binding;
    for(UInt32 j=0;j<noe;++j)
    {
        _in->getValue(id_binding);
        info._ids_binding.push_back(id_binding);
    }
}

/***************************************************************************\
 *                            Writer                                       *
\***************************************************************************/

void NFIOBase::getFCCount(const FieldContainerPtr &fc, UInt32 &count)
{
    if(fc == NullFC)
        return;

    if(_fcSet.count(fc.getFieldContainerId()) > 0)
        return;

    _fcSet.insert(fc.getFieldContainerId());
    ++count;

    FieldContainerType  &fcType = fc->getType();
    
    //go through all fields
    for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
    {
        FieldDescription    *fDesc = fcType.getFieldDescription(i);
        Field               *fieldPtr = fc->getField(i);
        const FieldType     &fType = fieldPtr->getType();

        if(!fDesc->isInternal())
        {
            // ignore node volume
            if(fcType == Node::getClassType() &&
               fDesc->getFieldMask() == Node::VolumeFieldMask)
            {
                continue;
            }
            
            FDEBUG(("NFIOBase::getFCCount: field: '%s' '%s'\n",
                    fDesc->getCName(), fType.getCName()));

            if(strstr(fType.getCName(), "Ptr") != NULL)
            {
                if(fieldPtr->getCardinality() == FieldType::SINGLE_FIELD)
                {
                    getFCCount(((SFFieldContainerPtr *) fieldPtr)->getValue(), count);
                }
                else if(fieldPtr->getCardinality() == FieldType::MULTI_FIELD)
                {
                    MFFieldContainerPtr *mfield = (MFFieldContainerPtr *) fieldPtr;
                    UInt32 noe = mfield->size();
                    for(UInt32 i = 0; i < noe; ++i)
                    {
                        getFCCount((*(mfield))[i], count);
                    }
                }
                
            }
            else if(!strcmp(fDesc->getCName(), "attachments"))
            {
                SFAttachmentMap *amap = (SFAttachmentMap *) fieldPtr;
                
                AttachmentMap::const_iterator   mapIt = amap->getValue().begin();
                AttachmentMap::const_iterator   mapEnd = amap->getValue().end();
                
                UInt32 noe = amap->getValue().size();
                for(; mapIt != mapEnd; ++mapIt)
                {
                    getFCCount(mapIt->second, count);
                }
            }
        }
    }
}

void NFIOBase::writeFieldContainer(const FieldContainerPtr &fc)
{
    FDEBUG(("NFIOBase::writeFieldContainer\n"));
    
    if(fc == NullFC)
        return;

    SceneFileHandler::the().updateWriteProgress(0);

    // need this for the progress calculation.
    UInt32 fcCount = 0;
    UInt32 currentFCCount = 0;
    if(SceneFileHandler::the().getWriteProgressCB() != NULL)
    {
        _fcSet.clear();
        getFCCount(fc, fcCount);
    }

    if(fcCount == 0)
        fcCount = 1;

    _fcList.clear();
    _fcSet.clear();
    
    // write header
    _out->putValue(std::string(OSGNFIOHEADERID));
    _out->putValue(std::string(""));
    _out->putValue(std::string(""));
    _out->putValue((UInt64) 0);
    
    std::string typeName = fc->getType().getCName();
    
    _out->putValue(typeName);
    _out->putValue(fc.getFieldContainerId());
    
    NFIOFactory::the().get(typeName)->writeFC(fc);
    SceneFileHandler::the().updateWriteProgress((currentFCCount++ * 100) / fcCount);

    FDEBUG(("NFIOBase::writeFC: writing fclist\n"));

    FieldContainerPtr lfc;
    for(std::list<FieldContainerPtr>::iterator i = _fcList.begin();
        i != _fcList.end(); ++i)
    {
        lfc = *i;
        typeName = lfc->getType().getCName();
        _out->putValue(typeName);
        _out->putValue(lfc.getFieldContainerId());
        NFIOFactory::the().get(lfc->getType().getCName())->writeFC(lfc);
        SceneFileHandler::the().updateWriteProgress((currentFCCount++ * 100) / fcCount);
    }
    
    // write eof marker
    writeEndMarker();

    _fcList.clear();
    _fcSet.clear();

    SceneFileHandler::the().updateWriteProgress(100);
}

void NFIOBase::writeFCFields(const FieldContainerPtr &fc,
                             const std::string &exclude,
                             bool endMarker)
{
    FieldContainerType  &fcType = fc->getType();
    
    //go through all fields
    for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
    {
        FieldDescription    *fDesc = fcType.getFieldDescription(i);
        Field               *fieldPtr = fc->getField(i);
        const FieldType     &fType = fieldPtr->getType();
        BitVector           mask = fDesc->getFieldMask();

        if(!fDesc->isInternal())
        {
            // ignore node volume
            if(fcType == Node::getClassType() &&
               fDesc->getFieldMask() == Node::VolumeFieldMask)
            {
                continue;
            }
            
            FDEBUG(("NFIOBase::writeFCPtr: field: '%s' '%s'\n",
                    fDesc->getCName(), fType.getCName()));
            std::string fieldName = fDesc->getCName();
            std::string fieldType = fType.getCName();
            
            if(!exclude.empty() && exclude.find("'" + fieldName + "'") != std::string::npos)
            {
                FDEBUG(("NFIOBase::writeFields: skipping field: '%s'.\n",
                        fieldName.c_str()));
                continue;
            }
            
            if(strstr(fType.getCName(), "Ptr") != NULL)
            {
                if(fieldPtr->getCardinality() == FieldType::SINGLE_FIELD)
                {
                    _out->putValue(fieldName);
                    _out->putValue(fieldType);
                    _out->putValue(fc->getBinSize(mask));
                    writeSFFieldContainerPtr((SFFieldContainerPtr *) fieldPtr);
                }
                else if(fieldPtr->getCardinality() == FieldType::MULTI_FIELD)
                {
                    MFFieldContainerPtr *mfield = (MFFieldContainerPtr *) fieldPtr;
                    if(!mfield->empty())
                    {
                        UInt32 size = sizeof(UInt32) + sizeof(UInt32) * mfield->size();
                        _out->putValue(fieldName);
                        _out->putValue(fieldType);
                        _out->putValue(size);
                        
                        writeMFFieldContainerPtr(mfield);
                    }
                }
                
            }
            else if(!strcmp(fDesc->getCName(), "attachments"))
            {
                SFAttachmentMap *amap = (SFAttachmentMap *) fieldPtr;
                
                if(!amap->getValue().empty())
                {
                    UInt32 size = sizeof(UInt32) + sizeof(UInt32) * amap->getValue().size();

                    // check for non zero bindings
                    AttachmentMap::const_iterator mapIt = amap->getValue().begin();
                    AttachmentMap::const_iterator   mapEnd = amap->getValue().end();

                    UInt16 id_binding = 0;
                    for(; mapIt != mapEnd; ++mapIt)
                    {
                        id_binding = UInt16(mapIt->first & 0x0000ffff);
                        if(id_binding != 0)
                            break;
                    }
    
                    if(id_binding != 0)
                        size += sizeof(UInt16) * amap->getValue().size();

                    _out->putValue(fieldName);
                    _out->putValue(fieldType);
                    _out->putValue(size);
                    writeSFAttachmentMap(amap);
                }
            }
            else
            {
                _out->putValue(fieldName);
                _out->putValue(fieldType);
                _out->putValue(fc->getBinSize(mask));
                fc->copyToBin(*_out, mask);
            }
            
        }
    }
    
    if(endMarker)
    {
        // write fieldcontainer end marker
        writeEndMarker();
    }
}

void NFIOBase::writeSFFieldContainerPtr(SFFieldContainerPtr *field)
{
    writeFCId(field->getValue());
}


void NFIOBase::writeMFFieldContainerPtr(MFFieldContainerPtr *field)
{
    UInt32 noe = field->size();
    _out->putValue(noe);
    for(UInt32 i = 0; i < noe; ++i)
    {
        writeFCId((*(field))[i]);
    }
}

void NFIOBase::writeSFAttachmentMap(SFAttachmentMap *amap)
{
    AttachmentMap::const_iterator   mapIt = amap->getValue().begin();
    AttachmentMap::const_iterator   mapEnd = amap->getValue().end();
    
    UInt32 noe = amap->getValue().size();
    _out->putValue(noe);

    for(; mapIt != mapEnd; ++mapIt)
    {
        writeFCId(mapIt->second);
    }

    // check for non zero bindings
    UInt16 id_binding = 0;
    mapIt = amap->getValue().begin();
    for(; mapIt != mapEnd; ++mapIt)
    {
        id_binding = UInt16(mapIt->first & 0x0000ffff);
        if(id_binding != 0)
            break;
    }

    // we write the binding only if we have a non zero binding
    // to keep it compatible to the old format!
    if(id_binding != 0)
    {
        mapIt = amap->getValue().begin();
        for(; mapIt != mapEnd; ++mapIt)
        {
            id_binding = UInt16(mapIt->first & 0x0000ffff);
            _out->putValue(id_binding);
        }
    }

}

void NFIOBase::readEndMarker(void)
{
    // end marker a empty field or fieldcontainer type name.
    std::string endMarker;
    _in->getValue(endMarker);
}

void NFIOBase::writeEndMarker(void)
{
    // end marker a empty field or fieldcontainer type name.
    _out->putValue(std::string("")); 
}

void NFIOBase::writeFCId(const FieldContainerPtr &fc)
{
    if(fc == NullFC)
    {
        _out->putValue((UInt32) 0);
        return;
    }
    
    UInt32 id = fc.getFieldContainerId();
    _out->putValue(id);
    
    if(_fcSet.count(id) == 0)
    {
        _fcSet.insert(id);
        _fcList.push_back(fc);
    }
}

void NFIOBase::skipFCFields(void)
{
    // skip all fields
    std::string fieldName;
    std::string fieldType;
    UInt32 size;
    while(true)
    {
        _in->getValue(fieldName);
        // check for fieldcontainer end marker.
        if(fieldName.empty())
        {
            FDEBUG(("NFIOBase::skipFCFields: found fieldcontainer end marker.\n"));
            break;
        }
        
        _in->getValue(fieldType);
        _in->getValue(size);

        _in->skip(size);
    }
}

Action::ResultE NFIOBase::clearAttachmentParent(NodePtr &node)
{
    if(node == NullFC)
        return Action::Continue;

    FieldContainerPtr fc = node->getCore();

    if(fc == NullFC)
        return Action::Continue;

    // the core could be shared this would lead to duplicated parent entries.
    if(_added_cores.count(fc) == 1)
        return Action::Continue;

    _added_cores.insert(fc);

    FieldContainerType  &fcType = fc->getType();

    //go through all fields
    for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
    {
        FieldDescription    *fDesc = fcType.getFieldDescription(i);
        Field               *fieldPtr = fc->getField(i);
        const FieldType     &fType = fieldPtr->getType();
        std::string         fieldType = fType.getCName();
        BitVector           mask = fDesc->getFieldMask();

        if(fDesc->isInternal())
        {
            continue;
        }

        if(strstr(fieldType.c_str(), "Ptr") != NULL)
        {
            if(fieldType[0] == 'S' && fieldType[1] == 'F') // single field
            {
                AttachmentPtr attachment =
                    AttachmentPtr::dcast(((SFFieldContainerPtr *) fieldPtr)
                    ->getValue());
                if(attachment != NullFC)
                {
                    fc.setParentFieldPos(fDesc->getFieldId());
                    beginEditCP(attachment, Attachment::ParentsFieldMask);
                        attachment->getParents().clear();
                    endEditCP(attachment, Attachment::ParentsFieldMask);
                }
            }
            else if(fieldType[0] == 'M' && fieldType[1] == 'F') // multi field
            {
                MFFieldContainerPtr *mfield = (MFFieldContainerPtr *) fieldPtr;
                UInt32 noe = mfield->size();
                for(UInt32 j = 0; j < noe; ++j)
                {
                    AttachmentPtr attachment =
                        AttachmentPtr::dcast((*(mfield))[j]);
                    if(attachment != NullFC)
                    {
                        fc.setParentFieldPos(fDesc->getFieldId());
                        beginEditCP(attachment, Attachment::ParentsFieldMask);
                            attachment->getParents().clear();
                        endEditCP(attachment, Attachment::ParentsFieldMask);
                    }
                }
            }
        }
    }

    return Action::Continue;
}

Action::ResultE NFIOBase::addAttachmentParent(NodePtr &node)
{
    if(node == NullFC)
        return Action::Continue;

    FieldContainerPtr fc = node->getCore();

    if(fc == NullFC)
        return Action::Continue;

    // the core could be shared this would lead to duplicated parent entries.
    if(_added_cores.count(fc) == 1)
        return Action::Continue;

    _added_cores.insert(fc);

    FieldContainerType  &fcType = fc->getType();

    //go through all fields
    for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
    {
        FieldDescription    *fDesc = fcType.getFieldDescription(i);
        Field               *fieldPtr = fc->getField(i);
        const FieldType     &fType = fieldPtr->getType();
        std::string         fieldType = fType.getCName();
        BitVector           mask = fDesc->getFieldMask();

        if(fDesc->isInternal())
        {
            continue;
        }

        if(strstr(fieldType.c_str(), "Ptr") != NULL)
        {
            if(fieldType[0] == 'S' && fieldType[1] == 'F') // single field
            {
                AttachmentPtr attachment =
                    AttachmentPtr::dcast(((SFFieldContainerPtr *) fieldPtr)
                    ->getValue());
                if(attachment != NullFC)
                {
                    fc.setParentFieldPos(fDesc->getFieldId());
                    beginEditCP(attachment, Attachment::ParentsFieldMask);
                        attachment->addParent(fc);
                    endEditCP(attachment, Attachment::ParentsFieldMask);
                }
            }
            else if(fieldType[0] == 'M' && fieldType[1] == 'F') // multi field
            {
                MFFieldContainerPtr *mfield = (MFFieldContainerPtr *) fieldPtr;
                UInt32 noe = mfield->size();
                for(UInt32 j = 0; j < noe; ++j)
                {
                    AttachmentPtr attachment =
                        AttachmentPtr::dcast((*(mfield))[j]);
                    if(attachment != NullFC)
                    {
                        fc.setParentFieldPos(fDesc->getFieldId());
                        beginEditCP(attachment, Attachment::ParentsFieldMask);
                            attachment->addParent(fc);
                        endEditCP(attachment, Attachment::ParentsFieldMask);
                    }
                }
            }
        }
    }

    return Action::Continue;
}

void NFIOBase::fillAttachmentParents(const NodePtr &node)
{
    if(node == NullFC)
        return;

    _added_cores.clear();
    // for some reason the geometry indices parents field is not empty.
    traverse(node, osgTypedFunctionFunctor1CPtrRef<Action::ResultE,
             NodePtr>(clearAttachmentParent));
    _added_cores.clear();
    traverse(node, osgTypedFunctionFunctor1CPtrRef<Action::ResultE,
             NodePtr>(addAttachmentParent));
    _added_cores.clear();
}


/*-------------------------------------------------------------------------*/
/*                           fcInfo struct                                 */

NFIOBase::fcInfo::fcInfo(const FieldContainerPtr &fc, const BitVector &mask,
                         UInt32 id, Field *field) :
    _fc(fc),
    _mask(mask),
    _id(id),
    _field(field),
    _ids(),
    _ids_binding()
{
}

NFIOBase::fcInfo::fcInfo(const FieldContainerPtr &fc, const BitVector &mask,
                         Field *field) :
    _fc(fc),
    _mask(mask),
    _id(0),
    _field(field),
    _ids(),
    _ids_binding()
{
}

bool NFIOBase::fcInfo::isMultiField(void) const
{
    return (_id == 0);
}


/*-------------------------------------------------------------------------*/
/*                              BinaryReadHandler                          */

/*! constructor
 */
NFIOBase::BinaryReadHandler::BinaryReadHandler(std::istream &is) :
    BinaryDataHandler(1),
    _is(is)
{
    _readMemory.resize(8192);
    readBufAdd(&_readMemory[0], _readMemory.size());
}

/*! destructor
 */
NFIOBase::BinaryReadHandler::~BinaryReadHandler(void)
{
}

/*! read
 */
void NFIOBase::BinaryReadHandler::read(MemoryHandle mem, UInt32 size)
{
    _is.read((char *) mem, size);
}

void NFIOBase::BinaryReadHandler::skip(UInt32 size)
{
    if(size == 0)
        return;

    char b;
    for(UInt32 i=0;i<size;++i)
        get((void *) &b, 1);
}

/*-------------------------------------------------------------------------*/
/*                           BinaryWriteHandler                             */

/*! constructor
 */
NFIOBase::BinaryWriteHandler::BinaryWriteHandler(std::ostream &os) :
    BinaryDataHandler(1),
    _os(os)
{
    _writeMemory.resize(8192);
    writeBufAdd(&_writeMemory[0], _writeMemory.size());
}

/*! destructor
 */
NFIOBase::BinaryWriteHandler::~BinaryWriteHandler(void)
{
}

/*! write to binary file
 */
void NFIOBase::BinaryWriteHandler::write(MemoryHandle mem, UInt32 size)
{
    _os.write((const char *) mem, size);
}



/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNFIOBase.cpp,v 1.14 2007/03/26 08:47:42 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGNFIOBASE_HEADER_CVSID;
}
