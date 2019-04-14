//
// Created by wangrl on 19-4-14.
//

#include <lzma.h>

int main(int argc, char *argv[]) {

    /**
     * Structure Declarations
     */

    // struct tag { member-list } variable_list;
    struct {
        int     a;
        char    b;
        float   c;
    } x;

    struct {
        int     a;
        char    b;
        float   c;
    } y[20], *z;

    // z = &x;      // illegal

    struct SIMPLE {
        int     a;
        char    b;
        float   c;
    };

    struct SIMPLE i;
    struct SIMPLE j[20], *k;

    typedef struct {
        int     a;
        char    b;
        float   c;
    } Simple;

    Simple o;
    Simple p[20], *q;

    // If you want to use particular structure in more than one source file, you should put
    // the tag declaration or typedef in a header file.

    /**
     * Structure Members
     */
    struct COMPLEX {
        float           f;
        int             a[20];
        long            *lp;
        struct SIMPLE   s;
        struct SIMPLE   sa[10];
        struct SIMPLE   *sp;
    };

    struct COMPLEX comp;

    // 访问其实不需要括号
    // ((comp.sa)[4]).c;

    // 不合法，无限引用。
    /*
    struct SELF_REF1 {
        int                 a;
        struct SELF_REF1    b;
        int                 c;
    };
    */

    struct SELF_REF2 {
        int                 a;
        struct SELF_REF2    *b;
        int                 c;
    };


    /**
     * Incomplete Declarations
     */
    struct  B;
    struct  A {
        struct      B *partner;
    };

    struct  B {
        struct      A *partner;
    };

    // Initializing Structures
    struct INIT_EX {
        int             a;
        short           b[10];
        Simple          c;
    } f = {
       10,
       {1, 2, 3, 4, 5},
       {25, 'x', 1.9}
    };

    typedef struct {
        int         a;
        short       b[2];
    } Ex2;

    typedef struct EX {
        int         a;
        char        b[3];
        Ex2         c;
        struct EX   *d;
    } Ex;

    Ex  e = {10, "Hi", {5, {-1, 25}}, 0};
    Ex *px = &e;

    // The expression *px + 1 is illegal, because the result of *px is a structure.

    *px->c.b;


    Ex h;
    e.d = &h;

    // Structure Storage Allocation
    struct ALIGN {
        char        a;
        int         b;
        char        c;
    };

    // 节省33%空间
    struct ALIGN2 {
        int     b;
        char    a;
        char    c;
    };

    // offsetoff(type, member)
    // return four
    offsetof(struct ALIGN, b);



    return 0;
}

// Structure as Function Arguments


