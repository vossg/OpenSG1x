

#include "MaterialPool.h"
#include <OpenSG/OSGSimpleGeometry.h>

OSG_USING_NAMESPACE;
using namespace std;


// static map
std::vector<OSG::MaterialPtr> MaterialPool::_mats;

MaterialPool* MaterialPool::_the = NULL;    

MaterialPool::MaterialPool()
{
}

MaterialPool::~MaterialPool()
{
}

bool isEqual(const osg::FieldContainerPtr& a, const osg::FieldContainerPtr& b)
{
    using std::string;

    // Compare the pointers.
    if(a == b)
        return true;

    if(a == NullFC || b == NullFC)
        return false;

    if(a->getType() != b->getType())
        return false;
    
    //printf("comparing: %s\n", a->getType().getName().str());
    
    const FieldContainerType &type = a->getType();
    UInt32 fcount = type.getNumFieldDescs();
    
    for(UInt32 i=1;i <= fcount;++i)
    {
        const FieldDescription* fdesc = type.getFieldDescription(i);
    
        if(fdesc->isInternal())
            continue;
    
        // ignore attachments
        if(strcmp(fdesc->getCName(), "attachments") == 0)
            continue;
    
        Field *a_field = a->getField(i);
        Field *b_field = b->getField(i);
    
        const FieldType &a_ftype = a_field->getType();
        const FieldType &b_ftype = b_field->getType();
    
        //printf("comparing field %s\n", a_ftype.getCName());
    
        if(a_ftype != b_ftype)
            return false;
    
        if(strstr(a_ftype.getCName(), "Ptr") == NULL)
        {
            // This would be nice but there is no virtual compare method :-(
            // if(*a_field != *b_field)
            //     return false;
    
            // This is very slow with multi fields!!!!
            string av, bv;
            a_field->getValueByStr(av);
            b_field->getValueByStr(bv);
            if(av != bv)
                return false;
        }
        else
        {
            if(a_field->getCardinality() == FieldType::SINGLE_FIELD)
            {
                if(!isEqual(((SFFieldContainerPtr *) a_field)->getValue(),
                            ((SFFieldContainerPtr *) b_field)->getValue()))
                    return false;
            }
            else if(a_field->getCardinality() == FieldType::MULTI_FIELD)
            {
                if(((MFFieldContainerPtr*)a_field)->size() !=
                   ((MFFieldContainerPtr*)b_field)->size())
                    return false;
    
                for(UInt32 j=0;j < ((MFFieldContainerPtr*)a_field)->size();++j)
                {
                    if(!isEqual((*(((MFFieldContainerPtr *)a_field)))[j],
                                (*(((MFFieldContainerPtr *)b_field)))[j]))
                        return false;
                }
            }
        }
    }
    return true;
}


bool equal(MaterialPtr a, MaterialPtr b) {
    // It's too bad Material::operator== doesn't work.
    //return *a == *b;
    return isEqual(a, b);
}

OSG::UInt32 MaterialPool::addMaterial(OSG::MaterialPtr mat)
{
    if(_the == NULL)
    {
        _the = new MaterialPool;
        
        // add the default material as index 0
        addMaterial(getDefaultMaterial());      
    }
       
    vector<OSG::MaterialPtr>::iterator it, end;
    
    end = _mats.end();
    
    UInt32 ind = 0;
    for (it = _mats.begin(); it != end; ++it, ++ind)
    {
        if(equal(*it, mat))
        {
            return ind;
        }
    }
    
    ind = _mats.size();
    _mats.push_back(mat);
    addRefCP(mat);
    
    return ind;
}

OSG::MaterialPtr MaterialPool::getMaterial(OSG::UInt32 ind)
{
    if(_the == NULL)
    {
        _the = new MaterialPool;
        
        // add the default material as index 0
        addMaterial(getDefaultMaterial());      
    }

    return _mats[ind];
}


