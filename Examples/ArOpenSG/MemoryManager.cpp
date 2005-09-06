/**************************************************************************
 *
 *                           ARToolKitPlus
 *
 *       This code is based on the work by Kato and Billinghurst
 *
 **************************************************************************
 *
 * $Id: MemoryManager.cpp,v 1.1 2005/09/06 20:22:40 dirk Exp $
 *
 **************************************************************************
 *
 *  Author: Daniel Wagner
 *
 **************************************************************************/


#include <ARToolKitPlus/MemoryManager.h>
#include <malloc.h>


namespace ARToolKitPlus
{


MemoryManager* memManager = NULL;


ARTOOLKITPLUS_API void
setMemoryManager(MemoryManager* nManager)
{
	memManager = nManager;
}


ARTOOLKITPLUS_API MemoryManager*
getMemoryManager()
{
	return memManager;
}


void
artkp_Free(void* rawMemory)
{
	if(!rawMemory)
		return;

	if(memManager)
		memManager->releaseMemory(rawMemory);
	else
		::free(rawMemory);

	rawMemory = NULL;
}


}  // namespace ARToolKitPlus


