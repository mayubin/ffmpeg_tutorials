//
// Created by wangrl on 19-4-17.
//

#pragma once

#include "core/SkPreConfig.h"
#include "core/SkPostConfig.h"


/**
 * Called internally if we hit an unrecoverable error.
 * The platform implementation must not return, but should either throw
 * an exception or otherwise exit.
 */
extern void sk_abort_no_print(void);

void SkDebugf(const char format[], ...);

/**
 * SkASSERT, SkASSERTF and SkASSERT_RELEASE can be used as stand alone assertion expressions, e.g.
 * uint32_t foo(int x) {
 *      SkASSERT(x > 4);
 *      return x - 4;
 * }
 */
#define SkASSERT_RELEASE(cond) \
        static_cast<void>( (cond) ? (void)0 : []{ SK_ABORT("assert(" #cond ")"); }() )

