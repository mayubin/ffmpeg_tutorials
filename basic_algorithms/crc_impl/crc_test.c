//
// Created by wangrl on 19-4-13.
//
/* How to Use CRC model                                                       */

/* Step 1: Declare a variable of type cm_t. Declare another variable          */
/*         (p_cm say) of type p_cm_t and initialize it to point to the first  */
/*         variable (e.g. p_cm_t p_cm = &cm_t).                               */
/*                                                                            */
/* Step 2: Assign values to the parameter fields of the structure.            */
/*         If you don't know what to assign, see the document cited earlier.  */
/*         For example:                                                       */
/*            p_cm->cm_width = 16;                                            */
/*            p_cm->cm_poly  = 0x8005L;                                       */
/*            p_cm->cm_init  = 0L;                                            */
/*            p_cm->cm_refin = TRUE;                                          */
/*            p_cm->cm_refot = TRUE;                                          */
/*            p_cm->cm_xorot = 0L;                                            */
/*         Note: Poly is specified without its top bit (18005 becomes 8005).  */
/*         Note: Width is one bit less than the raw poly width.               */
/*                                                                            */
/* Step 3: Initialize the instance with a call cm_ini(p_cm);                  */
/*                                                                            */
/* Step 4: Process zero or more message bytes by placing zero or more         */
/*         successive calls to cm_nxt. Example: cm_nxt(p_cm,ch);              */
/*                                                                            */
/* Step 5: Extract the CRC value at any time by calling crc = cm_crc(p_cm);   */
/*         If the CRC is a 16-bit value, it will be in the bottom 16 bits.    */

#include <stdlib.h>
#include <stdio.h>
#include "crc_model.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    cm_t c = {
            16,
            0x8005L,
            0L,
            TRUE,
            TRUE,
            0L
    };

    p_cm_t p_cm = &c;

    cm_init(p_cm);

    cm_nxt(p_cm, 8);    // 传递需要计算的数字

    printf("crc byte %lu\n", cm_crc(p_cm));

    // 可以传递一串数字进行计算。
    char *s = "123456789";

    cm_blk(p_cm, s, 9);

    printf("crc block %lu\n", cm_crc(p_cm));

    return EXIT_SUCCESS;
}