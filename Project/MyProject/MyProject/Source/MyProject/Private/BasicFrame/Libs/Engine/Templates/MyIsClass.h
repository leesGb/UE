// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

namespace MyNS
{
	/**
	 * Determines if T is a struct/class type
	 */
	template <typename T>
	struct TIsClass
	{
	private:
		template <typename U> static uint16 Func(int U::*);
		template <typename U> static uint8  Func(...);

	public:
		enum { Value = !__is_union(T) && sizeof(Func<T>(0)) - 1 };
	};
}