#include "demo-helpers.h"

Vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(ROBOTO, text, font_size_px, 0);
}

Vec2 get_window_size(void) {
    return (Vec2){(f32)GetScreenWidth(), (f32)GetScreenHeight()};
}

void draw_tab(const char* id, MDBox box) {
    Vec2 m = measure_text_fn((char*)id, 20);
    DrawTextEx(ROBOTO, id, (Vector2){box.x + (box.w-m.x)/2, box.y + (box.h-m.y)/2}, 20, 0, COLOR.Scheme.OnBackground);
}

f32 s1 = 0.5;
f32 s2 = 0.5;
f32 i1 = 0.5;
f32 i2 = 0.5;
i32 t1 = 0;
i32 t2 = 0;
i32 t3 = 0;
void MakeLayout(void) {
    // {{{
    // gf2 layout:
    MDL_STACK(&s1) {
        MDL_INLINE(&i1) {
            MDL_TAB("DISASSEMBLY");
            MDL_STACK(&s2) {
                MDL_TABS(&t1) {
                    MDL_TAB("EXE");
                    MDL_TAB("BREAKPOINTS");
                    MDL_TAB("COMMANDS");
                    MDL_TAB("STRUCT");
                }
                MDL_TABS(&t2) {
                    MDL_TAB("STACK");
                    MDL_TAB("FILES");
                    MDL_TAB("THREAD");
                    MDL_TAB("CMDSEARCH");
                }
            }
        }
        MDL_INLINE(&i2) {
            MDL_TAB("CMDLINE");
            MDL_TABS(&t3) {
                MDL_TAB("WATCH");
                MDL_TAB("LOCALS");
                MDL_TAB("REGISTERS");
                MDL_TAB("DATA");
            }
        }
    }
    // }}}
}

int main(void) {
    const int W = 800;
    const int H = 800;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "FLOAT");
    // SetTargetFPS(500);

    md_color_global_init(true);
    init_fonts(false); // demo-helper; must be done AFTER InitWindow()

    i32 mon = GetCurrentMonitor();
    Vec2 monitor_size = (Vec2){GetMonitorPhysicalWidth(mon), GetMonitorPhysicalHeight(mon)};
    Vec2 monitor_resolution = (Vec2){GetMonitorWidth(mon), GetMonitorHeight(mon)};
    md_ctx_init(monitor_size, monitor_resolution);
    md_ctx_set_scaling(2);
    md_ctx_set_measure_text(measure_text_fn);
    md_ctx_set_get_window_size(get_window_size);

    while (!WindowShouldClose()) {
        // {{{
        // MOUSE = GetMousePosition();
        // MOUSE_DOWN = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // MOUSE_PRESSED = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();

        BeginDrawing();
        ClearBackground(COLOR.Scheme.Background);

        // dotted background
        f32 dp = md_dp2px(1);
        for (f32 y = 0; y < GetScreenHeight(); y += dp*10) {
            for (f32 x = 0; x < GetScreenWidth(); x += dp*10) {
                MDColor col = COLOR.Scheme.OnBackground;
                col.a = 51;
                DrawPixel((i32)x, (i32)y, col);
            }
        }

        MakeLayout();
        mdl_render_layout();

        MDCommand cmd = {0};
        while (md_ctx_poll(&cmd)) {
            // {{{
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
                    f32 fs = cmd.as.text.font_size;
                    DrawTextEx(ROBOTO, cmd.as.text.text, (Vector2){box.x, box.y}, fs, 0, col);
                }; break;
                case MD_COMMAND_DRAW_ICON: {
                    MDBox box = cmd.as.icon.box;
                    MDColor col = cmd.as.icon.color;
                    f32 fs = cmd.as.icon.icon_size;
                    // 0.1fs is needed because the font's symbols are not squares,
                    // so by default the icons are shown a bit to the left.
                    DrawTextCodepoint(ICONS, cmd.as.icon.codepoint, (Vector2){box.x+fs*0.1, box.y}, fs, col);
                }; break;
                case MD_COMMAND_DRAW_LAYOUT: {
                    MDBox box = cmd.as.layout.box;
                    const char* id = cmd.as.layout.id;
                    draw_tab(id, box);
                }; break;
                default: UNREACHABLE();
            }
            // }}}
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
