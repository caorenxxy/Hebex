#ifndef HEBEX_H
#define HEBEX_H

#include <string>
#include <vector>
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <malloc.h>

#include <stdint.h>
#include <float.h>
#include <intrin.h>
#pragma warning(disable : 4305)  // double constant assigned to float
#pragma warning(disable : 4244)  // int -> float conversion
#pragma warning(disable : 4843)  // double -> float conversion
#pragma warning(disable : 4267)  // size_t -> int
#pragma warning(disable : 4838)  // another double -> int


// Global Macros
#define ALLOCA(TYPE, COUNT) (TYPE *) alloca((COUNT) * sizeof(TYPE))

#endif
