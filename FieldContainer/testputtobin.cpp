
#include <stdio.h>
#include <OSGContainerFieldDataType.h>
#include <OSGVecFieldDataType.h>
#include <OSGGroup.h>

void main(void)
{
    fprintf(stderr, "TestStart\n");

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::putToBin();
    OSG::FieldDataTraits<OSG::GroupPtr>::putToBin();
    OSG::FieldDataTraits<OSG::Vec3f>::putToBin();
}
