
#include <stdio.h>
#include <OSGContainerFieldDataType.h>
#include <OSGGeometry.h>
#include <OSGGeoPropInterfaceFields.h>

int main(void)
{
    char memblock[2048];

    OSG::MemoryHandle pMem = (OSG::MemoryHandle) memblock;

    fprintf(stderr, "TestStart\n");

    OSG::FieldContainerPtr pfc;
    OSG::NodePtr           pn;
    OSG::NodeCorePtr       pnc;
    OSG::AttachmentMap     am;

    OSG::GeoPositionPtr    pp;
    OSG::GeoNormalPtr      pno;
    OSG::GeoColorPtr       pc;
    OSG::GeoTexCoordsPtr   ptc;
    OSG::GeoIndexPtr       pi;
    OSG::GeoPTypePtr       pt;
    OSG::GeoPLengthPtr     pl;

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(pMem, pfc);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(pMem, pn);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(pMem, pnc);
    OSG::FieldDataTraits<OSG::GeoPositionPtr   >::copyToBin(pMem, pp);
    OSG::FieldDataTraits<OSG::GeoNormalPtr     >::copyToBin(pMem, pno);
    OSG::FieldDataTraits<OSG::GeoColorPtr      >::copyToBin(pMem, pc);
    OSG::FieldDataTraits<OSG::GeoTexCoordsPtr  >::copyToBin(pMem, ptc);
    OSG::FieldDataTraits<OSG::GeoIndexPtr      >::copyToBin(pMem, pi);
    OSG::FieldDataTraits<OSG::GeoPTypePtr      >::copyToBin(pMem, pt);
    OSG::FieldDataTraits<OSG::GeoPLengthPtr    >::copyToBin(pMem, pl);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(pMem, am);

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoPositionPtr   >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoNormalPtr     >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoColorPtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoTexCoordsPtr  >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoIndexPtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoPTypePtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoPLengthPtr    >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(pMem, NULL, 0);
}
