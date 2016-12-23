template< class T >
T* EngineApi::CreateWidget(UWorld* World, UClass* UserWidgetClass)
{
	return CreateWidget<T>(World, UserWidgetClass);
}

template< class T >
T* EngineApi::CreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass)
{
	return CreateWidget<T>(OwningPlayer, UserWidgetClass);
}

template< class T >
T* EngineApi::CreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass)
{
	return CreateWidget<T>(OwningGame, UserWidgetClass);
}

template<class T>
TSubclassOf<T> EngineApi::FindClass(const TCHAR* ClassToFind)
{
	ConstructorHelpers::FClassFinder<T> findClass(ClassToFind);
	return findClass.Class;
}

template<class T>
T* EngineApi::FindObject(const TCHAR* ObjectToFind)
{
	ConstructorHelpers::FObjectFinder<T> findObject(ObjectToFind);
	return findObject.Object;
}