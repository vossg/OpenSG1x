
#include <stdio.h>

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGLog.h>

#include <OSGNormalQuantifier.h>

int main (int argc, char **argv)
{
	int retCode = 0;

	osg::NormalQuantifier nq;

	FLOG (("Build NormalQuantifier with 4 subdivisions\n"));

	nq.build(4);

	FLOG (("Normal count: %d\n", nq.getNormalCount()));

	return retCode;
}
