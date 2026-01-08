/*
Single header style library for Material Design
All measurements are in dp, unless stated otherwise.
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
    typedef Color MDColor;
#else
    typedef struct { u8 r, g, b, a; } MDColor;
#endif

#define COLOR_INVALID (MDColor){0xFF,0,0xFF,0xFF}
#define COLOR_UNSET(C) ((C).r == 0 && (C).g == 0 && (C).b == 0 && (C).a == 0)
#define COLOR_EQ(A,B) ((A).r == (B).r && (A).g == (B).g && (A).b == (B).b && (A).a == (B).a)

static struct {
    /* {{{ */
    MDColor Black, White, Transparent;
    MDColor Blue[101], Yellow[101], Red[101], Purple[101], Cyan[101], Grey[101], Green[101], Orange[101], Pink[101];
    MDColor Primary[101], Secondary[101], Tertiary[101], Neutral[101], Error[101];
    struct {
        MDColor Primary;
        MDColor OnPrimary;
        MDColor PrimaryContainer;
        MDColor OnPrimaryContainer;
        MDColor PrimaryFixed;
        MDColor OnPrimaryFixed;
        MDColor PrimaryFixedDim;
        MDColor OnPrimaryFixedVariant;
        MDColor InversePrimary;
        MDColor Secondary;
        MDColor OnSecondary;
        MDColor SecondaryContainer;
        MDColor OnSecondaryContainer;
        MDColor SecondaryFixed;
        MDColor OnSecondaryFixed;
        MDColor SecondaryFixedDim;
        MDColor OnSecondaryFixedVariant;
        MDColor Tertiary;
        MDColor OnTertiary;
        MDColor TertiaryContainer;
        MDColor OnTertiaryContainer;
        MDColor TertiaryFixed;
        MDColor OnTertiaryFixed;
        MDColor TertiaryFixedDim;
        MDColor OnTertiaryFixedVariant;
        MDColor Error;
        MDColor OnError;
        MDColor ErrorContainer;
        MDColor OnErrorContainer;
        MDColor Surface;
        MDColor OnSurface;
        MDColor SurfaceVariant;
        MDColor OnSurfaceVariant;
        MDColor SurfaceContainerHighest;
        MDColor SurfaceContainerHigh;
        MDColor SurfaceContainer;
        MDColor SurfaceContainerLow;
        MDColor SurfaceContainerLowest;
        MDColor InverseSurface;
        MDColor InverseOnSurface;
        MDColor SurfaceTint;
        MDColor Outline;
        MDColor OutlineVariant;
        MDColor SurfaceBright;
        MDColor SurfaceDim;
        MDColor Background;
        MDColor OnBackground;
    } Scheme, SchemeDark, SchemeLight; // [0] == Dark; [1] == Light
    /* }}} */
} COLOR = {0}; // Global Color Lookup

void md_color_global_init(bool interpolate);
void md_color_global_set_theme(u8 theme);
void md_color_global_switch_theme();

#if defined(RAYLIB_H)
    typedef Vector2 Vec2;
#else
    typedef struct { f32 x, y; } Vec2;
#endif

typedef struct { f32 x, y, w, h; } MDBox;
typedef struct { f32 tl, tr, bl, br; } MDCorners;

MD_ENUM(u8, MDAlign) { MD_ALIGN_START, MD_ALIGN_CENTER, MD_ALIGN_END, };
typedef struct { MDAlign x, y; } MDTextAlign;

MD_ENUM(u8, MDSize) { MD_SIZE_XS, MD_SIZE_S, MD_SIZE_M, MD_SIZE_L, MD_SIZE_XL, };

#define MD_COMMANDS_MAXIMUM_QUANTITY 1024
typedef u8 MDCommandType; enum {
    MD_COMMAND_DRAW_NONE,
    MD_COMMAND_DRAW_BOX,
    MD_COMMAND_DRAW_BOX_OUTLINE,
    MD_COMMAND_DRAW_TEXT,
};
typedef struct {
    MDCommandType type;
    union {
        struct {
            MDBox box;
            MDColor color;
            MDCorners round;
        } box;
        struct {
            MDBox box;
            MDColor color;
            MDCorners round;
            f32 thickness;
        } box_outline;
        struct {
            MDBox box; // width and height are for scissor mode, ignored if 0
            char* text;
            MDColor color;
            f32 font_size;
        } text;
    } as;
} MDCommand;

typedef Vec2 (*MDMeasureTextFn)(char* text, f32 font_size_px);

typedef struct {
    Vec2 monitor_size_mm; // physical size, in mm
    Vec2 monitor_size_px; // width and height, in pixels
    f32 scaling_factor;   // default 1.0, used for in-app scaling.
    f32 ppi;              // pixels per inch

    MDMeasureTextFn measure_text; // required

    MDCommand* cmd_list; // must be at least MD_COMMANDS_MAXIMUM_QUANTITY
    u32 cmd_list_len;
    u32 cmd_list_poll_index;
} MDContext;
static MDContext CTX = {0};

void md_ctx_init(Vec2 monitor_size_mm, Vec2 monitor_size_px, void* cmd_list_memory, MDMeasureTextFn fn);
void md_ctx_init_ctx(MDContext* ctx, Vec2 monitor_size_mm, Vec2 monitor_size_px, void* cmd_list_memory, MDMeasureTextFn fn);
bool md_ctx_append(MDCommand cmd);
bool md_ctx_append_ctx(MDContext* ctx, MDCommand cmd);
bool md_ctx_poll(MDCommand* cmd);
bool md_ctx_poll_ctx(MDContext* ctx, MDCommand* cmd);

f32 md_px2dp(f32 px);
f32 md_px2dp_ctx(MDContext* ctx, f32 px);
f32 md_dp2px(f32 dp);
f32 md_dp2px_ctx(MDContext* ctx, f32 dp);
f32 md_pt2dp(f32 pt);
f32 md_pt2dp_ctx(MDContext* ctx, f32 pt);

/* https://m3.material.io/components/buttons/overview */
MD_ENUM(u8, MDButtonState) {
    MD_BUTTON_STATE_ENABLED,
    MD_BUTTON_STATE_DISABLED,
    MD_BUTTON_STATE_HOVERED,
    MD_BUTTON_STATE_FOCUSED,
    MD_BUTTON_STATE_PRESSED,
};
MD_ENUM(u8, MDButtonType) {
    MD_BUTTON_TYPE_DEFAULT,    // normal
    MD_BUTTON_TYPE_UNSELECTED, // toggle - off
    MD_BUTTON_TYPE_SELECTED,   // toggle - on
};
MD_ENUM(u8, MDButtonDesign) {
    MD_BUTTON_DESIGN_ELEVATED,
    MD_BUTTON_DESIGN_FILLED,
    MD_BUTTON_DESIGN_TONAL,
    MD_BUTTON_DESIGN_OUTLINED,
    MD_BUTTON_DESIGN_TEXT,
};
typedef void(*MDCallbackButton)(void);
typedef struct {
    MDBox box;       // X,Y - required; W,H - optional;
    MDSize size;     // required
    MDCorners round; // inferred
    MDColor bg;      // inferred
    u8 state_layer;  // inferred
    u8 elevation;    // inferred

    char* text;             // required
    f32 font_size;          // inferred
    Vec2 text_size;         // inferred
    MDTextAlign text_align; // inferred
    MDColor fg;             // inferred

    MDButtonType type;     // required
    MDButtonState state;   // required
    MDButtonDesign design; // required

    MDCallbackButton cb; // optional
} MDButton;

// When some info is omitted, the functions will fill it in and return the object back.
MDButton md_button(MDButton button);
MDButton md_button_ctx(MDContext* ctx, MDButton button);

// These will "render" the objects into Context by appending commands.
bool md_render_button(MDButton button);
bool md_render_button_ctx(MDContext* ctx, MDButton button);

#endif /* MD_UI }}} */



#ifdef MD_UI_IMPLEMENTATION /* {{{ */

Vec2 empty_measure_text_fn(char* text, f32 font_size_px) { UNUSED(text); UNUSED(font_size_px); return (Vec2){0}; }

void md_ctx_init(Vec2 monitor_size_mm, Vec2 monitor_size_px, void* cmd_list_memory, MDMeasureTextFn fn) {
    md_ctx_init_ctx(&CTX, monitor_size_mm, monitor_size_px, cmd_list_memory, fn);
}
void md_ctx_init_ctx(MDContext* ctx, Vec2 monitor_size_mm, Vec2 monitor_size_px, void* cmd_list_memory, MDMeasureTextFn fn) {
    // {{{
    ctx->monitor_size_mm = monitor_size_mm;
    ctx->monitor_size_px = monitor_size_px;
    ctx->scaling_factor  = 1;
    ctx->ppi = monitor_size_px.x / (monitor_size_mm.x/25.4f);
    ctx->measure_text = fn == NULL ? empty_measure_text_fn : fn;
    ctx->cmd_list = (MDCommand*)cmd_list_memory;
    // }}}
}

bool md_ctx_append(MDCommand cmd) { return md_ctx_append_ctx(&CTX, cmd); }
bool md_ctx_append_ctx(MDContext* ctx, MDCommand cmd) {
    // {{{
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
    // }}}
}

bool md_ctx_poll(MDCommand* cmd) { return md_ctx_poll_ctx(&CTX, cmd); }
bool md_ctx_poll_ctx(MDContext* ctx, MDCommand* cmd) {
    // {{{
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
    // }}}
}

MDButton md_button(MDButton button) { return md_button_ctx(&CTX, button); }
MDButton md_button_ctx(MDContext* ctx, MDButton button) {
    // {{{
    #define TRY_SET(var, col) (COLOR_UNSET(var) ? ((var) = (col), true) : (false))

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
        case MD_BUTTON_TYPE_DEFAULT:    t_def=1; break;
        case MD_BUTTON_TYPE_UNSELECTED: t_uns=1; break;
        case MD_BUTTON_TYPE_SELECTED:   t_sel=1; break;
        default: MD_ERROR("Unknown button type."); UNREACHABLE();
        // }}}
    }

    bool sz_xs=0, sz_s=0, sz_m=0, sz_l=0, sz_xl=0;
    switch (button.size) {
        // {{{
        case MD_SIZE_XS: sz_xs=1; break;
        case MD_SIZE_S:  sz_s=1;  break;
        case MD_SIZE_M:  sz_m=1;  break;
        case MD_SIZE_L:  sz_l=1;  break;
        case MD_SIZE_XL: sz_xl=1; break;
        default: MD_ERROR("Unknown button size."); UNREACHABLE();
        // }}}
    }

    u8 elevation = 0; // basically a shadow
    if (d_ele && (s_ena || s_pre)) elevation = 1;
    if (d_ele && (s_hov || s_foc)) elevation = 2;
    if (d_fil && s_hov && (t_uns || t_sel)) elevation = 1;
    if (d_ton && s_hov) elevation = 1;
    button.elevation = elevation;

    u8 state_layer = 0; // background shape, foreground color, with opacity=state_layer
    if (s_hov) state_layer = (u8)(255.0*0.1); // should be 0.08
    if (s_foc || s_pre) state_layer = (u8)(255.0*0.15); // should be 0.1
    button.state_layer = state_layer;

    f32 corner_size = 1e6;
    if (t_sel) {
        if (sz_xs || sz_s) corner_size = 12;
        if (sz_m)          corner_size = 16;
        if (sz_l || sz_xl) corner_size = 28;
        corner_size = md_dp2px_ctx(ctx, corner_size);
    }
    if (s_pre) {
        if (sz_xs || sz_s) corner_size = 8;
        if (sz_m)          corner_size = 12;
        if (sz_l || sz_xl) corner_size = 16;
        corner_size = md_dp2px_ctx(ctx, corner_size);
    }
    button.round.tl = corner_size;
    button.round.tr = corner_size;
    button.round.bl = corner_size;
    button.round.br = corner_size;

    f32 font_size = 0; // dp
    if (sz_xs) font_size = 14;
    if (sz_s ) font_size = 14;
    if (sz_m ) font_size = 16;
    if (sz_l ) font_size = 24;
    if (sz_xl) font_size = 32;
    button.font_size = md_dp2px_ctx(ctx, md_pt2dp_ctx(ctx, font_size));

    if (sz_xs) button.box.h =  32;
    if (sz_s ) button.box.h =  40;
    if (sz_m ) button.box.h =  56;
    if (sz_l ) button.box.h =  96;
    if (sz_xl) button.box.h = 136;
    button.box.h = md_dp2px_ctx(ctx, button.box.h);

    f32 padding = 0; // dp
    if (sz_xs) padding = 12;
    if (sz_s ) padding = 16;
    if (sz_m ) padding = 24;
    if (sz_l ) padding = 48;
    if (sz_xl) padding = 64;
    padding = md_dp2px_ctx(ctx, padding);

    button.text_size = ctx->measure_text(button.text, button.font_size);
    button.box.w = MAX(button.box.w, padding*2 + button.text_size.x);

    if (s_dis) {
        if (TRY_SET(button.bg, COLOR.Scheme.OnSurface)) {
            button.bg.a = (u8)((f32)button.bg.a * 0.1);
        }
        if (TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant)) {
            button.fg.a = (u8)((f32)button.fg.a * 0.4);
        }
    }
    if (d_ele) {
        if (t_def) TRY_SET(button.bg, COLOR.Scheme.SurfaceContainerLow);
        if (t_def) TRY_SET(button.fg, COLOR.Scheme.Primary);
        if (t_uns) TRY_SET(button.bg, COLOR.Scheme.SurfaceContainerLow);
        if (t_uns) TRY_SET(button.fg, COLOR.Scheme.Primary);
        if (t_sel) TRY_SET(button.bg, COLOR.Scheme.Primary);
        if (t_sel) TRY_SET(button.fg, COLOR.Scheme.OnPrimary);
    }
    if (d_fil) {
        if (t_def) TRY_SET(button.bg, COLOR.Scheme.Primary);
        if (t_def) TRY_SET(button.fg, COLOR.Scheme.OnPrimary);
        if (t_uns) TRY_SET(button.bg, COLOR.Scheme.SurfaceContainer);
        if (t_uns) TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant);
        if (t_sel) TRY_SET(button.bg, COLOR.Scheme.Primary);
        if (t_sel) TRY_SET(button.fg, COLOR.Scheme.OnPrimary);
    }
    if (d_ton) {
        if (t_def) TRY_SET(button.bg, COLOR.Scheme.SecondaryContainer);
        if (t_def) TRY_SET(button.fg, COLOR.Scheme.OnSecondaryContainer);
        if (t_uns) TRY_SET(button.bg, COLOR.Scheme.SecondaryContainer);
        if (t_uns) TRY_SET(button.fg, COLOR.Scheme.OnSecondaryContainer);
        if (t_sel) TRY_SET(button.bg, COLOR.Scheme.Secondary);
        if (t_sel) TRY_SET(button.fg, COLOR.Scheme.OnSecondary);
    }
    if (d_out) {
        if (t_def) TRY_SET(button.bg, COLOR.Scheme.OutlineVariant);
        if (t_def) TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant);
        if (t_uns) TRY_SET(button.bg, COLOR.Scheme.OutlineVariant);
        if (t_uns) TRY_SET(button.fg, COLOR.Scheme.OnSurfaceVariant);
        if (t_sel) TRY_SET(button.bg, COLOR.Scheme.InverseSurface);
        if (t_sel) TRY_SET(button.fg, COLOR.Scheme.InverseOnSurface);
    }
    if (d_txt) {
        if (t_def) TRY_SET(button.fg, COLOR.Scheme.Primary);
        if (!t_def) MD_WARN("Button Text Design Does Not Support Toggle.");
    }

    return button;
    #undef TRY_SET
    // }}}
}

bool md_render_button(MDButton button) { return md_render_button_ctx(&CTX, button); }
bool md_render_button_ctx(MDContext* ctx, MDButton button) {
    // {{{
    #define APPEND(CMD) md_ctx_append_ctx(ctx, (CMD)); (CMD)=(MDCommand){0}
    MDCommand cmd = {0};

    // elevation
    for (u8 i = 0; i < button.elevation; i++) {
        f32 thickness = 1;
        if (button.size == MD_SIZE_L) thickness = 2;
        if (button.size == MD_SIZE_XL) thickness = 3;
        thickness = md_dp2px_ctx(ctx, thickness);
        cmd.type = MD_COMMAND_DRAW_BOX;
        cmd.as.box.box = button.box;
        if (i == 0) cmd.as.box.box.y -= thickness*0.5;
        cmd.as.box.box.x -= thickness*(0.5 + (f32)i*0.25);
        cmd.as.box.box.w += thickness*(1 + (f32)i*0.5);
        cmd.as.box.box.h += thickness*(1.5 + (f32)i*0.5);
        cmd.as.box.color = COLOR.Black;
        cmd.as.box.color.a = 51 * MIN(5, button.elevation);
        cmd.as.box.round = button.round;
        APPEND(cmd);
    }

    // background
    if (button.type == MD_BUTTON_TYPE_SELECTED || button.state == MD_BUTTON_STATE_DISABLED || button.design != MD_BUTTON_DESIGN_OUTLINED) {
        cmd.type = MD_COMMAND_DRAW_BOX;
        cmd.as.box.box = button.box;
        cmd.as.box.color = button.bg;
        cmd.as.box.round = button.round;
        APPEND(cmd);
    }

    // state layer
    if (button.state_layer > 0) {
        cmd.type = MD_COMMAND_DRAW_BOX;
        cmd.as.box.box = button.box;
        cmd.as.box.color = button.fg;
        cmd.as.box.color.a = button.state_layer;
        cmd.as.box.round = button.round;
        APPEND(cmd);
    }

    // outline
    if (button.design == MD_BUTTON_DESIGN_OUTLINED && button.type != MD_BUTTON_TYPE_SELECTED) {
        f32 thickness = 1;
        if (button.size == MD_SIZE_L) thickness = 2;
        if (button.size == MD_SIZE_XL) thickness = 3;
        thickness = md_dp2px_ctx(ctx, thickness);
        cmd.type = MD_COMMAND_DRAW_BOX_OUTLINE;
        cmd.as.box_outline.box = button.box;
        cmd.as.box_outline.color = button.bg;
        cmd.as.box_outline.round = button.round;
        cmd.as.box_outline.thickness = md_dp2px_ctx(ctx, thickness);
        APPEND(cmd);
    }

    // focus
    if (button.state == MD_BUTTON_STATE_FOCUSED) {
        f32 offset = 0;
        if (button.design == MD_BUTTON_DESIGN_ELEVATED) offset = 1;
        if (button.design == MD_BUTTON_DESIGN_OUTLINED) offset = 1;
        f32 thickness = 1;
        if (button.size == MD_SIZE_L) thickness = 2;
        if (button.size == MD_SIZE_XL) thickness = 3;
        thickness = md_dp2px_ctx(ctx, thickness);
        thickness *= 2 + offset;
        cmd.type = MD_COMMAND_DRAW_BOX_OUTLINE;
        cmd.as.box_outline.box = button.box;
        cmd.as.box_outline.box.x -= thickness;
        cmd.as.box_outline.box.y -= thickness;
        cmd.as.box_outline.box.w += thickness*2;
        cmd.as.box_outline.box.h += thickness*2;
        cmd.as.box_outline.color = COLOR.Scheme.Outline; // probably
        cmd.as.box_outline.round = button.round;
        cmd.as.box_outline.round.tl += thickness;
        cmd.as.box_outline.round.tr += thickness;
        cmd.as.box_outline.round.bl += thickness;
        cmd.as.box_outline.round.br += thickness;
        cmd.as.box_outline.thickness = md_dp2px_ctx(ctx, thickness/(2+offset)*2);
        APPEND(cmd);
    }

    cmd.type = MD_COMMAND_DRAW_TEXT;
    cmd.as.text.box = button.box;
    cmd.as.text.color = button.fg;
    cmd.as.text.text = button.text;
    cmd.as.text.font_size = button.font_size;
    cmd.as.text.box.x += (cmd.as.text.box.w - button.text_size.x) / 2;
    cmd.as.text.box.y += (cmd.as.text.box.h - button.text_size.y) / 2;
    APPEND(cmd);

    return true;
    #undef APPEND
    // }}}
}

// DP = PX * 160 / DPI
f32 md_px2dp(f32 px) { return md_px2dp_ctx(&CTX, px); }
f32 md_px2dp_ctx(MDContext* ctx, f32 px) {
    return (f32)px / (ctx->scaling_factor * ctx->ppi/160.0f);
}

// PX = DP * DPI / 160
f32 md_dp2px(f32 dp) { return md_dp2px_ctx(&CTX, dp); }
f32 md_dp2px_ctx(MDContext* ctx, f32 dp) {
    return (f32)(0.5 + dp * (ctx->scaling_factor * ctx->ppi/160.0f)); // +0.5 to round
}

// DP = PT * 160 / 72
f32 md_pt2dp(f32 pt) { return md_pt2dp_ctx(&CTX, pt); }
f32 md_pt2dp_ctx(MDContext* ctx, f32 pt) {
    UNUSED(ctx);
    return pt * 160.0f/72.0f * 0.66f;
}

/* Color Initialization Macro Magic {{{ */
void _fill_in_gaps(MDColor* colors) {
    for (u8 i = 1; i < 100; i++) {
        if (colors[i].a != 0) continue;
        MDColor prev = {0}, next = {0};
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
    COLOR.Black = (MDColor){0,0,0,255};
    COLOR.White = (MDColor){255,255,255,255};
    // black transparent == unset
    // white transparent != unset
    COLOR.Transparent = (MDColor){255,255,255,0};

    static MDColor colors[101];
    memset(colors, 0, sizeof(MDColor)*101);
    colors[0] = (MDColor){0,0,0,0xFF};
    colors[100] = (MDColor){0xFF,0xFF,0xFF,0xFF};

    // Baseline
    #define Y(NAME, Name) \
        COMBINE(MATERIAL_PALETTE_BASELINE_, NAME); \
        if (interpolate) _fill_in_gaps(colors); \
        for (u8 i = 0; i < 101; i++) ACCESS(Name)[i] = colors[i]; \
        memset(&colors[1], 0, sizeof(MDColor)*99);

    #define COMBINE(A,B) A##B
    #define ACCESS(Name) COLOR.Name
    #define X(NAME, P, R,G,B) colors[P] = (MDColor){R,G,B,0xFF};
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
        memset(&colors[1], 0, sizeof(MDColor)*99);

    #define COMBINE(A,B) A##B
    #define ACCESS(Name) COLOR.Name
    #define X(NAME, P, R,G,B) colors[P] = (MDColor){R,G,B,0xFF};
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
