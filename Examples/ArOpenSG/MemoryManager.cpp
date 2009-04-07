/**************************************************************************
 *
 *                           ARToolKitPlus
 *
 *       This code is based on the work by Kato and Billinghurst
 *
 **************************************************************************
 *
 * $Id: MemoryManager.cpp,v 1.2 2009/04/07 17:09:28 neumannc Exp $
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


