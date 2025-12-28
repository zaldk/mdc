/*
Single header style library for Material Design
*/

#ifndef MD_UI
#define MD_UI

#include <stdint.h>
#include <stdbool.h>
typedef uint8_t      u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef uintptr_t usize;
typedef int8_t       i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;
typedef intptr_t  isize;
typedef float       f32;
typedef double      f64;

typedef struct {
    i32 dpi;
} md_ctx_t;
static md_ctx_t CTX = {0};

void md_ctx_set_dpi(i32 dpi);

// UM == Useful Measurement == 10mm ≈ 0.3937007874in
i32 md_px2um(i32 px);
i32 md_um2px(i32 um);



/* IMPLEMENTATION {{{ */

void md_ctx_set_dpi(i32 dpi) {
    CTX.dpi = dpi;
}

i32 md_px2um(i32 px) {
    return px;
}

i32 md_um2px(i32 um) {
    return um;
}

/* }}} */

#endif /* MD_UI */
