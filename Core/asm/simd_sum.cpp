#include "simd_sum.h"
#include <immintrin.h>

// Compiled with /arch:AVX2 -- caller must guard with CPUID check.
uint64_t SmonSumU64_AVX2(const uint64_t* data, uint32_t count)
{
    __m256i acc0 = _mm256_setzero_si256();
    __m256i acc1 = _mm256_setzero_si256();
    __m256i acc2 = _mm256_setzero_si256();
    __m256i acc3 = _mm256_setzero_si256();

    uint32_t i = 0;
    uint32_t unrolled = count & ~15u; // 4 accumulators x 4 lanes each = 16 per iteration

    for (; i < unrolled; i += 16) {
        acc0 = _mm256_add_epi64(acc0, _mm256_loadu_si256((const __m256i*)(data + i +  0)));
        acc1 = _mm256_add_epi64(acc1, _mm256_loadu_si256((const __m256i*)(data + i +  4)));
        acc2 = _mm256_add_epi64(acc2, _mm256_loadu_si256((const __m256i*)(data + i +  8)));
        acc3 = _mm256_add_epi64(acc3, _mm256_loadu_si256((const __m256i*)(data + i + 12)));
    }

    // Consume remaining full 256-bit chunks (groups of 4) with a single accumulator.
    uint32_t tail4 = (count - i) & ~3u;
    for (uint32_t j = 0; j < tail4; j += 4, i += 4)
        acc0 = _mm256_add_epi64(acc0, _mm256_loadu_si256((const __m256i*)(data + i)));

    // Reduce 4 accumulators to one __m256i.
    __m256i sum256 = _mm256_add_epi64(
                         _mm256_add_epi64(acc0, acc1),
                         _mm256_add_epi64(acc2, acc3));

    // Horizontal reduction: fold high 128 bits into low 128 bits.
    __m128i lo  = _mm256_castsi256_si128(sum256);
    __m128i hi  = _mm256_extracti128_si256(sum256, 1);
    __m128i sum128 = _mm_add_epi64(lo, hi);
    // sum128 holds [lane0+lane2, lane1+lane3]; add the two 64-bit halves.
    __m128i hi64   = _mm_unpackhi_epi64(sum128, sum128);
    __m128i total  = _mm_add_epi64(sum128, hi64);

    uint64_t result = (uint64_t)_mm_cvtsi128_si64(total);

    // Scalar tail for remaining elements (count % 4 != 0).
    for (; i < count; ++i)
        result += data[i];

    return result;
}
