
#include <OSGConfig.h>

#include <iostream>

#include <OSGFieldContainerFactory.h>
#include <OSGNodePtr.h>
#include <OSGNode.h>
#include <OSGSFNodePtr.h>

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::NodePtr    pNode;
    OSG::SFNodePtr *sfNode;
    OSG::SFInt32   *sfInt;

    pNode  =     OSG::Node::create();
    sfNode = new OSG::SFNodePtr;
    sfInt  = new OSG::SFInt32;

    sfInt->setValue(42);
    sfNode->setValue(pNode);

#define FC_FIELD

#ifdef FC_FIELD
    OSG::Field *pField = sfNode;
#else
    OSG::Field *pField = sfInt;
#endif

    cerr << "CT : " << pField->getContentType().getCName() << endl;

    if(pField->getCardinality() == OSG::FieldType::SINGLE_FIELD)
    {
        cerr << "SField " << endl;

        if(pField->getContentType() == 
           OSG::FieldDataTraits<OSG::NodePtr>::getType())
        {
            OSG::SFNodePtr *pSField    = static_cast<OSG::SFNodePtr *>(pField);
            
            OSG::FieldContainerPtr pFC = pSField->getValue();
                        
            if(pFC != OSG::NullFC)
            {
                cerr << "Got empty FC " << endl;
            }
            else
            {
                cerr << "Got valid FC" << endl;
            }
        }
        else
        {
            cerr << "Field contais no container " << endl;
        }
    }
    else
    {
        cerr << "MField " << endl;
    }

    return 0;
}

