﻿#pragma once

#include "AuxMObjectLoaderBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "FormType.h"
#include "ResPackType.h"
#include "CoreInc.h"
#include "TypeDef.h"
#include "PlatformDefine.h"

class UClass;
class UUMGWidget;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 预制
 */
class AuxMUiClassLoader : public AuxMObjectLoaderBase
{
	M_DECLARE_CLASS(AuxMUiClassLoader, AuxMObjectLoaderBase)

protected:
	UMGOuterType mUMGOuterType;
	UClass* mWidgetClass;
	UUMGWidget* mWidgetObject;

public:
	AuxMUiClassLoader();

public:
	virtual void onPrefabLoaded(uint eventId, IDispatchObject* dispObj) override;
	void setUMGOuterType(UMGOuterType value);
	UUMGWidget* getWidgetObject();
	void insPrefab();
};

MY_END_NAMESPACE