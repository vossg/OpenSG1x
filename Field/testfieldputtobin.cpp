#include <stdio.h>
#include <vector>
#include <OSGConfig.h>
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

OSG_USING_NAMESPACE

class TestHandler:public OSG::BinaryDataHandler
{
public:
    TestHandler(FILE *file):OSG::BinaryDataHandler(15000),_file(file) {
        unsigned int i;
        _memory.resize(7*2);
        for(i=0;i<_memory.size();i+=2)
        {
            _memory[i  ].resize(15000);
            _memory[i+1].resize(15000);
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
    std::vector<std::vector<OSG::UInt8> > _memory;
    FILE *_file;
};

template <class T>
void runTest(bool write,BinaryDataHandler &pMem,const T &value)
{
    SField<T> sfield;
    MField<T> mfield;
    if(write)
    {
        sfield.setValue(value);
        sfield.copyToBin(pMem);
        mfield.clear();
        mfield.push_back(value);
        mfield.push_back(value);
        mfield.copyToBin(pMem);
        SLOG << SField<T>::SFieldTraits::getSName() << " size " 
             << sfield.getBinSize() << std::endl;
        SLOG << MField<T>::MFieldTraits::getMName() << " size " 
             << mfield.size() << " " << mfield.getBinSize() << std::endl;
    }
    else
    {
        sfield.copyFromBin(pMem);
        if(sfield.getValue() == value)
            SLOG << SField<T>::SFieldTraits::getSName() << " " 
                 << "OK" << std::endl;
        else
            SLOG << SField<T>::SFieldTraits::getSName() << " " 
                 << "ERROR" << std::endl;
        mfield.copyFromBin(pMem);
        if(mfield[0] == value &&
           mfield[1] == value)
            SLOG << SField<T>::SFieldTraits::getMName() << " "
                 << "OK" << std::endl;
        else
            SLOG << SField<T>::SFieldTraits::getMName() << " " 
                 << "ERROR" << std::endl;
    }
}

template <class T>
void runTest1(bool write,BinaryDataHandler &pMem,const T &value)
{
    SField<T,1> sfield;
    MField<T,1> mfield;
    if(write)
    {
        sfield.setValue(value);
        sfield.copyToBin(pMem);
        mfield.clear();
        mfield.push_back(value);
        mfield.push_back(value);
        mfield.copyToBin(pMem);
        SLOG << SField<T,1>::SFieldTraits::getSName() << " size " 
             << sfield.getBinSize() << std::endl;
        SLOG << MField<T,1>::MFieldTraits::getMName() << " size " 
             << mfield.size() << " " << mfield.getBinSize() << std::endl;
    }
    else
    {
        sfield.copyFromBin(pMem);
        if(sfield.getValue() == value)
            SLOG << SField<T,1>::SFieldTraits::getSName() << " " 
                 << "OK" << std::endl;
        else
            SLOG << SField<T,1>::SFieldTraits::getSName() << " " 
                 << "ERROR " << std::endl;
        mfield.copyFromBin(pMem);
        if(mfield[0] == value &&
           mfield[1] == value)
            SLOG << SField<T,1>::SFieldTraits::getMName() << " "
                 << "OK" << std::endl;
        else
            SLOG << SField<T,1>::SFieldTraits::getMName() << " " 
                 << "ERROR" << std::endl;
    }
}

template <class T>
void runTest2(bool write,BinaryDataHandler &pMem,const T &value)
{
    SField<T,2> sfield;
    MField<T,2> mfield;
    if(write)
    {
        sfield.setValue(value);
        sfield.copyToBin(pMem);
        mfield.clear();
        mfield.push_back(value);
        mfield.push_back(value);
        mfield.copyToBin(pMem);
        SLOG << SField<T,2>::SFieldTraits::getSName() << " size " 
             << sfield.getBinSize() << std::endl;
        SLOG << MField<T,2>::MFieldTraits::getMName() << " size " 
             << mfield.size() << " " << mfield.getBinSize() << std::endl;
    }
    else
    {
        sfield.copyFromBin(pMem);
        if(sfield.getValue() == value)
            SLOG << SField<T,2>::SFieldTraits::getSName() << " " 
                 << "OK" << std::endl;
        else
            SLOG << SField<T,2>::SFieldTraits::getSName() << " " 
                 << "ERROR" << std::endl;
        mfield.copyFromBin(pMem);
        if(mfield[0] == value &&
           mfield[1] == value)
            SLOG << SField<T,2>::SFieldTraits::getMName() << " "
                 << "OK" << std::endl;
        else
            SLOG << SField<T,2>::SFieldTraits::getMName() << " " 
                 << "ERROR" << std::endl;
    }
}

void runTests(bool write,BinaryDataHandler &pMem)
{
    runTest  (write,pMem, std::string("Hallo") );
    runTest1 (write,pMem, Time(222.22) );
    runTest  (write,pMem, Color3f(1.1,2.2,3.3) );
    runTest  (write,pMem, Color4f(1.1,2.2,3.3,4.4) );
    runTest  (write,pMem, Color3ub(1,2,3) );
    runTest  (write,pMem, Color4ub(1,2,3,4) );
    runTest  (write,pMem, DynamicVolume(DynamicVolume::BOX_VOLUME) );
    runTest  (write,pMem, DynamicVolume(DynamicVolume::SPHERE_VOLUME) );
    runTest1 (write,pMem, BitVector(0xabcd) );
    runTest  (write,pMem, Plane(Vec3f(1.0,0),0.222) );
    runTest  (write,pMem, Matrix(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16) );
    runTest  (write,pMem, Quaternion(Vec3f(1,2,3),22) );
    runTest2<bool>(write,pMem, true );
    runTest  (write,pMem, Int8(-22) );
    runTest  (write,pMem, UInt8(11) );
    runTest  (write,pMem, Int16(-10233) );
    runTest  (write,pMem, UInt16(20233) );
    runTest  (write,pMem, Int32(-222320233) );
    runTest  (write,pMem, UInt32(522320233) );
    runTest<Int64>  (write,pMem, Int64(-522323334) );
    runTest  (write,pMem, UInt64(44523423) );
    runTest  (write,pMem, Real32(22.333224) );
    runTest  (write,pMem, Real64(52.334534533224) );
    runTest  (write,pMem, Vec2f(1.1,2.2) );
    runTest  (write,pMem, Vec3f(1.1,2.2,3.3) );
    runTest  (write,pMem, Vec4f(1.1,2.2,3.3,4.4) );
    runTest  (write,pMem, Pnt2f(1.1,2.2) );
    runTest  (write,pMem, Pnt2d(1.1,2.2) );
    runTest  (write,pMem, Pnt3f(1.1,2.2,3.3) );
    runTest  (write,pMem, Pnt3d(1.1,2.2,3.3) );
    runTest  (write,pMem, Pnt4f(1.1,2.2,3.3,4.4) );
    runTest  (write,pMem, Pnt4d(1.1,2.2,3.3,4.4) );
}

int main()
{
    FILE *wfile=fopen("binfile","w");
    TestHandler w(wfile);
    runTests(true,w);
    w.flush();
    fclose(wfile);
    FILE *rfile=fopen("binfile","r");
    TestHandler r(rfile);
    runTests(false,r);
    fclose(rfile);
}

