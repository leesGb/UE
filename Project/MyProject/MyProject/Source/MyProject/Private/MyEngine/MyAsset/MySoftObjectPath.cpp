#include "MyProject.h"
#include "MySoftObjectPath.h"
#include "UtilStr.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

MySoftObjectPath::MySoftObjectPath()
{

}

MySoftObjectPath::~MySoftObjectPath()
{

}

void MySoftObjectPath::setPath(FString Path)
{
	this->mNativeSoftObjectPath.SetPath(Path);
}

void MySoftObjectPath::setPath(std::string path)
{
	this->mNativeSoftObjectPath.SetPath(UtilStr::ConvStdStr2FString(path));
}

UObject* MySoftObjectPath::tryLoad() const
{
	return this->mNativeSoftObjectPath.TryLoad();
}

UObject* MySoftObjectPath::resolveObject() const
{
	return this->mNativeSoftObjectPath.ResolveObject();
}

FSoftObjectPath& MySoftObjectPath::getNativeSoftObjectPath()
{
	return this->mNativeSoftObjectPath;
}

MY_END_NAMESPACE