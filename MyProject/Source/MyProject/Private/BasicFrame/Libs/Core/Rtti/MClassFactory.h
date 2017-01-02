#pragma once

#include <string>
#include <unordered_map>

class GObject;
class MClassInfo;

class MClassFactory
{
public:
    static MClassFactory* Instance();
    static void Destroy();

    void Register(const MClassInfo* rtti, const std::string& className);
    bool ClassExists(const std::string& className) const;
    const MClassInfo* GetClassRtti(const std::string& className) const;
	GObject* Create(const std::string& className) const;

private:
	MClassFactory();
    ~MClassFactory();

    static MClassFactory* Singleton;
    std::unordered_map<const std::string, const MClassInfo*> nameTable;
};