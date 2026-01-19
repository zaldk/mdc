#include "demo-helpers.h"

Vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(ROBOTO, text, font_size_px, 0);
}

void tree_print_specific(i32 idx, int depth) {
    if (idx == -1) return;

    MDElement* elem = &CTX.elems[idx];

    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d\n", elem->comp.type);

    for (i32 child = elem->child_first; child != MD_NIL_ELEMENT;) {
        tree_print_specific(child, depth + 1);
        child = CTX.elems[child].sibling_next;
    }
}
void tree_print() {
    for (i32 i = 0; i < MD_MAX_ELEMENTS; i++) {
        if (CTX.elems[i].parent != -1 || CTX.elems[i].child_first == -1) continue;
        tree_print_specific(i, 0);
    }
}

int main(void) {
    const int W = 600;
    const int H = 600;

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

    MDL(.type=1) {
        MDL(.type=2) {
            MDL(.type=3);
            MDL(.type=4);
        }
        MDL(.type=5) {
            MDL(.type=6);
        }
    }
    MDL(.type=7) {
        MDL(.type=8) {
            MDL(.type=9);
            MDL(.type=10);
        }
        MDL(.type=11) {
            MDL(.type=12);
        }
    }
    tree_print();
    // __asm("int3");

    // while (!WindowShouldClose()) {
    //     {{{
    //     // MOUSE = GetMousePosition();
    //     // MOUSE_DOWN = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    //     // MOUSE_PRESSED = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    //     if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
    //
    //     BeginDrawing();
    //     ClearBackground(COLOR.Scheme.Background);
    //
    //     // dotted background
    //     f32 dp = md_dp2px(1);
    //     for (f32 y = 0; y < GetScreenHeight(); y += dp*10) {
    //         for (f32 x = 0; x < GetScreenWidth(); x += dp*10) {
    //             MDColor col = COLOR.Scheme.OnBackground;
    //             col.a = 51;
    //             DrawPixel((i32)x, (i32)y, col);
    //         }
    //     }
    //
    //     MDCommand cmd = {0};
    //     while (md_ctx_poll(&cmd)) {
    //         // {{{
    //         switch (cmd.type) {
    //             case MD_COMMAND_DRAW_BOX: {
    //                 MDBox box = cmd.as.box.box;
    //                 MDCorners round = cmd.as.box.round;
    //                 MDColor col = cmd.as.box.color;
    //                 DrawBoxRound(box.x, box.y, box.w, box.h, round.tl, round.tr, round.bl, round.br, col);
    //             }; break;
    //             case MD_COMMAND_DRAW_OUTLINE: {
    //                 MDBox box = cmd.as.outline.box;
    //                 MDCorners round = cmd.as.outline.round;
    //                 MDColor col = cmd.as.outline.color;
    //                 f32 thickness = cmd.as.outline.thickness;
    //                 DrawBoxRoundLines(box.x, box.y, box.w, box.h, round.tl, round.tr, round.bl, round.br, thickness, col);
    //             }; break;
    //             case MD_COMMAND_DRAW_TEXT: {
    //                 MDBox box = cmd.as.text.box;
    //                 MDColor col = cmd.as.text.color;
    //                 f32 fs = cmd.as.text.font_size;
    //                 DrawTextEx(ROBOTO, cmd.as.text.text, (Vector2){box.x, box.y}, fs, 0, col);
    //             }; break;
    //             case MD_COMMAND_DRAW_ICON: {
    //                 MDBox box = cmd.as.icon.box;
    //                 MDColor col = cmd.as.icon.color;
    //                 f32 fs = cmd.as.icon.icon_size;
    //                 // 0.1fs is needed because the font's symbols are not squares,
    //                 // so by default the icons are shown a bit to the left.
    //                 DrawTextCodepoint(ICONS, cmd.as.icon.codepoint, (Vector2){box.x+fs*0.1, box.y}, fs, col);
    //             }; break;
    //             default: UNREACHABLE();
    //         }
    //         // }}}
    //     }
    //
    //     // DrawFPS(0,0);
    //     DrawTextEx(ROBOTO, "Press 'Space' To Change Theme", (Vector2){5, GetScreenHeight()-20}, 20.0, 0.0, COLOR.Scheme.OnBackground);
    //     EndDrawing();
    //     // }}}
    // }

    UnloadFont(ICONS);
    UnloadFont(ROBOTO);
    CloseWindow();
    return 0;
}
