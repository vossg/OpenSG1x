
#include <FieldContainerViewCtl.h>

#include <string>

#ifdef FCD_GUI

#include <qapp.h>

int main( int argc, char **argv )
{ 
	int retCode = -1;
	FieldContainer fc;
	bool writeBase = false, writeFC = false;
	std::string fcdFile, typeFile;

	// Win32 doesn't have getopt, DIY
	do 
	{
		argc--, argv++;
		if ( argc && argv[0][0] == '-' )
		{
    		switch (argv[0][1]) 
    		{
    		case 'd':
    			if ( argc > 1 )
    			{
    				fcdFile = argv[1];
    				argv++, argc--;
    			}
    			else
    			{
    				cerr << "fcdEdit: -d but no argument given!" <<endl;
    				return 1;
    			}				
    			break;
    		case 't':
    			if ( argc > 1 )
    			{
    				typeFile = argv[1];
    				argv++, argc--;
    			}
    			else
    			{
    				cerr << "fcdEdit: -t but no argument given!" <<endl;
    				return 1;
    			}				
    			break;
    		case 'b':
    			writeBase = true;
    			break;
    		case 'f':
    			writeFC = true;
    			break;
    		case 'h':
    			cerr << "Usage: fcdEdit -d file.fcd -t file.ftd -bfh" << endl;
    			cerr << "  -d file.fcd: load the field container description" << endl;
    			cerr << "  -t file.ftd: load the field type description" << endl;
    			cerr << "  -b write the field container base code files" << endl;
    			cerr << "  -f write the field container code files" << endl;
    			cerr << "  -h print usage" << endl;
    			return 0;
    			break;
    		}
    	}
		else
			break;
	}
	while (argc > 0);
		
	if ( argc )
		fcdFile = argv[ 0 ];
		
	if (typeFile.empty())
		Field::loadDefaultFieldTypeList();
	else
		Field::loadFieldTypeList(typeFile.c_str());

	if (writeBase || writeFC) 
	{
		if (fcdFile.empty())
			cerr << "ERROR: Can't write code without description" << endl;
		else 
		{
			fc.readDesc(fcdFile.c_str());
			fc.writeCode(writeBase,writeFC);
			retCode = 0;
		}
	}
	else 
	{
    	QApplication app( argc, argv );
		FieldContainerViewCtl fCViewCtl(fcdFile.c_str());
		app.setMainWidget(&fCViewCtl);
		fCViewCtl.show();
		retCode = app.exec();
	}

	return 0;
}

#endif

#ifdef FCD_TERM

int main( int argc, char **argv )
{ 
	int retCode = -1;
	FieldContainer fc;
	bool writeBase = false, writeFC = false;
	const char *optstring = "d:t:bfh";
	std::string fcdFile, typeFile;
	int opt = 0;

	while (opt >= 0) {
		opt = getopt(argc,argv,optstring);
		switch (opt) {
		case 'd':
			fcdFile = optarg;
			break;
		case 't':
			typeFile = optarg;
			break;
		case 'b':
			writeBase = true;
			break;
		case 'f':
			writeFC = true;
			break;
		case 'h':
			cerr << "Usage: fcdEdit -d file.fcd -t file.ftd -bfh" << endl;
			cerr << "  -d file.fcd: load the field container description" << endl;
			cerr << "  -t file.ftd: load the field type description" << endl;
			cerr << "  -b write the field container base code files" << endl;
			cerr << "  -f write the field container code files" << endl;
			cerr << "  -h print usage" << endl;
			return 0;
			break;
		}
	}
	
	if ( optind < argc )
		fcdFile = argv[ optind ];
		
	if (typeFile.empty())
		Field::loadDefaultFieldTypeList();
	else
		Field::loadFieldTypeList(typeFile.c_str());

	if (writeBase || writeFC) {
		if (fcdFile.empty())
			cerr << "ERROR: Can't write code without description" << endl;
		else {
			fc.readDesc(fcdFile.c_str());
			fc.writeCode(writeBase,writeFC);
			retCode = 0;
		}
	}


	return 0;
}

#endif





