#include <assert.h>

#define TABS_COUNT 8

#define TAB_ICON_LABELS \
    X(0, Search,	search) \
    X(1, Home,		home) \
    X(2, Menu,		menu) \
    X(3, Close,		close) \
    X(4, Settings,	settings) \
    X(5, Favorite,	favorite) \
    X(6, Add,		add) \
    X(7, Delete,	delete)

#include "demo-helpers.h"
static const char* TAB_LABELS[TABS_COUNT] = {
    #define X(index, Name, name) #Name,
    TAB_ICON_LABELS
    #undef X
};
static i32 TAB_ICONS[TABS_COUNT];

MDIconAlign ALIGN = MD_ICON_ALIGN_STACKED;

void DrawLayout() {
    // {{{
    char num[2] = {'0', 0};
    f32 max_width = 100 * CTX.scaling;
    for (u8 state = 0; state < 4; state++) {
        f32 offset_x = 0;
        for (u8 active = 0; active < 2; active++) {
            u8 index = state * 2 + active;
            f32 x = 50 + (f32)active * max_width * 2.5;
            f32 y = 50 + (f32)state * 100.0;
            if (active == 0) {
                num[0] = state+1+'0';
                DrawTextEx(ROBOTO, num, (Vector2){x-30, y+30}, 30.0, 0.0, COLOR.Scheme.OnBackground);
            }

            MDCTab input = {0};
            input.box = (MDBox){x, y, max_width, 0};
            input.state = state; input.active = active;
            input.text = (char*)TAB_LABELS[index];
            input.icon_code = TAB_ICONS[index];
            input.icon_align = ALIGN;
            input.type = MDC_TAB_TYPE_PRIMARY;
            MDCTab output = mdc_tab(input);
            mdc_render_tab(output);
            offset_x += output.box.w;

            input = (MDCTab){0};
            input.box = (MDBox){x + output.box.w, y, max_width, 0};
            input.state = 0; input.active = 0;
            input.text = (char*)TAB_LABELS[index];
            input.icon_code = TAB_ICONS[index];
            input.icon_align = ALIGN;
            input.type = MDC_TAB_TYPE_PRIMARY;
            output = mdc_tab(input);
            mdc_render_tab(output);
            offset_x += output.box.w;
        }
    }
    for (u8 state = 0; state < 4; state++) {
        f32 offset_x = 0;
        for (u8 active = 0; active < 2; active++) {
            u8 index = state * 2 + active;
            f32 x = 50 + (f32)active * max_width * 2.5;
            f32 y = 550 + (f32)state * 100.0;
            if (active == 0) {
                num[0] = state+1+'0';
                DrawTextEx(ROBOTO, num, (Vector2){x-30, y+30}, 30.0, 0.0, COLOR.Scheme.OnBackground);
            }

            MDCTab input = {0};
            input.box = (MDBox){x, y, max_width, 0};
            input.state = state; input.active = active;
            input.text = (char*)TAB_LABELS[index];
            input.type = MDC_TAB_TYPE_SECONDARY;
            MDCTab output = mdc_tab(input);
            mdc_render_tab(output);
            offset_x += output.box.w;

            input = (MDCTab){0};
            input.box = (MDBox){x + output.box.w, y, max_width, 0};
            input.state = 0; input.active = 0;
            input.text = (char*)TAB_LABELS[index];
            input.type = MDC_TAB_TYPE_SECONDARY;
            output = mdc_tab(input);
            mdc_render_tab(output);
            offset_x += output.box.w;
        }
    }
    DrawTextEx(ROBOTO, "Primary Inactive",   (Vector2){50+max_width *.5, 15}, 30.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(ROBOTO, "Primary Active",     (Vector2){50+max_width * 3, 15}, 30.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(ROBOTO, "Secondary Inactive", (Vector2){50+max_width *.5, 515}, 30.0, 0.0, COLOR.Scheme.OnBackground);
    DrawTextEx(ROBOTO, "Secondary Active",   (Vector2){50+max_width * 3, 515}, 30.0, 0.0, COLOR.Scheme.OnBackground);
    // }}}
}

int main(void) {
    const int W = 1000;
    const int H = 1000;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "FLOAT");
    // SetTargetFPS(500);
    init_fonts(true, true); // must be done AFTER InitWindow()

    i32 mon = GetCurrentMonitor();
    Vec2 monitor_size = (Vec2){GetMonitorPhysicalWidth(mon), GetMonitorPhysicalHeight(mon)};
    Vec2 monitor_resolution = (Vec2){GetMonitorWidth(mon), GetMonitorHeight(mon)};
    md_ctx_init(monitor_size, monitor_resolution);
    md_ctx_set_scaling(2);
    md_ctx_set_measure_text(measure_text_fn);

    md_color_global_init(true);

    TAB_ICONS[0] = find_icon("flight");
    for (i32 i = 1; i < TABS_COUNT; i++) TAB_ICONS[i] = TAB_ICONS[0];
    // #define X(index, Name, name) TAB_ICONS[index] = find_icon(#name);
    // TAB_ICON_LABELS
    // #undef X

    while (!WindowShouldClose()) {
        // {{{
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
        if (IsKeyPressed(KEY_TAB)) ALIGN = !ALIGN;
        BeginDrawing();
        ClearBackground(COLOR.Scheme.SurfaceContainerLow);

        // dotted background
        i32 dp10 = (i32)md_dp2px(10);
        for (i32 y = 0; y < GetScreenHeight(); y += dp10) {
            for (i32 x = 0; x < GetScreenWidth(); x += dp10) {
                MDColor col = COLOR.Scheme.OnBackground;
                col.a = 51;
                DrawPixel(x, y, col);
            }
        }


        DrawLayout();
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
                default: UNREACHABLE();
            }
            // }}}
        }

        // DrawFPS(0,0);
        DrawTextEx(ROBOTO, "State: 1=Enabled | 2=Hovered | 3=Focused | 4=Pressed", (Vector2){5, GetScreenHeight()-60}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        DrawTextEx(ROBOTO, "Press 'Tab' To Change Icon Alignment", (Vector2){5, GetScreenHeight()-40}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        DrawTextEx(ROBOTO, "Press 'Space' To Change Theme", (Vector2){5, GetScreenHeight()-20}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        EndDrawing();
        // }}}
    }

    free_fonts();
    CloseWindow();
    return 0;
}
