#include "../thirdparty/raylib/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#define MD_UI_IMPLEMENTATION
#include "md_ui.h"
#include <assert.h>
#include <stdlib.h>

#define RL1(C) (Color){(C).r,(C).g,(C).b,51}
#define RL2(C,O) (Color){(C).r,(C).g,(C).b,(O)}

#define ROBOTO_FLEX "assets/RobotoFlex/RobotoFlex-VariableFont_GRAD,XOPQ,XTRA,YOPQ,YTAS,YTDE,YTFI,YTLC,YTUC,opsz,slnt,wdth,wght.ttf"
#define ICONS_PATH "assets/MaterialSymbols/MaterialSymbolsRounded.ttf"
static Font roboto, icons_font;

#include "../assets/MaterialSymbols/MaterialSymbolsRounded.h"
typedef struct {
    i32 codepoint;
    const char* name;
} Icon;
static Icon icons[MATERIAL_SYMBOLS_COUNT+1];
static i32 icon_codepoints[MATERIAL_SYMBOLS_COUNT+1];

void DrawBoxRound(f32 x, f32 y, f32 w, f32 h, f32 tlr, f32 trr, f32 blr, f32 brr, MDColor bg) {
    // {{{
    /* Normal
        /--+---+--\
       / 1 | 5 | 2 \
       +---+---+---+
       | 7 | 9 | 8 |
       +---+---+---+
       \ 3 | 6 | 4 /
        \--+---+--/  */
    /* Degenerate
       /---+------+---\
      /    |  5   | 2  \
     /  1  +------+-----+
    /      |     7      |
    +------+------------+
    |         9         |
    +----------+--------/
    |     8    |       /
    +---+------+  4   /
    \ 3 |  6   |     /
     \--+------+----/ */
    f32 r1 = MIN(tlr, MIN(w/2.0f, h/2.0f));
    f32 r2 = MIN(trr, MIN(w/2.0f, h/2.0f));
    f32 r3 = MIN(blr, MIN(w/2.0f, h/2.0f));
    f32 r4 = MIN(brr, MIN(w/2.0f, h/2.0f));

    f32 x1,y1, x2,y2, x3,y3, x4,y4; // corner closest to the center of the box
    f32 x5,y5, x6,y6, x7,y7, x8,y8, x9,y9; // top-left corner
    f32 w5,h5, w6,h6, w7,h7, w8,h8, w9,h9;

    x1 = x + r1; y1 = y + r1;
    x2 = x+w-r2; y2 = y + r2;
    x3 = x + r3; y3 = y+h-r3;
    x4 = x+w-r4; y4 = y+h-r4;

    x5 = x + r1;
    y5 = y;
    w5 = w - r1 - r2;
    h5 = MIN(r1, r2);

    x6 = x + r3;
    y6 = y + h - MIN(r3, r4);
    w6 = w - r3 - r4;
    h6 = MIN(r3, r4);

    x7 = x + (r1>r2 ? r1 : 0);
    y7 = y + MIN(r1, r2);
    w7 = w - MAX(r1, r2);
    h7 = ABS(r1 - r2);

    x8 = x + (r3>r4 ? r3 : 0);
    y8 = y + h - MAX(r3, r4);
    w8 = w - MAX(r3, r4);
    h8 = ABS(r3 - r4);

    x9 = x;
    y9 = y + MAX(r1, r2);
    w9 = w;
    h9 = h - MAX(r1, r2) - MAX(r3, r4);

    if (r1 > 0) DrawCircleSector((Vector2){x1,y1}, r1, 180, 270, 10, bg);
    if (r2 > 0) DrawCircleSector((Vector2){x2,y2}, r2, 270, 360, 10, bg);
    if (r3 > 0) DrawCircleSector((Vector2){x3,y3}, r3,  90, 180, 10, bg);
    if (r4 > 0) DrawCircleSector((Vector2){x4,y4}, r4,   0,  90, 10, bg);

    if (w5 > 0 && h5 > 0) DrawRectangleRec((Rectangle){x5,y5,w5,h5}, bg);
    if (w6 > 0 && h6 > 0) DrawRectangleRec((Rectangle){x6,y6,w6,h6}, bg);
    if (w7 > 0 && h7 > 0) DrawRectangleRec((Rectangle){x7,y7,w7,h7}, bg);
    if (w8 > 0 && h8 > 0) DrawRectangleRec((Rectangle){x8,y8,w8,h8}, bg);
    if (w9 > 0 && h9 > 0) DrawRectangleRec((Rectangle){x9,y9,w9,h9}, bg);
    // }}}
}

void DrawBoxRoundLines(f32 x, f32 y, f32 w, f32 h, f32 tlr, f32 trr, f32 blr, f32 brr, f32 thickness, MDColor color) {
    // {{{
    f32 r1 = MIN(tlr, MIN(w/2.0f, h/2.0f)); // top-left
    f32 r2 = MIN(trr, MIN(w/2.0f, h/2.0f)); // top-right
    f32 r3 = MIN(blr, MIN(w/2.0f, h/2.0f)); // bottom-left
    f32 r4 = MIN(brr, MIN(w/2.0f, h/2.0f)); // bottom-right

    f32 ht = thickness / 2.0f; // half thickness

    Vector2 c1 = {x + r1,     y + r1};     // top-left
    Vector2 c2 = {x + w - r2, y + r2};     // top-right
    Vector2 c3 = {x + r3,     y + h - r3}; // bottom-left
    Vector2 c4 = {x + w - r4, y + h - r4}; // bottom-right

    if (r1 > 0) DrawRing(c1, r1 - ht, r1 + ht, 180, 270, 10, color);
    if (r2 > 0) DrawRing(c2, r2 - ht, r2 + ht, 270, 360, 10, color);
    if (r3 > 0) DrawRing(c3, r3 - ht, r3 + ht,  90, 180, 10, color);
    if (r4 > 0) DrawRing(c4, r4 - ht, r4 + ht,   0,  90, 10, color);

    DrawRectangleRec((Rectangle){x + r1, y - ht, w - r1 - r2, thickness}, color);     // Top edge
    DrawRectangleRec((Rectangle){x + r3, y + h - ht, w - r3 - r4, thickness}, color); // Bottom edge
    DrawRectangleRec((Rectangle){x - ht, y + r1, thickness, h - r1 - r3}, color);     // Left edge
    DrawRectangleRec((Rectangle){x + w - ht, y + r2, thickness, h - r2 - r4}, color); // Right edge
    // }}}
}

void DrawLayout() {
    // {{{
    // MDButton input = {0}; input.design = design; input.state = state; input.type = type; input.size = BUTTON_SIZE;
    // input.text = type == 0 ? "Default" : type == 1 ? "Unselected" : "Selected";
    // input.box.x = x;
    // input.box.y = y + offset_z;
    // input.box.w = max_width;
    // MDButton output = md_button(input);
    // md_render_button(output);
    // }}}
}

#define R(N) (rand()%(N))

Vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(roboto, text, font_size_px, 0);
}

int main(void) {
    md_color_global_init(true);

    const int W = 800;
    const int H = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "FLOAT");
    // SetTargetFPS(500);

    i32 mon = GetCurrentMonitor();
    Vec2 monitor_size = (Vec2){GetMonitorPhysicalWidth(mon), GetMonitorPhysicalHeight(mon)};
    Vec2 monitor_resolution = (Vec2){GetMonitorWidth(mon), GetMonitorHeight(mon)};
    md_ctx_init(monitor_size, monitor_resolution);
    md_ctx_set_scaling(1);
    md_ctx_set_measure_text(measure_text_fn);

    roboto = LoadFontEx(ROBOTO_FLEX, 60, NULL, 0);
    GenTextureMipmaps(&roboto.texture);
    SetTextureFilter(roboto.texture, TEXTURE_FILTER_TRILINEAR);

    #define X(CP, ID, NAME) icons[ID] = (Icon){(CP), (#NAME)}; icon_codepoints[ID] = (CP);
    MATERIAL_SYMBOLS
    #undef X

    icons_font = LoadFontEx(ICONS_PATH, 60, icon_codepoints, MATERIAL_SYMBOLS_COUNT);
    GenTextureMipmaps(&icons_font.texture);
    SetTextureFilter(icons_font.texture, TEXTURE_FILTER_TRILINEAR);

    while (!WindowShouldClose()) {
        // {{{
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
        BeginDrawing();
        ClearBackground(COLOR.Scheme.Background);

        const f32 icon_size = 20;
        const i32 W = GetScreenWidth()/(i32)icon_size;
        const i32 H = GetScreenHeight()/(i32)icon_size;
        for (i32 y = 0; y < H; y++) {
            for (i32 x = 0; x < W; x++) {
                i32 index = y * W + x;
                if (index >= MATERIAL_SYMBOLS_COUNT) goto out;
                DrawTextCodepoint(icons_font, icons[index].codepoint, (Vector2){icon_size/2+icon_size*x, icon_size/2+icon_size*y}, icon_size, COLOR.Scheme.OnBackground);
            }
        }
    out:

        // DrawTextEx(roboto, "Press 'Space' To Change Theme", (Vector2){5, GetScreenHeight()-20}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        // DrawFPS(0,0);
        EndDrawing();
        // }}}
    }

    UnloadFont(icons_font);
    UnloadFont(roboto);
    CloseWindow();
    return 0;
}
