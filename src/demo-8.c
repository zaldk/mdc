#include "demo-helpers.h"

Vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(ROBOTO, text, font_size_px, 0);
}

Vec2 get_window_size_fn(void) {
    return (Vec2){(f32)GetScreenWidth(), (f32)GetScreenHeight()};
}

Vec2 get_mouse_position_fn(void) {
    return GetMousePosition();
}

bool button_down_fn(MDInputButton button) {
    switch (button) {
        case MD_INPUT_LMB: return IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        case MD_INPUT_RMB: return IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        default: UNREACHABLE();
    }
}
bool button_pressed_fn(MDInputButton button) {
    switch (button) {
        case MD_INPUT_LMB: return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        case MD_INPUT_RMB: return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
        default: UNREACHABLE();
    }
}

void draw_tab(MDBox box, const char* name, i32 id) {
    Vec2 m = measure_text_fn((char*)name, 20);
    DrawTextEx(ROBOTO, name, (Vector2){box.x + (box.w-m.x)/2, box.y + (box.h-m.y)/2}, 20, 0, COLOR.Scheme.OnBackground);
    DrawTextEx(ROBOTO, TextFormat("\n%d", id), (Vector2){box.x + (box.w-m.x)/2, box.y + (box.h-m.y)/2}, 20, 0, COLOR.Scheme.OnBackground);
}

f32 s1 = 0.5;
f32 s2 = 0.5;
f32 s3 = 0.5;
f32 i1 = 0.5;
f32 i2 = 0.25;
i32 t1 = 1;
i32 t2 = 2;
i32 t3 = 0;
void MakeLayout(void) {
    // {{{
    // gf2 layout:
    MDL_STACK(&s1) {
        MDL_INLINE(&i1) {
            MDL_TAB("Disassembly");
            MDL_STACK(&s2) {
                MDL_TABS(&t1) {
                    MDL_TAB("Exe");
                    MDL_TAB("Breakpoints");
                    MDL_TAB("Commands");
                    MDL_TAB("Struct");
                }
                MDL_TABS(&t2) {
                    MDL_TAB("Stack");
                    MDL_TAB("Files");
                    MDL_TAB("Thread");
                    MDL_TAB("CmdSearch");
                }
            }
        }
        MDL_INLINE(&i2) {
            MDL_TAB("CmdLine");
            MDL_TABS(&t3) {
                MDL_TAB("Watch") {
                    MDL_INLINE(&s3) {
                        MDL_TAB("Analog");
                        MDL_TAB("Digital");
                    }
                }
                MDL_TAB("Locals");
                MDL_TAB("Registers");
                MDL_TAB("Data");
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
    SetTargetFPS(120);

    md_color_global_init(true);
    init_fonts(false); // demo-helper; must be done AFTER InitWindow()

    i32 mon = GetCurrentMonitor();
    Vec2 monitor_size = (Vec2){GetMonitorPhysicalWidth(mon), GetMonitorPhysicalHeight(mon)};
    Vec2 monitor_resolution = (Vec2){GetMonitorWidth(mon), GetMonitorHeight(mon)};
    md_ctx_init(monitor_size, monitor_resolution);
    md_ctx_set_scaling(2);
    md_ctx_set_measure_text(measure_text_fn);
    // for the layouting engine
    md_ctx_set_get_window_size(get_window_size_fn);
    md_ctx_set_get_mouse_pos(get_mouse_position_fn);
    md_ctx_set_button_down(button_down_fn);
    md_ctx_set_button_pressed(button_pressed_fn);

    // const f32 dp = md_dp2px(1);
    while (!WindowShouldClose()) {
        // {{{
        CTX.id_gen = 0;
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();

        BeginDrawing();
        ClearBackground(COLOR.Scheme.Surface);

        MakeLayout();
        if (!mdl_update_and_render_layout()) break;

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
                    draw_tab(cmd.as.layout.box, cmd.as.layout.name, cmd.as.layout.id);
                }; break;
                default: UNREACHABLE();
            }
            // }}}
        }

        DrawFPS(0,0);
        DrawTextEx(ROBOTO, "Press 'Space' To Change Theme", (Vector2){5, GetScreenHeight()-20}, 20.0, 0.0, COLOR.Scheme.OnSurface);
        EndDrawing();
        // }}}
    }

    UnloadFont(ICONS);
    UnloadFont(ROBOTO);
    CloseWindow();
    return 0;
}
