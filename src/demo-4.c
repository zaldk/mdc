#include "../thirdparty/raylib-5.5_linux_amd64/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#include "md_ui.h"
#include <assert.h>
#include <stdlib.h>

#define RL(C) (Color){(C).r,(C).g,(C).b,(C).a}
#define RL1(C) (Color){(C).r,(C).g,(C).b,51}
#define RL2(C,O) (Color){(C).r,(C).g,(C).b,(u8)((O)*255.0)}

#define ROBOTO_FLEX "assets/Roboto/Flex/RobotoFlex-VariableFont_GRAD,XOPQ,XTRA,YOPQ,YTAS,YTDE,YTFI,YTLC,YTUC,opsz,slnt,wdth,wght.ttf"
#define ROBOTO_CONDENSED "assets/Roboto/Condensed/static/RobotoCondensed-Regular.ttf"
static Font roboto;

void DrawTextCentered(const char* text, f32 size, int x, int y, int w, int h, color_t fg) {
    Vector2 sz = MeasureTextEx(roboto, text, size, 0);
    DrawTextEx(roboto, text, (Vector2){x+(w-sz.x)/2, y+(h-sz.y)/2}, size, 0, RL(fg));
}

void DrawBoxRound(f32 x, f32 y, f32 w, f32 h, f32 tlr, f32 trr, f32 blr, f32 brr, color_t bg) {
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
    f32 r1 = MIN(tlr, MIN(w/2, h/2));
    f32 r2 = MIN(trr, MIN(w/2, h/2));
    f32 r3 = MIN(blr, MIN(w/2, h/2));
    f32 r4 = MIN(brr, MIN(w/2, h/2));

    f32 x1,y1, x2,y2, x3,y3, x4,y4; // corner closest to the center of the box
    f32 x5,y5, x6,y6, x7,y7, x8,y8, x9,y9; // top-left corner
    f32 w5,h5, w6,h6, w7,h7, w8,h8, w9,h9;

    x1 = x + r1; y1 = y + r1;
    x2 = x+w-r2; y2 = y + r2;
    x3 = x + r3; y3 = y+h-r3;
    x4 = x+w-r4; y4 = y+h-r4;

    x5 = x + r1; y5 = y; w5 = w - r1 - r2; h5 = MIN(r1, r2);
    x6 = x + r3; y6 = y + h - MIN(r3, r4); w6 = w - r3 - r4; h6 = MIN(r3, r4);
    x7 = x + (r1>r2 ? r1 : 0); y7 = y + MIN(r1, r2); w7 = w - MAX(r1, r2); h7 = ABS(r1 - r2);
    x8 = x + (r3>r4 ? r3 : 0); y8 = y + h - MAX(r3, r4); w8 = w - MAX(r3, r4); h8 = ABS(r3 - r4);
    x9 = x; y9 = y + MAX(r1, r2); w9 = w; h9 = h - MAX(r1, r2) - MAX(r3, r4);

    if (r1 > 0) DrawCircleSector((Vector2){x1,y1}, r1, 180, 270, 10, RL(COLOR.Red[30]));
    if (r2 > 0) DrawCircleSector((Vector2){x2,y2}, r2, 270, 360, 10, RL(COLOR.Green[30]));
    if (r3 > 0) DrawCircleSector((Vector2){x3,y3}, r3,  90, 180, 10, RL(COLOR.Blue[30]));
    if (r4 > 0) DrawCircleSector((Vector2){x4,y4}, r4,   0,  90, 10, RL(COLOR.Yellow[30]));

    if (w5 > 0 && h5 > 0) DrawRectangleRec((Rectangle){x5,y5,w5,h5}, RL(COLOR.Red[60]));
    if (w6 > 0 && h6 > 0) DrawRectangleRec((Rectangle){x6,y6,w6,h6}, RL(COLOR.Green[60]));
    if (w7 > 0 && h7 > 0) DrawRectangleRec((Rectangle){x7,y7,w7,h7}, RL(COLOR.Blue[60]));
    if (w8 > 0 && h8 > 0) DrawRectangleRec((Rectangle){x8,y8,w8,h8}, RL(COLOR.Yellow[80]));
    if (w9 > 0 && h9 > 0) DrawRectangleRec((Rectangle){x9,y9,w9,h9}, RL(COLOR.Purple[60]));
}

void DrawLayout() {
    // {{{
    for (u8 state = 0; state < 5; state++) {
        for (u8 style = 0; style < 5; style++) {
            u8 x = state;
            u8 y = style;
            DrawTextEx(roboto, TextFormat("%d", x+1),   (Vector2){100+x*150-10,  50+y*150-20}, 20, 0, RL(COLOR.Scheme.OnBackground));
            DrawTextEx(roboto, TextFormat("%c", y+'A'), (Vector2){ 50+x*150-15, 100+y*150-10}, 20, 0, RL(COLOR.Scheme.OnBackground));

            {
                md_button_t input = {0}; input.state = state; input.style = style; input.type = 0;
                md_button_t output = md_button(input);
                DrawRectangle(50+x*150, 50+y*150, 100,25, RL(output.bg));
                DrawRectangle(50+x*150, 50+y*150, 100,25, RL2(output.fg, output.state_layer));
                DrawTextCentered("Default", 15, 75+x*150, 56+y*150, 50,12, output.fg);
            }
            if (style < 4) {
                md_button_t input = {0}; input.state = state; input.style = style; input.type = 1; input.toggle = 0;
                md_button_t output = md_button(input);
                DrawRectangle(50+x*150, 50+y*150+37, 100,25, RL(output.bg));
                DrawRectangle(50+x*150, 50+y*150+37, 100,25, RL2(output.fg, output.state_layer));
                DrawTextCentered("Selected", 15, 75+x*150, 56+y*150+37, 50,12, output.fg);
            }
            if (style < 4) {
                md_button_t input = {0}; input.state = state; input.style = style; input.type = 1; input.toggle = 1;
                md_button_t output = md_button(input);
                DrawRectangle(50+x*150, 50+y*150+75, 100,25, RL(output.bg));
                DrawRectangle(50+x*150, 50+y*150+75, 100,25, RL2(output.fg, output.state_layer));
                DrawTextCentered("Unselected", 15, 75+x*150, 56+y*150+75, 50,12, output.fg);
            }
        }
    }

    DrawTextEx(roboto, "Button Reference", (Vector2){5, 0}, 20.0, 0.0, RL(COLOR.Scheme.OnBackground));
    DrawTextEx(roboto, "Styles: A=Elevated B=Filled C=Tonal D=Outline E=Text", (Vector2){5, 740}, 20.0, 0.0, RL(COLOR.Scheme.OnBackground));
    DrawTextEx(roboto, "States: 1=Default 2=Disabled 3=Hovered 4=Focused 5=Pressed", (Vector2){5, 760}, 20.0, 0.0, RL(COLOR.Scheme.OnBackground));
    // }}}
}

#define R(N) (rand()%(N))

int main(void) {
    md_color_global_init(true);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(800, 800, "FLOAT");
    SetTargetFPS(500);

    roboto = LoadFontEx(ROBOTO_FLEX, 60, NULL, 0);
    GenTextureMipmaps(&roboto.texture);
    SetTextureFilter(roboto.texture, TEXTURE_FILTER_TRILINEAR);


    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
        BeginDrawing();
        ClearBackground(RL(COLOR.Scheme.Background));

        // srand(0);
        // for (int y = 0; y < 800; y += 200) {
        //     for (int x = 0; x < 800; x += 200) {
        //         DrawBoxRound(x+25,y+25,150,150, R(75),R(75),R(75),R(75), COLOR.Scheme.OnBackground);
        //     }
        // }

        DrawLayout();

        DrawTextEx(roboto, "Press 'Space' To Change Theme", (Vector2){5, 780}, 20.0, 0.0, RL(COLOR.Scheme.OnBackground));
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
/*
   style Elevated   Filled     Tonal      Outlined   Text
state
         Default    Default    Default    Default    Default
Default  Unselected Unselected Unselected Unselected Unselected
         Selected   Selected   Selected   Selected   Selected

         Default    Default    Default    Default    Default
Disabled Unselected Unselected Unselected Unselected Unselected
         Selected   Selected   Selected   Selected   Selected

         Default    Default    Default    Default    Default
Hovered  Unselected Unselected Unselected Unselected Unselected
         Selected   Selected   Selected   Selected   Selected

         Default    Default    Default    Default    Default
Focused  Unselected Unselected Unselected Unselected Unselected
         Selected   Selected   Selected   Selected   Selected

         Default    Default    Default    Default    Default
Pressed  Unselected Unselected Unselected Unselected Unselected
         Selected   Selected   Selected   Selected   Selected
*/
