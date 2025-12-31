#include "../thirdparty/raylib-5.5_linux_amd64/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#include "md_ui.h"

#define RL(C) (Color){(C).r,(C).g,(C).b,(C).a}

#define ROBOTO_FLEX "assets/Roboto/Flex/RobotoFlex-VariableFont_GRAD,XOPQ,XTRA,YOPQ,YTAS,YTDE,YTFI,YTLC,YTUC,opsz,slnt,wdth,wght.ttf"
#define ROBOTO_CONDENSED "assets/Roboto/Condensed/static/RobotoCondensed-Regular.ttf"
static Font roboto;

int main(void) {
    md_init_global_color(true);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "Demo 3");
    SetTargetFPS(500);

    roboto = LoadFontEx(ROBOTO_FLEX, 60, NULL, 0);
    GenTextureMipmaps(&roboto.texture);
    SetTextureFilter(roboto.texture, TEXTURE_FILTER_TRILINEAR);

    int themeIndex = 0;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) themeIndex = !themeIndex;
        BeginDrawing();
        ClearBackground(RL_BLACK);
        DrawTextEx(roboto, "Press 'Space' To Change Theme", (Vector2){5, 580}, 20.0, 0.0, RL(COLOR.Scheme.OnBackground[themeIndex]));
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
