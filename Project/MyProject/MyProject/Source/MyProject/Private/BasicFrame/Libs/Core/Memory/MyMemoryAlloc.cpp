#include "MyProject.h"
#include "MyMemoryAlloc.h"

void* operator new(size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz, file, line, func);
}

void* operator new(size_t sz, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz);
}

void* operator new(size_t sz, void* ptr, MyMemoryConstructorFlag constructorFlag)
{
	(void)sz;
	return ptr;
}

void* operator new[](size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz, file, line, func);
}

void* operator new[](size_t sz, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz);
}

void operator delete(void* ptr, MyMemoryConstructorFlag constructorFlag)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void operator delete(void* ptr, void*, MyMemoryConstructorFlag constructorFlag)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void operator delete(void* ptr, const char*, int, const char*, MyMemoryConstructorFlag constructorFlag)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void operator delete[](void* ptr, MyMemoryConstructorFlag constructorFlag)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void operator delete[](void* ptr, const char*, int, const char*, MyMemoryConstructorFlag constructorFlag)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}