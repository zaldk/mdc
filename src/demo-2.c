#include "../thirdparty/raylib/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#define MD_UI_IMPLEMENTATION
#include "md_ui.h"

#define RL(C) (Color){(C).r,(C).g,(C).b,(C).a}

void DrawLayout1(void) {
    for (int y = 0; y < 100; y++) {
        #define Y(Space, Name, Index) DrawRectangle(Index*50, y*8, 50,8, RL(COLOR.Name[y]));
        COLOR_LABELS_ALL
        #undef Y
    }
}

int main(void) {
    bool interpolate = true;
    md_color_global_init(interpolate);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(700, 800, "FLOAT");
    SetTargetFPS(500);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            interpolate = !interpolate;
            md_color_global_init(interpolate);
        }
        BeginDrawing();
        ClearBackground(RL_BLACK);
        DrawLayout1();
        DrawText("Press 'Space' To Toggle Interpolation", 5, 800-20, 20.0, RL_BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
