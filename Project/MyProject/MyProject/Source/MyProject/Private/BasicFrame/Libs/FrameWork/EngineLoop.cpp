﻿#include "MyProject.h"
#include "EngineLoop.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

EngineLoop::EngineLoop()
{

}

void EngineLoop::init()
{

}

void EngineLoop::dispose()
{

}

void EngineLoop::MainLoop()
{
	// 每一帧处理
	// 处理 input
	//Ctx.mInstance.mInputMgr.handleKeyBoard();

	// 处理客户端的各类消息
	// 处理客户端自己的消息机制
	//MsgRouteBase routeMsg = nullptr;
	//while ((routeMsg = Ctx.mInstance.mSysMsgRoute.pop()) != nullptr)
	//{
	//	Ctx.mInstance.mMsgRouteNotify.handleMsg(routeMsg);
	//}

	// 处理网络
	//if (!Ctx.mInstance.mNetCmdNotify.isStopNetHandle)
	//{
	//    MByteBuffer ret = nullptr;
	//    while ((ret = Ctx.mInstance.mNetMgr.getMsg()) != nullptr)
	//    {
	//        if (nullptr != Ctx.mInstance.mNetCmdNotify)
	//        {
	//            Ctx.mInstance.mNetCmdNotify.addOneHandleMsg();
	//            Ctx.mInstance.mNetCmdNotify.handleMsg(ret);       // CS 中处理
	//            Ctx.mInstance.mLuaSystem.receiveToLuaRpc(ret);    // Lua 中处理
	//        }
	//    }
	//}

	// 填充数据到 KBEngine ，使用 KBEngine 引擎的逻辑解析
	//if (!Ctx.mInstance.mNetCmdNotify.isStopNetHandle)
	//{
	//    MByteBuffer ret = nullptr;
	//    while ((ret = Ctx.mInstance.mNetMgr.getMsg_KBE()) != nullptr)
	//    {
	//        Ctx.mInstance.mMKBEMainEntry.gameapp.pushBuffer(ret.dynBuffer.buffer, ret.dynBuffer.size);
	//    }
	//}

	// KBEngine 引擎逻辑处理
	//Ctx.mInstance.mMKBEMainEntry.FixedUpdate();

	// 每一帧的游戏逻辑处理
	GProcessSys->ProcessNextFrame();
	// 日志处理
	//Ctx.mInstance.mLogSys.updateLog();
}

void EngineLoop::FixedUpdate()
{
	//Ctx.mInstance.fixUpdateActor();
}

// 循环执行完成后，再次
void EngineLoop::postUpdate()
{
	//Ctx.mInstance.mPlayerMgr.postUpdate();
}

MY_END_NAMESPACE