// OpenSG Example: NewTypes
//

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// OSG File IO
#include <OpenSG/OSGOSGWriter.h>
#include <OpenSG/OSGBINWriter.h>
#include <OpenSG/OSGSceneFileHandler.h>


// The new Field and FieldContainer types

// The versions to use directly in an app
#include <OSGNewFieldType.h>
#include <OSGNewFieldContainer.h>

// The versions that can also be used in a library/dll
#include <OSGNewFieldTypeLib.h>
#include <OSGNewFieldContainerLib.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Simple Dummy Binary Data Handler
// useful for testing the toBin/fromBin functions
class DummyHandler:public BinaryDataHandler
{
  public:
    DummyHandler(FILE *file) :
        BinaryDataHandler(),
        _file(file) 
    {
        readBufAdd (_readmem,  sizeof(_readmem ));
        writeBufAdd(_writemem, sizeof(_writemem));
    }
    void read(MemoryHandle mem, UInt32 size) 
    {
        fread(mem,size,1,_file);
    }
    void write(MemoryHandle mem, UInt32 size) 
    {
        fwrite(mem,size,1,_file);
    }
  private:
    UInt8 _readmem[200];
    UInt8 _writemem[200];
    FILE *_file;
};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);  
   
    // Test the new Field Type(s)    
    {
    UInt32 fooVal = 1;
    TripleInt barVal(1,2,3);

    SLOG << "Test FieldDataTraits<TripleInt>" << endLog;
   
    // String functions
    std::string str;
    
    FieldDataTraits<TripleInt>::putToString(barVal, str);
    SLOG << "TripleInt putToString: >" << str << "<" << endLog;
    
    TripleInt fromstr;
    const Char8 *c = str.c_str();
    FieldDataTraits<TripleInt>::getFromString(fromstr, c);
    SLOG << "TripleInt getFromString: (" << fromstr.getValue(0) << ","
                                         << fromstr.getValue(1) << ","
                                         << fromstr.getValue(2) << ")" 
                                         << endLog;
    
    // BIN Functions

    SLOG << "TripleInt Binsize: " 
         << FieldDataTraits<TripleInt>::getBinSize(barVal)
         << endLog;

    FILE* wfile=fopen("binfile", "w");
    DummyHandler w(wfile);                 
    FieldDataTraits<TripleInt>::copyToBin(w, barVal);   
    w.flush();
    fclose(wfile);

    TripleInt fromfile;
    FILE *rfile=fopen("binfile", "r");
    DummyHandler r(rfile);
    FieldDataTraits<TripleInt>::copyFromBin(r, fromfile);
    fclose(rfile);

    SLOG << "TripleInt copyFromBin: (" << fromfile.getValue(0) << ","
                                       << fromfile.getValue(1) << ","
                                       << fromfile.getValue(2) << ")" 
                                       << endLog;
   
	}
    
    // Test the Library version
    {
    UInt32 fooVal = 2;
    TripleIntLib barVal(4,5,6);
    
    SLOG << "Test FieldDataTraits<TripleIntLib>" << endLog;
   
    // String functions
    std::string str;
    
    FieldDataTraits<TripleIntLib>::putToString(barVal, str);
    SLOG << "TripleIntLib putToString: >" << str << "<" << endLog;
    
    TripleIntLib fromstr;
    const Char8 *c = str.c_str();
    FieldDataTraits<TripleIntLib>::getFromString(fromstr, c);
    SLOG << "TripleIntLib getFromString: (" << fromstr.getValue(0) << ","
                                         << fromstr.getValue(1) << ","
                                         << fromstr.getValue(2) << ")" 
                                         << endLog;
    
    // BIN Functions

    SLOG << "TripleIntLib Binsize: " 
         << FieldDataTraits<TripleIntLib>::getBinSize(barVal)
         << endLog;

    FILE* wfile=fopen("binfile", "w");
    DummyHandler w(wfile);                 
    FieldDataTraits<TripleIntLib>::copyToBin(w, barVal);   
    w.flush();
    fclose(wfile);

    TripleIntLib fromfile;
    FILE *rfile=fopen("binfile", "r");
    DummyHandler r(rfile);
    FieldDataTraits<TripleIntLib>::copyFromBin(r, fromfile);
    fclose(rfile);

    SLOG << "TripleIntLib copyFromBin: (" << fromfile.getValue(0) << ","
                                       << fromfile.getValue(1) << ","
                                       << fromfile.getValue(2) << ")" 
                                       << endLog;
   
	}

	// New FieldContainer types	
	
    std::ofstream outFileStream( "asciifile" );
    OSGWriter writer( outFileStream, 4 );
    
    // First the app version
    {
    UInt32 fooVal = 3;
    TripleInt barVal(7,8,9);   
     
    // Create new FieldContainer type instance
    SLOG << "Test NewFieldContainer" << endLog;

    // This is the non-library version, which only works if directly used
    NewFieldContainerPtr p = NewFieldContainer::create();
   
    // change it
    beginEditCP(p,  NewFieldContainer::FooFieldMask |
                    NewFieldContainer::BarFieldMask);

    p->getFoo().push_back(fooVal);
    p->setBar(barVal);

    endEditCP  (p,  NewFieldContainer::FooFieldMask |
                    NewFieldContainer::BarFieldMask);

    // read it
    UInt32 foo;
    TripleInt bar;
    
    foo = p->getFoo()[0];
    bar = p->getBar();

    SLOG << "Foo: "  << foo << endLog;
    SLOG << "Bar: (" << bar.getValue(0) << ","
                     << bar.getValue(1) << ","
                     << bar.getValue(2) << ")" 
                     << endLog;
     
    // write it out
    // note that you can not read it back in, as does not start with a Node!
    writer.write(p);  
 	}
    
    // Then the library version
    {
    UInt32 fooVal = 4;
    TripleInt barVal(10,11,12);

    SLOG << "Test NewFieldContainerLib" << endLog;

    // This is the library version, which can also be put into a library/dll
    NewFieldContainerLibPtr lp = NewFieldContainerLib::create();
   
    // change it
    beginEditCP(lp,  NewFieldContainerLib::FooFieldMask |
                     NewFieldContainerLib::BarFieldMask);

    lp->getFoo().push_back(fooVal);
    lp->setBar(barVal);

    endEditCP  (lp,  NewFieldContainerLib::FooFieldMask |
                     NewFieldContainerLib::BarFieldMask);

    // read it
    UInt32 foo;
    TripleInt bar;

    foo = lp->getFoo()[0];
    bar = lp->getBar();

    SLOG << "Foo: "  << foo << endLog;
    SLOG << "Bar: (" << bar.getValue(0) << ","
                     << bar.getValue(1) << ","
                     << bar.getValue(2) << ")" 
                     << endLog;
     
    // write it out
    // note that you can not read it back in, as does not start with a Node!
    writer.write(lp);
	}
    
    osgExit();
    
    return 0;
}
