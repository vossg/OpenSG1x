
#include <stdio.h>
#include <vector>
#include <OSGBaseTypes.h>
#include <OSGSFVecTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGVecFieldDataType.h>
#include <OSGSysFieldDataType.h>
#include <OSGMathFieldDataType.h>
#include <OSGBaseFieldDataType.h>
#include <OSGBinaryDataHandler.h>
#include <OSGSFSysTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGSFBaseTypes.h>

using std::vector;

class TestHandler:public OSG::BinaryDataHandler
{
public:
    TestHandler(FILE *file):OSG::BinaryDataHandler(),_file(file) {
        unsigned int i;
        _memory.resize(7);
        for(i=0;i<_memory.size();i++)
        {
            _memory[i].resize(5);
            _buffers.push_back(MemoryBlock(&_memory[i][0],
                                           _memory[i].size()));
        }
        _zeroCopyThreshold=5;
        reset();
    }
    void read(OSG::MemoryHandle mem,int size) {
        fprintf(stderr,"dorect read %d bytes\n",size);
        fread(mem,size,1,_file);
    }
    void write(OSG::MemoryHandle mem,int size) {
        fprintf(stderr,"direct write %d bytes\n",size);
        fwrite(mem,size,1,_file);
    }
private:
    vector<vector<OSG::UInt8> > _memory;
    FILE *_file;
};

struct TestData {
    OSG::SFUInt32  uint32;
    OSG::SFUInt16  uint16;
    OSG::MFUInt32  muint32;
    OSG::SFString  str;
    OSG::SFVec2f   v2;
    OSG::SFVec3f   v3;
    OSG::SFVec4f   v4;
};

int main(void)
{
    fprintf(stderr, "TestStart\n");

    FILE *wfile=fopen("binfile","w");

    TestHandler pMem(wfile);

    OSG::Vec2f  v2;
    OSG::Vec3f  v3;
    OSG::Vec4f  v4;
    OSG::Vec4ub v4ub;

    OSG::Pnt2f p2;
    OSG::Pnt3f p3;
    OSG::Pnt4f p4;

    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(pMem, v2);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(pMem, v3);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(pMem, v4);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(pMem, v4ub);
    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt2f> ::copyToBin(pMem, p2);
    OSG::FieldDataTraits<OSG::Pnt3f> ::copyToBin(pMem, p3);
    OSG::FieldDataTraits<OSG::Pnt4f> ::copyToBin(pMem, p4);
    OSG::FieldDataTraits<OSG::Pnt2f> ::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt3f> ::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt4f> ::copyToBin(pMem, NULL, 0);

    OSG::Bool b;

    OSG:: Int8  i8;
    OSG::UInt8 ui8;

    OSG:: Int16  i16;
    OSG::UInt16 ui16;

    OSG:: Int32  i32;
    OSG::UInt32 ui32;

    OSG:: Int64  i64;
    OSG::UInt64 ui64;

    OSG::Real32  r32;
    OSG::Real64  r64;


    OSG::FieldDataTraits2<OSG::Bool>::copyToBin(pMem, b);

    OSG::FieldDataTraits<OSG:: Int8>::copyToBin(pMem, i8);
    OSG::FieldDataTraits<OSG::UInt8>::copyToBin(pMem, ui8);

    OSG::FieldDataTraits<OSG:: Int16>::copyToBin(pMem, i16);
    OSG::FieldDataTraits<OSG::UInt16>::copyToBin(pMem, ui16);

    OSG::FieldDataTraits<OSG:: Int32>::copyToBin(pMem, i32);
    OSG::FieldDataTraits<OSG::UInt32>::copyToBin(pMem, ui32);

    OSG::FieldDataTraits<OSG:: Int64>::copyToBin(pMem, i64);
    OSG::FieldDataTraits<OSG::UInt64>::copyToBin(pMem, ui64);

    OSG::FieldDataTraits<OSG::Real32>::copyToBin(pMem, r32);
    OSG::FieldDataTraits<OSG::Real64>::copyToBin(pMem, r64);


    OSG::FieldDataTraits2<OSG::Bool>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int8>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt8>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int16>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt16>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int32>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt32>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int64>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt64>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG::Real32>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Real64>::copyToBin(pMem, NULL, 0);

    OSG::Matrix     mat;
    OSG::Quaternion quat;

    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(pMem, mat);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(pMem, quat);


    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(pMem, NULL, 0);

    OSG::String        str("xxx");;
    OSG::Time          tim;
    OSG::Color3f       c3;
    OSG::Color4f       c4;
    OSG::Color3ub      c3ub;
    OSG::Color4ub      c4ub;
    OSG::DynamicVolume dv;
    OSG::BitVector     bv;

    OSG::FieldDataTraits <OSG::String       >::copyToBin(pMem, str);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(pMem, tim);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(pMem, c3);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(pMem, c4);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(pMem, c3ub);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(pMem, c4ub);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(pMem, dv);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(pMem, bv);

    OSG::FieldDataTraits <OSG::String       >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(pMem, NULL, 0);
    fclose(wfile);

    TestData src,dst;

    src.uint32.setValue(33);
    src.muint32.push_back(2);
    src.muint32.push_back(4);
    src.muint32.push_back(6);
    src.muint32.push_back(3);
    src.uint16.setValue(2);
    src.str.setValue(OSG::String("teststr"));
    src.v2.setValue(OSG::Vec2f(1,2));
    src.v3.setValue(OSG::Vec3f(3,4,5));
    src.v4.setValue(OSG::Vec4f(6,7,8,9));
    
    src.uint32.setValue(0x1111);
    src.uint16.setValue(2);
    src.str.setValue(OSG::String("teststr"));
    src.v2.setValue(OSG::Vec2f(1,2));
    src.v3.setValue(OSG::Vec3f(3,4,5));
    src.v4.setValue(OSG::Vec4f(6,7,8,9));

    wfile=fopen("binfile","w");
    TestHandler w(wfile);
    src.uint32.copyToBin  (w);
    src.muint32.copyToBin (w);
    src.uint16.copyToBin  (w);
    src.str.copyToBin     (w);
    src.v2.copyToBin      (w);
    src.v3.copyToBin      (w);
    src.v4.copyToBin      (w);
    w.flush();
    fclose(wfile);

    FILE *rfile=fopen("binfile","r");
    TestHandler r(rfile);
    dst.uint32.copyFromBin  (r);
    dst.muint32.copyFromBin (r);
    dst.uint16.copyFromBin  (r);
    dst.str.copyFromBin     (r);
    dst.v2.copyFromBin      (r);
    dst.v3.copyFromBin      (r);
    dst.v4.copyFromBin      (r);
    fclose(rfile);
    
    if(src.uint32.getValue() != dst.uint32.getValue()   ||
       src.muint32[0]        != dst.muint32[0] ||
       src.muint32.size()    != dst.muint32.size() ||
       src.uint16.getValue() != dst.uint16.getValue())
        fprintf(stderr,"Int error\n");
    else
        fprintf(stderr,"Int OK\n");

    if(src.str.getValue() != dst.str.getValue())
        fprintf(stderr,"string error\n");
    else
        fprintf(stderr,"string OK\n");

    if(src.v2.getValue() != dst.v2.getValue() ||
       src.v3.getValue() != dst.v3.getValue() ||
       src.v4.getValue() != dst.v4.getValue())
        fprintf(stderr,"Vec error\n");
    else
        fprintf(stderr,"Vec OK\n");
    return 0;
}






