#pragma once

#include "MyPlayerStartBase.h"
#include "MyFlyPlayerStart.generated.h"

UCLASS(config=Game)
class AMyFlyPlayerStart : public AMyPlayerStartBase
{
	GENERATED_BODY()

public:
	AMyFlyPlayerStart(const FObjectInitializer& ObjectInitializer);
	bool GetIsPlayerOnly();
};