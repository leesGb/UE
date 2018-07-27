#pragma once

#include "MyProject.h"
#include "GameFramework/Actor.h"
#include "AnimateVertexPositionsBPFunctionLibrary.generated.h"

/**
* @brief https://wiki.unrealengine.com/Animated_Vertex_Positions_of_Character_Mesh,_How_To_Obtain_Them
*/

UCLASS()
class UAnimateVertexPositionsBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	bool AnimatedVertex__GetAnimatedVertexLocations(
		USkeletalMeshComponent* Mesh,
		TArray<FVector>& Locations,
		TArray<FMatrix>& CachedRefToLocals,
		const FSkeletalMeshLODRenderData& Model,
		FSkinWeightVertexBuffer& SkinWeightBuffer,
		bool PerformPawnVelocityCorrection
	);
};