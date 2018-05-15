// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

namespace MyNS
{
	/**
	 * A functor which returns whatever is passed to it.  Mainly used for generic composition.
	 */
	struct FIdentityFunctor
	{
		template <typename T>
		FORCEINLINE T&& operator()(T&& Val) const
		{
			return (T&&)Val;
		}
	};
}