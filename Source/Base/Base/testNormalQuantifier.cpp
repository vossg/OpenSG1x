
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

	OSG::UInt32 i, nCount, index, retIndex;
	OSG::NormalQuantifier nq;
	OSG::Vec3f vec, retVec;
  OSG::Real32 dot;

  std::cout << "Build NormalQuantifier with 4 subdivisions" << std::endl;

	nq.build(4);

	nCount = nq.getNormalCount();

	std::cout << "Normal count: " << nCount << std::endl;

	// Run some random tests
	for (i = 0; i < 10; i++)
	{
    std::cout << "-----------------------------------------------\n";

		index = OSG::UInt32(double(nCount)*rand()/(RAND_MAX+1.0));
		std::cout << "index:    " << index;
		vec = nq.getNormal(index);
		std::cout << ", vec: " << vec;
    std::cout << std::endl;

		retIndex = nq.getIndex(vec);
		std::cout << "retIndex: " << retIndex;
		retVec = nq.getNormal(retIndex);
		std::cout << ", retVec: " << retVec;
		std::cout << std::endl;

    dot = vec.dot(retVec);
		std::cout << "dot: " << dot;
    std::cout << std::endl;
	}

	return retCode;
}
