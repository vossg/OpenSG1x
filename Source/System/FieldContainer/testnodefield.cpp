
#include <OSGConfig.h>

#ifdef WIN32

#include <stdio.h>
int main (int , char **)
{
    fprintf(stderr,"testnodefield: not supported on Windows!\n");
    return -1;
}

#else

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

    std::cerr << "CT : " << pField->getContentType().getCName() << std::endl;

    if(pField->getCardinality() == OSG::FieldType::SINGLE_FIELD)
    {
        std::cerr << "SField " << std::endl;

        if(pField->getContentType() == 
           OSG::FieldDataTraits<OSG::FieldContainerPtr>::getType())
        {
            OSG::SFNodePtr *pSField    = static_cast<OSG::SFNodePtr *>(pField);
            
            OSG::FieldContainerPtr pFC = pSField->getValue();
                        
            if(pFC != OSG::NullFC)
            {
                std::cerr << "Got empty FC " << std::endl;
            }
            else
            {
                std::cerr << "Got valid FC" << std::endl;
            }
        }
        else
        {
            std::cerr << "Field contais no container " << std::endl;
        }
    }
    else
    {
        std::cerr << "MField " << std::endl;
    }

    return 0;
}

#endif
