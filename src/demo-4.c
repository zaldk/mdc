#include "../thirdparty/raylib/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#define MD_UI_IMPLEMENTATION
#include "md_ui.h"
#include <assert.h>
#include <stdlib.h>

#define RL1(C) (Color){(C).r,(C).g,(C).b,51}
#define RL2(C,O) (Color){(C).r,(C).g,(C).b,(O)}

#define ROBOTO_FLEX "assets/RobotoFlex/RobotoFlex-VariableFont_GRAD,XOPQ,XTRA,YOPQ,YTAS,YTDE,YTFI,YTLC,YTUC,opsz,slnt,wdth,wght.ttf"
static Font roboto;

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

MDSize BUTTON_SIZE = MD_SIZE_M;
void DrawLayout() {
    // {{{
    f32 max_width = 0;
    f32 max_height = 0;
    {
        MDCButton input = {0}; input.design = 0; input.state = 0; input.type = 0; input.size = BUTTON_SIZE;
        input.text = "Unselected";
        MDCButton output = mdc_button(input);
        max_width = output.box.w;
        max_height = output.box.h;
    }

    f32 offset_x = 0;
    for (u8 state = 0; state < 5; state++) {
        f32 offset_y = 0;
        for (u8 design = 0; design < 5; design++) {
            f32 x = 20 + offset_x;
            f32 y = 20 + offset_y;
            if (design == 0) DrawTextEx(roboto, TextFormat("%d", state+1),    (Vector2){x-10+max_width/2, y-20}, 20, 0, COLOR.Scheme.OnBackground);
            if (state  == 0) DrawTextEx(roboto, TextFormat("%c", design+'A'), (Vector2){x-15, y-20+max_height*(design==4?0.75:2.25)}, 20, 0, COLOR.Scheme.OnBackground);

            f32 offset_z = 0;
            for (u8 type = 0; type < 3; type++) {
                if (design == MD_BUTTON_DESIGN_TEXT && type > 0) continue;
                MDCButton input = {0}; input.design = design; input.state = state; input.size = BUTTON_SIZE;
                input.type = type == 0 ? 0 : 1;
                input.selected = type == 2;
                input.text = type == 0 ? "Default" : type == 1 ? "Unselected" : "Selected";
                input.box.x = x;
                input.box.y = y + offset_z;
                input.box.w = max_width;
                MDCButton output = mdc_button(input);
                mdc_render_button(output);
                offset_z += output.box.h + 16;
            }
            offset_y += offset_z + 20;
        }
        offset_x += max_width + 20;
    }

    // DrawTextEx(roboto, "Button Reference", (Vector2){5, 0}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(roboto, "Press 1-5 To Change Button Sizes", (Vector2){5, GetScreenHeight()-80}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(roboto, "Styles (Y): A=Elevated | B=Filled | C=Tonal | D=Outline | E=Text", (Vector2){5, GetScreenHeight()-60}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(roboto, "States (X): 1=Default | 2=Disabled | 3=Hovered | 4=Focused | 5=Pressed", (Vector2){5, GetScreenHeight()-40}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    // }}}
}

#define R(N) (rand()%(N))

Vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(roboto, text, font_size_px, 0);
}

int main(void) {
    md_color_global_init(true);

    const int W = 650;
    const int H = 900;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "FLOAT");
    // SetTargetFPS(500);

    i32 mon = GetCurrentMonitor();
    Vec2 monitor_size = (Vec2){GetMonitorPhysicalWidth(mon), GetMonitorPhysicalHeight(mon)};
    Vec2 monitor_resolution = (Vec2){GetMonitorWidth(mon), GetMonitorHeight(mon)};
    MDCommand cmd_list_memory[MD_COMMANDS_QUANTITY] = {0};
    md_ctx_init(monitor_size, monitor_resolution);
    md_ctx_set_scaling(1);
    md_ctx_set_measure_text(measure_text_fn);
    md_ctx_set_memory_cmd(cmd_list_memory, MD_COMMANDS_QUANTITY);

    roboto = LoadFontEx(ROBOTO_FLEX, 60, NULL, 0);
    GenTextureMipmaps(&roboto.texture);
    SetTextureFilter(roboto.texture, TEXTURE_FILTER_TRILINEAR);

    i32 dp = md_dp2px(10);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
        if (IsKeyPressed(KEY_ONE))   BUTTON_SIZE = MD_SIZE_XS;
        if (IsKeyPressed(KEY_TWO))   BUTTON_SIZE = MD_SIZE_S;
        if (IsKeyPressed(KEY_THREE)) BUTTON_SIZE = MD_SIZE_M;
        if (IsKeyPressed(KEY_FOUR))  BUTTON_SIZE = MD_SIZE_L;
        if (IsKeyPressed(KEY_FIVE))  BUTTON_SIZE = MD_SIZE_XL;
        BeginDrawing();
        ClearBackground(COLOR.Scheme.Background);

        for (i32 y = 0; y < GetScreenHeight(); y += dp) {
            for (i32 x = 0; x < GetScreenWidth(); x += dp) {
                MDColor col = COLOR.Scheme.OnBackground;
                col.a = 51;
                DrawPixel(x, y, col);
            }
        }

        DrawLayout();
        MDCommand cmd = {0};
        int counter = 0;
        while (md_ctx_poll(&cmd)) {
            switch (cmd.type) {
                case MD_COMMAND_DRAW_BOX: {
                    MDBox box = cmd.as.box.box;
                    MDCorners round = cmd.as.box.round;
                    MDColor col = cmd.as.box.color;
                    DrawBoxRound(box.x, box.y, box.w, box.h, round.tl, round.tr, round.bl, round.br, col);
                }; break;
                case MD_COMMAND_DRAW_OUTLINE: {
                    MDBox box = cmd.as.outline.box;
                    MDCorners round = cmd.as.outline.round;
                    MDColor col = cmd.as.outline.color;
                    f32 thickness = cmd.as.outline.thickness;
                    DrawBoxRoundLines(box.x, box.y, box.w, box.h, round.tl, round.tr, round.bl, round.br, thickness, col);
                }; break;
                case MD_COMMAND_DRAW_TEXT: {
                    MDBox box = cmd.as.text.box;
                    MDColor col = cmd.as.text.color;
                    DrawTextEx(roboto, cmd.as.text.text, (Vector2){box.x, box.y}, cmd.as.text.font_size, 0, col);
                }; break;
                default: UNREACHABLE();
            }
            counter++;
        }

        DrawTextEx(roboto, "Press 'Space' To Change Theme", (Vector2){5, GetScreenHeight()-20}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        // DrawFPS(0,0);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
