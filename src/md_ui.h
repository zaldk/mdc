/*
Single header style library for Material Design
All measurements are in mm, unless stated otherwise.
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

#define MD_ENUM(type, name) typedef type name; enum

#include <stdio.h>
#define MD_PRINTF printf
#ifdef NO_LOGGING
#       define MD_LOG(...) (void)0
#else
#       define MD_LOG(log_type, fmt, ...) MD_PRINTF(log_type "\t%s:%d\t" fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif
#ifdef NO_ANSI
#       define ANSI_CLEAR ""
#       define ANSI_DEBUG ""
#       define ANSI_INFO  ""
#       define ANSI_WARN  ""
#       define ANSI_ERROR ""
#else
#       define ANSI_CLEAR "\e[0m"
#       define ANSI_DEBUG "\e[1;90m"
#       define ANSI_INFO  "\e[1;34m"
#       define ANSI_WARN  "\e[1;33m"
#       define ANSI_ERROR "\e[1;31m"
#endif
#define MD_DEBUG(fmt, ...) MD_LOG(ANSI_DEBUG "<DEBUG>" ANSI_CLEAR, fmt, ##__VA_ARGS__)
#define MD_INFO(fmt,  ...) MD_LOG(ANSI_INFO  "<INFO>"  ANSI_CLEAR, fmt, ##__VA_ARGS__)
#define MD_WARN(fmt,  ...) MD_LOG(ANSI_WARN  "<WARN>"  ANSI_CLEAR, fmt, ##__VA_ARGS__)
#define MD_ERROR(fmt, ...) MD_LOG(ANSI_ERROR "<ERROR>" ANSI_CLEAR, fmt, ##__VA_ARGS__)

#include "colors_material_palettes.h"
#include "colors_material_schemes.h"

typedef struct {
    u8 r, g, b, a;
} color_t;
#define COLOR_INVALID (color_t){0xFF,0,0xFF,0xFF}
#define COLOR_UNSET(C) ((C).r == 0 && (C).g == 0 && (C).b == 0 && (C).a == 0)
#define COLOR_EQ(A,B) ((A).r == (B).r && (A).g == (B).g && (A).b == (B).b && (A).a == (B).a)

static struct {
    /* {{{ */
    color_t Black, White, Transparent;
    color_t Blue[101], Yellow[101], Red[101], Purple[101], Cyan[101], Grey[101], Green[101], Orange[101], Pink[101];
    color_t Primary[101], Secondary[101], Tertiary[101], Neutral[101], Error[101];
    struct {
        color_t Primary;
        color_t OnPrimary;
        color_t PrimaryContainer;
        color_t OnPrimaryContainer;
        color_t PrimaryFixed;
        color_t OnPrimaryFixed;
        color_t PrimaryFixedDim;
        color_t OnPrimaryFixedVariant;
        color_t InversePrimary;
        color_t Secondary;
        color_t OnSecondary;
        color_t SecondaryContainer;
        color_t OnSecondaryContainer;
        color_t SecondaryFixed;
        color_t OnSecondaryFixed;
        color_t SecondaryFixedDim;
        color_t OnSecondaryFixedVariant;
        color_t Tertiary;
        color_t OnTertiary;
        color_t TertiaryContainer;
        color_t OnTertiaryContainer;
        color_t TertiaryFixed;
        color_t OnTertiaryFixed;
        color_t TertiaryFixedDim;
        color_t OnTertiaryFixedVariant;
        color_t Error;
        color_t OnError;
        color_t ErrorContainer;
        color_t OnErrorContainer;
        color_t Surface;
        color_t OnSurface;
        color_t SurfaceVariant;
        color_t OnSurfaceVariant;
        color_t SurfaceContainerHighest;
        color_t SurfaceContainerHigh;
        color_t SurfaceContainer;
        color_t SurfaceContainerLow;
        color_t SurfaceContainerLowest;
        color_t InverseSurface;
        color_t InverseOnSurface;
        color_t SurfaceTint;
        color_t Outline;
        color_t OutlineVariant;
        color_t SurfaceBright;
        color_t SurfaceDim;
        color_t Background;
        color_t OnBackground;
    } Scheme, SchemeDark, SchemeLight; // [0] == Dark; [1] == Light
    /* }}} */
} COLOR = {0}; // Global Color Lookup

void md_color_global_init(bool interpolate);
void md_color_global_set_theme(u8 theme);
void md_color_global_switch_theme();

typedef struct {
    f32 x, y;
} vec2;

typedef struct {
    f32 x, y, w, h;
} box_t;

MD_ENUM(u8, md_align_t) {
    MD_ALIGN_START,
    MD_ALIGN_CENTER,
    MD_ALIGN_END,
};
typedef struct {
    md_align_t x, y;
} md_text_align_t;

typedef struct {
    f32 tl, tr, br, bl;
} md_corners_t;
static const f32 MD_ROUND_NONE     =    0;
static const f32 MD_ROUND_SMALLEST =    1;
static const f32 MD_ROUND_SMALL    =    2;
static const f32 MD_ROUND_MEDIUM   =    5;
static const f32 MD_ROUND_LARGE    =   10;
static const f32 MD_ROUND_LARGEST  =   20;
static const f32 MD_ROUND_FULL     = 9999;

#define MD_COMMANDS_MAXIMUM_QUANTITY 1024
typedef u8 md_command_type_t; enum {
    MD_COMMAND_DRAW_BOX,
    MD_COMMAND_DRAW_TEXT,
};
typedef struct {
    md_command_type_t type;
    union {
        struct {
            box_t box;
            color_t color;
            md_corners_t round;
        } draw_box;
    } cmd;
} md_command_t;

typedef struct {
    vec2 scaling_factor; // global scaling of the window manager
    vec2 monitor_size; // physical size, in mm
    vec2 monitor_resolution; // width and height, in pixels

    md_command_t* cmd_list; // must be at least MD_COMMANDS_MAXIMUM_QUANTITY
    u32 cmd_list_len;
} md_ctx_t;
static md_ctx_t CTX = {0};

void md_ctx_init(vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory);
void md_ctx_init_ctx(md_ctx_t* ctx, vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory);
bool md_ctx_append_command(md_command_t cmd);
bool md_ctx_append_command_ctx(md_ctx_t* ctx, md_command_t cmd);

f32 md_px2mm(i32 px);
f32 md_px2mm_ctx(md_ctx_t* ctx, i32 px);
i32 md_mm2px(f32 mm);
i32 md_mm2px_ctx(md_ctx_t* ctx, f32 mm);

/* https://m3.material.io/components/buttons/overview */
MD_ENUM(u8, md_button_state_t) {
    MD_BUTTON_STATE_DEFAULT,
    MD_BUTTON_STATE_DISABLED,
    MD_BUTTON_STATE_HOVERED,
    MD_BUTTON_STATE_FOCUSED,
    MD_BUTTON_STATE_PRESSED,
};
MD_ENUM(u8, md_button_toggle_t) {
    MD_BUTTON_TOGGLE_SELECTED,   // only for TOGGLE type
    MD_BUTTON_TOGGLE_UNSELECTED, // only for TOGGLE type
};
MD_ENUM(u8, md_button_type_t) {
    MD_BUTTON_TYPE_DEFAULT, // button auto resets to default state after press
    MD_BUTTON_TYPE_TOGGLE,  // button does not auto reset to default state after press
};
MD_ENUM(u8, md_button_style_t) {
    MD_BUTTON_DESIGN_ELEVATED,
    MD_BUTTON_DESIGN_FILLED,
    MD_BUTTON_DESIGN_TONAL,
    MD_BUTTON_DESIGN_OUTLINED,
    MD_BUTTON_DESIGN_TEXT,
};
typedef void(*md_callback_button)(void*);
typedef struct {
    box_t box;          // X,Y - required; W,H - optional;
    md_corners_t round; // required
    color_t bg;         // optional
    f32 state_layer;

    const char* text;           // required
    md_text_align_t text_align; // optional
    color_t fg;                 // optional

    md_button_type_t type;     // required
    md_button_state_t state;   // optional
    md_button_toggle_t toggle; // optional
    md_button_style_t style;   // optional

    md_callback_button cb;     // optional
} md_button_t;

// When some info is omitted, the functions will fill it in and return the object back.
md_button_t md_button(md_button_t button);
md_button_t md_button_ctx(md_ctx_t* ctx, md_button_t button);



/* IMPLEMENTATION {{{ */

void md_ctx_init(vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory) {
    md_ctx_init_ctx(&CTX, scaling_factor, monitor_size, monitor_resolution, cmd_list_memory);
}
void md_ctx_init_ctx(md_ctx_t* ctx, vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory) {
    ctx->scaling_factor     = scaling_factor;
    ctx->monitor_size       = monitor_size;
    ctx->monitor_resolution = monitor_resolution;
    ctx->cmd_list = (md_command_t*)cmd_list_memory;
}

bool md_ctx_append_command(md_command_t cmd) { return md_ctx_append_command_ctx(&CTX, cmd); }
bool md_ctx_append_command_ctx(md_ctx_t* ctx, md_command_t cmd) {
    if (ctx->cmd_list == NULL) {
        MD_ERROR("Context memory not initialized.");
        return false;
    }
    if (ctx->cmd_list_len >= MD_COMMANDS_MAXIMUM_QUANTITY) {
        MD_ERROR("Context memory was not big enough.");
        return false;
    }
    ctx->cmd_list[ctx->cmd_list_len++] = cmd;
    return true;
}

md_button_t md_button(md_button_t button) { return md_button_ctx(&CTX, button); }
md_button_t md_button_ctx(md_ctx_t* ctx, md_button_t button) {
    u8 shadow_amount = 0;
    f32 state_layer = 0; // background shape, with foreground color, with opacity=state_layer

    switch (button.state) {
        case MD_BUTTON_STATE_DEFAULT: {
        }; break;
        case MD_BUTTON_STATE_DISABLED: {
            if (COLOR_UNSET(button.bg)) {
                button.bg = COLOR.Scheme.OnSurface;
                button.bg.a = (u8)((f32)button.bg.a * 0.1);
            }
            if (COLOR_UNSET(button.fg)) {
                button.fg = COLOR.Scheme.OnSurfaceVariant;
                button.fg.a = (u8)((f32)button.fg.a * 0.4);
            }
        }; break;
        case MD_BUTTON_STATE_HOVERED: {
            state_layer = 0.1; // should be 0.08
            shadow_amount += 1;
        }; break;
        case MD_BUTTON_STATE_FOCUSED: {
            state_layer = 0.15; // should be 0.1
        }; break;
        case MD_BUTTON_STATE_PRESSED: {
            state_layer = 0.15; // should be 0.1
        }; break;
        default: MD_ERROR("Unknown button state.");
    }

    switch (button.style) {
        case MD_BUTTON_DESIGN_ELEVATED: {
            if (button.state != MD_BUTTON_STATE_DISABLED) {
                shadow_amount += 1;
            }
            switch (button.type) {
                case MD_BUTTON_TYPE_DEFAULT: {
                    if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.SurfaceContainerLow;
                    if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.Primary;
                }; break;
                case MD_BUTTON_TYPE_TOGGLE: {
                    switch (button.toggle) {
                        case MD_BUTTON_TOGGLE_UNSELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.SurfaceContainerLow;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.Primary;
                        }; break;
                        case MD_BUTTON_TOGGLE_SELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.Primary;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnPrimary;
                        }; break;
                        default: MD_ERROR("Unknown button toggle.");
                    }
                }; break;
                default: MD_ERROR("Unknown button type.");
            }
        }; break;
        case MD_BUTTON_DESIGN_FILLED: {
            switch (button.type) {
                case MD_BUTTON_TYPE_DEFAULT: {
                    if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.Primary;
                    if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnPrimary;
                }; break;
                case MD_BUTTON_TYPE_TOGGLE: {
                    switch (button.toggle) {
                        case MD_BUTTON_TOGGLE_UNSELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.SurfaceContainer;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnSurfaceVariant;
                        }; break;
                        case MD_BUTTON_TOGGLE_SELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.Primary;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnPrimary;
                        }; break;
                        default: MD_ERROR("Unknown button toggle.");
                    }
                }; break;
                default: MD_ERROR("Unknown button type.");
            }
        }; break;
        case MD_BUTTON_DESIGN_TONAL: {
            switch (button.type) {
                case MD_BUTTON_TYPE_DEFAULT: {
                    if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.SecondaryContainer;
                    if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnSecondaryContainer;
                }; break;
                case MD_BUTTON_TYPE_TOGGLE: {
                    switch (button.toggle) {
                        case MD_BUTTON_TOGGLE_UNSELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.SecondaryContainer;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnSecondaryContainer;
                        }; break;
                        case MD_BUTTON_TOGGLE_SELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.Secondary;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnSecondary;
                        }; break;
                        default: MD_ERROR("Unknown button toggle.");
                    }
                }; break;
                default: MD_ERROR("Unknown button type.");
            }
        }; break;
        case MD_BUTTON_DESIGN_OUTLINED: {
            state_layer = 0.1;
            switch (button.type) {
                case MD_BUTTON_TYPE_DEFAULT: {
                    if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.OutlineVariant;
                    if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnSurfaceVariant;
                }; break;
                case MD_BUTTON_TYPE_TOGGLE: {
                    switch (button.toggle) {
                        case MD_BUTTON_TOGGLE_UNSELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.OutlineVariant;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.OnSurfaceVariant;
                        }; break;
                        case MD_BUTTON_TOGGLE_SELECTED: {
                            if (COLOR_UNSET(button.bg)) button.bg = COLOR.Scheme.InverseSurface;
                            if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.InverseOnSurface;
                        }; break;
                        default: MD_ERROR("Unknown button toggle.");
                    }
                }; break;
                default: MD_ERROR("Unknown button type.");
            }
        }; break;
        case MD_BUTTON_DESIGN_TEXT: {
            switch (button.type) {
                case MD_BUTTON_TYPE_DEFAULT: {
                    if (COLOR_UNSET(button.fg)) button.fg = COLOR.Scheme.Primary;
                }; break;
                default: MD_ERROR("Button style 'Text' does not support 'Toggle' type.");
            }
        }; break;
        default: MD_ERROR("Unknown button design.");
    }

    button.state_layer = state_layer;
    return button;
}

f32 md_px2mm(i32 px) { return md_px2mm_ctx(&CTX, px); }
f32 md_px2mm_ctx(md_ctx_t* ctx, i32 px) {
    return (f32)px * ctx->monitor_size.x / ctx->monitor_resolution.x;
}

i32 md_mm2px(f32 mm) { return md_mm2px_ctx(&CTX, mm); }
i32 md_mm2px_ctx(md_ctx_t* ctx, f32 mm) {
    return (i32) (mm * ctx->monitor_resolution.x / ctx->monitor_size.x);
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

void md_color_global_init(bool interpolate) {
    COLOR.Black = (color_t){0,0,0,255};
    COLOR.White = (color_t){255,255,255,255};
    // black transparent == unset
    // white transparent != unset
    COLOR.Transparent = (color_t){255,255,255,0};

    static color_t colors[101];
    memset(colors, 0, sizeof(color_t)*101);
    colors[0] = (color_t){0,0,0,0xFF};
    colors[100] = (color_t){0xFF,0xFF,0xFF,0xFF};

    // Baseline
    #define Y(NAME, Name) \
        COMBINE(MATERIAL_PALETTE_BASELINE_, NAME); \
        if (interpolate) _fill_in_gaps(colors); \
        for (u8 i = 0; i < 101; i++) ACCESS(Name)[i] = colors[i]; \
        memset(&colors[1], 0, sizeof(color_t)*99);

    #define COMBINE(A,B) A##B
    #define ACCESS(Name) COLOR.Name
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
        for (u8 i = 0; i < 101; i++) ACCESS(Name)[i] = colors[i]; \
        memset(&colors[1], 0, sizeof(color_t)*99);

    #define COMBINE(A,B) A##B
    #define ACCESS(Name) COLOR.Name
    #define X(NAME, P, R,G,B) colors[P] = (color_t){R,G,B,0xFF};
    COLOR_LABELS_STATIC
    #undef COMBINE
    #undef ACCESS
    #undef X
    #undef Y

    // Dark Scheme
    #define X(SchemeName, BaselineName, BaselineVariant) \
        COLOR.SchemeDark.SchemeName = COLOR.BaselineName[BaselineVariant];
    MATERIAL_SCHEME_DARK
    #undef X

    // Light Scheme
    #define X(SchemeName, BaselineName, BaselineVariant) \
        COLOR.SchemeLight.SchemeName = COLOR.BaselineName[BaselineVariant];
    MATERIAL_SCHEME_LIGHT
    #undef X

    md_color_global_set_theme(0);
}

void md_color_global_set_theme(u8 theme) {
    if (theme == 0) {
        COLOR.Scheme = COLOR.SchemeDark;
        return;
    }
    if (theme == 1) {
        COLOR.Scheme = COLOR.SchemeLight;
        return;
    }
    MD_ERROR("Invalid theme. Valid: 0/1; Provided: %d", theme);
    return;
}

void md_color_global_switch_theme() {
    if (COLOR_EQ(COLOR.Scheme.Primary, COLOR.SchemeDark.Primary)) {
        COLOR.Scheme = COLOR.SchemeLight;
    } else {
        COLOR.Scheme = COLOR.SchemeDark;
    }
}

/* }}} */

/* }}} */

#endif /* MD_UI */
