
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGLog.h>

#include <OSGNormalQuantifier.h>

int main (int argc, char **argv)
{
	int retCode = 0;

	osg::UInt32 i, nCount, index, retIndex;
	osg::NormalQuantifier nq;
	osg::Vec3f vec, retVec;
  osg::Real32 dot;

  cout << "Build NormalQuantifier with 4 subdivisions" << endl;

	nq.build(4);

	nCount = nq.getNormalCount();

	cout << "Normal count: " << nCount << endl;

	// Run some random tests
	for (i = 0; i < 10; i++)
	{
    cout << "-----------------------------------------------\n";

		index = osg::UInt32(double(nCount)*rand()/(RAND_MAX+1.0));
		cout << "index:    " << index;
		vec = nq.getNormal(index);
		cout << ", vec: " << vec;
    cout << endl;

		retIndex = nq.getIndex(vec);
		cout << "retIndex: " << retIndex;
		retVec = nq.getNormal(retIndex);
		cout << ", retVec: " << retVec;
		cout << endl;

    dot = vec.dot(retVec);
		cout << "dot: " << dot;
    cout << endl;
	}

	return retCode;
}
