
#include <stdio.h>
#include <OSGContainerFieldDataType.h>

void main(void)
{
    fprintf(stderr, "TestStart\n");

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(NULL, NULL, 0);
}
