#include "MyProject.h"
#include "MyTomGameEngine.h"
#include "Prequisites.h"
#include "MyTomPhysicsCollisionHandler.h"
#include "MyTomAvoidanceManager.h"
#include "MyTomLocalPlayer.h"

UMyTomGameEngine::UMyTomGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 全局物理碰撞处理
	this->PhysicsCollisionHandlerClass = UMyTomPhysicsCollisionHandler::StaticClass();
	this->AvoidanceManagerClass = UMyTomAvoidanceManager::StaticClass();
	// 等价于 MyProject\Config\DefaultEngine.ini 配置文件中的 LocalPlayerClassName 设置
	this->LocalPlayerClass = UMyTomLocalPlayer::StaticClass();
}

void UMyTomGameEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}