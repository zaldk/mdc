/*
Single header style library for Material Design
All measurements are in mm, unless stated otherwise.
*/

#ifndef MD_UI /* {{{ */
#define MD_UI

#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

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

#define ABS(x) ((x)>=0?(x):-(x))
#define MAX(a,b) ((a)>=(b)?(a):(b))
#define MIN(a,b) ((a)<=(b)?(a):(b))
#define MD_ENUM(type, name) typedef type name; enum

#define UNUSED(X) ((void)X)
#define UNREACHABLE(S) assert(0 && (#S))

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

#if defined(RAYLIB_H)
    typedef Color color_t;
#else
    typedef struct { u8 r, g, b, a; } color_t;
#endif

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

#if defined(RAYLIB_H)
    typedef Vector2 vec2;
#else
    typedef struct { f32 x, y; } vec2;
#endif
typedef struct { f32 x, y, w, h; } box_t;

MD_ENUM(u8, md_align_t) {
    MD_ALIGN_START,
    MD_ALIGN_CENTER,
    MD_ALIGN_END,
};
typedef struct { md_align_t x, y; } md_text_align_t;

typedef struct { f32 tl, tr, bl, br; } md_corners_t;
static const f32 MD_ROUND_NONE     =   0;
static const f32 MD_ROUND_SMALLEST =   1;
static const f32 MD_ROUND_SMALL    =   2;
static const f32 MD_ROUND_MEDIUM   =   5;
static const f32 MD_ROUND_LARGE    =  10;
static const f32 MD_ROUND_LARGEST  =  20;
static const f32 MD_ROUND_FULL     = 100;

#define MD_COMMANDS_MAXIMUM_QUANTITY 1024
typedef u8 md_command_type_t; enum {
    MD_COMMAND_DRAW_NONE,
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
        } box;
        struct {
            box_t box; // width and height are for scissor mode, ignored if 0
            char* text;
            color_t color;
            f32 font_size;
        } text;
    } as;
} md_command_t;

typedef vec2 (*md_measure_text_fn)(char* text, f32 font_size);

typedef struct {
    vec2 scaling_factor; // global scaling of the window manager
    vec2 monitor_size; // physical size, in mm
    vec2 monitor_resolution; // width and height, in pixels

    md_measure_text_fn measure_text; // required
    f32 font_size;

    md_command_t* cmd_list; // must be at least MD_COMMANDS_MAXIMUM_QUANTITY
    u32 cmd_list_len;
    u32 cmd_list_poll_index;
} md_ctx_t;
static md_ctx_t CTX = {0};

void md_ctx_init(vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory, md_measure_text_fn fn);
void md_ctx_init_ctx(md_ctx_t* ctx, vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory, md_measure_text_fn fn);
bool md_ctx_append(md_command_t cmd);
bool md_ctx_append_ctx(md_ctx_t* ctx, md_command_t cmd);
bool md_ctx_poll(md_command_t* cmd);
bool md_ctx_poll_ctx(md_ctx_t* ctx, md_command_t* cmd);

f32 md_px2mm(i32 px);
f32 md_px2mm_ctx(md_ctx_t* ctx, i32 px);
i32 md_mm2px(f32 mm);
i32 md_mm2px_ctx(md_ctx_t* ctx, f32 mm);

/* https://m3.material.io/components/buttons/overview */
MD_ENUM(u8, md_button_state_t) {
    MD_BUTTON_STATE_ENABLED,
    MD_BUTTON_STATE_DISABLED,
    MD_BUTTON_STATE_HOVERED,
    MD_BUTTON_STATE_FOCUSED,
    MD_BUTTON_STATE_PRESSED,
};
MD_ENUM(u8, md_button_type_t) {
    MD_BUTTON_TYPE_DEFAULT,    // normal
    MD_BUTTON_TYPE_UNSELECTED, // toggle - off
    MD_BUTTON_TYPE_SELECTED,   // toggle - on
};
MD_ENUM(u8, md_button_design_t) {
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
    u8 state_layer, elevation;

    char* text;                 // required
    md_text_align_t text_align; // optional
    color_t fg;                 // optional

    md_button_type_t type;     // required
    md_button_state_t state;   // optional
    md_button_design_t design; // optional

    md_callback_button cb;     // optional
} md_button_t;

// When some info is omitted, the functions will fill it in and return the object back.
md_button_t md_button(md_button_t button);
md_button_t md_button_ctx(md_ctx_t* ctx, md_button_t button);
bool md_render_button(md_button_t button);
bool md_render_button_ctx(md_ctx_t* ctx, md_button_t button);

#endif /* MD_UI }}} */



#ifdef MD_UI_IMPLEMENTATION /* {{{ */

void md_ctx_init(vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory, md_measure_text_fn fn) {
    md_ctx_init_ctx(&CTX, scaling_factor, monitor_size, monitor_resolution, cmd_list_memory, fn);
}
void md_ctx_init_ctx(md_ctx_t* ctx, vec2 scaling_factor, vec2 monitor_size, vec2 monitor_resolution, void* cmd_list_memory, md_measure_text_fn fn) {
    ctx->scaling_factor     = scaling_factor;
    ctx->monitor_size       = monitor_size;
    ctx->monitor_resolution = monitor_resolution;
    ctx->measure_text       = fn;
    ctx->font_size          = md_mm2px_ctx(ctx, 4);
    ctx->cmd_list = (md_command_t*)cmd_list_memory;
}

bool md_ctx_append(md_command_t cmd) { return md_ctx_append_ctx(&CTX, cmd); }
bool md_ctx_append_ctx(md_ctx_t* ctx, md_command_t cmd) {
    if (ctx->cmd_list == NULL) {
        MD_ERROR("Context memory not initialized.");
        UNREACHABLE();
        return false;
    }
    if (ctx->cmd_list_len >= MD_COMMANDS_MAXIMUM_QUANTITY) {
        MD_ERROR("Context memory was not big enough.");
        UNREACHABLE();
        return false;
    }
    ctx->cmd_list[ctx->cmd_list_len++] = cmd;
    return true;
}

bool md_ctx_poll(md_command_t* cmd) { return md_ctx_poll_ctx(&CTX, cmd); }
bool md_ctx_poll_ctx(md_ctx_t* ctx, md_command_t* cmd) {
    if (ctx->cmd_list == NULL) {
        MD_ERROR("Context memory not initialized.");
        UNREACHABLE();
        return false;
    }
    if (ctx->cmd_list_len == 0) {
        return false;
    }
    if (ctx->cmd_list_poll_index >= ctx->cmd_list_len) {
        ctx->cmd_list_len = 0;
        ctx->cmd_list_poll_index = 0;
        return false;
    }
    *cmd = ctx->cmd_list[ctx->cmd_list_poll_index++];
    return true;
}

md_button_t md_button(md_button_t button) { return md_button_ctx(&CTX, button); }
md_button_t md_button_ctx(md_ctx_t* ctx, md_button_t button) {
    // {{{
    #define TRY_SET(var, col) (COLOR_UNSET(var) ? ((var) = (col), true) : (false))
    UNUSED(ctx);

    bool d_ele=0, d_fil=0, d_ton=0, d_out=0, d_txt=0;
    switch (button.design) {
        // {{{
        case MD_BUTTON_DESIGN_ELEVATED: d_ele=1; break;
        case MD_BUTTON_DESIGN_FILLED:   d_fil=1; break;
        case MD_BUTTON_DESIGN_TONAL:    d_ton=1; break;
        case MD_BUTTON_DESIGN_OUTLINED: d_out=1; break;
        case MD_BUTTON_DESIGN_TEXT:     d_txt=1; break;
        default: MD_ERROR("Unknown button design."); UNREACHABLE();
        // }}}
    }

    bool s_ena=0, s_dis=0, s_hov=0, s_foc=0, s_pre=0;
    switch (button.state) {
        // {{{
        case MD_BUTTON_STATE_ENABLED:  s_ena=1; break;
        case MD_BUTTON_STATE_DISABLED: s_dis=1; break;
        case MD_BUTTON_STATE_HOVERED:  s_hov=1; break;
        case MD_BUTTON_STATE_FOCUSED:  s_foc=1; break;
        case MD_BUTTON_STATE_PRESSED:  s_pre=1; break;
        default: MD_ERROR("Unknown button state."); UNREACHABLE();
        // }}}
    }

    bool t_def=0, t_uns=0, t_sel=0;
    switch (button.type) {
        // {{{
        case MD_BUTTON_TYPE_DEFAULT: t_def=1; break;
        case MD_BUTTON_TYPE_UNSELECTED: t_uns=1; break;
        case MD_BUTTON_TYPE_SELECTED:   t_sel=1; break;
        default: MD_ERROR("Unknown button type."); UNREACHABLE();
        // }}}
    }

    u8 elevation = 0; // basically a shadow
    if (d_ele && (s_ena || s_pre)) elevation = 1;
    if (d_ele && (s_hov || s_foc)) elevation = 2;
    if (d_fil && s_hov && (t_uns || t_sel)) elevation = 1;
    if (d_ton && s_hov) elevation = 1;

    u8 state_layer = 0; // background shape, foreground color, with opacity=state_layer
    if (s_hov) state_layer = (u8)(255.0*0.1); // should be 0.08
    if (s_foc || s_pre) state_layer = (u8)(255.0*0.15); // should be 0.1
    if (s_dis) {
        if (TRY_SET(button.bg, COLOR.Scheme.OnSurface)) {
            button.bg.a = (u8)((f32)button.bg.a * 0.1);
        }
        if (TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant)) {
            button.fg.a = (u8)((f32)button.fg.a * 0.4);
        }
    }

    if (t_def || t_uns) {
        button.round.tl = md_mm2px_ctx(ctx, MD_ROUND_FULL);
        button.round.tr = md_mm2px_ctx(ctx, MD_ROUND_FULL);
        button.round.bl = md_mm2px_ctx(ctx, MD_ROUND_FULL);
        button.round.br = md_mm2px_ctx(ctx, MD_ROUND_FULL);
    }
    if (t_sel) {
        button.round.tl = md_mm2px_ctx(ctx, MD_ROUND_SMALL);
        button.round.tr = md_mm2px_ctx(ctx, MD_ROUND_SMALL);
        button.round.bl = md_mm2px_ctx(ctx, MD_ROUND_SMALL);
        button.round.br = md_mm2px_ctx(ctx, MD_ROUND_SMALL);
    }

    if (d_ele) {
        if (t_def) {
            TRY_SET(button.bg, COLOR.Scheme.SurfaceContainerLow);
            TRY_SET(button.fg, COLOR.Scheme.Primary);
        }
        if (t_uns) {
            TRY_SET(button.bg, COLOR.Scheme.SurfaceContainerLow);
            TRY_SET(button.fg, COLOR.Scheme.Primary);
        }
        if (t_sel) {
            TRY_SET(button.bg, COLOR.Scheme.Primary);
            TRY_SET(button.fg, COLOR.Scheme.OnPrimary);
        }
    }
    if (d_fil) {
        if (t_def) {
            TRY_SET(button.bg, COLOR.Scheme.Primary);
            TRY_SET(button.fg, COLOR.Scheme.OnPrimary);
        }
        if (t_uns) {
            TRY_SET(button.bg, COLOR.Scheme.SurfaceContainer);
            TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant);
        }
        if (t_sel) {
            TRY_SET(button.bg, COLOR.Scheme.Primary);
            TRY_SET(button.fg, COLOR.Scheme.OnPrimary);
        }
    }
    if (d_ton) {
        if (t_def) {
            TRY_SET(button.bg, COLOR.Scheme.SecondaryContainer);
            TRY_SET(button.fg, COLOR.Scheme.OnSecondaryContainer);
        }
        if (t_uns) {
            TRY_SET(button.bg, COLOR.Scheme.SecondaryContainer);
            TRY_SET(button.fg, COLOR.Scheme.OnSecondaryContainer);
        }
        if (t_sel) {
            TRY_SET(button.bg, COLOR.Scheme.Secondary);
            TRY_SET(button.fg, COLOR.Scheme.OnSecondary);
        }
    }
    if (d_out) {
        if (t_def) {
            TRY_SET(button.bg, COLOR.Scheme.OutlineVariant);
            TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant);
        }
        if (t_uns) {
            TRY_SET(button.bg, COLOR.Scheme.OutlineVariant);
            TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant);
        }
        if (t_sel) {
            TRY_SET(button.bg, COLOR.Scheme.InverseSurface);
            TRY_SET(button.fg, COLOR.Scheme.InverseOnSurface);
        }
    }
    if (d_txt) {
        if (t_def) {
            TRY_SET(button.fg, COLOR.Scheme.Primary);
        } else {
            MD_WARN("Button Text Design Does Not Support Toggle.");
        }
    }

    button.state_layer = state_layer;
    button.elevation = elevation;
    return button;

    #undef TRY_SET
    // }}}
}

bool md_render_button(md_button_t button) { return md_render_button_ctx(&CTX, button); }
bool md_render_button_ctx(md_ctx_t* ctx, md_button_t button) {
    UNUSED(ctx);
    UNUSED(button);

    md_command_t cmd = {0};
    cmd.type = MD_COMMAND_DRAW_BOX;
    cmd.as.box.box = button.box;
    cmd.as.box.color = button.bg;
    cmd.as.box.round = button.round;
    md_ctx_append_ctx(ctx, cmd);

    cmd = (md_command_t){0};
    cmd.type = MD_COMMAND_DRAW_TEXT;
    cmd.as.text.box = button.box;
    cmd.as.text.color = button.fg;
    cmd.as.text.text = button.text;
    cmd.as.text.font_size = ctx->font_size;

    vec2 text_sz = ctx->measure_text(button.text, ctx->font_size);
    cmd.as.text.box.x += (cmd.as.text.box.w-text_sz.x)/2;
    cmd.as.text.box.y += (cmd.as.text.box.h-text_sz.y)/2;

    md_ctx_append_ctx(ctx, cmd);

    return true;
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

#endif /* MD_UI_IMPLEMENTATION }}} */
