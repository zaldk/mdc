/*
Single header style library for Material Design 3
*/

#ifndef M3_UI
#define M3_UI

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
} m3_ctx_t;
static m3_ctx_t CTX = {0};

void m3_ctx_set_dpi(i32 dpi);

// UM == Useful Measurement == 10mm ≈ 0.3937007874in
i32 m3_px2um(i32 px);
i32 m3_um2px(i32 um);



/* IMPLEMENTATION {{{ */

void m3_ctx_set_dpi(i32 dpi) {
    CTX.dpi = dpi;
}

i32 m3_px2um(i32 px) {

}

i32 m3_um2px(i32 um) {

}

/* }}} */

#endif
