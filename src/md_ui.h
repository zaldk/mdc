/*
Single header stb-style library for Material Design
All measurements are in dp, unless stated otherwise.
*/

#ifndef MD_UI /* {{{ */
#define MD_UI

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "colors_material_palettes.h"
#include "colors_material_schemes.h"

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

#define MD_MAX_COMMANDS 1024
#define MD_MAX_NODES 1024
#define MD_NIL_NODE (-1)
#define MD_MAX_DEPTH 1024

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

MD_ENUM(u8, MDAlign) { MD_ALIGN_START=0, MD_ALIGN_CENTER=1, MD_ALIGN_END=2 };
typedef struct { MDAlign x, y; } MDTextAlign;

MD_ENUM(u8, MDSize) { MD_SIZE_XS=1, MD_SIZE_S=2, MD_SIZE_M=0, MD_SIZE_L=3, MD_SIZE_XL=4 };
MD_ENUM(u8, MDIconAlign) { MD_ICON_ALIGN_INLINED=0, MD_ICON_ALIGN_STACKED=1 };

// {{{ MDCommand
typedef u8 MDCommandType; enum {
    MD_COMMAND_DRAW_NONE    = 0,
    MD_COMMAND_DRAW_BOX     = 1,
    MD_COMMAND_DRAW_OUTLINE = 2,
    MD_COMMAND_DRAW_TEXT    = 3,
    MD_COMMAND_DRAW_ICON    = 4,
    MD_COMMAND_DRAW_LAYOUT  = 5,
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
        } outline;
        struct {
            MDBox box; // width and height are for scissor mode, ignored if 0
            MDColor color;
            char* text;
            f32 font_size;
        } text;
        struct {
            MDBox box; // width and height are for scissor mode, ignored if 0
            MDColor color;
            i32 codepoint;
            f32 icon_size;
        } icon;
        struct {
            MDBox box; // bounding box of the screen
            const char* id; // ID of the tab
        } layout; // only used for calling user fn responsible for the tab render
    } as;
} MDCommand;
// }}}

MD_ENUM(u8, MDInputButton) {
    MD_INPUT_LMB = 0,
    MD_INPUT_RMB = 1,
};

typedef Vec2 (*MDGetWindowSizeFn)(void);
typedef Vec2 (*MDMeasureTextFn)(char* text, f32 font_size_px);
typedef Vec2 (*MDGetMousePositionFn)(void);
typedef bool (*MDCButtonDownFn)(MDInputButton button);

typedef struct MDContext MDContext; // see below

void md_ctx_init(Vec2 monitor_size_mm, Vec2 monitor_size_px);
void md_ctx_init_ctx(MDContext* ctx, Vec2 monitor_size_mm, Vec2 monitor_size_px);
void md_ctx_set_scaling(f32 scaling);
void md_ctx_set_scaling_ctx(MDContext* ctx, f32 scaling);

void md_ctx_set_get_window_size(MDGetWindowSizeFn fn);
void md_ctx_set_get_window_size_ctx(MDContext* ctx, MDGetWindowSizeFn fn);
void md_ctx_set_measure_text(MDMeasureTextFn fn);
void md_ctx_set_measure_text_ctx(MDContext* ctx, MDMeasureTextFn fn);
void md_ctx_set_mouse_pos(MDGetMousePositionFn fn);
void md_ctx_set_mouse_pos_ctx(MDContext* ctx, MDGetMousePositionFn fn);
void md_ctx_set_button_down(MDCButtonDownFn fn);
void md_ctx_set_button_down_ctx(MDContext* ctx, MDCButtonDownFn fn);

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

// basically just a box
// {{{ MDCDiv
typedef struct {
    MDBox box;
} MDCDiv;
// }}}

MDCDiv mdc_div(MDCDiv div);
MDCDiv mdc_div_ctx(MDContext* ctx, MDCDiv div);
bool mdc_render_div(MDCDiv div);
bool mdc_render_div_ctx(MDContext* ctx, MDCDiv div);
// #define MD_DIV(...) mdc_div((MDCDiv){__VA_ARGS__})
// #define MD_DIV_CTX(ctx, ...) mdc_div_ctx((ctx), (MDCDiv){__VA_ARGS__})

/* https://m3.material.io/components/buttons/overview */
// {{{ MDCButton
MD_ENUM(u8, MDCButtonState) {
    MD_BUTTON_STATE_ENABLED  = 0,
    MD_BUTTON_STATE_DISABLED = 1,
    MD_BUTTON_STATE_HOVERED  = 2,
    MD_BUTTON_STATE_FOCUSED  = 3,
    MD_BUTTON_STATE_PRESSED  = 4,
};
MD_ENUM(u8, MDCButtonType) {
    MD_BUTTON_TYPE_DEFAULT = 0,
    MD_BUTTON_TYPE_TOGGLE  = 1,
};
MD_ENUM(u8, MDCButtonDesign) {
    MD_BUTTON_DESIGN_ELEVATED = 0,
    MD_BUTTON_DESIGN_FILLED   = 1,
    MD_BUTTON_DESIGN_TONAL    = 2,
    MD_BUTTON_DESIGN_OUTLINED = 3,
    MD_BUTTON_DESIGN_TEXT     = 4,
};
typedef void(*MDCallbackButton)(void);
typedef struct {
    MDBox box;              // X,Y - required; W,H - inferred;
    MDSize size;            // required
    char* text;             // required
    MDCButtonType type;     // required
    MDCButtonState state;   // required
    MDCButtonDesign design; // required
    bool selected;          // required - only for toggle type

    i32 icon_code;          // optional // TODO
    MDIconAlign icon_align; // optional // TODO
    MDCallbackButton cb;    // optional

    MDColor bg;      // inferred
    MDColor fg;      // inferred
    MDCorners round; // inferred
    f32 font_size;   // inferred
    Vec2 text_size;  // inferred
    u8 state_layer;  // inferred
    u8 elevation;    // inferred
} MDCButton;
// }}}

MDCButton mdc_button(MDCButton button);
MDCButton mdc_button_ctx(MDContext* ctx, MDCButton button);
bool mdc_render_button(MDCButton button);
bool mdc_render_button_ctx(MDContext* ctx, MDCButton button);
// #define MD_BUTTON(...) mdc_button((MDCButton){__VA_ARGS__})
// #define MD_BUTTON_CTX(ctx, ...) mdc_button_ctx((ctx), (MDCButton){__VA_ARGS__})

// {{{ MDCTab
MD_ENUM(u8, MDCTabType) {
    MDC_TAB_TYPE_PRIMARY   = 0,
    MDC_TAB_TYPE_SECONDARY = 1,
};
MD_ENUM(u8, MDCTabState) {
    MDC_TAB_STATE_ENABLED = 0,
    MDC_TAB_STATE_HOVERED = 1,
    MDC_TAB_STATE_FOCUSED = 2,
    MDC_TAB_STATE_PRESSED = 3,
};
typedef void(*MDCallbackTab)(void);
typedef struct {
    MDBox box;         // X,Y - required; W,H - inferred;
    char* text;        // required
    MDCTabType type;   // required
    MDCTabState state; // required
    bool active;       // required

    i32 icon_code;          // optional
    MDIconAlign icon_align; // optional
    MDCallbackTab cb;       // optional

    MDColor bg;     // inferred from type/state
    MDColor fg;     // inferred from type/state
    u8 state_layer; // inferred from state
    f32 font_size;  // inferred
    f32 icon_size;  // inferred
    Vec2 text_size; // inferred from text
} MDCTab;
// }}}

MDCTab mdc_tab(MDCTab tab);
MDCTab mdc_tab_ctx(MDContext* ctx, MDCTab tab);
bool mdc_render_tab(MDCTab tab);
bool mdc_render_tab_ctx(MDContext* ctx, MDCTab tab);
// #define MD_TAB(...) mdc_tab((MDCTab){__VA_ARGS__})
// #define MD_TAB_CTX(ctx, ...) mdc_tab_ctx((ctx), (MDCTab){__VA_ARGS__})

// {{{ MDComponent
MD_ENUM(u8, MDComponentType) {
    MDC_DIV    = 0,
    MDC_BUTTON = 1,
    MDC_TAB    = 2,
};
typedef struct MDComponent {
    MDComponentType type;
    union {
        MDCDiv div;
        MDCButton button;
        MDCTab tab;
    } as;
} MDComponent;
// }}}

MDComponent mdc_component(MDComponent component);
MDComponent mdc_component_ctx(MDContext* ctx, MDComponent component);
bool mdc_render_component(MDComponent component);
bool mdc_render_component_ctx(MDContext* ctx, MDComponent component);
// #define MD_COMPONENT(...) mdc_component((MDComponent){__VA_ARGS__})
// #define MD_COMPONENT_CTX(ctx, ...) mdc_component_ctx((ctx), (MDComponent){__VA_ARGS__})

// {{{ MDElement
MD_ENUM(u8, MDElementType) {
    MDL_TYPE_TAB,    // 0  children (leaf node)
    MDL_TYPE_STACK,  // 2  children
    MDL_TYPE_INLINE, // 2  children
    MDL_TYPE_TABS,   // 1+ children
};
typedef struct {
    MDElementType type;
    // non-leaf-only
    f32* split; // STACK/INLINE percentage [0 < split < 1]
    i32* tab;   // TABS active tab index, 0-based
    // leaf-only
    const char* id;
} MDElement;
typedef struct {
    MDElement element;
    i32 parent, self;
    i32 child_first, child_last;
    i32 sibling_next, sibling_prev;
} MDLayoutNode;
// }}}

i32 mdl_element_add(MDElement elem, i32 parent_index);
i32 mdl_element_add_ctx(MDContext* ctx, MDElement elem, i32 parent_index);
bool mdl_render_layout(void);
bool mdl_render_layout_ctx(MDContext* ctx);

// trick from clay.h (https://github.com/nicbarker/clay)
static u8 _MDL_ELEMENT_LATCH;
#define _MDL_GENERIC(type, split, tab, id) \
    if (CTX.ps_len < 0) { MD_ERROR("Parent stack length cannot be negative"); UNREACHABLE(); } \
    if (CTX.ps_len >= MD_MAX_DEPTH-1) { MD_ERROR("Reached layout depth limit (MD_MAX_DEPTH)"); UNREACHABLE(); } \
    for ( \
        _MDL_ELEMENT_LATCH = (CTX.ps[CTX.ps_len+1] = mdl_element_add((MDElement){type,split,tab,id}, CTX.ps[CTX.ps_len]), CTX.ps_len+=1, 0); \
        _MDL_ELEMENT_LATCH < 1; \
        _MDL_ELEMENT_LATCH = 1, CTX.ps_len = MAX(0,CTX.ps_len-1) \
    )
#define MDL_TAB(id)       _MDL_GENERIC(   MDL_TYPE_TAB,  NULL, NULL,   id)
#define MDL_TABS(tab)     _MDL_GENERIC(  MDL_TYPE_TABS,  NULL,  tab, NULL)
#define MDL_STACK(split)  _MDL_GENERIC( MDL_TYPE_STACK, split, NULL, NULL)
#define MDL_INLINE(split) _MDL_GENERIC(MDL_TYPE_INLINE, split, NULL, NULL)

// {{{ MDContext
struct MDContext {
    Vec2 monitor_size_mm; // physical size, in mm
    Vec2 monitor_size_px; // width and height, in pixels
    f32 ppi;              // pixels per inch
    f32 scaling;          // default 1.0, used for in-app scaling.

    MDGetWindowSizeFn get_window_size;
    MDMeasureTextFn measure_text;
    MDGetMousePositionFn get_mouse;
    MDCButtonDownFn button_down;

    // Drawing Commands Buffer
    MDCommand cmds[MD_MAX_COMMANDS];
    i32 cmds_len;
    i32 cmds_poll_index; // internal use only

    // Layout Components Buffer
    MDLayoutNode nodes[MD_MAX_NODES];
    i32 nodes_len;

    i32 ps[MD_MAX_DEPTH]; // layout parent stack, internal use only
    i32 ps_len;
};
static MDContext CTX = {0};
// }}}

#endif /* MD_UI }}} */



#ifdef MD_UI_IMPLEMENTATION /* {{{ */

void md_ctx_init(Vec2 monitor_size_mm, Vec2 monitor_size_px) { md_ctx_init_ctx(&CTX, monitor_size_mm, monitor_size_px); }
void md_ctx_init_ctx(MDContext* ctx, Vec2 monitor_size_mm, Vec2 monitor_size_px) {
    // {{{
    ctx->monitor_size_mm = monitor_size_mm;
    ctx->monitor_size_px = monitor_size_px;
    ctx->ppi = monitor_size_px.x / (monitor_size_mm.x/25.4f);
    ctx->scaling = 1;
    ctx->cmds_len = 0;
    ctx->nodes_len = 0;
    ctx->ps_len = 0;

    for (i32 i = 0; i < MD_MAX_DEPTH; i++) {
        ctx->ps[i] = MD_NIL_NODE;
    }

    UNUSED(_MDL_ELEMENT_LATCH); // HACK: suppress warning
    // }}}
}

void md_ctx_set_scaling(f32 scaling) { md_ctx_set_scaling_ctx(&CTX, scaling); }
void md_ctx_set_scaling_ctx(MDContext* ctx, f32 scaling) { ctx->scaling = scaling; }

void md_ctx_set_get_window_size(MDGetWindowSizeFn fn) { md_ctx_set_get_window_size_ctx(&CTX, fn); }
void md_ctx_set_get_window_size_ctx(MDContext* ctx, MDGetWindowSizeFn fn) { ctx->get_window_size = fn; }

void md_ctx_set_measure_text(MDMeasureTextFn fn) { md_ctx_set_measure_text_ctx(&CTX, fn); }
void md_ctx_set_measure_text_ctx(MDContext* ctx, MDMeasureTextFn fn) { ctx->measure_text = fn; }

void md_ctx_set_mouse_pos(MDGetMousePositionFn fn) { md_ctx_set_mouse_pos_ctx(&CTX, fn); }
void md_ctx_set_mouse_pos_ctx(MDContext* ctx, MDGetMousePositionFn fn) { ctx->get_mouse = fn; }

void md_ctx_set_button_down(MDCButtonDownFn fn) { md_ctx_set_button_down_ctx(&CTX, fn); }
void md_ctx_set_button_down_ctx(MDContext* ctx, MDCButtonDownFn fn) { ctx->button_down = fn; }

bool md_ctx_append(MDCommand cmd) { return md_ctx_append_ctx(&CTX, cmd); }
bool md_ctx_append_ctx(MDContext* ctx, MDCommand cmd) {
    // {{{
    if (ctx->cmds_len >= MD_MAX_COMMANDS) {
        MD_ERROR("Context memory (commands) was not big enough.");
        UNREACHABLE();
        return false;
    }
    ctx->cmds[ctx->cmds_len++] = cmd;
    return true;
    // }}}
}

bool md_ctx_poll(MDCommand* cmd) { return md_ctx_poll_ctx(&CTX, cmd); }
bool md_ctx_poll_ctx(MDContext* ctx, MDCommand* cmd) {
    // {{{
    if (ctx->cmds_len == 0) {
        return false;
    }
    if (ctx->cmds_poll_index >= ctx->cmds_len) {
        ctx->cmds_len = 0;
        ctx->cmds_poll_index = 0;
        return false;
    }
    *cmd = ctx->cmds[ctx->cmds_poll_index++];
    return true;
    // }}}
}

MDCDiv mdc_div(MDCDiv div) { return mdc_div_ctx(&CTX, div); }
MDCDiv mdc_div_ctx(MDContext* ctx, MDCDiv div) {
    // {{{
    // NOOP - div is just a box
    UNUSED(ctx);
    return div;
    // }}}
}

bool mdc_render_div(MDCDiv div) { return mdc_render_div_ctx(&CTX, div); }
bool mdc_render_div_ctx(MDContext* ctx, MDCDiv div) {
    // {{{
    // TODO: render edges?
    UNUSED(ctx);
    UNUSED(div);
    return true;
    // }}}
}

MDCButton mdc_button(MDCButton button) { return mdc_button_ctx(&CTX, button); }
MDCButton mdc_button_ctx(MDContext* ctx, MDCButton button) {
    // {{{
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

    bool t_def=0, t_tog=0;
    switch (button.type) {
        // {{{
        case MD_BUTTON_TYPE_DEFAULT: t_def=1; break;
        case MD_BUTTON_TYPE_TOGGLE:  t_tog=1; break;
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
    if (d_fil && s_hov && t_tog) elevation = 1;
    if (d_ton && s_hov) elevation = 1;
    button.elevation = elevation;

    u8 state_layer = 0; // background shape, foreground color, with opacity=state_layer
    if (!s_dis && s_hov) state_layer = (u8)(255.0*0.1); // should be 0.08
    if (!s_dis && (s_foc || s_pre)) state_layer = (u8)(255.0*0.15); // should be 0.1
    button.state_layer = state_layer;

    f32 corner_size = 1e6;
    if (t_tog && button.selected) {
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

    f32 padding = 0; // dp
    if (sz_xs) padding = 12;
    if (sz_s ) padding = 16;
    if (sz_m ) padding = 24;
    if (sz_l ) padding = 48;
    if (sz_xl) padding = 64;
    padding = md_dp2px_ctx(ctx, padding);

    button.text_size = ctx->measure_text(button.text, button.font_size);
    button.box.w = MAX(button.box.w, padding*2 + button.text_size.x);

    if (sz_xs) button.box.h =  32;
    if (sz_s ) button.box.h =  40;
    if (sz_m ) button.box.h =  56;
    if (sz_l ) button.box.h =  96;
    if (sz_xl) button.box.h = 136;
    button.box.h = md_dp2px_ctx(ctx, button.box.h);

    if (s_dis) {
        button.bg = COLOR.Scheme.OnSurface;
        button.bg.a = (u8)((f32)button.bg.a * 0.1);
        button.fg = COLOR.Scheme.OnSurfaceVariant;
        button.fg.a = (u8)((f32)button.fg.a * 0.4);
    }
    if (d_ele) {
        if (t_def) button.bg = COLOR.Scheme.SurfaceContainerLow;
        if (t_def) button.fg = COLOR.Scheme.Primary;
        if (t_tog && !button.selected) button.bg = COLOR.Scheme.SurfaceContainerLow;
        if (t_tog && !button.selected) button.fg = COLOR.Scheme.Primary;
        if (t_tog &&  button.selected) button.bg = COLOR.Scheme.Primary;
        if (t_tog &&  button.selected) button.fg = COLOR.Scheme.OnPrimary;
    }
    if (d_fil) {
        if (t_def) button.bg = COLOR.Scheme.Primary;
        if (t_def) button.fg = COLOR.Scheme.OnPrimary;
        if (t_tog && !button.selected) button.bg = COLOR.Scheme.SurfaceContainer;
        if (t_tog && !button.selected) button.fg = COLOR.Scheme.OnSurfaceVariant;
        if (t_tog &&  button.selected) button.bg = COLOR.Scheme.Primary;
        if (t_tog &&  button.selected) button.fg = COLOR.Scheme.OnPrimary;
    }
    if (d_ton) {
        if (t_def) button.bg = COLOR.Scheme.SecondaryContainer;
        if (t_def) button.fg = COLOR.Scheme.OnSecondaryContainer;
        if (t_tog && !button.selected) button.bg = COLOR.Scheme.SecondaryContainer;
        if (t_tog && !button.selected) button.fg = COLOR.Scheme.OnSecondaryContainer;
        if (t_tog &&  button.selected) button.bg = COLOR.Scheme.Secondary;
        if (t_tog &&  button.selected) button.fg = COLOR.Scheme.OnSecondary;
    }
    if (d_out) {
        if (t_def) button.bg = COLOR.Scheme.OutlineVariant;
        if (t_def) button.fg = COLOR.Scheme.OnSurfaceVariant;
        if (t_tog && !button.selected) button.bg = COLOR.Scheme.OutlineVariant;
        if (t_tog && !button.selected) button.fg = COLOR.Scheme.OnSurfaceVariant;
        if (t_tog &&  button.selected) button.bg = COLOR.Scheme.InverseSurface;
        if (t_tog &&  button.selected) button.fg = COLOR.Scheme.InverseOnSurface;
    }
    if (d_txt) {
        if (t_def) button.fg = COLOR.Scheme.Primary;
        if (!t_def) MD_WARN("Button Text Design Does Not Support Toggle.");
    }

    return button;
    // }}}
}

bool mdc_render_button(MDCButton button) { return mdc_render_button_ctx(&CTX, button); }
bool mdc_render_button_ctx(MDContext* ctx, MDCButton button) {
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
        if (i == 0) {
            cmd.as.box.box.y -= thickness*0.5;
            cmd.as.box.box.h += thickness*0.5;
        }
        cmd.as.box.box.x -= thickness*(0.5 + (f32)i*0.25);
        cmd.as.box.box.w += thickness*(1.0 + (f32)i*0.5);
        cmd.as.box.box.h += thickness*(1.5 + (f32)i*0.5);
        cmd.as.box.color = COLOR.Black;
        cmd.as.box.color.a = 51 * MIN(5, button.elevation);
        cmd.as.box.round = button.round;
        APPEND(cmd);
    }

    // background
    if (button.selected || button.state == MD_BUTTON_STATE_DISABLED || button.design != MD_BUTTON_DESIGN_OUTLINED) {
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
    if (button.design == MD_BUTTON_DESIGN_OUTLINED && button.type == MD_BUTTON_TYPE_TOGGLE && !button.selected) {
        f32 thickness = 1;
        if (button.size == MD_SIZE_L) thickness = 2;
        if (button.size == MD_SIZE_XL) thickness = 3;
        thickness = md_dp2px_ctx(ctx, thickness);
        cmd.type = MD_COMMAND_DRAW_OUTLINE;
        cmd.as.outline.box = button.box;
        cmd.as.outline.color = button.bg;
        cmd.as.outline.round = button.round;
        cmd.as.outline.thickness = md_dp2px_ctx(ctx, thickness);
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
        cmd.type = MD_COMMAND_DRAW_OUTLINE;
        cmd.as.outline.box = button.box;
        cmd.as.outline.box.x -= thickness;
        cmd.as.outline.box.y -= thickness;
        cmd.as.outline.box.w += thickness*2;
        cmd.as.outline.box.h += thickness*2;
        cmd.as.outline.color = COLOR.Scheme.OnSurfaceVariant; // probably
        cmd.as.outline.round = button.round;
        cmd.as.outline.round.tl += thickness;
        cmd.as.outline.round.tr += thickness;
        cmd.as.outline.round.bl += thickness;
        cmd.as.outline.round.br += thickness;
        cmd.as.outline.thickness = md_dp2px_ctx(ctx, thickness/(2+offset)*2);
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

MDCTab mdc_tab(MDCTab tab) { return mdc_tab_ctx(&CTX, tab); }
MDCTab mdc_tab_ctx(MDContext* ctx, MDCTab tab) {
    // {{{
    bool t_pri=0, t_sec=0;
    switch (tab.type) {
        // {{{
        case MDC_TAB_TYPE_PRIMARY:   t_pri=1; break;
        case MDC_TAB_TYPE_SECONDARY: t_sec=1; break;
        default: MD_ERROR("Unknown tab type."); UNREACHABLE();
        // }}}
    }

    bool s_ena=0, s_hov=0, s_foc=0, s_pre=0;
    switch (tab.state) {
        // {{{
        case MDC_TAB_STATE_ENABLED:  s_ena=1; break;
        case MDC_TAB_STATE_HOVERED:  s_hov=1; break;
        case MDC_TAB_STATE_FOCUSED:  s_foc=1; break;
        case MDC_TAB_STATE_PRESSED:  s_pre=1; break;
        default: MD_ERROR("Unknown tab state."); UNREACHABLE();
        // }}}
    }

    bool a_inl=0, a_sta=0;
    switch (tab.icon_align) {
        // {{{
        case MD_ICON_ALIGN_INLINED: a_inl=1; break;
        case MD_ICON_ALIGN_STACKED: a_sta=1; break;
        default: MD_ERROR("Unknown tab icon alignment."); UNREACHABLE();
        // }}}
    }

    u8 state_layer = 0;
    if (s_hov) state_layer = (u8)(255.0f*0.1f); // should be 0.08
    if (s_pre || (s_foc && tab.active)) state_layer = (u8)(255.0f*0.15f); // should be 0.1
    tab.state_layer = state_layer;

    tab.bg = COLOR.Scheme.Surface;

    if ( tab.active &&  t_pri) tab.fg = COLOR.Scheme.Primary;
    if ( tab.active &&  t_sec) tab.fg = COLOR.Scheme.OnSurface;
    if (!tab.active &&  s_ena) tab.fg = COLOR.Scheme.OnSurfaceVariant;
    if (!tab.active && !s_ena) tab.fg = COLOR.Scheme.OnSurface;

    tab.icon_size = md_dp2px_ctx(ctx, 24) * 1.5; // 1.5 to make it look slightly better, unsure what causes the problem
    tab.font_size = md_dp2px_ctx(ctx, md_pt2dp_ctx(ctx, 14));
    tab.text_size = ctx->measure_text(tab.text, tab.font_size);

    tab.box.h = MAX(tab.box.h, md_dp2px_ctx(ctx, 48));
    if (tab.icon_code != 0 && a_sta) tab.box.h = md_dp2px_ctx(ctx, 64);

    f32 good_width = 0;
    good_width = tab.box.h + tab.text_size.x;
    if (tab.icon_code != 0 && a_inl) good_width += md_dp2px_ctx(ctx, 24 + 4);
    tab.box.w = MAX(tab.box.w, good_width);

    return tab;
    // }}}
}

bool mdc_render_tab(MDCTab tab) { return mdc_render_tab_ctx(&CTX, tab); }
bool mdc_render_tab_ctx(MDContext* ctx, MDCTab tab) {
    // {{{
    #define APPEND(CMD) md_ctx_append_ctx(ctx, (CMD)); (CMD)=(MDCommand){0}
    MDCommand cmd = {0};

    f32 dp = md_dp2px_ctx(ctx, 1);

    // background
    cmd.type = MD_COMMAND_DRAW_BOX;
    cmd.as.box.box = tab.box;
    cmd.as.box.color = tab.bg;
    APPEND(cmd);

    // state layer
    if (tab.state_layer > 0) {
        cmd.type = MD_COMMAND_DRAW_BOX;
        cmd.as.box.box = tab.box;
        cmd.as.box.color = tab.fg;
        cmd.as.box.color.a = tab.state_layer;
        APPEND(cmd);
    }

    // text & icon
    if (tab.icon_code == 0) {
        cmd.type = MD_COMMAND_DRAW_TEXT;
        cmd.as.text.text = tab.text;
        cmd.as.text.color = tab.fg;
        cmd.as.text.font_size = tab.font_size;
        cmd.as.text.box.x = tab.box.x + (tab.box.w - tab.text_size.x)/2.0;
        cmd.as.text.box.y = tab.box.y + (tab.box.h - tab.text_size.y)/2.0;
        APPEND(cmd);
    } else {
        f32 gap = 4*dp;

        cmd.type = MD_COMMAND_DRAW_ICON;
        cmd.as.icon.codepoint = tab.icon_code;
        cmd.as.icon.color = tab.fg;
        cmd.as.icon.icon_size = tab.icon_size;
        cmd.as.icon.box.x = tab.box.x + (tab.box.w - tab.text_size.x)/2.0;
        cmd.as.icon.box.y = tab.box.y + (tab.box.h - tab.icon_size)/2.0;
        if (tab.icon_align == MD_ICON_ALIGN_STACKED) {
            cmd.as.icon.box.x = tab.box.x + (tab.box.w - tab.icon_size)/2.0;
            cmd.as.icon.box.y = tab.box.y + (tab.box.h - tab.icon_size - tab.text_size.y)/2.0;
        } else {
            cmd.as.icon.box.x = tab.box.x + (tab.box.w - tab.icon_size - tab.text_size.x - gap)/2.0;
            cmd.as.icon.box.y = tab.box.y + (tab.box.h - tab.icon_size)/2.0;
        }
        APPEND(cmd);

        cmd.type = MD_COMMAND_DRAW_TEXT;
        cmd.as.text.text = tab.text;
        cmd.as.text.color = tab.fg;
        cmd.as.text.font_size = tab.font_size;
        if (tab.icon_align == MD_ICON_ALIGN_STACKED) {
            cmd.as.text.box.x = tab.box.x + (tab.box.w - tab.text_size.x)/2.0;
            cmd.as.text.box.y = tab.box.y + (tab.box.h + tab.icon_size - tab.text_size.y)/2.0;
            cmd.as.text.box.y -= 3*dp;
        } else {
            cmd.as.icon.box.x = tab.box.x + (tab.box.w + tab.icon_size - tab.text_size.x + gap)/2.0;
            cmd.as.icon.box.y = tab.box.y + (tab.box.h - tab.text_size.y)/2.0;
        }
        APPEND(cmd);
    }

    // focus
    if (tab.state == MDC_TAB_STATE_FOCUSED) {
        f32 offset = 3*dp;
        if (tab.active) {
            if (tab.type == MDC_TAB_TYPE_PRIMARY) {
                offset += 3*dp;
            } else {
                offset += 2*dp;
            }
        }
        f32 thickness = 2*dp;
        f32 roundness = 8*dp; // probably
        cmd.type = MD_COMMAND_DRAW_OUTLINE;
        cmd.as.outline.box = tab.box;
        cmd.as.outline.box.x += dp;
        cmd.as.outline.box.y += dp;
        cmd.as.outline.box.w -= 2*dp;
        cmd.as.outline.box.h -= offset;
        cmd.as.outline.color = COLOR.Scheme.OnSurfaceVariant; // probably
        cmd.as.outline.round.tl = roundness;
        cmd.as.outline.round.tr = roundness;
        cmd.as.outline.round.bl = roundness;
        cmd.as.outline.round.br = roundness;
        cmd.as.outline.thickness = thickness;
        APPEND(cmd);
    }

    // active indicator
    if (tab.active) {
        cmd.type = MD_COMMAND_DRAW_BOX;
        cmd.as.box.box = tab.box;
        cmd.as.box.box.y += cmd.as.box.box.h - 2*dp;
        cmd.as.box.box.h = 2*dp;
        if (tab.type == MDC_TAB_TYPE_PRIMARY) {
            cmd.as.box.box.y -= dp;
            cmd.as.box.box.h += dp;
            cmd.as.box.round.tl = 3*dp;
            cmd.as.box.round.tr = 3*dp;
            cmd.as.box.round.bl = 0;
            cmd.as.box.round.br = 0;
            cmd.as.box.box.w = tab.text_size.x - 2*dp;
            if (tab.icon_code != 0 && tab.icon_align == MD_ICON_ALIGN_INLINED) {
                cmd.as.box.box.w += tab.icon_size + 4*dp;
            }
            cmd.as.box.box.w = MAX(cmd.as.box.box.w, 24*dp);
        }
        cmd.as.box.box.x += (tab.box.w - cmd.as.box.box.w) / 2.0;
        cmd.as.box.color = COLOR.Scheme.Primary;
        APPEND(cmd);
    }

    // divider
    cmd.type = MD_COMMAND_DRAW_BOX;
    cmd.as.box.box = tab.box;
    cmd.as.box.box.y += cmd.as.box.box.h - dp;
    cmd.as.box.box.h = dp;
    cmd.as.box.color = COLOR.Scheme.OutlineVariant;
    APPEND(cmd);

    return true;
    #undef APPEND
    // }}}
}

MDComponent mdc_component(MDComponent component) { return mdc_component_ctx(&CTX, component); }
MDComponent mdc_component_ctx(MDContext* ctx, MDComponent component) {
    // {{{
    switch (component.type) {
        case MDC_DIV: component.as.div = mdc_div_ctx(ctx, component.as.div); break;
        case MDC_BUTTON: component.as.button = mdc_button_ctx(ctx, component.as.button); break;
        case MDC_TAB: component.as.tab = mdc_tab_ctx(ctx, component.as.tab); break;
        default: MD_ERROR("Unknown component type"); UNREACHABLE();
    }
    return component;
    // }}}
}

bool mdc_render_component(MDComponent component) { return mdc_render_component_ctx(&CTX, component); }
bool mdc_render_component_ctx(MDContext* ctx, MDComponent component) {
    // {{{
    switch (component.type) {
        case MDC_DIV: return mdc_render_div_ctx(ctx, component.as.div); break;
        case MDC_BUTTON: return mdc_render_button_ctx(ctx, component.as.button); break;
        case MDC_TAB: return mdc_render_tab_ctx(ctx, component.as.tab); break;
        default: MD_ERROR("Unknown component type"); UNREACHABLE();
    }
    return false;
    // }}}
}

i32 mdl_element_add(MDElement elem, i32 parent_index) { return mdl_element_add_ctx(&CTX, elem, parent_index); }
i32 mdl_element_add_ctx(MDContext* ctx, MDElement elem, i32 parent_index) {
    // {{{
    if (ctx->nodes_len >= MD_MAX_NODES) {
        MD_ERROR("Context memory (elements) was not big enough.");
        UNREACHABLE();
        return MD_NIL_NODE;
    }

    i32 self = ctx->nodes_len++;
    MDLayoutNode* this = &ctx->nodes[self];
    this->element = elem;
    this->self = self;
    this->parent = parent_index;
    this->child_first = MD_NIL_NODE;
    this->child_last = MD_NIL_NODE;
    this->sibling_next = MD_NIL_NODE;
    this->sibling_prev = MD_NIL_NODE;

    if (parent_index != MD_NIL_NODE) {
        MDLayoutNode* parent = &ctx->nodes[parent_index];
        if (parent->child_last == MD_NIL_NODE) {
            // no children were set before
            parent->child_first = self;
            parent->child_last = self;
        } else {
            // append to the end
            MDLayoutNode* old_last_child = &ctx->nodes[parent->child_last];
            old_last_child->sibling_next = self;
            this->sibling_prev = parent->child_last;
            parent->child_last = self;
        }
    }

    return self;
    // }}}
}

void _mdl_render_layout_ctx(MDContext* ctx, MDBox box, i32 id, i32 depth) {
    // {{{
    if (id == MD_NIL_NODE) return;

    MDLayoutNode* node = &ctx->nodes[id];

    switch (node->element.type) {
        case MDL_TYPE_TAB: {
            MDCommand cmd = {0};
            cmd.type = MD_COMMAND_DRAW_LAYOUT;
            cmd.as.layout.id = node->element.id;
            cmd.as.layout.box = box;
            md_ctx_append_ctx(ctx, cmd);

            cmd = (MDCommand){0};
            cmd.type = MD_COMMAND_DRAW_OUTLINE;
            box.x += 10;
            box.y += 10;
            box.w -= 20;
            box.h -= 20;
            cmd.as.outline.box = box;
            cmd.as.outline.color = COLOR.Red[50];
            cmd.as.outline.thickness = 1;
            cmd.as.outline.round.tl = 10;
            cmd.as.outline.round.tr = 10;
            cmd.as.outline.round.bl = 10;
            cmd.as.outline.round.br = 10;
            md_ctx_append_ctx(ctx, cmd);
            return; // leaf node, guaranteed* to not have children
        }; break;
        case MDL_TYPE_TABS: {
            // TODO: handle the tabbar offset properly
            // f32 tabbar_height = 60;
            // box.y += tabbar_height;
            // box.h -= tabbar_height;
            i32 active_tab = node->child_first;
            if (active_tab == MD_NIL_NODE) {
                MD_ERROR("TABS layout requires at least 1 child");
                return;
            }
            i32 N = *node->element.tab;
            for (i32 i = 0; i < N; i++) {
                active_tab = ctx->nodes[active_tab].sibling_next;
                if (active_tab == MD_NIL_NODE) {
                    MD_ERROR("TABS layout could not find child #%d, only up to %d were found", N, i);
                    return;
                }
            }
            _mdl_render_layout_ctx(ctx, box, active_tab, depth + 1);
            return;
        }; break;
        case MDL_TYPE_STACK: {
            i32 child_top = node->child_first;
            if (child_top == MD_NIL_NODE) {
                MD_ERROR("STACK layout requires 2 children, got 0");
                return;
            }
            i32 child_bot = ctx->nodes[child_top].sibling_next;
            if (child_bot == MD_NIL_NODE) {
                MD_ERROR("STACK layout requires 2 children, got 1");
                return;
            }
            if (ctx->nodes[child_bot].sibling_next != MD_NIL_NODE) {
                MD_WARN("STACK layout requires 2 children, the rest are ignored.");
            }

            MDBox box_top = box;
            MDBox box_bot = box;
            box_top.h *= *node->element.split;
            box_bot.y += box_top.h;
            box_bot.h -= box_top.h;

            _mdl_render_layout_ctx(ctx, box_top, child_top, depth + 1);
            _mdl_render_layout_ctx(ctx, box_bot, child_bot, depth + 1);

            MDBox box_div = box;
            box_div.x += 10;
            box_div.w -= 20;
            box_div.h = 10;
            box_div.y = box_bot.y - 5;

            MDCommand cmd = {0};
            cmd.type = MD_COMMAND_DRAW_BOX;
            cmd.as.box.box = box_div;
            cmd.as.box.color = COLOR.Blue[50];
            md_ctx_append_ctx(ctx, cmd);
            return;
        }; break;
        case MDL_TYPE_INLINE: {
            i32 child_l = node->child_first;
            if (child_l == MD_NIL_NODE) {
                MD_ERROR("INLINE layout requires 2 children, got 0");
                return;
            }
            i32 child_r = ctx->nodes[child_l].sibling_next;
            if (child_r == MD_NIL_NODE) {
                MD_ERROR("INLINE layout requires 2 children, got 1");
                return;
            }
            if (ctx->nodes[child_r].sibling_next != MD_NIL_NODE) {
                MD_WARN("INLINE layout requires 2 children, the rest are ignored.");
            }

            MDBox box_l = box;
            MDBox box_r = box;
            box_l.w *= *node->element.split;
            box_r.x += box_l.w;
            box_r.w -= box_l.w;

            _mdl_render_layout_ctx(ctx, box_l, child_l, depth + 1);
            _mdl_render_layout_ctx(ctx, box_r, child_r, depth + 1);

            MDBox box_div = box;
            box_div.y += 10;
            box_div.h -= 20;
            box_div.w = 10;
            box_div.x = box_r.x - 5;

            MDCommand cmd = {0};
            cmd.type = MD_COMMAND_DRAW_BOX;
            cmd.as.box.box = box_div;
            cmd.as.box.color = COLOR.Blue[50];
            md_ctx_append_ctx(ctx, cmd);
            return;
        }; break;
        default: UNREACHABLE();
    }
    UNREACHABLE();
    // }}}
}

bool mdl_render_layout(void) { return mdl_render_layout_ctx(&CTX); }
bool mdl_render_layout_ctx(MDContext* ctx) {
    // {{{
    // TODO: handle invalid state here
    Vec2 screen = ctx->get_window_size();
    MDBox box = {0};
    box.w = screen.x;
    box.h = screen.y;
    _mdl_render_layout_ctx(ctx, box, 0, 0);
    ctx->nodes_len = 0;
    return true;
    // }}}
}



// DP = PX * 160 / DPI
f32 md_px2dp(f32 px) { return md_px2dp_ctx(&CTX, px); }
f32 md_px2dp_ctx(MDContext* ctx, f32 px) {
    return (f32)px / (ctx->scaling * ctx->ppi/160.0f);
}

// PX = DP * DPI / 160
f32 md_dp2px(f32 dp) { return md_dp2px_ctx(&CTX, dp); }
f32 md_dp2px_ctx(MDContext* ctx, f32 dp) {
    return (f32)(0.5 + dp * (ctx->scaling * ctx->ppi/160.0f)); // +0.5 to round
}

// DP = PT * 160 / 96
// PX = PT * DPI / 96
f32 md_pt2dp(f32 pt) { return md_pt2dp_ctx(&CTX, pt); }
f32 md_pt2dp_ctx(MDContext* ctx, f32 pt) {
    UNUSED(ctx);
    return pt * 160.0f/96.0f * 0.66f;
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
    for (u8 i = 0; i < 101; i++) colors[i] = (MDColor){0};
    colors[0] = (MDColor){0,0,0,0xFF};
    colors[100] = (MDColor){0xFF,0xFF,0xFF,0xFF};

    // Baseline
    #define Y(NAME, Name) \
        COMBINE(MATERIAL_PALETTE_BASELINE_, NAME); \
        if (interpolate) _fill_in_gaps(colors); \
        for (u8 i = 0; i < 101; i++) ACCESS(Name)[i] = colors[i]; \
        for (u8 i = 1; i < 100; i++) colors[i] = (MDColor){0};

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
        for (u8 i = 1; i < 100; i++) colors[i] = (MDColor){0};

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
