#pragma once

#include "MySmDelegateCombinations.h"

MY_DECLARE_DELEGATE_ThreeParams(MyCommonDelegate, int, int, bool);

namespace MyNS
{
	class AppFrame
	{
	protected:
		MyCommonDelegate mCommonDelegate;

	public:
		AppFrame();
		~AppFrame();

		void init();
		void dispose();

		void handle(int aaa, int bbb, bool ccc);
	};

	void handle(int aaa, int bbb, bool ccc);
	static void staticHandle(int aaa, int bbb, bool ccc);
}