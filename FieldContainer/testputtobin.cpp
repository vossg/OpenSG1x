
#include <stdio.h>
#include <OSGContainerFieldDataType.h>

int main(void)
{
    fprintf(stderr, "TestStart\n");

    OSG::FieldContainerPtr pfc;
    OSG::NodePtr           pn;
    OSG::NodeCorePtr       pnc;
    OSG::AttachmentMap     am;


    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(NULL, pfc);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(NULL, pn);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(NULL, pnc);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(NULL, am);

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(NULL, NULL, 0);
}
