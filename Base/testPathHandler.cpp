
#include <OSGPathHandler.h>
#include <OSGLog.h>

OSG_USING_NAMESPACE

int main( int argc, char** argv )
{
  PathHandler ph;
	   	
  ph.addPath( "" );
  ph.setBaseFile( "" );
  
  SLOG << "Looking for OSGPathHandler.h: "
       << ph.findFile( "~/OSGPathHandler.h" ) << endl;
  SLOG << "Looking for testCalcFaceNormals.cpp: "
       << ph.findFile( "testCalcFaceNormals.cpp" ) << endl;
  ph.subPath( "~/Develop/OpenSG/Base" );
  
 
  return 0;
}




