
#include <stdio.h>

#include <iostream>

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGLog.h>

#include <OSGNormalQuantifier.h>

int main (int argc, char **argv)
{
	int retCode = 0;

	osg::UInt32 index, retIndex;
	osg::NormalQuantifier nq;
	osg::Vec3f vec(5,7,6);

	FLOG (("Build NormalQuantifier with 4 subdivisions\n"));

	nq.build(4);

	FLOG (("Normal count: %d\n", nq.getNormalCount()));

	index = nq.getNormalCount() / 2;

	vec = nq.getNormal(index);

	cout << vec << endl;

	retIndex = nq.getIndex(vec);

	cout << retIndex << endl;

	FLOG (("Index: %d\n", retIndex ));

	return retCode;
}
