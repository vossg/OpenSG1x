
#include <stdio.h>

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGLog.h>

#include <OSGNormalQuantifier.h>

int main (int argc, char **argv)
{
	int retCode = 0;

	osg::NormalQuantifier nq;

	nq.build(4);

	return retCode;
}
