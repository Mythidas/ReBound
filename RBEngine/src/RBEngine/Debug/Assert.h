#pragma once

#ifdef RB_ASSERTS_ENABLED
#define RB_ASSERT(x, ...)	{ if(!(x)) { Log::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define RB_ASSERT(...)
#endif