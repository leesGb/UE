#include "MyProject.h"
#include "TestClassBind.h"
#include "TestClass.h"
#include "LuaBindInc.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestClassBind::bind(lua_State* L)
{
	//luabridge::getGlobalNamespace(L)
	//	.beginClass<TestClass>("TestClass")
	//	//.addConstructor<void(*)(void)>()  // 如果有多个构造函数,则只能导出一个
	//	.addConstructor<void(*)(const std::string&)>()
	//	.addFunction("getLength", &TestClass::Length)
	//	.addFunction("startWith", &TestClass::StartWith)
	//	.addCFunction("startWith", &TestClass::Lua_StartWith)
	//	.endClass();

	LuaIntf::LuaBinding(L)
		.beginClass<TestClass>("TestClass")
		//.addConstructor<void(*)(const std::string&)>()	// LuaIntf 出错
		.addFunction("getLength", &TestClass::Length)
		.addFunction("startWith", &TestClass::StartWith)
		//.addCFunction("startWith", &TestClass::Lua_StartWith)
		.addFunction("startWith", &TestClass::Lua_StartWith)	// 只有 addFunction 没有 addCFunction
		.endClass();
}

MY_END_NAMESPACE