#pragma once

#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManagerBase.generated.h"

UCLASS()
class AMyPlayerCameraManagerBase : public APlayerCameraManager
{
	GENERATED_UCLASS_BODY()

public:

	/** normal FOV */
	float NormalFOV;

	/** targeting FOV */
	float TargetingFOV;

	/** After updating camera, inform pawn to update 1p mesh to match camera's location&rotation */
	virtual void UpdateCamera(float DeltaTime) override;
};
