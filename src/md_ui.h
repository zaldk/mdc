/*
Single header style library for Material Design
*/

#ifndef MD_UI
#define MD_UI

#include <math.h>
#include <string.h>
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

typedef struct { f32 x, y; } vec2;
typedef struct { f32 x, y, w, h; } rect;

#include "colors_material_palettes.h"
#include "colors_material_schemes.h"

typedef struct { u8 r, g, b, a; } color_t;
#define COLOR_INVALID (color_t){0xFF,0,0xFF,0xFF}

static struct {
    struct {
        color_t Blue[101];
        color_t Yellow[101];
        color_t Red[101];
        color_t Purple[101];
        color_t Cyan[101];
        color_t Grey[101];
        color_t Green[101];
        color_t Orange[101];
        color_t Pink[101];
    } Static; // [0] == Black; [100] == White
    struct {
        color_t Primary[101];
        color_t Secondary[101];
        color_t Tertiary[101];
        color_t Neutral[101];
        color_t Error[101];
    } Baseline; // [0] == Black; [100] == White
    struct {
        color_t Primary[2];
        color_t OnPrimary[2];
        color_t PrimaryContainer[2];
        color_t OnPrimaryContainer[2];
        color_t PrimaryFixed[2];
        color_t OnPrimaryFixed[2];
        color_t PrimaryFixedDim[2];
        color_t OnPrimaryFixedVariant[2];
        color_t InversePrimary[2];
        color_t Secondary[2];
        color_t OnSecondary[2];
        color_t SecondaryContainer[2];
        color_t OnSecondaryContainer[2];
        color_t SecondaryFixed[2];
        color_t OnSecondaryFixed[2];
        color_t SecondaryFixedDim[2];
        color_t OnSecondaryFixedVariant[2];
        color_t Tertiary[2];
        color_t OnTertiary[2];
        color_t TertiaryContainer[2];
        color_t OnTertiaryContainer[2];
        color_t TertiaryFixed[2];
        color_t OnTertiaryFixed[2];
        color_t TertiaryFixedDim[2];
        color_t OnTertiaryFixedVariant[2];
        color_t Error[2];
        color_t OnError[2];
        color_t ErrorContainer[2];
        color_t OnErrorContainer[2];
        color_t Surface[2];
        color_t OnSurface[2];
        color_t SurfaceVariant[2];
        color_t OnSurfaceVariant[2];
        color_t SurfaceContainerHighest[2];
        color_t SurfaceContainerHigh[2];
        color_t SurfaceContainer[2];
        color_t SurfaceContainerLow[2];
        color_t SurfaceContainerLowest[2];
        color_t InverseSurface[2];
        color_t InverseOnSurface[2];
        color_t SurfaceTint[2];
        color_t Outline[2];
        color_t OutlineVariant[2];
        color_t SurfaceBright[2];
        color_t SurfaceDim[2];
        color_t Background[2];
        color_t OnBackground[2];
    } Scheme; // [0] == Dark; [1] == Light
} COLOR = {0}; // Global Color Lookup

void md_init_global_color(bool interpolate);

typedef struct {
    vec2 scaling_factor; // global scaling of the window manager
    vec2 monitor_size; // physical size, in mm
    vec2 monitor_resolution; // width and height, in pixels
} md_ctx_t;
static md_ctx_t CTX = {0};

void md_ctx_init(vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution);

// UM == Useful Measurement == 10mm ≈ 0.3937007874in
i32 md_px2um(i32 px);
i32 md_um2px(i32 um);



/* IMPLEMENTATION {{{ */

void md_ctx_init(vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution) {
    CTX.scaling_factor     = scaling_factor;
    CTX.monitor_size       = monitor_size;
    CTX.monitor_resolution = monitor_resolution;
}

i32 md_px2um(i32 px) {
    return (i32) ((f32)px * CTX.monitor_size.x / CTX.monitor_resolution.x / 10.0);
}

i32 md_um2px(i32 um) {
    return (i32) ((f32)um * CTX.monitor_resolution.x / CTX.monitor_size.x * 10.0);
}

/* Color Initialization Macro Magic {{{ */
void _fill_in_gaps(color_t* colors) {
    for (u8 i = 1; i < 100; i++) {
        if (colors[i].a != 0) continue;
        color_t prev, next;
        i8 iprev, inext;
        for (iprev = i; iprev >= 0; iprev--) {
            if (colors[iprev].a != 0) {
                prev = colors[iprev];
                break;
            }
        }
        for (inext = i; inext < 101; inext++) {
            if (colors[inext].a != 0) {
                next = colors[inext];
                break;
            }
        }
        f32 p = ((f32)i - (f32)iprev) / ((f32)inext - (f32)iprev);
        colors[i].r = prev.r + (u8)(((f32)next.r - (f32)prev.r)*p);
        colors[i].g = prev.g + (u8)(((f32)next.g - (f32)prev.g)*p);
        colors[i].b = prev.b + (u8)(((f32)next.b - (f32)prev.b)*p);
        colors[i].a = 0xFF;
    }
}

void md_init_global_color(bool interpolate) {
    static color_t colors[101];
    memset(colors, 0, sizeof(color_t)*101);
    colors[0] = (color_t){0,0,0,0xFF};
    colors[100] = (color_t){0xFF,0xFF,0xFF,0xFF};

    // Baseline
    #define Y(NAME, Name) \
        COMBINE(MATERIAL_PALETTE_BASELINE_, NAME); \
        if (interpolate) _fill_in_gaps(colors); \
        for (u8 i = 0; i < 101; i++) ACCESS(Baseline,Name)[i] = colors[i]; \
        memset(&colors[1], 0, sizeof(color_t)*99);

    #define COMBINE(A,B) A##B
    #define ACCESS(A,B) COLOR.A.B
    #define X(NAME, P, R,G,B) colors[P] = (color_t){R,G,B,0xFF};
    COLOR_LABELS_BASELINE
    #undef COMBINE
    #undef ACCESS
    #undef X
    #undef Y

    // Static
    #define Y(NAME, Name) \
        COMBINE(MATERIAL_PALETTE_STATIC_, NAME); \
        if (interpolate) _fill_in_gaps(colors); \
        for (u8 i = 0; i < 101; i++) ACCESS(Static,Name)[i] = colors[i]; \
        memset(&colors[1], 0, sizeof(color_t)*99);

    #define COMBINE(A,B) A##B
    #define ACCESS(A,B) COLOR.A.B
    #define X(NAME, P, R,G,B) colors[P] = (color_t){R,G,B,0xFF};
    COLOR_LABELS_STATIC
    #undef COMBINE
    #undef ACCESS
    #undef X
    #undef Y

    // Dark Scheme
    #define X(SchemeName, BaselineName, BaselineVariant) \
        COLOR.Scheme.SchemeName[0] = COLOR.Baseline.BaselineName[BaselineVariant];
    MATERIAL_SCHEME_DARK
    #undef X

    // Light Scheme
    #define X(SchemeName, BaselineName, BaselineVariant) \
        COLOR.Scheme.SchemeName[1] = COLOR.Baseline.BaselineName[BaselineVariant];
    MATERIAL_SCHEME_LIGHT
    #undef X
}
/* }}} */

/* }}} */

#endif /* MD_UI */

    // MATERIAL_PALETTE_BASELINE_PRIMARY;   _fill_in_gaps(colors); for (u8 i = 0; i < 101; i++) COLOR.Baseline.Primary[i]   = colors[i]; memset(&colors[1], 0, sizeof(color_t)*99);
    // MATERIAL_PALETTE_BASELINE_SECONDARY; _fill_in_gaps(colors); for (u8 i = 0; i < 101; i++) COLOR.Baseline.Secondary[i] = colors[i]; memset(&colors[1], 0, sizeof(color_t)*99);
    // MATERIAL_PALETTE_BASELINE_TERTIARY;  _fill_in_gaps(colors); for (u8 i = 0; i < 101; i++) COLOR.Baseline.Tertiary[i]  = colors[i]; memset(&colors[1], 0, sizeof(color_t)*99);
