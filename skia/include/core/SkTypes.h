//
// Created by wangrl on 19-4-17.
//

#pragma once

/**
 * Called internally if we hit an unrecoverable error.
 * The platform implementation must not return, but should either throw
 * an exception or otherwise exit.
 */
extern void sk_abort_no_print(void);

void SkDebugf(const char format[], ...);

