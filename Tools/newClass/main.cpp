#include <sysConfig.h>
#include <iostream>

#include "XMApp.h"
#include "XMNewClass.h"

int main (int argc, char **argv)
{
	char *className = 0;

	XMApp app("NewClass", argc, argv);

  for (argv++; --argc; argv++)
		if (**argv == '-')
			cout << "Param: " << *argv << endl;
	  else
			if (className)
				cout << "ERROR: className !=0 in main() \n";
			else
				className = *argv;
	
	XMNewClass newClass (app.topWidget(), className);

	app.engage();
}
