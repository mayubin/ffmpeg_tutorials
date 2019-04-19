//
// Created by wangrl on 19-4-19.
//

#pragma once

#include <cassert>
#include "SkTypes.h"

// 64bit -> 32bit utilities

// Handy util that can be pass two ints, and will automatically promote to
// 64 bits before the multiply, so the caller doesn't have to remember to cast
// e.g. (int64_t)a * b;
static inline int64_t sk_64_mul(int64_t a, int64_t b) {
    return a * b;
}

// 不超过最大值

/**
 * Given an integer and a positive (max) integer, return the value
 * pinned against 0 and max, inclusive.
 * @param value     The value we want returned pinned between [0...max]
 * @param max       The positive max value
 * @return 0 if value < 0, max if value > max, else value
 */
static inline int SkClampMax(int value, int max) {
    // ensure that max is positive
    assert(max >= 0);
    if (value < 0) {
        value = 0;
    }
    if (value > max) {
        value = max;
    }
    return value;
}

/**
 * Returns true if value is a power of 2. Does not explicitly check for
 * value <= 0.
 */
template <typename T> constexpr inline bool SkIsPow2(T value) {
    return (value & (value - 1)) == 0;
}
