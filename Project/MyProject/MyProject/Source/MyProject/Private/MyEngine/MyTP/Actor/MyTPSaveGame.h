#pragma once

#include "MySaveGameBase.h"
#include "MyTPSaveGame.generated.h"

/**
 * @url https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame/Code/index.html
 */

UCLASS()
class UMyTPSaveGame : public UMySaveGameBase
{
	GENERATED_UCLASS_BODY()

public:
	/** Loads user persistence data if it exists, creates an empty record otherwise. */
	static UMyTPSaveGame* LoadPersistentUser(FString SlotName, const int32 UserIndex);

private:
	/** The string identifier used to save/load this persistent user. */
	FString SlotName;
	int32 UserIndex;
};