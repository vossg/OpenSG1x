#include <stdio.h>
#include <vector>
#include <OSGGeometry.h>
#include <OSGSFFieldContainerTypes.h>
#include <OSGBinaryDataHandler.h>
#include <OSGFieldContainerFactory.h>
#include <OSGImage.h>
#include <OSGImageFields.h>

using std::vector;

class TestHandler:public OSG::BinaryDataHandler
{
public:
    TestHandler(FILE *file):OSG::BinaryDataHandler(1024),_file(file) {
        unsigned int i;
        _memory.resize(7*2);
        for(i=0;i<_memory.size();i+=2)
        {
            _memory[i  ].resize(5);
            _memory[i+1].resize(5);
            readBufAdd (&_memory[i  ][0],_memory[i  ].size());
            writeBufAdd(&_memory[i+1][0],_memory[i+1].size());
        }
    }
    void read(OSG::MemoryHandle mem,OSG::UInt32 size) {
        fread(mem,size,1,_file);
    }
    void write(OSG::MemoryHandle mem,OSG::UInt32 size) {
        fwrite(mem,size,1,_file);
    }
private:
    vector<vector<OSG::UInt8> > _memory;
    FILE *_file;
};

int main(int argc,char **argv)
{
    fprintf(stderr, "TestStart\n");

    OSG::osgInit(argc,argv);
    FILE *wfile=fopen("binfile","w");
    TestHandler pMem(wfile);

    OSG::FieldContainerPtr pfc;
    OSG::NodePtr           pn;
    OSG::NodeCorePtr       pnc;
    OSG::AttachmentMap     am;

    OSG::GeoPositionsPtr    pp;
    OSG::GeoNormalsPtr      pno;
    OSG::GeoColorsPtr       pc;
    OSG::GeoTexCoordsPtr   ptc;
    OSG::GeoIndicesPtr       pi;
    OSG::GeoPTypesPtr       pt;
    OSG::GeoPLengthsPtr     pl;

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(pMem, pfc);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(pMem, pn);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(pMem, pnc);
    OSG::FieldDataTraits<OSG::GeoPositionsPtr   >::copyToBin(pMem, pp);
    OSG::FieldDataTraits<OSG::GeoNormalsPtr     >::copyToBin(pMem, pno);
    OSG::FieldDataTraits<OSG::GeoColorsPtr      >::copyToBin(pMem, pc);
    OSG::FieldDataTraits<OSG::GeoTexCoordsPtr  >::copyToBin(pMem, ptc);
    OSG::FieldDataTraits<OSG::GeoIndicesPtr      >::copyToBin(pMem, pi);
    OSG::FieldDataTraits<OSG::GeoPTypesPtr      >::copyToBin(pMem, pt);
    OSG::FieldDataTraits<OSG::GeoPLengthsPtr    >::copyToBin(pMem, pl);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(pMem, am);

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::NodePtr          >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoPositionsPtr   >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoNormalsPtr     >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoColorsPtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoTexCoordsPtr  >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoIndicesPtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoPTypesPtr      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::GeoPLengthsPtr    >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::AttachmentMap    >::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG::FieldContainerPtr>::getBinSize(&pfc, 1);
    OSG::FieldDataTraits<OSG::NodePtr          >::getBinSize(&pn, 1);
    OSG::FieldDataTraits<OSG::NodeCorePtr      >::getBinSize(&pnc, 1);
    OSG::FieldDataTraits<OSG::GeoPositionsPtr   >::getBinSize(&pp, 1);
    OSG::FieldDataTraits<OSG::GeoNormalsPtr     >::getBinSize(&pno, 1);
    OSG::FieldDataTraits<OSG::GeoColorsPtr      >::getBinSize(&pc, 1);
    OSG::FieldDataTraits<OSG::GeoTexCoordsPtr  >::getBinSize(&ptc, 1);
    OSG::FieldDataTraits<OSG::GeoIndicesPtr      >::getBinSize(&pi, 1);
    OSG::FieldDataTraits<OSG::GeoPTypesPtr      >::getBinSize(&pt, 1);
    OSG::FieldDataTraits<OSG::GeoPLengthsPtr    >::getBinSize(&pl, 1);

    fclose(wfile);

    vector<OSG::FieldContainerPtr> ptr_src;
    vector<OSG::FieldContainerPtr> ptr_dst;
    vector<OSG::FieldContainerPtr>::iterator i;

    // maybe there is a better way to get all known types
    int t;
    OSG::FieldContainerType *fct;
    OSG::FieldContainerPtr fcp;
    for(t=0;t<1000;t++)
    {
        fct=OSG::FieldContainerFactory::the()->findType(t);
        if(fct && (!fct->isAbstract()))
        {
            fprintf(stderr,"create Type: %d '%s'\n", t,fct->getName().str());
            fcp=fct->createFieldContainer();
            if(fcp==OSG::NullFC)
                fprintf(stderr,"can't create Type: %d '%s'\n",
                        t,fct->getName().str());
            else
                ptr_src.push_back(fcp);
            fcp=fct->createFieldContainer();
            if(fcp==OSG::NullFC)
                fprintf(stderr,"can't create Type: %d '%s'\n",
                        t,fct->getName().str());
            else
                ptr_dst.push_back(fcp);
        }
    }

    wfile=fopen("binfile","w");
    TestHandler w(wfile);
    for(i=ptr_src.begin();i!=ptr_src.end();i++)
    {
        fprintf(stderr,"toBin Type: '%s'\n", 
                (*i)->getType().getName().str());
        (*i)->copyToBin(w,OSG::FieldBits::AllFields);
    }
    w.flush();
    char *teststr="Read/Write OK\n";
    fwrite(teststr,strlen(teststr)+1,1,wfile);
    fclose(wfile);

    FILE *rfile=fopen("binfile","r");
    TestHandler r(rfile);
    for(i=ptr_dst.begin();i!=ptr_dst.end();i++)
    {
        fprintf(stderr,"fromBin Type: '%s'\n", 
                (*i)->getType().getName().str());
        (*i)->copyFromBin(r,OSG::FieldBits::AllFields);
    }
    char str[100];
    fread(str,strlen(teststr)+1,1,rfile);
    fclose(rfile);

    // check if bytes written is equal to bytes read
    if(strcmp(teststr,str)==0)
        fprintf(stderr,"%s",str); 
    else
        fprintf(stderr,"Bytes write != bytes read\n"); 

    // check image

    wfile=fopen("binfile","w");
    TestHandler imgw(wfile);

    OSG::UChar8 img[2*2*3] = {
        11,12,13, 21,22,23,
        31,32,33, 41,42,43
    };

    OSG::ImagePtr pImage = OSG::Image::create();
    pImage->set(OSG::Image::OSG_RGB_PF,
                2,2,
                1,
                1,
                1,0.0,
                img);

    pImage->setAttachmentField("hallo","blubber");
    pImage->setAttachmentField("hallo2","blubber2");

    OSG::SFImagePtr sfimage;

    sfimage.setValue(pImage);

    sfimage.copyToBin(imgw);
    imgw.flush();
    fclose(wfile);

    rfile=fopen("binfile","r");
    TestHandler imgr(rfile);

    OSG::SFImagePtr sfimager;
    sfimager.copyFromBin(imgr);

    if(sfimager.getValue()->getWidth() != 2 ||
       sfimager.getValue()->getHeight() != 2)
        fprintf(stderr,"Error: image\n"); 
    else
        fprintf(stderr,"Image copy OK\n"); 

    return 0;
}





