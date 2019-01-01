#ifndef HEBEX_H
#define HEBEX_H

#pragma warning(disable : 4305)  // double constant assigned to float
#pragma warning(disable : 4244)  // int -> float conversion
#pragma warning(disable : 4843)  // double -> float conversion
#pragma warning(disable : 4267)  // size_t -> int
#pragma warning(disable : 4838)  // another double -> int

#if (defined _MSC_VER && _MSC_VER < 1500)
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else 
#include <stdint.h> 
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <float.h>
#endif



#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <iostream>

#include <malloc.h>
#include <stdint.h>
#include <float.h>
#include <intrin.h>
#include <string.h>

#ifndef L1_CACHE_LINE_SIZE
#define L1_CACHE_LINE_SIZE 64
#endif

// Global Macros
#define ALLOCA(TYPE, COUNT) (TYPE *) alloca((COUNT) * sizeof(TYPE))

#define HEBEX_ASSERT(expr) \
	do { if(!(expr)) { std::cerr << "Error: assertion `"#expr"' failed at " << __FILE__ << ":" << __LINE__ << std::endl; exit(2); } } while(0)
#else

#endif
