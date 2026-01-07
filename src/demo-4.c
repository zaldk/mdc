#include "../thirdparty/raylib-5.5_linux_amd64/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#define MD_UI_IMPLEMENTATION
#include "md_ui.h"
#include <assert.h>
#include <stdlib.h>

#define RL1(C) (Color){(C).r,(C).g,(C).b,51}
#define RL2(C,O) (Color){(C).r,(C).g,(C).b,(O)}

#define ROBOTO_FLEX "assets/Roboto/Flex/RobotoFlex-VariableFont_GRAD,XOPQ,XTRA,YOPQ,YTAS,YTDE,YTFI,YTLC,YTUC,opsz,slnt,wdth,wght.ttf"
#define ROBOTO_CONDENSED "assets/Roboto/Condensed/static/RobotoCondensed-Regular.ttf"
static Font roboto;

void DrawTextCentered(const char* text, f32 size, int x, int y, int w, int h, color_t fg) {
    Vector2 sz = MeasureTextEx(roboto, text, size, 0);
    DrawTextEx(roboto, text, (Vector2){x+(w-sz.x)/2, y+(h-sz.y)/2}, size, 0, fg);
}

void DrawBoxRound(f32 x, f32 y, f32 w, f32 h, f32 tlr, f32 trr, f32 blr, f32 brr, color_t bg) {
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
void DrawBoxRoundLines(f32 x, f32 y, f32 w, f32 h, f32 tlr, f32 trr, f32 blr, f32 brr, color_t bg) {
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

    // TODO:make this actually useful...
    if (r1 > 0) DrawCircleSectorLines((Vector2){x1,y1}, r1, 180, 270, 10, bg);
    if (r2 > 0) DrawCircleSectorLines((Vector2){x2,y2}, r2, 270, 360, 10, bg);
    if (r3 > 0) DrawCircleSectorLines((Vector2){x3,y3}, r3,  90, 180, 10, bg);
    if (r4 > 0) DrawCircleSectorLines((Vector2){x4,y4}, r4,   0,  90, 10, bg);

    if (w5 > 0 && h5 > 0) DrawRectangleLinesEx((Rectangle){x5,y5,w5,h5}, 1, bg);
    if (w6 > 0 && h6 > 0) DrawRectangleLinesEx((Rectangle){x6,y6,w6,h6}, 1, bg);
    if (w7 > 0 && h7 > 0) DrawRectangleLinesEx((Rectangle){x7,y7,w7,h7}, 1, bg);
    if (w8 > 0 && h8 > 0) DrawRectangleLinesEx((Rectangle){x8,y8,w8,h8}, 1, bg);
    if (w9 > 0 && h9 > 0) DrawRectangleLinesEx((Rectangle){x9,y9,w9,h9}, 1, bg);
    // }}}
}

void DrawLayout() {
    // {{{
    for (u8 state = 0; state < 5; state++) {
        for (u8 design = 0; design < 5; design++) {
            u8 x = state;
            u8 y = design;
            if (y == 0) DrawTextEx(roboto, TextFormat("%d", x+1),   (Vector2){100+x*150-10,  50+y*150-20}, 20, 0, COLOR.Scheme.OnBackground);
            if (x == 0) DrawTextEx(roboto, TextFormat("%c", y+'A'), (Vector2){ 50+x*150-15, 100+y*150-10}, 20, 0, COLOR.Scheme.OnBackground);

            for (u8 type = 0; type < 3; type++) {
                if (design == MD_BUTTON_DESIGN_TEXT && type > 0) continue;
                md_button_t input = {0}; input.state = state; input.design = design;
                input.type = type;
                input.text = type == 0 ? "Default" : type == 1 ? "Unselected" : "Selected";
                input.box = (box_t){50+x*150, 50+y*150 + 37*type, 100, 25};
                md_button_t output = md_button(input);
                md_render_button(output);
            }
        }
    }

    // DrawTextEx(roboto, "Button Reference", (Vector2){5, 0}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(roboto, "Styles (Y): A=Elevated | B=Filled | C=Tonal | D=Outline | E=Text", (Vector2){5, 740}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(roboto, "States (X): 1=Default | 2=Disabled | 3=Hovered | 4=Focused | 5=Pressed", (Vector2){5, 760}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    // }}}
}

#define R(N) (rand()%(N))

vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(roboto, text, font_size_px, 0);
}

int main(void) {
    md_color_global_init(true);

    const int W = 800;
    const int H = W;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "FLOAT");
    // SetTargetFPS(500);

    vec2 monitor_size = (vec2){GetMonitorPhysicalWidth(GetCurrentMonitor()), GetMonitorPhysicalHeight(GetCurrentMonitor())};
    vec2 monitor_resolution = (vec2){GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor())};
    void* cmd_list_memory = calloc(MD_COMMANDS_MAXIMUM_QUANTITY, sizeof(md_command_t));
    md_ctx_init(monitor_size, monitor_resolution, cmd_list_memory, measure_text_fn);

    roboto = LoadFontEx(ROBOTO_FLEX, 20, NULL, 0);
    GenTextureMipmaps(&roboto.texture);
    SetTextureFilter(roboto.texture, TEXTURE_FILTER_TRILINEAR);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
        BeginDrawing();
        ClearBackground(COLOR.Scheme.Background);

        for (int y = H/200; y < H; y += H/100) {
            for (int x = W/200; x < W; x += W/100) {
                color_t col = COLOR.Scheme.OnBackground;
                col.a = 51;
                DrawPixel(x, y, col);
            }
        }

        DrawLayout();
        md_command_t cmd = {0};
        int counter = 0;
        while (md_ctx_poll(&cmd)) {
            switch (cmd.type) {
                case MD_COMMAND_DRAW_BOX: {
                    box_t box = cmd.as.box.box;
                    md_corners_t round = cmd.as.box.round;
                    color_t col = cmd.as.box.color;
                    // MD_DEBUG("[%lf]\t[%d] box.x=%.0f\tbox.y=%.0f\tbox.w=%.0f\tbox.h=%.0f", GetTime(), counter, box.x, box.y, box.w, box.h);
                    // MD_DEBUG("[%lf]\t[%d] rnd.tl=%.0f\trnd.tr=%.0f\trnd.bl=%.0f\trnd.br=%.0f", GetTime(), counter, round.tl, round.tr, round.bl, round.br);
                    // MD_DEBUG("[%lf]\t[%d] col.r=%02X\tcol.g=%02X\tcol.b=%02X\tcol.a=%02X", GetTime(), counter, col.r, col.g, col.b, col.a);
                    DrawBoxRound(box.x, box.y, box.w, box.h, round.tl, round.tr, round.bl, round.br, col);
                }; break;
                case MD_COMMAND_DRAW_TEXT: {
                    box_t box = cmd.as.text.box;
                    color_t col = cmd.as.text.color;
                    DrawTextEx(roboto, cmd.as.text.text, (Vector2){box.x, box.y}, cmd.as.text.font_size, 0, col);
                }; break;
                default: UNREACHABLE();
            }
            counter++;
        }

        DrawTextEx(roboto, "Press 'Space' To Change Theme", (Vector2){5, 780}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        // DrawFPS(0,0);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
