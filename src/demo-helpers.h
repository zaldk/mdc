#include "../thirdparty/raylib/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#define MD_UI_IMPLEMENTATION
#include "md_ui.h"

#define R(N) (rand()%(N))
#define RL1(C) (Color){(C).r,(C).g,(C).b,51}
#define RL2(C,O) (Color){(C).r,(C).g,(C).b,(O)}

#define ROBOTO_PATH "assets/RobotoFlex/RobotoFlex-VariableFont_GRAD,XOPQ,XTRA,YOPQ,YTAS,YTDE,YTFI,YTLC,YTUC,opsz,slnt,wdth,wght.ttf"
#define ICONS_PATH "assets/MaterialSymbols/MaterialSymbolsRounded.ttf"
static Font ROBOTO, ICONS;

#include "../assets/MaterialSymbols/MaterialSymbolsRounded.h"
static const i32 ICON_COUNT = MATERIAL_SYMBOLS_COUNT;
static const char* ICON_NAME[MATERIAL_SYMBOLS_COUNT+1] = {
    NULL,
    #define X(CP, ID, NAME) (#NAME),
    MATERIAL_SYMBOLS
    #undef X
};
static i32 ICON_CODE[MATERIAL_SYMBOLS_COUNT+1] = {
    0,
    #define X(CP, ID, NAME) (CP),
    MATERIAL_SYMBOLS
    #undef X
};

i32 find_icon(const char* icon_name) {
    for (i32 i = 0; i < ICON_COUNT; i++) {
        if (TextIsEqual(ICON_NAME[i], icon_name)) {
            return ICON_CODE[i];
        }
    }
    return 0;
}

void init_fonts(bool load_icons) {
    ROBOTO = LoadFontEx(ROBOTO_PATH, 60, NULL, 0);
    GenTextureMipmaps(&ROBOTO.texture);
    SetTextureFilter(ROBOTO.texture, TEXTURE_FILTER_BILINEAR);

    if (load_icons) {
        ICONS = LoadFontEx(ICONS_PATH, 60, ICON_CODE, ICON_COUNT);
        GenTextureMipmaps(&ICONS.texture);
        SetTextureFilter(ICONS.texture, TEXTURE_FILTER_BILINEAR);
    }
}

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
