
#include <OSGPathHandler.h>
#include <OSGLog.h>

OSG_USING_NAMESPACE

int main( int argc, char** argv )
{
    PathHandler ph;

//    ph.push_backPath("a/b:b/c/d/:c/d/e/f:/d/f/g/h/i/");
//    ph.push_backPath("e");
//    ph.push_backPath("");

//    ph.addPath("/x:/x/y/z/");

//    ph.addPath("%FOO%/a;%BAR%/a/b/c");
//    ph.addPath("%FOO%%BAR%");
//    ph.addPath("%FOO%");
//    ph.addPath("%FOO%;/o/p/q");

//    ph.push_frontPath ("wa\\wb;wc\\wd\\we\\;\\wx\\wy\\wz");


//    ph.addPath("%FOO%/wa;%BAR%/wa/wb/wc");

//  ph.addPath ("a\\b;c\\d\\e\\;E:\\x\\y\\z");

//  ph.addUnixPath();

//  ph.dump();
/*
  ph.setBaseFile("../foo/test.ppm");
  ph.dump();

  ph.setBaseFile("../foo/");
  ph.dump();

  ph.setBaseFile("../foo");
  ph.dump();

  ph.setBaseFile("..\\foo\\test.ppm");
  ph.dump();

  ph.setBaseFile("..\\foo\\");
  ph.dump();

  ph.setBaseFile("..\\foo");
  ph.dump();

  ph.setBaseFile("test.ppm");
  ph.dump();
*/
  

    ph.setBaseFile("../../../Experimental/VRMLLoader/tie.wrl");
    ph.push_frontCurrentDir();
    ph.push_backPath("~/tmpx");

    ph.dump();
  
    ph.push_backPath( "~" );
    ph.dump();

    
    SLOG << "Looking for tie.wrl: "
         << std::endl
         << ph.findFile("../../../Experimental/VRMLLoader/tie.wrl")
         << std::endl;

    SLOG << "Looking for std.wrl: "
         << std::endl
         << ph.findFile("std.wrl")
         << std::endl;

    SLOG << "Looking for polyp.tif: "
         << std::endl
         << ph.findFile("polyp.tif")
         << std::endl;

//  SLOG << "Looking for testCalcFaceNormals.cpp: "
//       << ph.findFile( "testCalcFaceNormals.cpp" ) << std::endl;

//  ph.subPath( "~/Develop/OpenSG/Base" );
  
 
  return 0;
}




