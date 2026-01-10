#include <assert.h>
#include <stdlib.h>

#include "demo-helpers.h"

void DrawLayout() {
    // {{{
    // }}}
}

Vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(ROBOTO, text, font_size_px, 0);
}

int main(void) {
    const int W = 800;
    const int H = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "FLOAT");
    // SetTargetFPS(500);
    init_fonts(); // must be done AFTER InitWindow()

    Vec2 monitor_size = (Vec2){GetMonitorPhysicalWidth(GetCurrentMonitor()), GetMonitorPhysicalHeight(GetCurrentMonitor())};
    Vec2 monitor_resolution = (Vec2){GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor())};
    void* cmd_list_memory = calloc(MD_COMMANDS_MAXIMUM_QUANTITY, sizeof(MDCommand));
    md_ctx_init(monitor_size, monitor_resolution, cmd_list_memory, measure_text_fn);
    md_ctx_set_scaling(1);

    md_color_global_init(true);
    i32 icon = find_icon("home");

    while (!WindowShouldClose()) {
        // {{{
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
        BeginDrawing();
        ClearBackground(COLOR.Scheme.Background);

        // dotted background
        i32 dp10 = (i32)md_dp2px(10);
        for (i32 y = 0; y < GetScreenHeight(); y += dp10) {
            for (i32 x = 0; x < GetScreenWidth(); x += dp10) {
                MDColor col = COLOR.Scheme.OnBackground;
                col.a = 51;
                DrawPixel(x, y, col);
            }
        }

        DrawTextCodepoint(ICONS, icon, (Vector2){50, 50}, 60, COLOR.Scheme.OnBackground);

        DrawLayout();
        MDCommand cmd = {0};
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
                    DrawTextEx(ROBOTO, cmd.as.text.text, (Vector2){box.x, box.y}, cmd.as.text.font_size, 0, col);
                }; break;
                default: UNREACHABLE();
            }
        }

        // DrawFPS(0,0);
        DrawTextEx(ROBOTO, "Press 'Space' To Change Theme", (Vector2){5, GetScreenHeight()-20}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        EndDrawing();
        // }}}
    }

    UnloadFont(ICONS);
    UnloadFont(ROBOTO);
    CloseWindow();
    return 0;
}
