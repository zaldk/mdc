#include "../thirdparty/raylib-5.5_linux_amd64/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#include "md_ui.h"

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

        // DrawRectangleRounded((Rectangle){100-1,   100, 200+2, 100+2}, 0.5, 10, RL1(COLOR.Black));
        // DrawRectangleRounded((Rectangle){  100, 100+1,   200,   100}, 0.5, 10, RL1(COLOR.Black));
        // DrawRectangleRounded((Rectangle){  100,   100,   200,   100}, 0.5, 10, RL(COLOR.Scheme.SurfaceContainerLow));
        //
        // DrawRectangleRounded((Rectangle){100-1,   300, 200+2, 100+2}, 0.5, 10, RL1(COLOR.Black));
        // DrawRectangleRounded((Rectangle){  100,   300,   200,   100}, 0.5, 10, RL(COLOR.Scheme.SurfaceContainerLow));

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
