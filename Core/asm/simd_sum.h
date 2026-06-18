#pragma once
#include <stdint.h>

// Sums an array of uint64_t values using AVX2 (256-bit SIMD).
// count is the number of elements. Does NOT require alignment.
uint64_t SmonSumU64_AVX2(const uint64_t* data, uint32_t count);
