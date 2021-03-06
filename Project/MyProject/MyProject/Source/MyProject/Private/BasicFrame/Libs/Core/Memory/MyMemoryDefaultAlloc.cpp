#include "MyProject.h"
#include "MyMemoryDefaultAlloc.h"
#include <stdlib.h>	// malloc, free
#include "MyMemoryTracker.h"
#include "HAL/UnrealMemory.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

void* MyDefaultAllocImpl::allocBytes(
	size_t count,
    const char* file, 
	int line, const 
	char* func
)
{
	//void* ptr = FMemory::Malloc(count, 0);
    void* ptr = malloc(count);
#if MY_MEMORY_TRACKER
	MyMemoryTracker::get().recordAlloc(ptr, count, file, line, func);
#endif
    return ptr;
}

void MyDefaultAllocImpl::deallocBytes(void* ptr)
{
	if (!ptr)
	{
		return;
	}

#if MY_MEMORY_TRACKER
	MyMemoryTracker::get().recordDealloc(ptr);
#endif

	//FMemory::Free(ptr);
	free(ptr);
}

void* MyDefaultAllocImpl::allocBytesAligned(size_t align, size_t count,
    const char* file, int line, const char* func)
{
    void* ptr = _aligned_malloc(count, align);

#if MY_MEMORY_TRACKER
	MyMemoryTracker::get().recordAlloc(ptr, count, file, line, func);
#endif

    return ptr;
}

void MyDefaultAllocImpl::deallocBytesAligned(size_t align, void* ptr)
{
	if (!ptr)
	{
		return;
	}

#if MY_MEMORY_TRACKER
	MyMemoryTracker::get().recordDealloc(ptr);
#endif

	_aligned_free(ptr);
}

MY_END_NAMESPACE