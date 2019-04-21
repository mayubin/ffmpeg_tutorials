//
// Created by wangrl on 19-4-13.
//

#pragma once

typedef unsigned long ulong;
typedef unsigned        bool;
typedef  unsigned char * p_ubyte_;

/**
 * CRC Model Abstract Type
 *
 * The following type stores the context of an executing instance of the model
 * algorithm. Most of the fields are model parameters which must be set before
 * the first initializing call to cm_ini.
 */
typedef struct {
    int cm_width;       /* Parameter: Width in bits [8, 32]. */
    ulong cm_poly;      /* Parameter: The algorithm's polynomial. */
    ulong cm_init;      /* Parameter: Initial register value. */
    bool cm_refin;      /* Parameter: Reflect input bytes? */
    bool cm_refot;      /* Parameter: Reflect output CRC? */
    ulong cm_xorot;     /* Parameter: XOR this to output CRC. */

    ulong cm_reg;       /* Context: Context during execution. */
} cm_t;

typedef cm_t * p_cm_t;

/**
 * Functions That Implement The Model
 *
 * The following functions animate the cm_t abstraction.
 */

// Initializes the argument CRC model instance.
// All parameter fields must be set before calling this.
void cm_init(p_cm_t p_cm);

// Processes a single message byte [0, 255].
void cm_nxt(p_cm_t p_cm, int ch);

// Process a block of message bytes.
void cm_blk(p_cm_t p_cm, p_ubyte_ blk_adr, ulong blk_len);

// Returns the CRC value for the message bytes processed so far.
ulong cm_crc(p_cm_t p_cm);

/**
 * Functions For Table Calculation
 *
 * The following function can be used to calculate a CRC lookup table.
 * It can also be used at run-time to create or check static tables.
 */

// Returns the i'th entry for the lookup table for the specified algorithm.
// The function examines the fields cm_width, cm_poly, cm_refin, and the
// argument table index in the range [0,255] and returns the table entry in
// the bottom cm_width bytes of the return value.
ulong cm_tab(p_cm_t p_cm, int index);